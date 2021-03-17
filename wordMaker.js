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
"b b_d b_f b_g b_j b_k b_l b_m b_n b_r b_s b_t b_v b_dr b_fl b_fr b_gl b_gr b_kl b_kr b_sl b_sm b"+
"_sn b_sp b_st b_tr d_b d_bl d_br d d_f d_g d_j d_k d_l d_m d_n d_p d_r d_s d_v d_fl d_fr d_gl d_"+
"gr d_kl d_kr d_pl d_pr d_sl d_sm d_sn d_sp d_st f_b f_bl f_br f_d f_dr f f_g f_j f_k f_l f_m f_n"+
" f_p f_r f_s f_t f_gl f_gr f_kl f_kr f_pl f_pr f_sl f_sm f_sn f_sp f_st f_tr g_b g_bl g_br g_d g"+
"_dr g_f g_fl g_fr g g_j g_l g_m g_n g_p g_r g_s g_t g_v g_pl g_pr g_sl g_sm g_sn g_sp g_st g_tr "+
"h j_b j_bl j_br j_d j_dr j_f j_fl j_fr j_g j_gl j_gr j j_k j_l j_m j_n j_p j_r j_s j_t j_v j_kl "+
"j_kr j_pl j_pr j_sl j_sm j_sn j_sp j_st j_tr k_b k_bl k_br k_d k_dr k_f k_fl k_fr k_j k k_l k_m "+
"k_n k_p k_r k_s k_t k_v k_pl k_pr k_sl k_sm k_sn k_sp k_st k_tr l_b lb_d lb_f lb_g lb_j lb_k l_b"+
"l lb_m lb_n l_br lb_s lb_t lb_v ld_b l_d ld_f ld_g ld_j ld_k ld_l ld_m ld_n ld_p l_dr ld_s ld_v "+
"lf_b lf_d l_f lf_g lf_j lf_k l_fl lf_m lf_n lf_p l_fr lf_s lf_t lg_b lg_d lg_f l_g lg_j l_gl lg_"+
"m lg_n lg_p l_gr lg_s lg_t lg_v lj_b lj_d lj_f lj_g l_j lj_k lj_l lj_m lj_n lj_p lj_r lj_s lj_t "+
"lj_v lk_b lk_d lk_f lk_j l_k l_kl lk_m lk_n lk_p l_kr lk_s lk_t lk_v l l_m l_n l_p l_s l_t l_v l"+
"m_b lm_d lm_f lm_g lm_j lm_k lm_l lm_n lm_p lm_r lm_s lm_t lm_v ln_b ln_d ln_f ln_g ln_j ln_k ln"+
"_l ln_m ln_p ln_r ln_s ln_t ln_v lp_d lp_f lp_g lp_j lp_k l_pl lp_m lp_n l_pr lp_s lp_t lp_v ls_"+
"b ls_d ls_f ls_g ls_j l_sk l_sl l_sm l_sn l_sp ls_r l_st ls_v lt_b lt_f lt_g lt_j lt_k lt_l lt_m"+
" lt_n lt_p l_tr lt_s lt_v lv_b lv_d lv_g lv_j lv_k lv_l lv_m lv_n lv_p lv_r lv_s lv_t m_b m_bl m"+
"_br m_d m_dr m_f m_fl m_fr m_g m_gl m_gr m_j m_k m_kl m_kr m_l m m_n m_p m_r m_s m_t m_v m_pl m_"+
"pr m_sl m_sm m_sn m_sp m_st m_tr n_b n_bl n_br n_d n_dr n_f n_fl n_fr n_g n_gl n_gr n_j n_k n_kl"+
" n_kr n_l n_m n n_p n_r n_s n_t n_v n_pl n_pr n_sl n_sm n_sn n_sp n_st n_tr p_d p_dr p_f p_fl p_"+
"fr p_g p_gl p_gr p_j p_k p_kl p_kr p_l p_m p_n p p_r p_s p_t p_v p_sl p_sm p_sn p_sp p_st p_tr r"+
"_b rb_d rb_f rb_g rb_j rb_k r_bl rb_m rb_n r_br rb_s rb_t rb_v rd_b r_d rd_f rd_g rd_j rd_k rd_l"+
" rd_m rd_n rd_p r_dr rd_s rd_v rf_b rf_d r_f rf_g rf_j rf_k r_fl rf_m rf_n rf_p r_fr rf_s rf_t r"+
"g_b rg_d rg_f r_g rg_j r_gl rg_m rg_n rg_p r_gr rg_s rg_t rg_v rj_b rj_d rj_f rj_g r_j rj_k rj_l"+
" rj_m rj_n rj_p rj_r rj_s rj_t rj_v rk_b rk_d rk_f rk_j r_k r_kl rk_m rk_n rk_p r_kr rk_s rk_t r"+
"k_v rm_b rm_d rm_f rm_g rm_j rm_k rm_l r_m rm_n rm_p rm_r rm_s rm_t rm_v rn_b rn_d rn_f rn_g rn_"+
"j rn_k rn_l rn_m r_n rn_p rn_r rn_s rn_t rn_v rp_d rp_f rp_g rp_j rp_k r_pl rp_m rp_n r_p r_pr r"+
"p_s rp_t rp_v r r_s r_t r_v rs_b rs_d rs_f rs_g rs_j rs_k r_sl r_sm r_sn r_sp rs_r r_st rs_v rt_"+
"b rt_f rt_g rt_j rt_k rt_l rt_m rt_n rt_p r_tr rt_s rt_v rv_b rv_d rv_g rv_j rv_k rv_l rv_m rv_n"+
" rv_p rv_r rv_s rv_t s_b s_bl s_br s_d s_dr s_f s_fl s_fr s_g s_gl s_gr s_j s_k s_kl s_kr s_l s_"+
"m s_n s_pl s_p s_pr s_r s s_t s_v s_tr t_b t_bl t_br t_f t_fl t_fr t_g t_gl t_gr t_j t_k t_kl t_"+
"kr t_l t_m t_n t_pl t_p t_pr t_r t_sl t_sm t_sn t_sp t_s t_st t t_v v_b v_bl v_br v_d v_dr v_g v"+
"_gl v_gr v_j v_k v_kl v_kr v_l v_m v_n v_pl v_p v_pr v_r v_sl v_sm v_sn v_sp v_s v_st v_tr v_t v";
		var c = "bablabradadrafaflafragaglagrahajakaklakralamanapaplaprarasaskaslasmasnaspastatatrav";
		var d = 
"badafaftagajakalalbaldalfalgaljalkalmalpaltalvamampamtanandankantapaptararbardarfargarjarkarmarna"+
"rpartarvaskastatav";		
		var e = "abebibobu";
		var r = new rc4Gen(260);
		this.wss		= new partMaker(inWurd,inWss,0,0);
		this.intern	 = new partMaker(inWurd,b,' ',0);
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
			n=l.replace(/_/g,"");
		} while (this.filter.map(x => x.test(n)).reduce((acc, li) => acc || li, false));
		 var m=l.replace(/_/g,this.myHyphen);		
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

