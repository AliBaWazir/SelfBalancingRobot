/*
 * PUBLISHED header for cgxert, the runtime library for CGXE
 *
 * Copyright 2014 The MathWorks, Inc.
 *
 */

#ifndef cgxert_h
#define cgxert_h

#if defined(_MSC_VER)
# pragma once
#endif
#if defined(__GNUC__) && (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ > 3))
# pragma once
#endif

/*
 * Only define EXTERN_C if it hasn't been defined already. This allows
 * individual modules to have more control over managing their exports.
 */
#ifndef EXTERN_C

#ifdef __cplusplus
#define EXTERN_C extern "C"
#else
#define EXTERN_C extern
#endif

#endif

#ifndef LIBCGXERT_API
#define LIBCGXERT_API
#endif

#define CGXE_SIM_RUNNING 0
#define CGXE_SIM_STOPPED 1
#define CGXE_SIM_PAUSED 2


#include "emlrt.h"
#include "simstruc.h"


/*
 * MATLAB INTERNAL USE ONLY :: Get varsize input port dimensions array address
 */
EXTERN_C LIBCGXERT_API int *ssGetCurrentInputPortDimensions_wrapper(SimStruct *S, int portNumber);

/*
 * MATLAB INTERNAL USE ONLY :: Get varsize output port dimensions array address
 */
EXTERN_C LIBCGXERT_API int *ssGetCurrentOutputPortDimensions_wrapper(SimStruct *S, int portNumber);

/*
 * MATLAB INTERNAL USE ONLY :: Check if model has stopped simulation
 */
EXTERN_C LIBCGXERT_API unsigned int cgxe_listen_for_ctrl_c(SimStruct *S, emlrtCTX aCtx);


#endif /* cgxert_h */
