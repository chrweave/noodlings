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

z=zeros(l*stretchFactor,1);
pa=0;
ta=0;
ki=0;
kj=0;
q=zeros(windowSize,1);
for cont=1:(2*n-1),
    q=w.*sourceVector(pa+1:pa+windowSize);
    pa+=www(ki+1);
    ki+=1;
    ki=mod(ki,2);
    r=fft(q);
    sa=rand(windowSize,1);
    sb=2*pi*i*sa;
    sc=exp(sb);
    sd=sc.*r;
    se=ifft(sd);
    s=real(se);
    for j=1:stretchFactor,
        z(ta+1:ta+windowSize)+=s;
        ta+=www(kj+1);
        kj+=1;
        kj=mod(kj,2);
    end;
end
y=rnorm(z);

