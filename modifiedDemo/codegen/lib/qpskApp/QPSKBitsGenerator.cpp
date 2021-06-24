//
// QPSKBitsGenerator.cpp
//
// Code generation for function 'QPSKBitsGenerator'
//

// Include files
#include "QPSKBitsGenerator.h"
#include "AsyncBuffer.h"
#include "AsyncBuffercgHelper.h"
#include "Scrambler.h"
#include "rt_nonfinite.h"
#include <cstring>
#include <string.h>

// Function Definitions
void QPSKBitsGenerator::releaseImpl()
{
  if (this->pScrambler.isInitialized == 1) {
    this->pScrambler.isInitialized = 2;
  }
  if (this->pSigSrc.pBuffer.isInitialized == 1) {
    this->pSigSrc.pBuffer.isInitialized = 2;
    if (this->pSigSrc.pBuffer.isSetupComplete) {
      this->pSigSrc.pBuffer.ReadPointer = 1;
      this->pSigSrc.pBuffer.WritePointer = 2;
      this->pSigSrc.pBuffer.CumulativeOverrun = 0;
      this->pSigSrc.pBuffer.CumulativeUnderrun = 0;
      this->pSigSrc.pBuffer.AsyncBuffercgHelper_isInitialized = false;
      this->pSigSrc.pBuffer.NumChannels = -1;
    }
  }
}

void QPSKBitsGenerator::resetImpl()
{
  if (this->pScrambler.isInitialized == 1) {
    // System object Initialization function: comm.Scrambler
    this->pScrambler.cSFunObject.W0_shiftReg[0] =
        this->pScrambler.cSFunObject.P1_IniState[0];
    this->pScrambler.cSFunObject.W0_shiftReg[1] =
        this->pScrambler.cSFunObject.P1_IniState[1];
    this->pScrambler.cSFunObject.W0_shiftReg[2] =
        this->pScrambler.cSFunObject.P1_IniState[2];
    this->pScrambler.cSFunObject.W0_shiftReg[3] =
        this->pScrambler.cSFunObject.P1_IniState[3];
  }
  if (this->pSigSrc.pBuffer.isInitialized == 1) {
    this->pSigSrc.pBuffer.ReadPointer = 1;
    this->pSigSrc.pBuffer.WritePointer = 2;
    this->pSigSrc.pBuffer.CumulativeOverrun = 0;
    this->pSigSrc.pBuffer.CumulativeUnderrun = 0;
    std::memset(&this->pSigSrc.pBuffer.Cache[0], 0, 11201U * sizeof(double));
  }
}

// End of code generation (QPSKBitsGenerator.cpp)
