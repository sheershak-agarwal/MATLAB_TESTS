//
// QPSKBitsGenerator.h
//
// Code generation for function 'QPSKBitsGenerator'
//

#ifndef QPSKBITSGENERATOR_H
#define QPSKBITSGENERATOR_H

// Include files
#include "Scrambler.h"
#include "SignalSource.h"
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
class QPSKBitsGenerator {
public:
  void matlabCodegenDestructor();
  ~QPSKBitsGenerator();
  QPSKBitsGenerator();
  boolean_T matlabCodegenIsDeleted;
  int isInitialized;
  boolean_T isSetupComplete;
  double pHeader[26];
  coder::commcodegen::Scrambler pScrambler;
  coder::dsp::SignalSource pSigSrc;
};

#endif
// End of code generation (QPSKBitsGenerator.h)
