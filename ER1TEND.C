#include <stdio.h>
#include <er1io51.h>
#include <er1exmt.h>
#ifndef BCDBG
#include  <exs03.h>
#else                                  /* BCDBG */
#include  <exdbg.h>
#endif                                 /* BCDBG */

extern int mk_dnum(long, UBYTE*, char);
extern void cal_multi(long long1, char d1, long long2_1, long long2_2, char d2);
extern void mk_lline(unsigned char *rbuf,UBYTE x,int end);
extern void mkrandom(long value,char ofst,char st);
extern void r_reissue();        /* yoo0919 */
extern char chk_dwrlimit();
extern void adcntl(int index);
//PKR0624 extern void clr_ex0();
//PKR0624 extern void set_ex0();
extern void cal_divi(long long1_1, long long1_2, char d1, long long2, char d2);
extern void credttaxcal();
extern long cal_subt();
extern void open_drw();
extern void delay();
extern void ej_prn();
extern void des_prn();
extern void lcd_rec(char type);
extern void dis9_out(char what);
extern void endlogr();
//PKR0624 extern void inidtx();
//PKR0624 extern void initseq();
extern void logo_only(char type);
extern void logo_nur(char type);
extern void mk_cprn(char cinx);
extern void mkdnur(char inf);
//PKR0624 extern void outdtx();
extern void prn_gcpt(char type,char dec,char lcd_f);
extern void prn_ctend(char lcd_f);
extern void prn_fdec(char dec,char type);
extern void rapo_tend();
extern void sep_prn();
extern void taxcal(long *tax_able,long *tax_amt);
extern void ttax_prn(long *tax_able,long *tax_amt);
extern void wait_pover();
extern void mk_idmsg( unsigned char *desc, long amt,UBYTE stay, UBYTE sp);
extern void mk_tdmsg( unsigned char *desc, long amt, UBYTE x, UBYTE y, UBYTE end);
extern UBYTE *get_fdesc(unsigned int);
extern void taxexm_set(int kfunc);
extern void dsp_str(UBYTE x, UBYTE y, UBYTE *str);
extern void dsp_tax(int type);
extern void mk_idamt(long amt, UBYTE x, UBYTE y, UBYTE end , UBYTE stay, UBYTE sp, char sym);
extern void chk_kpend();
extern void cmemcpy(UBYTE *, UBYTE *, UBYTE);
extern void send_kp();

extern const UBYTE s_chrate[12];

/*****************************************************************************/
void ad_drwtl()
{
  adcntl(drwtl);adcntl(cdrwtl);
  return;
}
/*****************************************************************************/
void prn_tend(char dinx,unsigned int kfunc,char lcd_f)
{
    static char *tend_flg[]={
        "CASH-IN-D ","CHECK-IN-D ",
        "CHANGE","TOTAL","","",
        "","","",
        "","",""
        };
    if((mode_id == VMODE) && (dinx == DINX_CNG)) nur = -nur;

    if(((kfunc >= CASH) && (kfunc <= CONV4)) || (kfunc == NONADD))
        strcpy(prt_buffer,get_fdesc(kfunc));
    else{
        sprintf(prt_buffer,"%s",tend_flg[dinx-DINX_CASH]);
        };
    if(lcd_f && !gnd_bit)
        {
        if ((regstep != RSTEP_RA) && (regstep != RSTEP_PO) && (dinx != DINX_NONADD))
            dsp_tax(kfunc);
        if( (dinx != DINX_CNG) && (dinx != DINX_TOTAL) )
            {
            mk_idmsg(prt_buffer,nur,0,1);
            if ((regstep != RSTEP_RA) &&(regstep != RSTEP_PO) &&
                (regstep != RSTEP_STEND) && !cng_bit && (dinx != DINX_NONADD) )
                mk_tdmsg(tend_flg[DINX_CNG-DINX_CASH],0,9,6,MAX_CLM);
            }
        else {
            mk_tdmsg(tend_flg[dinx-DINX_CASH],nur,9,6,MAX_CLM);
            }
        }

    if(lcd_f != 2)
        sep_prn();
    if((mode_id == VMODE) && (dinx == DINX_CNG)) nur = -nur;
    return;
}

