class latinSquare{
	rc4;
	xy = [];
	yz = [];
	xz = [];
	cubeDim;
	constructor(inNum,keyString){
		this.cubeDim=inNum;
		this.rc4=new rc4Gen(100*this.cubeDim);
		this.rc4.initBuffer(keyString);
	}

	makeSquare(x){
		var s=[];
		var i,j;
		for(i=0;i<x;i++){
		s[i]=[];
			for(j=0;j<x;j++){
				s[i][j]=0;
			}
		}
		return s;
	}
	initMarginals(){
		var i,j,k;
	
		this.xy = this.makeSquare(this.cubeDim);
		this.yz = this.makeSquare(this.cubeDim);
		this.xz = this.makeSquare(this.cubeDim);
		for(i=0;i<this.cubeDim;i++){
			for(j=0;j<this.cubeDim;j++){
				k=i+j;
				k%=this.cubeDim;
				this.xy[i][j]=k;
				this.yz[j][k]=i;
				this.xz[i][k]=j;
			}
		}
	}
	randswap(x){
		if(this.rc4.pump()%2==1){
			var temp =x[0];
			x[0]=x[1];
			x[1]=temp;
		}
	}
	latin() { /* Ported Via C from Paul Hankin's source */
		var mxy, mxz, myz;
		var m = [0,0,0];
		var proper = true;
		var minIter = this.cubeDim*this.cubeDim*this.cubeDim;
		var iter;
	
		this.initMarginals();
		for(iter=0;iter<minIter||!proper; iter++){
			var i, j, k, i2=[0,0], j2=[0,0], k2=[0,0];
	
			if (proper) {
				// Pick a random 0 in the array
				do{
					i = this.rc4.pump()%this.cubeDim;
					j = this.rc4.pump()%this.cubeDim;
					k = this.rc4.pump()%this.cubeDim;
				}while( this.xy[i][j] == k);
				// find i2 such that [i2, j, k] is 1. same for j2, k2
				i2[0] = this.yz[j][k];
				j2[0] = this.xz[i][k];
				k2[0] = this.xy[i][j];
				i2[1]=i;
				j2[1]=j;
				k2[1]=k;
			} else {
				i = m[0];
				j = m[1];
				k = m[2];
				// find one such that [i2, j, k] is 1, same for j2, k2.
				// each is either the value stored in the corresponding
				// slice, or one of our three temporary "extra" 1s.
				// That's because (i, j, k) is -1.
				
				this.randswap(i2=[this.yz[j][k],myz]);
				this.randswap(j2=[this.xz[i][k],mxz]);
				this.randswap(k2=[this.xy[i][j],mxy]);
			}
	
			proper = (this.xy[i2[0]][j2[0]] == k2[0]);
			if (!proper) {
				m[0]=i2[0];
				m[1]=j2[0];
				m[2]=k2[0];
				mxy = this.xy[i2[0]][j2[0]];
				myz = this.yz[j2[0]][k2[0]];
				mxz = this.xz[i2[0]][k2[0]];
			}
	
			this.xy[i][j]         = k2[1];
			this.xy[i][j2[0]]     = k2[0];
			this.xy[i2[0]][j]     = k2[0];
			this.xy[i2[0]][j2[0]] = k;
	
			this.yz[j][k]      	 = i2[1];
			this.yz[j][k2[0]]  	 = i2[0];
			this.yz[j2[0]][k]     = i2[0];
			this.yz[j2[0]][k2[0]] = i;
	
			this.xz[i][k]         = j2[1];
			this.xz[i][k2[0]]     = j2[0];
			this.xz[i2[0]][k]     = j2[0];
			this.xz[i2[0]][k2[0]] = j;
		}
		return this.xy;
	}
}