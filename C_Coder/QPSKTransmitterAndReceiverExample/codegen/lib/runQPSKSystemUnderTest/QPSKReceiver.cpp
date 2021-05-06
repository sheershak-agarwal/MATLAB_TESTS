//
// QPSKReceiver.cpp
//
// Code generation for function 'QPSKReceiver'
//

// Include files
#include "QPSKReceiver.h"
#include "AGC.h"
#include "CarrierSynchronizer.h"
#include "CoarseFrequencyCompensator.h"
#include "Descrambler.h"
#include "ErrorRate.h"
#include "FIRDecimator.h"
#include "FrameSynchronizer.h"
#include "PhaseFrequencyOffset.h"
#include "PreambleDetector.h"
#include "QPSKDataDecoder.h"
#include "QPSKDemodulator.h"
#include "RaisedCosineReceiveFilter.h"
#include "SymbolSynchronizer.h"
#include "rt_nonfinite.h"
#include "runQPSKSystemUnderTest_data.h"
#include "runQPSKSystemUnderTest_rtwutil.h"
#include <algorithm>
#include <cmath>
#include <string.h>

// Function Declarations
static double rt_powd_snf(double u0, double u1);

// Function Definitions
static double rt_powd_snf(double u0, double u1)
{
  double y;
  if (std::isnan(u0) || std::isnan(u1)) {
    y = rtNaN;
  } else {
    double d;
    double d1;
    d = std::abs(u0);
    d1 = std::abs(u1);
    if (std::isinf(u1)) {
      if (d == 1.0) {
        y = 1.0;
      } else if (d > 1.0) {
        if (u1 > 0.0) {
          y = rtInf;
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = rtInf;
      }
    } else if (d1 == 0.0) {
      y = 1.0;
    } else if (d1 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = std::sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > std::floor(u1))) {
      y = rtNaN;
    } else {
      y = std::pow(u0, u1);
    }
  }
  return y;
}

QPSKReceiver::QPSKReceiver()
{
  this->matlabCodegenIsDeleted = true;
}

QPSKReceiver::~QPSKReceiver()
{
  this->matlabCodegenDestructor();
}

void QPSKReceiver::matlabCodegenDestructor()
{
  QPSKDataDecoder *b_obj;
  coder::dspcodegen::FIRDecimator *obj;
  if (!this->matlabCodegenIsDeleted) {
    this->matlabCodegenIsDeleted = true;
    if (this->isInitialized == 1) {
      this->isInitialized = 2;
      if (this->isSetupComplete) {
        if (this->pAGC.isInitialized == 1) {
          this->pAGC.isInitialized = 2;
        }
        if (this->pRxFilter.isInitialized == 1) {
          this->pRxFilter.isInitialized = 2;
          if (this->pRxFilter.isSetupComplete) {
            obj = this->pRxFilter.pFilter;
            if (obj->isInitialized == 1) {
              obj->isInitialized = 2;
            }
          }
        }
        if (this->pCoarseFreqEstimator.isInitialized == 1) {
          this->pCoarseFreqEstimator.isInitialized = 2;
        }
        if (this->pCoarseFreqCompensator.isInitialized == 1) {
          this->pCoarseFreqCompensator.isInitialized = 2;
        }
        if (this->pFineFreqCompensator.isInitialized == 1) {
          this->pFineFreqCompensator.isInitialized = 2;
        }
        if (this->pTimingRec.isInitialized == 1) {
          this->pTimingRec.isInitialized = 2;
        }
        if (this->pPrbDet.isInitialized == 1) {
          this->pPrbDet.isInitialized = 2;
        }
        if (this->pFrameSync.isInitialized == 1) {
          this->pFrameSync.isInitialized = 2;
        }
        b_obj = &this->pDataDecod;
        if (this->pDataDecod.isInitialized == 1) {
          this->pDataDecod.isInitialized = 2;
          if (this->pDataDecod.isSetupComplete) {
            if (b_obj->pQPSKDemodulator.isInitialized == 1) {
              b_obj->pQPSKDemodulator.isInitialized = 2;
            }
            if (b_obj->pDescrambler.isInitialized == 1) {
              b_obj->pDescrambler.isInitialized = 2;
            }
            if (b_obj->pErrorRateCalc.isInitialized == 1) {
              b_obj->pErrorRateCalc.isInitialized = 2;
            }
            this->pDataDecod.pBER[0] = 0.0;
            this->pDataDecod.pBER[1] = 0.0;
            this->pDataDecod.pBER[2] = 0.0;
          }
        }
      }
    }
  }
}

