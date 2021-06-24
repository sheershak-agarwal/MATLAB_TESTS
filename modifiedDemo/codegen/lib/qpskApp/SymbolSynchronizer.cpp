//
// SymbolSynchronizer.cpp
//
// Code generation for function 'SymbolSynchronizer'
//

// Include files
#include "SymbolSynchronizer.h"
#include "qpskApp_data.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <string.h>

// Function Definitions
namespace coder {
namespace comm {
void SymbolSynchronizer::resetImpl()
{
  this->pLoopFilterState = 0.0;
  this->pLoopPreviousInput = 0.0;
  this->pStrobe = false;
  this->pNumStrobe = 0.0;
  this->pStrobeHistory[0] = false;
  this->pStrobeHistory[1] = false;
  this->pMu = 0.0;
  this->pNCOCounter = 0.0;
  this->pTimingError = 0.0;
  this->pInterpFilterState[0].re = 0.0;
  this->pInterpFilterState[0].im = 0.0;
  this->pInterpFilterState[1].re = 0.0;
  this->pInterpFilterState[1].im = 0.0;
  this->pInterpFilterState[2].re = 0.0;
  this->pInterpFilterState[2].im = 0.0;
  this->pTEDBuffer[0].re = 0.0;
  this->pTEDBuffer[0].im = 0.0;
  this->pTEDBuffer[1].re = 0.0;
  this->pTEDBuffer[1].im = 0.0;
  this->pSymbolHolder.re = 0.0;
  this->pSymbolHolder.im = 0.0;
}

void SymbolSynchronizer::step(const creal_T varargin_1,
                              creal_T varargout_1_data[], int *varargout_1_size)
{
  static const double dv[12]{0.0, -0.5, 0.5,  0.0, 1.5,  -0.5,
                             1.0, -0.5, -0.5, 0.0, -0.5, 0.5};
  creal_T dcv[12];
  creal_T y[3];
  double d;
  double theta;
  double zeta;
  if (this->isInitialized != 1) {
    this->isSetupComplete = false;
    this->isInitialized = 1;
    zeta = this->DampingFactor;
    theta = this->NormalizedLoopBandwidth / 2.0 / (zeta + 0.25 / zeta);
    d = -((2.0 * zeta * theta + 1.0) + theta * theta) * this->DetectorGain;
    this->pProportionalGain = 4.0 * zeta * theta / d;
    this->pIntegratorGain = 4.0 * theta * theta / d;
    this->isSetupComplete = true;
    this->TunablePropsChanged = false;
    this->resetImpl();
  }
  if (this->TunablePropsChanged) {
    this->TunablePropsChanged = false;
    zeta = this->DampingFactor;
    theta = this->NormalizedLoopBandwidth / 2.0 / (zeta + 0.25 / zeta);
    d = -((2.0 * zeta * theta + 1.0) + theta * theta) * this->DetectorGain;
    this->pProportionalGain = 4.0 * zeta * theta / d;
    this->pIntegratorGain = 4.0 * theta * theta / d;
  }
  this->pNumStrobe = 0.0;
  if ((!(this->pNumStrobe == 1.0)) || (!this->pStrobe)) {
    creal_T xSeq_idx_1;
    creal_T xSeq_idx_2;
    creal_T xSeq_idx_3;
    double b_d;
    double intOut_im;
    double intOut_re;
    int i;
    this->pNumStrobe += static_cast<double>(this->pStrobe);
    this->pTimingError = this->pMu;
    xSeq_idx_1 = this->pInterpFilterState[0];
    xSeq_idx_2 = this->pInterpFilterState[1];
    xSeq_idx_3 = this->pInterpFilterState[2];
    for (i = 0; i < 12; i++) {
      dcv[i].re = dv[i];
      dcv[i].im = 0.0;
    }
    for (i = 0; i < 3; i++) {
      double d1;
      double d2;
      b_d = dcv[i].re;
      zeta = dcv[i].im;
      theta = dcv[i + 3].re;
      d = dcv[i + 3].im;
      intOut_im = dcv[i + 6].re;
      intOut_re = dcv[i + 6].im;
      d1 = dcv[i + 9].re;
      d2 = dcv[i + 9].im;
      y[i].re = (((b_d * varargin_1.re - zeta * varargin_1.im) +
                  (theta * xSeq_idx_1.re - d * xSeq_idx_1.im)) +
                 (intOut_im * xSeq_idx_2.re - intOut_re * xSeq_idx_2.im)) +
                (d1 * xSeq_idx_3.re - d2 * xSeq_idx_3.im);
      y[i].im = (((b_d * varargin_1.im + zeta * varargin_1.re) +
                  (theta * xSeq_idx_1.im + d * xSeq_idx_1.re)) +
                 (intOut_im * xSeq_idx_2.im + intOut_re * xSeq_idx_2.re)) +
                (d1 * xSeq_idx_3.im + d2 * xSeq_idx_3.re);
    }
    zeta = this->pMu;
    b_d = zeta * zeta;
    intOut_re = (y[0].re + this->pMu * y[1].re) + b_d * y[2].re;
    intOut_im = (y[0].im + this->pMu * y[1].im) + b_d * y[2].im;
    this->pInterpFilterState[0] = varargin_1;
    this->pInterpFilterState[1] = xSeq_idx_1;
    this->pInterpFilterState[2] = xSeq_idx_2;
    if (this->pStrobe) {
      this->pSymbolHolder.re = intOut_re;
      this->pSymbolHolder.im = intOut_im;
    }
    if (!(this->pNumStrobe > 1.0)) {
      if (this->pStrobe && (!this->pStrobeHistory[1])) {
        zeta = this->pTEDBuffer[1].re + this->pTEDBuffer[1].re;
        d = this->pTEDBuffer[1].im + this->pTEDBuffer[1].im;
        if (d == 0.0) {
          theta = zeta / 2.0;
          zeta = 0.0;
        } else if (zeta == 0.0) {
          theta = 0.0;
          zeta = d / 2.0;
        } else {
          theta = zeta / 2.0;
          zeta = d / 2.0;
        }
        d = theta * (this->pTEDBuffer[0].re - intOut_re) +
            zeta * (this->pTEDBuffer[0].im - intOut_im);
      } else {
        d = 0.0;
      }
      switch (this->pStrobeHistory[1] + this->pStrobe) {
      case 0:
        break;
      case 1:
        this->pTEDBuffer[0] = this->pTEDBuffer[1];
        this->pTEDBuffer[1].re = intOut_re;
        this->pTEDBuffer[1].im = intOut_im;
        break;
      default:
        this->pTEDBuffer[0].re = 0.0;
        this->pTEDBuffer[0].im = 0.0;
        this->pTEDBuffer[1].re = intOut_re;
        this->pTEDBuffer[1].im = intOut_im;
        break;
      }
      zeta = this->pLoopPreviousInput + this->pLoopFilterState;
      theta = d * this->pProportionalGain + zeta;
      this->pLoopFilterState = zeta;
      this->pLoopPreviousInput = d * this->pIntegratorGain;
      this->pStrobeHistory[0] = this->pStrobeHistory[1];
      this->pStrobeHistory[1] = this->pStrobe;
      this->pStrobe = (this->pNCOCounter < theta + 0.5);
      if (this->pStrobe) {
        this->pMu = this->pNCOCounter / (theta + 0.5);
      }
      zeta = this->pNCOCounter - (theta + 0.5);
      if (std::isnan(zeta) || std::isinf(zeta)) {
        theta = rtNaN;
      } else if (zeta == 0.0) {
        theta = 0.0;
      } else {
        theta = std::fmod(zeta, 1.0);
        if (theta == 0.0) {
          theta = 0.0;
        } else if (zeta < 0.0) {
          theta++;
        }
      }
      this->pNCOCounter = theta;
    }
  }
  *varargout_1_size = !(1.0 > this->pNumStrobe);
  if (0 <= *varargout_1_size - 1) {
    varargout_1_data[0] = this->pSymbolHolder;
  }
}

} // namespace comm
} // namespace coder

// End of code generation (SymbolSynchronizer.cpp)
