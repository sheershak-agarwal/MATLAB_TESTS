//
// RaisedCosineTransmitFilter.h
//
// Code generation for function 'RaisedCosineTransmitFilter'
//

#ifndef RAISEDCOSINETRANSMITFILTER_H
#define RAISEDCOSINETRANSMITFILTER_H

// Include files
#include "FIRInterpolator.h"
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
namespace coder {
namespace comm {
class RaisedCosineTransmitFilter {
public:
  void matlabCodegenDestructor();
  ~RaisedCosineTransmitFilter();
  RaisedCosineTransmitFilter();
  boolean_T matlabCodegenIsDeleted;
  int isInitialized;
  boolean_T isSetupComplete;
  dspcodegen::FIRInterpolator *pFilter;
  dspcodegen::FIRInterpolator _pobj0;
};

} // namespace comm
} // namespace coder

#endif
// End of code generation (RaisedCosineTransmitFilter.h)
