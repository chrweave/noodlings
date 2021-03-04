//#include <rc4Gen.js>
class partMaker {
	constructor(inWurd,inArray,delim,modPlus){
		var p=modPlus;
		if (delim ==0){
			this.palette=inArray;
			p=0;
		} else {
			this.palette=inArray.split(delim);
		}
		var l=this.palette.length;
		this.lim=[l,l+p];
		this.gen=this.setRg(l+p,inWurd);
	}
	getPart(){
		var t=this.gen.pump()%this.lim[1];
		var u;
		if (t<this.lim[0]){
			u=this.palette[t];
		} else {
			u="";
		}
		return u;
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
}
class wordMaker {
	constructor(inWurd, inWss){
		var a =	"azjvcxoqjkoynrzlwpdsbdkmjhatyooqjidfcghumxlidflwfvzeotyqueivblcdypaluqoiatnxgoefhrknzeqtlkgxephrrglykbgbgldepmrhjsbgqqdffkjweapb"+
				"ujhesafphrteyeduldtumtugcgavdekkqxkejgqalbbiszcarevtznxgocitrgdssxoxcmjwjxtdqdudowwgipkkeumjvkfxei";
		var b=	"babdabfabgabjabkablabmabnabrabsabtabvabdrabflabfrabglabgrabklabkrabslabsmabsnabspabstabtradbadbladbradadfadgadjadkadladmadnadpad"+
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
		var c = "bablabradadrafaflafragaglagrahajakaklakralamanapaplaprarasaskaslasmasnaspastatatrav";
		var d = "badafaftagajakalalbaldalfalgaljalkalmalpaltalvamampamtanandankantapaptararbardarfargarjarkarmarnarpartarvaskastatav";
		var e = "abebibobu";
		var f = "badafagajakalamanaparasatav";
		var r = new rc4Gen(260);
		this.wss = new partMaker(inWurd,inWss,0,0);
		this.intern     = new partMaker(inWurd,b,'a',0);
		this.initials   = new partMaker(inWurd,c,'a',1);
		this.finals     = new partMaker(inWurd,d,'a',3);
		this.vowels     = new partMaker(inWurd,e,'b',0);
		this.pragmatics = new partMaker(inWurd,f,'a',0);
		r.initBuffer("Sanitize");		
		this.filter=String.fromCharCode.apply(null,a.split('')
				.map(x => (x.charCodeAt(0)-71-r.pump()%26)%26+97))
				.replace(/y/g,'.').replace(/x/g,'[').replace(/w/g,']').split('z').map(y => new RegExp(y));
	}	
	makeWords(e){
		return e.map(x => this.makeSingleWord(x));
	}	
	makeSingleWord(capvar){
		var m;
		do{
			m=this.getTrialWord();
		} while (this.filter.map(x => x.test(m)).reduce((acc, li) => acc || li, false));
		return capvar == 0 ? m.charAt(0).toUpperCase() + m.slice(1) : m;
	}		
	getTrialWord(){
		var ws = this.wss.getPart();
		var i;
		var m = this.initials.getPart();
		for(i=0;i<ws;i++){
			m += this.vowels.getPart()+this.intern.getPart();
		}
		m += this.vowels.getPart()+this.finals.getPart();
		return m.replace(/[lr][iou][lr][bdfgjkmnpstv]/g, 
				x => x[0]+x[1]+this.pragmatics.getPart()+this.vowels.getPart()+x[2]+x[3]
				);
	}
}

