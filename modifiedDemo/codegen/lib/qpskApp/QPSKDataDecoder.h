//
// QPSKDataDecoder.h
//
// Code generation for function 'QPSKDataDecoder'
//

#ifndef QPSKDATADECODER_H
#define QPSKDATADECODER_H

// Include files
#include "Descrambler.h"
#include "QPSKDemodulator.h"
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
class QPSKDataDecoder {
public:
  void step(const creal_T varargin_1[1133], boolean_T varargin_2);
  boolean_T matlabCodegenIsDeleted;
  int isInitialized;
  boolean_T isSetupComplete;
  coder::commcodegen::QPSKDemodulator pQPSKDemodulator;
  coder::commcodegen::Descrambler pDescrambler;
};

#endif
// End of code generation (QPSKDataDecoder.h)
