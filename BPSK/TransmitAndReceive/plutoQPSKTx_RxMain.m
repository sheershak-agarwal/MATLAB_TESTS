%% QPSK Transmitter and Receiver with ADALM-PLUTO Radio

%% Initialization

% Transmitter parameter structure
%prmQPSKTransmitter = plutoradioqpsktransmitter_init;
% Specify Radio ID
%prmQPSKTransmitter.Address = 'usb:1'

% Receiver parameter structure
prmQPSKRadio = plutoradioqpsk_init;
% Specify Radio ID
prmQPSKRadio.Address = 'usb:0';

%% Execution and Results

printReceivedData = true;    % true if the received data is to be printed
useScopes = true;            % true if scopes are to be used

BER = runPlutoradioQPSKTransmitAndReceiver(prmQPSKRadio, useScopes, printReceivedData); 

fprintf('Error rate is = %f.\n',BER(1));
fprintf('Number of detected errors = %d.\n',BER(2));
fprintf('Total number of compared samples = %d.\n',BER(3));
