class rc4Gen{
	x;
	y;
	buffer;
	bufferSize;
	constructor(q){
		var i;
		this.bufferSize=q;
		this.buffer=[];
		for(i=0;i<this.bufferSize;i++){
			this.buffer[i]=i;
		}
	}
	pump(){
		var temp=this.buffer[this.x];
		this.y+=temp;
		this.y%=this.bufferSize;
		this.buffer[this.x]=this.buffer[this.y];
		this.buffer[this.y]=temp;
		temp+=this.buffer[this.x];
		temp%=this.bufferSize;
		temp=this.buffer[temp];
		this.x++;
		this.x%=this.bufferSize;
		return temp;
	} 
	initBuffer(p){
		var i;
		var pp=p.split('').map(y => y.charCodeAt(0));
		var l=pp.length;
		this.x = 0;
		this.y = 0;
		for(i=0;i<this.bufferSize;i++){
			this.buffer[i]=i;
		}
		for(i=0;i<this.bufferSize;i++){
			this.y+=pp[i%l]+256;
			this.pump();
		}
		for(i=0;i<this.bufferSize;i++){
			this.pump();
		}
	}
}