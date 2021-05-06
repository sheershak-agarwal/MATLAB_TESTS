//
// FIRDecimator.cpp
//
// Code generation for function 'FIRDecimator'
//

// Include files
#include "FIRDecimator.h"
#include "rt_nonfinite.h"
#include <string.h>

// Function Definitions
namespace coder {
namespace dspcodegen {
FIRDecimator::FIRDecimator()
{
  this->matlabCodegenIsDeleted = true;
}

FIRDecimator::~FIRDecimator()
{
  this->matlabCodegenDestructor();
}

void FIRDecimator::matlabCodegenDestructor()
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

// End of code generation (FIRDecimator.cpp)
