//
// Descrambler.cpp
//
// Code generation for function 'Descrambler'
//

// Include files
#include "Descrambler.h"
#include "rt_nonfinite.h"
#include <string.h>

// Function Definitions
namespace coder {
namespace commcodegen {
Descrambler::Descrambler()
{
  this->matlabCodegenIsDeleted = true;
}

Descrambler::~Descrambler()
{
  this->matlabCodegenDestructor();
}

void Descrambler::matlabCodegenDestructor()
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

// End of code generation (Descrambler.cpp)
