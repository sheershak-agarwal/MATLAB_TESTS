//
// PhaseFrequencyOffset.cpp
//
// Code generation for function 'PhaseFrequencyOffset'
//

// Include files
#include "PhaseFrequencyOffset.h"
#include "rt_nonfinite.h"
#include <string.h>

// Function Definitions
namespace coder {
namespace commcodegen {
PhaseFrequencyOffset::PhaseFrequencyOffset()
{
  this->matlabCodegenIsDeleted = true;
}

PhaseFrequencyOffset::~PhaseFrequencyOffset()
{
  this->matlabCodegenDestructor();
}

void PhaseFrequencyOffset::matlabCodegenDestructor()
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

// End of code generation (PhaseFrequencyOffset.cpp)
