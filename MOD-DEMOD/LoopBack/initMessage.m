function [messageBits, berMask] = initMessage(message, messageLength, numberOfMessages)
%#codegen
coder.inline('always');

%% Message generation and BER calculation parameters
msgSet = zeros(numberOfMessages* messageLength, 1); 
for msgCnt = 0 : numberOfMessages
    msgSet(msgCnt * messageLength + (1 : messageLength)) = ...
        sprintf('%s', message);
end
messageBits = reshape(de2bi(msgSet, 7, 'left-msb')', [], 1);
%SimParams.MessageBits = messageBits;

% For BER calculation masks
berMask = zeros(numberOfMessages * length(message) * 7, 1);
for i = 1 : numberOfMessages
    berMask( (i-1) * length(message) * 7 + ( 1: length(message) * 7) ) = ...
        (i-1) * messageLength * 7 + (1: length(message) * 7);
end

end