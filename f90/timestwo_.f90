! Copyright (C) 2022 Joel Fischer

subroutine timestwo(input,output)

    implicit none
    
    real(kind=kind(1.0d0)), intent(in) :: input
    real(kind=kind(1.0d0)), intent(out) :: output
    
    output = 2*input
    
    return

end subroutine