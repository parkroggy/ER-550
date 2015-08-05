#include  <stdio.h>
#include  <er1io51.h>
#include  <er1exmt.h>
#ifndef BCDBG
#include  <exs03.h>
#else                                  /* BCDBG */
#include  <exdbg.h>
#endif                                 /* BCDBG */


extern const UBYTE s_deptpd[8];
extern const UBYTE s_plupd[7];
extern const UBYTE s_galcnt[8];
extern const UBYTE s_galamt[8];
extern const UBYTE s_ltrcnt[8];
extern const UBYTE s_ltramt[8];
extern const UBYTE s_eprice[12];

extern void adcntl(int dd);
extern void ban_olim();
extern void cal_multi(long long1, char d1, long long2_1, long long2_2, char d2);
extern void cal_divi(long long1_1, long long1_2, char d1, long long2, char d2);
extern void prn_com(char type);
extern void des_prn();
extern void desc2pbuf();
//PKR0624 extern void initseq();
extern void mkdeach(char type);
extern void mkfunc();
extern void mkdsp();
extern void mkdnur(char inf);
extern void make_desc(char *temps,char max);
extern void logo_only(char type);
//PKR0624 extern void loadseq();
extern void load_dstat();
extern void load_pstat();
extern void load_dpstat();
//PKR0624 extern void outdtx();
extern void prn_gcpt(char type,char dec,char lcd_f);
extern void pow10(char ii);
extern void prn_fdec(char dec,char type);
extern void prn_dtlogo(char tax_inf);
extern void prn_plucode(char st_code,char type);
extern void r_tender();
//PKR0624 extern void saveseq();
extern void sep_prn();
extern void taxselc();
extern void tbl_clr(char tinx);
extern void price_view(char type);
extern void wait_pover();
extern void mk_idmsg( unsigned char *desc, long amt, UBYTE stay, UBYTE sp);
extern long round_func(char sys_no,long value,char frac);
extern void sv_lcd();
extern void lcd_rec(char type);
extern void pop_menu(unsigned char *msg, unsigned char ch);
extern void prn_sfd(unsigned int kfunc,unsigned char ch);
extern void pmemcpy(UBYTE *, UBYTE *, unsigned int);
extern void per_taxcali();
extern char halo_err(unsigned int kfunc, long val);
extern void dp_idmsg(long amt, UBYTE stay);
extern void comm_scale(char);
extern void make_kp();
/*****************************************************************************/
void dsp_dpi()
{
  long amt;
  if(PRT_OPT.OPT1_2) {
      if (cupn_bit) prn_dtlogo(rstep_id & perstp_id);
      else prn_dtlogo(rstep_id);
      }
  else {
      if (cupn_bit) prn_dtlogo(0);
      else prn_dtlogo(0);
      }

  if(rpt_flg)
    amt = rdptamt;
  else
    amt = dptamt;
  if(!vd1_bit)
      dp_idmsg(amt,rpt_flg);
  return;
}
void prn_ddec()
{

  if (dept[func].desc[0] != 0){
     make_desc(dept[func].desc,MAX_DEPT_DESC);
     desc2pbuf();
     }
  else
       sprintf(prt_buffer,s_deptpd,func+1);
  dsp_dpi();
  return;
}

