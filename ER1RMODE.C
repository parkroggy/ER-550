#include <stdio.h>
#include <er1io51.h>
#include <er1exmt.h>
#ifndef BCDBG
#include  <exs03.h>
#else                                  /* BCDBG */
#include  <exdbg.h>
#endif                                 /* BCDBG */

extern const UBYTE s_recacc[18];
extern const UBYTE s_padout[15];
extern const UBYTE s_amount[7];
extern const UBYTE s_tsftpd[13];
extern const UBYTE s_tarepd[9];

extern char chk_dwrlimit();
extern void adcntl(int index);
extern void ad_drwtl();
extern void open_drw();
extern void cal_multi(long long1, char d1, long long2_1, long long2_2, char d2);
extern void cal_divi(long long1_1, long long1_2, char d1, long long2, char d2);  /* 981024 */
//PKR0624 extern void clr_ex0();
extern long mk_reg_form(char type);
extern void comm_slip(char tbl_no,char type);
extern void comm_kp(char type);
extern void clr_kpbuf();
extern void delay();
extern void desc2pbuf();
extern void des_prn();
extern void dis9_out(char what);
extern void dpcon();
extern void endlogr();
extern void endlogo();
extern void fill_time(char ss);
//PKR0624 extern void inidtx();
//PKR0624 extern void initseq();
extern void comm_scale(char);
extern char level_err();
extern void logo_only(char type);
extern void logo_nur(char type);
extern void load_pstat();
extern void load_dstat();
//PKR0624 extern void loadseq();
extern void make_desc(char *temps,char max);
extern void mkrandom(long value,char ofst,char st);
extern void mkdnur(char inf);
extern void mkdsp();
extern void open_drw();
//PKR0624 extern void outdtx();
extern void prn_tend(char dinx,unsigned int kfunc,char lcd_f);
extern void prn_gcpt(char type,char dec,char lcd_f);
extern void prn_fdec(char dec,char type);
//PKR0624 extern void prn();
extern void ej_prn();
extern void prn_ddec();
extern void prn_pdec();
extern long round_func(char sys_no,long value,char frac);
//PKR0624 extern void set_ex0();
extern void sep_prn();
extern void taxcal(long *tax_able,long *tax_amt);
extern void wait_pover();
extern void ini_outdtx();
extern void mk_idamt(long amt, UBYTE x, UBYTE y, UBYTE end, UBYTE stay, UBYTE sp, char sym);

extern void dsp_tax(int);
extern void sv_lcd();
extern void lcd_rec(char type);
extern void pop_menu(unsigned char *msg, unsigned char ch);
extern void dsp_str(UBYTE x, UBYTE y, unsigned char *str);
extern void func_menu();
extern void lcd_dsp(char clr_f);
extern void prn_sfd(unsigned int kfunc,unsigned char ch);
extern long tax_sum(int kfunc,long *tax_amt);
extern void mk_lline(unsigned char *rbuf, UBYTE x, int end);
extern UBYTE *get_fdesc(unsigned int kfunc);
extern char halo_err(unsigned int kfunc,long lval);
extern int mk_dnum(long num, unsigned char *rmsg, char sym);
extern void taxexm_set(int kfunc);
extern void ionur_sign();
extern void chk_kpend();
extern void dsp_scl();
extern void sign_off(char);
extern void pmemcpy(UBYTE *, UBYTE *, unsigned int);
extern void ban_olim();                /* 981024 */

/*****************************************************************************/
void prn_ctend(char lcd_f)
{
    if (func == CASH) prn_tend(DINX_CASH,CASH,lcd_f);
    if (func == CHECK) prn_tend(DINX_CHECK,CHECK,lcd_f);
    if ((func >= MISCTND1) && (func <= CONV4) ) prn_tend(DINX_MISC1+func-MISCTND1,func,lcd_f);
    return;
}
/*****************************************************************************/
/***                            NO SALE KEY                                ***/
/*****************************************************************************/
void r_nosale()
{
    char temp;
    if (ncnt == 0) { /* no sale */
        if(FUNCKEY[NOSALE-CASH].KEY_ST.NS_KEY.INACT) { errmsg = E_INACT; ERR}
        if (mode_id != RMODE || (regstep != RSTEP_END && regstep != RSTEP_SRT)
            || ((FUNCKEY[NOSALE-CASH].KEY_ST.NS_KEY.AFT_NADD) && nona_bit)) { errmsg = E_KEY; ERR}
        ini_outdtx();
        cntint=1; result=0;
        adcntl(nosale);adcntl(cnosale);
        open_drw();
        clr_flg = 1;                   /* PKR1223 Power Fail */

        post_tamt=0;
        xoff_flg=1;
        regstep = RSTEP_END;

        buf_cnt=rcnt=0;

        get_fdesc(NOSALE);

        pop_lcd = 2;
        pop_menu(lcdbuf,'|');
        pop_lcd = 0;
        if (!FUNCKEY[NOSALE-CASH].KEY_ST.NS_KEY.NO_RCT && !rpoff_bit) {
            EJ_FLAG = EJ_NS;
            prn_sfd(NOSALE,'-'); /* NO SALES */
            endlogr();
            }
        else {
            endclr(); snona_flg=0;
            initseq();
            end_mark=1;
            xoff_flg=0;
            pfend_flg=0;
            clr_flg = 1;
            pmenu_inx = 0;
              if (SYS_OPT.OPT19_1)
                      sign_off(0);
            }
        }
    else { /* NON-ADD # */
        if (ncnt > 8 || twostep_id || kdec_bit)
            { errmsg = E_PGM; ERR}
        EJ_FLAG |= EJ_NS;
        post_tamt=0;
        xcnt_bit=1;
        result = nur;
        if(mode_id == VMODE) result = -result;
        cntint=0;
        adcntl(nosale);
        adcntl(cnosale);
        if (regstep == RSTEP_END) regstep=RSTEP_SRT;
        if((mode_id == VMODE) && !voidmd_flg) {
            voidmd_flg = 1;
            logo_only(LOGO_VOID);
            }
        temp = SYS_OPT.OPT18_1;
        SYS_OPT.OPT18_1 = 0;
        prn_tend(DINX_NONADD,NONADD,1);
        SYS_OPT.OPT18_1 = temp;
        initseq();
        nona_bit=1;                         /* not clear at the clear key */
        if (FUNCKEY[NOSALE-CASH].KEY_ST.NS_KEY.COM_NADD == 1) snona_flg=1;   /* clear at tender key */
        cantime +=1;
        };
    return;
}

