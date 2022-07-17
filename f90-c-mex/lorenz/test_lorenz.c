/*
 * test_lorenz.c
 * function for testing interoperability with the lorenz ODE fortran routine. 
 *
 * Copyright (c) Joel Fischer 2022
 */
#include <stdio.h>

extern void f_lorenz(double sigma, double rho, double beta,
		double* y0, double t0, double dt, int n,
		double* output);

int main(){

	double sigma = 28.;
	double rho = 10.;
	double beta = 8.0/3.0;

	double y0[3] = {1.0, 0.0, 0.0};
	double t0 = 0.;
	double dt = 1e-3;

	int n = 1000000;

	double* output = malloc(4*n*sizeof(double));

	f_lorenz(sigma, rho, beta, y0, t0, dt, n, output);


	for (size_t i_tout = 0 ; i_tout<n ; i_tout++) {
		printf("%e\t%e\t%e\t%e\n",
			output[4*i_tout+0],
			output[4*i_tout+1],
			output[4*i_tout+2],
			output[4*i_tout+3]);	
	}

	free(output);

	return 0;
}

