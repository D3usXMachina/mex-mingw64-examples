// Copyright (C) 2022 Joel Fischer

#include <stdio.h>

extern "C" { void timestwo(double input, double* output); }

int main( int argc, char* argv[] ){

    double input, output;
    int status;

    if ( argc > 1 ) {
        status = sscanf(argv[1], "%lg", &input);
        if ( !status ){
            fprintf(stderr, " Invalid input argument. First input argument must be a floating point number.");
            return 1;
        } else {
            printf(" Input argument: %g\n", input);
        }
    } else {
        printf(" No input arguments. Using example: input = 1.3\n");
        input = 1.3;
    }

    timestwo(input, &output);

    printf("Result: %g", output);

    return 0;
}