/*****************************************************************************/
void prn_pdec()
{
  if (plu[pcode].desc[0] != 0){
     make_desc(plu[pcode].desc,MAX_PLU_DESC);
     desc2pbuf();
     }
  else {
     sprintf(prt_buffer,s_plupd,pcode+1);
     };
  dsp_dpi();
  return;
}
/*****************************************************************************/
/****                   dpt,plu,subgroup update                            ***/
/*****************************************************************************/
void mupdate(long tmp)     /*** dpt,plu,subgroup update ***/
{
    long cnt;

    result=dptamt;
    cntint=tmp;

    if (upmul == 0) upmul=tmp*100;
    else if (tmp < 0) upmul=-upmul;
    if(scale_bit) {
        if(vd1_bit || vd2_bit)
            item_time -= 100;
        else
            item_time += 100;
        }
    else {
        item_time+=upmul;
        }

    if (gas_bit) cntint=gas_cnt;
    else cntint=upmul;

    if(cupn_bit) cntint=0;

    cnt = cntint;

    if (pluon_bit) {
        adcntl(tplu); /* plu total */

//    if (gas_bit) cntint=gas_cnt;
//    if (cinc_bit) cntint=-cntint;  /* count dec/inc */
    if(invent_bit && !train_flg)
        stock_p[pcode] -= cntint;
//        cntint = -cntint;
    adcntl(pluup);     /* plu up */
    cntint = cnt;

//    if (gas_bit) cntint=0;
//    else cntint=upmul;

    func=plu[pcode].link_dept-1;         /* linked dept no */
    if (negat_bit) {    /* plu is negative */
        load_dstat();    /* dept status fetch */
//       cntint=tmp;
        if (!negat_bit) adcntl(nppdpt);   /* -plu linked to +dept */
        }
    else {
        load_dstat();    /* dept status fetch */
        };
    }; /* pluon_bit */
// if (gas_bit) cntint=0;
// else cntint=upmul;
    if (!negat_bit) adcntl(podept);
    else adcntl(nedept);

// if (gas_bit) cntint=gas_cnt;
// if (cinc_bit) cntint=-cntint;                /* count dec/inc */
    if(invent_bit && !train_flg) {
        if (pluon_bit && !SYS_OPT.OPT3_1)
            cntint = 0;
        else
            stock_d[func] -= cntint;
//            cntint = -cntint;
        }
    adcntl(dptup);     /* dept up */
    cntint = cnt;

// if (gas_bit) cntint=0;
    adcntl(adjdpt);                             /* adjust dept up */

    adcntl(g_base+dept[func].group);            /* dept group up*/
    adcntl(grp_total);                          /* dept group totl*/
/*--------------------------------------------------------------------*/
    if (pluon_bit) load_pstat();     /* retrive plu status */

    cntint=tmp;
// if (hash_bit) { hash_amt +=result;adcntl(hashamt); };

 /* nontax up */
    if (!(rstep_id & 0x0f)) {
        cntint = 0;
        adcntl(nontaxamt);
        adcntl(cnontaxamt);
        cntint = tmp;
        };

    if (singl_bit && ((regstep == RSTEP_END) || (regstep == RSTEP_SRT)))     /* single item step */
        sglok_flg=1;
    if (pluon_bit) pluact_bit=1;

/*--- void1,2 & return update - not active in the void mode ---*/
    if (vd1_bit || vd2_bit || rtn_bit) {
        if (cntint < 0) cntint=-cntint;

        if (vd1_bit) { adcntl(void1); adcntl(cvoid1); }
        if (vd2_bit) { adcntl(void2); adcntl(cvoid2); }
        if (rtn_bit) {      /* 96.06.13 */
            if (vd1_bit) cntint=-cntint;
            adcntl(retn); adcntl(cretn);
            if (vd1_bit) cntint=-cntint;
            };
        };

 /*----              coupon update                ----*/
    if (cupn_bit) {        /* 96.06.13 */
        if (vd1_bit)   cntint = -cntint;
        adcntl(per1tl+cpnfunc);
        adcntl(cper1tl+cpnfunc);
        };

 /*---------------   GROSS UPDATE   ------------------*/
    cntint=0;
// if (!hash_bit) {
    if (!cupn_bit && !negat_bit && !rtn_bit && (voidmd_flg != 1)) adcntl(gross);
    if ((voidmd_flg == 1) && (negat_bit || cupn_bit)) {
        result=-result; adcntl(gross);
        if (voidmd_flg != 1 && rtn_bit && cupn_bit) adcntl(gross);
        };
//    };
    return;
}

