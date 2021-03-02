//#include <rc4Gen.js>
class wordMaker {
	a;
	initial;
	myfinal;
	vowels;
	wss;
	intern;
	plnmt;
	bdfgkpt;
	rl;
	bfgkp;
	seen;
	lim;
	lin;
	lfn;
	lvs;
	lws;
	vowlGen;
	finGen;
	iniGen;
	ternGen;
	wssGen;
	filter;
	filterFlag;

	constructor(inWurd, inFilterFlag, inWss){
		var i;
		this.a = [ "b", "d", "f", "g", "h", "j", "k", "l", "m", "n", "p", "r", "s", "t", "v"]; 
		this.initial = [ "b", "bl", "br", "d", "dr", "f", "fl", "fr", "g", "gl", "gr", "h", "j", "k", "kl", "kr", "l", "m", "n", "p", "pl", "pr", "r", "s", "sk", "sl", "sm", "sn", "sp", "st", "t", "tr", "v"];
		this.myfinal = ["b", "d", "f", "ft", "g", "j", "k", "l", "lb", "ld", "lf", "lg", "lj", "lk", "lm", "lp", "lt", "lv", "m", "mp", "mt", "n", "nd", "nk", "nt", "p", "pt", "r", "rb", "rd", "rf", "rg", "rj", "rk", "rm", "rn", "rp", "rt", "rv", "sk", "st", "t", "v"];
		this.vowels = ["a","e","i","o","u"];
		this.wss = inWss;
		this.intern = [];
		this.plnmt = new Set(['p','l','n','m','t']);
		this.bdfgkpt = new Set(['b','d','f','g','k','p','t']);
		this.rl = new Set(['r','l']);
		this.bfgkp = new Set(['b','f','g','k','p']);
		this.seen = new Set([]);
		this.lim = this.intern.length;
		this.lin = this.initial.length;
		this.lfn = this.myfinal.length;
		this.lvs = this.vowels.length;
		this.lws = this.wss.length;
		this.vowlGen=new rc4Gen(this.getRgBound(this.lvs));
		this.finGen=new rc4Gen(this.getRgBound(this.lfn+3));
		this.iniGen=new rc4Gen(this.getRgBound(this.lin+1));
		this.ternGen=new rc4Gen(this.getRgBound(this.lim));
		this.wssGen=new rc4Gen(this.getRgBound(this.lws));
		this.vowlGen.initBuffer(inWurd);
		this.finGen.initBuffer(inWurd);
		this.iniGen.initBuffer(inWurd);
		this.ternGen.initBuffer(inWurd);
		this.wssGen.initBuffer(inWurd);
		this.filterFlag=inFilterFlag;
		for(i=0;i<this.a.length;i++){
			var j;
			for(j=0;j<this.a.length;j++){
				var k;
				for(k=0;k<this.a.length;k++){
					this.processIndices(i,j,k);
				}
			}
		}
		var g="azjvcxoqjkkynrzlwpdsbdkmjhatyooqjidfcghumxlidflwfvzeotyqueivblcdypaluqoiatnxgoefhrknzeqtlkgxephrrglykbgbgldepmrhjsbgqqdffzqbewsdifvuhxty";
		var r=new rc4Gen(260);
		r.initBuffer("Sanitize");		
		this.filter=String.fromCharCode.apply(null,g.split('').map(x => (x.charCodeAt(0)-71-r.pump()%26)%26+97)).split('z').map(y => new RegExp(y));
	}
	
	makeWords(e){
		return e.map(x => this.makeSingleWord(x));
	}
	
	getRgBound(e){
		var i=512;
		if (e>i){
			i=e;
		} else {			
			while(i%e>0){
				i--;
			}
		}
		return i;
	}
	
	forbidden(q){
		return this.filterFlag > 0 && this.filter.map(x => x.test(q)).reduce((acc, li) => acc || li, false);
	}
	
	makeSingleWord(capvar){
		var magicWord;
		do{
			magicWord=this.makeWordFast();
		} while (this.forbidden(magicWord));
		return capvar == 0 ? magicWord.charAt(0).toUpperCase() + magicWord.slice(1) : magicWord;
	}
		
	makeWordFast(){
		var ws = 0;
		var dx = 0;
		var i = 0;
		var magicWord = "";
		var t;
		
		t=this.wssGen.pump();
		t%=this.lws;
		ws = this.wss[t];
		dx=this.iniGen.pump();
		dx%=(this.lin+1);
		if(dx<this.lin){
			magicWord += this.initial[dx];
		}
		for(i=0;i<ws;i++){
			t=this.vowlGen.pump();
			t %= this.lvs;
			magicWord += this.vowels[t];
			t = this.ternGen.pump();
			magicWord += this.intern[t];
		}
		t=this.vowlGen.pump();
		t %= this.lvs;
		magicWord += this.vowels[t];
		dx = this.finGen.pump();
		dx %= (this.lfn+3);
		if(dx<this.lfn){
			magicWord += this.myfinal[dx];
		}
		return magicWord;
	}
	
	processIndices(i,j,k){
		var indices = [i, j, k];
		var myString;
		if (this.tripleInspectable(indices)){
			if (this.isNotForbiddenAllPairs(indices)){
				if (i==j){
					if(j==k){
							myString=this.a[i];
					} else {
						myString=this.a[i]+this.a[k];
					}  
				} else if (j==k) {
					myString=this.a[i]+this.a[k];
				} else {
					myString=this.a[i]+this.a[j]+this.a[k];
				}
				if(!this.seen.has(myString)){
					this.seen.add(myString);
					this.intern.push(myString);
				} 
			}  
		}
		return true;
	}
	
	isNotForbiddenAllPairs(indices){
		var ret = true;
		var pairs = ["td","vf","pb","gk","rl"];
		var i;
		for(i=0;i<pairs.length;i++){    
			var con = pairs[i].split('');
			ret = ret && this.isAllowedPair(indices,con);
		}
		ret = ret && this.a[indices[0]] != 'h';
		ret = ret && this.a[indices[1]] != 'h';
		ret = ret && this.a[indices[2]] != 'h';
		ret = ret || (indices[0] == indices[1] && indices[1] == indices[2])
		return ret;
	}
	
	isAllowedPair(indices, con){
		var q;
		var ret = true;
		
		for(q=0;q<2;q++){
			var r;
			for(r=0;r<2;r++){
				if(this.a[indices[q]] == con[r]){
					if(this.a[indices[q+1]] == con[1-r]){
						ret = false;
					}
				}
			}
		}    
		return ret;
	}
	
	tripleInspectable(indices){
		var ret = false;
			
		ret = ret || (this.a[indices[1]]=='s' && this.plnmt.has(this.a[indices[2]]));
		ret = ret || this.rl.has(this.a[indices[0]]);
		ret = ret || (this.a[indices[2]]=='r' && this.bdfgkpt.has(this.a[indices[1]]));
		ret = ret || (this.a[indices[2]]=='l' && this.bfgkp.has(this.a[indices[1]]));
		ret = ret || indices[0] == indices[1];  
		ret = ret || indices[1] == indices[2];
		return ret;
	}
	
}

