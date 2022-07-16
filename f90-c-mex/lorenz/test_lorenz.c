/*
 * test_lorenz.c
 * function for testing interoperability with the lorenz ODE fortran routine. 
 *
 * Copyright (c) Joel Fischer 2022
 */

extern void f_lorenz(double sigma, double rho, double beta,
		double* y0, double t0, double dt, int n);

int main(){

	double sigma = 28.;
	double rho = 10.;
	double beta = 8.0/3.0;

	double y0[3] = {1.0, 0.0, 0.0};
	double t0 = 0.;
	double dt = 1e-3;

	int n = 1000000;

	f_lorenz(sigma, rho, beta, y0, t0, dt, n);

	return 0;
}