/*****************************************************************************/
#if 0
void clr_regbuf()
{
 reg.r_index=0;
 reg.crt.r_kcode[0]=-100;
 reg.r_amt[0]=0;
 return;
}
#endif
long mk_reg_form(char type)
{
  char index;
  int  k_code;
  long ret_amt=0;

  if (regstep == RSTEP_END || regstep == RSTEP_SRT)
               reg.r_index=0;
  if (rtn_bit) return(FAULT);

  if (reg.r_index < MAX_KITEM) {
     if (pluon_bit) k_code=pcode+S_PCODE;
     else k_code=func;
     for (index=0; index<reg.r_index; index++) {
//         if ((reg.crt[index].r_kcode == k_code) && !(rtn_bit ^ reg.crt[index].rtn_b)){
         if (reg.r_kcode[index] == k_code) {
            if (type == 1) reg.r_amt[index] +=nur;
            ret_amt=reg.r_amt[index];
            return(ret_amt);
            };
         }
     if (type == 1) {
          reg.r_kcode[index]=k_code;
//        reg.crt[index].r_kcode=k_code;
//        reg.crt[index].rtn_b=rtn_bit;
        reg.r_amt[index]=nur;
        index++;
        reg.r_index=index;
        };
     };

  return(FAULT);
}

/*****************************************************************************/
void itemmize(char tax_inf)
{
  taxable[tax_inf] +=dptamt;
  return;
}

