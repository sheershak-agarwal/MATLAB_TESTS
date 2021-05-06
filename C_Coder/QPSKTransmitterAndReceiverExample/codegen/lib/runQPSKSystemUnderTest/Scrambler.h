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
  void matlabCodegenDestructor();
  ~Scrambler();
  Scrambler();
  boolean_T matlabCodegenIsDeleted;
  int isInitialized;
  boolean_T isSetupComplete;
  comm_Scrambler_1 cSFunObject;
};

} // namespace commcodegen
} // namespace coder

#endif
// End of code generation (Scrambler.h)
