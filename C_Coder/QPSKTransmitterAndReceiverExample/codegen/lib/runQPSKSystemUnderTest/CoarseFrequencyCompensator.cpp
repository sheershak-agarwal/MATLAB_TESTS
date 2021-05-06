//
// CoarseFrequencyCompensator.cpp
//
// Code generation for function 'CoarseFrequencyCompensator'
//

// Include files
#include "CoarseFrequencyCompensator.h"
#include "rt_nonfinite.h"
#include <string.h>

// Function Definitions
namespace coder {
namespace comm {
CoarseFrequencyCompensator::CoarseFrequencyCompensator()
{
  this->matlabCodegenIsDeleted = true;
}

CoarseFrequencyCompensator::~CoarseFrequencyCompensator()
{
  this->matlabCodegenDestructor();
}

void CoarseFrequencyCompensator::matlabCodegenDestructor()
{
  if (!this->matlabCodegenIsDeleted) {
    this->matlabCodegenIsDeleted = true;
    if (this->isInitialized == 1) {
      this->isInitialized = 2;
    }
  }
}

} // namespace comm
} // namespace coder

// End of code generation (CoarseFrequencyCompensator.cpp)
