//
// FrameSynchronizer.h
//
// Code generation for function 'FrameSynchronizer'
//

#ifndef FRAMESYNCHRONIZER_H
#define FRAMESYNCHRONIZER_H

// Include files
#include "AGC.h"
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
namespace coder {
namespace comm {
namespace internal {
namespace examples {
class FrameSynchronizer {
public:
  void step(const creal_T varargin_1_data[], int varargin_1_size,
            const double varargin_2_data[], int varargin_2_size,
            const double varargin_3_data[], int varargin_3_size,
            creal_T varargout_1[1133], boolean_T *varargout_2);
  void matlabCodegenDestructor();
  ~FrameSynchronizer();
  FrameSynchronizer();
  boolean_T matlabCodegenIsDeleted;
  int isInitialized;
  double pNBuffer;
  double pBufferStartIdx;
  double pBufferEndIdx;
  double pPrbIdxBuffer[5];
  double pNPrbIdxBuffer;
  double pPrbIdxBufferStartIdx;

private:
  boolean_T isSetupComplete;
  cell_wrap_4 inputVarSize[3];
  double pPrbLenOffset;
  creal_T pBuffer[5665];
};

} // namespace examples
} // namespace internal
} // namespace comm
} // namespace coder

#endif
// End of code generation (FrameSynchronizer.h)
