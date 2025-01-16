import sys, os
class O:
	def __init__(a,n,S):
		a.s=list(range(n));a.x=a.y=0;a.n=n
		for i in S:a.y=a.y+ord(i);a.Q()
		for i in range(8*a.n):a.Q()
	def Q(a):a.x=(a.x+1)%a.n;t=a.s[a.x];a.y=(a.y+t)%a.n;a.s[a.x]=a.s[a.y];a.s[a.y]=t;t=(t+a.s[a.x])%a.n;return a.s[t]
def V(b):os.mkdir(b);os.chdir(b)
U=sys.argv
P=O(360,U[1])
def T(x):return list(x)[P.Q()%len(x)]
L='aeiou'
M='bcdfgjklmnprstvwxz'
def I():return(''.join([T(M),T(L),T(M),T(L),T(M)]))
l=(int(U[2])-1)*2
b=c=0
e=l-1
z=l+1
r=[-2*(v&1)+1 for v in O(l,U[1]).s]+[0]
p=[(l+v)%z for v in range(z)]
n=[(v+2)%z for v in p]
while c!=e:
	t=r[b];c=b
	while t!=0:c=n[c];t=t+r[c]
	g=n[c]
	if r[b]==-1:
		a=p[b];t=n[b];d=p[c];f=n[e];n[a]=c;p[c]=a;n[e]=b;p[b]=e;n[d]=f;p[f]=d
		if b!=d:
			while t!=f:r[t]*=-1;t=n[t]
	b=g
k=[]
t=n[-1]
while r[t]!=0:k.append(r[t]);t=n[t]
V(U[3])
for i in range(l):
	if k[i]==1:
		V(I())
		if k[i+1]==-1:
			with open(I()+".txt", "w") as W:W.write(I()+"\n")
	else:
		os.chdir('..')
