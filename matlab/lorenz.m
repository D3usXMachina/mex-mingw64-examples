% Copyright (c) 2022 Joel Fischer

function [t,y] = lorenz(t0,y0,sigma,rho,beta,dt,nt,rtol)

    f = @(t,y) f_lorenz(t,y,sigma,rho,beta);
    [t,y] = ode15s(f,[t0,t0+dt*nt],y0,odeset('RelTol',rtol,'MaxStep',0.1e-2));
end

function ydot = f_lorenz(t,y,sigma,rho,beta)
    ydot = [...
           sigma*(y(2) - y(1));...
           y(1)*(rho - y(3)) - y(2);...
           y(1)*y(2) - beta*y(3)...
           ];
end
