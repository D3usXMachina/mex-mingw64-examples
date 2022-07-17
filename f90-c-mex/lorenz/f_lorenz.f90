! Copyright (c) 2022 Joel Fischer

subroutine f_lorenz(sigma, rho, beta, y0, t0, dt, n, output) bind(C, name='f_lorenz')
  !> =DESCRIPTION=============================================================
  !> Solve a Lorenz system ODE
  !> -NOTES-------------------------------------------------------------------
  !> =========================================================================
  use lorenz, only : m_f, dp, ci 
  implicit none
  external dlsode
  ! ==VARIABLE=DECLARATION====================================================
  ! input variables ----------------------------------------------------------
  real(dp), value, intent(in) :: sigma, rho, beta, t0, dt
  real(dp), intent(in) :: y0(3)
  integer(ci), value, intent(in) :: n
  ! output variables ---------------------------------------------------------
  real(dp) :: output(4,n)
  ! lsode variables ----------------------------------------------------------
  integer :: jac
  integer :: iopt, iout, istate, itask, itol, iwork(20+3), liw, lrw, mf, neq
  real(dp) :: atol, rtol, rwork(22+9*3+3**2), t, tout, y(3)
  ! other variables ----------------------------------------------------------
  integer(ci) :: itout
  ! ==========================================================================

  neq = 3 ! number of equations of ode
  y = y0 ! initial value of dependent variable
  t = t0 ! initial value of independent variable
  itol = 1 ! 1 -> use one absolute tolerance, 2 -> use individual absolute tolerances
  rtol = 1e-4 ! relative tolerance
  atol = 1e-6 ! absolute tolerance
  itask = 1 ! task : compute value at predefined value of independent variable
  istate = 1 ! 1 for first call
  iopt = 0 ! no optional arguments
  lrw = 22+9*3+3**2 ! length of floating point work array
  liw = 20+3 ! length of integer work array
  mf = 22 ! which method to use : 22 -> stiff method, auto-generated jacobian
  
  tout = 0.1d0 ! first output time

  do itout = 1, n
    call dlsode(m_f, neq, y, t, tout, &
                itol, rtol, atol, itask, istate, iopt, &
                rwork, lrw, iwork, liw, jac, mf)
    output(1,itout) = t
    output(2:4,itout) = y
    if (istate < 0) then
      write(*,*) 'Error halt.. istate = ', istate
      STOP "LSODE ran into a problem."
    end if
    t = tout
    tout = tout + dt
  end do

end subroutine f_lorenz

