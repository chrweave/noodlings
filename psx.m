function y=psx(windowSize,stretchFactor,sourceVector)

w=zeros(windowSize,1);
ww=floor(windowSize/2);
w(1:ww)=(0:ww-1)'/(ww-1);
w+=flipud(w);
y=w;