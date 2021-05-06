%% BPSK Transmitter with ADALM-PLUTO Radio

%% Initialization

% Transmitter parameter structure
prmBPSKTransmitter = plutoradiobpsktransmitter_init;
% Specify Radio ID
prmBPSKTransmitter.Address = 'ip:192.168.2.1';

runPlutoradioBPSKTransmitter(prmBPSKTransmitter);
