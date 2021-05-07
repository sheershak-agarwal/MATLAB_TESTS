//
// runQPSKSystemUnderTest.cpp
//
// Code generation for function 'runQPSKSystemUnderTest'
//

// Include files
#include "runQPSKSystemUnderTest.h"
#include "AGC.h"
#include "CarrierSynchronizer.h"
#include "CoarseFrequencyCompensator.h"
#include "Descrambler.h"
#include "ErrorRate.h"
#include "FIRDecimator.h"
#include "FIRInterpolator.h"
#include "FrameSynchronizer.h"
#include "PhaseFrequencyOffset.h"
#include "PreambleDetector.h"
#include "QPSKBitsGenerator.h"
#include "QPSKDataDecoder.h"
#include "QPSKDemodulator.h"
#include "QPSKModulator.h"
#include "QPSKReceiver.h"
#include "QPSKTransmitter.h"
#include "RaisedCosineReceiveFilter.h"
#include "RaisedCosineTransmitFilter.h"
#include "Scrambler.h"
#include "SymbolSynchronizer.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <cstring>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <signal.h>
#include <stdio.h>

#include <iio.h>

/* helper macros */
#define MHZ(x) ((long long)(x*1000000.0 + .5))
#define GHZ(x) ((long long)(x*1000000000.0 + .5))

#define IIO_ENSURE(expr) { \
	if (!(expr)) { \
		fprintf(stderr, "assertion failed (%s:%d)\n", __FILE__, __LINE__); \
		abort(); \
	} \
}

/* RX is input, TX is output */
enum iodev { RX, TX };

/* common RX and TX streaming params */
struct stream_cfg {
	long long bw_hz; // Analog banwidth in Hz
	long long fs_hz; // Baseband sample rate in Hz
	long long lo_hz; // Local oscillator frequency in Hz
	const char* rfport; // Port name
};

/* static scratch mem for strings */
static char tmpstr[64];

/* IIO structs required for streaming */
static struct iio_context *ctx   = NULL;
static struct iio_channel *rx0_i = NULL;
static struct iio_channel *rx0_q = NULL;
static struct iio_channel *tx0_i = NULL;
static struct iio_channel *tx0_q = NULL;
static struct iio_buffer  *rxbuf = NULL;
static struct iio_buffer  *txbuf = NULL;


/* cleanup and exit */
static void shutdown()
{
	printf("* Destroying buffers\n");
	if (rxbuf) { iio_buffer_destroy(rxbuf); }
	if (txbuf) { iio_buffer_destroy(txbuf); }

	printf("* Disabling streaming channels\n");
	if (rx0_i) { iio_channel_disable(rx0_i); }
	if (rx0_q) { iio_channel_disable(rx0_q); }
	if (tx0_i) { iio_channel_disable(tx0_i); }
	if (tx0_q) { iio_channel_disable(tx0_q); }

	printf("* Destroying context\n");
	if (ctx) { iio_context_destroy(ctx); }
	exit(0);
}

/* check return value of attr_write function */
static void errchk(int v, const char* what) {
	 if (v < 0) { fprintf(stderr, "Error %d writing to channel \"%s\"\nvalue may not be supported.\n", v, what); shutdown(); }
}

/* write attribute: long long int */
static void wr_ch_lli(struct iio_channel *chn, const char* what, long long val)
{
	errchk(iio_channel_attr_write_longlong(chn, what, val), what);
}

/* write attribute: string */
static void wr_ch_str(struct iio_channel *chn, const char* what, const char* str)
{
	errchk(iio_channel_attr_write(chn, what, str), what);
}

/* helper function generating channel names */
static char* get_ch_name(const char* type, int id)
{
	snprintf(tmpstr, sizeof(tmpstr), "%s%d", type, id);
	return tmpstr;
}

/* returns ad9361 phy device */
static struct iio_device* get_ad9361_phy(struct iio_context *ctx)
{
	struct iio_device *dev =  iio_context_find_device(ctx, "ad9361-phy");
	IIO_ENSURE(dev && "No ad9361-phy found");
	return dev;
}

/* finds AD9361 streaming IIO devices */
static bool get_ad9361_stream_dev(struct iio_context *ctx, enum iodev d, struct iio_device **dev)
{
	switch (d) {
	case TX: *dev = iio_context_find_device(ctx, "cf-ad9361-dds-core-lpc"); return *dev != NULL;
	case RX: *dev = iio_context_find_device(ctx, "cf-ad9361-lpc");  return *dev != NULL;
	default: IIO_ENSURE(0); return false;
	}
}

