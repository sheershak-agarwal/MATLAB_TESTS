//
// _coder_runQPSKSystemUnderTest_api.cpp
//
// Code generation for function 'runQPSKSystemUnderTest'
//

// Include files
#include "_coder_runQPSKSystemUnderTest_api.h"
#include "_coder_runQPSKSystemUnderTest_mex.h"

// Variable Definitions
emlrtCTX emlrtRootTLSGlobal{nullptr};

emlrtContext emlrtContextGlobal{
    true,                                                 // bFirstTime
    false,                                                // bInitialized
    131610U,                                              // fVersionInfo
    nullptr,                                              // fErrorFunction
    "runQPSKSystemUnderTest",                             // fFunctionName
    nullptr,                                              // fRTCallStack
    false,                                                // bDebugMode
    {2045744189U, 2170104910U, 2743257031U, 4284093946U}, // fSigWrd
    nullptr                                               // fSigMem
};

// Function Declarations
static const mxArray *emlrt_marshallOut(const real_T u[3]);

// Function Definitions
static const mxArray *emlrt_marshallOut(const real_T u[3])
{
  static const int32_T i{0};
  static const int32_T i1{3};
  const mxArray *m;
  const mxArray *y;
  y = nullptr;
  m = emlrtCreateNumericArray(1, (const void *)&i, mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m, (void *)&u[0]);
  emlrtSetDimensions((mxArray *)m, &i1, 1);
  emlrtAssign(&y, m);
  return y;
}

void runQPSKSystemUnderTest_api(const mxArray **plhs)
{
  real_T(*BER)[3];
  BER = (real_T(*)[3])mxMalloc(sizeof(real_T[3]));
  // Invoke the target function
  runQPSKSystemUnderTest(*BER);
  // Marshall function outputs
  *plhs = emlrt_marshallOut(*BER);
}

void runQPSKSystemUnderTest_atexit()
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  runQPSKSystemUnderTest_xil_terminate();
  runQPSKSystemUnderTest_xil_shutdown();
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

void runQPSKSystemUnderTest_initialize()
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, nullptr);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

void runQPSKSystemUnderTest_terminate()
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

// End of code generation (_coder_runQPSKSystemUnderTest_api.cpp)