void ban_olim()
{
  if (mvalue < 0) mvalue=-mvalue;
  mvalue+=(moksub[0]+5)/10;  /* 445 0  round */
  if (cal_nega) mvalue=-mvalue;
  return;
}

void prn_euro(char opt1, char opt2)         /* 980605  981210*/
{
    if(opt2 != 5)
    {
        if (FUNCKEY[CONV1-CASH].HALO == 0) return;
        if(SYS_OPT.OPT18_2 == 0)           /* Home base 981024 */
		    {
    	    cal_divi(nur,0,0,FUNCKEY[CONV1-CASH].HALO,
        	        FUNCKEY[CONV1-CASH].KEY_ST.CONV_KEY.DECI_NO);
		    }
	    else							   /* Euro base */
		    {
    	    cal_multi(FUNCKEY[CONV1-CASH].HALO,
        	        FUNCKEY[CONV1-CASH].KEY_ST.CONV_KEY.DECI_NO,nur,0,0);
		    }
	    ban_olim();
        if(opt2 == 1)
            conv0t = mvalue;
        else if(opt2 == 2)
            conv0e = mvalue;
    }
    else
    {
        mvalue = conv0e - conv0t;
    }
    if(opt1 == 0)
        return;
    mk_dnum(mvalue, lcdbuf,0);
    sprintf(prt_buffer,"%c  %s",PRT_OPT.OPT13[0],lcdbuf);
    ej_prn();
}
void prn_conv2(char opt1, char opt2)                /* 981210 */
{
//    if(!conv_bit)               /* 990122 990128*/
//        return;
    if(opt2 != 5)
    {
        if (FUNCKEY[CONV1-CASH].HALO == 0) return;
        if (FUNCKEY[CONV1+convnk-CASH].HALO == 0) return;
        if(SYS_OPT.OPT18_2 == 0)           /* Home base */
		    {
    	    cal_multi(FUNCKEY[CONV1+convnk-CASH].HALO,
        	        FUNCKEY[CONV1+convnk-CASH].KEY_ST.CONV_KEY.DECI_NO,nur,0,0);
    	    cal_divi(mvalue,mvalue2,FUNCKEY[CONV1+convnk-CASH].KEY_ST.CONV_KEY.DECI_NO,
                    FUNCKEY[CONV1-CASH].HALO,  /* 990111 */
        	        FUNCKEY[CONV1-CASH].KEY_ST.CONV_KEY.DECI_NO);
		    }
	    else							   /* Euro base */
		    {
    	    cal_multi(FUNCKEY[CONV1+convnk-CASH].HALO,
        	        FUNCKEY[CONV1+convnk-CASH].KEY_ST.CONV_KEY.DECI_NO,nur,0,0);
		    }
	    ban_olim();
        if(opt2 == 1)
            conv1t = mvalue;
        else if(opt2 == 2)
            conv1e = mvalue;
    }
    else
    {
        mvalue = conv1e - conv1t;
    }
    if(opt1 == 0)
        return;
    mk_dnum(mvalue, lcdbuf,0);
    sprintf(prt_buffer,"%c  %s",PRT_OPT.OPT13[convnk],lcdbuf);
    ej_prn();
}
/*****************************************************************************/
/**                       tend memory update                                **/
/*****************************************************************************/
void nexmtax_up(char tax_inf,char taxmix)
{
//  cntint = 0;
//  result = taxable[tax_inf];
//  adcntl(taxm1abl+tax_inf);
  if (taxmix != 0) {
     taxable[tax_inf]=taxable[taxmix]=0;
     ctaxable[tax_inf]=ctaxable[taxmix]=0;
     }
     else {
        taxable[TAX4]=ctaxable[TAX4]=0;
        taxable[TAX14]=ctaxable[TAX14]=0;
        taxable[TAX24]=ctaxable[TAX24]=0;
        taxable[TAX34]=ctaxable[TAX34]=0;
        };
  tnd_tax[tax_inf]=0;
  return;
  }

