//
// qpskApp.cpp
//
// Code generation for function 'qpskApp'
//

// Include files
#include "qpskApp.h"
#include "AGC.h"
#include "AsyncBuffer.h"
#include "AsyncBuffercgHelper.h"
#include "CarrierSynchronizer.h"
#include "CoarseFrequencyCompensator.h"
#include "Descrambler.h"
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
#include "qpskApp_data.h"
#include "qpskApp_initialize.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <algorithm>
#include <cfloat>
#include <cmath>
#include <cstddef>
#include <cstring>
#include <stdio.h>
#include <string.h>

// Variable Definitions
static QPSKTransmitter qpskTx;

static boolean_T qpskTx_not_empty;

static QPSKReceiver qpskRx;

// Function Declarations
static double rt_remd_snf(double u0, double u1);

// Function Definitions
static double rt_remd_snf(double u0, double u1)
{
  double y;
  if (std::isnan(u0) || std::isnan(u1) || std::isinf(u0)) {
    y = rtNaN;
  } else if (std::isinf(u1)) {
    y = u0;
  } else if ((u1 != 0.0) && (u1 != std::trunc(u1))) {
    double q;
    q = std::abs(u0 / u1);
    if (!(std::abs(q - std::floor(q + 0.5)) > DBL_EPSILON * q)) {
      y = 0.0 * u0;
    } else {
      y = std::fmod(u0, u1);
    }
  } else {
    y = std::fmod(u0, u1);
  }
  return y;
}

