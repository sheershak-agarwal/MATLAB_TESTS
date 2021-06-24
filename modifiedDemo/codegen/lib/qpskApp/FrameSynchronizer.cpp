//
// FrameSynchronizer.cpp
//
// Code generation for function 'FrameSynchronizer'
//

// Include files
#include "FrameSynchronizer.h"
#include "AsyncBuffercgHelper.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <cstring>
#include <string.h>

// Function Definitions
void FrameSynchronizer::step(const creal_T varargin_1_data[],
                             int varargin_1_size, int varargin_2_size,
                             int varargin_3_size, creal_T varargout_1[1133],
                             boolean_T *varargout_2)
{
  double circularIdx[1133];
  double d;
  double linIdx;
  double linearIdx_data;
  double nInvalid;
  double r;
  int i;
  int k;
  signed char inSize[8];
  signed char bestIdx_size_idx_0;
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
    //  Only floating-point supported for now.
    //  Fixed buffer length
    std::memset(&this->pBuffer[0], 0, 5665U * sizeof(creal_T));
    this->pPrbLenOffset = 12.0;
    this->isSetupComplete = true;
    //  Initialize internal buffer and related properties
    this->pNBuffer = 0.0;
    this->pBufferStartIdx = 0.0;
    this->pBufferEndIdx = 0.0;
    for (i = 0; i < 5; i++) {
      this->pPrbIdxBuffer[i] = 0.0;
    }
    this->pNPrbIdxBuffer = 0.0;
    this->pPrbIdxBufferStartIdx = 1.0;
  }
  inSize[0] = static_cast<signed char>(varargin_1_size);
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
  inSize[0] = static_cast<signed char>(varargin_2_size);
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
  inSize[0] = static_cast<signed char>(varargin_3_size);
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
  bestIdx_size_idx_0 = static_cast<signed char>(varargin_2_size != 0);
  if (varargin_1_size != 0) {
    //  Process x
    linearIdx_data = ((this->pBufferStartIdx + this->pNBuffer) + 1.0) - 1.0;
    if (std::isnan(linearIdx_data) || std::isinf(linearIdx_data)) {
      r = rtNaN;
    } else if (linearIdx_data == 0.0) {
      r = 0.0;
    } else {
      r = std::fmod(linearIdx_data, 5665.0);
      if (r == 0.0) {
        r = 0.0;
      } else if (linearIdx_data < 0.0) {
        r += 5665.0;
      }
    }
    this->pBuffer[static_cast<short>(static_cast<short>(r + 1.0) - 1)] =
        varargin_1_data[0];
    linearIdx_data = this->pNBuffer;
    this->pNBuffer++;
    this->pBufferEndIdx = r + 1.0;
    if (this->pNBuffer > 5665.0) {
      //  Buffer overflow. Data at the beginning of the buffer
      //  overwritten with new data.
      this->pNBuffer = 5665.0;
      this->pBufferStartIdx = r + 1.0;
      d = this->pNPrbIdxBuffer;
      i = static_cast<int>(((-1.0 - d) + 1.0) / -1.0);
      for (k = 0; k < i; k++) {
        linIdx =
            (this->pPrbIdxBufferStartIdx - 1.0) + (d + -static_cast<double>(k));
        if (std::isnan(linIdx - 1.0) || std::isinf(linIdx - 1.0)) {
          nInvalid = rtNaN;
        } else if (linIdx - 1.0 == 0.0) {
          nInvalid = 0.0;
        } else {
          nInvalid = std::fmod(linIdx - 1.0, 5.0);
          if (nInvalid == 0.0) {
            nInvalid = 0.0;
          } else if (linIdx - 1.0 < 0.0) {
            nInvalid += 5.0;
          }
        }
        if (this->pPrbIdxBuffer[static_cast<int>(nInvalid + 1.0) - 1] <=
            r + 1.0) {
          this->pPrbIdxBuffer[static_cast<int>(nInvalid + 1.0) - 1] = 0.0;
          this->pNPrbIdxBuffer--;
        }
      }
    }
    //  Process preambleEndIdx
    if (bestIdx_size_idx_0 != 0) {
      linearIdx_data = (this->pBufferStartIdx + linearIdx_data) +
                       (1.0 - this->pPrbLenOffset);
      if (linearIdx_data > 0.0) {
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
        if (std::isinf(linearIdx_data - 1.0)) {
          nInvalid = rtNaN;
        } else if (linearIdx_data - 1.0 == 0.0) {
          nInvalid = 0.0;
        } else {
          nInvalid = std::fmod(linearIdx_data - 1.0, 5665.0);
          if (nInvalid == 0.0) {
            nInvalid = 0.0;
          } else if (linearIdx_data - 1.0 < 0.0) {
            nInvalid += 5665.0;
          }
        }
        this->pPrbIdxBuffer[static_cast<int>(r + 1.0) - 1] = nInvalid + 1.0;
        this->pNPrbIdxBuffer++;
        if (this->pNPrbIdxBuffer > 5.0) {
          //  Buffer overflow. Data at the beginning of the buffer
          //  overwritten with new data.
          this->pNPrbIdxBuffer = 5.0;
          if (std::isnan(r + 1.0)) {
            nInvalid = rtNaN;
          } else if (r + 1.0 == 0.0) {
            nInvalid = 0.0;
          } else {
            nInvalid = std::fmod(r + 1.0, 5.0);
            if (nInvalid == 0.0) {
              nInvalid = 0.0;
            } else if (r + 1.0 < 0.0) {
              nInvalid += 5.0;
            }
          }
          this->pPrbIdxBufferStartIdx = nInvalid + 1.0;
        }
      }
    }
  }
  std::memset(&varargout_1[0], 0, 1133U * sizeof(creal_T));
  *varargout_2 = false;
  if (this->pNPrbIdxBuffer > 0.0) {
    //  Buffer has a preamble
    i = static_cast<int>(this->pPrbIdxBufferStartIdx) - 1;
    linIdx = this->pPrbIdxBuffer[i];
    linearIdx_data = (this->pBufferEndIdx - linIdx) + 1.0;
    if (linearIdx_data < 1.0) {
      linearIdx_data =
          this->pNBuffer - ((linIdx - this->pBufferStartIdx) - 1.0);
    }
    if (linearIdx_data >= 1133.0) {
      //  Enough valid data in the buffer to output
      nInvalid = this->pNBuffer - linearIdx_data;
      for (k = 0; k < 1133; k++) {
        d = (linIdx + static_cast<double>(k)) - 1.0;
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
      //  Update buffer states
      this->pPrbIdxBuffer[i] = 0.0;
      this->pNPrbIdxBuffer--;
      linearIdx_data = this->pPrbIdxBufferStartIdx;
      if (std::isnan(linearIdx_data) || std::isinf(linearIdx_data)) {
        r = rtNaN;
      } else if (linearIdx_data == 0.0) {
        r = 0.0;
      } else {
        r = std::fmod(linearIdx_data, 5.0);
        if (r == 0.0) {
          r = 0.0;
        } else if (linearIdx_data < 0.0) {
          r += 5.0;
        }
      }
      this->pPrbIdxBufferStartIdx = r + 1.0;
      this->pBufferStartIdx = static_cast<short>(circularIdx[1132]);
      this->pNBuffer = (this->pNBuffer - 1133.0) - nInvalid;
    }
  }
}

// End of code generation (FrameSynchronizer.cpp)
