//
// QPSKReceiver.cpp
//
// Code generation for function 'QPSKReceiver'
//

// Include files
#include "QPSKReceiver.h"
#include "AGC.h"
#include "AsyncBuffercgHelper.h"
#include "CarrierSynchronizer.h"
#include "CoarseFrequencyCompensator.h"
#include "FrameSynchronizer.h"
#include "PhaseFrequencyOffset.h"
#include "PreambleDetector.h"
#include "QPSKDataDecoder.h"
#include "RaisedCosineReceiveFilter.h"
#include "SymbolSynchronizer.h"
#include "qpskApp_rtwutil.h"
#include "rt_nonfinite.h"
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string.h>

// Function Declarations
static double rt_hypotd_snf(double u0, double u1);

static double rt_powd_snf(double u0, double u1);

// Function Definitions
static double rt_hypotd_snf(double u0, double u1)
{
  double a;
  double y;
  a = std::abs(u0);
  y = std::abs(u1);
  if (a < y) {
    a /= y;
    y *= std::sqrt(a * a + 1.0);
  } else if (a > y) {
    y /= a;
    y = a * std::sqrt(y * y + 1.0);
  } else if (!std::isnan(y)) {
    y = a * 1.4142135623730951;
  }
  return y;
}

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

void QPSKReceiver::stepImpl(const creal_T bufferSignal, creal_T *RCRxSignal,
                            creal_T timingRecSignal_data[],
                            int *timingRecSignal_size,
                            creal_T fineCompSignal_data[],
                            int *fineCompSignal_size)
{
  static const creal_T b[13]{{
                                 -0.70710678118654757, // re
                                 0.70710678118654757   // im
                             },
                             {
                                 0.70710678118654757, // re
                                 -0.70710678118654757 // im
                             },
                             {
                                 -0.70710678118654757, // re
                                 0.70710678118654757   // im
                             },
                             {
                                 0.70710678118654757, // re
                                 -0.70710678118654757 // im
                             },
                             {
                                 -0.70710678118654757, // re
                                 0.70710678118654757   // im
                             },
                             {
                                 -0.70710678118654757, // re
                                 0.70710678118654757   // im
                             },
                             {
                                 0.70710678118654757, // re
                                 -0.70710678118654757 // im
                             },
                             {
                                 0.70710678118654757, // re
                                 -0.70710678118654757 // im
                             },
                             {
                                 -0.70710678118654757, // re
                                 0.70710678118654757   // im
                             },
                             {
                                 -0.70710678118654757, // re
                                 0.70710678118654757   // im
                             },
                             {
                                 -0.70710678118654757, // re
                                 0.70710678118654757   // im
                             },
                             {
                                 -0.70710678118654757, // re
                                 0.70710678118654757   // im
                             },
                             {
                                 -0.70710678118654757, // re
                                 0.70710678118654757   // im
                             }};
  coder::comm::CoarseFrequencyCompensator *obj;
  coder::comm::PreambleDetector *c_obj;
  coder::commcodegen::PhaseFrequencyOffset *b_obj;
  cell_wrap_3 varSizes;
  creal_T varargout_1[1133];
  creal_T currFilterStates[12];
  creal_T newFilterStates[12];
  creal_T raisedSignalBuffer_idx_0;
  creal_T raisedSignalBuffer_idx_1;
  creal_T raisedSignalBuffer_idx_2;
  double filterState[49];
  double K;
  double cumFreqOffset;
  double filterSum;
  double g;
  double raisedSignal_im;
  double raisedSignal_re;
  double x;
  int i;
  int k;
  unsigned int stateIdx;
  int varargout_2_size;
  signed char inSize[8];
  boolean_T exitg1;
  boolean_T varargin_2;
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
  x = bufferSignal.re * bufferSignal.re + bufferSignal.im * bufferSignal.im;
  filterSum += x;
  cumFreqOffset = filterSum * 0.02;
  filterSum -= filterState[static_cast<int>(stateIdx) - 1];
  if (filterSum < 0.0) {
    filterSum = 0.0;
  }
  filterState[static_cast<int>(stateIdx) - 1] = x;
  stateIdx++;
  if (static_cast<int>(stateIdx) > 49) {
    stateIdx = 1U;
  }
  cumFreqOffset = std::log(cumFreqOffset);
  for (i = 0; i < 49; i++) {
    this->pAGC.pFilterState[i] = filterState[i];
  }
  this->pAGC.pFilterSum = filterSum;
  this->pAGC.pFilterStateIdx = stateIdx;
  this->pAGC.Gain =
      std::fmin(g + K * (0.69314718055994529 - (cumFreqOffset + 2.0 * g)),
                2.3025850929940459);
  //  AGC control
  K = std::exp(g);
  raisedSignalBuffer_idx_0.re = K * bufferSignal.re;
  raisedSignalBuffer_idx_0.im = K * bufferSignal.im;
  *RCRxSignal = this->pRxFilter.step(raisedSignalBuffer_idx_0);
  //  Pass the signal through
  //  Square-Root Raised Cosine Received Filter
  obj = &this->pCoarseFreqEstimator;
  if (this->pCoarseFreqEstimator.isInitialized != 1) {
    this->pCoarseFreqEstimator.isSetupComplete = false;
    this->pCoarseFreqEstimator.isInitialized = 1;
    this->pCoarseFreqEstimator.isSetupComplete = true;
    this->pCoarseFreqEstimator.pRaisedSignalBuffer[0].re = 0.0;
    this->pCoarseFreqEstimator.pRaisedSignalBuffer[0].im = 0.0;
    this->pCoarseFreqEstimator.pRaisedSignalBuffer[1].re = 0.0;
    this->pCoarseFreqEstimator.pRaisedSignalBuffer[1].im = 0.0;
    this->pCoarseFreqEstimator.pRaisedSignalBuffer[2].re = 0.0;
    this->pCoarseFreqEstimator.pRaisedSignalBuffer[2].im = 0.0;
    this->pCoarseFreqEstimator.pCumFreqOffset = 0.0;
    this->pCoarseFreqEstimator.pScratchVar.re = 0.0;
    this->pCoarseFreqEstimator.pScratchVar.im = 0.0;
  }
  cumFreqOffset = this->pCoarseFreqEstimator.pCumFreqOffset;
  if ((RCRxSignal->im == 0.0) && (RCRxSignal->re >= 0.0)) {
    raisedSignal_re = rt_powd_snf(RCRxSignal->re, 4.0);
    raisedSignal_im = 0.0;
  } else if (RCRxSignal->re == 0.0) {
    raisedSignal_re = rt_powd_snf(RCRxSignal->im, 4.0);
    raisedSignal_im = 0.0;
  } else {
    if (RCRxSignal->im == 0.0) {
      if (RCRxSignal->re < 0.0) {
        raisedSignal_re = std::log(std::abs(RCRxSignal->re));
        raisedSignal_im = 3.1415926535897931;
      } else {
        raisedSignal_re = std::log(RCRxSignal->re);
        raisedSignal_im = 0.0;
      }
    } else if ((std::abs(RCRxSignal->re) > 8.9884656743115785E+307) ||
               (std::abs(RCRxSignal->im) > 8.9884656743115785E+307)) {
      raisedSignal_re =
          std::log(rt_hypotd_snf(RCRxSignal->re / 2.0, RCRxSignal->im / 2.0)) +
          0.69314718055994529;
      raisedSignal_im = rt_atan2d_snf(RCRxSignal->im, RCRxSignal->re);
    } else {
      raisedSignal_re = std::log(rt_hypotd_snf(RCRxSignal->re, RCRxSignal->im));
      raisedSignal_im = rt_atan2d_snf(RCRxSignal->im, RCRxSignal->re);
    }
    raisedSignal_re *= 4.0;
    raisedSignal_im *= 4.0;
    if (raisedSignal_im == 0.0) {
      raisedSignal_re = std::exp(raisedSignal_re);
      raisedSignal_im = 0.0;
    } else if (std::isinf(raisedSignal_im) && std::isinf(raisedSignal_re) &&
               (raisedSignal_re < 0.0)) {
      raisedSignal_re = 0.0;
      raisedSignal_im = 0.0;
    } else {
      K = std::exp(raisedSignal_re / 2.0);
      raisedSignal_re = K * (K * std::cos(raisedSignal_im));
      raisedSignal_im = K * (K * std::sin(raisedSignal_im));
    }
  }
  raisedSignalBuffer_idx_0 = this->pCoarseFreqEstimator.pRaisedSignalBuffer[0];
  raisedSignalBuffer_idx_1 = this->pCoarseFreqEstimator.pRaisedSignalBuffer[1];
  raisedSignalBuffer_idx_2 = this->pCoarseFreqEstimator.pRaisedSignalBuffer[2];
  this->pCoarseFreqEstimator.pScratchVar = raisedSignalBuffer_idx_2;
  g = this->pCoarseFreqEstimator.pScratchVar.re * raisedSignal_re -
      this->pCoarseFreqEstimator.pScratchVar.im * raisedSignal_im;
  K = this->pCoarseFreqEstimator.pScratchVar.re * raisedSignal_im +
      this->pCoarseFreqEstimator.pScratchVar.im * raisedSignal_re;
  obj->pScratchVar = raisedSignalBuffer_idx_1;
  filterSum = obj->pScratchVar.re * raisedSignal_re -
              obj->pScratchVar.im * raisedSignal_im;
  x = obj->pScratchVar.re * raisedSignal_im +
      obj->pScratchVar.im * raisedSignal_re;
  g += filterSum;
  K += x;
  obj->pScratchVar = raisedSignalBuffer_idx_0;
  filterSum = obj->pScratchVar.re * raisedSignal_re -
              obj->pScratchVar.im * raisedSignal_im;
  x = obj->pScratchVar.re * raisedSignal_im +
      obj->pScratchVar.im * raisedSignal_re;
  g += filterSum;
  K += x;
  filterSum = 1989.4367886486918 * rt_atan2d_snf(K, g);
  this->pCoarseFreqEstimator.pRaisedSignalBuffer[0] = raisedSignalBuffer_idx_1;
  this->pCoarseFreqEstimator.pRaisedSignalBuffer[1] = raisedSignalBuffer_idx_2;
  this->pCoarseFreqEstimator.pRaisedSignalBuffer[2].re = raisedSignal_re;
  this->pCoarseFreqEstimator.pRaisedSignalBuffer[2].im = -raisedSignal_im;
  this->pCoarseFreqEstimator.pCumFreqOffset =
      cumFreqOffset - filterSum * 1.0E-5;
  //  Coarse frequency offset estimation
  //  average coarse frequency offset estimate, so that carrier
  //  sync is able to lock/converge
  K = (filterSum + this->pCnt * this->pMeanFreqOff) / (this->pCnt + 1.0);
  this->pCnt++;
  //  update state
  this->pMeanFreqOff = K;
  b_obj = &this->pCoarseFreqCompensator;
  if (this->pCoarseFreqCompensator.isInitialized != 1) {
    this->pCoarseFreqCompensator.isSetupComplete = false;
    this->pCoarseFreqCompensator.isInitialized = 1;
    this->pCoarseFreqCompensator.isSetupComplete = true;
    // System object Initialization function: comm.PhaseFrequencyOffset
    b_obj->cSFunObject.W0_freqTnow = 0.0;
  }
  // System object Outputs function: comm.PhaseFrequencyOffset
  if ((b_obj->cSFunObject.W0_freqTnow >= 1.0) ||
      (b_obj->cSFunObject.W0_freqTnow <= -1.0)) {
    (&b_obj->cSFunObject.W0_freqTnow)[0U] =
        std::fmod(b_obj->cSFunObject.W0_freqTnow, 1.0);
  }
  // Compute (w*t + phi) argument for calls to cos and sin below
  filterSum = 6.2831853071795862 * b_obj->cSFunObject.W0_freqTnow +
              b_obj->cSFunObject.P0_Phase;
  (&b_obj->cSFunObject.W0_freqTnow)[0U] =
      b_obj->cSFunObject.W0_freqTnow + -K * 1.0E-5;
  //  Coarse frequency compensation
  g = std::sin(filterSum);
  K = std::cos(filterSum);
  raisedSignalBuffer_idx_0.re = RCRxSignal->re * K - RCRxSignal->im * g;
  raisedSignalBuffer_idx_0.im = RCRxSignal->re * g + RCRxSignal->im * K;
  this->pTimingRec.step(raisedSignalBuffer_idx_0, timingRecSignal_data,
                        timingRecSignal_size);
  //  Symbol timing recovery
  this->pFineFreqCompensator.step(timingRecSignal_data, *timingRecSignal_size,
                                  fineCompSignal_data, fineCompSignal_size);
  //  Fine frequency compensation
  c_obj = &this->pPrbDet;
  if (this->pPrbDet.isInitialized != 1) {
    this->pPrbDet.isSetupComplete = false;
    this->pPrbDet.isInitialized = 1;
    varSizes.f1[0] = static_cast<unsigned int>(*fineCompSignal_size);
    varSizes.f1[1] = 1U;
    for (k = 0; k < 6; k++) {
      varSizes.f1[k + 2] = 1U;
    }
    this->pPrbDet.inputVarSize[0] = varSizes;
    this->pPrbDet.pThreshold = this->pPrbDet.Threshold;
    for (i = 0; i < 12; i++) {
      this->pPrbDet.pFilterStates[i].re = 0.0;
      this->pPrbDet.pFilterStates[i].im = 0.0;
    }
    this->pPrbDet.isSetupComplete = true;
    this->pPrbDet.TunablePropsChanged = false;
    for (i = 0; i < 12; i++) {
      this->pPrbDet.pFilterStates[i].re = 0.0;
      this->pPrbDet.pFilterStates[i].im = 0.0;
    }
  }
  if (this->pPrbDet.TunablePropsChanged) {
    this->pPrbDet.TunablePropsChanged = false;
    this->pPrbDet.pThreshold = this->pPrbDet.Threshold;
  }
  inSize[0] = static_cast<signed char>(*fineCompSignal_size);
  inSize[1] = 1;
  for (k = 0; k < 6; k++) {
    inSize[k + 2] = 1;
  }
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 8)) {
    if (c_obj->inputVarSize[0].f1[k] != static_cast<unsigned int>(inSize[k])) {
      for (k = 0; k < 8; k++) {
        c_obj->inputVarSize[0].f1[k] = static_cast<unsigned int>(inSize[k]);
      }
      exitg1 = true;
    } else {
      k++;
    }
  }
  if (*fineCompSignal_size == 0) {
    k = 0;
    varargout_2_size = 0;
  } else {
    for (i = 0; i < 12; i++) {
      currFilterStates[i] = this->pPrbDet.pFilterStates[i];
    }
    g = this->pPrbDet.pThreshold;
    std::memset(&newFilterStates[0], 0, 12U * sizeof(creal_T));
    K = currFilterStates[0].re;
    filterSum = currFilterStates[0].im;
    x = fineCompSignal_data[0].re;
    cumFreqOffset = fineCompSignal_data[0].im;
    raisedSignal_re = b[0].re;
    raisedSignal_im = b[0].im;
    for (k = 0; k < 1; k++) {
      K += x * raisedSignal_re - cumFreqOffset * raisedSignal_im;
      filterSum += x * raisedSignal_im + cumFreqOffset * raisedSignal_re;
    }
    std::copy(&currFilterStates[1], &currFilterStates[12], &newFilterStates[0]);
    for (k = 0; k < 12; k++) {
      raisedSignal_re = b[k + 1].re;
      raisedSignal_im = b[k + 1].im;
      newFilterStates[k].re +=
          x * raisedSignal_re - cumFreqOffset * raisedSignal_im;
      newFilterStates[k].im +=
          x * raisedSignal_im + cumFreqOffset * raisedSignal_re;
    }
    k = 1;
    if (!(rt_hypotd_snf(K, filterSum) >= g)) {
      k = 0;
    }
    if (k == 0) {
      k = 0;
    }
    varargout_2_size = 1;
    for (i = 0; i < 12; i++) {
      this->pPrbDet.pFilterStates[i] = newFilterStates[i];
    }
  }
  //  Detect frame header
  this->pFrameSync.step(fineCompSignal_data, *fineCompSignal_size, k,
                        varargout_2_size, varargout_1, &varargin_2);
  //  Frame synchronization
  this->pDataDecod.step(varargout_1, varargin_2);
}

// End of code generation (QPSKReceiver.cpp)
