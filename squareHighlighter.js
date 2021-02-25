class squareHighlighter{	
	static parseTid(x,y){
		var k=x.id.split('_').map(z => parseInt(z)).map( w => isNaN(w)?-2:w);
		y[0]=k[0];
		y[1]=k[1];
		if(k.length==3){
			y[1]=k[2];
		}
	}
	
	static clearHighlight(x,lt){
		var y=[0,0];
		var i;
		squareHighlighter.parseTid(x,y);
		if(y[0] > -1 && y[1] > -1){
			lt.rlu[y[0]].style.background="";
			lt.clu[y[1]].style.background="";
			lt.lu[y[0]][y[1]].style.background="";
			for(i=0;i<y[1];i++){
				lt.lu[y[0]][i].style.background="";
			}
			for(i=0;i<y[0];i++){
				lt.lu[i][y[1]].style.background="";
			}
		} else {
			x.style.background="";
		}				
	}
	
	static highlight(x,lt){
		var y=[0,0];
		var i;
		squareHighlighter.parseTid(x,y);
		if((y[0] > -1) && y[1] > -1){
			lt.rlu[y[0]].style.background="Lime";
			lt.clu[y[1]].style.background="Lime";
			lt.lu[y[0]][y[1]].style.background="DeepPink";
			for(i=0;i<y[1];i++){
				lt.lu[y[0]][i].style.background="Lime";
			}
			for(i=0;i<y[0];i++){
				lt.lu[i][y[1]].style.background="Lime";
			}
		} else {
			x.style.background="DeepPink";
		}
		
	}
}