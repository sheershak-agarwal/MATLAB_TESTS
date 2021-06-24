//
// CarrierSynchronizer.cpp
//
// Code generation for function 'CarrierSynchronizer'
//

// Include files
#include "CarrierSynchronizer.h"
#include "AsyncBuffercgHelper.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <string.h>

// Function Definitions
namespace coder {
namespace comm {
void CarrierSynchronizer::step(const creal_T varargin_1_data[],
                               int varargin_1_size, creal_T varargout_1_data[],
                               int *varargout_1_size)
{
  static const char b[4]{'A', 'u', 't', 'o'};
  double DDSOut;
  double DDSPreviousInp;
  double PhaseRecoveryGain;
  double d;
  double loopFiltOut;
  double previousSample_im;
  double previousSample_re;
  double theta;
  double y_im;
  int ret;
  signed char inSize[8];
  boolean_T exitg1;
  if (this->isInitialized != 1) {
    this->isSetupComplete = false;
    this->isInitialized = 1;
    this->inputVarSize[0].f1[0] = static_cast<unsigned int>(varargin_1_size);
    this->inputVarSize[0].f1[1] = 1U;
    for (ret = 0; ret < 6; ret++) {
      this->inputVarSize[0].f1[ret + 2] = 1U;
    }
    this->pPhase = 0.0;
    this->pPreviousSample.re = 0.0;
    this->pPreviousSample.im = 0.0;
    PhaseRecoveryGain = this->SamplesPerSymbol;
    theta = this->NormalizedLoopBandwidth * this->SamplesPerSymbol /
            ((this->DampingFactor + 0.25 / this->DampingFactor) *
             this->SamplesPerSymbol);
    d = (2.0 * this->DampingFactor * theta + 1.0) + theta * theta;
    this->pProportionalGain =
        4.0 * this->DampingFactor * theta / d / (2.0 * PhaseRecoveryGain);
    this->pIntegratorGain = 4.0 * theta * theta / d / (2.0 * PhaseRecoveryGain);
    ret = memcmp(&this->ModulationPhaseOffset[0], &b[0], 4);
    if (ret == 0) {
      this->pActualPhaseOffset = 0.0;
    } else {
      this->pActualPhaseOffset = this->CustomPhaseOffset - 0.78539816339744828;
    }
    this->pDigitalSynthesizerGain = -1.0;
    this->isSetupComplete = true;
    this->TunablePropsChanged = false;
    this->pLoopFilterState = 0.0;
    this->pIntegFilterState = 0.0;
    this->pDDSPreviousInput = 0.0;
    this->pPhase = 0.0;
    this->pPreviousSample.re = 0.0;
    this->pPreviousSample.im = 0.0;
  }
  if (this->TunablePropsChanged) {
    this->TunablePropsChanged = false;
    PhaseRecoveryGain = this->SamplesPerSymbol;
    theta = this->NormalizedLoopBandwidth * this->SamplesPerSymbol /
            ((this->DampingFactor + 0.25 / this->DampingFactor) *
             this->SamplesPerSymbol);
    d = (2.0 * this->DampingFactor * theta + 1.0) + theta * theta;
    this->pProportionalGain =
        4.0 * this->DampingFactor * theta / d / (2.0 * PhaseRecoveryGain);
    this->pIntegratorGain = 4.0 * theta * theta / d / (2.0 * PhaseRecoveryGain);
    ret = memcmp(&this->ModulationPhaseOffset[0], &b[0], 4);
    if (ret == 0) {
      this->pActualPhaseOffset = 0.0;
    } else {
      this->pActualPhaseOffset = this->CustomPhaseOffset - 0.78539816339744828;
    }
  }
  inSize[0] = static_cast<signed char>(varargin_1_size);
  inSize[1] = 1;
  for (ret = 0; ret < 6; ret++) {
    inSize[ret + 2] = 1;
  }
  ret = 0;
  exitg1 = false;
  while ((!exitg1) && (ret < 8)) {
    if (this->inputVarSize[0].f1[ret] !=
        static_cast<unsigned int>(inSize[ret])) {
      for (ret = 0; ret < 8; ret++) {
        this->inputVarSize[0].f1[ret] = static_cast<unsigned int>(inSize[ret]);
      }
      exitg1 = true;
    } else {
      ret++;
    }
  }
  loopFiltOut = this->pLoopFilterState;
  DDSOut = this->pIntegFilterState;
  DDSPreviousInp = this->pDDSPreviousInput;
  previousSample_re = this->pPreviousSample.re;
  previousSample_im = this->pPreviousSample.im;
  *varargout_1_size = varargin_1_size;
  for (ret = 0; ret < varargin_1_size; ret++) {
    PhaseRecoveryGain = previousSample_re;
    if (previousSample_re < 0.0) {
      PhaseRecoveryGain = -1.0;
    } else if (previousSample_re > 0.0) {
      PhaseRecoveryGain = 1.0;
    } else if (previousSample_re == 0.0) {
      PhaseRecoveryGain = 0.0;
    }
    theta = previousSample_im;
    if (previousSample_im < 0.0) {
      theta = -1.0;
    } else if (previousSample_im > 0.0) {
      theta = 1.0;
    } else if (previousSample_im == 0.0) {
      theta = 0.0;
    }
    PhaseRecoveryGain =
        PhaseRecoveryGain * previousSample_im - theta * previousSample_re;
    d = this->pPhase * 0.0;
    y_im = this->pPhase;
    if (y_im == 0.0) {
      d = std::exp(d);
      y_im = 0.0;
    } else {
      theta = std::exp(d / 2.0);
      d = theta * (theta * std::cos(y_im));
      y_im = theta * (theta * std::sin(y_im));
    }
    previousSample_re =
        varargin_1_data[0].re * d - varargin_1_data[0].im * y_im;
    previousSample_im =
        varargin_1_data[0].re * y_im + varargin_1_data[0].im * d;
    varargout_1_data[0].re = previousSample_re;
    varargout_1_data[0].im = previousSample_im;
    loopFiltOut += PhaseRecoveryGain * this->pIntegratorGain;
    DDSOut += DDSPreviousInp;
    DDSPreviousInp = PhaseRecoveryGain * this->pProportionalGain + loopFiltOut;
    this->pPhase = this->pDigitalSynthesizerGain * DDSOut;
  }
  d = this->pActualPhaseOffset * 0.0;
  y_im = this->pActualPhaseOffset;
  if (y_im == 0.0) {
    d = std::exp(d);
    y_im = 0.0;
  } else {
    theta = std::exp(d / 2.0);
    d = theta * (theta * std::cos(y_im));
    y_im = theta * (theta * std::sin(y_im));
  }
  for (ret = 0; ret < varargin_1_size; ret++) {
    PhaseRecoveryGain =
        varargout_1_data[0].re * y_im + varargout_1_data[0].im * d;
    varargout_1_data[0].re =
        varargout_1_data[0].re * d - varargout_1_data[0].im * y_im;
    varargout_1_data[0].im = PhaseRecoveryGain;
  }
  this->pLoopFilterState = loopFiltOut;
  this->pIntegFilterState = DDSOut;
  this->pPreviousSample.re = previousSample_re;
  this->pPreviousSample.im = previousSample_im;
  this->pDDSPreviousInput = DDSPreviousInp;
}

} // namespace comm
} // namespace coder

// End of code generation (CarrierSynchronizer.cpp)
