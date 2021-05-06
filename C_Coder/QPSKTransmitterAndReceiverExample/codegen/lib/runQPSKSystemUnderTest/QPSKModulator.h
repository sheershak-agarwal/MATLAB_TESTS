//
// QPSKModulator.h
//
// Code generation for function 'QPSKModulator'
//

#ifndef QPSKMODULATOR_H
#define QPSKMODULATOR_H

// Include files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
struct comm_QPSKModulator_0 {
  int S0_isInitialized;
  double P0_modmap[8];
};

namespace coder {
namespace commcodegen {
class QPSKModulator {
public:
  void matlabCodegenDestructor();
  ~QPSKModulator();
  QPSKModulator();
  boolean_T matlabCodegenIsDeleted;
  int isInitialized;
  boolean_T isSetupComplete;
  comm_QPSKModulator_0 cSFunObject;
};

} // namespace commcodegen
} // namespace coder

#endif
// End of code generation (QPSKModulator.h)