void dpcon()
{
 long cnt,ck_amt;
 int  nxt_pluno, sspcode;

 unit=nur;                  /* calculation buffer */
 upmul=0;

 if (mul_bit || scale_bit) {    /* mul reg */
    cal_multi(mul,sdcnt1,unit,0,0);
    if(err_bit)  ERR

    if (spl_bit){
//       if (!SYS_OPT.OPT24_1)    /* split pricing */
          cal_divi(mvalue,mvalue2,sdcnt1,quant,sdcnt2);
//       else   /* triple multiplication */
//          cal_multi(quant,sdcnt2,mvalue,mvalue2,sdcnt1);
       if(err_bit) ERR

       };
    /* rounding */
    nur = round_func(SYS_OPT.OPT22_1,mvalue,moksub[0]);
/*===============   rcnt   ================*/
    pow10(3-sdcnt1);
    cal_divi((mul * pow_val),0,3,1000,0);
    if (err_bit) ERR
    calmul=rcnt=round_func(SYS_OPT.OPT22_1,mvalue,moksub[0]);
    mvalue=(mvalue*100) + (moksub[0]* 10) + moksub[1];
    upmul=round_func(SYS_OPT.OPT22_1,mvalue,moksub[2]);     /* report update */

/*    rcnt%=10;
    if (rcnt == 0) rcnt=10; */                   /* for repeat check */
    }; /* mul_bit */


 if (gas_bit) {
    cal_divi(nur,0,0,gas_amt,3);
    ban_olim();
    gas_cnt=mvalue;
    };

 if (!scale_bit && !mul_bit && !vd1_bit) {
    rcnt+=1;   /* normal rept cnt inc */
    }

 rstepold_id=rstep_id;
 taxselc();
 rstepsv_id=rstep_id;  /* for link plu */
 saveseq();
 dptamt=snur=nur;                         /* amount repeat & void1 save */
 sunit=unit;                              /* for void1 save */
 smul=mul;
 squant=quant;
 if(!rpt_flg)
     rdptamt=dptamt;
 else
     rdptamt+=unit;

/*===========================================================================*/
/*===                          itemmize  memory                           ===*/
/*===========================================================================*/
 if (vd2_bit) {
    if(halo_err(VOID,-nur)) { errmsg = E_HALO; ERR}

    ck_amt=mk_reg_form(0);       /* reg amt check with parameter 0 */
    errmsg = E_VOID;
    if (((ck_amt != nur) && ck_amt == 0) || ck_amt == FAULT) ERR;
    if (ck_amt > 0 && ((-nur) > ck_amt)) ERR
    if (ck_amt < 0 && ((-nur) < ck_amt)) ERR
    errmsg = 0;
    };
 /* enter amt check */
 cal_multi((gamt+dptamt),0,1,0,0);
 if (err_bit) ERR
 if (!cupn_bit) {
    if (tax1_bit) itemmize(TAX1);
    if (tax2_bit) itemmize(TAX2);
    if (tax3_bit) itemmize(TAX3);
    if (tax4_bit) itemmize(TAX4);
    if (tax1_bit && tax4_bit) itemmize(TAX14);
    if (tax2_bit && tax4_bit) itemmize(TAX24);
    if (tax3_bit && tax4_bit) itemmize(TAX34);
    sgamt=gamt +=dptamt;
    asgamt=agamt +=dptamt;

    pmemcpy((char *)staxable,(char *)taxable,sizeof(TAX_LEN));
    }
    else { /* later !! */
       perstp_id=persav_id;
       per_taxcali(); /* add & food */
       };
 vmark_flg = 0;
 if ((mode_id == VMODE) && (voidmd_flg == 0)) {      /* temp for r on/off */
       vmark_flg = 1;
       voidmd_flg=1;
    };

/*===========================================================================*/
/*===                          memory update                              ===*/
/*===========================================================================*/
 cnt=1;
 if (rtn_bit) cnt=-1;
 if (vd1_bit || vd2_bit) cnt=-cnt;
 if (voidmd_flg == 1) cnt=-cnt;
 if ((/*sacle_bit ||*/mul_bit) && mul != 0 && calmul != 0) cnt *=calmul;
 /* if cpn is active, counter is positive */
 mupdate(cnt);

/*===========================================================================*/
/*===                             display                                 ===*/
/*===========================================================================*/
/*===========================================================================*/
 if(kp_bit)
     make_kp();
 mk_reg_form(1);        /* reg inital & make form */
 regstep=RSTEP_DPT;

/* if (void_bit) rcnt=0; */
/* if (!rpt_flg) mkdnur(0);
 mkdsp();*/
 if ( rpt_flg == 1 ) {
    flg_dis_txtmp[7]= rcnt%10; /* repeat count */
    outdtx();
    }
 else {
    mkdnur(0);
/*    if (rcnt != 1) rpt_flg=1; */
    mkdsp();
    };

/*=========================================================================*/
/*===                             print                                 ===*/
/*=========================================================================*/
 if(vmark_flg) {
       vmark_flg = 0;
       logo_only(LOGO_VOID);
       }
 if (rtn_bit && !vd1_bit && !cupn_bit) {    /* rtrn  */
    regstep=RSTEP_RTN;
    prn_sfd(RETURN,'*');
    };

 if (( scale_bit || mul_bit) && !vd1_bit){
    amount1=nur;
    nur=mul;
    fdec_inx=0;
    if (spl_bit) {
//       if (SYS_OPT.OPT22_1 == 0){   /* split pricing */
          prn_fdec(sdcnt1,P_SLASH);
          nur=quant;
          prn_fdec(sdcnt2,P_FOR); /* 999.999/999.999FOR */
//          }
//       else{   /* triple multiplication */
//          prn_fdec(sdcnt1,P_X);
//          nur=quant;
//          prn_fdec(sdcnt2,P_X); /* 999.999X999.999X */
//          };
          }
    else if (scale_bit) {
        rcnt = 1;
        prn_fdec(sdcnt1,scale_logo);
        lgol_bit = 1;
        mk_idmsg(prt_buffer,unit,0,3);
        lgol_bit = 0;
        }
    else {
        prn_fdec(sdcnt1,P_X);
//        lgol_bit = 1;
        }
    nur=unit;
    fdec_inx = 10;
    prn_com(0);
//    sep_prn();
    *(ptxpnt++)='@';
    while (ptxpnt != &numtxt[0])
          prt_buffer[fdec_inx++]=*(ptxpnt--);
    prt_buffer[fdec_inx++]=*(ptxpnt--);
    des_prn();
    nur=amount1;        /* retrieval */
    func=sfunc;
    };

 if (gas_bit) {
    amount1=nur;
    nur=gas_cnt;
    if(SYS_OPT.OPT3_3)
        sprintf(prt_buffer,s_ltrcnt);
    else
        sprintf(prt_buffer,s_galcnt);
    lsharp_bit=1;prn_gcpt(0,2,1);
    nur=gas_amt;
    if(SYS_OPT.OPT3_3)
        sprintf(prt_buffer,s_ltramt);
    else
        sprintf(prt_buffer,s_galamt);
    lgol_bit=1;prn_gcpt(0,3,1);
    nur=amount1;        /* retrieval */
    };

 if (vd1_bit) {regstep=RSTEP_VD1;prn_sfd(ERR_CORR,'-'); /* logo_only(17); */};    /* void1 */
 if (vd2_bit) {                         /* void2 */
     prn_sfd(VOID,'-');    /* void2 */
     regstep=RSTEP_VD2;
     func=sfunc;                        /* retrieve for dept no print */
     };
 if (cupn_bit) {
    regstep=RSTEP_CPN;
    if (vd1_bit) regstep=RSTEP_CVD1;
    }

// rstep1_id |= rstep_id;
 if (pluon_bit) {
    prn_pdec();
    }
 else {
    prn_ddec();
    }

 sep_prn();
 rpt_flg=0;

 if (!vd1_bit && !vd2_bit) void_bit=0;

 /*================   link plu check   ===================*/
 if (pluon_bit && plu[pcode].link_plu != 0) {
    nxt_pluno=plu[pcode].link_plu-1;
    sspcode = pcode;
    pcode = nxt_pluno;
    load_pstat();
    pcode = sspcode;
    if (!preset_bit) {errmsg = E_PGM; ERR}         /* not preset plu then error */
    initseq();
    rstep_id=rstepold_id;
    twostep_id=twosave_id;
    if (mst_pluno == 0 && !vd1_bit && !vd2_bit) {   /* for e correct */
       mst_pluno=spcode+1;
       pluvsnur=snur;
       m_plu_two=twosave_id;
       m_plu_rstep=rstep_id;
       if ( scale_bit || mul_bit) pluvsnur=sunit;
       };
    nur=plu[spcode].link_plu;  /* for repeat plu input no */
    if ( scale_bit || mul_bit) mul=smul;
    if (spl_bit) quant=squant;
    knur_bit=1;
    cantime +=1;
    if (!vd1_bit) {
       pluon_bit=0;
       wait_pover();
       if (repeat_flg == 1) {plu_rpt_flg=1;repeat_flg=0;};
       lplu_flg=1;
       smst_pluno=mst_pluno;
       sfunc=PLU;
       return;
       }
    else {
       pcode=nxt_pluno;
       load_pstat();
       nur= -plu[pcode].price;
       if (mode_id == VMODE || voidmd_flg == 1) nur=-nur;
       if (negat_bit) nur =-nur;

       dpcon();
       return;
       }
    };
 plu_rpt_flg=0;
 lplu_flg=0;
 smst_pluno=0;

/*==================   single item check   ===============*/
 if (sglok_flg) {                 /* single item */
    initseq();
    sglok_flg=1;
    regstep=RSTEP_DPT;
    func=CASH;
    r_tender();
    return;
    };

 initseq();
// rstepsv_id=0;
 mul=0;
 quant=0;
 cantime +=1;
 nona_bit=0;
 return;
}

