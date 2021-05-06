//
// CoarseFrequencyCompensator.h
//
// Code generation for function 'CoarseFrequencyCompensator'
//

#ifndef COARSEFREQUENCYCOMPENSATOR_H
#define COARSEFREQUENCYCOMPENSATOR_H

// Include files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
namespace coder {
namespace comm {
class CoarseFrequencyCompensator {
public:
  void matlabCodegenDestructor();
  ~CoarseFrequencyCompensator();
  CoarseFrequencyCompensator();
  boolean_T matlabCodegenIsDeleted;
  int isInitialized;
  boolean_T isSetupComplete;
  creal_T pRaisedSignalBuffer[32];
  double pCumFreqOffset;
  creal_T pScratchVar[2266];
};

} // namespace comm
} // namespace coder

#endif
// End of code generation (CoarseFrequencyCompensator.h)
