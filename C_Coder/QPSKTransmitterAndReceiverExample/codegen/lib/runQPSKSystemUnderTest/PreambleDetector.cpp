//
// PreambleDetector.cpp
//
// Code generation for function 'PreambleDetector'
//

// Include files
#include "PreambleDetector.h"
#include "AGC.h"
#include "rt_nonfinite.h"
#include "runQPSKSystemUnderTest_rtwutil.h"
#include <algorithm>
#include <cstring>
#include <string.h>

// Function Definitions
namespace coder {
namespace comm {
void PreambleDetector::step(const creal_T varargin_1_data[],
                            int varargin_1_size, double varargout_1_data[],
                            int *varargout_1_size, double varargout_2_data[],
                            int *varargout_2_size)
{
  static const creal_T b[13]{{
                                 -0.70710678118654757, // re
                                 0.70710678118654757   // im
                             },
                             {
                                 0.70710678118654757, // re
                                 -0.70710678118654757 // im
                             },
                             {
                                 -0.70710678118654757, // re
                                 0.70710678118654757   // im
                             },
                             {
                                 0.70710678118654757, // re
                                 -0.70710678118654757 // im
                             },
                             {
                                 -0.70710678118654757, // re
                                 0.70710678118654757   // im
                             },
                             {
                                 -0.70710678118654757, // re
                                 0.70710678118654757   // im
                             },
                             {
                                 0.70710678118654757, // re
                                 -0.70710678118654757 // im
                             },
                             {
                                 0.70710678118654757, // re
                                 -0.70710678118654757 // im
                             },
                             {
                                 -0.70710678118654757, // re
                                 0.70710678118654757   // im
                             },
                             {
                                 -0.70710678118654757, // re
                                 0.70710678118654757   // im
                             },
                             {
                                 -0.70710678118654757, // re
                                 0.70710678118654757   // im
                             },
                             {
                                 -0.70710678118654757, // re
                                 0.70710678118654757   // im
                             },
                             {
                                 -0.70710678118654757, // re
                                 0.70710678118654757   // im
                             }};
  creal_T crossCorr1_data[1247];
  creal_T newFilterStates[12];
  int i;
  int k;
  short ii_data[1247];
  short inSize[8];
  boolean_T x_data[1247];
  boolean_T exitg1;
  if (this->isInitialized != 1) {
    this->isSetupComplete = false;
    this->isInitialized = 1;
    this->inputVarSize[0].f1[0] = static_cast<unsigned int>(varargin_1_size);
    this->inputVarSize[0].f1[1] = 1U;
    for (i = 0; i < 6; i++) {
      this->inputVarSize[0].f1[i + 2] = 1U;
    }
    this->pThreshold = this->Threshold;
    this->isSetupComplete = true;
    this->TunablePropsChanged = false;
    std::memset(&this->pFilterStates[0], 0, 12U * sizeof(creal_T));
  }
  if (this->TunablePropsChanged) {
    this->TunablePropsChanged = false;
    this->pThreshold = this->Threshold;
  }
  inSize[0] = static_cast<short>(varargin_1_size);
  inSize[1] = 1;
  for (i = 0; i < 6; i++) {
    inSize[i + 2] = 1;
  }
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 8)) {
    if (this->inputVarSize[0].f1[k] != static_cast<unsigned int>(inSize[k])) {
      for (i = 0; i < 8; i++) {
        this->inputVarSize[0].f1[i] = static_cast<unsigned int>(inSize[i]);
      }
      exitg1 = true;
    } else {
      k++;
    }
  }
  if (varargin_1_size == 0) {
    *varargout_1_size = 0;
    *varargout_2_size = 0;
  } else {
    double threshold;
    int b_re_tmp;
    int j;
    int naxpy;
    int niccp;
    threshold = this->pThreshold;
    std::memset(&newFilterStates[0], 0, 12U * sizeof(creal_T));
    if (varargin_1_size < 12) {
      niccp = varargin_1_size - 1;
    } else {
      niccp = 11;
    }
    if (0 <= niccp) {
      std::copy(&this->pFilterStates[0], &this->pFilterStates[niccp + 1],
                &crossCorr1_data[0]);
    }
    i = niccp + 2;
    if (i <= varargin_1_size) {
      std::memset(&crossCorr1_data[i + -1], 0,
                  ((varargin_1_size - i) + 1) * sizeof(creal_T));
    }
    if (varargin_1_size >= 26) {
      for (k = 0; k < 13; k++) {
        niccp = k + 1;
        for (j = niccp; j <= varargin_1_size; j++) {
          double d;
          double d1;
          b_re_tmp = (j - k) - 1;
          d = b[k].re;
          d1 = b[k].im;
          crossCorr1_data[j - 1].re += d * varargin_1_data[b_re_tmp].re -
                                       d1 * varargin_1_data[b_re_tmp].im;
          crossCorr1_data[j - 1].im += d * varargin_1_data[b_re_tmp].im +
                                       d1 * varargin_1_data[b_re_tmp].re;
        }
      }
    } else {
      double d;
      double d1;
      if (varargin_1_size > 13) {
        niccp = varargin_1_size - 14;
      } else {
        niccp = -1;
      }
      for (k = 0; k <= niccp; k++) {
        for (j = 0; j < 13; j++) {
          i = k + j;
          d = b[j].re;
          d1 = b[j].im;
          crossCorr1_data[i].re +=
              varargin_1_data[k].re * d - varargin_1_data[k].im * d1;
          crossCorr1_data[i].im +=
              varargin_1_data[k].re * d1 + varargin_1_data[k].im * d;
        }
      }
      naxpy = varargin_1_size - niccp;
      i = niccp + 2;
      for (k = i; k <= varargin_1_size; k++) {
        for (j = 0; j <= naxpy - 2; j++) {
          niccp = (k + j) - 1;
          d = b[j].re;
          d1 = b[j].im;
          crossCorr1_data[niccp].re +=
              varargin_1_data[k - 1].re * d - varargin_1_data[k - 1].im * d1;
          crossCorr1_data[niccp].im +=
              varargin_1_data[k - 1].re * d1 + varargin_1_data[k - 1].im * d;
        }
        naxpy--;
      }
    }
    if (varargin_1_size < 12) {
      niccp = 11 - varargin_1_size;
      for (k = 0; k <= niccp; k++) {
        newFilterStates[k] = this->pFilterStates[k + varargin_1_size];
      }
    }
    if (varargin_1_size >= 13) {
      niccp = varargin_1_size - 12;
    } else {
      niccp = 0;
    }
    i = varargin_1_size - 1;
    for (k = niccp; k <= i; k++) {
      b_re_tmp = varargin_1_size - k;
      naxpy = 12 - b_re_tmp;
      for (j = 0; j <= naxpy; j++) {
        int varargin_1_re_tmp;
        varargin_1_re_tmp = b_re_tmp + j;
        newFilterStates[j].re +=
            varargin_1_data[k].re * b[varargin_1_re_tmp].re -
            varargin_1_data[k].im * b[varargin_1_re_tmp].im;
        newFilterStates[j].im +=
            varargin_1_data[k].re * b[varargin_1_re_tmp].im +
            varargin_1_data[k].im * b[varargin_1_re_tmp].re;
      }
    }
    *varargout_2_size = varargin_1_size;
    for (k = 0; k < varargin_1_size; k++) {
      varargout_2_data[k] =
          rt_hypotd_snf(crossCorr1_data[k].re, crossCorr1_data[k].im);
    }
    for (i = 0; i < varargin_1_size; i++) {
      x_data[i] = (varargout_2_data[i] >= threshold);
    }
    niccp = 0;
    *varargout_1_size = varargin_1_size;
    b_re_tmp = 0;
    exitg1 = false;
    while ((!exitg1) && (b_re_tmp <= varargin_1_size - 1)) {
      if (x_data[b_re_tmp]) {
        niccp++;
        ii_data[niccp - 1] = static_cast<short>(b_re_tmp + 1);
        if (niccp >= varargin_1_size) {
          exitg1 = true;
        } else {
          b_re_tmp++;
        }
      } else {
        b_re_tmp++;
      }
    }
    if (varargin_1_size == 1) {
      if (niccp == 0) {
        *varargout_1_size = 0;
      }
    } else if (1 > niccp) {
      *varargout_1_size = 0;
    } else {
      *varargout_1_size = niccp;
    }
    for (i = 0; i < *varargout_1_size; i++) {
      varargout_1_data[i] = ii_data[i];
    }
    std::copy(&newFilterStates[0], &newFilterStates[12],
              &this->pFilterStates[0]);
  }
}

} // namespace comm
} // namespace coder

// End of code generation (PreambleDetector.cpp)
