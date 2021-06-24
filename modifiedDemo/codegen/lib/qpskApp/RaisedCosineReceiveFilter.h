//
// RaisedCosineReceiveFilter.h
//
// Code generation for function 'RaisedCosineReceiveFilter'
//

#ifndef RAISEDCOSINERECEIVEFILTER_H
#define RAISEDCOSINERECEIVEFILTER_H

// Include files
#include "FIRDecimator.h"
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
namespace coder {
namespace comm {
class RaisedCosineReceiveFilter {
public:
  creal_T step(const creal_T varargin_1);
  boolean_T matlabCodegenIsDeleted;
  int isInitialized;
  boolean_T isSetupComplete;
  dspcodegen::FIRDecimator *pFilter;
  dspcodegen::FIRDecimator _pobj0;
};

} // namespace comm
} // namespace coder

#endif
// End of code generation (RaisedCosineReceiveFilter.h)
