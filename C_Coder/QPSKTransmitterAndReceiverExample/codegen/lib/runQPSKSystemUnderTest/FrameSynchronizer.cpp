//
// FrameSynchronizer.cpp
//
// Code generation for function 'FrameSynchronizer'
//

// Include files
#include "FrameSynchronizer.h"
#include "AGC.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <cstring>
#include <string.h>

// Function Definitions
namespace coder {
namespace comm {
namespace internal {
namespace examples {
FrameSynchronizer::FrameSynchronizer()
{
  this->matlabCodegenIsDeleted = true;
}

FrameSynchronizer::~FrameSynchronizer()
{
  this->matlabCodegenDestructor();
}

void FrameSynchronizer::matlabCodegenDestructor()
{
  if (!this->matlabCodegenIsDeleted) {
    this->matlabCodegenIsDeleted = true;
    if (this->isInitialized == 1) {
      this->isInitialized = 2;
    }
  }
}

void FrameSynchronizer::step(const creal_T varargin_1_data[],
                             int varargin_1_size,
                             const double varargin_2_data[],
                             int varargin_2_size,
                             const double varargin_3_data[],
                             int varargin_3_size, creal_T varargout_1[1133],
                             boolean_T *varargout_2)
{
  double circularIdx_data[1247];
  double linearIdx_data[1247];
  double circularIdx[1133];
  double bestIdx_data;
  double d;
  double nValid;
  double oldNBuffer;
  double r;
  int b_i;
  int bestIdx_size;
  int i;
  int k;
  short tmp_data[1247];
  short inSize[8];
  boolean_T exitg1;
  if (this->isInitialized != 1) {
    this->isSetupComplete = false;
    this->isInitialized = 1;
    this->inputVarSize[0].f1[0] = static_cast<unsigned int>(varargin_1_size);
    this->inputVarSize[0].f1[1] = 1U;
    this->inputVarSize[1].f1[0] = static_cast<unsigned int>(varargin_2_size);
    this->inputVarSize[1].f1[1] = 1U;
    this->inputVarSize[2].f1[0] = static_cast<unsigned int>(varargin_3_size);
    this->inputVarSize[2].f1[1] = 1U;
    for (i = 0; i < 6; i++) {
      this->inputVarSize[0].f1[i + 2] = 1U;
      this->inputVarSize[1].f1[i + 2] = 1U;
      this->inputVarSize[2].f1[i + 2] = 1U;
    }
    std::memset(&this->pBuffer[0], 0, 5665U * sizeof(creal_T));
    this->pPrbLenOffset = 12.0;
    this->isSetupComplete = true;
    this->pNBuffer = 0.0;
    this->pBufferStartIdx = 0.0;
    this->pBufferEndIdx = 0.0;
    for (b_i = 0; b_i < 5; b_i++) {
      this->pPrbIdxBuffer[b_i] = 0.0;
    }
    this->pNPrbIdxBuffer = 0.0;
    this->pPrbIdxBufferStartIdx = 1.0;
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
  inSize[0] = static_cast<short>(varargin_2_size);
  inSize[1] = 1;
  for (i = 0; i < 6; i++) {
    inSize[i + 2] = 1;
  }
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 8)) {
    if (this->inputVarSize[1].f1[k] != static_cast<unsigned int>(inSize[k])) {
      for (i = 0; i < 8; i++) {
        this->inputVarSize[1].f1[i] = static_cast<unsigned int>(inSize[i]);
      }
      exitg1 = true;
    } else {
      k++;
    }
  }
  inSize[0] = static_cast<short>(varargin_3_size);
  inSize[1] = 1;
  for (i = 0; i < 6; i++) {
    inSize[i + 2] = 1;
  }
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 8)) {
    if (this->inputVarSize[2].f1[k] != static_cast<unsigned int>(inSize[k])) {
      for (i = 0; i < 8; i++) {
        this->inputVarSize[2].f1[i] = static_cast<unsigned int>(inSize[i]);
      }
      exitg1 = true;
    } else {
      k++;
    }
  }
  if (varargin_2_size != 0) {
    for (i = 0; i < varargin_2_size; i++) {
      linearIdx_data[i] =
          varargin_3_data[static_cast<int>(varargin_2_data[i]) - 1];
    }
    if (varargin_2_size <= 2) {
      if (varargin_2_size == 1) {
        b_i = 1;
      } else {
        d = varargin_3_data[static_cast<int>(varargin_2_data[0]) - 1];
        nValid = varargin_3_data[static_cast<int>(varargin_2_data[1]) - 1];
        if ((d < nValid) || (std::isnan(d) && (!std::isnan(nValid)))) {
          b_i = 2;
        } else {
          b_i = 1;
        }
      }
    } else {
      if (!std::isnan(linearIdx_data[0])) {
        b_i = 1;
      } else {
        b_i = 0;
        k = 2;
        exitg1 = false;
        while ((!exitg1) && (k <= varargin_2_size)) {
          if (!std::isnan(linearIdx_data[k - 1])) {
            b_i = k;
            exitg1 = true;
          } else {
            k++;
          }
        }
      }
      if (b_i == 0) {
        b_i = 1;
      } else {
        nValid = linearIdx_data[b_i - 1];
        i = b_i + 1;
        for (k = i; k <= varargin_2_size; k++) {
          d = linearIdx_data[k - 1];
          if (nValid < d) {
            nValid = d;
            b_i = k;
          }
        }
      }
    }
    bestIdx_size = 1;
    bestIdx_data = varargin_2_data[b_i - 1];
  } else {
    bestIdx_size = 0;
  }
  if (varargin_1_size != 0) {
    double linIdx;
    int circularIdx_size_idx_1_tmp;
    b_i = varargin_1_size - 1;
    for (i = 0; i <= b_i; i++) {
      linearIdx_data[i] = static_cast<double>(i) + 1.0;
    }
    nValid = this->pBufferStartIdx + this->pNBuffer;
    b_i = varargin_1_size - 1;
    for (i = 0; i <= b_i; i++) {
      linearIdx_data[i] += nValid;
    }
    for (i = 0; i <= b_i; i++) {
      linearIdx_data[i]--;
    }
    circularIdx_size_idx_1_tmp = static_cast<short>(varargin_1_size);
    for (k = 0; k < circularIdx_size_idx_1_tmp; k++) {
      d = linearIdx_data[k];
      if (std::isnan(d) || std::isinf(d)) {
        r = rtNaN;
      } else if (d == 0.0) {
        r = 0.0;
      } else {
        r = std::fmod(d, 5665.0);
        if (r == 0.0) {
          r = 0.0;
        } else if (d < 0.0) {
          r += 5665.0;
        }
      }
      circularIdx_data[k] = r;
    }
    b_i = static_cast<short>(varargin_1_size) - 1;
    for (i = 0; i <= b_i; i++) {
      circularIdx_data[i]++;
    }
    for (i = 0; i < circularIdx_size_idx_1_tmp; i++) {
      tmp_data[i] =
          static_cast<short>(static_cast<short>(circularIdx_data[i]) - 1);
    }
    for (i = 0; i < varargin_1_size; i++) {
      this->pBuffer[tmp_data[i]] = varargin_1_data[i];
    }
    oldNBuffer = this->pNBuffer;
    this->pNBuffer += static_cast<double>(varargin_1_size);
    d = circularIdx_data[static_cast<short>(varargin_1_size) - 1];
    this->pBufferEndIdx = d;
    if (this->pNBuffer > 5665.0) {
      this->pNBuffer = 5665.0;
      this->pBufferStartIdx = d;
      nValid = this->pNPrbIdxBuffer;
      i = static_cast<int>(((-1.0 - nValid) + 1.0) / -1.0);
      for (k = 0; k < i; k++) {
        linIdx = (this->pPrbIdxBufferStartIdx - 1.0) +
                 (nValid + -static_cast<double>(k));
        if (std::isnan(linIdx - 1.0) || std::isinf(linIdx - 1.0)) {
          r = rtNaN;
        } else if (linIdx - 1.0 == 0.0) {
          r = 0.0;
        } else {
          r = std::fmod(linIdx - 1.0, 5.0);
          if (r == 0.0) {
            r = 0.0;
          } else if (linIdx - 1.0 < 0.0) {
            r += 5.0;
          }
        }
        if (this->pPrbIdxBuffer[static_cast<int>(r + 1.0) - 1] <= d) {
          this->pPrbIdxBuffer[static_cast<int>(r + 1.0) - 1] = 0.0;
          this->pNPrbIdxBuffer--;
        }
      }
    }
    if (bestIdx_size != 0) {
      oldNBuffer = (this->pBufferStartIdx + oldNBuffer) +
                   (bestIdx_data - this->pPrbLenOffset);
      if (oldNBuffer > 0.0) {
        linIdx = this->pPrbIdxBufferStartIdx + this->pNPrbIdxBuffer;
        if (std::isnan(linIdx - 1.0) || std::isinf(linIdx - 1.0)) {
          r = rtNaN;
        } else if (linIdx - 1.0 == 0.0) {
          r = 0.0;
        } else {
          r = std::fmod(linIdx - 1.0, 5.0);
          if (r == 0.0) {
            r = 0.0;
          } else if (linIdx - 1.0 < 0.0) {
            r += 5.0;
          }
        }
        if (std::isinf(oldNBuffer - 1.0)) {
          nValid = rtNaN;
        } else if (oldNBuffer - 1.0 == 0.0) {
          nValid = 0.0;
        } else {
          nValid = std::fmod(oldNBuffer - 1.0, 5665.0);
          if (nValid == 0.0) {
            nValid = 0.0;
          } else if (oldNBuffer - 1.0 < 0.0) {
            nValid += 5665.0;
          }
        }
        this->pPrbIdxBuffer[static_cast<int>(r + 1.0) - 1] = nValid + 1.0;
        this->pNPrbIdxBuffer++;
        if (this->pNPrbIdxBuffer > 5.0) {
          this->pNPrbIdxBuffer = 5.0;
          if (std::isnan(r + 1.0)) {
            nValid = rtNaN;
          } else if (r + 1.0 == 0.0) {
            nValid = 0.0;
          } else {
            nValid = std::fmod(r + 1.0, 5.0);
            if (nValid == 0.0) {
              nValid = 0.0;
            } else if (r + 1.0 < 0.0) {
              nValid += 5.0;
            }
          }
          this->pPrbIdxBufferStartIdx = nValid + 1.0;
        }
      }
    }
  }
  std::memset(&varargout_1[0], 0, 1133U * sizeof(creal_T));
  *varargout_2 = false;
  if (this->pNPrbIdxBuffer > 0.0) {
    b_i = static_cast<int>(this->pPrbIdxBufferStartIdx) - 1;
    oldNBuffer = this->pPrbIdxBuffer[b_i];
    nValid = (this->pBufferEndIdx - oldNBuffer) + 1.0;
    if (nValid < 1.0) {
      nValid = this->pNBuffer - ((oldNBuffer - this->pBufferStartIdx) - 1.0);
    }
    if (nValid >= 1133.0) {
      bestIdx_data = this->pNBuffer - nValid;
      for (k = 0; k < 1133; k++) {
        d = (oldNBuffer + static_cast<double>(k)) - 1.0;
        if (std::isnan(d) || std::isinf(d)) {
          r = rtNaN;
        } else if (d == 0.0) {
          r = 0.0;
        } else {
          r = std::fmod(d, 5665.0);
          if (r == 0.0) {
            r = 0.0;
          } else if (d < 0.0) {
            r += 5665.0;
          }
        }
        circularIdx[k] = r + 1.0;
        varargout_1[k] = this->pBuffer[static_cast<int>(circularIdx[k]) - 1];
      }
      *varargout_2 = true;
      this->pPrbIdxBuffer[b_i] = 0.0;
      this->pNPrbIdxBuffer--;
      nValid = this->pPrbIdxBufferStartIdx;
      if (std::isnan(nValid) || std::isinf(nValid)) {
        r = rtNaN;
      } else if (nValid == 0.0) {
        r = 0.0;
      } else {
        r = std::fmod(nValid, 5.0);
        if (r == 0.0) {
          r = 0.0;
        } else if (nValid < 0.0) {
          r += 5.0;
        }
      }
      this->pPrbIdxBufferStartIdx = r + 1.0;
      this->pBufferStartIdx = static_cast<short>(circularIdx[1132]);
      this->pNBuffer = (this->pNBuffer - 1133.0) - bestIdx_data;
    }
  }
}

} // namespace examples
} // namespace internal
} // namespace comm
} // namespace coder

// End of code generation (FrameSynchronizer.cpp)