/* finds AD9361 streaming IIO channels */
static bool get_ad9361_stream_ch(__notused struct iio_context *ctx, enum iodev d, struct iio_device *dev, int chid, struct iio_channel **chn)
{
	*chn = iio_device_find_channel(dev, get_ch_name("voltage", chid), d == TX);
	if (!*chn)
		*chn = iio_device_find_channel(dev, get_ch_name("altvoltage", chid), d == TX);
	return *chn != NULL;
}

/* finds AD9361 phy IIO configuration channel with id chid */
static bool get_phy_chan(struct iio_context *ctx, enum iodev d, int chid, struct iio_channel **chn)
{
	switch (d) {
	case RX: *chn = iio_device_find_channel(get_ad9361_phy(ctx), get_ch_name("voltage", chid), false); return *chn != NULL;
	case TX: *chn = iio_device_find_channel(get_ad9361_phy(ctx), get_ch_name("voltage", chid), true);  return *chn != NULL;
	default: IIO_ENSURE(0); return false;
	}
}

/* finds AD9361 local oscillator IIO configuration channels */
static bool get_lo_chan(struct iio_context *ctx, enum iodev d, struct iio_channel **chn)
{
	switch (d) {
	 // LO chan is always output, i.e. true
	case RX: *chn = iio_device_find_channel(get_ad9361_phy(ctx), get_ch_name("altvoltage", 0), true); return *chn != NULL;
	case TX: *chn = iio_device_find_channel(get_ad9361_phy(ctx), get_ch_name("altvoltage", 1), true); return *chn != NULL;
	default: IIO_ENSURE(0); return false;
	}
}

/* applies streaming configuration through IIO */
bool cfg_ad9361_streaming_ch(struct iio_context *ctx, struct stream_cfg *cfg, enum iodev type, int chid)
{
	struct iio_channel *chn = NULL;

	// Configure phy and lo channels
	printf("* Acquiring AD9361 phy channel %d\n", chid);
	if (!get_phy_chan(ctx, type, chid, &chn)) {	return false; }
	wr_ch_str(chn, "rf_port_select",     cfg->rfport);
	wr_ch_lli(chn, "rf_bandwidth",       cfg->bw_hz);
	wr_ch_lli(chn, "sampling_frequency", cfg->fs_hz);

	// Configure LO channel
	printf("* Acquiring AD9361 %s lo channel\n", type == TX ? "TX" : "RX");
	if (!get_lo_chan(ctx, type, &chn)) { return false; }
	wr_ch_lli(chn, "frequency", cfg->lo_hz);
	return true;
}

