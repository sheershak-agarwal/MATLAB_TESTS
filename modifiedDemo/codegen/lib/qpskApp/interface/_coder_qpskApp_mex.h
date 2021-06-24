//
// _coder_qpskApp_mex.h
//
// Code generation for function 'qpskApp'
//

#ifndef _CODER_QPSKAPP_MEX_H
#define _CODER_QPSKAPP_MEX_H

// Include files
#include "emlrt.h"
#include "mex.h"
#include "tmwtypes.h"

// Function Declarations
MEXFUNCTION_LINKAGE void mexFunction(int32_T nlhs, mxArray *plhs[],
                                     int32_T nrhs, const mxArray *prhs[]);

emlrtCTX mexFunctionCreateRootTLS();

void unsafe_qpskApp_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs);

#endif
// End of code generation (_coder_qpskApp_mex.h)
