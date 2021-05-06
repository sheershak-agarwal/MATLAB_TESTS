function runPlutoradioBPSKTransmitter(prmBPSKTransmitter)
%#codegen

%   Copyright 2017 The MathWorks, Inc.

persistent hTx radio
if isempty(hTx)
    % Initialize the components
    % Create and configure the transmitter System object
    hTx = BPSKTransmitter(...
        'UpsamplingFactor',             prmBPSKTransmitter.Interpolation, ...
        'RolloffFactor',                prmBPSKTransmitter.RolloffFactor, ...
        'RaisedCosineFilterSpan',       prmBPSKTransmitter.RaisedCosineFilterSpan, ...
        'MessageBits',                  prmBPSKTransmitter.MessageBits, ...
        'MessageLength',                prmBPSKTransmitter.MessageLength, ...
        'NumberOfMessage',              prmBPSKTransmitter.NumberOfMessage, ...
        'ScramblerBase',                prmBPSKTransmitter.ScramblerBase, ...
        'ScramblerPolynomial',          prmBPSKTransmitter.ScramblerPolynomial, ...
        'ScramblerInitialConditions',   prmBPSKTransmitter.ScramblerInitialConditions);
    
    % Create and configure the Pluto System object.
    radio = sdrtx('Pluto');
    radio.RadioID               = prmBPSKTransmitter.Address;
    radio.CenterFrequency       = prmBPSKTransmitter.PlutoCenterFrequency;
    radio.BasebandSampleRate    = prmBPSKTransmitter.PlutoFrontEndSampleRate;
    radio.SamplesPerFrame       = prmBPSKTransmitter.PlutoFrameLength;
    radio.Gain                  = prmBPSKTransmitter.PlutoGain;
end

currentTime = 0;
disp('Transmission has started')
    
    % Transmission Process
while currentTime < prmBPSKTransmitter.StopTime
    % Bit generation, modulation and transmission filtering
    data = step(hTx);

    % Data transmission
    step(radio, data);

    % Update simulation time
    currentTime = currentTime+prmBPSKTransmitter.FrameTime;
end

if currentTime ~= 0
    disp('Transmission has ended')
end    

release(hTx);
release(radio);

end
