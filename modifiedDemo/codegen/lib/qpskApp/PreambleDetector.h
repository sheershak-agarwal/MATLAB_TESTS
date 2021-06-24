//
// PreambleDetector.h
//
// Code generation for function 'PreambleDetector'
//

#ifndef PREAMBLEDETECTOR_H
#define PREAMBLEDETECTOR_H

// Include files
#include "AsyncBuffercgHelper.h"
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
namespace coder {
namespace comm {
class PreambleDetector {
public:
  int isInitialized;
  boolean_T isSetupComplete;
  boolean_T TunablePropsChanged;
  cell_wrap_3 inputVarSize[1];
  double Threshold;
  double pThreshold;
  creal_T pFilterStates[12];
};

} // namespace comm
} // namespace coder

#endif
// End of code generation (PreambleDetector.h)
