//
// QPSKDemodulator.h
//
// Code generation for function 'QPSKDemodulator'
//

#ifndef QPSKDEMODULATOR_H
#define QPSKDEMODULATOR_H

// Include files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
struct comm_QPSKDemodulator_5 {
  int S0_isInitialized;
};

namespace coder {
namespace commcodegen {
class QPSKDemodulator {
public:
  void matlabCodegenDestructor();
  ~QPSKDemodulator();
  QPSKDemodulator();
  boolean_T matlabCodegenIsDeleted;
  int isInitialized;
  boolean_T isSetupComplete;

private:
  comm_QPSKDemodulator_5 cSFunObject;
};

} // namespace commcodegen
} // namespace coder

#endif
// End of code generation (QPSKDemodulator.h)
