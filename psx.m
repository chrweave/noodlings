function y=psx(windowSize,stretchFactor,sourceVector)
%function y=psx(windowSize,stretchFactor,sourceVector)

%w=zeros(windowSize,1);
ww=windowSize/2;
www=[floor(ww),windowSize-floor(ww)];

w=ivize(abs(ww-.5-(0:windowSize-1)'));

w.*=w;
w=1-w;
w=w.^1.25;
n=floor(length(sourceVector)/windowSize);
l=n*windowSize;

y=zeros(l*stretchFactor,1);
for i=1:n,

end