void tndmodup()
{
  char a;

  clr_ex0();

  result=nur;
  cntint=1;
  if (mode_id == VMODE) cntint=-cntint;

  if (func == CASH) adcntl(cshsale);
  if (func == CASH && (!conv_bit || conv_amt == 0)) {
     adcntl(cshindw);
     adcntl(ccshindw);
     }; /* clerk update */

  if (cng_bit && conv_bit && conv_amt != 0) {
     cntint=0; result=-change_amt; adcntl(cshindw); adcntl(ccshindw);
     ad_drwtl();
     if (regstep != RSTEP_STEND) cntint=1;
     result=nur;
     };
  if (func == CHECK && (!conv_bit || conv_amt == 0)) {  /* 981219 */
     adcntl(chksale);
     adcntl(chkindw);
     adcntl(cchkindw);
     ad_drwtl();
     if (cng_bit) {
        cntint=0; result=-change_amt; adcntl(cshindw); adcntl(ccshindw);
        result=change_amt;
        adcntl(chkindw);
        adcntl(cchkindw);
        if (regstep != RSTEP_STEND) cntint=1;
        result=nur;
        };
     };

  if ( (func >= MISCTND1) && (func <= MISCTND4) &&
        (!conv_bit || conv_amt == 0)) {  /* 981219 */
     a = func-MISCTND1;
     adcntl(misc1sale+a);
     adcntl(misc1dw+a);
     adcntl(cmisc1dw+a);
     ad_drwtl();
     if (cng_bit) {
    cntint=0; result=-change_amt; adcntl(cshindw); adcntl(ccshindw);
    result=change_amt;
    adcntl(misc1dw+a);
    adcntl(cmisc1dw+a);
    if (regstep != RSTEP_STEND) cntint=1;
    result=nur;
    };
     };
//  if (func == CHARGE1 || func == CHARGE2) {
//     adcntl(chgsale1+func-CHARGE1);
//    ad_drwtl();
//   };
                          /* clerk update */
  if (tnd_bit) cntint=0;
  if (audct_bit) adcntl(audact);

  adcntl(netsale);
  amount1=result;
  adcntl(cnetsale);
  result=amount1;

  rtc_read();
  adcntl(timeup);
  adcntl(tmtotl);
  /* daily total update */
  adcntl(dailyup-1);
  adcntl(datotl);

  cntint=0;
  if ((func == CASH || func == CHECK) && (!conv_bit || conv_amt == 0))  /* 981219 */
     ad_drwtl();

//  if (hash_amt != 0 && !(SYS_OPT.OPT13_1)) {
//     cntint=0; result = -hash_amt;
//     adcntl(netsale); adcntl(cnetsale);
//     };
  hash_amt=0;
  if (conv_bit && conv_amt != 0) {
     cntint =0; result=conv_amt;       /* 981219 */
     if (func == CASH)
        adcntl(conv1+convnk*6);
     else if (func == CHECK)
        adcntl(conv1+convnk*6+1);
     else
        adcntl(conv1+convnk*6+(func-MISCTND1)+2);
     };
  if (!tnd_bit) {
     if (mode_id == VMODE) {
        cntint=1; result=tndtotal; adcntl(void3); adcntl(cvoid3);
        };

     /* normal exempt tax update */
     if (emtax1_bit) nexmtax_up(TAX1,TAX14);
     if (emtax2_bit) nexmtax_up(TAX2,TAX24);
     if (emtax3_bit) nexmtax_up(TAX3,TAX34);
     if (emtax4_bit) nexmtax_up(TAX4,0);

     /* tax amount update */
     cntint=0;
     for (a=0; a<MAX_TAX; a++){
         result = taxable[a];
         adcntl(tax1abl+a);
         adcntl(ctax1abl+a);
         result=tnd_tax[a]; adcntl(tax1amt+a);
         adcntl(ctax1amt+a);
         if (vat_inp[a] != 1 && mode_id != VMODE) adcntl(gross);
         }

     /*----------- credit tax update -------------*/
     credttaxcal();       /* credit tax cal */
#if 0
     if (table_no_flg != 0) {
        table[table_no_flg].t_active=0;
        /*buf_cnt=30; onlytd_bit=0;*/
        table_no_flg=0;
        };
#endif
     };

  pfend_flg=1;
  set_ex0();
  return;
}

