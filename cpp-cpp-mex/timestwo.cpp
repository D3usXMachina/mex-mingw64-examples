// Copyright (c) 2022 Joel Fischer

#include "mex.hpp"
#include "mexAdapter.hpp"

extern void timestwo(double input, double* output);

class MexFunction : public matlab::mex::Function {

public:
    void operator()(matlab::mex::ArgumentList outputs, matlab::mex::ArgumentList inputs){
        
        matlab::data::ArrayFactory factory;

        checkArguments(outputs, inputs, factory);
        double x = inputs[0][0];
        double y;

        // call compute routine
        timestwo(x, &y);

        outputs[0] = factory.createScalar(y);
    }

    void checkArguments(matlab::mex::ArgumentList outputs, matlab::mex::ArgumentList inputs, matlab::data::ArrayFactory& factory) {
        std::shared_ptr<matlab::engine::MATLABEngine> matlabPtr = getEngine();

        if (inputs.size() != 1) {
            matlabPtr->feval(u"error", 
                0, std::vector<matlab::data::Array>({ factory.createScalar("One input is required") }));
        }
        
        if (inputs[0].getNumberOfElements() != 1 || inputs[0].getType() != matlab::data::ArrayType::DOUBLE) {
            matlabPtr->feval(u"error", 
                0, std::vector<matlab::data::Array>({ factory.createScalar("Input must be scalar double") }));
        }

        if (outputs.size() > 1) {
            matlabPtr->feval(u"error", 
                0, std::vector<matlab::data::Array>({ factory.createScalar("Too many output arguments") }));
        }
    }
};