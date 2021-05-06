//
// RaisedCosineTransmitFilter.cpp
//
// Code generation for function 'RaisedCosineTransmitFilter'
//

// Include files
#include "RaisedCosineTransmitFilter.h"
#include "FIRInterpolator.h"
#include "rt_nonfinite.h"
#include <string.h>

// Function Definitions
namespace coder {
namespace comm {
RaisedCosineTransmitFilter::RaisedCosineTransmitFilter()
{
  this->matlabCodegenIsDeleted = true;
}

RaisedCosineTransmitFilter::~RaisedCosineTransmitFilter()
{
  this->matlabCodegenDestructor();
}

void RaisedCosineTransmitFilter::matlabCodegenDestructor()
{
  dspcodegen::FIRInterpolator *obj;
  if (!this->matlabCodegenIsDeleted) {
    this->matlabCodegenIsDeleted = true;
    if (this->isInitialized == 1) {
      this->isInitialized = 2;
      if (this->isSetupComplete) {
        obj = this->pFilter;
        if (obj->isInitialized == 1) {
          obj->isInitialized = 2;
        }
      }
    }
  }
}

} // namespace comm
} // namespace coder

// End of code generation (RaisedCosineTransmitFilter.cpp)