double qpskApp()
{
  static const double dv[8]{0.70710678118654757,  0.70710678118654757,
                            -0.70710678118654746, 0.70710678118654757,
                            -0.70710678118654768, -0.70710678118654746,
                            0.70710678118654735,  -0.70710678118654768};
  static double b[11200];
  static const char varargin_52[11]{'h', 'e', 'l', 'l', 'o', ' ',
                                    'w', 'o', 'r', 'l', 'd'};
  coder::commcodegen::PhaseFrequencyOffset *c_obj;
  coder::commcodegen::QPSKModulator *obj;
  coder::dspcodegen::FIRDecimator *d_obj;
  coder::dspcodegen::FIRInterpolator *b_obj;
  coder::array<char, 2U> charStr;
  comm_Descrambler_6 *e_obj;
  creal_T transmittedSignal_data[2266];
  creal_T varargout_1;
  creal_T varargout_2_data;
  creal_T varargout_3_data;
  double BER;
  int transmittedSignal_size[2];
  int count;
  int msgCnt;
  int nbytes;
  short berMask[1540];
  signed char b_b[11200];
  unsigned char msgSet[1600];
  if (!isInitialized_qpskApp) {
    qpskApp_initialize();
  }
  //  Message generation and BER calculation parameters
  for (msgCnt = 0; msgCnt < 100; msgCnt++) {
    nbytes = snprintf(nullptr, 0, "%s %03d\n", "hello world", msgCnt);
    charStr.set_size(1, nbytes + 1);
    snprintf(&charStr[0], (size_t)(nbytes + 1), "%s %03d\n", "hello world",
             msgCnt);
    if (1 > nbytes) {
      nbytes = 0;
    }
    charStr.set_size(charStr.size(0), nbytes);
    nbytes = msgCnt << 4;
    for (count = 0; count < 16; count++) {
      msgSet[count + nbytes] = static_cast<unsigned char>(charStr[count]);
    }
  }
  std::memset(&b[0], 0, 11200U * sizeof(double));
  for (msgCnt = 0; msgCnt < 1600; msgCnt++) {
    double tmp;
    nbytes = 1;
    tmp = msgSet[msgCnt];
    while ((nbytes <= 7) && (tmp > 0.0)) {
      b[msgCnt + 1600 * (nbytes - 1)] = rt_remd_snf(tmp, 2.0);
      tmp /= 2.0;
      tmp = std::floor(tmp);
      nbytes++;
    }
  }
  for (count = 0; count < 7; count++) {
    for (msgCnt = 0; msgCnt < 1600; msgCnt++) {
      b_b[msgCnt + 1600 * count] =
          static_cast<signed char>(b[msgCnt + 1600 * (6 - count)]);
    }
  }
  for (count = 0; count < 7; count++) {
    for (msgCnt = 0; msgCnt < 1600; msgCnt++) {
      nbytes = msgCnt + 1600 * count;
      b[nbytes] = b_b[nbytes];
    }
  }
  // SimParams.MessageBits = messageBits;
  //  For BER calculation masks
  for (msgCnt = 0; msgCnt < 20; msgCnt++) {
    short i;
    i = static_cast<short>((msgCnt << 4) * 7 + 1);
    nbytes = msgCnt * 11 * 7;
    for (count = 0; count < 77; count++) {
      berMask[count + nbytes] = static_cast<short>(count + i);
    }
  }
  //  Copyright 2012-2017 The MathWorks, Inc.
  // qpskChan
  if (!qpskTx_not_empty) {
    //  Initialize the components
    //  Create and configure the transmitter System object
    qpskTx.isInitialized = 0;
    for (count = 0; count < 1600; count++) {
      for (msgCnt = 0; msgCnt < 7; msgCnt++) {
        b_b[msgCnt + 7 * count] =
            static_cast<signed char>(b[count + 1600 * msgCnt]);
      }
    }
    for (count = 0; count < 11200; count++) {
      qpskTx.MessageBits[count] = b_b[count];
    }
    qpskTx.matlabCodegenIsDeleted = false;
    qpskTx_not_empty = true;
    //      % Create and configure the AWGN channel System object
    //      qpskChan = QPSKChannel(...
    //          'DelayType',                            myStruct.DelayType, ...
    //          'DelayStepSize', 0.0125*myStruct.Interpolation, ...
    //          'DelayMaximum', 2*myStruct.Interpolation, ... 'DelayMinimum',
    //          0.1, ... 'RaisedCosineFilterSpan',
    //          myStruct.RaisedCosineFilterSpan, ... 'PhaseOffset',
    //          myStruct.PhaseOffset, ... 'SignalPower',
    //          1/myStruct.Interpolation, ... 'InterpolationFactor',
    //          myStruct.Interpolation, ... 'EbNo', myStruct.EbNo, ...
    //          'BitsPerSymbol', log2(myStruct.ModulationOrder), ...
    //          'FrequencyOffset', myStruct.FrequencyOffset, ... 'SampleRate',
    //          myStruct.Fs);
    //  Create and configure the receiver System object
    qpskRx.isInitialized = 0;
    for (msgCnt = 0; msgCnt < 1540; msgCnt++) {
      qpskRx.BerMask[msgCnt] = berMask[msgCnt];
    }
    for (count = 0; count < 11; count++) {
      qpskRx.pMessage[count] = varargin_52[count];
    }
    qpskRx.pMessageLength = 16.0;
    qpskRx.matlabCodegenIsDeleted = false;
  }
  BER = 3.1415926535897931;
  for (count = 0; count < 1000; count++) {
    if (qpskTx.isInitialized != 1) {
      qpskTx.isSetupComplete = false;
      qpskTx.isInitialized = 1;
      std::copy(&qpskTx.MessageBits[0], &qpskTx.MessageBits[11200], &b[0]);
      qpskTx.pBitGenerator.isInitialized = 0;
      std::copy(&b[0], &b[11200], &qpskTx.pBitGenerator.MessageBits[0]);
      qpskTx.pBitGenerator.matlabCodegenIsDeleted = false;
      obj = &qpskTx.pQPSKModulator;
      qpskTx.pQPSKModulator.isInitialized = 0;
      // System object Constructor function: comm.QPSKModulator
      for (msgCnt = 0; msgCnt < 8; msgCnt++) {
        obj->cSFunObject.P0_modmap[msgCnt] = dv[msgCnt];
      }
      qpskTx.pQPSKModulator.matlabCodegenIsDeleted = false;
      qpskTx.pTransmitterFilter.isInitialized = 0;
      qpskTx.pTransmitterFilter.matlabCodegenIsDeleted = false;
      qpskTx.isSetupComplete = true;
      if (qpskTx.pBitGenerator.isInitialized == 1) {
        qpskTx.pBitGenerator.resetImpl();
      }
      if (qpskTx.pTransmitterFilter.isInitialized == 1) {
        b_obj = qpskTx.pTransmitterFilter.pFilter;
        if (b_obj->isInitialized == 1) {
          // System object Initialization function: dsp.FIRInterpolator
          for (msgCnt = 0; msgCnt < 10; msgCnt++) {
            b_obj->cSFunObject.W0_TapDelayBuff[msgCnt].re = 0.0;
            b_obj->cSFunObject.W0_TapDelayBuff[msgCnt].im = 0.0;
          }
          b_obj->cSFunObject.W1_PrevNumChan = -1;
        }
      }
    }
    qpskTx.stepImpl(transmittedSignal_data, transmittedSignal_size);
    //  Transmitter
    //     rcvdSignal = qpskChan(transmittedSignal, count); % AWGN Channel
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
      c_obj = &qpskRx.pCoarseFreqCompensator;
      qpskRx.pCoarseFreqCompensator.isInitialized = 0;
      // System object Constructor function: comm.PhaseFrequencyOffset
      c_obj->cSFunObject.P0_Phase = 0.0;
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
      qpskRx.pTimingRec.DetectorGain = 5.3999999999999995;
      qpskRx.pTimingRec.matlabCodegenIsDeleted = false;
      qpskRx.pPrbDet.isInitialized = 0;
      flag = (qpskRx.pPrbDet.isInitialized == 1);
      if (flag) {
        qpskRx.pPrbDet.TunablePropsChanged = true;
      }
      qpskRx.pPrbDet.Threshold = 20.0;
      qpskRx.pFrameSync.isInitialized = 0;
      qpskRx.pFrameSync.matlabCodegenIsDeleted = false;
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
        d_obj = qpskRx.pRxFilter.pFilter;
        if (d_obj->isInitialized == 1) {
          // System object Initialization function: dsp.FIRDecimator
          d_obj->cSFunObject.W2_CoeffIdx = 0;
          d_obj->cSFunObject.W0_PhaseIdx = 0;
          d_obj->cSFunObject.W4_TapDelayIndex = 0;
          d_obj->cSFunObject.W1_Sums.re = 0.0;
          d_obj->cSFunObject.W1_Sums.im = 0.0;
          for (msgCnt = 0; msgCnt < 20; msgCnt++) {
            d_obj->cSFunObject.W3_StatesBuff[msgCnt].re = 0.0;
            d_obj->cSFunObject.W3_StatesBuff[msgCnt].im = 0.0;
          }
        }
      }
      if (qpskRx.pCoarseFreqEstimator.isInitialized == 1) {
        qpskRx.pCoarseFreqEstimator.pRaisedSignalBuffer[0].re = 0.0;
        qpskRx.pCoarseFreqEstimator.pRaisedSignalBuffer[0].im = 0.0;
        qpskRx.pCoarseFreqEstimator.pRaisedSignalBuffer[1].re = 0.0;
        qpskRx.pCoarseFreqEstimator.pRaisedSignalBuffer[1].im = 0.0;
        qpskRx.pCoarseFreqEstimator.pRaisedSignalBuffer[2].re = 0.0;
        qpskRx.pCoarseFreqEstimator.pRaisedSignalBuffer[2].im = 0.0;
        qpskRx.pCoarseFreqEstimator.pCumFreqOffset = 0.0;
        qpskRx.pCoarseFreqEstimator.pScratchVar.re = 0.0;
        qpskRx.pCoarseFreqEstimator.pScratchVar.im = 0.0;
      }
      if (qpskRx.pCoarseFreqCompensator.isInitialized == 1) {
        // System object Initialization function: comm.PhaseFrequencyOffset
        qpskRx.pCoarseFreqCompensator.cSFunObject.W0_freqTnow = 0.0;
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
        //  Initialize internal buffer and related properties
        qpskRx.pFrameSync.pNBuffer = 0.0;
        qpskRx.pFrameSync.pBufferStartIdx = 0.0;
        qpskRx.pFrameSync.pBufferEndIdx = 0.0;
        for (msgCnt = 0; msgCnt < 5; msgCnt++) {
          qpskRx.pFrameSync.pPrbIdxBuffer[msgCnt] = 0.0;
        }
        qpskRx.pFrameSync.pNPrbIdxBuffer = 0.0;
        qpskRx.pFrameSync.pPrbIdxBufferStartIdx = 1.0;
      }
      if (qpskRx.pDataDecod.isInitialized == 1) {
        if (qpskRx.pDataDecod.pDescrambler.isInitialized == 1) {
          e_obj = &qpskRx.pDataDecod.pDescrambler.cSFunObject;
          // System object Initialization function: comm.Descrambler
          e_obj->W0_shiftReg[0] = e_obj->P1_IniState[0];
          e_obj->W0_shiftReg[1] = e_obj->P1_IniState[1];
          e_obj->W0_shiftReg[2] = e_obj->P1_IniState[2];
          e_obj->W0_shiftReg[3] = e_obj->P1_IniState[3];
        }
        //             reset(obj.pErrorRateCalc);
      }
      qpskRx.pMeanFreqOff = 0.0;
      qpskRx.pCnt = 0.0;
    }
    qpskRx.stepImpl(transmittedSignal_data[0], &varargout_1,
                    (creal_T *)&varargout_2_data, &nbytes,
                    (creal_T *)&varargout_3_data, &msgCnt);
    //  Receiver
  }
  return BER;
}

