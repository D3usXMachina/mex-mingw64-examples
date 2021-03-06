! Copyright (c) 2022 Joel Fischer

subroutine f(neq, t, y, ydot)
  !> =DESCRIPTION=============================================================
  !> Calculate the integrand of a Lorenz system
  !> -NOTES-------------------------------------------------------------------
  !> =========================================================================
  use lorenz, only : dp, sigma, rho, beta
  implicit none
  ! ==VARIABLE=DECLARATION====================================================
  ! input arguments ----------------------------------------------------------
  integer, intent(in) :: neq ! the number of equations
  real(dp), intent(in) :: t ! independent variable
  real(dp), dimension(3), intent(in) :: y ! dependent variable
  ! output arguments ---------------------------------------------------------
  real(dp), dimension(3), intent(out) :: ydot ! integrand
  ! ==========================================================================

  ydot = (/ &
          sigma*(y(2) - y(1)), &
          y(1)*(rho - y(3)) - y(2), &
          y(1)*y(2) - beta*y(3) &
          /)
  
end subroutine f

program lorenz
  !> =DESCRIPTION=============================================================
  !> Solve a Lorenz system ODE
  !> -NOTES-------------------------------------------------------------------
  !> =========================================================================
  use lorenz, only : dp
  implicit none
  ! ==VARIABLE=DECLARATION====================================================
  ! lsode variables ----------------------------------------------------------
  external dlsode, f
  integer :: jac
  integer :: iopt, iout, istate, itask, itol, iwork(20+3), liw, lrw, mf, neq
  real(dp) :: atol, rtol, rwork(22+9*3+3**2), t, tout, y(3)
  ! other variables ----------------------------------------------------------
  integer :: itout
  ! ==========================================================================

  neq = 3 ! number of equations of ode
  y = (/ 1.0d0, 0.0d0, 0.0d0 /) ! initial value of dependent variable
  t = 0.0d0 ! initial value of independent variable
  itol = 1 ! 1 -> use one absolute tolerance, 2 -> use individual absolute tolerances
  rtol = 1d-4 ! relative tolerance
  atol = 1d-6 ! absolute tolerance
  itask = 1 ! task : compute value at predefined value of independent variable
  istate = 1 ! 1 for first call
  iopt = 0 ! no optional arguments
  lrw = 22+9*3+3**2 ! length of floating point work array
  liw = 20+3 ! length of integer work array
  mf = 22 ! which method to use : 22 -> stiff method, auto-generated jacobian
  
  tout = 0.1d0 ! first output time

  do itout = 1,1000000
    call dlsode(f, neq, y, t, tout, &
                itol, rtol, atol, itask, istate, iopt, &
                rwork, lrw, iwork, liw, jac, mf)
    write(*,*) t, y(1), y(2), y(3)
    if (istate < 0) then
      write(*,*) 'Error halt.. istate = ', istate
      STOP "LSODE ran into a problem."
    end if
    tout = tout + 0.1d-2
  end do
  write(*,*) iwork(11), iwork(12), iwork(13)

end program lorenz
