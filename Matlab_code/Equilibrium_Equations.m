%% Equilibrium Equations for Frill Neck

g=9.8;
n_of_linkages=4;
% Lower Linkage
Len_lower=0.05;
M_Lower=0.005;
% Upper Linkage
Len_upper_total=0.15;
Len_upper_pin=0.045;
M_upper=0.010;
COM_upper=0.055;

% Lower Face
M_face=0.0075;

% Moment Equation
Ly=(M_upper*g*COM_upper)*(1/Len_upper_pin);

% Force Equation
F=M_face*g+(M_Lower*g+Ly)*n_of_linkages



