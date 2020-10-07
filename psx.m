function y=psx(windowSize,stretchFactor,sourceVector)
%function y=psx(windowSize,stretchFactor,sourceVector)

%w=zeros(windowSize,1);
ww=windowSize/2;

w=ivize(abs(ww-.5-(0:windowSize-1)'));

w.*=w;
w=1-w;
w=w.^1.25;
y=w;