/*****************************   amount sign check  **************************/
void dpamt()        /* case of preset & open , coupon */
{
 UBYTE status;
 if (nadd_bit && !nona_bit) { errmsg = E_CNONADD; ERR}     /* compul nona */
 if ((negat_bit && rtn_bit) || (negat_bit && cupn_bit)  || (scale_bit && gas_bit)) {
    errmsg = E_KEY; ERR
    }
    if(rtn_bit) {
        if(halo_err(RETURN,nur)) { errmsg = E_HALO; ERR}
        }

 if (gas_bit && !nur) { errmsg = E_OPEN; ERR}
 if (gas_bit && spl_bit) { errmsg = E_SPLITPR; ERR}

 if (!negat_bit && pluon_bit) {          /* p-plu n-dept -> err */
    status=dept[plu[pcode].link_dept-1].status[0];
    if (status & 0x10) { errmsg = E_PGM; ERR} /* =negat_bit */
    };
#if 0
 if ((negat_bit && hash_bit) || (negat_bit && gas_bit) ||
     (singl_bit && valid_bit)) { errmsg = E_PGM; ERR}
#endif

 if (mode_id == VMODE || voidmd_flg == 1) nur=-nur;

 if (cupn_bit) {
    EJ_FLAG |= EJ_PERM;
    nur=-nur;
    }
 if (vd2_bit) nur=-nur;
 if (rtn_bit) nur=-nur;
 if (negat_bit) nur=-nur;
 if (nur < 0) sign_bit=1;
 dpcon();
 return;
}

