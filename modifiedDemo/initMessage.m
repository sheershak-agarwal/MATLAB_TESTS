function [messageBits, berMask] = initMessage(message, messageLength, numberOfMessages)
%#codegen
coder.inline('always');

%% Message generation and BER calculation parameters
msgSet = zeros(100 * messageLength, 1); 
for msgCnt = 0 : 99
    msgSet(msgCnt * messageLength + (1 : messageLength)) = ...
        sprintf('%s %03d\n', message, int32(msgCnt));
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