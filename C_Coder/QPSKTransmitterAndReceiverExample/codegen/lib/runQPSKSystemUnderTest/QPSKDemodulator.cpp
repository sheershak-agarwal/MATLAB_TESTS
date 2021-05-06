//
// QPSKDemodulator.cpp
//
// Code generation for function 'QPSKDemodulator'
//

// Include files
#include "QPSKDemodulator.h"
#include "rt_nonfinite.h"
#include <string.h>

// Function Definitions
namespace coder {
namespace commcodegen {
QPSKDemodulator::QPSKDemodulator()
{
  this->matlabCodegenIsDeleted = true;
}

QPSKDemodulator::~QPSKDemodulator()
{
  this->matlabCodegenDestructor();
}

void QPSKDemodulator::matlabCodegenDestructor()
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

// End of code generation (QPSKDemodulator.cpp)