/*****************************************************************************/
/****                                                                     ****/
/****                           DEPARTMENT MAIN                           ****/
/****                                                                     ****/
/*****************************************************************************/
char twosave_err()
{
 if (mul_bit || scale_bit ) return(FAIL);
 if (twosave_id & 0x10) mul_bit=1;
 if (twosave_id & 0x01) rtn_bit=1;
 return(SUCCESS);
}

/*****************************************************************************/
char preset_over(long dp_price)
{
 /* option 12=1 : Disable preset override */
// if (!gas_bit && (SYS_OPT.OPT14_1) && dp_price != 0 && nur > dp_price)
//  return(E_OVERRIDE);
// if (!(SYS_OPT.OPT14_1)) {
    if (!scale_bit && !mul_bit && !gas_bit && dp_price != 0 && !preset_bit && nur > dp_price &&
        (mode_id != XMODE))
       return(E_HALO);
//  };
 return(SUCCESS);
}
char mk_gasamt(long dp_price)
{
 if (gas_bit) {
    gas_amt=dp_price;
    if (gas_amt == 0 || gas_amt > 999999) return(E_HALO);
    };
 return(SUCCESS);
}
/*****************************************************************************/
void itemopn_err()
{
  if (reqscl_bit && !scale_bit && !SYS_OPT.OPT2_4) {errmsg=E_COMPSCL;ERR}
  if (!reqscl_bit && scale_bit) {errmsg= E_SCALE; ERR}
  return;
  }

