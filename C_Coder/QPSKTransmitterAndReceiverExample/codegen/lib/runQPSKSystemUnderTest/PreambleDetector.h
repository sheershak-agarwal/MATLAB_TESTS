//
// PreambleDetector.h
//
// Code generation for function 'PreambleDetector'
//

#ifndef PREAMBLEDETECTOR_H
#define PREAMBLEDETECTOR_H

// Include files
#include "AGC.h"
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
namespace coder {
namespace comm {
class PreambleDetector {
public:
  void step(const creal_T varargin_1_data[], int varargin_1_size,
            double varargout_1_data[], int *varargout_1_size,
            double varargout_2_data[], int *varargout_2_size);
  int isInitialized;
  boolean_T TunablePropsChanged;
  double Threshold;
  creal_T pFilterStates[12];

private:
  boolean_T isSetupComplete;
  cell_wrap_4 inputVarSize[1];
  double pThreshold;
};

} // namespace comm
} // namespace coder

#endif
// End of code generation (PreambleDetector.h)
