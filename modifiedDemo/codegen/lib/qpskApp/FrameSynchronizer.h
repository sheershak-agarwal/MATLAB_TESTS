//
// FrameSynchronizer.h
//
// Code generation for function 'FrameSynchronizer'
//

#ifndef FRAMESYNCHRONIZER_H
#define FRAMESYNCHRONIZER_H

// Include files
#include "AsyncBuffercgHelper.h"
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
class FrameSynchronizer {
public:
  void step(const creal_T varargin_1_data[], int varargin_1_size,
            int varargin_2_size, int varargin_3_size, creal_T varargout_1[1133],
            boolean_T *varargout_2);
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
  cell_wrap_3 inputVarSize[3];
  double pPrbLenOffset;
  creal_T pBuffer[5665];
};

#endif
// End of code generation (FrameSynchronizer.h)