/*****************************************************************************/
/*****                                                                    ****/
/*****                         T E N D  M A I N                           ****/
/*****                                                                    ****/
/*****************************************************************************/
/*****************************************************************************/
char halo_err(unsigned int kfunc,long lval)
{
       if ( (mode_id != XMODE) && FUNCKEY[kfunc-CASH].HALO && (FUNCKEY[kfunc-CASH].HALO < lval) )
    return(E_HALO);
 return(SUCCESS);
}

void tax4_exmt(long *tax_amt)
{
  *(&tax_amt[TAX1]) -=mix_taxamt[TAX1];
  *(&tax_amt[TAX2]) -=mix_taxamt[TAX2];
  *(&tax_amt[TAX3]) -=mix_taxamt[TAX3];
  return;
}
void
prn_order()
{
    if(PRT_OPT.OPT4_4) {
        sprintf(lcdbuf," * ORDER#");
        mkrandom((long)PRT_OPT.OPT5,1,1);
        mkrandom((consno+1) % 100,3,1);
        prt_buffer[8] = 0;
        prt_buffer[6] = prt_buffer[3];
        prt_buffer[4] = prt_buffer[2];
        prt_buffer[2] = prt_buffer[1];
        prt_buffer[1] = prt_buffer[3] = prt_buffer[5] = prt_buffer[7] = 0x11;
        mk_lline(prt_buffer,0,MAX_CLM);
        sprintf(prt_buffer,"%s *",lcdbuf);
        ej_prn();
        }
}

