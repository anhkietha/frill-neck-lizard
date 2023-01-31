% Push out force in N
F_t = 20;

% Pinion Speed in rad/s
pps = 2000;
total_degree = 2000*1.8;
w_p = total_degree*pi/180;

% pinion torque Nm
t_p = 0.12;

% pinion diameter mm
D_p = (2*t_p/F_t)*1000

% length of the rack mm
L_r = 150;

% yield strength of the MDF MPa (mm)
xigma_mdf = 18;

% full depth or stub
full_depth = 1;

% number of teeth on rack and pinion
N_p = 18;

%Module and dimetral pitch
P = N_p/D_p
m = 1/P

% addendum and dedendum
a = D_p/N_p;
d = 1.25*m;



% circular pitch
p = pi/P;

% Lewis form factor in the table
Y = 0.309;

% fatique safety factor 
K_f = 2;

% face width for pinion
b = (F_t*P/(xigma_mdf*Y))*K_f


