//
// qpskApp_terminate.cpp
//
// Code generation for function 'qpskApp_terminate'
//

// Include files
#include "qpskApp_terminate.h"
#include "qpskApp.h"
#include "qpskApp_data.h"
#include "rt_nonfinite.h"
#include <string.h>

// Function Definitions
void qpskApp_terminate()
{
  qpskApp_free();
  isInitialized_qpskApp = false;
}

// End of code generation (qpskApp_terminate.cpp)