/*****************************************************************************/
void taxselc()
{
    char rs;

    rs = rstep_id & 0xf0;
    rstep_id = (rstep_id & 0x0f) ^ (dptstp_id & 0x0f);
    rstep_id |= rs;

    return;
}

/*****************************************************************************/
void pitabl_up(char inf)
{
    taxable[inf] +=nur;
    return;
}

void per_taxcali()
{
    char tax_inf;

    tax_inf=(rstepsv_id & 0x0f) & (perstp_id & 0x0f);

    if (tax_inf & 0x01) pitabl_up(TAX1);
    if (tax_inf & 0x02) pitabl_up(TAX2);
    if (tax_inf & 0x04) pitabl_up(TAX3);
    if (tax_inf & 0x08) pitabl_up(TAX4);
    if (tax_inf & 0x09) pitabl_up(TAX14);
    if (tax_inf & 0x0a) pitabl_up(TAX24);
    if (tax_inf & 0x0c) pitabl_up(TAX34);
    gamt +=nur;
    return;
}

/*****************************************************************************/
/***                              X/TIME KEY                               ***/
/*****************************************************************************/
void r_xtime()
{
//UBYTE bbuu[22];
//    chk_kpend();
    if (regstep >= RSTEP_RA || nur == 0 || spl_bit ||  scale_bit ||
        (dcnt != 0 && ((ncnt-dcnt > 3) || dcnt > 3)) || /* 999.999 */
    (dcnt == 0 && ncnt > 3)) { errmsg = E_NUMOVER; ERR}
    if (mul_bit) {
/*     if (sdcnt != 0 || dcnt != 0) ERR*/

        spl_bit=1;
        quant=nur;
        nur=mul;
        fdec_inx = 0;
        sdcnt2=dcnt;
//sprintf(bbuu,"%d %d",sdcnt2, dcnt);
        prn_fdec(sdcnt1,P_SLASH);
        nur=quant;
        prn_fdec(sdcnt2,P_FOR); /* 999.999/999.999FOR */
        }
    else {
        mul_bit=1;
        mul=nur;
        sdcnt1=dcnt;
//        sncnt1=ncnt;
        fdec_inx = 0;
        prn_fdec(sdcnt1,P_X);
        };
    pop_menu(prt_buffer,'|');
    memset(prt_buffer,0x20,sizeof(prt_buffer));
//dsp_str(0,1,bbuu);
    nur=0;
    dcnt=0;
    ncnt=0;
    kdec_bit=0;
    knur_bit=0;
    return;
}

/******************************************************************************/
/***                 RECEIVED ON ACCOUNT/PAID OUT KEY                       ***/
/******************************************************************************/
void prn_rapo(unsigned int kfunc, char type)
{
    strcpy(prt_buffer,get_fdesc(kfunc));
    if (type == 1) {
        sprintf(lcdbuf," %s",prt_buffer);
        mk_idamt(rapo_total,0,0,MAX_CLM,0,1,0);
        sep_prn();
        memset(lcdbuf,0x20,20);
        dsp_str(0,6,lcdbuf);
        }
    else des_prn();

    return;
}

/******************************************************************************/
void rapo_tend()
{
    char  tcnt;
    long  temp_tot, rtcnt;

    if (nur == 0 || dcnt != 0 || (func != CASH && func != CHECK &&
        !(func >= MISCTND1 && func <= MISCTND4))) { errmsg = E_KEY; ERR}
    if (regstep == RSTEP_PO)
        {
        nur= -nur;
        if(halo_err(PO,-(nur+rapo_total))) { errmsg = E_HALO; ERR}
        rtcnt = FUNCKEY[PO-CASH].HALO;
        }
    else {
        if(halo_err(RA,nur+rapo_total)) { errmsg = E_HALO; ERR}
        rtcnt = FUNCKEY[RA-CASH].HALO;
        }
    temp_tot=rapo_total+nur;
    if (temp_tot < 0) temp_tot= -temp_tot;
    for (tcnt=0; temp_tot!=0; tcnt++) temp_tot/=10;
    if ((rtcnt != 0 && rtcnt < tcnt) || tcnt > 7) { errmsg = E_HALO; ERR}
    rapo_total+=nur;
        /* memory update ! */
    cntint=1; result=nur;
    if (func == CASH) { adcntl(cshindw); adcntl(ccshindw); }
    else if(func == CHECK){ adcntl(chkindw); adcntl(cchkindw); }
    else { /* Misc tend1-4 */
        adcntl(misc1dw+func-MISCTND1); adcntl(cmisc1dw+func-MISCTND1);
        }
    mkdnur(0);
    prn_ctend(1);
    dsp_tax(-1);
    if (chk_dwrlimit()) { errmsg = E_DRWOVER; ERR }
    initseq();
    return;
}
/******************************************************************************/
/***                 RECEIVED ON ACCOUNT/PAID OUT KEY                       ***/
/***                                                                        ***/
/***   CHANGE BACK : amount -> R/A -> amount -> CASH or CHECK               ***/
/***   NORMAL      : R/A[P/O] -> amount -> CASH or CHECK -> R/A[P/O]        ***/
/******************************************************************************/
void r_rapo()
{
    if (mode_id == VMODE || ncnt || dcnt != 0 ||
            (regstep != RSTEP_END && regstep != RSTEP_SRT
            && regstep != RSTEP_RA && regstep != RSTEP_PO)
            || twostep_id)
        { errmsg = E_KEY; ERR}
    if ((regstep == RSTEP_RA && func != RA) ||
            (regstep == RSTEP_PO && func != PO))
        { errmsg = E_KEY; ERR}

    if (func == RA) {
        if (FUNCKEY[RA-CASH].KEY_ST.NORM_KEY.XONLY && mode_id != XMODE)
            {errmsg = E_XONLY; ERR}
    if(FUNCKEY[RA-CASH].KEY_ST.NORM_KEY.INACT) { errmsg = E_KEY; ERR}
        if (regstep == RSTEP_RA){ /* R/A end ! */
            if (knur_bit) { errmsg = E_KEY; ERR}
            cntint=1; pfail_amt=nur=result=rapo_total; adcntl(ra); adcntl(cra);
            ad_drwtl();
            menu_flg = menu_act2 = 0;
            pfend_flg=1;
            regstep = RSTEP_END;
            xoff_flg = 1;
            mkdnur(0);
            open_drw();
            dis9_out(D_TENDER);
            prn_rapo(RA,1);
            endlogr();
            if (chk_dwrlimit()) { errmsg = E_DRWOVER; ERR }
            }
        else{
            EJ_FLAG = EJ_RAPO;
            rapo_total=0;
            regstep=RSTEP_RA;
            clr_lcd();
            pop_lcd =0;
            dsp_str(1,0,s_recacc);
            ini_outdtx();
            prn_rapo(RA,0);
            };
        }
    else { /* P/O */
        if (FUNCKEY[PO-CASH].KEY_ST.NORM_KEY.XONLY && mode_id != XMODE)
            { errmsg = E_XONLY; ERR}
    if(FUNCKEY[PO-CASH].KEY_ST.NORM_KEY.INACT) { errmsg = E_KEY; ERR}
        if (knur_bit) { errmsg = E_KEY; ERR}
        if (regstep == RSTEP_PO){ /* P/O end ! */
            cntint=1; pfail_amt=nur=result=rapo_total; adcntl(po); adcntl(cpo);
            ad_drwtl();
            pfend_flg=1;
            regstep = RSTEP_END;
            xoff_flg = 1;
            mkdnur(0);
            open_drw();
            dis9_out(D_TENDER);
            prn_rapo(PO,1);
            endlogr();
            if (chk_dwrlimit()) { errmsg = E_DRWOVER; ERR }
            }
        else{ /* P/O start ! */
            EJ_FLAG = EJ_RAPO;
            rapo_total=0;
            regstep=svrstep=RSTEP_PO;
            clr_lcd();
            pop_lcd =0;
            dsp_str(3,0,s_padout);
            ini_outdtx();
            prn_rapo(PO,0);
            };
        };
    sfunc=func;
    post_tamt=0;

    initseq();
    nona_bit=0;
    return;
}
/*****************************************************************************/
/***                           SUBTOTAL KEY                                ***/
/*****************************************************************************/
long cal_subt()                        /* 980513 */
{
    long taxl;
    taxl = 0L;

    nur=0;

    taxcal(taxable,tnd_tax);
    nur=gamt;
    nur += taxl = tax_sum(0,tnd_tax);

    if (PRT_OPT.OPT9_1) nur -= taxl;
    return nur;
}

