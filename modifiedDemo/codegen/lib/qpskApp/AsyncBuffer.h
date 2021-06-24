//
// AsyncBuffer.h
//
// Code generation for function 'AsyncBuffer'
//

#ifndef ASYNCBUFFER_H
#define ASYNCBUFFER_H

// Include files
#include "AsyncBuffercgHelper.h"
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
namespace coder {
namespace dsp {
class AsyncBuffer {
public:
  void write(const double in[11200]);
  void read(double out_data[], int *out_size);
  boolean_T matlabCodegenIsDeleted;
  private_::AsyncBuffercgHelper pBuffer;
};

} // namespace dsp
} // namespace coder

#endif
// End of code generation (AsyncBuffer.h)
