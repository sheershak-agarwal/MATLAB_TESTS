//
// QPSKTransmitter.cpp
//
// Code generation for function 'QPSKTransmitter'
//

// Include files
#include "QPSKTransmitter.h"
#include "AsyncBuffer.h"
#include "AsyncBuffercgHelper.h"
#include "FIRInterpolator.h"
#include "QPSKBitsGenerator.h"
#include "QPSKModulator.h"
#include "RaisedCosineTransmitFilter.h"
#include "Scrambler.h"
#include "rt_nonfinite.h"
#include <algorithm>
#include <cmath>
#include <string.h>

// Function Definitions
void QPSKTransmitter::stepImpl(creal_T transmittedSignal_data[],
                               int transmittedSignal_size[2])
{
  static const double dv[22]{-0.00045472051487622253, -0.0071456080909122616,
                             0.0021436824272736714,   0.0300115539818315,
                             -0.075028884954578726,   0.80373860039798006,
                             -0.075028884954578726,   0.0300115539818315,
                             0.0021436824272736714,   -0.0071456080909122616,
                             -0.00045472051487622253, 0.0035368955557498576,
                             0.0075790619051782785,   -0.010610686667249576,
                             -0.053053433336247971,   0.40916871463405252,
                             0.40916871463405252,     -0.053053433336247971,
                             -0.010610686667249576,   0.0075790619051782785,
                             0.0035368955557498576,   0.0};
  static double b_obj[11200];
  static const signed char a[13]{1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1};
  static const signed char iv[5]{1, 1, 1, 0, 1};
  QPSKBitsGenerator *obj;
  coder::comm::RaisedCosineTransmitFilter *d_obj;
  coder::dspcodegen::FIRInterpolator *e_obj;
  comm_QPSKModulator_0 *c_obj;
  dsp_FIRInterpolator_2 *f_obj;
  creal_T modulatedData_data[1133];
  double varargout_1_data[2266];
  double scrambledMsg_data[2240];
  double varargout_2_data[2240];
  double reshapes_f1[26];
  int scrambledMsg_size[2];
  int i;
  int ibtile;
  int j;
  int jtilecol;
  int k;
  int modulatedData_size_idx_0_tmp;
  signed char b[26];
  signed char b_b[26];
  obj = &this->pBitGenerator;
  if (this->pBitGenerator.isInitialized != 1) {
    this->pBitGenerator.isSetupComplete = false;
    this->pBitGenerator.isInitialized = 1;
    //  Generate unipolar Barker Code and duplicate it as header
    for (jtilecol = 0; jtilecol < 2; jtilecol++) {
      ibtile = jtilecol * 13;
      for (k = 0; k < 13; k++) {
        b_b[ibtile + k] = a[k];
      }
    }
    for (j = 0; j < 13; j++) {
      ibtile = j << 1;
      b[ibtile] = b_b[j];
      b[ibtile + 1] = b_b[j + 13];
    }
    for (j = 0; j < 26; j++) {
      this->pBitGenerator.pHeader[j] = b[j];
    }
    //  Initialize scrambler system object
    obj->pScrambler.isInitialized = 0;
    // System object Constructor function: comm.Scrambler
    for (i = 0; i < 5; i++) {
      this->pBitGenerator.pScrambler.cSFunObject.P0_Polynomial[i] =
          static_cast<unsigned char>(iv[i]);
    }
    this->pBitGenerator.pScrambler.cSFunObject.P1_IniState[0] = 0;
    this->pBitGenerator.pScrambler.cSFunObject.P1_IniState[1] = 0;
    this->pBitGenerator.pScrambler.cSFunObject.P1_IniState[2] = 0;
    this->pBitGenerator.pScrambler.cSFunObject.P1_IniState[3] = 0;
    obj->pScrambler.matlabCodegenIsDeleted = false;
    //  Initialize signal source
    this->pBitGenerator.pSigSrc.pBuffer.NumChannels = -1;
    this->pBitGenerator.pSigSrc.pBuffer.isInitialized = 0;
    this->pBitGenerator.pSigSrc.pBuffer.matlabCodegenIsDeleted = false;
    obj->pSigSrc.matlabCodegenIsDeleted = false;
    std::copy(&this->pBitGenerator.MessageBits[0],
              &this->pBitGenerator.MessageBits[11200], &b_obj[0]);
    this->pBitGenerator.pSigSrc.write(b_obj);
    //              % Initialize signal source
    //              obj.pSigSrc = dsp.SignalSource(obj.MessageBits, ...
    //                  'SamplesPerFrame', obj.MessageLength * 7 *
    //                  obj.NumberOfMessage, ... 'SignalEndAction', 'Cyclic
    //                  repetition');
    this->pBitGenerator.isSetupComplete = true;
    this->pBitGenerator.resetImpl();
  }
  //  Generate message binaries from signal source.
  ibtile = this->pBitGenerator.pSigSrc.pBuffer.WritePointer;
  k = this->pBitGenerator.pSigSrc.pBuffer.ReadPointer;
  if ((ibtile >= 0) && (k < ibtile - MAX_int32_T)) {
    jtilecol = MAX_int32_T;
  } else if ((ibtile < 0) && (k > ibtile - MIN_int32_T)) {
    jtilecol = MIN_int32_T;
  } else {
    jtilecol = ibtile - k;
  }
  if (jtilecol < -2147483647) {
    jtilecol = MIN_int32_T;
  } else {
    jtilecol--;
  }
  k = this->pBitGenerator.pSigSrc.pBuffer.ReadPointer;
  if (k < -2147472447) {
    ibtile = MAX_int32_T;
  } else {
    ibtile = 11200 - k;
  }
  k = this->pBitGenerator.pSigSrc.pBuffer.WritePointer;
  if ((ibtile < 0) && (k < MIN_int32_T - ibtile)) {
    ibtile = MIN_int32_T;
  } else if ((ibtile > 0) && (k > MAX_int32_T - ibtile)) {
    ibtile = MAX_int32_T;
  } else {
    ibtile += k;
  }
  if (this->pBitGenerator.pSigSrc.pBuffer.ReadPointer <
      this->pBitGenerator.pSigSrc.pBuffer.WritePointer) {
    ibtile = jtilecol;
  } else if (this->pBitGenerator.pSigSrc.pBuffer.ReadPointer ==
             this->pBitGenerator.pSigSrc.pBuffer.WritePointer) {
    ibtile = 11200;
  }
  if (ibtile >= 2240) {
    short input_sizes_idx_0;
    this->pBitGenerator.pSigSrc.read(varargout_2_data, &ibtile);
    //  Scramble the data
    obj->pScrambler.step(varargout_2_data, scrambledMsg_data,
                         scrambledMsg_size);
    //  Append the scrambled bit sequence to the header
    for (i = 0; i < 26; i++) {
      reshapes_f1[i] = this->pBitGenerator.pHeader[i];
    }
    if ((scrambledMsg_size[0] != 0) && (scrambledMsg_size[1] != 0)) {
      input_sizes_idx_0 = static_cast<short>(scrambledMsg_size[0]);
    } else {
      input_sizes_idx_0 = 0;
    }
    ibtile = input_sizes_idx_0 + 26;
    std::copy(&reshapes_f1[0], &reshapes_f1[26], &varargout_1_data[0]);
    jtilecol = input_sizes_idx_0;
    if (0 <= jtilecol - 1) {
      std::copy(&scrambledMsg_data[0], &scrambledMsg_data[jtilecol],
                &varargout_1_data[26]);
    }
  } else {
    short input_sizes_idx_0;
    std::copy(&this->pBitGenerator.MessageBits[0],
              &this->pBitGenerator.MessageBits[11200], &b_obj[0]);
    this->pBitGenerator.pSigSrc.write(b_obj);
    this->pBitGenerator.pSigSrc.read(varargout_2_data, &ibtile);
    //  Scramble the data
    obj->pScrambler.step(varargout_2_data, scrambledMsg_data,
                         scrambledMsg_size);
    //  Append the scrambled bit sequence to the header
    for (i = 0; i < 26; i++) {
      reshapes_f1[i] = this->pBitGenerator.pHeader[i];
    }
    if ((scrambledMsg_size[0] != 0) && (scrambledMsg_size[1] != 0)) {
      input_sizes_idx_0 = static_cast<short>(scrambledMsg_size[0]);
    } else {
      input_sizes_idx_0 = 0;
    }
    ibtile = input_sizes_idx_0 + 26;
    std::copy(&reshapes_f1[0], &reshapes_f1[26], &varargout_1_data[0]);
    jtilecol = input_sizes_idx_0;
    if (0 <= jtilecol - 1) {
      std::copy(&scrambledMsg_data[0], &scrambledMsg_data[jtilecol],
                &varargout_1_data[26]);
    }
  }
  //              % Generate message binaries from signal source.
  //              msgBin = obj.pSigSrc();
  //
  //              % Scramble the data
  //              scrambledMsg = obj.pScrambler(msgBin);
  //
  //              % Append the scrambled bit sequence to the header
  //              y = [obj.pHeader ; scrambledMsg];
  //  Generates the data to be transmitted
  if (this->pQPSKModulator.isInitialized != 1) {
    this->pQPSKModulator.isSetupComplete = false;
    this->pQPSKModulator.isInitialized = 1;
    this->pQPSKModulator.isSetupComplete = true;
  }
  c_obj = &this->pQPSKModulator.cSFunObject;
  // System object Outputs function: comm.QPSKModulator
  modulatedData_size_idx_0_tmp = ibtile >> 1;
  jtilecol = 0;
  k = 0;
  for (i = 0; i < modulatedData_size_idx_0_tmp; i++) {
    ibtile = (static_cast<int>(std::floor(varargout_1_data[jtilecol])) << 1) +
             static_cast<int>(std::floor(varargout_1_data[jtilecol + 1]));
    jtilecol += 2;
    ibtile ^= ibtile >> 1;
    j = ibtile << 1;
    modulatedData_data[k].re = c_obj->P0_modmap[j];
    modulatedData_data[k].im = c_obj->P0_modmap[j + 1];
    k++;
  }
  //  Modulates the bits into QPSK symbols
  d_obj = &this->pTransmitterFilter;
  if (this->pTransmitterFilter.isInitialized != 1) {
    this->pTransmitterFilter.isSetupComplete = false;
    this->pTransmitterFilter.isInitialized = 1;
    d_obj->_pobj0.isInitialized = 0;
    // System object Constructor function: dsp.FIRInterpolator
    this->pTransmitterFilter._pobj0.cSFunObject.P0_IC.re = 0.0;
    this->pTransmitterFilter._pobj0.cSFunObject.P0_IC.im = 0.0;
    for (i = 0; i < 22; i++) {
      this->pTransmitterFilter._pobj0.cSFunObject.P1_FILTER_COEFF[i] = dv[i];
    }
    d_obj->_pobj0.matlabCodegenIsDeleted = false;
    this->pTransmitterFilter.pFilter = &d_obj->_pobj0;
    this->pTransmitterFilter.isSetupComplete = true;
    e_obj = this->pTransmitterFilter.pFilter;
    if (e_obj->isInitialized == 1) {
      // System object Initialization function: dsp.FIRInterpolator
      for (i = 0; i < 10; i++) {
        e_obj->cSFunObject.W0_TapDelayBuff[i].re = 0.0;
        e_obj->cSFunObject.W0_TapDelayBuff[i].im = 0.0;
      }
      e_obj->cSFunObject.W1_PrevNumChan = -1;
    }
  }
  e_obj = this->pTransmitterFilter.pFilter;
  if (e_obj->isInitialized != 1) {
    e_obj->isSetupComplete = false;
    e_obj->isInitialized = 1;
    e_obj->isSetupComplete = true;
    // System object Initialization function: dsp.FIRInterpolator
    for (i = 0; i < 10; i++) {
      e_obj->cSFunObject.W0_TapDelayBuff[i].re = 0.0;
      e_obj->cSFunObject.W0_TapDelayBuff[i].im = 0.0;
    }
    e_obj->cSFunObject.W1_PrevNumChan = -1;
  }
  f_obj = &e_obj->cSFunObject;
  // System object Outputs function: dsp.FIRInterpolator
  if (e_obj->cSFunObject.W1_PrevNumChan == -1) {
    e_obj->cSFunObject.W1_PrevNumChan = 1;
  }
  transmittedSignal_size[0] = modulatedData_size_idx_0_tmp << 1;
  transmittedSignal_size[1] = 1;
  // Loop over each input channel
  for (int m{0}; m < 2; m++) {
    double accumulator_im;
    double accumulator_re;
    double product_im;
    double product_re;
    k = m * 11;
    // Consume delay line and beginning of input samples
    for (i = 0; i < 10; i++) {
      accumulator_re = 0.0;
      accumulator_im = 0.0;
      for (j = 0; j < i + 1; j++) {
        ibtile = k + j;
        jtilecol = i - j;
        product_re =
            f_obj->P1_FILTER_COEFF[ibtile] * modulatedData_data[jtilecol].re;
        product_im =
            f_obj->P1_FILTER_COEFF[ibtile] * modulatedData_data[jtilecol].im;
        accumulator_re += product_re;
        accumulator_im += product_im;
      }
      for (j = 0; j < 10 - i; j++) {
        ibtile = ((k + i) + j) + 1;
        product_re =
            f_obj->P1_FILTER_COEFF[ibtile] * f_obj->W0_TapDelayBuff[j].re;
        product_im =
            f_obj->P1_FILTER_COEFF[ibtile] * f_obj->W0_TapDelayBuff[j].im;
        accumulator_re += product_re;
        accumulator_im += product_im;
      }
      j = m + (i << 1);
      transmittedSignal_data[j].re = accumulator_re;
      transmittedSignal_data[j].im = accumulator_im;
    }
    ibtile = m + 20;
    // Consume remaining input samples
    while (i < modulatedData_size_idx_0_tmp) {
      accumulator_re = 0.0;
      accumulator_im = 0.0;
      for (j = 0; j < 11; j++) {
        product_re =
            f_obj->P1_FILTER_COEFF[k + j] * modulatedData_data[i - j].re;
        product_im =
            f_obj->P1_FILTER_COEFF[k + j] * modulatedData_data[i - j].im;
        accumulator_re += product_re;
        accumulator_im += product_im;
      }
      transmittedSignal_data[ibtile].re = accumulator_re;
      transmittedSignal_data[ibtile].im = accumulator_im;
      ibtile += 2;
      i++;
    }
  }
  // Update delay line for next frame
  for (i = 0; i < 10; i++) {
    f_obj->W0_TapDelayBuff[9 - i] =
        modulatedData_data[(modulatedData_size_idx_0_tmp + i) - 10];
  }
  //  Square root Raised Cosine Transmit Filter
}

// End of code generation (QPSKTransmitter.cpp)
