% Copyright (c) 2022 Joel Fischer

a = tic();
x = lorenz(10.,28.,8./3,[1.,0,0],0.,1e-3,int32(500000)).';
figure;
plot3(x(:,2),x(:,3),x(:,4));
toc(a)