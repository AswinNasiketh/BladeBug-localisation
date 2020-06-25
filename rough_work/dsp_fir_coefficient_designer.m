N = 30; % filter order restrained to 30
Fs = 100e3; % sampling frequency 100kHz
Fp = 10e3; % cut-off frequency at 10kHz
Ap = 0.5; % passband ripple restrained at 3dB
Ast = 20; % stopband attenuation at -20dB

%Obtain the maximum deviation for the passband and stopband ripples in linear units.
Rp  = (10^(Ap/20) - 1)/(10^(Ap/20) + 1);
Rst = 10^(-Ast/20);

%Design the filter using firceqrip and view the magnitude frequency response.
NUM = firceqrip(N,Fp/(Fs/2),[Rp Rst],'passedge');
fvtool(NUM,'Fs',Fs)