void r_subt()
{
    long taxl;
    taxl = 0L;

    if (knur_bit || (twostep_id & 0x7f)) { errmsg = E_KEY; ERR}
    if (/* addcktnd == 0 && */ regstep == RSTEP_END) { errmsg = E_KEY; ERR}

    nur=0;

    if (regstep == RSTEP_RA || regstep == RSTEP_PO)
        nur=rapo_total;
    else{
//     if (regstep == RSTEP_STEND  || regstep == RSTEP_ADDCK  || addcktnd == 0){
        /* normal !! */
    taxcal(taxable,tnd_tax);
    nur=gamt;
    nur += taxl = tax_sum(0,tnd_tax);
//  }
//     else{  /* during each addcheck !! */
//  taxcal(ataxable,tnd_tax);
//  nur=agamt;
//  };
    };

    mkdnur(0);
    dis9_out(D_SUBTOTAL);   /*0x6d;   S */
    dsp_tax(-2);
    if (PRT_OPT.OPT9_1) nur -= taxl;
    if (PRT_OPT.OPT11_2) logo_nur(18);
    nur=0;
    ksub_bit=1;
//    conv_bit=0;            /* conv_amt  981219*/
    vatbk_bit=0;           /*vat break down*/
    rcnt=0;
    return;
}

