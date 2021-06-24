//
// Scrambler.cpp
//
// Code generation for function 'Scrambler'
//

// Include files
#include "Scrambler.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <string.h>

// Function Definitions
namespace coder {
namespace commcodegen {
void Scrambler::step(const double varargin_1_data[], double varargout_1_data[],
                     int varargout_1_size[2])
{
  comm_Scrambler_1 *obj;
  if (this->isInitialized != 1) {
    this->isSetupComplete = false;
    this->isInitialized = 1;
    this->isSetupComplete = true;
    // System object Initialization function: comm.Scrambler
    this->cSFunObject.W0_shiftReg[0] = this->cSFunObject.P1_IniState[0];
    this->cSFunObject.W0_shiftReg[1] = this->cSFunObject.P1_IniState[1];
    this->cSFunObject.W0_shiftReg[2] = this->cSFunObject.P1_IniState[2];
    this->cSFunObject.W0_shiftReg[3] = this->cSFunObject.P1_IniState[3];
  }
  obj = &this->cSFunObject;
  // System object Outputs function: comm.Scrambler
  varargout_1_size[0] = 2240;
  varargout_1_size[1] = 1;
  for (int j{0}; j < 2240; j++) {
    int tmp;
    tmp =
        static_cast<int>(std::floor(varargin_1_data[j])) +
        static_cast<unsigned char>(obj->W0_shiftReg[0] * obj->P0_Polynomial[1]);
    tmp +=
        static_cast<unsigned char>(obj->W0_shiftReg[1] * obj->P0_Polynomial[2]);
    tmp +=
        static_cast<unsigned char>(obj->W0_shiftReg[2] * obj->P0_Polynomial[3]);
    tmp +=
        static_cast<unsigned char>(obj->W0_shiftReg[3] * obj->P0_Polynomial[4]);
    tmp %= 2;
    varargout_1_data[j] = tmp;
    obj->W0_shiftReg[3] = obj->W0_shiftReg[2];
    obj->W0_shiftReg[2] = obj->W0_shiftReg[1];
    obj->W0_shiftReg[1] = obj->W0_shiftReg[0];
    obj->W0_shiftReg[0U] = tmp;
  }
}

} // namespace commcodegen
} // namespace coder

// End of code generation (Scrambler.cpp)
