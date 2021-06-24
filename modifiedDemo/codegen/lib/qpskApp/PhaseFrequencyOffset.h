//
// PhaseFrequencyOffset.h
//
// Code generation for function 'PhaseFrequencyOffset'
//

#ifndef PHASEFREQUENCYOFFSET_H
#define PHASEFREQUENCYOFFSET_H

// Include files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
struct comm_PhaseFrequencyOffset_3 {
  int S0_isInitialized;
  double W0_freqTnow;
  double P0_Phase;
};

namespace coder {
namespace commcodegen {
class PhaseFrequencyOffset {
public:
  boolean_T matlabCodegenIsDeleted;
  int isInitialized;
  boolean_T isSetupComplete;
  comm_PhaseFrequencyOffset_3 cSFunObject;
};

} // namespace commcodegen
} // namespace coder

#endif
// End of code generation (PhaseFrequencyOffset.h)
