% Input value
%The torque of the servo
Torque = 2.5*9.8*0.01; % In Nm

%The willing force to push out the frill
willing_F = 1.018*5; % In N

%The pitch diameter of the gear
D_p = 0.08; % In m

%The number of teeth on the pinion
number_teeth = 32;

%The minimum number of teeth to check for the interference
min_teeth = 17;

%The force that the servo can provide with the diameter D_p
F = 2*Torque/D_p;

if F > willing_F
    if number_teeth > min_teeth
        disp('This gear allow the servo to provide enough force');


        % diametral pitch
        P = number_teeth/(D_p*1000);

        % module
        module = 1/P
        number_teeth
        
        % addendum and dedendum for the full depth gear
        addendum = module;
        dedendum = 1.25*module;

        % Lewis form factor
        Y = 0.365;

        % yield strength of the material
        xigma_y = 18;

        % fatique factor with suddenly applied load
        Kf = 2.5;

        % the minimum face width to widstand the force
        face_width = (F*P/(xigma_y*Y))*Kf %In mm
        
        % The maximum distance that the rack can travel
        max_dis_travel = pi*D_p/2;
    end
else
    disp('do not meet the desired force');
end



