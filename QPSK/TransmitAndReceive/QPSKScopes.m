
%

%   Copyright 2012-2017 The MathWorks, Inc.

classdef (StrictDefaults)QPSKScopes < matlab.System
    
    properties
      SampleRate = 1
    end
  
    properties (Access=private)
        pRxScope              % Spectrum analyzer System object to plot received signal after filtering
        pRxConstellation      % Constellation scope System object to plot received signal after filtering
        pTimeRecConstellation % Constellation scope System object to plot received signal after timing recovery
        pFreqRecConstellation % Constellation scope System object to plot received signal after fine frequency compensation        
        pFirstLength          % For visualizing var-size signals with Constellation Diagram
    end
    
    methods
        function obj = QPSKScopes(varargin)
            setProperties(obj,nargin,varargin{:});
        end
    end
    
    methods (Access=protected)
        function setupImpl(obj, ~, ~, coarseCompBuffer, ~)
            obj.pRxScope = dsp.SpectrumAnalyzer('NumInputPorts', 2, ...
                    'SampleRate', obj.SampleRate, ...
                    'SpectralAverages', 2, ...
                    'PowerUnits', 'dBW', 'YLimits', [-130 -15], ...
                    'Title', 'After Raised Cosine Rx Filter', ...
                    'SpectralAverages', 1, ...
                    'YLabel', 'PSD', ...
                    'SpectrumType', 'Power density', ...
                    'ShowLegend', true, ...
                    'ChannelNames', {'received', 'filtered'});
            obj.pRxConstellation = comm.ConstellationDiagram( ...
                    'ShowGrid', true, ...          
                    'SamplesPerSymbol', 2, ...                    
                    'YLimits', [-3 3], ...
                    'XLimits', [-3 3], ...
                    'Title', 'After Raised Cosine Rx Filter', ...
                    'ReferenceConstellation', sqrt(2)*qammod(0:3, 4));
            obj.pTimeRecConstellation = comm.ConstellationDiagram( ...
                    'ShowGrid', true, ...
                    'YLimits', [-3 3], ...
                    'XLimits', [-3 3], ...                    
                    'SamplesPerSymbol', 2, ...                    
                    'Title', 'After Timing Recovery', ...
                    'ReferenceConstellation', sqrt(2)*qammod(0:3, 4));
            obj.pFreqRecConstellation = comm.ConstellationDiagram( ...
                    'ShowGrid', true, ...
                    'YLimits', [-3 3], ...
                    'XLimits', [-3 3], ...                    
                    'SamplesPerSymbol', 2, ...                    
                    'Title', 'After Fine Frequency Compensation', ...
                    'EnableMeasurements', true, ...
                    'ReferenceConstellation', sqrt(2)*qammod(0:3, 4));
                  
            
            obj.pFirstLength = length(coarseCompBuffer);
        end
        
        
        function stepImpl(obj, RxSignal, RCRxSignal, timingRecSignal, freqRecSignal)
            
            obj.pRxConstellation(RCRxSignal);            % Plots the constellation of the filtered signal               
            obj.pRxScope(RxSignal, RCRxSignal);                    % Plots the spectrum scope of the filtered signal     
            len = max(1, 2*round((obj.pFirstLength-6)/2)); % Fixed-size, even length
            obj.pTimeRecConstellation(timingRecSignal(1:len)); % Plots the constellation of the symbol synchronized signal
            obj.pFreqRecConstellation(freqRecSignal(1:len)); % Plots the constellation of the phase recovered signal
        end
        
        function resetImpl(obj)
            reset(obj.pRxConstellation);
            reset(obj.pFreqRecConstellation);
            reset(obj.pRxScope);
        end
        
        function releaseImpl(obj)
            release(obj.pRxConstellation);
            release(obj.pFreqRecConstellation);
            release(obj.pRxScope);
        end
        
        function N = getNumInputsImpl(~)
            N = 4; 
        end
        
        function N = getNumOutputsImpl(~)
            N = 0; 
        end
    end
end
