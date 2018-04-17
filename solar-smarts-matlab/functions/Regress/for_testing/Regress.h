//
// MATLAB Compiler: 6.6 (R2018a)
// Date: Mon Apr 16 23:22:46 2018
// Arguments:
// "-B""macro_default""-W""cpplib:Regress,all""-T""link:lib""-d""X:\Users\raj\Do
// cuments\Spring
// 2018\Capstone\SolarSmarts\solar-smarts-matlab\functions\Regress\for_testing""
// -v""X:\Users\raj\Documents\Spring
// 2018\Capstone\SolarSmarts\solar-smarts-matlab\functions\Regress.m"
//

#ifndef __Regress_h
#define __Regress_h 1

#if defined(__cplusplus) && !defined(mclmcrrt_h) && defined(__linux__)
#  pragma implementation "mclmcrrt.h"
#endif
#include "mclmcrrt.h"
#include "mclcppclass.h"
#ifdef __cplusplus
extern "C" {
#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_Regress_C_API 
#define LIB_Regress_C_API /* No special import/export declaration */
#endif

/* GENERAL LIBRARY FUNCTIONS -- START */

extern LIB_Regress_C_API 
bool MW_CALL_CONV RegressInitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_Regress_C_API 
bool MW_CALL_CONV RegressInitialize(void);

extern LIB_Regress_C_API 
void MW_CALL_CONV RegressTerminate(void);

extern LIB_Regress_C_API 
void MW_CALL_CONV RegressPrintStackTrace(void);

/* GENERAL LIBRARY FUNCTIONS -- END */

/* C INTERFACE -- MLX WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- START */

extern LIB_Regress_C_API 
bool MW_CALL_CONV mlxRegress(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

/* C INTERFACE -- MLX WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- END */

#ifdef __cplusplus
}
#endif


/* C++ INTERFACE -- WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- START */

#ifdef __cplusplus

/* On Windows, use __declspec to control the exported API */
#if defined(_MSC_VER) || defined(__MINGW64__)

#ifdef EXPORTING_Regress
#define PUBLIC_Regress_CPP_API __declspec(dllexport)
#else
#define PUBLIC_Regress_CPP_API __declspec(dllimport)
#endif

#define LIB_Regress_CPP_API PUBLIC_Regress_CPP_API

#else

#if !defined(LIB_Regress_CPP_API)
#if defined(LIB_Regress_C_API)
#define LIB_Regress_CPP_API LIB_Regress_C_API
#else
#define LIB_Regress_CPP_API /* empty! */ 
#endif
#endif

#endif

extern LIB_Regress_CPP_API void MW_CALL_CONV Regress(const mwArray& input, const mwArray& output);

/* C++ INTERFACE -- WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- END */
#endif

#endif
