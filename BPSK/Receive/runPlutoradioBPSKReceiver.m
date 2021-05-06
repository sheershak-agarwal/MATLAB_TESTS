function BER = runPlutoradioBPSKReceiver(prmBPSKReceiver, useScopes, printData)

%   Copyright 2017 The MathWorks, Inc.

persistent rx radio bpskScopes;
if isempty(rx)
    rx  = BPSKReceiver(...
        'ModulationOrder',                      prmBPSKReceiver.ModulationOrder, ...
        'SampleRate',                           prmBPSKReceiver.Fs, ...
        'DecimationFactor',                     prmBPSKReceiver.Decimation, ...
        'FrameSize',                            prmBPSKReceiver.FrameSize, ...
        'HeaderLength',                         prmBPSKReceiver.HeaderLength, ...
        'NumberOfMessage',                      prmBPSKReceiver.NumberOfMessage, ...
        'PayloadLength',                        prmBPSKReceiver.PayloadLength, ...
        'DesiredPower',                         prmBPSKReceiver.DesiredPower, ...
        'AveragingLength',                      prmBPSKReceiver.AveragingLength, ...
        'MaxPowerGain',                         prmBPSKReceiver.MaxPowerGain, ...
        'RolloffFactor',                        prmBPSKReceiver.RolloffFactor, ...
        'RaisedCosineFilterSpan',               prmBPSKReceiver.RaisedCosineFilterSpan, ...
        'InputSamplesPerSymbol',                prmBPSKReceiver.Interpolation, ...
        'MaximumFrequencyOffset',               prmBPSKReceiver.MaximumFrequencyOffset, ...
        'PostFilterOversampling',               prmBPSKReceiver.Interpolation/prmBPSKReceiver.Decimation, ...
        'PhaseRecoveryLoopBandwidth',           prmBPSKReceiver.PhaseRecoveryLoopBandwidth, ...
        'PhaseRecoveryDampingFactor',           prmBPSKReceiver.PhaseRecoveryDampingFactor, ...
        'TimingRecoveryDampingFactor',          prmBPSKReceiver.TimingRecoveryDampingFactor, ...
        'TimingRecoveryLoopBandwidth',          prmBPSKReceiver.TimingRecoveryLoopBandwidth, ...
        'TimingErrorDetectorGain',              prmBPSKReceiver.TimingErrorDetectorGain, ...
        'PreambleDetectorThreshold',            prmBPSKReceiver.PreambleDetectorThreshold, ...
        'DescramblerBase',                      prmBPSKReceiver.ScramblerBase, ...
        'DescramblerPolynomial',                prmBPSKReceiver.ScramblerPolynomial, ...
        'DescramblerInitialConditions',         prmBPSKReceiver.ScramblerInitialConditions,...
        'BerMask',                              prmBPSKReceiver.BerMask, ...
        'PrintOption',                          printData);
    
    % Create and configure the Pluto System object.
    radio = sdrrx('Pluto');
    radio.RadioID               = prmBPSKReceiver.Address;
    radio.CenterFrequency       = prmBPSKReceiver.PlutoCenterFrequency;
    radio.BasebandSampleRate    = prmBPSKReceiver.PlutoFrontEndSampleRate;
    radio.SamplesPerFrame       = prmBPSKReceiver.PlutoFrameLength;
    radio.GainSource            = 'Manual';
    radio.Gain                  = prmBPSKReceiver.PlutoGain;
    radio.OutputDataType        = 'double';
    
    if useScopes
        % Create the System object for plotting all the scopes
        sampleRate = prmBPSKReceiver.Rsym*prmBPSKReceiver.Interpolation/prmBPSKReceiver.Decimation;
        bpskScopes = BPSKScopes('SampleRate', sampleRate);
    end
end

% Initialize variables
currentTime = 0;
BER = [];
rcvdSignal = complex(zeros(prmBPSKReceiver.PlutoFrameLength,1));

while currentTime <  prmBPSKReceiver.StopTime
    % Receive signal from the radio
    rcvdSignal = radio();
    
    % Decode the received message
    [RCRxSignal, timingRecSignal, freqRecSignal, BER] = rx(rcvdSignal);
    
    if useScopes
        % Plots all the scopes
        bpskScopes(rcvdSignal, RCRxSignal,timingRecSignal, freqRecSignal);
    end
    
    % Update simulation time
    currentTime=currentTime+(radio.SamplesPerFrame / radio.BasebandSampleRate);
end

release(rx);
release(radio);
if useScopes
    release(bpskScopes);
end

end
