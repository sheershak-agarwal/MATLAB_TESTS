%% BPSK Receiver with ADALM-PLUTO Radio

%% Initialization
% Receiver parameter structure
prmBPSKReceiver = plutoradiobpskreceiver_init;
% Specify Radio ID
prmBPSKReceiver.Address = 'usb:1';

%% Execution and Results

printReceivedData = true;    % true if the received data is to be printed
useScopes = true;            % true if scopes are to be used

BER = runPlutoradioBPSKReceiver(prmBPSKReceiver, useScopes, printReceivedData); 

fprintf('Error rate is = %f.\n',BER(1));
fprintf('Number of detected errors = %d.\n',BER(2));
fprintf('Total number of compared samples = %d.\n',BER(3));
