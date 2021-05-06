BER = runQPSKSystemUnderTest();
fprintf('\nError rate = %f.\n',BER(1));
fprintf('Number of detected errors = %d.\n',BER(2));
fprintf('Total number of compared samples = %d.\n',BER(3));



% fid = fopen('messageBits.txt','wt');
% fprintf(fid, '[');
% Message = 'Hello World';
% MessageLength = length(Message) + 5;
% NumberOfMessage = 20;
% msgSet = zeros(100 * MessageLength, 1); 
% for msgCnt = 0 : 99
%     msgSet(msgCnt * MessageLength + (1 : MessageLength)) = ...
%     sprintf('%s %03d\n', Message, int64(msgCnt));
% end
% msgBits = reshape(de2bi(msgSet, 7, 'left-msb')', [], 1);
% for i = 1:11200
%     fprintf(fid,  '%d;', msgBits(i));
% end
% fprintf(fid, ']');
% fclose(fid);

% fid = fopen('BERMaskBits.txt','wt');
% fprintf(fid, '[');
% Message = 'Hello World';
% MessageLength = length(Message) + 5;
% NumberOfMessage = 20;
% BerMask = zeros(NumberOfMessage * length(Message) * 7, 1);
% for i = 1 : NumberOfMessage
%     BerMask( (i-1) * length(Message) * 7 + ( 1: length(Message) * 7) ) = (i-1) * MessageLength * 7 + (1: length(Message) * 7);
% end
% for i = 1:1540
%     fprintf(fid,  '%d;', BerMask(i));
% end
% fprintf(fid, ']');
% fclose(fid);