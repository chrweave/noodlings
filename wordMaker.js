//#include <rc4Gen.js>
class partMaker {
	constructor(inWurd,inArray,delim,modPlus){
		this.palette = delim ==0?inArray:inArray.split(delim);
		var l=this.palette.length, p=delim==0?l:l+modPlus, o= p>512?p:p*Math.floor(512/p);
		this.lim=[l,p];
		this.gen=new rc4Gen(o);
		this.gen.initBuffer(inWurd);
	}
	getPart(){
		var t=this.gen.pump()%this.lim[1];
		return t<this.lim[0]?this.palette[t]:"";
	}
}
class wordMaker {
	constructor(inWurd, inWss, myHyphen){
		var a =	
"imyngegxsqvnpmqkwirphhimecamivzuoxoutwoqjnbppxpffifyotlhdobphlxtfmukzqfsbetyvhbaatlzbeteaahyzznl"+
"naveotdbybetbyillhrhvnsqvrzlymlvnalhlkatufxfggouxqrjarmzxuvmjafsvxdjwfrjgcowbaktcdlomomzlvsfzwqh"+
"faezaoypwugaxwwytcmybxddybqjdovkmfvyoegpulmofv"
		var b=	
"babqdabqfabqgabqjabqkabqlabqmabqnabqrabqsabqtabqvabqdrabqflabqfrabqglabqgrabqklabqkrabqslabqsmab"+
"qsnabqspabqstabqtradqbadqbladqbradadqfadqgadqjadqkadqladqmadqnadqpadqradqsadqvadqfladqfradqgladq"+
"gradqkladqkradqpladqpradqsladqsmadqsnadqspadqstafqbafqblafqbrafqdafqdrafafqgafqjafqkafqlafqmafqn"+
"afqpafqrafqsafqtafqglafqgrafqklafqkrafqplafqprafqslafqsmafqsnafqspafqstafqtragqbagqblagqbragqdag"+
"qdragqfagqflagqfragagqjagqlagqmagqnagqpagqragqsagqtagqvagqplagqpragqslagqsmagqsnagqspagqstagqtra"+
"hajqbajqblajqbrajqdajqdrajqfajqflajqfrajqgajqglajqgrajajqkajqlajqmajqnajqpajqrajqsajqtajqvajqkla"+
"jqkrajqplajqprajqslajqsmajqsnajqspajqstajqtrakqbakqblakqbrakqdakqdrakqfakqflakqfrakqjakakqlakqma"+
"kqnakqpakqrakqsakqtakqvakqplakqprakqslakqsmakqsnakqspakqstakqtralqbalbqdalbqfalbqgalbqjalbqkalqb"+
"lalbqmalbqnalqbralbqsalbqtalbqvaldqbalqdaldqfaldqgaldqjaldqkaldqlaldqmaldqnaldqpalqdraldqsaldqva"+
"lfqbalfqdalqfalfqgalfqjalfqkalqflalfqmalfqnalfqpalqfralfqsalfqtalgqbalgqdalgqfalqgalgqjalqglalgq"+
"malgqnalgqpalqgralgqsalgqtalgqvaljqbaljqdaljqfaljqgalqjaljqkaljqlaljqmaljqnaljqpaljqraljqsaljqta"+
"ljqvalkqbalkqdalkqfalkqjalqkalqklalkqmalkqnalkqpalqkralkqsalkqtalkqvalalqmalqnalqpalqsalqtalqval"+
"mqbalmqdalmqfalmqgalmqjalmqkalmqlalmqnalmqpalmqralmqsalmqtalmqvalnqbalnqdalnqfalnqgalnqjalnqkaln"+
"qlalnqmalnqpalnqralnqsalnqtalnqvalpqdalpqfalpqgalpqjalpqkalqplalpqmalpqnalqpralpqsalpqtalpqvalsq"+
"balsqdalsqfalsqgalsqjalqskalqslalqsmalqsnalqspalsqralqstalsqvaltqbaltqfaltqgaltqjaltqkaltqlaltqm"+
"altqnaltqpalqtraltqsaltqvalvqbalvqdalvqgalvqjalvqkalvqlalvqmalvqnalvqpalvqralvqsalvqtamqbamqblam"+
"qbramqdamqdramqfamqflamqframqgamqglamqgramqjamqkamqklamqkramqlamamqnamqpamqramqsamqtamqvamqplamq"+
"pramqslamqsmamqsnamqspamqstamqtranqbanqblanqbranqdanqdranqfanqflanqfranqganqglanqgranqjanqkanqkl"+
"anqkranqlanqmananqpanqranqsanqtanqvanqplanqpranqslanqsmanqsnanqspanqstanqtrapqdapqdrapqfapqflapq"+
"frapqgapqglapqgrapqjapqkapqklapqkrapqlapqmapqnapapqrapqsapqtapqvapqslapqsmapqsnapqspapqstapqtrar"+
"qbarbqdarbqfarbqgarbqjarbqkarqblarbqmarbqnarqbrarbqsarbqtarbqvardqbarqdardqfardqgardqjardqkardql"+
"ardqmardqnardqparqdrardqsardqvarfqbarfqdarqfarfqgarfqjarfqkarqflarfqmarfqnarfqparqfrarfqsarfqtar"+
"gqbargqdargqfarqgargqjarqglargqmargqnargqparqgrargqsargqtargqvarjqbarjqdarjqfarjqgarqjarjqkarjql"+
"arjqmarjqnarjqparjqrarjqsarjqtarjqvarkqbarkqdarkqfarkqjarqkarqklarkqmarkqnarkqparqkrarkqsarkqtar"+
"kqvarmqbarmqdarmqfarmqgarmqjarmqkarmqlarqmarmqnarmqparmqrarmqsarmqtarmqvarnqbarnqdarnqfarnqgarnq"+
"jarnqkarnqlarnqmarqnarnqparnqrarnqsarnqtarnqvarpqdarpqfarpqgarpqjarpqkarqplarpqmarpqnarqparqprar"+
"pqsarpqtarpqvararqsarqtarqvarsqbarsqdarsqfarsqgarsqjarsqkarqslarqsmarqsnarqsparsqrarqstarsqvartq"+
"bartqfartqgartqjartqkartqlartqmartqnartqparqtrartqsartqvarvqbarvqdarvqgarvqjarvqkarvqlarvqmarvqn"+
"arvqparvqrarvqsarvqtasqbasqblasqbrasqdasqdrasqfasqflasqfrasqgasqglasqgrasqjasqkasqklasqkrasqlasq"+
"masqnasqplasqpasqprasqrasasqtasqvasqtratqbatqblatqbratqfatqflatqfratqgatqglatqgratqjatqkatqklatq"+
"kratqlatqmatqnatqplatqpatqpratqratqslatqsmatqsnatqspatqsatqstatatqvavqbavqblavqbravqdavqdravqgav"+
"qglavqgravqjavqkavqklavqkravqlavqmavqnavqplavqpavqpravqravqslavqsmavqsnavqspavqsavqstavqtravqtav";

		var c = "bablabradadrafaflafragaglagrahajakaklakralamanapaplaprarasaskaslasmasnaspastatatrav";
		var d = 
"badafaftagajakalalbaldalfalgaljalkalmalpaltalvamampamtanandankantapaptararbardarfargarjarkarmarna"+
"rpartarvaskastatav";
		
		var e = "abebibobu";
		var r = new rc4Gen(260);
		this.wss		= new partMaker(inWurd,inWss,0,0);
		this.intern	 = new partMaker(inWurd,b,'a',0);
		this.initials   = new partMaker(inWurd,c,'a',1);
		this.finals	 = new partMaker(inWurd,d,'a',3);
		this.vowels	 = new partMaker(inWurd,e,'b',0);
		this.myHyphen=myHyphen;
		r.initBuffer("Sanitize");		
		this.filter=String.fromCharCode.apply(null,a.split('')
				.map(x => (x.charCodeAt(0)-71-r.pump()%26)%26+97))
				.replace(/y/g,'.').replace(/x/g,'[').replace(/w/g,']').split('z').map(y => new RegExp(y));
	}	
	makeWords(e){
		return e.map(x => this.makeSingleWord(x));
	}	
	makeSingleWord(capvar){
		var l;
		var n;
		do{
			l=this.getTrialWord();
			n=l.replace(/q/g,"");
		} while (this.filter.map(x => x.test(n)).reduce((acc, li) => acc || li, false));
		 var m=l.replace(/q/g,this.myHyphen);		
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
		return m;
	}
}
