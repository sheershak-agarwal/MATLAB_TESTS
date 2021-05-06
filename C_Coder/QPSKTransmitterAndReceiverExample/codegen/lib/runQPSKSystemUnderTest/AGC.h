//
// AGC.h
//
// Code generation for function 'AGC'
//

#ifndef AGC_H
#define AGC_H

// Include files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
struct cell_wrap_4 {
  unsigned int f1[8];
};

namespace coder {
namespace comm {
class AGC {
public:
  int isInitialized;
  boolean_T isSetupComplete;
  boolean_T TunablePropsChanged;
  double AdaptationStepSize;
  double pCastedStepSize;
  boolean_T pStepSizeSet;
  boolean_T pDetectorMethodSet;
  boolean_T pLoopMethodSet;
  boolean_T pUpdatePeriodSet;
  boolean_T pGainOutputPortSet;
  double pFilterState[49];
  double pFilterSum;
  unsigned int pFilterStateIdx;
  double Gain;

private:
  cell_wrap_4 inputVarSize[1];
};

} // namespace comm
} // namespace coder

#endif
// End of code generation (AGC.h)