void QPSKReceiver::stepImpl(const creal_T bufferSignal[2266],
                            creal_T RCRxSignal[2266],
                            creal_T timingRecSignal_data[],
                            int *timingRecSignal_size,
                            creal_T fineCompSignal_data[],
                            int *fineCompSignal_size, double BER[3])
{
  static creal_T raisedSignalBuffer_data[2297];
  static creal_T AGCSignal[2266];
  static const double dv[12]{0.0, -0.5, 0.5,  0.0, 1.5,  -0.5,
                             1.0, -0.5, -0.5, 0.0, -0.5, 0.5};
  coder::comm::CoarseFrequencyCompensator *obj;
  coder::comm::SymbolSynchronizer *d_obj;
  coder::commcodegen::PhaseFrequencyOffset *b_obj;
  comm_PhaseFrequencyOffset_3 *c_obj;
  creal_T a[2266];
  creal_T conjRaisedSignal[2266];
  creal_T varargout_1[1133];
  creal_T raisedSignalBuffer[32];
  creal_T dcv[12];
  creal_T b_y[3];
  creal_T x[3];
  double varargout_1_data[1247];
  double varargout_2_data[1247];
  double filterState[49];
  double K;
  double autoCorrSum_im;
  double autoCorrSum_re;
  double d;
  double d1;
  double d2;
  double filterSum;
  double g;
  double intOut_im;
  double intOut_re;
  int i;
  int p;
  unsigned int stateIdx;
  boolean_T exitg1;
  boolean_T y;
  if (this->pAGC.isInitialized != 1) {
    this->pAGC.isSetupComplete = false;
    this->pAGC.isInitialized = 1;
    this->pAGC.Gain = 0.0;
    this->pAGC.pCastedStepSize = this->pAGC.AdaptationStepSize;
    for (i = 0; i < 49; i++) {
      this->pAGC.pFilterState[i] = 0.0;
    }
    this->pAGC.pFilterSum = 0.0;
    this->pAGC.pFilterStateIdx = 1U;
    this->pAGC.isSetupComplete = true;
    this->pAGC.TunablePropsChanged = false;
    this->pAGC.Gain = 0.0;
    for (i = 0; i < 49; i++) {
      this->pAGC.pFilterState[i] = 0.0;
    }
    this->pAGC.pFilterSum = 0.0;
    this->pAGC.pFilterStateIdx = 1U;
  }
  if (this->pAGC.TunablePropsChanged) {
    this->pAGC.TunablePropsChanged = false;
    this->pAGC.pCastedStepSize = this->pAGC.AdaptationStepSize;
  }
  g = this->pAGC.Gain;
  K = this->pAGC.pCastedStepSize;
  for (i = 0; i < 49; i++) {
    filterState[i] = this->pAGC.pFilterState[i];
  }
  filterSum = this->pAGC.pFilterSum;
  stateIdx = this->pAGC.pFilterStateIdx;
  for (p = 0; p < 2266; p++) {
    d = bufferSignal[p].re;
    d1 = bufferSignal[p].im;
    intOut_im = d * d + d1 * d1;
    filterSum += intOut_im;
    d2 = filterSum * 0.02;
    filterSum -= filterState[static_cast<int>(stateIdx) - 1];
    if (filterSum < 0.0) {
      filterSum = 0.0;
    }
    filterState[static_cast<int>(stateIdx) - 1] = intOut_im;
    i = static_cast<int>(stateIdx + 1U);
    if (static_cast<int>(stateIdx + 1U) > 49) {
      i = 1;
    }
    stateIdx = static_cast<unsigned int>(i);
    intOut_re = std::exp(g);
    AGCSignal[p].re = intOut_re * d;
    AGCSignal[p].im = intOut_re * d1;
    g = std::fmin(g + K * (0.69314718055994529 - (std::log(d2) + 2.0 * g)),
                  2.3025850929940459);
  }
  for (i = 0; i < 49; i++) {
    this->pAGC.pFilterState[i] = filterState[i];
  }
  this->pAGC.pFilterSum = filterSum;
  this->pAGC.pFilterStateIdx = stateIdx;
  this->pAGC.Gain = g;
  //  AGC control
  this->pRxFilter.step(AGCSignal, RCRxSignal);
  //  Pass the signal through
  //  Square-Root Raised Cosine Received Filter
  obj = &this->pCoarseFreqEstimator;
  if (this->pCoarseFreqEstimator.isInitialized != 1) {
    this->pCoarseFreqEstimator.isSetupComplete = false;
    this->pCoarseFreqEstimator.isInitialized = 1;
    this->pCoarseFreqEstimator.isSetupComplete = true;
    for (i = 0; i < 32; i++) {
      this->pCoarseFreqEstimator.pRaisedSignalBuffer[i].re = 0.0;
      this->pCoarseFreqEstimator.pRaisedSignalBuffer[i].im = 0.0;
    }
    this->pCoarseFreqEstimator.pCumFreqOffset = 0.0;
    for (p = 0; p < 2266; p++) {
      this->pCoarseFreqEstimator.pScratchVar[p].re = 0.0;
      this->pCoarseFreqEstimator.pScratchVar[p].im = 0.0;
    }
  }
  filterSum = this->pCoarseFreqEstimator.pCumFreqOffset;
  for (p = 0; p < 2266; p++) {
    d = RCRxSignal[p].re;
    d1 = RCRxSignal[p].im;
    if ((d1 == 0.0) && (d >= 0.0)) {
      AGCSignal[p].re = rt_powd_snf(d, 4.0);
      AGCSignal[p].im = 0.0;
    } else if (d == 0.0) {
      AGCSignal[p].re = rt_powd_snf(d1, 4.0);
      AGCSignal[p].im = 0.0;
    } else {
      if (d1 == 0.0) {
        if (d < 0.0) {
          autoCorrSum_re = std::log(std::abs(d));
          autoCorrSum_im = 3.1415926535897931;
        } else {
          autoCorrSum_re = std::log(d);
          autoCorrSum_im = 0.0;
        }
      } else if ((std::abs(d) > 8.9884656743115785E+307) ||
                 (std::abs(d1) > 8.9884656743115785E+307)) {
        autoCorrSum_re =
            std::log(rt_hypotd_snf(d / 2.0, d1 / 2.0)) + 0.69314718055994529;
        autoCorrSum_im = rt_atan2d_snf(d1, d);
      } else {
        autoCorrSum_re = std::log(rt_hypotd_snf(d, d1));
        autoCorrSum_im = rt_atan2d_snf(d1, d);
      }
      autoCorrSum_re *= 4.0;
      autoCorrSum_im *= 4.0;
      if (autoCorrSum_im == 0.0) {
        AGCSignal[p].re = std::exp(autoCorrSum_re);
        AGCSignal[p].im = 0.0;
      } else if (std::isinf(autoCorrSum_im) && std::isinf(autoCorrSum_re) &&
                 (autoCorrSum_re < 0.0)) {
        AGCSignal[p].re = 0.0;
        AGCSignal[p].im = 0.0;
      } else {
        K = std::exp(autoCorrSum_re / 2.0);
        AGCSignal[p].re = K * (K * std::cos(autoCorrSum_im));
        AGCSignal[p].im = K * (K * std::sin(autoCorrSum_im));
      }
    }
  }
  for (i = 0; i < 32; i++) {
    raisedSignalBuffer[i] = this->pCoarseFreqEstimator.pRaisedSignalBuffer[i];
  }
  for (i = 0; i < 2266; i++) {
    conjRaisedSignal[i].re = AGCSignal[i].re;
    conjRaisedSignal[i].im = -AGCSignal[i].im;
  }
  autoCorrSum_re = 0.0;
  autoCorrSum_im = 0.0;
  for (int idx{0}; idx < 32; idx++) {
    i = 2264 - idx;
    p = idx - 31;
    if (0 <= p + 31) {
      std::copy(&raisedSignalBuffer[31 - idx],
                &raisedSignalBuffer[(31 - idx) + (p + 32)],
                &raisedSignalBuffer_data[0]);
    }
    if (0 <= i) {
      std::copy(&conjRaisedSignal[0], &conjRaisedSignal[i + 1],
                &raisedSignalBuffer_data[idx + 1]);
    }
    for (p = 0; p < 2266; p++) {
      obj->pScratchVar[p] = raisedSignalBuffer_data[p];
    }
    for (p = 0; p < 2266; p++) {
      a[p] = obj->pScratchVar[p];
    }
    g = 0.0;
    K = 0.0;
    for (p = 0; p < 2266; p++) {
      d = a[p].re;
      d1 = a[p].im;
      d2 = AGCSignal[p].re;
      intOut_re = AGCSignal[p].im;
      g += d * d2 - d1 * intOut_re;
      K += d * intOut_re + d1 * d2;
    }
    autoCorrSum_re += g;
    autoCorrSum_im += K;
  }
  K = 1929.150825356307 * rt_atan2d_snf(autoCorrSum_im, autoCorrSum_re);
  for (i = 0; i < 32; i++) {
    this->pCoarseFreqEstimator.pRaisedSignalBuffer[i] =
        conjRaisedSignal[i + 2234];
  }
  this->pCoarseFreqEstimator.pCumFreqOffset = filterSum - K * 2266.0 * 1.25E-6;
  //  Coarse frequency offset estimation
  //  average coarse frequency offset estimate, so that carrier
  //  sync is able to lock/converge
  filterSum = (K + this->pCnt * this->pMeanFreqOff) / (this->pCnt + 1.0);
  this->pCnt++;
  //  update state
  this->pMeanFreqOff = filterSum;
  b_obj = &this->pCoarseFreqCompensator;
  if (this->pCoarseFreqCompensator.isInitialized != 1) {
    this->pCoarseFreqCompensator.isSetupComplete = false;
    this->pCoarseFreqCompensator.isInitialized = 1;
    this->pCoarseFreqCompensator.isSetupComplete = true;
    // System object Initialization function: comm.PhaseFrequencyOffset
    b_obj->cSFunObject.W0_freqTnow = 0.0;
  }
  c_obj = &this->pCoarseFreqCompensator.cSFunObject;
  // System object Outputs function: comm.PhaseFrequencyOffset
  for (i = 0; i < 2266; i++) {
    if ((c_obj->W0_freqTnow >= 1.0) || (c_obj->W0_freqTnow <= -1.0)) {
      (&c_obj->W0_freqTnow)[0U] = std::fmod(c_obj->W0_freqTnow, 1.0);
    }
    // Compute (w*t + phi) argument for calls to cos and sin below
    K = 6.2831853071795862 * c_obj->W0_freqTnow + c_obj->P0_Phase;
    d = std::sin(K);
    d1 = std::cos(K);
    d2 = RCRxSignal[i].re;
    intOut_re = RCRxSignal[i].im;
    AGCSignal[i].re = d2 * d1 - intOut_re * d;
    AGCSignal[i].im = d2 * d + intOut_re * d1;
    (&c_obj->W0_freqTnow)[0U] =
        c_obj->W0_freqTnow + -filterSum * 1.2499999999999999E-6;
  }
  //  Coarse frequency compensation
  d_obj = &this->pTimingRec;
  if (this->pTimingRec.isInitialized != 1) {
    this->pTimingRec.isSetupComplete = false;
    this->pTimingRec.isInitialized = 1;
    K = this->pTimingRec.DampingFactor;
    filterSum = this->pTimingRec.NormalizedLoopBandwidth / 2.0 / (K + 0.25 / K);
    g = -((2.0 * K * filterSum + 1.0) + filterSum * filterSum) *
        this->pTimingRec.DetectorGain;
    this->pTimingRec.pProportionalGain = 4.0 * K * filterSum / g;
    this->pTimingRec.pIntegratorGain = 4.0 * filterSum * filterSum / g;
    this->pTimingRec.isSetupComplete = true;
    this->pTimingRec.TunablePropsChanged = false;
    this->pTimingRec.resetImpl();
  }
  if (this->pTimingRec.TunablePropsChanged) {
    this->pTimingRec.TunablePropsChanged = false;
    K = this->pTimingRec.DampingFactor;
    filterSum = this->pTimingRec.NormalizedLoopBandwidth / 2.0 / (K + 0.25 / K);
    g = -((2.0 * K * filterSum + 1.0) + filterSum * filterSum) *
        this->pTimingRec.DetectorGain;
    this->pTimingRec.pProportionalGain = 4.0 * K * filterSum / g;
    this->pTimingRec.pIntegratorGain = 4.0 * filterSum * filterSum / g;
  }
  this->pTimingRec.pNumStrobe = 0.0;
  i = 0;
  exitg1 = false;
  while ((!exitg1) && ((i < 2266) && ((!(d_obj->pNumStrobe == 1247.0)) ||
                                      (!d_obj->pStrobe)))) {
    creal_T xSeq_idx_0;
    creal_T xSeq_idx_1;
    creal_T xSeq_idx_2;
    creal_T xSeq_idx_3;
    d_obj->pNumStrobe += static_cast<double>(d_obj->pStrobe);
    d_obj->pTimingError[i] = d_obj->pMu;
    xSeq_idx_0 = AGCSignal[i];
    xSeq_idx_1 = d_obj->pInterpFilterState[0];
    xSeq_idx_2 = d_obj->pInterpFilterState[1];
    xSeq_idx_3 = d_obj->pInterpFilterState[2];
    for (p = 0; p < 12; p++) {
      dcv[p].re = dv[p];
      dcv[p].im = 0.0;
    }
    for (p = 0; p < 3; p++) {
      d = dcv[p].re;
      d1 = dcv[p].im;
      d2 = dcv[p + 3].re;
      intOut_re = dcv[p + 3].im;
      g = dcv[p + 6].re;
      K = dcv[p + 6].im;
      filterSum = dcv[p + 9].re;
      intOut_im = dcv[p + 9].im;
      b_y[p].re = (((d * xSeq_idx_0.re - d1 * xSeq_idx_0.im) +
                    (d2 * xSeq_idx_1.re - intOut_re * xSeq_idx_1.im)) +
                   (g * xSeq_idx_2.re - K * xSeq_idx_2.im)) +
                  (filterSum * xSeq_idx_3.re - intOut_im * xSeq_idx_3.im);
      b_y[p].im = (((d * xSeq_idx_0.im + d1 * xSeq_idx_0.re) +
                    (d2 * xSeq_idx_1.im + intOut_re * xSeq_idx_1.re)) +
                   (g * xSeq_idx_2.im + K * xSeq_idx_2.re)) +
                  (filterSum * xSeq_idx_3.im + intOut_im * xSeq_idx_3.re);
    }
    K = d_obj->pMu;
    x[1].re = d_obj->pMu * b_y[1].re;
    x[1].im = d_obj->pMu * b_y[1].im;
    d = K * K;
    intOut_re = (b_y[0].re + x[1].re) + d * b_y[2].re;
    intOut_im = (b_y[0].im + x[1].im) + d * b_y[2].im;
    d_obj->pInterpFilterState[0] = xSeq_idx_0;
    d_obj->pInterpFilterState[1] = xSeq_idx_1;
    d_obj->pInterpFilterState[2] = xSeq_idx_2;
    if (d_obj->pStrobe) {
      d_obj->pSymbolHolder[static_cast<int>(d_obj->pNumStrobe) - 1].re =
          intOut_re;
      d_obj->pSymbolHolder[static_cast<int>(d_obj->pNumStrobe) - 1].im =
          intOut_im;
    }
    if (d_obj->pNumStrobe > 1247.0) {
      exitg1 = true;
    } else {
      boolean_T x_idx_1;
      if (d_obj->pStrobe) {
        y = !d_obj->pStrobeHistory[1];
        if (y) {
          autoCorrSum_re = d_obj->pTEDBuffer[1].re;
          autoCorrSum_im = d_obj->pTEDBuffer[1].im;
          K = d_obj->pTEDBuffer[1].re;
          filterSum = d_obj->pTEDBuffer[1].im;
          g = autoCorrSum_re + K;
          filterSum += autoCorrSum_im;
          if (filterSum == 0.0) {
            g /= 2.0;
            filterSum = 0.0;
          } else if (g == 0.0) {
            g = 0.0;
            filterSum /= 2.0;
          } else {
            g /= 2.0;
            filterSum /= 2.0;
          }
          g = g * (d_obj->pTEDBuffer[0].re - intOut_re) +
              filterSum * (d_obj->pTEDBuffer[0].im - intOut_im);
        } else {
          g = 0.0;
        }
      } else {
        g = 0.0;
      }
      y = d_obj->pStrobeHistory[1];
      x_idx_1 = d_obj->pStrobe;
      switch (y + x_idx_1) {
      case 0:
        break;
      case 1:
        K = d_obj->pTEDBuffer[1].re;
        filterSum = d_obj->pTEDBuffer[1].im;
        d_obj->pTEDBuffer[0].re = K;
        d_obj->pTEDBuffer[0].im = filterSum;
        d_obj->pTEDBuffer[1].re = intOut_re;
        d_obj->pTEDBuffer[1].im = intOut_im;
        break;
      default:
        d_obj->pTEDBuffer[0].re = 0.0;
        d_obj->pTEDBuffer[0].im = 0.0;
        d_obj->pTEDBuffer[1].re = intOut_re;
        d_obj->pTEDBuffer[1].im = intOut_im;
        break;
      }
      K = d_obj->pLoopPreviousInput + d_obj->pLoopFilterState;
      filterSum = g * d_obj->pProportionalGain + K;
      d_obj->pLoopFilterState = K;
      d_obj->pLoopPreviousInput = g * d_obj->pIntegratorGain;
      y = d_obj->pStrobeHistory[1];
      d_obj->pStrobeHistory[0] = y;
      d_obj->pStrobeHistory[1] = d_obj->pStrobe;
      d_obj->pStrobe = (d_obj->pNCOCounter < filterSum + 0.5);
      if (d_obj->pStrobe) {
        d_obj->pMu = d_obj->pNCOCounter / (filterSum + 0.5);
      }
      intOut_im = d_obj->pNCOCounter - (filterSum + 0.5);
      if (std::isnan(intOut_im) || std::isinf(intOut_im)) {
        K = rtNaN;
      } else if (intOut_im == 0.0) {
        K = 0.0;
      } else {
        K = std::fmod(intOut_im, 1.0);
        if (K == 0.0) {
          K = 0.0;
        } else if (intOut_im < 0.0) {
          K++;
        }
      }
      d_obj->pNCOCounter = K;
      i++;
    }
  }
  d = this->pTimingRec.pNumStrobe;
  if (1.0 > d) {
    *timingRecSignal_size = 0;
  } else {
    *timingRecSignal_size = static_cast<int>(d);
  }
  for (p = 0; p < *timingRecSignal_size; p++) {
    timingRecSignal_data[p] = this->pTimingRec.pSymbolHolder[p];
  }
  //  Symbol timing recovery
  this->pFineFreqCompensator.step(timingRecSignal_data, *timingRecSignal_size,
                                  fineCompSignal_data, fineCompSignal_size);
  //  Fine frequency compensation
  this->pPrbDet.step(fineCompSignal_data, *fineCompSignal_size,
                     varargout_1_data, &i, varargout_2_data, &p);
  //  Detect frame header
  this->pFrameSync.step(fineCompSignal_data, *fineCompSignal_size,
                        varargout_1_data, i, varargout_2_data, p, varargout_1,
                        &y);
  //  Frame synchronization
  this->pDataDecod.step(varargout_1, y, BER);
}

// End of code generation (QPSKReceiver.cpp)
