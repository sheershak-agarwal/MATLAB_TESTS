//
// FIRInterpolator.cpp
//
// Code generation for function 'FIRInterpolator'
//

// Include files
#include "FIRInterpolator.h"
#include "rt_nonfinite.h"
#include <string.h>

// Function Definitions
namespace coder {
namespace dspcodegen {
FIRInterpolator::FIRInterpolator()
{
  this->matlabCodegenIsDeleted = true;
}

FIRInterpolator::~FIRInterpolator()
{
  this->matlabCodegenDestructor();
}

void FIRInterpolator::matlabCodegenDestructor()
{
  if (!this->matlabCodegenIsDeleted) {
    this->matlabCodegenIsDeleted = true;
    if (this->isInitialized == 1) {
      this->isInitialized = 2;
    }
  }
}

} // namespace dspcodegen
} // namespace coder

// End of code generation (FIRInterpolator.cpp)
