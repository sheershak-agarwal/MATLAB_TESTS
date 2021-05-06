//
// _coder_runQPSKSystemUnderTest_mex.cpp
//
// Code generation for function 'runQPSKSystemUnderTest'
//

// Include files
#include "_coder_runQPSKSystemUnderTest_mex.h"
#include "_coder_runQPSKSystemUnderTest_api.h"

// Function Definitions
void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs,
                 const mxArray *prhs[])
{
  (void)prhs;
  mexAtExit(&runQPSKSystemUnderTest_atexit);
  // Module initialization.
  runQPSKSystemUnderTest_initialize();
  try {
    emlrtShouldCleanupOnError((emlrtCTX *)emlrtRootTLSGlobal, false);
    // Dispatch the entry-point.
    unsafe_runQPSKSystemUnderTest_mexFunction(nlhs, plhs, nrhs);
    // Module termination.
    runQPSKSystemUnderTest_terminate();
  } catch (...) {
    emlrtCleanupOnException((emlrtCTX *)emlrtRootTLSGlobal);
    throw;
  }
}

emlrtCTX mexFunctionCreateRootTLS()
{
  emlrtCreateRootTLSR2021a(&emlrtRootTLSGlobal, &emlrtContextGlobal, nullptr, 1,
                           nullptr);
  return emlrtRootTLSGlobal;
}

void unsafe_runQPSKSystemUnderTest_mexFunction(int32_T nlhs, mxArray *plhs[1],
                                               int32_T nrhs)
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  const mxArray *outputs;
  st.tls = emlrtRootTLSGlobal;
  // Check for proper number of arguments.
  if (nrhs != 0) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 0, 4,
                        22, "runQPSKSystemUnderTest");
  }
  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 22,
                        "runQPSKSystemUnderTest");
  }
  // Call the function.
  runQPSKSystemUnderTest_api(&outputs);
  // Copy over outputs to the caller.
  emlrtReturnArrays(1, &plhs[0], &outputs);
}

// End of code generation (_coder_runQPSKSystemUnderTest_mex.cpp)
