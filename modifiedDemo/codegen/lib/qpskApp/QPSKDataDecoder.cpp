//
// QPSKDataDecoder.cpp
//
// Code generation for function 'QPSKDataDecoder'
//

// Include files
#include "QPSKDataDecoder.h"
#include "Descrambler.h"
#include "QPSKDemodulator.h"
#include "qpskApp_data.h"
#include "qpskApp_rtwutil.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <cstring>
#include <stdio.h>
#include <string.h>

// Function Definitions
void QPSKDataDecoder::step(const creal_T varargin_1[1133], boolean_T varargin_2)
{
  static const creal_T dcv[13]{{
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
                               }};
  static const signed char iv[5]{1, 1, 1, 0, 1};
  coder::commcodegen::Descrambler *obj;
  comm_Descrambler_6 *b_obj;
  creal_T phShiftedData[1133];
  creal_T x[13];
  double b_d[320];
  int i;
  signed char demodOut[2266];
  signed char b[2240];
  signed char deScrData[2240];
  char b_varargin_1[321];
  if (this->isInitialized != 1) {
    this->isSetupComplete = false;
    this->isInitialized = 1;
    this->pQPSKDemodulator.isInitialized = 0;
    // System object Constructor function: comm.QPSKDemodulator
    this->pQPSKDemodulator.matlabCodegenIsDeleted = false;
    obj = &this->pDescrambler;
    this->pDescrambler.isInitialized = 0;
    // System object Constructor function: comm.Descrambler
    for (i = 0; i < 5; i++) {
      obj->cSFunObject.P0_Polynomial[i] = static_cast<unsigned char>(iv[i]);
    }
    obj->cSFunObject.P1_IniState[0] = 0;
    obj->cSFunObject.P1_IniState[1] = 0;
    obj->cSFunObject.P1_IniState[2] = 0;
    obj->cSFunObject.P1_IniState[3] = 0;
    this->pDescrambler.matlabCodegenIsDeleted = false;
    //              obj.pErrorRateCalc = comm.ErrorRate( ...
    //                  'Samples', 'Custom', ...
    //                  'CustomSamples', obj.BerMask);
    //  Since we only calculate BER on message part, 000s are not
    //  necessary here, they are just place-holder.
    //              msgSet = zeros(obj.NumberOfMessage * obj.pMessageLength, 1);
    //              for msgCnt = 0 : obj.NumberOfMessage - 1
    //                  msgSet(msgCnt * obj.pMessageLength + (1 :
    //                  obj.pMessageLength)) = ...
    //                      sprintf('%s %03d\n', obj.pMessage, mod(msgCnt,
    //                      100));
    //              end
    //              obj.pTargetBits = reshape(de2bi(msgSet, 7, 'left-msb')', [],
    //              1);
    this->isSetupComplete = true;
    if (this->pDescrambler.isInitialized == 1) {
      // System object Initialization function: comm.Descrambler
      this->pDescrambler.cSFunObject.W0_shiftReg[0] =
          this->pDescrambler.cSFunObject.P1_IniState[0];
      this->pDescrambler.cSFunObject.W0_shiftReg[1] =
          this->pDescrambler.cSFunObject.P1_IniState[1];
      this->pDescrambler.cSFunObject.W0_shiftReg[2] =
          this->pDescrambler.cSFunObject.P1_IniState[2];
      this->pDescrambler.cSFunObject.W0_shiftReg[3] =
          this->pDescrambler.cSFunObject.P1_IniState[3];
    }
    //             reset(obj.pErrorRateCalc);
  }
  if (varargin_2) {
    double d;
    double d1;
    double pp;
    double r;
    double x_re;
    int iIdx;
    int k;
    //  Phase ambiguity estimation
    for (i = 0; i < 13; i++) {
      d = dcv[i].re;
      d1 = dcv[i].im;
      pp = varargin_1[i].re;
      r = varargin_1[i].im;
      x[i].re = d * pp - d1 * r;
      x[i].im = d * r + d1 * pp;
    }
    x_re = x[0].re;
    pp = x[0].im;
    for (k = 0; k < 12; k++) {
      x_re += x[k + 1].re;
      pp += x[k + 1].im;
    }
    if (pp == 0.0) {
      r = x_re / 13.0;
      pp = 0.0;
    } else if (x_re == 0.0) {
      r = 0.0;
      pp /= 13.0;
    } else {
      r = x_re / 13.0;
      pp /= 13.0;
    }
    //  Compensating for the phase ambiguity
    pp = std::round(rt_atan2d_snf(pp, r) * 2.0 / 3.1415926535897931) / 2.0 *
         3.1415926535897931;
    x_re = pp * 0.0;
    if (-pp == 0.0) {
      x_re = std::exp(x_re);
      pp = 0.0;
    } else {
      r = std::exp(x_re / 2.0);
      x_re = r * (r * std::cos(-pp));
      pp = r * (r * std::sin(-pp));
    }
    for (i = 0; i < 1133; i++) {
      d = varargin_1[i].re;
      d1 = varargin_1[i].im;
      phShiftedData[i].re = d * x_re - d1 * pp;
      phShiftedData[i].im = d * pp + d1 * x_re;
    }
    //  Demodulating the phase recovered data
    if (this->pQPSKDemodulator.isInitialized != 1) {
      this->pQPSKDemodulator.isSetupComplete = false;
      this->pQPSKDemodulator.isInitialized = 1;
      this->pQPSKDemodulator.isSetupComplete = true;
    }
    // System object Outputs function: comm.QPSKDemodulator
    for (iIdx = 0; iIdx < 1133; iIdx++) {
      d = phShiftedData[iIdx].re;
      if (d > 0.0) {
        if (phShiftedData[iIdx].im >= 0.0) {
          k = 0;
        } else {
          k = 3;
        }
      } else if (d < 0.0) {
        if (phShiftedData[iIdx].im <= 0.0) {
          k = 2;
        } else {
          k = 1;
        }
      } else {
        d = phShiftedData[iIdx].im;
        if (d < 0.0) {
          k = 3;
        } else {
          k = (d > 0.0);
        }
      }
      k ^= k >> 1;
      i = iIdx << 1;
      demodOut[i + 1] = static_cast<signed char>(k % 2);
      k >>= 1;
      demodOut[i] = static_cast<signed char>(k % 2);
    }
    //  Performs descrambling on only payload part
    if (this->pDescrambler.isInitialized != 1) {
      this->pDescrambler.isSetupComplete = false;
      this->pDescrambler.isInitialized = 1;
      this->pDescrambler.isSetupComplete = true;
      // System object Initialization function: comm.Descrambler
      this->pDescrambler.cSFunObject.W0_shiftReg[0] =
          this->pDescrambler.cSFunObject.P1_IniState[0];
      this->pDescrambler.cSFunObject.W0_shiftReg[1] =
          this->pDescrambler.cSFunObject.P1_IniState[1];
      this->pDescrambler.cSFunObject.W0_shiftReg[2] =
          this->pDescrambler.cSFunObject.P1_IniState[2];
      this->pDescrambler.cSFunObject.W0_shiftReg[3] =
          this->pDescrambler.cSFunObject.P1_IniState[3];
    }
    b_obj = &this->pDescrambler.cSFunObject;
    // System object Outputs function: comm.Descrambler
    for (iIdx = 0; iIdx < 2240; iIdx++) {
      k = demodOut[iIdx + 26];
      i = k - static_cast<unsigned char>(b_obj->W0_shiftReg[0] *
                                         b_obj->P0_Polynomial[1]);
      i -= static_cast<unsigned char>(b_obj->W0_shiftReg[1] *
                                      b_obj->P0_Polynomial[2]);
      i -= static_cast<unsigned char>(b_obj->W0_shiftReg[2] *
                                      b_obj->P0_Polynomial[3]);
      for (i -= static_cast<unsigned char>(b_obj->W0_shiftReg[3] *
                                           b_obj->P0_Polynomial[4]);
           i < 0; i += 2) {
      }
      i %= 2;
      deScrData[iIdx] = static_cast<signed char>(i);
      b_obj->W0_shiftReg[3] = b_obj->W0_shiftReg[2];
      b_obj->W0_shiftReg[2] = b_obj->W0_shiftReg[1];
      b_obj->W0_shiftReg[1] = b_obj->W0_shiftReg[0];
      b_obj->W0_shiftReg[0U] = k;
    }
    //  Recovering the message from the data
    for (k = 0; k < 7; k++) {
      for (i = 0; i < 320; i++) {
        b[i + 320 * k] = deScrData[k + 7 * i];
      }
    }
    pp = 1.0;
    std::memset(&b_d[0], 0, 320U * sizeof(double));
    for (iIdx = 0; iIdx < 7; iIdx++) {
      for (i = 0; i < 320; i++) {
        r = b_d[i];
        if (b[i + 320 * (6 - iIdx)] != 0) {
          r += pp;
        }
        b_d[i] = r;
      }
      pp *= 2.0;
    }
    for (k = 0; k < 320; k++) {
      signed char b_i;
      d = b_d[k];
      if (d < 128.0) {
        b_i = static_cast<signed char>(d);
      } else {
        b_i = MAX_int8_T;
      }
      b_varargin_1[k] = b_i;
    }
    b_varargin_1[320] = '\x00';
    printf("%s", &b_varargin_1[0]);
    fflush(stdout);
    //  Perform BER calculation only on message part
    //                 obj.pBER = obj.pErrorRateCalc(obj.pTargetBits,
    //                 deScrData);
  }
  //             BER = obj.pBER;
  //  dummy value
}

// End of code generation (QPSKDataDecoder.cpp)
