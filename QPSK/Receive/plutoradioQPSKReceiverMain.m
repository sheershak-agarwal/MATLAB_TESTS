%% QPSK Receiver with ADALM-PLUTO Radio

%% Initialization
% Receiver parameter structure
prmQPSKReceiver = plutoradioqpskreceiver_init;
% Specify Radio ID
prmQPSKReceiver.Address = 'ip:192.168.2.1';

%% Execution and Results

printReceivedData = true;    % true if the received data is to be printed
useScopes = false;            % true if scopes are to be used

BER = runPlutoradioQPSKReceiver(prmQPSKReceiver, useScopes, printReceivedData); 

fprintf('\nError rate is = %f.\n',BER(1));
fprintf('Number of detected errors = %d.\n',BER(2));
fprintf('Total number of compared samples = %d.\n',BER(3));
