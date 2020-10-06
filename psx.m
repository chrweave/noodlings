function y=psx(windowSize,stretchFactor,sourceVector)

w=zeros(windowSize,1);
ww=floor(windowSize/2);
if mod(w,2)==0,
    w(1:ww)=(0:ww-1)'/(ww-1);
else
    w(1:ww)=(0:ww-1)'/(ww); 
    w(ww)=1/2;
end
w+=flipud(w);
y=w;