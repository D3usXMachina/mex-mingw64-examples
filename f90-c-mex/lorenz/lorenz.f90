! Copyright (c) 2022 Joel Fischer

module lorenz
  !> =DESCRIPTION===============================================================
  !> -NOTES---------------------------------------------------------------------
  !> -CHANGELOG-----------------------------------------------------------------
  !> ===========================================================================
  use iso_c_binding, only: c_double, c_int
  implicit none
  private
  ! ==VARIABLES=================================================================
  public :: sigma, rho, beta, &
            dp, ci
  ! ==SUBROUTINES=&=FUNCTIONS===================================================
  public :: m_f
  ! ============================================================================
  integer, parameter :: dp = c_double
  integer, parameter :: ci = c_int
  real(dp) :: sigma = 10.0d0
  real(dp) :: rho = 28.0d0
  real(dp) :: beta = 8.0d0/3.0d0

contains

  subroutine m_f(neq, t, y, ydot)
    !> =DESCRIPTION=============================================================
    !> Calculate the integrand of a Lorenz system
    !> -NOTES-------------------------------------------------------------------
    !> =========================================================================
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
    
  end subroutine m_f

end module lorenz

