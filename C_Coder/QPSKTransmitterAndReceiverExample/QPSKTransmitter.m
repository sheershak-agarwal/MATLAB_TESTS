classdef (StrictDefaults)QPSKTransmitter < matlab.System  
%#codegen
% Generates the QPSK signal to be transmitted
    
%   Copyright 2012-2017 The MathWorks, Inc.
    
    properties (Constant)
        UpsamplingFactor = 2;                       % Interpolation
        ScramblerBase = 2;                          % ScramblerBase
        ScramblerPolynomial = [1 1 1 0 1];          % ScramblerPolynomial
        ScramblerInitialConditions = [0 0 0 0];     % ScramblerInitialConditions
        RolloffFactor = 0.5                         % RolloffFactor
        RaisedCosineFilterSpan = 10                 % RaisedCosineFilterSpan
        MessageLength = 16 % len(Message) + 5    'Hello world 000\n'...
        NumberOfMessage = 20 % Number of messages in a frame
        Message = 'Hello world'; % Message
        %MessageBits = []
    end
    
    properties (Access=private)
        pBitGenerator
        pQPSKModulator 
        pTransmitterFilter
        pMessage = 'Hello world';
        pHeader = [+1 +1 +1 +1 +1 -1 -1 +1 +1 -1 +1 -1 +1]; % Bipolar barker-code
    end
    
    methods
        function obj = QPSKTransmitter(varargin)
            setProperties(obj,nargin,varargin{:});
        end
    end
    
    methods (Access=protected)
        function setupImpl(obj)

            obj.pBitGenerator = QPSKBitsGenerator();
            obj.pQPSKModulator  = comm.QPSKModulator( ...
                'BitInput',                     true, ...
                'PhaseOffset',                  pi/4, ...
                'OutputDataType',               'double');
            obj.pTransmitterFilter = comm.RaisedCosineTransmitFilter( ...
                'RolloffFactor',                obj.RolloffFactor, ...
                'FilterSpanInSymbols',          obj.RaisedCosineFilterSpan, ...
                'OutputSamplesPerSymbol',       obj.UpsamplingFactor);
        end

        function transmittedSignal = stepImpl(obj) 
            [transmittedBin, ~] = obj.pBitGenerator();                 % Generates the data to be transmitted
            modulatedData = obj.pQPSKModulator(transmittedBin);        % Modulates the bits into QPSK symbols           
            transmittedSignal = obj.pTransmitterFilter(modulatedData); % Square root Raised Cosine Transmit Filter
        end
        
        function resetImpl(obj)
            reset(obj.pBitGenerator);
            reset(obj.pQPSKModulator );
            reset(obj.pTransmitterFilter);
        end
        
        function releaseImpl(obj)
            release(obj.pBitGenerator);
            release(obj.pQPSKModulator );
            release(obj.pTransmitterFilter);
        end
        
        function N = getNumInputsImpl(~)
            N = 0;
        end
    end
end

