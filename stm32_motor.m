clear; clc
close all

dataMatrix = readmatrix('sine_signal.txt');

length = 5001;

time = dataMatrix(1 : length, 1);
pos = dataMatrix(1 : length, 2);
vel = dataMatrix(1 : length, 3);
u = dataMatrix(1 : length, 4);
%% arx model
Ts = 1e-03;
data = iddata(pos, u, Ts);
model = arx(data, [2 1 1]);
%% Transfer function model
Gd = tf(model);
Gc = d2c(Gd);
%% State-Space model
[num,den]=tfdata(Gc,'v');
[A, B, C, D] = tf2ss(num, den);
%% PID controller parameter
Kp = 33.6;
Ki = 81.77;
Kd = 0.8559;
%%
x0=[0 0 0];
tspan=[0 5];
[t,x]=ode45(@(t,x) func(t,x,A,B,C,Kp,Ki,Kd),tspan,x0);
y = C * x(:, 1 : 2)';
figure(), plot(t, y, 'r')
yline(pi, '--k')
legend('Actual','Reference')
%% function of the ID system
function xp=func(t,x,A,B,C,Kp,Ki,Kd)
    r = pi;
    y = C * [x(1); x(2)];
    e = r - y;
    u = Kp * e + Ki * x(3) + Kd * (-x(2));
    xp(1: 2, :) = A * [x(1); x(2)] + B * u;
    xp(3) = e;
end