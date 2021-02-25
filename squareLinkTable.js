class squareLinkTable{
	dim;
	lu = [];
	rlu = [];
	clu = [];
	constructor(p){
		var i, j;
		this.dim=p;
		for(i=0;i<this.dim;i++){
			this.rlu[i]=0;
			this.clu[i]=0;
			this.lu[i]=[];
			for(j=0;j<this.dim;j++){
				this.lu[i][j]=0;
			}
		}
	}
}