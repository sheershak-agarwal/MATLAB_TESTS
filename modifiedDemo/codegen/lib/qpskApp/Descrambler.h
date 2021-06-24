//
// Descrambler.h
//
// Code generation for function 'Descrambler'
//

#ifndef DESCRAMBLER_H
#define DESCRAMBLER_H

// Include files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
struct comm_Descrambler_6 {
  int S0_isInitialized;
  int W0_shiftReg[4];
  unsigned char P0_Polynomial[5];
  int P1_IniState[4];
};

namespace coder {
namespace commcodegen {
class Descrambler {
public:
  boolean_T matlabCodegenIsDeleted;
  int isInitialized;
  boolean_T isSetupComplete;
  comm_Descrambler_6 cSFunObject;
};

} // namespace commcodegen
} // namespace coder

#endif
// End of code generation (Descrambler.h)
