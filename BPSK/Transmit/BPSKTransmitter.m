classdef (StrictDefaults)BPSKTransmitter < matlab.System  
%#codegen
% Generates the QPSK signal to be transmitted
    
%   Copyright 2012-2017 The MathWorks, Inc.
    
    properties (Nontunable)
        UpsamplingFactor = 2;
        ScramblerBase = 2;
        ScramblerPolynomial = [1 1 1 0 1];
        ScramblerInitialConditions = [0 0 0 0];
        RolloffFactor = 0.5
        RaisedCosineFilterSpan = 10
        NumberOfMessage = 10
        MessageLength = 16
        MessageBits = []
    end
    
    properties (Access=private)
        pBitGenerator
        pBPSKModulator 
        pTransmitterFilter
        pMessage = 'Hello world';
        pHeader = [+1 +1 +1 +1 +1 -1 -1 +1 +1 -1 +1 -1 +1]; % Bipolar barker-code
    end
    
    methods
        function obj = BPSKTransmitter(varargin)
            setProperties(obj,nargin,varargin{:});
        end
    end
    
    methods (Access=protected)
        function setupImpl(obj)
            obj.pBitGenerator = QPSKBitsGenerator( ...
                'NumberOfMessage',              obj.NumberOfMessage, ...
                'MessageLength',                obj.MessageLength, ...
                'MessageBits',                  obj.MessageBits, ...
                'ScramblerBase',                obj.ScramblerBase, ...
                'ScramblerPolynomial',          obj.ScramblerPolynomial, ...
                'ScramblerInitialConditions',   obj.ScramblerInitialConditions);
            obj.pBPSKModulator  = comm.BPSKModulator( ...
                'PhaseOffset',                  pi/2, ...
                'OutputDataType',               'double');
            obj.pTransmitterFilter = comm.RaisedCosineTransmitFilter( ...
                'RolloffFactor',                obj.RolloffFactor, ...
                'FilterSpanInSymbols',          obj.RaisedCosineFilterSpan, ...
                'OutputSamplesPerSymbol',       obj.UpsamplingFactor);
        end

        function transmittedSignal = stepImpl(obj) 
            [transmittedBin, ~] = obj.pBitGenerator();                 % Generates the data to be transmitted
            modulatedData = obj.pBPSKModulator(transmittedBin);        % Modulates the bits into QPSK symbols           
            transmittedSignal = obj.pTransmitterFilter(modulatedData); % Square root Raised Cosine Transmit Filter
        end
        
        function resetImpl(obj)
            reset(obj.pBitGenerator);
            reset(obj.pBPSKModulator );
            reset(obj.pTransmitterFilter);
        end
        
        function releaseImpl(obj)
            release(obj.pBitGenerator);
            release(obj.pBPSKModulator );
            release(obj.pTransmitterFilter);
        end
        
        function N = getNumInputsImpl(~)
            N = 0;
        end
    end
end

