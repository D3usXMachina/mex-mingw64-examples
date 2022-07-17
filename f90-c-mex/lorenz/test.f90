program test
        implicit none
        integer, parameter :: seed = 12314
        integer :: i
        real(kind(1.0d0)) :: y(4)
        call srand(seed)
        
        do i = 1,4
                y(i) = rand()
        end do

        write(*,"(4(E12.6,2X))") y(1), y(2), y(3), y(4)
end program test
