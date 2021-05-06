//
// FIRDecimator.h
//
// Code generation for function 'FIRDecimator'
//

#ifndef FIRDECIMATOR_H
#define FIRDECIMATOR_H

// Include files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
struct dsp_FIRDecimator_4 {
  int S0_isInitialized;
  int W0_PhaseIdx;
  creal_T W1_Sums;
  int W2_CoeffIdx;
  creal_T W3_StatesBuff[20];
  int W4_TapDelayIndex;
  int W5_PrevNumChan;
  creal_T P0_IC;
  double P1_FILT[21];
  creal_T O0_Y0[2266];
};

namespace coder {
namespace dspcodegen {
class FIRDecimator {
public:
  void matlabCodegenDestructor();
  ~FIRDecimator();
  FIRDecimator();
  boolean_T matlabCodegenIsDeleted;
  int isInitialized;
  boolean_T isSetupComplete;
  dsp_FIRDecimator_4 cSFunObject;
};

} // namespace dspcodegen
} // namespace coder

#endif
// End of code generation (FIRDecimator.h)
