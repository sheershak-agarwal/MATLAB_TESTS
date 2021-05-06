//
// _coder_runQPSKSystemUnderTest_api.h
//
// Code generation for function 'runQPSKSystemUnderTest'
//

#ifndef _CODER_RUNQPSKSYSTEMUNDERTEST_API_H
#define _CODER_RUNQPSKSYSTEMUNDERTEST_API_H

// Include files
#include "emlrt.h"
#include "tmwtypes.h"
#include <algorithm>
#include <cstring>

// Variable Declarations
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

// Function Declarations
void runQPSKSystemUnderTest(real_T BER[3]);

void runQPSKSystemUnderTest_api(const mxArray **plhs);

void runQPSKSystemUnderTest_atexit();

void runQPSKSystemUnderTest_initialize();

void runQPSKSystemUnderTest_terminate();

void runQPSKSystemUnderTest_xil_shutdown();

void runQPSKSystemUnderTest_xil_terminate();

#endif
// End of code generation (_coder_runQPSKSystemUnderTest_api.h)
