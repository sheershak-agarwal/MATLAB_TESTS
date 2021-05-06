//
// QPSKModulator.cpp
//
// Code generation for function 'QPSKModulator'
//

// Include files
#include "QPSKModulator.h"
#include "rt_nonfinite.h"
#include <string.h>

// Function Definitions
namespace coder {
namespace commcodegen {
QPSKModulator::QPSKModulator()
{
  this->matlabCodegenIsDeleted = true;
}

QPSKModulator::~QPSKModulator()
{
  this->matlabCodegenDestructor();
}

void QPSKModulator::matlabCodegenDestructor()
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

// End of code generation (QPSKModulator.cpp)
