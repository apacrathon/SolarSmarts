/*
 * MATLAB Compiler: 6.6 (R2018a)
 * Date: Mon Apr 16 17:36:18 2018
 * Arguments:
 * "-B""macro_default""-W""lib:regress""-T""link:lib""-d""X:\Users\raj\Documents
 * \Spring
 * 2018\Capstone\SolarSmarts\solar-smarts-matlab\generated\regress\for_testing""
 * -v""X:\Users\raj\Documents\Spring
 * 2018\Capstone\SolarSmarts\solar-smarts-matlab\functions\Regress.m"
 */

#ifndef __regress_h
#define __regress_h 1

#if defined(__cplusplus) && !defined(mclmcrrt_h) && defined(__linux__)
#  pragma implementation "mclmcrrt.h"
#endif
#include "mclmcrrt.h"
#ifdef __cplusplus
extern "C" {
#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_regress_C_API 
#define LIB_regress_C_API /* No special import/export declaration */
#endif

/* GENERAL LIBRARY FUNCTIONS -- START */

extern LIB_regress_C_API 
bool MW_CALL_CONV regressInitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_regress_C_API 
bool MW_CALL_CONV regressInitialize(void);

extern LIB_regress_C_API 
void MW_CALL_CONV regressTerminate(void);

extern LIB_regress_C_API 
void MW_CALL_CONV regressPrintStackTrace(void);

/* GENERAL LIBRARY FUNCTIONS -- END */

/* C INTERFACE -- MLX WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- START */

extern LIB_regress_C_API 
bool MW_CALL_CONV mlxRegress(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

/* C INTERFACE -- MLX WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- END */

/* C INTERFACE -- MLF WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- START */

extern LIB_regress_C_API bool MW_CALL_CONV mlfRegress(mxArray* input, mxArray* output);

#ifdef __cplusplus
}
#endif
/* C INTERFACE -- MLF WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- END */

#endif
