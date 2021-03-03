//#include <rc4Gen.js>
class wordMaker {
	constructor(inWurd, inFilterFlag, inWss){
		var i;
		var g="azjvcxoqjkoynrzlwpdsbdkmjhatyooqjidfcghumxlidflwfvzeotyqueivblcdypaluqoiatnxgoefhrknzeqtlkgxephrrglykbgbgldepmrhjsbgqqdffkjtlpzrjgvonvpeygkyfvqmtbegnjzompxcqafrpekfhjypynvdrrlccuavfbfwwas";
		var r=new rc4Gen(260);
		r.initBuffer("Sanitize");		
		this.filter=String.fromCharCode.apply(null,g.split('').map(x => (x.charCodeAt(0)-71-r.pump()%26)%26+97)).replace(/y/g,'.').replace(/x/g,'[').replace(/w/g,']').split('z').map(y => new RegExp(y));
		this.a = "badafagahajakalamanaparasatav".split('a'); 
		this.initial = "bablabradadrafaflafragaglagrahajakaklakralamanapaplaprarasaskaslasmasnaspastatatrav".split('a');
		this.myfinal = "badafaftagajakalalbaldalfalgaljalkalmalpaltalvamampamtanandankantapaptararbardarfargarjarkarmarnarpartarvaskastatav".split('a');
		this.vowels = "abebibobu".split('b');
		this.wss = inWss;
		this.intern = [
				"babdabfabgabjabkablabmabnabrabsabtabvabdrabflabfrabglabgrabklabkrabslabsmabsnabspabstabtradbadbladbradadfadgadjadkadladmadnadpad",
				"radsadvadfladfradgladgradkladkradpladpradsladsmadsnadspadstafbafblafbrafdafdrafafgafjafkaflafmafnafpafrafsaftafglafgrafklafkrafp",
				"lafprafslafsmafsnafspafstaftragbagblagbragdagdragfagflagfragagjaglagmagnagpagragsagtagvagplagpragslagsmagsnagspagstagtrahajbajbl",
				"ajbrajdajdrajfajflajfrajgajglajgrajajkajlajmajnajpajrajsajtajvajklajkrajplajprajslajsmajsnajspajstajtrakbakblakbrakdakdrakfakfla",
				"kfrakjakaklakmaknakpakraksaktakvakplakprakslaksmaksnakspakstaktralbalbdalbfalbgalbjalbkalblalbmalbnalbralbsalbtalbvaldbaldaldfal",
				"dgaldjaldkaldlaldmaldnaldpaldraldsaldvalfbalfdalfalfgalfjalfkalflalfmalfnalfpalfralfsalftalgbalgdalgfalgalgjalglalgmalgnalgpalgr",
				"algsalgtalgvaljbaljdaljfaljgaljaljkaljlaljmaljnaljpaljraljsaljtaljvalkbalkdalkfalkjalkalklalkmalknalkpalkralksalktalkvalalmalnal",
				"palsaltalvalmbalmdalmfalmgalmjalmkalmlalmnalmpalmralmsalmtalmvalnbalndalnfalngalnjalnkalnlalnmalnpalnralnsalntalnvalpdalpfalpgal",
				"pjalpkalplalpmalpnalpralpsalptalpvalsbalsdalsfalsgalsjalskalslalsmalsnalspalsralstalsvaltbaltfaltgaltjaltkaltlaltmaltnaltpaltral",
				"tsaltvalvbalvdalvgalvjalvkalvlalvmalvnalvpalvralvsalvtambamblambramdamdramfamflamframgamglamgramjamkamklamkramlamamnampamramsamt",
				"amvamplampramslamsmamsnamspamstamtranbanblanbrandandranfanflanfranganglangranjankanklankranlanmananpanransantanvanplanpranslansm",
				"ansnanspanstantrapdapdrapfapflapfrapgapglapgrapjapkapklapkraplapmapnapaprapsaptapvapslapsmapsnapspapstaptrarbarbdarbfarbgarbjarb",
				"karblarbmarbnarbrarbsarbtarbvardbardardfardgardjardkardlardmardnardpardrardsardvarfbarfdarfarfgarfjarfkarflarfmarfnarfparfrarfsa",
				"rftargbargdargfargargjarglargmargnargpargrargsargtargvarjbarjdarjfarjgarjarjkarjlarjmarjnarjparjrarjsarjtarjvarkbarkdarkfarkjark",
				"arklarkmarknarkparkrarksarktarkvarmbarmdarmfarmgarmjarmkarmlarmarmnarmparmrarmsarmtarmvarnbarndarnfarngarnjarnkarnlarnmarnarnpar",
				"nrarnsarntarnvarpdarpfarpgarpjarpkarplarpmarpnarparprarpsarptarpvararsartarvarsbarsdarsfarsgarsjarskarslarsmarsnarsparsrarstarsv",
				"artbartfartgartjartkartlartmartnartpartrartsartvarvbarvdarvgarvjarvkarvlarvmarvnarvparvrarvsarvtasbasblasbrasdasdrasfasflasfrasg",
				"asglasgrasjaskasklaskraslasmasnasplaspasprasrasastasvastratbatblatbratfatflatfratgatglatgratjatkatklatkratlatmatnatplatpatpratra",
				"tslatsmatsnatspatsatstatatvavbavblavbravdavdravgavglavgravjavkavklavkravlavmavnavplavpavpravravslavsmavsnavspavsavstavtravtav"
				].join('').split('a');
		this.vowlGen=this.setRg(this.vowels.length,inWurd);
		this.finGen=this.setRg(this.myfinal.length+3,inWurd);
		this.iniGen=this.setRg(this.initial.length+1,inWurd);
		this.ternGen=this.setRg(this.intern.length,inWurd);
		this.wssGen=this.setRg(this.wss.length,inWurd);
		this.filterFlag=inFilterFlag;
	}
	
	makeWords(e){
		return e.map(x => this.makeSingleWord(x));
	}
	
	setRg(e,inWurd){
		var l=512;
		var rg;
		if (e>l){
			l=e;
		} else {			
			while(l%e>0){
				l--;
			}
		}
		rg= new rc4Gen(l);
		rg.initBuffer(inWurd);
		return rg;
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
		t%=this.wss.length;
		ws = this.wss[t];
		dx=this.iniGen.pump();
		dx%=(this.initial.length+1);
		if(dx<this.initial.length){
			magicWord += this.initial[dx];
		}
		for(i=0;i<ws;i++){
			t=this.vowlGen.pump();
			t %= this.vowels.length;
			magicWord += this.vowels[t];
			t = this.ternGen.pump();
			magicWord += this.intern[t];
		}
		t=this.vowlGen.pump();
		t %= this.vowels.length;
		magicWord += this.vowels[t];
		dx = this.finGen.pump();
		dx %= (this.myfinal.length+3);
		if(dx<this.myfinal.length){
			magicWord += this.myfinal[dx];
		}
		return magicWord;
	}
}

