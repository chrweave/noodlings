import sys
import os
    
class Rc4g:
    def __init__(self, n, seed):
        self.s=[v for v in range(n)]
        self.x=0 
        self.y=0 
        self.t=0
        self.n=n
        for i in seed:
            self.y=self.y+ord(i)
            self.pump()
        for i in range(8*self.n):
            self.pump()
    def pump(self):
        self.x=(self.x+1)%self.n
        self.y=(self.y+self.s[self.x])%self.n
        self.t=self.s[self.x]
        self.s[self.x]=self.s[self.y]
        self.s[self.y]=self.t
        self.t=self.t+self.s[self.x]
        self.t=self.t%self.n
        return self.s[self.t]
        
 
def makePreBrackets(n, p):
    m=Rc4g(n,p)
    r=[[0,-1,-1] for v in range (n+1)]
    for i in range(n): 
        r[i][0]=-2*(m.s[i]&1)+1
    for i in range(n+1): #corrected for dummy node
        r[i][1]= (n+i)%(n+1) #previous
        r[i][2]= (i+1)%(n+1) #next
    return r
    
def getWordEnd(x,r): #triple ,list of triples
    t=r[x][0]
    while t!=0:
        x=r[x][2]
        t=t+r[x][0]
    return x

def phi(r):
    b=0
    e=len(r)-2
    endCondition=True
    while endCondition:
        we=getWordEnd(b,r)
        endCondition= not we==e
        bnew=r[we][2]
        if r[b][0]==-1: #mis formed word; fix pointers ... in python
            bp=r[b][1]
            t=r[b][2]
            wep=r[we][1]
            en=r[e][2]
            r[bp][2]=we
            r[we][1]=bp
            r[e][2]=b
            r[b][1]=e
            r[wep][2]=en
            r[en][1]=wep
            if b!=wep:                
                while t!=en:
                    r[t][0]=r[t][0]*-1
                    t=r[t][2]
        b=bnew
    q=[]
    t=r[len(r)-1][2] #start at the dummy node's next
    while r[t][0] !=0:
        q.append(r[t][0])
        t=r[t][2]
    return q
    
    
vo=[x for x in 'aeiou']
co=[x for x in 'bcdfgjklmnprstvwxz']

def getFivoul(rc):
    q=[co[rc.pump()%18],vo[rc.pump()%5],co[rc.pump()%18],vo[rc.pump()%5],co[rc.pump()%18]]
    return(''.join(q))
    
def makeFolders(n, a, b):
    j=makePreBrackets((n-1)*2,a)
    k=phi(j) # get a properly formatted bracket structure   
    fivul=Rc4g(360,a)
    os.mkdir(b)
    os.chdir(b)
    for i in range( len(k)):
        if k[i] == 1:
            dn=getFivoul(fivul)
            os.mkdir(dn)
            os.chdir(dn)
            if k[i+1]==-1:
                dn=getFivoul(fivul)
                with open(dn+".txt", "w") as file:
                    dn=getFivoul(fivul)
                    file.write(dn+"\n")
        else:
            os.chdir('..')
            
makeFolders(int(sys.argv[2]),sys.argv[1],sys.argv[3])