/*****************************************************************************/
/***                           TAX KEY                                     ***/
/*****************************************************************************/
void r_tax()
{
    char index;

    if (conv_bit || regstep >= RSTEP_RA) { errmsg = E_KEY; ERR}
    if ( !knur_bit || (nur < 1) || (nur > 4)) { errmsg = E_NUMOVER; ERR}

    index = nur;

    taxsft_bit=~taxsft_bit;
#if 0
    if (ksub_bit){
        if(nur == 1) exmt1_bit = 1;
        if(nur == 2) exmt2_bit = 1;
        if(nur == 3) exmt3_bit = 1;
        if(nur == 4) exmt4_bit = 1;
    else
#endif
        {
        if (index == 1) tax1_bit=~tax1_bit;
        if (index == 2) tax2_bit=~tax2_bit;
        if (index == 3) tax3_bit=~tax3_bit;
        if (index == 4) tax4_bit=~tax4_bit;
        };
    sprintf(lcdbuf,s_tsftpd,index);
    pop_menu(lcdbuf,'|');
    outdtx();
    initky();
    return;
}
/*****************************************************************************/
/***                              SCALE  KEY                               ***/
/*****************************************************************************/
void r_tare()
{
  if (regstep >= RSTEP_RA || mul_bit ) { errmsg = E_KEY; ERR}
  if (knur_bit && dcnt == 0) {
     if (FUNCKEY[SCALE-CASH].KEY_ST.SCALE_KEY.INHI_TARE) {
        errmsg = E_IN_TARE; ERR}
     if (FUNCKEY[SCALE-CASH].KEY_ST.SCALE_KEY.TARE_IN_X && !(mode_id & VXMODE)) {
        errmsg = E_XONLY; ERR}

     if ((nur == 0) || (nur > MAX_TARE)) { errmsg = E_KEY; ERR}
     tare_flg=(char)nur;
     nur=tare_weight[tare_flg-1];
     kdec_bit=1;
     sprintf(lcdbuf,s_tarepd,tare_flg);
     pop_menu(lcdbuf,'|');
     dcnt=3;
     mkdnur(dcnt);
     outdtx();
     initseq();
     return;
     }
}

void r_scale()
{
  char i;

  if (regstep >= RSTEP_RA || mul_bit || pluon_bit) { errmsg = E_KEY; ERR}
#if 0
  if (knur_bit && dcnt == 0) {
     if (FUNCKEY[SCALE-CASH].KEY_ST.SCALE_KEY.INHI_TARE) {
        errmsg = E_IN_TARE; ERR}
     if (FUNCKEY[SCALE-CASH].KEY_ST.SCALE_KEY.TARE_IN_X) {
        errmsg = E_XONLY; ERR}

     if (nur == 0 || (nur > MAX_TARE)) { errmsg = E_KEY; ERR}
     tare_flg=(char)nur;
     nur=tare_weight[tare_flg-1];
     kdec_bit=1;
     sprintf(lcdbuf,s_tarepd,tare_flg);
     pop_menu(lcdbuf,'|');
     dcnt=3;
     mkdnur(dcnt);
     outdtx();
     initseq();
     return;
     };
#endif
   if ((FUNCKEY[SCALE-CASH].KEY_ST.SCALE_KEY.COMP_TARE)
        && tare_flg == 0 && (!knur_bit || kdec_bit)) {errmsg=E_COMPTARE;ERR};

  if (FUNCKEY[SCALE-CASH].KEY_ST.SCALE_KEY.XONLY && !(mode_id & VXMODE)) {errmsg = E_XONLY; ERR}

  if (!knur_bit) {              /* read scale interface */
     if(SYS_OPT.OPT13_1) {
        errmsg = E_PGM; ERR
        }

     comm_scale(0);
     if (err_bit) ERR
     }
  else {
//     if (!FUNCKEY[SCALE-CASH].KEY_ST.SCALE_KEY.MANUAL) {
//        errmsg = E_MANSCL; ERR}
     if ((dcnt == 0) || (dcnt > 3)) {
        errmsg = E_NUMOVER; ERR}

     if (FUNCKEY[SCALE-CASH].KEY_ST.SCALE_KEY.SCALE_UNIT) scale_logo=P_KG;
     else scale_logo=P_LB;

     if (tare_flg != 0) {
        for(i=dcnt;i<3;i++)            /* 980703 */
           nur *= 10;
        nur -=tare_weight[tare_flg-1];
        if(nur <= 0) { errmsg = E_NUMOVER; ERR }
        kdec_bit=1;
        dcnt=3;
        mkdnur(3);
        outdtx();
        };
      if (nur < 0) {errmsg=E_SCALE;ERR};
      dsp_scl();
      }
  tare_flg=0;
  scale_bit=1;
  mul=nur;
  sdcnt1=dcnt;

  nur=0;
  dcnt=0;
  ncnt=0;
  kdec_bit=0;
  knur_bit=0;
}


/*****************************************************************************/
/***                        CONVERSION KEY                                 ***/
/*****************************************************************************/
void r_conv()
{
    long camt;

    if (regstep == RSTEP_RA || regstep == RSTEP_PO) { errmsg = E_KEY; ERR}
    if (knur_bit || regstep == RSTEP_END || (twostep_id & 0x7f)) { errmsg = E_KEY; ERR}
    convnk=func-CONV1;
    if (FUNCKEY[CONV1+convnk-CASH].HALO == 0) { errmsg = E_PGM; ERR}
    taxcal(taxable,tnd_tax);

    taxexm_set(0); /* for tax shift */

    rmtotl=gamt;
    rmtotl +=tax_sum(CASH,tnd_tax);
    if(SYS_OPT.OPT18_2 == 0)           /* Home base 981024 */
        {
        if(convnk == 0)
            {
            cal_divi(rmtotl,0,0,FUNCKEY[CONV1+convnk-CASH].HALO,
                    FUNCKEY[CONV1+convnk-CASH].KEY_ST.CONV_KEY.DECI_NO);
            }
        else
            {
            cal_multi(FUNCKEY[CONV1+convnk-CASH].HALO,
                    FUNCKEY[CONV1+convnk-CASH].KEY_ST.CONV_KEY.DECI_NO,
                    rmtotl,0,0);
            cal_divi(mvalue,mvalue2,FUNCKEY[CONV1+convnk-CASH].KEY_ST.CONV_KEY.DECI_NO,
                    FUNCKEY[CONV1-CASH].HALO,
                    FUNCKEY[CONV1-CASH].KEY_ST.CONV_KEY.DECI_NO);
            }
        }
    else                               /* Euro base */
        {
        cal_multi(FUNCKEY[CONV1+convnk-CASH].HALO,
                FUNCKEY[CONV1+convnk-CASH].KEY_ST.CONV_KEY.DECI_NO,
                rmtotl,0,0);
        }
    ban_olim();                           /* 981024 */
    conv1t=nur=camt=mvalue;
    mk_dnum(camt, lcdbuf,0);
    sprintf(lcdbuf1,"%c%s",PRT_OPT.OPT13[convnk],lcdbuf);
    get_fdesc(CONV1+convnk);
    mk_lline(lcdbuf1, 0, 16);
    pop_menu(lcdbuf,'|');

    mkdnur(0);
    dis9_out(D_SUBTOTAL);  /*0x6d;  S */
    dsp_tax(-2);

    conv_bit=1; /* conv_amt */
    conv_amt=nur;
    nur=0;
    rcnt=0;
    return;
}
/*****************************************************************************/
/***                           RETURN KEY                                  ***/
/*****************************************************************************/
void r_rtn()
{
    if (FUNCKEY[RETURN-CASH].KEY_ST.NORM_KEY.INACT) {
    errmsg = E_INACT; ERR}
    if (mode_id == VMODE || regstep >= RSTEP_RA  || vd2_bit) { errmsg = E_KEY; ERR}
    if (FUNCKEY[RETURN-CASH].KEY_ST.NORM_KEY.XONLY && !(mode_id & VXMODE)) { errmsg = E_XONLY; ERR}

    rcnt=0;
    rtn_bit=1;
    pop_menu(get_fdesc(RETURN),'|');
    if (!knur_bit) ini_outdtx();
    return;
}
/*****************************************************************************/
/***                           PRICE KEY                                   ***/
/*****************************************************************************/
#if 0
void price_view(char type)
{
    char sys_temp;

    sys_temp=SYS_OPT.OPT18_1;
    if (type == IS_DEPT) {nur=dept[func].price;load_dstat();}
    else {nur=plu[pcode].price;load_pstat();};
    if (negat_bit) nur=-nur;
    if (gas_bit) SYS_OPT.OPT18_1=3; /* X.XXX */
    mkdnur(0);
    mkdsp();
    price_flg=0;
    SYS_OPT.OPT18_1=sys_temp;
    initseq();

    return;
}
#endif
/**********************************************************/
/**                CANCEL MEMORY UPDATE                  **/
/**********************************************************/
void cancel_cal()
{
    int  rr, dd;

    rr=0;

    while (rr < canclcnt) {
        dd=cancl[rr].roder;
        rep[dd].cnt -=cancl[rr].rcnt;
        cancl[rr].rcnt=0;
        rep[dd].total -=cancl[rr].rtotl;
        cancl[rr].rtotl=0;
        rr++;
        }

    clr_ex0();
    if (gamt != 0 && !train_flg) {
        rep[void4].cnt +=1;
        rep[void4].total +=gamt;
        rep[cvoid4].cnt +=1;
        rep[cvoid4].total +=gamt;
        gamt=0;
        };
    canclcnt=0;

    clr_flg = 1;                       /* PKR1223 Power Fail */
    set_ex0();
    return;
}

/*****************************************************************************/
/***                           CANCEL KEY                                  ***/
/*****************************************************************************/
void r_cancel()
{
//  chk_kpend();
  if (FUNCKEY[CANCEL-CASH].KEY_ST.NORM_KEY.INACT) {
    errmsg = E_INACT; ERR}

  if(regstep == RSTEP_END || twostep_id || regstep == RSTEP_STEND ||
      cantime > 30 || knur_bit) { errmsg = E_KEY; ERR}
  if ((FUNCKEY[CANCEL-CASH].KEY_ST.NORM_KEY.XONLY) && !(mode_id & VXMODE)) { errmsg = E_XONLY; ERR}

  if(halo_err(CANCEL,gamt)) { errmsg = E_HALO; ERR}

  if(regstep == RSTEP_RA)
      gamt = rapo_total;
  else if(regstep == RSTEP_PO)
      gamt = -rapo_total;

  ini_outdtx();
  cancel_cal();

  pop_lcd = 2;
  pop_menu(get_fdesc(CANCEL),'|');
  pop_lcd = 0;

  dis9_out(D_CHANGE);

  regstep = RSTEP_END;
  xoff_flg=1;
  EJ_FLAG = EJ_CANCEL;
  post_tamt=0;
  hash_amt=0;
  item_time = 0;
  kp_regr.pack_no = 0;
  prn_sfd(CANCEL,'*');
  endlogr();
  EJ_FLAG = EJ_NORMAL;
  return;
}

/*****************************************************************************/
/***                       PERCENT    KEY                                  ***/
/*****************************************************************************/
/*    ÚÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄ¿      */
/*    ³   X   ³pdirect³ popen ³pdiscnt³   X   ³pinact ³ppercnt³ pitem ³      */
/*    ÀÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÙ      */
/*---------------------------------------------------------------------------*/

void pstabl_up(char inf,long rate,char dr)
{                                                /* sale cal */
 if (!FUNCKEY[PER1+perno-CASH].KEY_ST.PCNT_KEY.AMOUNT) {                       /* per */
     cal_multi(rate,dr,taxable[inf],0,0);
     taxable[inf] +=round_func(27,mvalue,moksub[0]);
//     cal_multi(rate,dr,ataxabl[inf],0,0);
//     ataxabl[inf] +=round_func(27,mvalue,moksub[0]);
     } else {taxable[inf] +=rate;
//       ataxabl[inf] +=rate;
         };
 return;
}

void per_taxcals(long rate, char dr)
{
  if ((perstp_id & 0x01) && taxable[TAX1] != 0) pstabl_up(TAX1,rate,dr);
  if ((perstp_id & 0x02) && taxable[TAX2] != 0) pstabl_up(TAX2,rate,dr);
  if ((perstp_id & 0x04) && taxable[TAX3] != 0) pstabl_up(TAX3,rate,dr);
  if ((perstp_id & 0x08) && taxable[TAX4] != 0) pstabl_up(TAX4,rate,dr);
  if ((perstp_id & 0x09) && taxable[TAX14] != 0) pstabl_up(TAX14,rate,dr);
  if ((perstp_id & 0x0a) && taxable[TAX24] != 0) pstabl_up(TAX24,rate,dr);
  if ((perstp_id & 0x0c) && taxable[TAX34] != 0) pstabl_up(TAX34,rate,dr);
 if (!FUNCKEY[PER1+perno-CASH].KEY_ST.PCNT_KEY.AMOUNT) {                       /* per */
     cal_multi(rate,dr,gamt,0,0);
     gamt +=round_func(27,mvalue,moksub[0]);
     cal_multi(rate,dr,agamt,0,0);
     agamt +=round_func(27,mvalue,moksub[0]);
     } else {gamt +=rate;
        agamt +=rate;
        };
  return;
  }

/*****************************************************************************/
void percom()
{
  long temp2;
  long nur_temp;

  /* PERCENT & SALE COUPON & DIRECT */
  if (!FUNCKEY[PER1+perno-CASH].KEY_ST.PCNT_KEY.POSITIVE) {nur=-nur; EJ_FLAG |= EJ_MINUS;}
  if ((FUNCKEY[PER1+perno-CASH].KEY_ST.PCNT_KEY.AMOUNT) &&
    ((regstep == RSTEP_RTN) || (mode_id == VMODE))) nur=-nur;

  perstp_id = FUNCKEY[PER1+perno-CASH].KEY_ST.PCNT_KEY.TAX_1 |
      (FUNCKEY[PER1+perno-CASH].KEY_ST.PCNT_KEY.TAX_2 << 1) |
      (FUNCKEY[PER1+perno-CASH].KEY_ST.PCNT_KEY.TAX_3 << 2) |
      (FUNCKEY[PER1+perno-CASH].KEY_ST.PCNT_KEY.TAX_4 << 3);

  if (!FUNCKEY[PER1+perno-CASH].KEY_ST.PCNT_KEY.SALE) {                /* item */
     if (!FUNCKEY[PER1+perno-CASH].KEY_ST.PCNT_KEY.AMOUNT) {           /* rate */
        cal_multi(nur,2+dcnt,dptamt,0,0);
        mvalue = round_func(SYS_OPT.OPT21_1,mvalue,moksub[0]);
        nur=mvalue;
        };
//     sgamt=gamt+=nur;
//     asgamt=agamt+=nur;
     func=sfunc;
     result=nur;
     /* dept/plu update */

     cntint=0;
     if (func == PLU) {
        pcode=spcode;
        load_pstat();
        adcntl(tplu);                                     /* plu total */
        adcntl(pluup);                                    /* plu up */
    /*  negative dept/plu dis sur error  */
    /*  if above seq is correct, refer to dept routine */
        func=plu[pcode].link_dept-1;   /* linked dept no */
        };
     load_dstat();
     if (!negat_bit) adcntl(podept);
     else adcntl(nedept);
     adcntl(dptup);                /* dept up */
     adcntl(adjdpt);               /* adjust dept up */
     adcntl(g_base+dept[func].group);      /* dept group */
     adcntl(grp_total);                        /* dept group totl*/
     dptstp_id=dptsav_id;          /* previous step(D/P) load */
     dptstp1_id=dptsav1_id;        /* only_item */
//     if (hash_bit) {hash_amt +=result;adcntl(hashamt);};
     mk_reg_form(1);                             /* reg inital & make form */
     if (!((rstepsv_id & 0x0f) & (perstp_id & 0x0f))) {
        adcntl(nontaxamt);
        adcntl(cnontaxamt);
        };
     if (!vd1_bit) per_taxcali();
     }
  else {                        /* sale */
     nur_temp=nur;
     if (!vd1_bit) {
        if (!FUNCKEY[PER1+perno-CASH].KEY_ST.PCNT_KEY.AMOUNT) {           /* rate */
            cal_multi(nur,2+dcnt,gamt,0,0);
            mvalue = round_func(SYS_OPT.OPT21_1,mvalue,moksub[0]);
            nur=mvalue;
            };
        sgamt = gamt;
        pmemcpy((char *)staxable,(char *)taxable,sizeof(TAX_LEN));
        ssgamt=gamt;
//        sgamt=gamt+=nur;
//        asgamt=agamt+=nur;
        per_taxcals(nur_temp,2+dcnt);

        }
     else {
        if (!FUNCKEY[PER1+perno-CASH].KEY_ST.PCNT_KEY.AMOUNT) {           /* rate */
                cal_multi(nur,2+dcnt,ssgamt,0,0);
                mvalue = round_func(SYS_OPT.OPT21_1,mvalue,moksub[0]);
                        nur=mvalue;
            }
        };
     };
  /*----------------------------------------------------*/
  /*                   memory update                    */
  /*----------------------------------------------------*/
  cntint=0; result=nur;

  if (!FUNCKEY[PER1+perno-CASH].KEY_ST.PCNT_KEY.SALE && regstep == RSTEP_RTN) {        /* return */
     adcntl(retn); adcntl(cretn);
     };

  /* GROSS UPDATE */
  if (voidmd_flg != 1) {
     if ((FUNCKEY[PER1+perno-CASH].KEY_ST.PCNT_KEY.SALE && FUNCKEY[PER1+perno-CASH].KEY_ST.PCNT_KEY.POSITIVE) ||                  /* sale surcharge gross update */
     (!FUNCKEY[PER1+perno-CASH].KEY_ST.PCNT_KEY.SALE && FUNCKEY[PER1+perno-CASH].KEY_ST.PCNT_KEY.POSITIVE && regstep != RSTEP_RTN) ||  /* item surcharge & not rtn gross update */
     (!FUNCKEY[PER1+perno-CASH].KEY_ST.PCNT_KEY.SALE && !FUNCKEY[PER1+perno-CASH].KEY_ST.PCNT_KEY.POSITIVE && regstep == RSTEP_RTN)) { /* item dis rtn gross update */
    if (!FUNCKEY[PER1+perno-CASH].KEY_ST.PCNT_KEY.SALE && !FUNCKEY[PER1+perno-CASH].KEY_ST.PCNT_KEY.POSITIVE && regstep == RSTEP_RTN) {
       result =-result;
       adcntl(gross);
       result =-result;
       }
    else adcntl(gross);
    };
     };
  if (voidmd_flg == 1 && (FUNCKEY[PER1+perno-CASH].KEY_ST.PCNT_KEY.SALE || !FUNCKEY[PER1+perno-CASH].KEY_ST.PCNT_KEY.POSITIVE)) {
     result =-result;
     if (!(FUNCKEY[PER1+perno-CASH].KEY_ST.PCNT_KEY.SALE && FUNCKEY[PER1+perno-CASH].KEY_ST.PCNT_KEY.POSITIVE)) /* sale surch is not update to gross */
    adcntl(gross);
     result =-result;
     };
  if (vd1_bit) {
     cntint = 1;
     regstep=RSTEP_PVD1;   /* per void step */
     adcntl(void1);
     adcntl(cvoid1);
     cntint = -1;
     }
  else
     cntint=1;
  adcntl(per1tl+cpnfunc);
  adcntl(cper1tl+cpnfunc);


  regstep=RSTEP_PER;


  /*----------------------------------------------------*/
  /*                  print & display                   */
 lcd_rec(2);
 sv_lcd();
  /*----------------------------------------------------*/
  kdec_bit=0;  /* avoid for decimal disp */

  mkdnur(0);

  temp2=nur;
  func=cpnfunc;
  if (FUNCKEY[PER1+perno-CASH].KEY_ST.PCNT_KEY.SALE) ksub_bit=1;


  if (vd1_bit) {prn_sfd(ERR_CORR,'-');}; /* ERROR CORRECT */
  strcpy(prt_buffer,get_fdesc(PER1+perno));
  if (!FUNCKEY[PER1+perno-CASH].KEY_ST.PCNT_KEY.POSITIVE) {         /* discount */
        nur=-spnur;
        }
  else {        /* surcharge */
        nur=spnur;
        };
  if (!FUNCKEY[PER1+perno-CASH].KEY_ST.PCNT_KEY.AMOUNT) {                /* percent */
     prn_gcpt(1,3,1);
    sprintf(prt_buffer,s_amount);       /* dis amt */
     };
  nur=temp2;  /* tax inform */
  iosign_bit = 0;
  ionur_sign();
  if(vd1_bit == 0) {
      sprintf(lcdbuf," %s",prt_buffer);
      mk_idamt(nur,0,0,MAX_CLM,0,1,1);
      dsp_tax(-1);
      }
  sep_prn();

  initseq();
  cantime +=1;
  nona_bit=0;
  rcnt=0;        /* to avoid repeat */
  return;
}

/*****************************************************************************/
void r_per()
{
  char a;
  S_PCNT_KEY *pflg;

  if( menu_flg && (regstep == RSTEP_MENU2) )
    regstep = svrstep;

  if (regstep == RSTEP_END || regstep == RSTEP_SRT || regstep >= RSTEP_RA ||
     (rstep_id & 0x0f) || (twostep_id & 0xef) || taxsft_bit ) {
     errmsg = E_KEY; ERR
     }

  if ((!ksub_bit && regstep >= RSTEP_VD1 && regstep <= RSTEP_PVD1) ||
        /*   vd1, vd2, vd1-cpn, vd1-% */
      (!ksub_bit && (dptsav_id & 0x010))) { errmsg = E_KEY; ERR}        /* negative dept */

  perno = func-PER1;

  pflg = &(FUNCKEY[func-CASH].KEY_ST.PCNT_KEY);
  if (pflg->INACT) {
    errmsg = E_INACT; ERR}

  if (regstep == RSTEP_END || regstep == RSTEP_SRT || regstep >= RSTEP_RA ||
     (rstep_id & 0x0f) || (twostep_id & 0xef) || taxsft_bit ) {
     errmsg = E_KEY; ERR}

  if (pflg->XONLY && !(mode_id & VXMODE))
    { errmsg = E_XONLY; ERR}

  if ((ksub_bit && !pflg->SALE) || (!ksub_bit && pflg->SALE)) {
    errmsg = E_KEY; ERR
    }
  if (pflg->POSITIVE && pflg->AMOUNT && !pflg->SALE) {
    errmsg = E_PGM; ERR
    }
  /* percent - percent -> err */
  if (!ksub_bit && !pflg->AMOUNT && regstep == RSTEP_PER) {
    errmsg = E_KEY; ERR
    }
  /* negative item dept */
  if (!pflg->SALE && !pflg->AMOUNT && voidmd_flg != 1 && regstep != RSTEP_RTN &&
     dptamt <= 0) ERR;

  if (mul_bit) {
     if (!pflg->AMOUNT || pflg->SALE) {
       errmsg = E_KEY; ERR
       }
     if (pflg->AMOUNT && sdcnt1 != 0) {
       errmsg = E_KEY; ERR
       }
     }

  if (knur_bit) {
     if (!pflg->AMOUNT) {                            /* percent open override */
    if (dcnt > 3 || nur == 0 || ((ncnt - dcnt) > 2)) { errmsg = E_NUMOVER; ERR}
    for (a=dcnt; a<3; a++) nur*=10;            /* rate */
    dcnt=a;
    /* override check */
    if (!pflg->OVERRIDE) {
       if (pflg->PRESET) { errmsg = E_OVERRIDE; ERR}
       if(halo_err(func,nur)) { errmsg = E_HALO; ERR}
       }
     }
     else {
       if (nur == 0 || dcnt != 0 || ncnt > 5) { errmsg = E_NUMOVER; ERR}    /* amount */
    /* override check */
       if (!pflg->OVERRIDE) {
        if (pflg->PRESET) { errmsg = E_OVERRIDE; ERR}
        if(halo_err(func,nur)) { errmsg = E_HALO; ERR}
        }
       }
  }
  else {
     if (!pflg->PRESET) { errmsg = E_PRESET; ERR }
     nur=FUNCKEY[func-CASH].HALO;            /* preset */
     if (nur == 0) { errmsg = E_PGM; ERR}
     dcnt=3;
     };

  /* mulitiple check */
  if (pflg->AMOUNT && mul_bit && pflg->SALE) {       /*  sale COUPON */
     unit=nur;
     nur=nur*mul;
     };

  perstp_id = FUNCKEY[PER1+perno-CASH].KEY_ST.PCNT_KEY.TAX_1 |
      (FUNCKEY[PER1+perno-CASH].KEY_ST.PCNT_KEY.TAX_2 << 1) |
      (FUNCKEY[PER1+perno-CASH].KEY_ST.PCNT_KEY.TAX_3 << 2) |
      (FUNCKEY[PER1+perno-CASH].KEY_ST.PCNT_KEY.TAX_4 << 3);

  spnur=nur;
  spdcnt=dcnt;
  cpnfunc=func-PER1;
  persav_id=perstp_id;
//  persav1_id=perstp1_id;
//  if(!menu_flg) {
//      sv_lcd();
//      }
  lcd_rec(2);
  menu_flg = 0;
  pmenu_inx = 0;

  if (pflg->AMOUNT && !pflg->SALE) {                   /*  item COUPON */
     if (mul_bit) {nur=nur*mul;twosave_id=0x10;}
    else twosave_id=twosave_id & 0xef;
//     get_fdesc(func);
     sprintf(lcdbuf,"COUPON");
     pop_menu(lcdbuf,'|');
     mkdnur(0);
     initseq();
     cupn_bit = 1;
     return;
     };
  EJ_FLAG |= EJ_PER;
  percom();
//  EJ_FLAG = EJ_NORMAL;
  return;
}

/*****************************************************************************/
/***                          RECEIPT KEY                                  ***/
/*****************************************************************************/
void r_reissue()
{
 char a, b;

 if (regstep != RSTEP_END  || buft_cnt == 0 || (!SYS_OPT.OPT4_3 && !r_off) ){errmsg = E_KEY; ERR}


 if (!knur_bit) {
    end_mark=0;

    okbuf_bit=1;
    notbuf_bit=1;
    EJ_FLAG = EJ_NOPRT;

    for (b=0; b<buft_cnt; b++) {
        for (a=0; a<MAX_RJ; a++) prt_buffer[a]=stubbuf[a+b*MAX_RJ];
        ej_prn();
        }
    reissue=1;
    endlogo();
    reissue=0;
    EJ_FLAG = EJ_NORMAL;
    okbuf_bit=0;
    if (!SYS_OPT.OPT4_3) buft_cnt=0;
 }
 return;
}

/*****************************************************************************/
/***                          VOID    KEY                                  ***/
/*****************************************************************************/
void dptpluvd()
{
 if (pluon_bit && mst_pluno != 0) {
    nur= - pluvsnur;                 /* sunit or snur */
    if (mul_bit || scale_bit ) mul=smul;
    if (spl_bit) quant=squant;
    pcode=mst_pluno-1;
    twostep_id=m_plu_two;
    rstep_id=m_plu_rstep;
    load_pstat();
    vd1_bit=1;
    m_plu_two=0;
    m_plu_rstep=0;
    mst_pluno=0;
    dpcon();
    return;
    };

 nur=-snur;
 if (mul_bit || scale_bit ) {
    nur=-sunit;
    mul=smul;
    if (spl_bit) quant=squant;
    };

 if (nur < 0) sign_bit=1;
 if (pluon_bit) pcode=spcode;
 dpcon();
 return;
}

/*****************************************************************************/
void r_void()
{
  if (regstep == RSTEP_END || regstep >= RSTEP_RA || knur_bit || regstep == RSTEP_SRT ||
      (twostep_id & 0xef)) { errmsg = E_KEY; ERR}

  if (mul_bit || kclr_bit) {
//     chk_kpend();
     if (FUNCKEY[VOID-CASH].KEY_ST.NORM_KEY.INACT) {
       errmsg = E_INACT; ERR}
     if (kdec_bit) {
        errmsg = E_NUMOVER; ERR}
     if(FUNCKEY[VOID-CASH].KEY_ST.NORM_KEY.XONLY && !(mode_id & VXMODE))
        { errmsg = E_XONLY; ERR}
     if (mul_bit == 0) mul=0;


     pop_menu(get_fdesc(VOID),'|');
     initseq();
     ini_outdtx();
     if (mul != 0) mul_bit=1;
     void_bit=1;outdtx();
     vd2_bit=1;
     }
  else {
     if (FUNCKEY[ERR_CORR-CASH].KEY_ST.NORM_KEY.INACT) {
       errmsg = E_INACT; ERR}
     if (kdec_bit) {
        errmsg = E_NUMOVER; ERR}
     if(FUNCKEY[VOID-CASH].KEY_ST.NORM_KEY.XONLY && !(mode_id & VXMODE))
        { errmsg = E_XONLY; ERR}
     if ((regstep >= RSTEP_VD1 && regstep <= RSTEP_PVD1) ||
     /* regstep == RSTEP_RTN || */ ksub_bit) { errmsg = E_KEY; ERR}
     if (pluon_bit && mst_pluno != 0) nur = pluvsnur;
     else nur = snur;
     if(halo_err(ERR_CORR,nur)) { errmsg = E_HALO; ERR}

     void_bit=1;
     if (regstep <= RSTEP_CPN) {
    loadseq();
    /* dept plu error correct */
    rcnt=0;
    vd1_bit=1;
    dptpluvd();
    lcd_rec(1);
    sv_put = (sv_put -1 + MAX_SV_LINE) % MAX_SV_LINE;
    }
     else { /* % error correct % */
    if (twosave_id & 0x01) { errmsg = E_KEY; ERR} /* rtn -dpt - % - vd -> err */
    if(halo_err(ERR_CORR,spnur)) { errmsg = E_HALO; ERR}
    nur=-spnur;
    dcnt=spdcnt;
    func=cpnfunc;
    lcd_rec(1);
    perstp_id=persav_id;
    /* rtn -dpt - % - vd -> err
    if ((!FUNCKEY[PER1+perno-CASH].KEY_ST.PCNT_KEY.SALE && (twosave_id & 0x01)) ||
        (FUNCKEY[PER1+perno-CASH].KEY_ST.PCNT_KEY.SALE && (sgamt <= 0))) { errmsg = E_KEY; ERR}
    if (!FUNCKEY[PER1+perno-CASH].KEY_ST.PCNT_KEY.AMOUNT && FUNCKEY[PER1+perno-CASH].KEY_ST.PCNT_KEY.SALE) {
       gamt=ssgamt;
       taxable[0]=staxable[0];
       taxable[1]=staxable[1];
       taxable[2]=staxable[2];
       taxable[3]=staxable[3];
       };
    */
    gamt = sgamt;
    pmemcpy((char *)taxable,(char *)staxable,sizeof(TAX_LEN));
    vd1_bit=1;     /* more think */
    percom();
    regstep = RSTEP_VD1;
    };
    dsp_tax(-1);
     };
  return;
}

/*****************************************************************************/
#if 0
void src_dcnt(int *d)
{
  for (*d=3; *d>0 && (nur%10)==0; (*d)--) nur/=10;
  return;
}

/*****************************************************************************/
void mul_prt(char c)
{
  int d;

  if (table[table_no_flg].t_cnt[c] != 1000) {
     nur=table[table_no_flg].t_cnt[c];
     src_dcnt(&d);
     fdec_inx=0;
     prn_fdec(d,P_X);
     cal_multi(nur,d,table[table_no_flg].t_price[c],0,0);
     nur=table[table_no_flg].t_price[c];
     lgol_bit=1;sep_prn();
     mvalue = round_func(SYS_OPT.OPT22_1,mvalue,moksub[0]);
     nur=mvalue;
     }
  return;
}
/*****************************************************************************/
/* check tender / clerk close */
void r_chktnd(char type)
{
/*  char inxx;
  char a,c;
  int  d;*/
}
#endif

void r_menu()
{
// if( (mode_id & RVPMODE) || ( (mode_id == XMODE) && (regstep != RSTEP_END) ) ) {
   if( mode_id & RVXPMODE ) {
//       if(ncnt) { errmsg = E_NUMOVER; ERR}
       if(menu_flg == 3) { errmsg = E_KEY; ERR}
//       if(menu_flg) return;
        if(!menu_flg)
                svrstep = regstep;
        if(mode_id == VMODE)
                   voidmd_flg = 1;
        if((pop_lcd == 0) && (mode_id != PMODE))
              sv_lcd();
//        else lcd_rec(1);
        pop_lcd = 1;
       menu_flg = (menu_flg+1) % 2;
       if(menu_flg == 0) menu_flg = 2;
//         menu_flg = 1;
       if(!ncnt)
              func_menu();
       if(mode_id != PMODE)
           regstep = RSTEP_MENU1;
       return;
       }
  else { errmsg = E_KEY; ERR}
}

void r_misc()
{
// if( (regstep == RSTEP_RA) || (regstep == RSTEP_PO)) { errmsg = E_KEY; ERR}
 if( ( (mode_id & RVXMODE) && (regstep != RSTEP_END)) || (mode_id == PMODE) ) {
//       if(ncnt) { errmsg = E_NUMOVER; ERR}
       if( (menu_flg == 1) || (menu_flg == 2)) { errmsg = E_KEY; ERR}
       if(menu_flg) return;
       svrstep = regstep;
       if(pop_lcd == 0)
             sv_lcd();
       else
             lcd_rec(1);

       pop_lcd = 1;
       menu_flg = 3;
       if(!ncnt)
              func_menu();
       if(mode_id != PMODE)
           regstep = RSTEP_MENU1;
       return;
       }
  else { errmsg = E_KEY; ERR}

}
void r_dptsft()
{
//  chk_kpend();
  if (regstep >= RSTEP_RA) { errmsg = E_KEY; ERR}
  if( (mode_id & RVMODE) || ((mode_id == XMODE) && (regstep != RSTEP_END)) ) {
//  if(ncnt) { errmsg = E_NUMOVER; ERR}
    if(FUNCKEY[DEPT_SFT-CASH].KEY_ST.SFT_KEY.INACT) {
    errmsg = E_INACT; ERR }
#if 0
    if(FUNCKEY[DEPT_SFT-CASH].KEY_ST.SFT_KEY.XONLY && !(mode_id & VXMODE)) {
        errmsg = E_XONLY; ERR }
#endif
    lcd_dsp(0);
    get_fdesc(DEPT_SFT);
    pop_menu(lcdbuf,'|');
    if(FUNCKEY[DEPT_SFT-CASH].KEY_ST.SFT_KEY.POP_UP)
        dsft_flg ^= 1;
    else
        dsft_flg = 1;

    return;
        }
   else { errmsg = E_KEY; ERR}
}
