// Copyright (c) Joel Fischer 2022

#include "mex.hpp"
#include "mexAdapter.hpp"

#include <cstdint>
#include <cstdio>
#include <memory>
#include <utility>

#include "matlabPtr.hpp"

extern "C" {
	void f_lorenz(double* sigma, double* rho, double* beta,
		const double* y0, double* t0, double* dt, int32_t* n,
		double* output);
}

class MexFunction : public matlab::mex::Function {

public:

    void operator()(matlab::mex::ArgumentList outputs, matlab::mex::ArgumentList inputs){
        
        matlab::data::ArrayFactory factory{};
        checkArguments(outputs, inputs, factory);

        double sigma 	= inputs[0][0];
        double rho 	    = inputs[1][0];
        double beta 	= inputs[2][0];
        const double* y0= getDataPtr<double>(inputs[3]);
        double t0 	    = inputs[4][0];
        double dt 	    = inputs[5][0];
        int32_t n 	    = inputs[6][0];

        matlab::data::buffer_ptr_t<double> y = factory.createBuffer<double>((size_t)(4*n));
        
        f_lorenz(&sigma, &rho, &beta, y0, &t0, &dt, &n, y.get());

        outputs[0] = factory.createArrayFromBuffer<double>(matlab::data::ArrayDimensions{(size_t)n,4}, std::move(y), matlab::data::MemoryLayout::ROW_MAJOR);
    }

private:

    void checkArguments(matlab::mex::ArgumentList outputs,
			matlab::mex::ArgumentList inputs,
			matlab::data::ArrayFactory& factory) {

        std::shared_ptr<matlab::engine::MATLABEngine> matlabPtr = getEngine();

        if ( inputs.size() != 7 ){
            matlabPtr->feval(u"error", 
                0, std::vector<matlab::data::Array>{
                factory.createScalar("MATLAB:lorenz:invalidNumInputs"),
                factory.createScalar("Exactly seven inputs required")
                });
        }

        for ( size_t i = 0 ; i < 7 ; i++ ){
            if ( i == 6 ){ // n

                if ( inputs[i].getType() != matlab::data::ArrayType::INT32 ||
                        inputs[i].getNumberOfElements() != 1 ){
                    char sbuf[32];
                    sprintf(sbuf, "Input %i must be a int32 scalar.", i);
                    matlabPtr->feval(u"error", 
                        0, std::vector<matlab::data::Array>{
                        factory.createScalar("MATLAB:lorenz:inputNotInt32Scalar"),
                        factory.createScalar(sbuf)});
                }
            }else if ( i == 3 ){ // y0

                if ( inputs[i].getType() != matlab::data::ArrayType::DOUBLE || 
                        inputs[i].getNumberOfElements() != 3 ){
                    char sbuf[32];
                    sprintf(sbuf, "Argument %i must be a noncomplex double array of length 3.", i);
                    matlabPtr->feval(u"error", 
                        0, std::vector<matlab::data::Array>{
                        factory.createScalar("MATLAB:lorenz:wrongInputFormat"),
                        factory.createScalar(sbuf)});
                }
            }else{

                if ( inputs[i].getType() != matlab::data::ArrayType::DOUBLE ||
                        inputs[i].getNumberOfElements() != 1 ){
                    char sbuf[44];
                    sprintf(sbuf, "Input %i must be a noncomplex double scalar.", i);
                    matlabPtr->feval(u"error", 
                        0, std::vector<matlab::data::Array>{
                        factory.createScalar("MATLAB:lorenz:inputNotRalScalarDouble"),
                        factory.createScalar(sbuf)});
                }
            }
        }
    }

};

