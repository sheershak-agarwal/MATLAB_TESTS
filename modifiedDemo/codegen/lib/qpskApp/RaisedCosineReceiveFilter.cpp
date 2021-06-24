//
// RaisedCosineReceiveFilter.cpp
//
// Code generation for function 'RaisedCosineReceiveFilter'
//

// Include files
#include "RaisedCosineReceiveFilter.h"
#include "FIRDecimator.h"
#include "rt_nonfinite.h"
#include <string.h>

// Function Definitions
namespace coder {
namespace comm {
creal_T RaisedCosineReceiveFilter::step(const creal_T varargin_1)
{
  static const double dv[21]{
      -0.00045472051487622253, 0.0035368955557498576, -0.0071456080909122616,
      0.0075790619051782785,   0.0021436824272736714, -0.010610686667249576,
      0.0300115539818315,      -0.053053433336247971, -0.075028884954578726,
      0.40916871463405252,     0.80373860039798006,   0.40916871463405252,
      -0.075028884954578726,   -0.053053433336247971, 0.0300115539818315,
      -0.010610686667249576,   0.0021436824272736714, 0.0075790619051782785,
      -0.0071456080909122616,  0.0035368955557498576, -0.00045472051487622253};
  dspcodegen::FIRDecimator *iobj_0_tmp_tmp;
  dsp_FIRDecimator_4 *obj;
  int cffIdx;
  int i;
  int jIdx;
  int maxWindow;
  int phaseIdx;
  if (this->isInitialized != 1) {
    this->isSetupComplete = false;
    this->isInitialized = 1;
    iobj_0_tmp_tmp = &this->_pobj0;
    this->_pobj0.isInitialized = 0;
    // System object Constructor function: dsp.FIRDecimator
    iobj_0_tmp_tmp->cSFunObject.P0_IC.re = 0.0;
    iobj_0_tmp_tmp->cSFunObject.P0_IC.im = 0.0;
    for (i = 0; i < 21; i++) {
      iobj_0_tmp_tmp->cSFunObject.P1_FILT[i] = dv[i];
    }
    this->_pobj0.matlabCodegenIsDeleted = false;
    this->pFilter = &this->_pobj0;
    this->isSetupComplete = true;
    iobj_0_tmp_tmp = this->pFilter;
    if (iobj_0_tmp_tmp->isInitialized == 1) {
      // System object Initialization function: dsp.FIRDecimator
      iobj_0_tmp_tmp->cSFunObject.W2_CoeffIdx = 0;
      iobj_0_tmp_tmp->cSFunObject.W0_PhaseIdx = 0;
      iobj_0_tmp_tmp->cSFunObject.W4_TapDelayIndex = 0;
      iobj_0_tmp_tmp->cSFunObject.W1_Sums.re = 0.0;
      iobj_0_tmp_tmp->cSFunObject.W1_Sums.im = 0.0;
      for (i = 0; i < 20; i++) {
        iobj_0_tmp_tmp->cSFunObject.W3_StatesBuff[i].re = 0.0;
        iobj_0_tmp_tmp->cSFunObject.W3_StatesBuff[i].im = 0.0;
      }
    }
  }
  iobj_0_tmp_tmp = this->pFilter;
  if (iobj_0_tmp_tmp->isInitialized != 1) {
    iobj_0_tmp_tmp->isSetupComplete = false;
    iobj_0_tmp_tmp->isInitialized = 1;
    iobj_0_tmp_tmp->isSetupComplete = true;
    // System object Initialization function: dsp.FIRDecimator
    iobj_0_tmp_tmp->cSFunObject.W2_CoeffIdx = 0;
    iobj_0_tmp_tmp->cSFunObject.W0_PhaseIdx = 0;
    iobj_0_tmp_tmp->cSFunObject.W4_TapDelayIndex = 0;
    iobj_0_tmp_tmp->cSFunObject.W1_Sums.re = 0.0;
    iobj_0_tmp_tmp->cSFunObject.W1_Sums.im = 0.0;
    for (i = 0; i < 20; i++) {
      iobj_0_tmp_tmp->cSFunObject.W3_StatesBuff[i].re = 0.0;
      iobj_0_tmp_tmp->cSFunObject.W3_StatesBuff[i].im = 0.0;
    }
  }
  obj = &iobj_0_tmp_tmp->cSFunObject;
  // System object Outputs function: dsp.FIRDecimator
  i = iobj_0_tmp_tmp->cSFunObject.W4_TapDelayIndex;
  phaseIdx = iobj_0_tmp_tmp->cSFunObject.W0_PhaseIdx + 1;
  cffIdx = iobj_0_tmp_tmp->cSFunObject.W2_CoeffIdx;
  maxWindow = phaseIdx * 20;
  iobj_0_tmp_tmp->cSFunObject.W1_Sums.re +=
      varargin_1.re * iobj_0_tmp_tmp->cSFunObject.P1_FILT[cffIdx];
  iobj_0_tmp_tmp->cSFunObject.W1_Sums.im +=
      varargin_1.im * iobj_0_tmp_tmp->cSFunObject.P1_FILT[cffIdx];
  cffIdx++;
  for (jIdx = i + 1; jIdx < maxWindow; jIdx++) {
    obj->W1_Sums.re += obj->W3_StatesBuff[jIdx].re * obj->P1_FILT[cffIdx];
    obj->W1_Sums.im += obj->W3_StatesBuff[jIdx].im * obj->P1_FILT[cffIdx];
    cffIdx++;
  }
  for (jIdx = maxWindow - 20; jIdx <= i; jIdx++) {
    obj->W1_Sums.re += obj->W3_StatesBuff[jIdx].re * obj->P1_FILT[cffIdx];
    obj->W1_Sums.im += obj->W3_StatesBuff[jIdx].im * obj->P1_FILT[cffIdx];
    cffIdx++;
  }
  iobj_0_tmp_tmp->cSFunObject.W3_StatesBuff[i] = varargin_1;
  i += 20;
  if (i >= 20) {
    i -= 20;
  }
  if (phaseIdx >= 1) {
    iobj_0_tmp_tmp->cSFunObject.O0_Y0 = iobj_0_tmp_tmp->cSFunObject.W1_Sums;
    iobj_0_tmp_tmp->cSFunObject.W1_Sums.re = 0.0;
    iobj_0_tmp_tmp->cSFunObject.W1_Sums.im = 0.0;
    phaseIdx = 0;
    cffIdx = 0;
    i--;
    if (i < 0) {
      i += 20;
    }
  }
  iobj_0_tmp_tmp->cSFunObject.W4_TapDelayIndex = i;
  iobj_0_tmp_tmp->cSFunObject.W2_CoeffIdx = cffIdx;
  iobj_0_tmp_tmp->cSFunObject.W0_PhaseIdx = phaseIdx;
  return iobj_0_tmp_tmp->cSFunObject.O0_Y0;
}

} // namespace comm
} // namespace coder

// End of code generation (RaisedCosineReceiveFilter.cpp)
