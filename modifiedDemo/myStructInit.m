function [SimParams, messageBits, berMask] = myStructInit(message)
coder.inline('always');
% Set simulation parameters
% Copyright 2011-2018 The MathWorks, Inc.

%% General simulation parameters
modulationOrder           = coder.const(4);
interpolation             = coder.const(2);
decimation                = coder.const(1);
rSym                      = coder.const(5e4);
tSym                      = coder.const(1/rSym);
fs                        = coder.const(rSym *interpolation);
totalFrames               = coder.const(1000);

SimParams.ModulationOrder = coder.const(modulationOrder);     % QPSK alphabet size
SimParams.Interpolation   = coder.const(interpolation);       % Interpolation factor
SimParams.Decimation      = coder.const(decimation);          % Decimation factor
SimParams.Rsym            = coder.const(rSym);                % Symbol rate in Hertz
SimParams.Tsym            = coder.const(tSym);                % Symbol time in sec
SimParams.Fs              = coder.const(fs);                  % Sample rate
SimParams.TotalFrame      = coder.const(totalFrames);         % Simulate 1000 frames in total

%% Frame Specifications
% [BarkerCode*2 | 'Hello world 000\n' | 'Hello world 001\n' ...];
barkerCode                = coder.const([+1 +1 +1 +1 +1 -1 -1 +1 +1 -1 +1 -1 +1]); % bipolar barker code
barkerLength              = coder.const(length(barkerCode));       
headerLength              = coder.const(barkerLength *2);                      % duplicate 2 barker codes as header
%message                   = coder.const('Hello world');            
messageLength             = coder.const(strlength(message) + 5);               % 'Hello World 000\n'       
numberOfMessages          = coder.const(20);
payloadLength             = coder.const(numberOfMessages * messageLength * 7); % 7 bits per character
frameSize                 = coder.const((headerLength + payloadLength)/log2(modulationOrder));
frameTime                 = coder.const(tSym*frameSize);

SimParams.BarkerCode      = coder.const(barkerCode);
SimParams.BarkerLength    = coder.const(barkerLength);
SimParams.HeaderLength    = coder.const(headerLength);
%SimParams.Message         = coder.const(message);
SimParams.MessageLength   = coder.const(messageLength);
SimParams.NumberOfMessage = coder.const(numberOfMessages);
SimParams.PayloadLength   = coder.const(payloadLength);
SimParams.FrameSize       = coder.const(frameSize);
SimParams.FrameTime       = coder.const(frameTime);

%% Tx parameters
rolloffFactor              = coder.const(0.5);         % rolloff factor of raise cosine filter
scramblerBase              = coder.const(2);
scramblerPolynomial        = coder.const([1 1 1 0 1]);
scramblerInitialConditions = coder.const([0 0 0 0]);
raisedCosineFilterSpan     = coder.const(10);          % filter span of raised cosine filters (in symbols)

SimParams.RolloffFactor              = coder.const(rolloffFactor);
SimParams.ScramblerBase              = coder.const(scramblerBase);
SimParams.ScramblerPolynomial        = coder.const(scramblerPolynomial);
SimParams.ScramblerInitialConditions = coder.const(scramblerInitialConditions);
SimParams.RaisedCosineFilterSpan     = coder.const(raisedCosineFilterSpan);

%% Channel parameters
phaseOffset     = coder.const(47);         % in degrees
EbNo            = coder.const(13);         % in dB
frequencyOffset = coder.const(5000);       % Frequency offset introduced by channel in Hertz
delayType       = coder.const('Triangle'); % type of delay for channel distortion

SimParams.PhaseOffset      = coder.const(phaseOffset);
SimParams.EbNo             = coder.const(EbNo);
SimParams.FrequencyOffset  = coder.const(frequencyOffset);
SimParams.DelayType        = coder.const(delayType);

%% Rx parameters
% Look into model for details for details of PLL parameter choice. Refer equation 7.30 of "Digital Communications - A Discrete-Time Approach" by Michael Rice.
% K_p for Timing Recovery PLL, determined by 2KA^2*2.7 (for binary PAM), 
% QPSK could be treated as two individual binary PAM, 
% 2.7 is for raised cosine filter with roll-off factor 0.5

desiredPower                  = coder.const(2);            % AGC desired output power (in watts)
averagingLength               = coder.const(50);           % AGC averaging length
maxPowerGain                  = coder.const(20);           % AGC maximum output power gain
maximumFrequencyOffset        = coder.const(6e3);
k                             = coder.const(1);
a                             = coder.const(1/sqrt(2));
phaseRecoveryLoopBandwidth    = coder.const(0.01);         % Normalized loop bandwidth for fine frequency compensation
phaseRecoveryDampingFactor    = coder.const(1);            % Damping Factor for fine frequency compensation
timingRecoveryLoopBandwidth   = coder.const(0.01);         % Normalized loop bandwidth for timing recovery
timingRecoveryDampingFactor   = coder.const(1);            % Damping Factor for timing recovery
timingErrorDetectorGain       = coder.const(2.7*2*k*a^2+2.7*2*k*a^2); 
preambleDetectorThreshold     = coder.const(20);

SimParams.DesiredPower                  = coder.const(desiredPower);
SimParams.AveragingLength               = coder.const(averagingLength);
SimParams.MaxPowerGain                  = coder.const(maxPowerGain);
SimParams.MaximumFrequencyOffset        = coder.const(maximumFrequencyOffset);
SimParams.PhaseRecoveryLoopBandwidth    = coder.const(phaseRecoveryLoopBandwidth);
SimParams.PhaseRecoveryDampingFactor    = coder.const(phaseRecoveryDampingFactor);
SimParams.TimingRecoveryLoopBandwidth   = coder.const(timingRecoveryLoopBandwidth);
SimParams.TimingRecoveryDampingFactor   = coder.const(timingRecoveryDampingFactor);
SimParams.TimingErrorDetectorGain       = coder.const(timingErrorDetectorGain);
SimParams.PreambleDetectorThreshold     = coder.const(preambleDetectorThreshold);

% %% Message generation and BER calculation parameters
% msgSet = zeros(100 * messageLength, 1); 
% for msgCnt = 0 : 99
%     msgSet(msgCnt * messageLength + (1 : messageLength)) = ...
%         sprintf('%s %03d\n', message, int32(msgCnt));
% end
% messageBits = reshape(de2bi(msgSet, 7, 'left-msb')', [], 1);
% %SimParams.MessageBits = messageBits;
% 
% % For BER calculation masks
% berMask = zeros(numberOfMessages * length(message) * 7, 1);
% for i = 1 : numberOfMessages
%     berMask( (i-1) * length(message) * 7 + ( 1: length(message) * 7) ) = ...
%         (i-1) * messageLength * 7 + (1: length(message) * 7);
% end


