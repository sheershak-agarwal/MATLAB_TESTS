//
// QPSKBitsGenerator.cpp
//
// Code generation for function 'QPSKBitsGenerator'
//

// Include files
#include "QPSKBitsGenerator.h"
#include "Scrambler.h"
#include "SignalSource.h"
#include "rt_nonfinite.h"
#include <string.h>

// Function Definitions
QPSKBitsGenerator::QPSKBitsGenerator()
{
  this->matlabCodegenIsDeleted = true;
}

QPSKBitsGenerator::~QPSKBitsGenerator()
{
  this->matlabCodegenDestructor();
}

void QPSKBitsGenerator::matlabCodegenDestructor()
{
  if (!this->matlabCodegenIsDeleted) {
    this->matlabCodegenIsDeleted = true;
    if (this->isInitialized == 1) {
      this->isInitialized = 2;
      if (this->isSetupComplete) {
        if (this->pScrambler.isInitialized == 1) {
          this->pScrambler.isInitialized = 2;
        }
        if (this->pSigSrc.isInitialized == 1) {
          this->pSigSrc.isInitialized = 2;
        }
      }
    }
  }
}

// End of code generation (QPSKBitsGenerator.cpp)
