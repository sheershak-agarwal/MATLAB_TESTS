//
// SymbolSynchronizer.cpp
//
// Code generation for function 'SymbolSynchronizer'
//

// Include files
#include "SymbolSynchronizer.h"
#include "rt_nonfinite.h"
#include <cstring>
#include <string.h>

// Function Definitions
namespace coder {
namespace comm {
SymbolSynchronizer::SymbolSynchronizer()
{
  this->matlabCodegenIsDeleted = true;
}

SymbolSynchronizer::~SymbolSynchronizer()
{
  this->matlabCodegenDestructor();
}

void SymbolSynchronizer::matlabCodegenDestructor()
{
  if (!this->matlabCodegenIsDeleted) {
    this->matlabCodegenIsDeleted = true;
    if (this->isInitialized == 1) {
      this->isInitialized = 2;
    }
  }
}

void SymbolSynchronizer::resetImpl()
{
  this->pLoopFilterState = 0.0;
  this->pLoopPreviousInput = 0.0;
  this->pStrobe = false;
  this->pNumStrobe = 0.0;
  this->pStrobeHistory[0] = false;
  this->pStrobeHistory[1] = false;
  this->pMu = 0.0;
  this->pNCOCounter = 0.0;
  std::memset(&this->pTimingError[0], 0, 2266U * sizeof(double));
  this->pInterpFilterState[0].re = 0.0;
  this->pInterpFilterState[0].im = 0.0;
  this->pInterpFilterState[1].re = 0.0;
  this->pInterpFilterState[1].im = 0.0;
  this->pInterpFilterState[2].re = 0.0;
  this->pInterpFilterState[2].im = 0.0;
  this->pTEDBuffer[0].re = 0.0;
  this->pTEDBuffer[0].im = 0.0;
  this->pTEDBuffer[1].re = 0.0;
  this->pTEDBuffer[1].im = 0.0;
  std::memset(&this->pSymbolHolder[0], 0, 1247U * sizeof(creal_T));
}

} // namespace comm
} // namespace coder

// End of code generation (SymbolSynchronizer.cpp)
