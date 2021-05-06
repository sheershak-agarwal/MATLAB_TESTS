//
// ErrorRate.h
//
// Code generation for function 'ErrorRate'
//

#ifndef ERRORRATE_H
#define ERRORRATE_H

// Include files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
struct comm_ErrorRate_7 {
  int S0_isInitialized;
  double W0_errors;
  double W1_symbols;
  int W2_STDelay;
  double W3_txBuff;
  int W4_curTx;
  boolean_T W5_useFrame[2240];
  double P0_Subframe[1540];
};

namespace coder {
namespace commcodegen {
class ErrorRate {
public:
  void matlabCodegenDestructor();
  ~ErrorRate();
  ErrorRate();
  boolean_T matlabCodegenIsDeleted;
  int isInitialized;
  boolean_T isSetupComplete;
  comm_ErrorRate_7 cSFunObject;
};

} // namespace commcodegen
} // namespace coder

#endif
// End of code generation (ErrorRate.h)
