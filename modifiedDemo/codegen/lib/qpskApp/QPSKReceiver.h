//
// QPSKReceiver.h
//
// Code generation for function 'QPSKReceiver'
//

#ifndef QPSKRECEIVER_H
#define QPSKRECEIVER_H

// Include files
#include "AGC.h"
#include "CarrierSynchronizer.h"
#include "CoarseFrequencyCompensator.h"
#include "FrameSynchronizer.h"
#include "PhaseFrequencyOffset.h"
#include "PreambleDetector.h"
#include "QPSKDataDecoder.h"
#include "RaisedCosineReceiveFilter.h"
#include "SymbolSynchronizer.h"
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
class QPSKReceiver {
public:
  void stepImpl(const creal_T bufferSignal, creal_T *RCRxSignal,
                creal_T timingRecSignal_data[], int *timingRecSignal_size,
                creal_T fineCompSignal_data[], int *fineCompSignal_size);
  boolean_T matlabCodegenIsDeleted;
  int isInitialized;
  boolean_T isSetupComplete;
  coder::comm::AGC pAGC;
  coder::comm::RaisedCosineReceiveFilter pRxFilter;
  coder::comm::CoarseFrequencyCompensator pCoarseFreqEstimator;
  coder::commcodegen::PhaseFrequencyOffset pCoarseFreqCompensator;
  coder::comm::CarrierSynchronizer pFineFreqCompensator;
  coder::comm::SymbolSynchronizer pTimingRec;
  coder::comm::PreambleDetector pPrbDet;
  FrameSynchronizer pFrameSync;
  QPSKDataDecoder pDataDecod;
  double pMeanFreqOff;
  double pCnt;
  double BerMask[1540];
  char pMessage[11];
  double pMessageLength;
};

#endif
// End of code generation (QPSKReceiver.h)
