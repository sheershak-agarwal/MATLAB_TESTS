//
// AsyncBuffer.cpp
//
// Code generation for function 'AsyncBuffer'
//

// Include files
#include "AsyncBuffer.h"
#include "AsyncBuffercgHelper.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <algorithm>
#include <cstring>
#include <string.h>

// Function Definitions
namespace coder {
namespace dsp {
void AsyncBuffer::read(double out_data[], int *out_size)
{
  static int readIdx_data[13440];
  static int y_data[11201];
  array<double, 1U> out;
  int b_y_data[11199];
  int b_wPtr;
  int c;
  int n;
  int n_tmp;
  int qY;
  int rPtr;
  int wPtr;
  int yk;
  wPtr = this->pBuffer.WritePointer;
  rPtr = this->pBuffer.ReadPointer;
  b_wPtr = this->pBuffer.WritePointer;
  qY = 0;
  if (rPtr > 2147483646) {
    rPtr = MAX_int32_T;
  } else {
    rPtr++;
  }
  if (rPtr > 11201) {
    rPtr = 1;
  }
  c = rPtr + 2239;
  if (rPtr + 2239 > 11201) {
    int c_tmp_tmp;
    int k;
    c_tmp_tmp = rPtr - 8962;
    c = rPtr - 8962;
    n_tmp = 11202 - rPtr;
    y_data[0] = rPtr;
    yk = rPtr;
    for (k = 2; k <= n_tmp; k++) {
      yk++;
      y_data[k - 1] = yk;
    }
    b_y_data[0] = 1;
    yk = 1;
    for (k = 2; k <= c_tmp_tmp; k++) {
      yk++;
      b_y_data[k - 1] = yk;
    }
    n = 2240;
    if (0 <= n_tmp - 1) {
      std::copy(&y_data[0], &y_data[n_tmp], &readIdx_data[0]);
    }
    for (n_tmp = 0; n_tmp < c_tmp_tmp; n_tmp++) {
      readIdx_data[(n_tmp - rPtr) + 11202] = b_y_data[n_tmp];
    }
    if (rPtr <= b_wPtr) {
      if (b_wPtr < -2147472446) {
        qY = MAX_int32_T;
      } else {
        qY = 11201 - b_wPtr;
      }
      if (qY > 2147483646) {
        qY = MAX_int32_T;
      } else {
        qY++;
      }
      if ((qY < 0) && (rPtr - 8962 < MIN_int32_T - qY)) {
        qY = MIN_int32_T;
      } else if ((qY > 0) && (rPtr - 8962 > MAX_int32_T - qY)) {
        qY = MAX_int32_T;
      } else {
        qY = (qY + rPtr) - 8962;
      }
    } else if (b_wPtr <= rPtr - 8962) {
      if ((rPtr - 8962 >= 0) && (b_wPtr < rPtr + 2147474687)) {
        qY = MAX_int32_T;
      } else if ((rPtr - 8962 < 0) && (b_wPtr > rPtr + 2147474686)) {
        qY = MIN_int32_T;
      } else {
        qY = (rPtr - b_wPtr) - 8962;
      }
      if (qY > 2147483646) {
        qY = MAX_int32_T;
      } else {
        qY++;
      }
    }
  } else {
    if (rPtr + 2239 < rPtr) {
      n = 0;
    } else {
      n = 2240;
    }
    if (n > 0) {
      y_data[0] = rPtr;
      yk = rPtr;
      for (int k{2}; k <= n; k++) {
        yk++;
        y_data[k - 1] = yk;
      }
    }
    if (0 <= n - 1) {
      std::copy(&y_data[0], &y_data[n], &readIdx_data[0]);
    }
    if ((rPtr <= b_wPtr) && (b_wPtr <= rPtr + 2239)) {
      if ((rPtr + 2239 >= 0) && (b_wPtr < rPtr - 2147481408)) {
        qY = MAX_int32_T;
      } else if ((rPtr + 2239 < 0) && (b_wPtr > rPtr - 2147481409)) {
        qY = MIN_int32_T;
      } else {
        qY = (rPtr - b_wPtr) + 2239;
      }
      if (qY > 2147483646) {
        qY = MAX_int32_T;
      } else {
        qY++;
      }
    }
  }
  out.set_size(n);
  for (n_tmp = 0; n_tmp < n; n_tmp++) {
    out[n_tmp] = this->pBuffer.Cache[readIdx_data[n_tmp] - 1];
  }
  if (qY != 0) {
    if (qY < -2147481407) {
      yk = MAX_int32_T;
    } else {
      yk = 2240 - qY;
    }
    if (yk > 2147483646) {
      yk = MAX_int32_T;
    } else {
      yk++;
    }
    if (yk > 2240) {
      yk = 1;
    }
    for (n_tmp = 0; n_tmp < qY; n_tmp++) {
      out[(yk + n_tmp) - 1] = 0.0;
    }
  }
  *out_size = out.size(0);
  yk = out.size(0);
  for (n_tmp = 0; n_tmp < yk; n_tmp++) {
    out_data[n_tmp] = out[n_tmp];
  }
  yk = this->pBuffer.CumulativeUnderrun;
  if ((yk < 0) && (qY < MIN_int32_T - yk)) {
    yk = MIN_int32_T;
  } else if ((yk > 0) && (qY > MAX_int32_T - yk)) {
    yk = MAX_int32_T;
  } else {
    yk += qY;
  }
  this->pBuffer.CumulativeUnderrun = yk;
  if (wPtr < -2147483647) {
    yk = MIN_int32_T;
  } else {
    yk = wPtr - 1;
  }
  if (qY != 0) {
    this->pBuffer.ReadPointer = yk;
  } else {
    this->pBuffer.ReadPointer = c;
  }
}

void AsyncBuffer::write(const double in[11200])
{
  static int y_data[11201];
  static short tmp_data[22400];
  array<int, 2U> bc;
  int b_y_data[11199];
  int b_qY;
  int c;
  int k;
  int n;
  int qY;
  int rPtr;
  int wPtr;
  int yk;
  if (this->pBuffer.isInitialized != 1) {
    this->pBuffer.isSetupComplete = false;
    this->pBuffer.isInitialized = 1;
    this->pBuffer.NumChannels = 1;
    this->pBuffer.AsyncBuffercgHelper_isInitialized = true;
    this->pBuffer.isSetupComplete = true;
    this->pBuffer.ReadPointer = 1;
    this->pBuffer.WritePointer = 2;
    this->pBuffer.CumulativeOverrun = 0;
    this->pBuffer.CumulativeUnderrun = 0;
    std::memset(&this->pBuffer.Cache[0], 0, 11201U * sizeof(double));
  }
  wPtr = this->pBuffer.WritePointer;
  rPtr = this->pBuffer.ReadPointer;
  qY = 0;
  if (wPtr > 2147472447) {
    b_qY = MAX_int32_T;
  } else {
    b_qY = wPtr + 11200;
  }
  c = b_qY - 1;
  if (b_qY - 1 > 11201) {
    int n_tmp;
    n = b_qY - 11202;
    c = b_qY - 11202;
    n_tmp = 11202 - wPtr;
    y_data[0] = wPtr;
    yk = wPtr;
    for (k = 2; k <= n_tmp; k++) {
      yk++;
      y_data[k - 1] = yk;
    }
    b_y_data[0] = 1;
    yk = 1;
    for (k = 2; k <= n; k++) {
      yk++;
      b_y_data[k - 1] = yk;
    }
    bc.set_size(1, b_qY - wPtr);
    for (k = 0; k < n_tmp; k++) {
      bc[k] = y_data[k];
    }
    for (k = 0; k < n; k++) {
      bc[(k - wPtr) + 11202] = b_y_data[k];
    }
    if (wPtr <= rPtr) {
      if (rPtr < -2147472446) {
        qY = MAX_int32_T;
      } else {
        qY = 11201 - rPtr;
      }
      if (qY > 2147483646) {
        qY = MAX_int32_T;
      } else {
        qY++;
      }
      if ((qY < 0) && (b_qY - 11202 < MIN_int32_T - qY)) {
        qY = MIN_int32_T;
      } else if ((qY > 0) && (b_qY - 11202 > MAX_int32_T - qY)) {
        qY = MAX_int32_T;
      } else {
        qY = (qY + b_qY) - 11202;
      }
    } else if (rPtr <= b_qY - 11202) {
      if (rPtr < b_qY + 2147472447) {
        b_qY = MAX_int32_T;
      } else {
        b_qY = (b_qY - rPtr) - 11202;
      }
      if (b_qY > 2147483646) {
        qY = MAX_int32_T;
      } else {
        qY = b_qY + 1;
      }
    }
  } else {
    if (b_qY - 1 < wPtr) {
      n = 0;
    } else {
      n = b_qY - wPtr;
    }
    if (n > 0) {
      y_data[0] = wPtr;
      yk = wPtr;
      for (k = 2; k <= n; k++) {
        yk++;
        y_data[k - 1] = yk;
      }
    }
    bc.set_size(1, n);
    for (k = 0; k < n; k++) {
      bc[k] = y_data[k];
    }
    if ((wPtr <= rPtr) && (rPtr <= b_qY - 1)) {
      if ((b_qY - 1 >= 0) && (rPtr < b_qY + MIN_int32_T)) {
        b_qY = MAX_int32_T;
      } else if ((b_qY - 1 < 0) && (rPtr > b_qY + MAX_int32_T)) {
        b_qY = MIN_int32_T;
      } else {
        b_qY = (b_qY - rPtr) - 1;
      }
      if (b_qY > 2147483646) {
        qY = MAX_int32_T;
      } else {
        qY = b_qY + 1;
      }
    }
  }
  n = bc.size(1);
  yk = bc.size(1);
  for (k = 0; k < yk; k++) {
    tmp_data[k] = static_cast<short>(static_cast<short>(bc[k]) - 1);
  }
  for (k = 0; k < n; k++) {
    this->pBuffer.Cache[tmp_data[k]] = in[k];
  }
  if (c + 1 > 11201) {
    wPtr = 1;
  } else {
    wPtr = c + 1;
  }
  if (qY != 0) {
    rPtr = wPtr;
  }
  n = this->pBuffer.CumulativeOverrun;
  if ((n < 0) && (qY < MIN_int32_T - n)) {
    b_qY = MIN_int32_T;
  } else if ((n > 0) && (qY > MAX_int32_T - n)) {
    b_qY = MAX_int32_T;
  } else {
    b_qY = n + qY;
  }
  this->pBuffer.CumulativeOverrun = b_qY;
  this->pBuffer.WritePointer = wPtr;
  this->pBuffer.ReadPointer = rPtr;
}

} // namespace dsp
} // namespace coder

// End of code generation (AsyncBuffer.cpp)
