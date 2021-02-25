class squareReader{
	xy;
	myDim;
	lt;
	constructor(inDim,inSquare){
		this.myDim=inDim;
		this.lt=new squareLinkTable(this.myDim);
		this.xy=inSquare;
	}
	setBorderBottom(x){
		x.style.textAlign = "right";
		x.addEventListener('mouseenter', e => {
			squareHighlighter.highlight(x,this.lt);
		});				
		x.addEventListener('mouseleave', e => {
			squareHighlighter.clearHighlight(x,this.lt);
		});
	}	
	readCube(){
		var i = 0;
		var j = 0;
		var t=document.createElement("TABLE");
		var thead=t.createTHead();
		var tbody=t.createTBody();
		var thr=thead.insertRow();
		var tbr=tbody.insertRow();
		
		let td = document.createElement("td");
		t.style="font-size: 1.2em; line-height: .9em; border-collapse: collapse; cellpadding: 2px;";
		this.setBorderBottom(td)
		thr.appendChild(td);
		for(i=0;i<this.myDim;i++){
			let myst=i.toString();
			let th = document.createElement("th");
			let text = document.createTextNode(myst);
			this.setBorderBottom(th);
			th.appendChild(text);
			th.id="_"+i;
			this.lt.clu[i]=th;
			thr.appendChild(th);
			let tr=tbody.insertRow();
			th = document.createElement("th");
			th.id=i+"_";
			this.lt.rlu[i]=th;
			this.lt.lu[i]=[]
			this.setBorderBottom(th);
			text = document.createTextNode(myst);
			th.appendChild(text);
			tr.appendChild(th);
			for(j=0;j<this.myDim;j++){
				let zc=this.xy[i][j].toString();
				let td = tr.insertCell();
				let thtext = document.createTextNode(zc);
				this.setBorderBottom(td);
				td.appendChild(thtext);
				td.id=i+"_"+j;
				this.lt.lu[i][j]=td;
				tr.appendChild(td);
			}
		}
		return t;
	}
}