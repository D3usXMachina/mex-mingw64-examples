/*
 * test_lorenz.cpp
 * function for testing interoperability with the lorenz ODE fortran routine. 
 *
 * Copyright (c) Joel Fischer 2022
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <memory>

extern "C" {
	void f_lorenz(double* sigma, double* rho, double* beta,
		double* y0, double* t0, double* dt, int32_t* n,
		double* output);
}

int main(){

	double sigma = 28.;
	double rho = 10.;
	double beta = 8.0/3.0;

	double y0[3] = {1.0, 0.0, 0.0};
	double t0 = 0.;
	double dt = 1e-3;

	int32_t n = 1000000;

	auto y = std::make_unique<double[]>(4*n);

	f_lorenz(&sigma, &rho, &beta, y0, &t0, &dt, &n, y.get());


	for (int32_t i_tout = 0 ; i_tout<n ; i_tout++) {
		printf("%e\t%e\t%e\t%e\n",
			y[4*i_tout+0],
			y[4*i_tout+1],
			y[4*i_tout+2],
			y[4*i_tout+3]);	
	}

	return 0;
}

