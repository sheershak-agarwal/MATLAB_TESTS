//
// QPSKDataDecoder.h
//
// Code generation for function 'QPSKDataDecoder'
//

#ifndef QPSKDATADECODER_H
#define QPSKDATADECODER_H

// Include files
#include "Descrambler.h"
#include "ErrorRate.h"
#include "QPSKDemodulator.h"
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
class QPSKDataDecoder {
public:
  void step(const creal_T varargin_1[1133], boolean_T varargin_2,
            double varargout_1[3]);
  void matlabCodegenDestructor();
  ~QPSKDataDecoder();
  QPSKDataDecoder();
  boolean_T matlabCodegenIsDeleted;
  int isInitialized;
  boolean_T isSetupComplete;
  coder::commcodegen::QPSKDemodulator pQPSKDemodulator;
  coder::commcodegen::Descrambler pDescrambler;
  coder::commcodegen::ErrorRate pErrorRateCalc;
  double pBER[3];

private:
  double pTargetBits[2240];
};

#endif
// End of code generation (QPSKDataDecoder.h)
