//
// ErrorRate.cpp
//
// Code generation for function 'ErrorRate'
//

// Include files
#include "ErrorRate.h"
#include "rt_nonfinite.h"
#include <string.h>

// Function Definitions
namespace coder {
namespace commcodegen {
ErrorRate::ErrorRate()
{
  this->matlabCodegenIsDeleted = true;
}

ErrorRate::~ErrorRate()
{
  this->matlabCodegenDestructor();
}

void ErrorRate::matlabCodegenDestructor()
{
  if (!this->matlabCodegenIsDeleted) {
    this->matlabCodegenIsDeleted = true;
    if (this->isInitialized == 1) {
      this->isInitialized = 2;
    }
  }
}

} // namespace commcodegen
} // namespace coder

// End of code generation (ErrorRate.cpp)
