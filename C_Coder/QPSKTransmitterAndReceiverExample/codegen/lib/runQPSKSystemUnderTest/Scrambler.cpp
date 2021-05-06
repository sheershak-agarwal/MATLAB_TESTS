//
// Scrambler.cpp
//
// Code generation for function 'Scrambler'
//

// Include files
#include "Scrambler.h"
#include "rt_nonfinite.h"
#include <string.h>

// Function Definitions
namespace coder {
namespace commcodegen {
Scrambler::Scrambler()
{
  this->matlabCodegenIsDeleted = true;
}

Scrambler::~Scrambler()
{
  this->matlabCodegenDestructor();
}

void Scrambler::matlabCodegenDestructor()
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

// End of code generation (Scrambler.cpp)