void tend_com()
{
 long io_amount;
 char idx,drw=0;

 sub_endr = 0;                         /* To keep Order # while p fail */
 if (regstep != RSTEP_STEND) {  /* not split tend  */
    if (mode_id != VMODE) {
       for (idx=0; idx<TAX_KIND; idx++)
       if (taxable[idx] < 0)
          ctaxable[idx]=taxable[idx];
       };

    tnd_total=gamt;
    /* tax exempt total selection */
    taxcal(taxable,tnd_tax);
    taxexm_set(func);
    rstep1_id=taxexm_flg;
    if (emtax4_bit) tax4_exmt(tnd_tax);
    if (!emtax1_bit && vat_inp[0] != 1) tnd_total +=tnd_tax[TAX1];
    if (!emtax2_bit && vat_inp[1] != 1) tnd_total +=tnd_tax[TAX2];
    if (!emtax3_bit && vat_inp[2] != 1) tnd_total +=tnd_tax[TAX3];
    if (!emtax4_bit && vat_inp[3] != 1) tnd_total +=tnd_tax[TAX4];

    /* european rounding & subtotal */
    io_amount=nur;
    pfail_amt=tnd_total;

    nur=io_amount;

    if (mode_id != VMODE && knur_bit && tnd_total < 0) { errmsg = E_KEY; ERR }
    if (mode_id != VMODE) {
       if(tnd_total <= 0) {
           if ( ( ((tnd_total < 0) && SYS_OPT.OPT6_2) || ( (tnd_total == 0) &&
        SYS_OPT.OPT6_3)) && !(mode_id & VXMODE)) {
          errmsg = E_XONLY; ERR
          }
           else
          audct_bit=1;

      }
       else audct_bit=0;
       };
    tndtotal=tnd_total;
    }  /* not split tend */
 else {
      tnd_bit=1;
      nodtax_bit = 1;
      }

 if (func == CASH) {
    post_tamt=tnd_total;
    EJ_FLAG |= EJ_CASH;
    }
 else post_tamt=0;

 if(func == CHECK)
    EJ_FLAG |= EJ_CHECK;

 if ((func >= MISCTND1) && (func <= MISCTND4)) {
    EJ_FLAG |= EJ_MISC;
    if(FUNCKEY[func-CASH].KEY_ST.MISC_KEY.REQ_NONADD && !nona_bit) {
        errmsg = E_CNONADD; ERR
        }
    }

 if (!knur_bit) {                /* no amt tendering */
    /* amt tnd not allow */
    if ((tnd_total > 0) &&
            ((((func == CASH) || (func == CHECK)) && FUNCKEY[func-CASH].KEY_ST.CASH_KEY.COMP_AMT) ||
            (((func >= MISCTND1) && (func <= MISCTND4)) && FUNCKEY[func-CASH].KEY_ST.MISC_KEY.COMP_AMT) )){
     errmsg = E_AMTTND; ERR
     }
    if(halo_err(func,tnd_total)) { errmsg = E_HALO; ERR}

    nur=io_amount=tnd_total;
    regstep=RSTEP_END;xoff_flg=1;
    conv_bit=0;
    };
 if (knur_bit) {   /* amount tendering */
    if (halo_err(func,nur)) { errmsg = E_HALO; ERR }

    if (mode_id == VMODE) nur=-nur;
    if (conv_bit && conv_amt != 0) { /* conversion function */
       EJ_FLAG |= EJ_MISC;
       amount1=nur;

    if (nur != conv_amt) {
      if(SYS_OPT.OPT18_2 == 0)           /* Home base 981024 */
	    {
        cal_multi(FUNCKEY[CONV1-CASH].HALO,
            FUNCKEY[CONV1-CASH].KEY_ST.CONV_KEY.DECI_NO,
            nur,0,0);
		if(convnk != 0)
        	cal_divi(mvalue,mvalue2,FUNCKEY[CONV1-CASH].KEY_ST.CONV_KEY.DECI_NO,
        	FUNCKEY[CONV1+convnk-CASH].HALO,
            		FUNCKEY[CONV1+convnk-CASH].KEY_ST.CONV_KEY.DECI_NO);
		}
	  else
	    {
        cal_divi(nur,0,0,FUNCKEY[CONV1+convnk-CASH].HALO,
            	FUNCKEY[CONV1+convnk-CASH].KEY_ST.CONV_KEY.DECI_NO);
		}
      ban_olim();
      snur=nur=mvalue;
      }
       else {
      snur=nur=tnd_total;
      };
       conv_amt=amount1;
       };
    result=tnd_total-nur;

    if ((mode_id == VMODE && result < 0) ||
    (mode_id != VMODE && result > 0)) {
       /* yet finalized */
       /* under tend not allow */
           if ( ( ((func == CASH) || (func == CHECK)) && !FUNCKEY[func-CASH].KEY_ST.CASH_KEY.UNDER_T ) ||
         ( ((func >= MISCTND1) && (func <= MISCTND4)) && !FUNCKEY[func-CASH].KEY_ST.MISC_KEY.UNDER_T) ) {
            errmsg = E_UNDERTND; ERR
            }
       tnd_total=gamt=result;
       io_amount=nur;                  /* for print/disp   */
       regstep=RSTEP_STEND;            /* split tend       */
    }

    if ((mode_id == VMODE && result > 0) ||
    (mode_id != VMODE && result < 0)) {
       /* over tend not allow */
       if ( !(mode_id & VXMODE) &&
            ( ( ((func == CASH) || (func == CHECK)) && FUNCKEY[func-CASH].KEY_ST.CASH_KEY.OVER_IN_X ) ||
            ( ((func >= MISCTND1) && (func <= MISCTND4)) && FUNCKEY[func-CASH].KEY_ST.CASH_KEY.OVER_IN_X) )) {
        errmsg = E_XONLY; ERR
        }
//       tnd_total=gamt=result;
//       io_amount=nur;                  /* for print/disp   */
//       regstep=RSTEP_STEND;            /* split tend       */
       };
    if (result == 0){
       nur=tnd_total;       /* ending step */
       io_amount=nur;       /* for print   */
       cng_bit=1;
       regstep=RSTEP_END;xoff_flg=1;
       };

    if ((mode_id == VMODE && result > 0) ||
    (mode_id != VMODE && result < 0)) {
#if 0
       /*  change step     */
       if (func == CHARGE1 || func == CHARGE2 ||
       (func == CHECK && chk_chalo != 0 && -result > chk_chalo)) ERR;
#endif
       cng_bit=1;
       change_amt =-result;                /* d/p */
       io_amount=nur;                      /* for print        */
       nur =tnd_total;                     /* for update       */
       regstep=RSTEP_END;xoff_flg=1;
       };
    }; /* amount tendering */

 /*====================================================================*/
 tndmodup();
 /*====================================================================*/

 /*=================   display tender amt   ===========================*/
 nur=tnd_total;         /* for display */
 if (cng_bit) {
    nur=change_amt;
    if (mode_id == VMODE) nur=-nur;
    };
 mkdnur(0);

 flg_dis_txtmp[9]=D_TENDER; /*0x48; = */
 if (regstep == RSTEP_STEND) flg_dis_txtmp[9]=D_SUBTOTAL;  /*0x6d; S */
 if (cng_bit) flg_dis_txtmp[9]=D_CHANGE;  /*0x39; C */
 outdtx();

/*===========   tender amt print & memory up   ==========================*/
 if (regstep == RSTEP_END || cng_bit) {
    if( (func == CASH) || (func == CHECK) )
        drw = FUNCKEY[func-CASH].KEY_ST.CASH_KEY.OPEN_DRW;
    else if( (func >= MISCTND1) && (func <= MISCTND4))
        drw = FUNCKEY[func-CASH].KEY_ST.MISC_KEY.OPEN_DRW;
    if ( drw ) open_drw();
    };

 nur=amount1=io_amount;

 if (!tnd_bit) {
    tnd_bit=1;

    amount1=nur;

    if (PRT_OPT.OPT11_1) {
       nur=item_time;item_time=0;
       fdec_inx=6;
       prn_fdec(2,P_No);des_prn();    /* sale of item print */
       };

//    if (addcktnd == 0) {
       if (PRT_OPT.OPT9_1) {       /* system option 1 ST */
//      nur=sgamt; logo_nur(18);
      nur=cal_subt(); logo_nur(18);    /* 980513 */
      };
       ttax_prn(taxable,tnd_tax);
//       };

    nur=tndtotal;
    prn_tend(DINX_TOTAL,0,0);
    prn_euro(PRT_OPT.OPT12_2, 1);
    prn_conv2(((PRT_OPT.OPT12_2) && (PRT_OPT.OPT12_7) && (convnk)), 1);
    nur=amount1;
    };

 chk_kpend();

 /*=======================   print   ====================================*/
 if (!conv_bit) {
    prn_ctend(1);
    prn_euro(PRT_OPT.OPT12_3, 2);
#if 0
    if (func == CHARGE1 || func == CHARGE2) {
       cng_bit=0; prn_tend(DINX_CHG1+func-CHARGE1,1);
       };
#endif
    if (cng_bit) {
       gnd_bit=1;       /* for validation format not print */
       nur=tnd_total;
       prn_ctend(1);

       nur=amount1;     /* tendered amt */
       };
    };

 if (conv_bit) { /* conversion function */
    if (PRT_OPT.OPT12_5)             /* 981210 */
    {
       nur=conv_amt;
       lgol_bit=1;
       strcpy(lcdbuf,get_fdesc(CONV1+convnk));   /* 981219 */
       if(func == CASH)
           sprintf(prt_buffer," %s(CA",lcdbuf);
       else if(func == CHECK)
           sprintf(prt_buffer," %s(CH",lcdbuf);
       else
           sprintf(prt_buffer," %s(M%d",lcdbuf,func-MISCTND1+1);
       sprintf(lcdbuf," %s",prt_buffer);
       mk_idamt(nur,0,0,MAX_CLM,0,1,1);
       sep_prn();
    }
    nur=FUNCKEY[CONV1+convnk-CASH].HALO;
    sprintf(prt_buffer,s_chrate);
    lsharp_bit=1;prn_gcpt(0,FUNCKEY[CONV1+convnk-CASH].KEY_ST.CONV_KEY.DECI_NO,1);
    nur=snur;                        /* 990115 */
    if (PRT_OPT.OPT12_6)             /* 981210 */
       logo_nur(20);
    prn_euro(convnk && PRT_OPT.OPT12_6 && PRT_OPT.OPT12_3, 2);
    if(convnk)
       conv1e = conv_amt;
    else                        /* 990105 */
       conv0e = conv_amt;
    conv_bit=0;
    }
 else                                  /* 990128 */
    convnk = 0;
 if (regstep == RSTEP_STEND) {
    nur=tnd_total;
    prn_tend(DINX_TOTAL,0,1);
    prn_euro(PRT_OPT.OPT12_2, 1);
    };

 if (cng_bit) {
    nur=change_amt;
    if (mode_id == VMODE) nur=-nur;
    prn_tend(DINX_CNG,0,1);
    prn_euro(PRT_OPT.OPT12_4, 5);
    prn_conv2((PRT_OPT.OPT12_4) && (PRT_OPT.OPT12_8) && (convnk),5);
    };

 if (regstep == RSTEP_END || cng_bit) {
    wait_pover();
    prn_order();
    endlogr();
    send_kp();
#if 0
    if (system[SINX_47] == _SP_OPN) {
       if (stable_no != 0) comm_slip(stable_no,1);
       }
    else comm_kp(0);
#endif
    if (chk_dwrlimit()) { errmsg = E_DRWOVER; ERR }
       };

 if (regstep == RSTEP_STEND) {
    initky();
    taxable[0]=taxable[1]=0;taxable[2]=taxable[3]=0;
    };
 return;
}