void qpskApp_free()
{
  FrameSynchronizer *e_obj;
  QPSKBitsGenerator *m_obj;
  QPSKDataDecoder *obj;
  coder::comm::CoarseFrequencyCompensator *h_obj;
  coder::comm::RaisedCosineReceiveFilter *i_obj;
  coder::comm::RaisedCosineTransmitFilter *j_obj;
  coder::comm::SymbolSynchronizer *f_obj;
  coder::commcodegen::Descrambler *b_obj;
  coder::commcodegen::PhaseFrequencyOffset *g_obj;
  coder::commcodegen::QPSKDemodulator *c_obj;
  coder::commcodegen::QPSKModulator *l_obj;
  coder::commcodegen::Scrambler *p_obj;
  coder::dsp::AsyncBuffer *n_obj;
  coder::dsp::private_::AsyncBuffercgHelper *o_obj;
  coder::dspcodegen::FIRDecimator *d_obj;
  coder::dspcodegen::FIRInterpolator *k_obj;
  if (!qpskRx.matlabCodegenIsDeleted) {
    qpskRx.matlabCodegenIsDeleted = true;
    if (qpskRx.isInitialized == 1) {
      qpskRx.isInitialized = 2;
      if (qpskRx.isSetupComplete) {
        if (qpskRx.pAGC.isInitialized == 1) {
          qpskRx.pAGC.isInitialized = 2;
        }
        if (qpskRx.pRxFilter.isInitialized == 1) {
          qpskRx.pRxFilter.isInitialized = 2;
          if (qpskRx.pRxFilter.isSetupComplete) {
            d_obj = qpskRx.pRxFilter.pFilter;
            if (d_obj->isInitialized == 1) {
              d_obj->isInitialized = 2;
            }
          }
        }
        if (qpskRx.pCoarseFreqEstimator.isInitialized == 1) {
          qpskRx.pCoarseFreqEstimator.isInitialized = 2;
        }
        if (qpskRx.pCoarseFreqCompensator.isInitialized == 1) {
          qpskRx.pCoarseFreqCompensator.isInitialized = 2;
        }
        if (qpskRx.pFineFreqCompensator.isInitialized == 1) {
          qpskRx.pFineFreqCompensator.isInitialized = 2;
        }
        if (qpskRx.pTimingRec.isInitialized == 1) {
          qpskRx.pTimingRec.isInitialized = 2;
        }
        if (qpskRx.pPrbDet.isInitialized == 1) {
          qpskRx.pPrbDet.isInitialized = 2;
        }
        if (qpskRx.pFrameSync.isInitialized == 1) {
          qpskRx.pFrameSync.isInitialized = 2;
        }
        obj = &qpskRx.pDataDecod;
        if (qpskRx.pDataDecod.isInitialized == 1) {
          qpskRx.pDataDecod.isInitialized = 2;
          if (qpskRx.pDataDecod.isSetupComplete) {
            if (obj->pQPSKDemodulator.isInitialized == 1) {
              obj->pQPSKDemodulator.isInitialized = 2;
            }
            if (obj->pDescrambler.isInitialized == 1) {
              obj->pDescrambler.isInitialized = 2;
            }
            //             release(obj.pErrorRateCalc);
          }
        }
      }
    }
  }
  obj = &qpskRx.pDataDecod;
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
    if (obj->isInitialized == 1) {
      obj->isInitialized = 2;
      if (obj->isSetupComplete) {
        if (obj->pQPSKDemodulator.isInitialized == 1) {
          obj->pQPSKDemodulator.isInitialized = 2;
        }
        if (obj->pDescrambler.isInitialized == 1) {
          obj->pDescrambler.isInitialized = 2;
        }
        //             release(obj.pErrorRateCalc);
      }
    }
  }
  b_obj = &qpskRx.pDataDecod.pDescrambler;
  if (!b_obj->matlabCodegenIsDeleted) {
    b_obj->matlabCodegenIsDeleted = true;
    if (b_obj->isInitialized == 1) {
      b_obj->isInitialized = 2;
    }
  }
  c_obj = &qpskRx.pDataDecod.pQPSKDemodulator;
  if (!c_obj->matlabCodegenIsDeleted) {
    c_obj->matlabCodegenIsDeleted = true;
    if (c_obj->isInitialized == 1) {
      c_obj->isInitialized = 2;
    }
  }
  e_obj = &qpskRx.pFrameSync;
  if (!e_obj->matlabCodegenIsDeleted) {
    e_obj->matlabCodegenIsDeleted = true;
    if (e_obj->isInitialized == 1) {
      e_obj->isInitialized = 2;
    }
  }
  f_obj = &qpskRx.pTimingRec;
  if (!f_obj->matlabCodegenIsDeleted) {
    f_obj->matlabCodegenIsDeleted = true;
    if (f_obj->isInitialized == 1) {
      f_obj->isInitialized = 2;
    }
  }
  g_obj = &qpskRx.pCoarseFreqCompensator;
  if (!g_obj->matlabCodegenIsDeleted) {
    g_obj->matlabCodegenIsDeleted = true;
    if (g_obj->isInitialized == 1) {
      g_obj->isInitialized = 2;
    }
  }
  h_obj = &qpskRx.pCoarseFreqEstimator;
  if (!h_obj->matlabCodegenIsDeleted) {
    h_obj->matlabCodegenIsDeleted = true;
    if (h_obj->isInitialized == 1) {
      h_obj->isInitialized = 2;
    }
  }
  i_obj = &qpskRx.pRxFilter;
  if (!i_obj->matlabCodegenIsDeleted) {
    i_obj->matlabCodegenIsDeleted = true;
    if (i_obj->isInitialized == 1) {
      i_obj->isInitialized = 2;
      if (i_obj->isSetupComplete) {
        d_obj = i_obj->pFilter;
        if (d_obj->isInitialized == 1) {
          d_obj->isInitialized = 2;
        }
      }
    }
  }
  d_obj = &qpskRx.pRxFilter._pobj0;
  if (!d_obj->matlabCodegenIsDeleted) {
    d_obj->matlabCodegenIsDeleted = true;
    if (d_obj->isInitialized == 1) {
      d_obj->isInitialized = 2;
    }
  }
  if (!qpskTx.matlabCodegenIsDeleted) {
    qpskTx.matlabCodegenIsDeleted = true;
    if (qpskTx.isInitialized == 1) {
      qpskTx.isInitialized = 2;
      if (qpskTx.isSetupComplete) {
        if (qpskTx.pBitGenerator.isInitialized == 1) {
          qpskTx.pBitGenerator.isInitialized = 2;
          if (qpskTx.pBitGenerator.isSetupComplete) {
            qpskTx.pBitGenerator.releaseImpl();
          }
        }
        if (qpskTx.pQPSKModulator.isInitialized == 1) {
          qpskTx.pQPSKModulator.isInitialized = 2;
        }
        if (qpskTx.pTransmitterFilter.isInitialized == 1) {
          qpskTx.pTransmitterFilter.isInitialized = 2;
          if (qpskTx.pTransmitterFilter.isSetupComplete) {
            k_obj = qpskTx.pTransmitterFilter.pFilter;
            if (k_obj->isInitialized == 1) {
              k_obj->isInitialized = 2;
            }
          }
        }
      }
    }
  }
  j_obj = &qpskTx.pTransmitterFilter;
  if (!j_obj->matlabCodegenIsDeleted) {
    j_obj->matlabCodegenIsDeleted = true;
    if (j_obj->isInitialized == 1) {
      j_obj->isInitialized = 2;
      if (j_obj->isSetupComplete) {
        k_obj = j_obj->pFilter;
        if (k_obj->isInitialized == 1) {
          k_obj->isInitialized = 2;
        }
      }
    }
  }
  k_obj = &qpskTx.pTransmitterFilter._pobj0;
  if (!k_obj->matlabCodegenIsDeleted) {
    k_obj->matlabCodegenIsDeleted = true;
    if (k_obj->isInitialized == 1) {
      k_obj->isInitialized = 2;
    }
  }
  l_obj = &qpskTx.pQPSKModulator;
  if (!l_obj->matlabCodegenIsDeleted) {
    l_obj->matlabCodegenIsDeleted = true;
    if (l_obj->isInitialized == 1) {
      l_obj->isInitialized = 2;
    }
  }
  m_obj = &qpskTx.pBitGenerator;
  if (!m_obj->matlabCodegenIsDeleted) {
    m_obj->matlabCodegenIsDeleted = true;
    if (m_obj->isInitialized == 1) {
      m_obj->isInitialized = 2;
      if (m_obj->isSetupComplete) {
        m_obj->releaseImpl();
      }
    }
  }
  n_obj = &qpskTx.pBitGenerator.pSigSrc;
  if (!n_obj->matlabCodegenIsDeleted) {
    n_obj->matlabCodegenIsDeleted = true;
  }
  o_obj = &qpskTx.pBitGenerator.pSigSrc.pBuffer;
  if (!o_obj->matlabCodegenIsDeleted) {
    o_obj->matlabCodegenIsDeleted = true;
    if (o_obj->isInitialized == 1) {
      o_obj->isInitialized = 2;
      if (o_obj->isSetupComplete) {
        o_obj->ReadPointer = 1;
        o_obj->WritePointer = 2;
        o_obj->CumulativeOverrun = 0;
        o_obj->CumulativeUnderrun = 0;
        o_obj->AsyncBuffercgHelper_isInitialized = false;
        o_obj->NumChannels = -1;
      }
    }
  }
  p_obj = &qpskTx.pBitGenerator.pScrambler;
  if (!p_obj->matlabCodegenIsDeleted) {
    p_obj->matlabCodegenIsDeleted = true;
    if (p_obj->isInitialized == 1) {
      p_obj->isInitialized = 2;
    }
  }
}

void qpskApp_init()
{
  qpskTx_not_empty = false;
  qpskTx.pBitGenerator.pScrambler.matlabCodegenIsDeleted = true;
  qpskTx.pBitGenerator.pSigSrc.pBuffer.matlabCodegenIsDeleted = true;
  qpskTx.pBitGenerator.pSigSrc.matlabCodegenIsDeleted = true;
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
  qpskRx.pDataDecod.matlabCodegenIsDeleted = true;
  qpskRx.matlabCodegenIsDeleted = true;
}

// End of code generation (qpskApp.cpp)
