/*
 * lorenz.c
 * Gateway function for the lorenz ODE fortran routine. 
 *
 * This is a MEX-file for MATLAB.
 * Copyright (c) Joel Fischer 2022
 */

#include "mex.h"
#include <stdint.h>
#include <stdlib.h>

extern void f_lorenz(double* sigma, double* rho, double* beta,
		double* y0, double* t0, double* dt, int32_t* n,
		double* output);

void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]) {
    int mrows, ncols;
    
    // Check for correct number of input arguments
   if ( nrhs != 7 ) {
        mexErrMsgIdAndTxt("MATLAB:lorenz:invalidNumInputs", "Exactly seven inputs required.");
    }

    // Check for correct argument types 
    for ( size_t i=0 ; i < 7 ; i++ ){
	
	    mrows = mxGetM(prhs[i]);
	    ncols = mxGetN(prhs[i]);
	    if ( i == 6 ){ // n
		    if ( !mxIsInt32(prhs[i]) || !(mrows == 1 && ncols == 1) ) {
			char str[36];
			sprintf(str,"Argument %i must be a 32bit integer scalar.", i+1);
			mexErrMsgIdAndTxt("MATLAB:lorenz:inputNotInt32Scalar", str);
		    }
	    }else if ( i == 3 ){ // y0
		    if ( !mxIsDouble(prhs[i]) || mxIsComplex(prhs[i]) || !(mrows == 3 && ncols == 1) ) {
			char str[60];
			sprintf(str,"Argument %i must be a noncomplex double array of size (3,1).", i+1);
			mexErrMsgIdAndTxt("MATLAB:lorenz:wrongInputFormat", str);
		    }
	    }else{
		    if ( !mxIsDouble(prhs[i]) || mxIsComplex(prhs[i]) || !(mrows == 1 && ncols == 1) ) {
			char str[47];
			sprintf(str,"Argument %i must be a noncomplex double scalar.", i+1);
			mexErrMsgIdAndTxt("MATLAB:lorenz:inputNotRealScalarDouble", str);
		    }
	    }
    }

    // Check for correct number of return arguments
    if ( nlhs != 1 ) {
	mexErrMsgIdAndTxt("MATLAB:lorenz:maxlhs", "Too many output arguments.");
    }


    /* Assign pointers to each input and output. */
#if MX_HAS_INTERLEAVED_COMPLEX
#error "Interleaved complex aren't currently supported."
#else
    double* sigma = mxGetPr(prhs[0]);
    double* rho   = mxGetPr(prhs[1]);
    double* beta  = mxGetPr(prhs[2]);
    double* y0    = mxGetPr(prhs[3]);
    double* t0    = mxGetPr(prhs[4]);
    double* dt    = mxGetPr(prhs[5]);
    int32_t* n	  = mxGetPr(prhs[6]);
#endif
    
    /* Create matrix for the return argument. */
    plhs[0] = mxCreateDoubleMatrix((mwSize)4, (mwSize)(*n), mxREAL);
#if MX_HAS_INTERLEAVED_COMPLEX
#error "Interleaved complex aren't currently supported."
#else
    double* output = mxGetPr(plhs[0]);
#endif

    /* Call the timestwo subroutine. */
    f_lorenz(sigma, rho, beta,
	     y0, t0, dt, n, output);
}

