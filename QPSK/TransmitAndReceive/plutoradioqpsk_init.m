classdef plutoradioqpsk_init
    properties
        Rsym % Symbol rate in Hertz
        ModulationOrder% QPSK alphabet size
        Interpolation% Interpolation factor
        Decimation% Decimation factor
        Tsym% Symbol time in sec
        Fs% Sample rate 
        BarkerCode% Bipolar Barker Code
        BarkerLength
        HeaderLength% Duplicate 2 Barker codes to be as a header
        Message
        MessageLength% 'Hello world 000\n'...
        NumberOfMessage% Number of messages in a frame
        PayloadLength% 7 bits per characters
        FrameSize% Frame size in symbols
        FrameTime
        RolloffFactor% Rolloff Factor of Raised Cosine Filter
        ScramblerBase
        ScramblerPolynomial
        ScramblerInitialConditions
        RaisedCosineFilterSpan% Filter span of Raised Cosine Tx Rx filters (in symbols)
        DesiredPower% AGC desired output power (in watts)
        AveragingLength% AGC averaging length
        MaxPowerGain% AGC maximum output power gain
        MaximumFrequencyOffset
        PhaseRecoveryLoopBandwidth% Normalized loop bandwidth for fine frequency compensation
        PhaseRecoveryDampingFactor% Damping Factor for fine frequency compensation
        TimingRecoveryLoopBandwidth% Normalized loop bandwidth for timing recovery
        TimingRecoveryDampingFactor% Damping Factor for timing recovery
        TimingErrorDetectorGain
        PreambleDetectorThreshold
        bits
        MessageBits
        BerMask
        PlutoCenterFrequency
        PlutoGain
        PlutoFrontEndSampleRate
        PlutoFrameLength
        PlutoFrameTime
        StopTime
        Address
    end

    methods
        function obj = plutoradioqpsk_init(Address, CenterFrequency)
            %% General simulation parameters
            obj.Rsym = 0.4e6;             % Symbol rate in Hertz
            obj.ModulationOrder = 4;      % QPSK alphabet size
            obj.Interpolation = 2;        % Interpolation factor
            obj.Decimation = 1;           % Decimation factor
            obj.Tsym = 1/obj.Rsym;  % Symbol time in sec
            obj.Fs   = obj.Rsym * obj.Interpolation; % Sample rate

            %% Frame Specifications
            % [BarkerCode*2 | 'Hello world 000\n' | 'Hello world 001\n' ... | 'Hello world 099\n'];
            obj.BarkerCode      = [+1 +1 +1 +1 +1 -1 -1 +1 +1 -1 +1 -1 +1];     % Bipolar Barker Code
            obj.BarkerLength    = length(obj.BarkerCode);
            obj.HeaderLength    = obj.BarkerLength * 2;                   % Duplicate 2 Barker codes to be as a header
            obj.Message         = 'Hello world';
            obj.MessageLength   = length(obj.Message) + 5;                % 'Hello world 000\n'...
            obj.NumberOfMessage = 100;                                          % Number of messages in a frame
            obj.PayloadLength   = obj.NumberOfMessage * obj.MessageLength * 7; % 7 bits per characters
            obj.FrameSize       = (obj.HeaderLength + obj.PayloadLength) ...
                / log2(obj.ModulationOrder);                                    % Frame size in symbols
            obj.FrameTime       = obj.Tsym*obj.FrameSize;

            %% Rx parameters
            obj.RolloffFactor     = 0.5;                      % Rolloff Factor of Raised Cosine Filter
            obj.ScramblerBase     = 2;
            obj.ScramblerPolynomial           = [1 1 1 0 1];
            obj.ScramblerInitialConditions    = [0 0 0 0];
            obj.RaisedCosineFilterSpan = 10;                  % Filter span of Raised Cosine Tx Rx filters (in symbols)
            obj.DesiredPower                  = 2;            % AGC desired output power (in watts)
            obj.AveragingLength               = 50;           % AGC averaging length
            obj.MaxPowerGain                  = 60;           % AGC maximum output power gain
            obj.MaximumFrequencyOffset        = 6e3;
            % Look into model for details for details of PLL parameter choice. 
            % Refer equation 7.30 of "Digital Communications - A Discrete-Time Approach" by Michael Rice.
            K = 1;
            A = 1/sqrt(2);
            obj.PhaseRecoveryLoopBandwidth    = 0.01;         % Normalized loop bandwidth for fine frequency compensation
            obj.PhaseRecoveryDampingFactor    = 1;            % Damping Factor for fine frequency compensation
            obj.TimingRecoveryLoopBandwidth   = 0.01;         % Normalized loop bandwidth for timing recovery
            obj.TimingRecoveryDampingFactor   = 1;            % Damping Factor for timing recovery
            % K_p for Timing Recovery PLL, determined by 2KA^2*2.7 (for binary PAM),
            % QPSK could be treated as two individual binary PAM,
            % 2.7 is for raised cosine filter with roll-off factor 0.5
            obj.TimingErrorDetectorGain       = 2.7*2*K*A^2+2.7*2*K*A^2;
            obj.PreambleDetectorThreshold     = 0.8;

            %% Message generation and BER calculation parameters
            msgSet = zeros(100 * obj.MessageLength, 1);
            for msgCnt = 0 : 99
                msgSet(msgCnt * obj.MessageLength + (1 : obj.MessageLength)) = ...
                    sprintf('%s %03d\n', obj.Message, int8(msgCnt));
            end
            obj.bits = de2bi(msgSet, 7, 'left-msb')';
            obj.MessageBits = obj.bits(:);

            % For BER calculation masks
            obj.BerMask = zeros(obj.NumberOfMessage * length(obj.Message) * 7, 1);
            for i = 1 : obj.NumberOfMessage
                obj.BerMask( (i-1) * length(obj.Message) * 7 + ( 1: length(obj.Message) * 7) ) = ...
                    (i-1) * obj.MessageLength * 7 + (1: length(obj.Message) * 7);
            end
            % Pluto receiver parameters
            obj.PlutoCenterFrequency      = CenterFrequency;
            obj.PlutoGain                 = 30;
            obj.PlutoFrontEndSampleRate   = obj.Fs;
            obj.PlutoFrameLength          = obj.Interpolation * obj.FrameSize;
            obj.Address                   = Address ; % Specify Radio ID
            % Experiment parameters
            obj.PlutoFrameTime = obj.PlutoFrameLength / obj.PlutoFrontEndSampleRate;
            obj.StopTime = 50;

        end
    end
    
end