/*****************************************************************************/
/***                         TENDERING                                     ***/
/*****************************************************************************/
void r_tender()
{

// if ( (regstep == RSTEP_MENU1) || (regstep == RSTEP_MENU2) ) ERR;
 if (regstep >= RSTEP_RA && regstep <= RSTEP_BACKRA){
    rapo_tend();
    return;
    };

 if ((regstep == RSTEP_END) || ((func == CHECK) && (regstep == RSTEP_SRT))) {
    /*******************************/
    /**       Buffered receipt    **/
    /*******************************/
    if (ncnt == 0) {r_reissue();return;};
    /*******************************/
    /**       Check-Cashing       **/
    /*******************************/
    if (func == CHECK)  {
       if (ncnt > 8 || nur == 0 || kdec_bit) { errmsg = E_NUMOVER; ERR}
       if(mode_id == VMODE) { errmsg = E_KEY; ERR}
       if(!SYS_OPT.OPT3_2) { errmsg = E_INACT; ERR}
//       if(SYS_OPT.OPT3_3 && !(mode_id & VXMODE)) {errmsg = E_XONLY; ERR}
       if(halo_err(CHECK,nur)) { errmsg = E_HALO; ERR}
       cntint=1;result=nur;adcntl(chkindw);
       xoff_flg=1;
       regstep = RSTEP_END;
       cntint=0;result=-nur;adcntl(cshindw);
       dis9_out(D_CHANGE);
       open_drw();
       EJ_FLAG = EJ_FLAG | EJ_CASH | EJ_CHECK;
       clr_lcd();
       pop_lcd =0;
       cmemcpy(prt_buffer,code_mem->logo_str[11],22);
       dsp_str(1,0,prt_buffer);
       logo_only(19);
       prn_tend(DINX_CHECK,CHECK,1);
       nur=-nur;
       prn_tend(DINX_CASH,CASH,1);
       nur = -nur;
       prn_tend(DINX_CNG,0,1);
       post_tamt=0;
       endlogr();
       return;
       };
    /*******************************/
    /**       Post-tendering      **/
    /*******************************/
    if (SYS_OPT.OPT4_1 && func == CASH && ncnt != 0) {
       if (post_tamt == 0 || nur < post_tamt || twostep_id || kdec_bit) {
        errmsg = E_KEY; ERR
        }
       nur-=post_tamt;
       mkdnur(0);
       prn_tend(DINX_CNG,0,2);
       dis9_out(D_CHANGE);

       wait_pover();
       delay();
       if(SYS_OPT.OPT4_2)
           open_drw();
       initseq();
       kclr_bit=1;
       clr_flg = 1;
       return;
       };
    errmsg = E_KEY;
    ERR
    }; /* RSTEP_END */

 /*******************************/
 /**         Tendering         **/
 /*******************************/
#if 0                        /* 981219 */
 if((func != CASH) && (conv_bit) ) {
          errmsg = E_KEY;
          ERR
          }
#endif
 lcd_rec(2);
 if ((twostep_id & 0x7f) || kdec_bit) {
    errmsg = E_GENERAL; ERR   /* vat break */
    }
// if (addcktnd == 1 && regstep != RSTEP_ADDCK && regstep != RSTEP_STEND) {errmsg=E_ADDCHK;ERR};
 void_bit=0; /* for avoid remaining cap */
 tend_com();
 return;
}

