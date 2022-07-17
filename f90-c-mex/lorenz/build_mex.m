% Copyright (c) 2022 Joel Fischer

%warning("Please change the path to mingwlibs according to your system and precompile the fortran objects.");
%mex lorenz.c m_lorenz.o f_lorenz.o dlsode.o -L"\C:\Program Files\MinGW-w64\lib" -lgfortran -lquadmath
%mex lorenz.c m_lorenz.o f_lorenz.o dlsode.o -L"C:\MinGW\lib\gcc\mingw32\6.3.0\" -lgfortran -lquadmath
mex lorenz.c m_lorenz.o f_lorenz.o dlsode.o -lgfortran -lquadmath