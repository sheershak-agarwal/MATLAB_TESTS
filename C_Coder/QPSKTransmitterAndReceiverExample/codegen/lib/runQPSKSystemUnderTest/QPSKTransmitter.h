//
// QPSKTransmitter.h
//
// Code generation for function 'QPSKTransmitter'
//

#ifndef QPSKTRANSMITTER_H
#define QPSKTRANSMITTER_H

// Include files
#include "QPSKBitsGenerator.h"
#include "QPSKModulator.h"
#include "RaisedCosineTransmitFilter.h"
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
class QPSKTransmitter {
public:
  void step(creal_T varargout_1[2266]);
  void matlabCodegenDestructor();
  ~QPSKTransmitter();
  QPSKTransmitter();
  boolean_T matlabCodegenIsDeleted;
  int isInitialized;
  QPSKBitsGenerator pBitGenerator;
  coder::commcodegen::QPSKModulator pQPSKModulator;
  coder::comm::RaisedCosineTransmitFilter pTransmitterFilter;

private:
  boolean_T isSetupComplete;
};

#endif
// End of code generation (QPSKTransmitter.h)
