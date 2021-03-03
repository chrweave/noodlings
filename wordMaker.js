//#include <rc4Gen.js>
class wordMaker {
	constructor(inWurd, inFilterFlag, inWss){
		var g = "azjvcxoqjkoynrzlwpdsbdkmjhatyooqjidfcghumxlidflwfvzeotyqueivblcdypaluqoiatnxgoefhrknzeqtlkgxephrrglykbgbgldepmrhjsbgqqdffkjweapb"+
				"ujhesafphrteyeduldtumtugcgavdekkqxkejgqalbbiszcarevtznxgocitrgdssxoxcmjwjxtdqdudowwgipkk";
		var h= "babdabfabgabjabkablabmabnabrabsabtabvabdrabflabfrabglabgrabklabkrabslabsmabsnabspabstabtradbadbladbradadfadgadjadkadladmadnadpad"+
				"radsadvadfladfradgladgradkladkradpladpradsladsmadsnadspadstafbafblafbrafdafdrafafgafjafkaflafmafnafpafrafsaftafglafgrafklafkrafp"+
				"lafprafslafsmafsnafspafstaftragbagblagbragdagdragfagflagfragagjaglagmagnagpagragsagtagvagplagpragslagsmagsnagspagstagtrahajbajbl"+
				"ajbrajdajdrajfajflajfrajgajglajgrajajkajlajmajnajpajrajsajtajvajklajkrajplajprajslajsmajsnajspajstajtrakbakblakbrakdakdrakfakfla"+
				"kfrakjakaklakmaknakpakraksaktakvakplakprakslaksmaksnakspakstaktralbalbdalbfalbgalbjalbkalblalbmalbnalbralbsalbtalbvaldbaldaldfal"+
				"dgaldjaldkaldlaldmaldnaldpaldraldsaldvalfbalfdalfalfgalfjalfkalflalfmalfnalfpalfralfsalftalgbalgdalgfalgalgjalglalgmalgnalgpalgr"+
				"algsalgtalgvaljbaljdaljfaljgaljaljkaljlaljmaljnaljpaljraljsaljtaljvalkbalkdalkfalkjalkalklalkmalknalkpalkralksalktalkvalalmalnal"+
				"palsaltalvalmbalmdalmfalmgalmjalmkalmlalmnalmpalmralmsalmtalmvalnbalndalnfalngalnjalnkalnlalnmalnpalnralnsalntalnvalpdalpfalpgal"+
				"pjalpkalplalpmalpnalpralpsalptalpvalsbalsdalsfalsgalsjalskalslalsmalsnalspalsralstalsvaltbaltfaltgaltjaltkaltlaltmaltnaltpaltral"+
				"tsaltvalvbalvdalvgalvjalvkalvlalvmalvnalvpalvralvsalvtambamblambramdamdramfamflamframgamglamgramjamkamklamkramlamamnampamramsamt"+
				"amvamplampramslamsmamsnamspamstamtranbanblanbrandandranfanflanfranganglangranjankanklankranlanmananpanransantanvanplanpranslansm"+
				"ansnanspanstantrapdapdrapfapflapfrapgapglapgrapjapkapklapkraplapmapnapaprapsaptapvapslapsmapsnapspapstaptrarbarbdarbfarbgarbjarb"+
				"karblarbmarbnarbrarbsarbtarbvardbardardfardgardjardkardlardmardnardpardrardsardvarfbarfdarfarfgarfjarfkarflarfmarfnarfparfrarfsa"+
				"rftargbargdargfargargjarglargmargnargpargrargsargtargvarjbarjdarjfarjgarjarjkarjlarjmarjnarjparjrarjsarjtarjvarkbarkdarkfarkjark"+
				"arklarkmarknarkparkrarksarktarkvarmbarmdarmfarmgarmjarmkarmlarmarmnarmparmrarmsarmtarmvarnbarndarnfarngarnjarnkarnlarnmarnarnpar"+
				"nrarnsarntarnvarpdarpfarpgarpjarpkarplarpmarpnarparprarpsarptarpvararsartarvarsbarsdarsfarsgarsjarskarslarsmarsnarsparsrarstarsv"+
				"artbartfartgartjartkartlartmartnartpartrartsartvarvbarvdarvgarvjarvkarvlarvmarvnarvparvrarvsarvtasbasblasbrasdasdrasfasflasfrasg"+
				"asglasgrasjaskasklaskraslasmasnasplaspasprasrasastasvastratbatblatbratfatflatfratgatglatgratjatkatklatkratlatmatnatplatpatpratra"+
				"tslatsmatsnatspatsatstatatvavbavblavbravdavdravgavglavgravjavkavklavkravlavmavnavplavpavpravravslavsmavsnavspavsavstavtravtav";
		var r=new rc4Gen(260);
		r.initBuffer("Sanitize");		
		this.filter=String.fromCharCode.apply(null,g.split('')
				.map(x => (x.charCodeAt(0)-71-r.pump()%26)%26+97))
				.replace(/y/g,'.').replace(/x/g,'[').replace(/w/g,']').split('z').map(y => new RegExp(y));
		this.initial = "bablabradadrafaflafragaglagrahajakaklakralamanapaplaprarasaskaslasmasnaspastatatrav".split('a');
		this.myfinal = "badafaftagajakalalbaldalfalgaljalkalmalpaltalvamampamtanandankantapaptararbardarfargarjarkarmarnarpartarvaskastatav".split('a');
		this.vowels = "abebibobu".split('b');
		this.wss = inWss;
		this.intern = h.split('a');
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
		if (e>l){
			l=e;
		} else {			
			while(l%e>0){
				l--;
			}
		}
		var rg= new rc4Gen(l);
		rg.initBuffer(inWurd);
		return rg;
	}	
	forbidden(q){
		return this.filterFlag > 0 && this.filter.map(x => x.test(q)).reduce((acc, li) => acc || li, false);
	}	
	makeSingleWord(capvar){
		var m;
		do{
			m=this.getTrialWord();
		} while (this.forbidden(m));
		return capvar == 0 ? m.charAt(0).toUpperCase() + m.slice(1) : m;
	}		
	getTrialWord(){
		var ws,t,i,m = "";		
		t=this.wssGen.pump()%this.wss.length;
		ws = this.wss[t];
		t=this.iniGen.pump()%(this.initial.length+1);
		if(t<this.initial.length){
			m += this.initial[t];
		}
		for(i=0;i<ws;i++){
			t=this.vowlGen.pump()%this.vowels.length;
			m += this.vowels[t];
			t = this.ternGen.pump();
			m += this.intern[t];
		}
		t=this.vowlGen.pump()%this.vowels.length;
		m += this.vowels[t];
		t = this.finGen.pump()%(this.myfinal.length+3);
		if(t<this.myfinal.length){
			m += this.myfinal[t];
		}
		return m;
	}
}

