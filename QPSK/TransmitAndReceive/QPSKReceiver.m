classdef (StrictDefaults)QPSKReceiver < matlab.System
    %

    % Copyright 2012-2018 The MathWorks, Inc.
    
    properties
        ModulationOrder;
        SampleRate;
        DecimationFactor;
        FrameSize;
        HeaderLength;
        NumberOfMessage;
        PayloadLength;
        DesiredPower;
        AveragingLength;
        MaxPowerGain;
        RolloffFactor;
        RaisedCosineFilterSpan;
        InputSamplesPerSymbol;
        MaximumFrequencyOffset;
        PostFilterOversampling;
        PhaseRecoveryLoopBandwidth;
        PhaseRecoveryDampingFactor;
        TimingRecoveryDampingFactor;
        TimingRecoveryLoopBandwidth;
        TimingErrorDetectorGain;
        PreambleDetectorThreshold;
        DescramblerBase;
        DescramblerPolynomial;
        DescramblerInitialConditions;
        BerMask;
        PrintOption;
    end
    
    properties (Access = private)
        pAGC
        pRxFilter
        pCoarseFreqEstimator
        pCoarseFreqCompensator
        pFineFreqCompensator
        pTimingRec
        pPrbDet
        pFrameSync
        pDataDecod
        pMeanFreqOff
        pCnt
    end
    
    properties (Access = private, Constant)
        pUpdatePeriod = 4 % Defines the size of vector that will be processed in AGC system object
        pModulatedHeader = sqrt(2)/2 * (-1-1i) * [+1; +1; +1; +1; +1; -1; -1; +1; +1; -1; +1; -1; +1];
        pMessage = 'Hello world';
        pMessageLength = 16;
    end
    
    methods
        function obj = QPSKReceiver(varargin)
            setProperties(obj,nargin,varargin{:});
        end
    end
    
    methods (Access = protected)
        function setupImpl(obj, ~)
            
            obj.pAGC = comm.AGC( ...
                'DesiredOutputPower',       obj.DesiredPower, ...
                'AveragingLength',          obj.AveragingLength, ...
                'MaxPowerGain',             obj.MaxPowerGain);
            
            obj.pRxFilter = comm.RaisedCosineReceiveFilter( ...
                'RolloffFactor',            obj.RolloffFactor, ...
                'FilterSpanInSymbols',      obj.RaisedCosineFilterSpan, ...
                'InputSamplesPerSymbol',    obj.InputSamplesPerSymbol, ...
                'DecimationFactor',         obj.DecimationFactor);
            
            obj.pCoarseFreqEstimator = comm.CoarseFrequencyCompensator( ...
                'Modulation',               'QPSK', ...
                'Algorithm',                'Correlation-based', ...
                'MaximumFrequencyOffset',   obj.MaximumFrequencyOffset, ....
                'SampleRate',               obj.SampleRate/obj.DecimationFactor);
            
            obj.pCoarseFreqCompensator = comm.PhaseFrequencyOffset( ...
                'PhaseOffset',              0, ...
                'FrequencyOffsetSource',    'Input port', ...
                'SampleRate',               obj.SampleRate/obj.DecimationFactor);

            obj.pMeanFreqOff = 0;
            
            obj.pCnt = 0;
            
            obj.pFineFreqCompensator = comm.CarrierSynchronizer( ...
                'Modulation',               'QPSK', ...
                'ModulationPhaseOffset',    'Auto', ...
                'SamplesPerSymbol',         obj.PostFilterOversampling, ...
                'DampingFactor',            obj.PhaseRecoveryDampingFactor, ...
                'NormalizedLoopBandwidth',  obj.PhaseRecoveryLoopBandwidth);
            
            obj.pTimingRec = comm.SymbolSynchronizer( ...
                'TimingErrorDetector',      'Gardner (non-data-aided)', ...
                'SamplesPerSymbol',         obj.PostFilterOversampling, ...
                'DampingFactor',            obj.TimingRecoveryDampingFactor, ...
                'NormalizedLoopBandwidth',  obj.TimingRecoveryLoopBandwidth, ...
                'DetectorGain',             obj.TimingErrorDetectorGain);
            
            obj.pPrbDet = comm.PreambleDetector(obj.pModulatedHeader, ...
                'Input',                    'Symbol', ...
                'Threshold',                obj.PreambleDetectorThreshold);
            
            obj.pFrameSync = comm.internal.examples.FrameSynchronizer(  ...
                'OutputFrameLength',        obj.FrameSize, ...
                'PreambleLength',           obj.HeaderLength / 2);
            
            obj.pDataDecod = QPSKDataDecoder( ...
                'ModulationOrder',          obj.ModulationOrder, ...
                'HeaderLength',             obj.HeaderLength, ...
                'NumberOfMessage',          obj.NumberOfMessage, ...
                'PayloadLength',            obj.PayloadLength, ...
                'DescramblerBase',          obj.DescramblerBase, ...
                'DescramblerPolynomial',    obj.DescramblerPolynomial, ...
                'DescramblerInitialConditions', obj.DescramblerInitialConditions, ...
                'BerMask',                  obj.BerMask, ...
                'PrintOption',              obj.PrintOption);
        end
        
        function [RCRxSignal, timingRecSignal, fineCompSignal, BER] = stepImpl(obj, bufferSignal)
            
            AGCSignal = obj.pAGC(bufferSignal);                          % AGC control
            RCRxSignal = obj.pRxFilter(AGCSignal);                       % Pass the signal through
                                                                         % Square-Root Raised Cosine Received Filter
            [~, freqOffsetEst] = obj.pCoarseFreqEstimator(RCRxSignal);   % Coarse frequency offset estimation
            % average coarse frequency offset estimate, so that carrier
            % sync is able to lock/converge
            freqOffsetEst = (freqOffsetEst + obj.pCnt * obj.pMeanFreqOff)/(obj.pCnt+1);
            obj.pCnt = obj.pCnt + 1;            % update state
            obj.pMeanFreqOff = freqOffsetEst;
            
            coarseCompSignal = obj.pCoarseFreqCompensator(RCRxSignal,...
                -freqOffsetEst);                                         % Coarse frequency compensation
            timingRecSignal = obj.pTimingRec(coarseCompSignal);          % Symbol timing recovery
            
            fineCompSignal = obj.pFineFreqCompensator(timingRecSignal);  % Fine frequency compensation
            
            [prbIdx, dtMt] = obj.pPrbDet(fineCompSignal);                % Detect frame header
            
            [symFrame, isFrameValid] = obj.pFrameSync(fineCompSignal, ...
                prbIdx, dtMt);                                           % Frame synchronization
            
            BER = obj.pDataDecod(symFrame, isFrameValid);
            
        end
        
        function resetImpl(obj)
            reset(obj.pAGC);
            reset(obj.pRxFilter);
            reset(obj.pCoarseFreqEstimator);
            reset(obj.pCoarseFreqCompensator);
            reset(obj.pFineFreqCompensator);
            reset(obj.pTimingRec);
            reset(obj.pPrbDet);
            reset(obj.pFrameSync);
            reset(obj.pDataDecod);
            obj.pMeanFreqOff = 0;
            obj.pCnt = 0;
        end
        
        function releaseImpl(obj)
            release(obj.pAGC);
            release(obj.pRxFilter);
            release(obj.pCoarseFreqEstimator);
            release(obj.pCoarseFreqCompensator);
            release(obj.pFineFreqCompensator);
            release(obj.pTimingRec);
            release(obj.pPrbDet);
            release(obj.pFrameSync);
            release(obj.pDataDecod);
        end
        
        function N = getNumOutputsImpl(~)
            N = 4;
        end
    end
end

