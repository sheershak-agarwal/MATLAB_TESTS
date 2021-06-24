//
// AsyncBuffercgHelper.h
//
// Code generation for function 'AsyncBuffercgHelper'
//

#ifndef ASYNCBUFFERCGHELPER_H
#define ASYNCBUFFERCGHELPER_H

// Include files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
struct cell_wrap_3 {
  unsigned int f1[8];
};

namespace coder {
namespace dsp {
namespace private_ {
class AsyncBuffercgHelper {
public:
  boolean_T matlabCodegenIsDeleted;
  int isInitialized;
  boolean_T isSetupComplete;
  int NumChannels;
  double Cache[11201];
  int CumulativeOverrun;
  int CumulativeUnderrun;
  int ReadPointer;
  int WritePointer;
  boolean_T AsyncBuffercgHelper_isInitialized;

private:
  cell_wrap_3 inputVarSize[1];
};

} // namespace private_
} // namespace dsp
} // namespace coder

#endif
// End of code generation (AsyncBuffercgHelper.h)
