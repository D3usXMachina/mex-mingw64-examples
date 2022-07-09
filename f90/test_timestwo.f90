program testtimestwo

implicit none

real(kind=kind(1.0d0)) :: input, output
character(len=16) :: inputarg

if ( command_argument_count() > 0 ) then
    call get_command_argument(1, inputarg)
    print *, "Input argument: ", inputarg
    read(inputarg, *) input
else
    print *, "No input arguments. Using example: input = 1.3"
    input = 1.3d0
end if

call timestwo(input, output)

print *, "Result: ", output

end program