//
// QPSKBitsGenerator.h
//
// Code generation for function 'QPSKBitsGenerator'
//

#ifndef QPSKBITSGENERATOR_H
#define QPSKBITSGENERATOR_H

// Include files
#include "AsyncBuffer.h"
#include "Scrambler.h"
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
class QPSKBitsGenerator {
public:
  void resetImpl();
  void releaseImpl();
  boolean_T matlabCodegenIsDeleted;
  int isInitialized;
  boolean_T isSetupComplete;
  double pHeader[26];
  coder::commcodegen::Scrambler pScrambler;
  coder::dsp::AsyncBuffer pSigSrc;
  double MessageBits[11200];
};

#endif
// End of code generation (QPSKBitsGenerator.h)
