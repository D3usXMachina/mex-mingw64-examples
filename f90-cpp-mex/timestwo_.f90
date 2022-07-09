! Copyright (c) 2022 Joel Fischer

subroutine timestwo(input,output) bind(C, name='timestwo')

    use iso_c_binding, only: c_double
    implicit none
    
    real(c_double), intent(in), value :: input
    real(c_double), intent(out) :: output
    
    output = 2.0d0*input

    return

end subroutine