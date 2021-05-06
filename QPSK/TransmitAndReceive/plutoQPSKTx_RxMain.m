%#codegen

%% QPSK Transmitter and Receiver with ADALM-PLUTO Radio
%% Initialization

function plutoQPSKTx_RxMain 

%% Execution and Results

printReceivedData = true;    % true if the received data is to be printed
useScopes = true;            % true if scopes are to be used

BER = runPlutoradioQPSKTransmitAndReceiver(useScopes, printReceivedData); 

fprintf('\nError rate is = %f.\n',BER(1));
fprintf('Number of detected errors = %d.\n',BER(2));
fprintf('Total number of compared samples = %d.\n',BER(3));

end