void auto_scl(char a_scl, char a_tare)
{
 long tnur;
 char tdcnt,tncnt,tkdec_bit,tknur_bit;

 if (FUNCKEY[SCALE-CASH].KEY_ST.SCALE_KEY.MANUAL)
    return;

 if(a_scl & 0x4) {                     /* autoscl_bit */
    if(mul_bit) { errmsg = E_KEY; ERR }
    tnur = nur;
    tdcnt = dcnt;
    tncnt = ncnt;
    tkdec_bit = kdec_bit;
    tknur_bit = knur_bit;

    knur_bit = 0;
    comm_scale(1);
    tare_flg=0;
    scale_bit=1;
    mul=nur;
    sdcnt1=dcnt;

    nur = tnur;
    dcnt = tdcnt;
    kdec_bit = tkdec_bit;
    knur_bit = tknur_bit;
    }
 if(a_tare) {
           if(sdcnt1 == 2)
                  mul *= 10;
           mul -=tare_weight[a_tare-1];
           if(mul <= 0) { errmsg = E_NUMOVER; ERR }
           sdcnt1 = 3;                 /* 980428 */
//           if(mul % 10)
//                  sdcnt1 = 3;
//           else
//                  mul /= 10;
           }
}
void r_dept()
{
 if(kdec_bit) { errmsg = E_NUMOVER; ERR}
 auto_scl(dept[func].status[1], dept[func].auto_tare);
 if (regstep>=RSTEP_RA || pluon_bit) { err_bit = 1; errmsg = E_KEY;}
 if(err_bit) ERR
 rpt_flg=0;
#if 0
 if (price_flg == 1) { /* price inquiry */
    if (knur_bit) ERR
    price_view(IS_DEPT);
    return;
    };
#endif
 lcd_rec(2);
 sv_lcd();

 if (!knur_bit) {         /* repeat , preset */
       if (cupn_bit) {                    /* coupon */
          if (twosave_err()) { errmsg = E_KEY; ERR}

          if (gas_bit) {
        errmsg = E_KEY; ERR
        }
          nur=spnur;
          load_dstat();                            /* preset */
          rcnt=0;
          dpamt();
          cupn_bit = 0;
          return;
          };
    if (rcnt != 0 && ((func == sfunc) || ((func+MAX_DPT_KEY) == sfunc)) && regstep != RSTEP_END &&  /* mul vd2 rtn */
    regstep != RSTEP_SRT && !rtn_bit && !mul_bit && !scale_bit &&
        !taxsft_bit && !(dptsav_id & 0x80) &&
        !(twosave_id & 0x067) && !vd2_bit) { /* 1 0 0(1)0 1 1 1 */
       loadseq();                                          /* repeat */ /* except mul */

//       taxs_cap();
       nur=snur;
       rpt_flg=1;
       if (mul_bit) {rpt_flg=2;nur=sunit;};
       mul_bit=0;
/*       rcnt%=10; */
       dpcon();
       return;
       };

    void_bit=0;      /* after err correct, preset dept */
    load_dstat();                            /* preset */
    if (inact_bit /* || (negat_bit && rtn_bit) */) { errmsg = E_INACTDEPT; ERR}
    itemopn_err();
    if(err_bit) ERR
    if (!preset_bit || gas_bit) { errmsg = E_PRESET; ERR}
    nur=dept[func].price;
    }
 else {
    /* open , override */
    load_dstat();                       /* override check */
    if (inact_bit /* || (negat_bit && rtn_bit) */) { errmsg = E_INACTDEPT; ERR}
    itemopn_err();
    if(err_bit) ERR
    if (ncnt > 8 || nur == 0 || dcnt != 0 || cupn_bit) { errmsg = E_KEY; ERR}

    /* option 13=1 : Disable preset override */
    if (!gas_bit && (SYS_OPT.OPT14_1) && preset_bit)
        { errmsg = E_OVERRIDE; ERR}
    errmsg = preset_over(dept[func].price);
    if(errmsg) ERR
    errmsg = mk_gasamt(dept[func].price);
    if(errmsg) ERR
    };
 rcnt=0;
 dpamt();
 mul_bit = 0;
 return;
}

/*****************************************************************************/
/****                                                                     ****/
/****                           PLU   MAIN                                ****/
/****                                                                     ****/
/*****************************************************************************/
char plu_inerr()
{
 if (nur == 0 || dcnt != 0 ||
        (nur > MAX_PLU))
    return(FAIL);   /* registered by code */
 return(SUCCESS);
}

/*****************************************************************************/
char mk_pcode()
{
 pcode=(int)(nur-1);
 load_pstat();
 if (plu[pcode].link_dept == 0) plu[pcode].link_dept = 1; /* TEMP PSS return(FAIL); */   /* not link dept */
 return(SUCCESS);
}

/*****************************************************************************/

