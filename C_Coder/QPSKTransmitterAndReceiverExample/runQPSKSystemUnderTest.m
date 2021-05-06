
function BER = runQPSKSystemUnderTest()

    %#codegen

    qpskTx = QPSKTransmitter();
    qpskRx = QPSKReceiver();

%     if useScopes
%         qpskScopes = QPSKScopes('SampleRate', 10e4);
%     end


    for count = 1:1000
        transmittedSignal = qpskTx();                                           % Transmitter
        [~, ~, ~, BER] = qpskRx(transmittedSignal); % Receiver
%         if useScopes
%             qpskScopes(transmittedSignal, RCRxSignal, timingRecSignal, freqRecSignal); % Plots all the scopes
%         end
    end

end
