function y=psx(stepSize,stretchFactor,sourceVector)
%function y=psx(stepSize,stretchFactor,sourceVector)

%w=zeros(windowSize,1);
bigStep=stretchFactor*stepSize;
windowSize=bigStep*2;

w=ivize(abs(bigStep-.5-(0:windowSize-1)'));

w.*=w;
w=1-w;
w=w.^1.25;
n=floor((length(sourceVector)-windowSize)/stepSize);
l=n*bigStep+windowSize;

z=zeros(l,1);
pa=0;
ta=0;
q=zeros(windowSize,1);
for cont=1:n,
    q=w.*sourceVector(pa+1:pa+windowSize);
    pa+=stepSize;
    r=fft(q);
    sa=rand(windowSize,1);
    sb=2*pi*i*sa;
    sc=exp(sb);
    sd=sc.*r;
    se=ifft(sd);
    s=real(se).*w;
    for j=1:stretchFactor,
        z(ta+1:ta+windowSize)+=s;
        ta+=stepSize;
    end;
end
y=rnorm(z);

