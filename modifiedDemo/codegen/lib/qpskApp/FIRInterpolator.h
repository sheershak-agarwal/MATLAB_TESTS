//
// FIRInterpolator.h
//
// Code generation for function 'FIRInterpolator'
//

#ifndef FIRINTERPOLATOR_H
#define FIRINTERPOLATOR_H

// Include files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
struct dsp_FIRInterpolator_2 {
  int S0_isInitialized;
  creal_T W0_TapDelayBuff[10];
  int W1_PrevNumChan;
  creal_T P0_IC;
  double P1_FILTER_COEFF[22];
};

namespace coder {
namespace dspcodegen {
class FIRInterpolator {
public:
  boolean_T matlabCodegenIsDeleted;
  int isInitialized;
  boolean_T isSetupComplete;
  dsp_FIRInterpolator_2 cSFunObject;
};

} // namespace dspcodegen
} // namespace coder

#endif
// End of code generation (FIRInterpolator.h)
