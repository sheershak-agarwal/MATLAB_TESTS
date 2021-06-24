//
// CarrierSynchronizer.h
//
// Code generation for function 'CarrierSynchronizer'
//

#ifndef CARRIERSYNCHRONIZER_H
#define CARRIERSYNCHRONIZER_H

// Include files
#include "AsyncBuffercgHelper.h"
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
namespace coder {
namespace comm {
class CarrierSynchronizer {
public:
  void step(const creal_T varargin_1_data[], int varargin_1_size,
            creal_T varargout_1_data[], int *varargout_1_size);
  int isInitialized;
  boolean_T TunablePropsChanged;
  char ModulationPhaseOffset[4];
  double CustomPhaseOffset;
  double SamplesPerSymbol;
  double DampingFactor;
  double NormalizedLoopBandwidth;
  double pPhase;
  creal_T pPreviousSample;
  double pLoopFilterState;
  double pIntegFilterState;
  double pDDSPreviousInput;

private:
  boolean_T isSetupComplete;
  cell_wrap_3 inputVarSize[1];
  double pProportionalGain;
  double pIntegratorGain;
  double pDigitalSynthesizerGain;
  double pActualPhaseOffset;
};

} // namespace comm
} // namespace coder

#endif
// End of code generation (CarrierSynchronizer.h)