void r_plu()
{
 char tcupn_bit;

  if(kdec_bit) { errmsg = E_NUMOVER; ERR}
 if(!pluon_bit)
     auto_scl(plu[nur-1].status[1], plu[nur-1].auto_tare);
 tcupn_bit = cupn_bit;
 if (regstep >= RSTEP_RA) { err_bit = 1; errmsg = E_KEY; ERR}
 if(err_bit) ERR
 rpt_flg=0;
#if 0
 if (price_flg == 1){ /* price inquiry */
    if (plu_inerr() || mk_pcode()) ERR
    pluon_bit=1;
    price_view(IS_PLU);
    pluon_bit=0;
    return;
    };
#endif
 if(!lplu_flg) {
  lcd_rec(2);
  sv_lcd();
  }
 /* repeat */
 if (!knur_bit) {
    if (pluon_bit || cupn_bit || regstep == RSTEP_END || regstep == RSTEP_SRT) { errmsg = E_KEY; ERR}

    if (rcnt != 0 /*&& func == sfunc*/ && !taxsft_bit && !mul_bit &&  !scale_bit &&
        !rtn_bit && !(dptsav_id & 0x80) &&
        !(twosave_id & 0x067) && !vd2_bit && !cupn_bit) {
       loadseq();                              /* repeat */
       repeat_flg=1;

       if (smst_pluno != 0) {
          pcode=smst_pluno-1;
          twostep_id=m_plu_two;
          rstep_id=m_plu_rstep;
          load_pstat();
          itemopn_err();
          if(err_bit) ERR
          smst_pluno=0;
          mst_pluno=0;
      nur=pluvsnur;
          }
       else {
          rpt_flg=1;
          nur=snur;
          if (  scale_bit || mul_bit) { rpt_flg=2; nur=sunit;};
          };
       mul_bit=0;
/*       rcnt %=10; */
       dpcon();
       return;
       };
    errmsg = E_KEY; ERR
    } /* !knur_bit */
 else
 {     /* open,preset,override */
    if (ncnt > 8 || nur == 0 || dcnt != 0) {
    errmsg = E_KEY; ERR
    }
    if (!pluon_bit) {
       if (plu_inerr()) {
    errmsg = E_KEY; ERR
    }
    mk_pcode();
    if(inact_bit) { errmsg = E_INACTDEPT; ERR}
    if (tcupn_bit) {                    /* coupon */
          if (twosave_err() || nur == 0 || nur > MAX_PLU || kdec_bit) ERR;
          pcode=(int)(nur-1);
          cupn_bit = tcupn_bit;
          if (gas_bit) {
        errmsg = E_KEY; ERR
        }
          pluon_bit=1;
          nur=spnur;
          rcnt=0;
          dpamt();
          cupn_bit = 0;
          return;
          };

       load_pstat();
          itemopn_err();
          if(err_bit) ERR

       if ((!mul_bit || (mul_bit && mul != 1)) &&
       preset_bit && !gas_bit /* && !scale_bit */ ) {  /* preset */
      pluon_bit=1;
      nur=plu[pcode].price;

      if (plu_rpt_flg == 1) {
         twostep_id=m_plu_two;
     rstep_id=m_plu_rstep;
     rcnt--;
/*             rcnt %=10; */
     }
      else rcnt=0;

      dpamt();
      return;
      }
       else {
      pop_menu(s_eprice,'|');
      pluon_bit=1;                  /* plu no enter */
      nur=0;ncnt=0;rcnt=0;
      knur_bit=0;
      return;
      }
       };
    if (pluon_bit) {                  /* open override */
       if (ncnt > 8 || nur == 0) { errmsg = E_KEY; ERR}
       /* override check */
       errmsg = preset_over(plu[pcode].price);
       if(errmsg) ERR
       errmsg = mk_gasamt(plu[pcode].price);
       if(errmsg) ERR
       rcnt=0;
       dpamt();
       return;
       };
    };  /* knur_bit */
}
