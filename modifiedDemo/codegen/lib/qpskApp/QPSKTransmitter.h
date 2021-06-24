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
  void stepImpl(creal_T transmittedSignal_data[],
                int transmittedSignal_size[2]);
  boolean_T matlabCodegenIsDeleted;
  int isInitialized;
  boolean_T isSetupComplete;
  QPSKBitsGenerator pBitGenerator;
  coder::commcodegen::QPSKModulator pQPSKModulator;
  coder::comm::RaisedCosineTransmitFilter pTransmitterFilter;
  double MessageBits[11200];
};

#endif
// End of code generation (QPSKTransmitter.h)