// Function Definitions
void runQPSKSystemUnderTest(double BER[3])
{

// Streaming devices
	struct iio_device *tx;
	struct iio_device *rx;

	// RX and TX sample counters
	size_t nrx = 0;
	size_t ntx = 0;

	// Stream configurations
	struct stream_cfg rxcfg;
	struct stream_cfg txcfg;

	// RX stream config
	rxcfg.bw_hz = MHZ(2);   // 2 MHz rf bandwidth
	rxcfg.fs_hz = MHZ(2.5);   // 2.5 MS/s rx sample rate
	rxcfg.lo_hz = MHZ(900); // 2.5 GHz rf frequency
	rxcfg.rfport = "A_BALANCED"; // port A (select for rf freq.)

	// TX stream config
	txcfg.bw_hz = MHZ(2); // 1.5 MHz rf bandwidth
	txcfg.fs_hz = MHZ(2.5);   // 2.5 MS/s tx sample rate
	txcfg.lo_hz = MHZ(900); // 2.5 GHz rf frequency
	txcfg.rfport = "A"; // port A (select for rf freq.)

	printf("* Acquiring IIO context\n");
	IIO_ENSURE((ctx = iio_create_default_context()) && "No context");

	IIO_ENSURE(iio_context_get_devices_count(ctx) > 0 && "No devices");

	printf("* Acquiring AD9361 streaming devices\n");
	IIO_ENSURE(get_ad9361_stream_dev(ctx, TX, &tx) && "No tx dev found");
	IIO_ENSURE(get_ad9361_stream_dev(ctx, RX, &rx) && "No rx dev found");

	printf("* Configuring AD9361 for streaming\n");
	IIO_ENSURE(cfg_ad9361_streaming_ch(ctx, &rxcfg, RX, 0) && "RX port 0 not found");
	IIO_ENSURE(cfg_ad9361_streaming_ch(ctx, &txcfg, TX, 0) && "TX port 0 not found");

	printf("* Initializing AD9361 IIO streaming channels\n");
	IIO_ENSURE(get_ad9361_stream_ch(ctx, RX, rx, 0, &rx0_i) && "RX chan i not found");
	IIO_ENSURE(get_ad9361_stream_ch(ctx, RX, rx, 1, &rx0_q) && "RX chan q not found");
	IIO_ENSURE(get_ad9361_stream_ch(ctx, TX, tx, 0, &tx0_i) && "TX chan i not found");
	IIO_ENSURE(get_ad9361_stream_ch(ctx, TX, tx, 1, &tx0_q) && "TX chan q not found");

	printf("* Enabling IIO streaming channels\n");
	iio_channel_enable(rx0_i);
	iio_channel_enable(rx0_q);
	iio_channel_enable(tx0_i);
	iio_channel_enable(tx0_q);

	printf("* Creating non-cyclic IIO buffers with 1 MiS\n");
	rxbuf = iio_device_create_buffer(rx, 2266, false);
	if (!rxbuf) {
		perror("Could not create RX buffer");
		shutdown();
	}
	txbuf = iio_device_create_buffer(tx, 2266, false);
	if (!txbuf) {
		perror("Could not create TX buffer");
		shutdown();
	}

  static QPSKReceiver qpskRx;
  static creal_T transmittedSignal[2266];
  static creal_T receivedSignal[2266];
  static creal_T varargout_1[2266];
  QPSKDataDecoder *c_obj;
  QPSKTransmitter qpskTx;
  coder::commcodegen::PhaseFrequencyOffset *obj;
  coder::dspcodegen::FIRDecimator *b_obj;
  comm_ErrorRate_7 *d_obj;
  creal_T varargout_2_data[1247];
  creal_T varargout_3_data[1247];
  int i;
  int sIdx;
  qpskTx.pBitGenerator.pScrambler.matlabCodegenIsDeleted = true;
  qpskTx.pBitGenerator.matlabCodegenIsDeleted = true;
  qpskTx.pQPSKModulator.matlabCodegenIsDeleted = true;
  qpskTx.pTransmitterFilter._pobj0.matlabCodegenIsDeleted = true;
  qpskTx.pTransmitterFilter.matlabCodegenIsDeleted = true;
  qpskTx.matlabCodegenIsDeleted = true;
  qpskRx.pRxFilter._pobj0.matlabCodegenIsDeleted = true;
  qpskRx.pRxFilter.matlabCodegenIsDeleted = true;
  qpskRx.pCoarseFreqEstimator.matlabCodegenIsDeleted = true;
  qpskRx.pCoarseFreqCompensator.matlabCodegenIsDeleted = true;
  qpskRx.pTimingRec.matlabCodegenIsDeleted = true;
  qpskRx.pFrameSync.matlabCodegenIsDeleted = true;
  qpskRx.pDataDecod.pQPSKDemodulator.matlabCodegenIsDeleted = true;
  qpskRx.pDataDecod.pDescrambler.matlabCodegenIsDeleted = true;
  qpskRx.pDataDecod.pErrorRateCalc.matlabCodegenIsDeleted = true;
  qpskRx.pDataDecod.matlabCodegenIsDeleted = true;
  qpskRx.matlabCodegenIsDeleted = true;
  qpskTx.isInitialized = 0;
  qpskTx.matlabCodegenIsDeleted = false;
  qpskRx.isInitialized = 0;
  qpskRx.matlabCodegenIsDeleted = false;
  //      if useScopes
  //          qpskScopes = QPSKScopes('SampleRate', 10e4);
  //      end
	
	printf("TransmittedSignal Created\n");
	qpskTx.step(transmittedSignal);
	//for (int i = 0; i < 2266; i++) {
	//	printf("%f, %f\n",transmittedSignal[i].re, transmittedSignal[i].im);
	//}
  for (int count{0}; count < 1000; count++) {

    ssize_t nbytes_rx, nbytes_tx;
    char *p_dat, *p_end;
		ptrdiff_t p_inc;

		// Schedule TX buffer
		nbytes_tx = iio_buffer_push(txbuf);
		if (nbytes_tx < 0) { printf("Error pushing buf %d\n", (int) nbytes_tx); shutdown(); }

		// Refill RX buffer
		nbytes_rx = iio_buffer_refill(rxbuf);
		if (nbytes_rx < 0) { printf("Error refilling buf %d\n",(int) nbytes_rx); shutdown(); }

		// WRITE: Get pointers to TX buf and write IQ to TX buf port 0
		p_inc = iio_buffer_step(txbuf);
		p_end = (char*)iio_buffer_end(txbuf);
		int index = 0;
		for (p_dat = (char *)iio_buffer_first(txbuf, tx0_i); p_dat < p_end; p_dat += p_inc) {
			((int16_t*)p_dat)[0] = transmittedSignal[index].re; // Real (I)
			((int16_t*)p_dat)[1] = transmittedSignal[index].im; // Imag (Q)
			index+=1;
		}
		
		// READ: Get pointers to RX buf and read IQ from RX buf port 0
		p_inc = iio_buffer_step(rxbuf);
		p_end = (char*)iio_buffer_end(rxbuf);
		index =0;
		for (p_dat = (char *)iio_buffer_first(rxbuf, rx0_i); p_dat < p_end; p_dat += p_inc) {
			const int16_t i = ((int16_t*)p_dat)[0]; // Real (I)
			const int16_t q = ((int16_t*)p_dat)[1]; // Imag (Q)
			receivedSignal[index].re = i;
			receivedSignal[index].im = q;
			index+=1;
		}

    if (qpskRx.isInitialized != 1) {
      boolean_T flag;
      qpskRx.isSetupComplete = false;
      qpskRx.isInitialized = 1;
      qpskRx.pAGC.AdaptationStepSize = 0.01;
      qpskRx.pAGC.pStepSizeSet = false;
      qpskRx.pAGC.pDetectorMethodSet = false;
      qpskRx.pAGC.pLoopMethodSet = false;
      qpskRx.pAGC.pUpdatePeriodSet = false;
      qpskRx.pAGC.pGainOutputPortSet = false;
      qpskRx.pAGC.isInitialized = 0;
      qpskRx.pRxFilter.isInitialized = 0;
      qpskRx.pRxFilter.matlabCodegenIsDeleted = false;
      qpskRx.pCoarseFreqEstimator.isInitialized = 0;
      qpskRx.pCoarseFreqEstimator.matlabCodegenIsDeleted = false;
      // .
      obj = &qpskRx.pCoarseFreqCompensator;
      qpskRx.pCoarseFreqCompensator.isInitialized = 0;
      // System object Constructor function: comm.PhaseFrequencyOffset
      obj->cSFunObject.P0_Phase = 0.0;
      qpskRx.pCoarseFreqCompensator.matlabCodegenIsDeleted = false;
      qpskRx.pMeanFreqOff = 0.0;
      qpskRx.pCnt = 0.0;
      qpskRx.pFineFreqCompensator.CustomPhaseOffset = 0.0;
      qpskRx.pFineFreqCompensator.isInitialized = 0;
      flag = (qpskRx.pFineFreqCompensator.isInitialized == 1);
      if (flag) {
        qpskRx.pFineFreqCompensator.TunablePropsChanged = true;
      }
      qpskRx.pFineFreqCompensator.ModulationPhaseOffset[0] = 'A';
      qpskRx.pFineFreqCompensator.ModulationPhaseOffset[1] = 'u';
      qpskRx.pFineFreqCompensator.ModulationPhaseOffset[2] = 't';
      qpskRx.pFineFreqCompensator.ModulationPhaseOffset[3] = 'o';
      flag = (qpskRx.pFineFreqCompensator.isInitialized == 1);
      if (flag) {
        qpskRx.pFineFreqCompensator.TunablePropsChanged = true;
      }
      qpskRx.pFineFreqCompensator.SamplesPerSymbol = 2.0;
      flag = (qpskRx.pFineFreqCompensator.isInitialized == 1);
      if (flag) {
        qpskRx.pFineFreqCompensator.TunablePropsChanged = true;
      }
      qpskRx.pFineFreqCompensator.DampingFactor = 1.0;
      flag = (qpskRx.pFineFreqCompensator.isInitialized == 1);
      if (flag) {
        qpskRx.pFineFreqCompensator.TunablePropsChanged = true;
      }
      qpskRx.pFineFreqCompensator.NormalizedLoopBandwidth = 0.01;
      qpskRx.pTimingRec.isInitialized = 0;
      flag = (qpskRx.pTimingRec.isInitialized == 1);
      if (flag) {
        qpskRx.pTimingRec.TunablePropsChanged = true;
      }
      qpskRx.pTimingRec.DampingFactor = 1.0;
      flag = (qpskRx.pTimingRec.isInitialized == 1);
      if (flag) {
        qpskRx.pTimingRec.TunablePropsChanged = true;
      }
      qpskRx.pTimingRec.NormalizedLoopBandwidth = 0.01;
      flag = (qpskRx.pTimingRec.isInitialized == 1);
      if (flag) {
        qpskRx.pTimingRec.TunablePropsChanged = true;
      }
      qpskRx.pTimingRec.DetectorGain = 2.7;
      qpskRx.pTimingRec.matlabCodegenIsDeleted = false;
      qpskRx.pPrbDet.isInitialized = 0;
      flag = (qpskRx.pPrbDet.isInitialized == 1);
      if (flag) {
        qpskRx.pPrbDet.TunablePropsChanged = true;
      }
      qpskRx.pPrbDet.Threshold = 20.0;
      qpskRx.pFrameSync.isInitialized = 0;
      qpskRx.pFrameSync.matlabCodegenIsDeleted = false;
      //  For BER calculation masks
      qpskRx.pDataDecod.isInitialized = 0;
      qpskRx.pDataDecod.matlabCodegenIsDeleted = false;
      qpskRx.isSetupComplete = true;
      if (qpskRx.pAGC.isInitialized == 1) {
        qpskRx.pAGC.Gain = 0.0;
        std::memset(&qpskRx.pAGC.pFilterState[0], 0, 49U * sizeof(double));
        qpskRx.pAGC.pFilterSum = 0.0;
        qpskRx.pAGC.pFilterStateIdx = 1U;
      }
      if (qpskRx.pRxFilter.isInitialized == 1) {
        b_obj = qpskRx.pRxFilter.pFilter;
        if (b_obj->isInitialized == 1) {
          // System object Initialization function: dsp.FIRDecimator
          b_obj->cSFunObject.W2_CoeffIdx = 0;
          b_obj->cSFunObject.W0_PhaseIdx = 0;
          b_obj->cSFunObject.W4_TapDelayIndex = 0;
          b_obj->cSFunObject.W1_Sums.re = 0.0;
          b_obj->cSFunObject.W1_Sums.im = 0.0;
          for (i = 0; i < 20; i++) {
            b_obj->cSFunObject.W3_StatesBuff[i].re = 0.0;
            b_obj->cSFunObject.W3_StatesBuff[i].im = 0.0;
          }
        }
      }
      if (qpskRx.pCoarseFreqEstimator.isInitialized == 1) {
        std::memset(&qpskRx.pCoarseFreqEstimator.pRaisedSignalBuffer[0], 0,
                    32U * sizeof(creal_T));
        qpskRx.pCoarseFreqEstimator.pCumFreqOffset = 0.0;
        std::memset(&qpskRx.pCoarseFreqEstimator.pScratchVar[0], 0,
                    2266U * sizeof(creal_T));
      }
      obj = &qpskRx.pCoarseFreqCompensator;
      if (qpskRx.pCoarseFreqCompensator.isInitialized == 1) {
        // System object Initialization function: comm.PhaseFrequencyOffset
        obj->cSFunObject.W0_freqTnow = 0.0;
      }
      if (qpskRx.pFineFreqCompensator.isInitialized == 1) {
        qpskRx.pFineFreqCompensator.pLoopFilterState = 0.0;
        qpskRx.pFineFreqCompensator.pIntegFilterState = 0.0;
        qpskRx.pFineFreqCompensator.pDDSPreviousInput = 0.0;
        qpskRx.pFineFreqCompensator.pPhase = 0.0;
        qpskRx.pFineFreqCompensator.pPreviousSample.re = 0.0;
        qpskRx.pFineFreqCompensator.pPreviousSample.im = 0.0;
      }
      if (qpskRx.pTimingRec.isInitialized == 1) {
        qpskRx.pTimingRec.resetImpl();
      }
      if (qpskRx.pPrbDet.isInitialized == 1) {
        std::memset(&qpskRx.pPrbDet.pFilterStates[0], 0, 12U * sizeof(creal_T));
      }
      if (qpskRx.pFrameSync.isInitialized == 1) {
        qpskRx.pFrameSync.pNBuffer = 0.0;
        qpskRx.pFrameSync.pBufferStartIdx = 0.0;
        qpskRx.pFrameSync.pBufferEndIdx = 0.0;
        for (i = 0; i < 5; i++) {
          qpskRx.pFrameSync.pPrbIdxBuffer[i] = 0.0;
        }
        qpskRx.pFrameSync.pNPrbIdxBuffer = 0.0;
        qpskRx.pFrameSync.pPrbIdxBufferStartIdx = 1.0;
      }
      if (qpskRx.pDataDecod.isInitialized == 1) {
        c_obj = &qpskRx.pDataDecod;
        if (c_obj->pDescrambler.isInitialized == 1) {
          // System object Initialization function: comm.Descrambler
          c_obj->pDescrambler.cSFunObject.W0_shiftReg[0] =
              c_obj->pDescrambler.cSFunObject.P1_IniState[0];
          c_obj->pDescrambler.cSFunObject.W0_shiftReg[1] =
              c_obj->pDescrambler.cSFunObject.P1_IniState[1];
          c_obj->pDescrambler.cSFunObject.W0_shiftReg[2] =
              c_obj->pDescrambler.cSFunObject.P1_IniState[2];
          c_obj->pDescrambler.cSFunObject.W0_shiftReg[3] =
              c_obj->pDescrambler.cSFunObject.P1_IniState[3];
        }
        if (c_obj->pErrorRateCalc.isInitialized == 1) {
          d_obj = &c_obj->pErrorRateCalc.cSFunObject;
          // System object Initialization function: comm.ErrorRate
          c_obj->pErrorRateCalc.cSFunObject.W0_errors = 0.0;
          c_obj->pErrorRateCalc.cSFunObject.W1_symbols = 0.0;
          c_obj->pErrorRateCalc.cSFunObject.W2_STDelay = 0;
          c_obj->pErrorRateCalc.cSFunObject.W4_curTx = 0;
          for (i = 0; i < 2240; i++) {
            d_obj->W5_useFrame[i] = false;
          }
          for (i = 0; i < 1540; i++) {
            sIdx = static_cast<int>(std::floor(d_obj->P0_Subframe[i]));
            if (sIdx > 0) {
              d_obj->W5_useFrame[sIdx - 1] = true;
            }
          }
        }
        c_obj->pBER[0] = 0.0;
        c_obj->pBER[1] = 0.0;
        c_obj->pBER[2] = 0.0;
      }
      qpskRx.pMeanFreqOff = 0.0;
      qpskRx.pCnt = 0.0;
    }
    qpskRx.stepImpl(receivedSignal, varargout_1, varargout_2_data, &sIdx,
                    varargout_3_data, &i, BER);
    //  Receiver
    //          if useScopes
    //              qpskScopes(transmittedSignal, RCRxSignal, timingRecSignal,
    //              freqRecSignal); % Plots all the scopes
    //          end
		// Sample counter increment and status output
		nrx += nbytes_rx / iio_device_get_sample_size(rx);
		ntx += nbytes_tx / iio_device_get_sample_size(tx);
  }
  qpskRx.matlabCodegenDestructor();
  qpskRx.pDataDecod.matlabCodegenDestructor();
  qpskRx.pDataDecod.pErrorRateCalc.matlabCodegenDestructor();
  qpskRx.pDataDecod.pDescrambler.matlabCodegenDestructor();
  qpskRx.pDataDecod.pQPSKDemodulator.matlabCodegenDestructor();
  qpskRx.pFrameSync.matlabCodegenDestructor();
  qpskRx.pTimingRec.matlabCodegenDestructor();
  qpskRx.pCoarseFreqCompensator.matlabCodegenDestructor();
  qpskRx.pCoarseFreqEstimator.matlabCodegenDestructor();
  qpskRx.pRxFilter.matlabCodegenDestructor();
  qpskRx.pRxFilter._pobj0.matlabCodegenDestructor();
  qpskTx.matlabCodegenDestructor();
  qpskTx.pTransmitterFilter.matlabCodegenDestructor();
  qpskTx.pTransmitterFilter._pobj0.matlabCodegenDestructor();
  qpskTx.pQPSKModulator.matlabCodegenDestructor();
  qpskTx.pBitGenerator.matlabCodegenDestructor();
  qpskTx.pBitGenerator.pScrambler.matlabCodegenDestructor();
}

// End of code generation (runQPSKSystemUnderTest.cpp)

