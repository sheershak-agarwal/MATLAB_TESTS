//
// Scrambler.h
//
// Code generation for function 'Scrambler'
//

#ifndef SCRAMBLER_H
#define SCRAMBLER_H

// Include files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
struct comm_Scrambler_1 {
  int S0_isInitialized;
  int W0_shiftReg[4];
  unsigned char P0_Polynomial[5];
  int P1_IniState[4];
};

namespace coder {
namespace commcodegen {
class Scrambler {
public:
  void step(const double varargin_1_data[], double varargout_1_data[],
            int varargout_1_size[2]);
  boolean_T matlabCodegenIsDeleted;
  int isInitialized;
  comm_Scrambler_1 cSFunObject;

private:
  boolean_T isSetupComplete;
};

} // namespace commcodegen
} // namespace coder

#endif
// End of code generation (Scrambler.h)
