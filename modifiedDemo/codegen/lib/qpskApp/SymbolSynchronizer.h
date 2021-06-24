//
// SymbolSynchronizer.h
//
// Code generation for function 'SymbolSynchronizer'
//

#ifndef SYMBOLSYNCHRONIZER_H
#define SYMBOLSYNCHRONIZER_H

// Include files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
namespace coder {
namespace comm {
class SymbolSynchronizer {
public:
  void step(const creal_T varargin_1, creal_T varargout_1_data[],
            int *varargout_1_size);
  void resetImpl();
  boolean_T matlabCodegenIsDeleted;
  int isInitialized;
  boolean_T TunablePropsChanged;
  double DampingFactor;
  double NormalizedLoopBandwidth;
  double DetectorGain;

private:
  boolean_T isSetupComplete;
  double pProportionalGain;
  double pIntegratorGain;
  creal_T pInterpFilterState[3];
  double pMu;
  creal_T pTEDBuffer[2];
  boolean_T pStrobe;
  double pNumStrobe;
  boolean_T pStrobeHistory[2];
  double pNCOCounter;
  double pTimingError;
  creal_T pSymbolHolder;
  double pLoopFilterState;
  double pLoopPreviousInput;
};

} // namespace comm
} // namespace coder

#endif
// End of code generation (SymbolSynchronizer.h)
