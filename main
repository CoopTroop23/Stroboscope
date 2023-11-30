/*
  This is a random file for testing purposes
*/
% program two unknown angles
% solves a loop equation
% written by Cooper Nelson

clear
dtr = pi/180; %degrees to radians conversion

%enter known values -length, radians

rk1 = 12;
thetak1 = 190*dtr;

rk2 = 6;
thetak2 = 40*dtr;

rua1 = 8;
rua2 = 5;

%step 0 collect knowns into single vector

rkx = rk1*cos(thetak1) + rk2*cos(thetak2);

rky = rk1*sin(thetak1) + rk2*sin(thetak2);

rk = sqrt(rkx^2 +rky^2);

thetak = atan2(rky,rkx);


%step 4 solve a,b,c (quadratic)

a = rua1^2 - rua2^2 - rk^2 + 2*rua2*rkx;

b = -4*rua2*rky;

c = rua1^2 - rua2^2 - rk^2 - 2*rua2*rkx;


%step 5 solve for t (quadratic equation)

tp = (-b+sqrt(b^2-4*a*c))/2*a;

tm = (-b-sqrt(b^2-4*a*c))/2*a;


%step 6 solve thetaua2

thetaua2p = 2*atan(tp);
thetaua2m = 2*atan(tm);

%step 7 solve tor thetaua1

thetaua1p = atan2((-rua2*sin(thetaua2p)-rky)/rua1, ...
                  (-rua1*cos(thetaua2p)-rkx)/rua1);

thetaua1m = atan2((-rua2*sin(thetaua2m)-rky)/rua1, ...
                  (-rua1*cos(thetaua2m)-rkx)/rua1);




