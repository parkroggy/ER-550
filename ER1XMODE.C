#include <stdio.h>
#include <er1io51.h>
#include <er1exmpx.h>
#ifndef BCDBG
#include  <exs03.h>
#else                                  /* BCDBG */
#include  <exdbg.h>
#endif                                 /* BCDBG */

extern void wait_clear();
extern void l2c(long no, unsigned char *buf, UBYTE pos);
//PKR0624 extern void clr_ex0();
//PKR0624 extern void set_ex0();
extern void cal_divi(long long1_1, long long1_2, char d1, long long2, char d2);
extern void dis9_out(char what);
extern void ej_prn();
extern void des_prn();
extern void open_drw();
extern void delay();
extern void dwl_prn();
extern void endlogo();
//PKR0624 extern void initseq();
//PKR0624 extern void inidtx();
extern void ini_outdtx();
extern char level_err();
extern void logo_only(char type);
extern void logo_nur(char type);
extern void load_pstat();
extern void load_dstat();
extern void mkdsp();
extern void mkfunc();
extern void mkdnur(char inf);
extern void mkline();
extern void mkstar();
extern void mkrandom(long value,char ofst,char st);
extern void mk_cprn(char cinx);
extern void mkdeach(char type);
//PKR0624 extern void outdtx();
extern void prn_tend(char dinx,unsigned int kfunc,char lcd_f);
extern void prn_dtlogo(UBYTE);
//PKR0624 extern void prn();
extern void prn_gcpt(char type,char dec,char lcd_f);
extern void prn_ctend(char lcd_f);
extern void sep_prn();
extern void xsep_prn();
extern void xlogo_nur(char type);
extern void make_desc(char *temps,char max);
extern void prn_xdptplu(char type, char rep_flg);
extern char tbl_act();
extern void prn_clkdec(char cc);
extern void prn_grpdec(char cc);
extern void start_menu(UBYTE cc);
extern void x_paid();
extern void dsp_menu();
extern void lcd_dsp(char);
extern void dsp_str(UBYTE x, UBYTE y, unsigned char *str);
extern void dsp_line(unsigned char *str, UBYTE stay);
extern void date_prn();
//PKR0624 extern void cnbclr();
extern void dsp_rep(unsigned char *lmsg, long amt, UBYTE y, unsigned char dot_pos, unsigned char esym);
//PKR0624 extern void clr_lcd();
extern void pmemcpy(UBYTE *, UBYTE *, unsigned int);
extern void cmemcpy(UBYTE *, UBYTE *, UBYTE);  /* PKR0829 */
extern void start_prn();
extern void desc2pbuf();
extern UBYTE *get_fdesc(unsigned int kfunc);
//extern void ej_prn();
extern void lcd_rec(char type);
extern void prn_fdec(char dec,char type);
extern void pop_menu(unsigned char *msg, unsigned char ch);
extern void fill_date(UBYTE *buffer, char ss, long date);
extern int mk_dnum(long, UBYTE*, char);
extern void comm_sior(UBYTE);

extern const UBYTE s_clkpd[10];
extern const UBYTE s_deptpd[8];
extern const UBYTE s_ldeptpd[15];
extern const UBYTE s_plupd[7];
extern const UBYTE s_deptpd[8];
extern const UBYTE s_cnts[5];
extern const UBYTE s_qtys[5];
extern const UBYTE s_samt[11];
extern const UBYTE s_srate[11];
extern const UBYTE s_srates[11];
extern const UBYTE s_scnt[5];
extern const UBYTE s_scnt2[7];
extern const UBYTE s_iclkno[21];
extern const UBYTE s_rclkno[20];
extern const UBYTE s_grttl[13];
extern const UBYTE s_ejreset[25];
extern const UBYTE s_sejs[27];
extern const UBYTE s_star[21];
extern const UBYTE s_gts[4];
extern const UBYTE s_ttlcnt[11];
extern const UBYTE s_ttlamt[11];
extern const UBYTE s_ttls[7];
extern const UBYTE s_space[2];
extern const UBYTE s_xpdreport[12];
extern const UBYTE s_xreport[13];
extern const UBYTE s_x2report[13];
extern const UBYTE s_timepd[13];
extern const UBYTE s_daypd[9];
extern const UBYTE s_tworked[15];
extern const UBYTE s_ttlwork[15];
extern const UBYTE s_tmoutss[22];
extern const UBYTE s_tminss[22];
extern const UBYTE s_cashind[11];
extern const UBYTE s_chind[12];
extern const UBYTE s_ipamt[11];
extern const UBYTE s_dwrttl[11];
extern const UBYTE s_diff[11];
extern const UBYTE s_rctps[21];
extern const UBYTE s_on[3];
extern const UBYTE s_off[4];
extern const UBYTE s_regprt[27];
extern const UBYTE s_yes[4];
extern const UBYTE s_no[4];

/*****************************************************************************/
/***                     clerk sign on check                               ***/
/*****************************************************************************/
void cl_out()
{
 inidtx();
 errmsg=3;
 flg_dis_txtmp[8]=16;
 dis9_out(D_CHANGE);
 return;
}

/*****************************************************************************/
void xxsep_prn()
{
 lblk_bit=1;xxcnt_bit=1;sep_prn();
 return;
}
/*****************************************************************************/
/***                      LONG LONG AMT PRINT                              ***/
/*****************************************************************************/
void llong_add()
{
  nur+=rep[gross].total;
  while(nur >= 100000000) {
       rmtotlh+=1;
       nur-=100000000;
       }
  return;
}
/*****************************************************************************/
void clr_rep()
{
  while(s_dim < e_dim){
       clr_ex0();
       rep[s_dim].cnt=0;
       rep[s_dim].total=0;
       s_dim++;
       set_ex0();
       }
 return;
}

void clr_rep2()
{
  while(s_dim < e_dim){
       clr_ex0();
       rep2[s_dim].cnt=0;
       rep2[s_dim].totall=0;
       rep2[s_dim].totalh=0;
       s_dim++;
       set_ex0();
       }
 return;
}
/*****************************************************************************/
void mk_cnt()
{
#ifdef SPECIAL_REP
    if(s_dim < (MAX_FIN+MAX_DEPT))
#else
    if(s_dim < MAX_FIN)
#endif
        rep2[s_dim].cnt +=rep[s_dim].cnt;
    rep[s_dim].cnt=0;
}
/*****************************************************************************/
void rep_sub(int idx)
{
    long temp;

    rep2[idx].totall += rep[idx].total;
    if(rep2[idx].totall > 100000000)
        {
        temp = rep2[idx].totall / 100000000;
        rep2[idx].totall -= (temp*100000000);
        rep2[idx].totalh += temp;
        }
}

void add_rep()
{
  if (memoryup == 3) {
     while (s_dim < e_dim){
           clr_ex0();
           if (rep[s_dim].total != 0 || rep[s_dim].cnt != 0) {
              if ((s_dim >= d_base && s_dim <= dptup) ||
                  (s_dim >= p_base && s_dim <= tplu)){ /* dept or plu */
                 if (s_dim <= dptup) {  /* dept */
                    func=s_dim-d_base;
                    load_dstat();
                    }
                 else {  /* plu */
                    pcode=s_dim-p_base;
                    load_pstat();
                    };
                 mk_cnt();
                 }
              else mk_cnt();

#ifdef SPECIAL_REP
              if(s_dim < (MAX_FIN + MAX_DEPT))
#else
              if(s_dim < MAX_FIN)
#endif
                 rep_sub(s_dim);
              rep[s_dim].total=0;
              };
           s_dim++;
           set_ex0();
           }
     };
  if (memoryup == 4) clr_rep2();
  return;
}
/*****************************************************************************/
/***                       TOTAL CNT/AMT PRINT                             ***/
/*****************************************************************************/
void prn_ttc(char tp)
{
    nur=rmcnt;
    if (tp == 1) {lblk_bit=1;xxcnt_bit=1;}
    else xcnt_bit=1;
    if((nur%100) == 0)                 /* PKR1128 */
        {
        nur /= 100;
        xcnt_bit = 1;
        }
    logo_nur(34);

    nur=rmtotl;
    logo_nur(35);
    feeding1();
}

/*****************************************************************************/
/***                     SALES PERCENT CAL & PRN                           ***/
/*****************************************************************************/
void xprn_rate()
{
  sprintf(prt_buffer,s_srate);
  prn_gcpt(1,2,0);
  return;
}

void per_calp(long part1,long part,long totl1,long totl,char tp, char what)
{
  float f_part;
  float f_totl;

  f_part=(part1*100000000)+part;
  f_totl=(totl1*100000000)+totl;

  if (f_totl > 0) {
     f_part=f_part / f_totl;
     f_part=f_part*10000;
     nur=(long)f_part;
     ionur=nur;
     if (nur >= 0 ||
            (nur < 0 && ((what == IS_DEPT && PRT_OPT.OPT3_1) ||
                (what == IS_PLU && PRT_OPT.OPT3_2)))) {
        if (!tp)
           xprn_rate();
     }
  }
  nur = 0;
  return;
}
/*****************************************************************************/
/***                       REPORT LOGO PRINT                               ***/
/*****************************************************************************/
void rptissue(UBYTE type)
{
    cnbclr();
    sprintf(prt_buffer,s_xpdreport,index+1);

    if (mode_id == ZMODE) {
        memoryup=3+index;
        prt_buffer[0]='Z';
        }
    else {
        memoryup=1+index;
        };
/*
    prt_buffer[0]|=0x80;
    prt_buffer[2]|=0x80;
*/
    if (PRT_OPT.OPT8_3) {
        if(memoryup % 2)
            {
            switch(type)
                {
                case 27: nur = zcnt_ct + 1; break;
                case 40:
                case 29: nur = zcnt_c + 1;  break;
                case 34: nur = zcnt_t + 1;  break;
                case 35: nur = zcnt_d + 1;  break;
                case 36: nur = zcnt_g + 1;  break;
                case 38: nur = zcnt_p + 1;  break;
                case 39: nur = zcnt + 1;    break;
                case 46: nur = zcnt_sp + 1; break;
                case 47: nur = zcnt_sd + 1; break;
                default: nur = 0;           break;
                }
            }
        else
            nur=zcnt2+1;  /* ISSUE COUNTER */
        mkrandom(nur,MAX_RJ-1,3);
        };
    des_prn();
    mkline();

    if (SYS_OPT.OPT12_1) open_drw();
}

/*****************************************************************************/
void logo_prn(char type)
{
 rptissue(type);
 logo_only(type);
/* prn(); */
 feeding1();
 return;
}
/*****************************************************************************/
void prn_dpcnt(long amt)
{
    if(preset_bit)
        {
        sprintf(prt_buffer,s_scnt2);
        mk_dnum(amt, &prt_buffer[strlen(prt_buffer)], 0);
        }
    else
        sprintf(prt_buffer,s_scnt);
//    rstep1_id=dptstp_id;
//    prn_dtlogo(rstep1_id);
    if((nur%100) == 0)                 /* PKR1128 */
        {
        nur /= 100;
        xsep_prn();
        }
    else
        xxsep_prn();
    return;
}

/*****************************************************************************/
#if 0
char no_skip(char what)
{
    if ((what == IS_PLU) && (rmtotl != 0 || rmcnt != 0 ||
               (PRT_OPT.OPT2_2 && plu[pcode].link_dept != 0)))
        return(FAIL);

    if ((what == IS_DEPT) && ((PRT_OPT.OPT2_3) || rmtotl != 0 || rmcnt != 0))
        return(FAIL);
    return(SUCCESS);
}
#endif
char no_skip(char what)
{
    if ((what == IS_PLU) && (rmtotl != 0 || rmcnt != 0 ||
               (PRT_OPT.OPT2_2 && plu[pcode].link_dept != 0)) &&
               (!stock_bit || (plu[pcode].status[1] & 0x10))) return(FAIL);  /* invent_bit */

    if ((what == IS_DEPT) && ((PRT_OPT.OPT2_3) || rmtotl != 0 || rmcnt != 0) &&
               (!stock_bit || (dept[func].status[1] & 0x10))) return(FAIL);  /* invent_bit */
    return(SUCCESS);
}

char ptd_skip()
{
    if ((PRT_OPT.OPT2_3) || rmtotl != 0 || rmtotlh != 0 || rmcnt != 0)
        return(FAIL);
    return(SUCCESS);
}

/*****************************************************************************/
#ifdef SPECIAL_REP
void ptd_dpt(int frst,int scnd,char tp)
{
    long tcnt=0;
    long ttol=0;
    int  upinx;
    int  totinx;

    while (frst <= scnd)
        {
        func=frst; upinx=dptup; totinx=adjdpt;
        rmcnt=rep2[upinx].cnt;
        rmtotl=rep2[upinx].totall;
        rmtotlh=rep2[upinx].totalh;

        if (ptd_skip())
            {
            if (dept[func].desc[0] != 0)
                {
                make_desc(dept[func].desc,MAX_DEPT_DESC);
                sprintf(prt_buffer,"%s",prt_desc);
                }
            else
                sprintf(prt_buffer,s_deptpd,func+1);
            nur=rmcnt;
            rmtotlh=0;

            load_dstat();         /* dept status */
            rstep1_id=dptstp_id;
            prn_dtlogo(rstep1_id);
            des_prn();
            prn_dpcnt(dept[func].price);

            prn_xdptplu(IS_DEPT,1);

            nur=rmtotl;
            rmtotlh=rep2[upinx].totalh;
            logo_nur(33);
            if (PRT_OPT.OPT3_1)
                per_calp(rmtotlh,rmtotl,rep2[totinx].totalh,rep2[totinx].totall,0,IS_DEPT);

            if (tp == 1)
                {
                if (!gas_bit) tcnt+=rmcnt;
                ttol+=rmtotl;
                };
            };
        frst++;
        }

    if (tp == 1)
        {rmcnt=tcnt;rmtotl=ttol;}
    dptstp_id=0;
    dptstp1_id=0;
    scale_bit = 0;
    rstep1_id=0;
}
#endif
void dptplu_com(char what,int frst,int scnd,char tp)
{
    long tcnt=0;
    long ttol=0;
    int  upinx;
    int  totinx;

    while (frst <= scnd)
        {
        if(stock_bit)
            {
            if (what == IS_DEPT)
                {
                func=frst;
                totinx=adjdpt;
                rmcnt=stock_d[func];
                rmtotl=0;
                }
            else{
                pcode=frst;
                totinx=tplu;
                rmcnt=stock_p[pcode];
                rmtotl=0;
                };
            }
        else
            {
            if (what == IS_DEPT){ func=frst; upinx=dptup; totinx=adjdpt; }
            else{ pcode=frst; upinx=pluup; totinx=tplu; };
            rmcnt=rep[upinx].cnt;
            rmtotl=rep[upinx].total;
            }

        if (no_skip(what))
            {
            if (what == IS_PLU){
                if (!(plu[pcode].status[1] & 2))  /* inact_bit */
                    {  /* PLU Active? */
                    if (plu[pcode].desc[0] != 0)
                        {
                        make_desc(plu[pcode].desc,MAX_PLU_DESC);
                        sprintf(prt_buffer,"%s",prt_desc);
                        }
                    else
                        sprintf(prt_buffer,s_plupd,pcode+1);
                    nur=rmcnt;
                    if ((plu[pcode].link_dept == 0) || stock_bit)
                        {
                        lblk_bit=1;
                        if((nur%100) == 0)
                            {
                            nur/=100;
                            xcnt_bit = 1;
                            }
                        if(stock_bit)
                            xxsep_prn();
                        else
                            {
                            des_prn();
                            logo_nur(31);
                            }
                        }
                    else
                        {
                        load_pstat();
                        rstep1_id=dptstp_id;
                        prn_dtlogo(rstep1_id);
                        des_prn();
                        if(PRT_OPT.OPT2_6)
                            {
                            nur=plu[pcode].link_dept;
                            xlogo_nur(11);
                            }
                        nur=rmcnt;
                        prn_dpcnt(plu[pcode].price);
                        }
                    }
                }
            else
                { /* dept */
                if (dept[func].desc[0] != 0)
                    {
                    make_desc(dept[func].desc,MAX_DEPT_DESC);
                    sprintf(prt_buffer,"%s",prt_desc);
                    }
                else
                    sprintf(prt_buffer,s_deptpd,func+1);
                nur=rmcnt;
                if(stock_bit)
                    {
                    if((nur%100) == 0)
                        {
                        nur/=100;
                        xsep_prn();
                        }
                    else
                        xxsep_prn();
                    }
                else
                    {
                    load_dstat();         /* dept status */
                    rstep1_id=dptstp_id;
                    prn_dtlogo(rstep1_id);
                    des_prn();
                    prn_dpcnt(dept[func].price);
                    }
                };

            if(stock_bit)
                {
                frst++;
                continue;
                }

            prn_xdptplu(what,1);

            nur=rmtotl;
            logo_nur(33);
            if (((what == IS_DEPT) && (PRT_OPT.OPT3_1)) ||
                    ((what == IS_PLU) && (PRT_OPT.OPT3_2)))
                per_calp(0,rmtotl,0,rep[totinx].total,0,what);

            if (tp == 1)
                {
                if (!gas_bit) tcnt+=rmcnt;
                ttol+=rmtotl;
                };
            };
        frst++;
        }

    if (tp == 1)
        {rmcnt=tcnt;rmtotl=ttol;}
    dptstp_id=0;
    dptstp1_id=0;
    scale_bit = 0;
    rstep1_id=0;
}

/*****************************************************************************/
void rep_plu()
{
  logo_prn(38);

  dptplu_com(IS_PLU,0,MAX_PLU-1,0);
/*  prn();*/
  feeding1();

  rmcnt=rep[tplu].cnt;
  rmtotl=rep[tplu].total;
  prn_ttc(1);

  if (memoryup >= 3) {          /* memory update */
     s_dim=p_base;
     e_dim=e_base;
     add_rep();
     zcnt_p++;
     };

  endlogo();
  return;
}
/*****************************************************************************/
/***                  TIME/DEPT GROUP/DAY REPORT                           ***/
/*****************************************************************************/
void rep_com()
{
 char indx[3]={24, 31, 10};
 int  base[3]={t_base,da_base,g_base};  /*{225,250,282}*/
 char ct=0;

 logo_prn(34+rpt_kind);

 while (ct < indx[rpt_kind]) {
       rmcnt=rep[base[rpt_kind]+ct].cnt;
       rmtotl=rep[base[rpt_kind]+ct].total;
       if (rmtotl != 0 || rmcnt != 0) { /* zero skip */
          if (rpt_kind == 0) sprintf(prt_buffer,s_timepd,(int)ct);
          else if (rpt_kind == 1) sprintf(prt_buffer,s_daypd,ct+1);
          else prn_grpdec(ct);
          des_prn();
          nur=rmcnt;
          if (rpt_kind == 2){lblk_bit=1; xxcnt_bit=1;}
          else xcnt_bit=1;
          if((nur%100) == 0)           /* PKR1128 */
              {
              nur /= 100;
              xcnt_bit = 1;
              }
          logo_nur(31);
          nur=rmtotl;
          logo_nur(33);
          if (rpt_kind == 0) per_calp(0,rmtotl,0,rep[tmtotl].total,0,99);
          };
       ct++;
       }
/*  prn();*/
  feeding1();

 rmcnt=rep[base[rpt_kind]+indx[rpt_kind]].cnt;
 rmtotl=rep[base[rpt_kind]+indx[rpt_kind]].total;
 if (rpt_kind != 2) prn_ttc(0);
 else prn_ttc(1);

 s_dim=base[rpt_kind];
 e_dim=base[rpt_kind]+indx[rpt_kind]+1;
 if (rpt_kind == 0 && memoryup >= 3) {add_rep(); zcnt_t++;}
 if (rpt_kind == 1 && memoryup == 3) {clr_rep(); zcnt_d++;}
 if (rpt_kind == 2 && memoryup >= 3) {add_rep(); zcnt_g++;}
 endlogo();
 return;
}

/*****************************************************************************/
/***                         CLERK REPORT                                  ***/
/*****************************************************************************/
char ccntprn_chk(char ct)
{
  if (((ct < FC_NONTAXA) || (ct > FC_TAXTO)) && ((ct < FC_CRTAX1) || (ct > FC_CRTAX4))
         && ((ct < FC_CASHIND) || (ct > FC_DRWR)))
     return(1);
  return(0);
}

void mk_dprn(int cinx)
{
  make_desc(FUNCKEY[cinx-CASH].DESC,MAX_FUNC_DESC);
  desc2pbuf();
  return;
}

void clogo_prn(char ct)
{
    if ((ct >= (cper1tl-clkup)) && (ct <= (cper4tl-clkup)))
        mk_dprn(PER1 + ct + clkup - cper1tl);
    else if (ct == (cvoid1-clkup)) mk_dprn(ERR_CORR);
    else if (ct == (cvoid2-clkup)) mk_dprn(VOID);
    else if (ct == (cvoid4-clkup)) mk_dprn(CANCEL);
    else if (ct == (cretn-clkup)) mk_dprn(RETURN);
    else if (ct == (cra-clkup)) mk_dprn(RA);
    else if (ct == (cpo-clkup)) mk_dprn(PO);
    else if (ct == (cnosale-clkup)) mk_dprn(NOSALE);
    else cmemcpy(prt_buffer,code_mem->clklogo[ct],12);
}

void clk_com(char frst,char scnd)
{
 char ct;
 char c;
 int  bb;

 name_prt = 0;
 for (c=frst; c<=scnd ;c++) {
     ct=0;
     bb=c_base+c*MAX_CLKITEM;
     while (ct < USE_CLKITEM) {
        rmcnt=rep[bb+ct].cnt;
        rmtotl=rep[bb+ct].total;

        if (((PRT_OPT.OPT2_4) && rmcnt == 0 && rmtotl == 0) ||
                    (!PRT_OPT.OPT1_3 && (ct == FC_RTN || ct == FC_MODEVOID))) {
           if ((!PRT_OPT.OPT1_1) && (ct == 0))
              ct = USE_CLKITEM - 2;
           ct++;
           continue;
        }

        if (name_prt == 0 && ct != 0){
           nur=0;prn_clkdec(c);xsep_prn();
           name_prt=1;
        }

        if (ccntprn_chk(ct)){
           nur=rmcnt;
           if (ct == 0) {name_prt=1;prn_clkdec(c);}
              else clogo_prn(ct);
           xsep_prn();
        }
        nur=rmtotl;
        if (ct != FC_NOSALE){
           if (ct == 0 || !ccntprn_chk(ct)) {clogo_prn(ct); sep_prn();}
           else logo_nur(LOGO_BLANK);
        }
        clk_rpt = 0;
        if (!PRT_OPT.OPT1_1 && (ct == 0))
           ct = USE_CLKITEM - 2;
        ct++;
     }
     if ( clk_rpt == 0 && c != MAX_CLERK-1) {
        mkline();
        clk_rpt = 1;
     }
 }
 return;
}

/*****************************************************************************/
void rep_clk()
{
 char d;

 if (nur == 0 || (nur > 20)) {errmsg = E_KEY; ERR};
 if (clerk == 0) {cl_out();errmsg=E_REQCLK;ERR};
 if (clk_rpt != 1 || (train_flg && mode_id == ZMODE)) {errmsg=E_KEY;ERR}
 if ((/*!knur_bit ||*/ nur == 0 || (nur > MAX_CLERK))) {errmsg=E_KEY;ERR}

 d=(char)nur-1;

 ini_outdtx();
 if (err_bit) return;
 logo_prn(40);

 clk_com(d,d);
/*  prn();*/
 feeding1();

 if (memoryup >= 3) {           /* memory update */
    s_dim=c_base+d*MAX_CLKITEM;
    e_dim=c_base+(d+1)*MAX_CLKITEM;
    add_rep();
    zcnt_c++;
    };

 endlogo();
 return;
}

void rep_clk_s()
{
    UBYTE buf[22];                       /* PKR0829 */

    clr_lcd();
    sprintf(buf,s_iclkno);
    dsp_str(0,1,buf);
    sprintf(buf,s_rclkno);
    dsp_str(0,3,buf);
    clrk_step = 1;
    return;
}

void rep_allclk()
{
 if (clerk == 0) {cl_out();errmsg=E_REQCLK;ERR};
 if (clk_rpt != 1 || (train_flg && mode_id == ZMODE)) {errmsg=E_KEY;ERR}
/* if ((!knur_bit || nur == 0 || (nur > MAX_CLERK))) {errmsg=E_KEY;ERR}*/

 ini_outdtx();
 if (err_bit) return;
 logo_prn(29);

 clk_com(0,MAX_CLERK-1);
/*  prn();*/
 feeding1();

 if (memoryup >= 3) {           /* memory update */
    s_dim=c_base;
    e_dim=t_base;
    add_rep();
    zcnt_c++;
    };

 endlogo();
 return;
}
/*****************************************************************************/
/***                      FINANCIAL REPORT                                 ***/
/*****************************************************************************/

char cntprn_chk(char ct)
{
  if (((ct < F_NONTAXA) || (ct > F_TAXTO)) && ((ct < F_CRTAX1) || (ct > F_CRTAX4))
         && (ct != F_GROSS) && ((ct < F_CASHIND) || (ct > F_DRWR)))
     return(1);
  return(0);
}

void flogo_prn(char ct)
{
 int i;

 if((ct >= tax1abl) && (ct <= tax4abl))
    {
    pmemcpy(prt_desc, tax_table[ct-tax1abl].desc, MAX_TAX_DESC);
    prt_desc[MAX_TAX_DESC]=0;
    sprintf(prt_buffer, "%s SALES", prt_desc);
    prt_desc[MAX_TAX_DESC]=0;
    }
 else if((ct >= tax1amt) && (ct <= tax4amt))
    {
    make_desc(tax_table[ct-tax1amt].desc,MAX_TAX_DESC);
    desc2pbuf();
    }
 else if (ct == cshsale) mk_dprn(CASH);
 else if (ct == chksale) mk_dprn(CHECK);
 else if ((ct >= per1tl) && (ct <= per4tl)) mk_dprn(PER1 + ct - per1tl);
 else if (ct == void1) mk_dprn(ERR_CORR);
 else if (ct == void2) mk_dprn(VOID);
 else if (ct == void4) mk_dprn(CANCEL);
 else if (ct == retn) mk_dprn(RETURN);
 else if (ct == ra) mk_dprn(RA);
 else if (ct == po) mk_dprn(PO);
 else if ((ct >= conv1) && (ct <= conv4m4))  /* 981219 */
    {
    mk_dprn(CONV1 + (ct - conv1) / 6);
    i = strlen(prt_buffer);
    if(i > 9)
        i = 9;
    prt_buffer[i++] = '(';
    if(((ct - conv1) % 6) == 0)
        {
        prt_buffer[i++] = 'C';
        prt_buffer[i++] = 'A';
        }
    else if(((ct - conv1) % 6) == 1)
        {
        prt_buffer[i++] = 'C';
        prt_buffer[i++] = 'H';
        }
    else
        {
        prt_buffer[i++] = 'M';
        prt_buffer[i++] = ((ct-conv1)%6)-1+0x30;  /* 990122 */
        }
    prt_buffer[i++] = 0;
    }
 else if ((ct >= misc1sale) && (ct <= misc4sale)) mk_dprn(MISCTND1 + ct - misc1sale);
 else if (ct == nosale) mk_dprn(NOSALE);
 else cmemcpy(prt_buffer,code_mem->finlogo[ct],12);
}

void ptd_fin()
{
 char ct=0, tfg;
 char cons0_flg=0;

 index = 1;
 logo_prn(39);

#if 0
 if (pdept_no != 0 && (pdept_no <= 10)) dptplu_com(IS_DEPT,0,pdept_no-1,0);
 else dptplu_com(IS_DEPT,0,MAX_DEPT-1,0);
#endif
#ifdef SPECIAL_REP
 ptd_dpt(0,MAX_DEPT-1,0);
 mkline();
#endif

 ct=0;
 rmtotlh = 0;
 while (ct < USE_FIN) {              /* except grand total */
       if (((ct == F_GROSS) && (((!PRT_OPT.OPT8_1) && (mode_id == XMODE))
          || ((!PRT_OPT.OPT8_2) && (mode_id == ZMODE)))) || (!PRT_OPT.OPT1_4 && (ct == F_AUDACT))
          || (!PRT_OPT.OPT1_3 && (ct == F_RTN || ct == F_MODEVOID))){ct++; continue; };
       rmcnt=rep2[ct].cnt;

       if ((PRT_OPT.OPT2_1) && (rmcnt == 0) && (rep2[ct].totall == 0) && (rep2[ct].totalh == 0))
           {ct++;continue;};
       if((ct == trainttl) && !PRT_OPT.OPT12_1) {ct++; continue;} //971009
#if 0
       if (ct == F_NONTAXA) {
           nur = rmtotl;
           flogo_prn(ct);
           sep_prn();
           ct++;
           continue;
       }
#endif
       if (cntprn_chk(ct)) {
          nur=rmcnt;
          flogo_prn(ct);
          if (ct <= 2)
            {
            if((nur%100) == 0)                 /* PKR1128 */
                {
                nur /= 100;
                xcnt_bit = 1;
                }
            xxsep_prn();       /*cnt - 0.00*/
            }
          else xsep_prn();
          };

       rmtotlh=rep2[ct].totalh;
       nur=rep2[ct].totall;
       if (!cntprn_chk(ct)) {
          flogo_prn(ct);
          if((ct >= F_CONV1) && (ct <= F_CONV4))
            {
            lgol_bit = 1;
            conv_bit = 1;
            convnk = (ct - F_CONV1)/6;  /* 981219 */
            }
          sep_prn();
          lgol_bit = 0;
          conv_bit = 0;
          convnk = 0;
       }
       else if (ct == F_NOSALE) xlogo_nur(40); /* NON-ADD# */
       else logo_nur(LOGO_BLANK);
       rmtotlh=0;

       if ((ct >= F_TAXFROM && ct < F_TAXTO) && (ct <= tax4abl)) {    /* yoo 1001 */
          if((tax_table[ct-F_TAXFROM].taxstat & 0x0f) != 1)
             {
             nur=tax_table[ct-F_TAXFROM].taxrate;
             prn_gcpt(1,3,0);
             }
          };

       if (ct == F_CASHIND) {           /* cash declaration */
          nur=cashdcl;
          if (nur != 0) {
             logo_nur(37);
             nur=cashdcl - rep2[cshindw].totall;
             rmtotlh = rep2[cshindw].totalh;
             if(rmtotlh)
                {
                tfg = 0;
                if(nur >= 0)
                    {
                    while(nur >= 0)
                        {
                        if(rmtotlh == 0)
                            {
                            tfg = 1;
                            break;
                            }
                        nur = 100000000 - nur;
                        rmtotlh--;
                        }
                    if(!tfg)
                        nur = -nur;
                    }
                else
                    {
                    nur = -nur;
                    rmtotlh = -rmtotlh;
                    }
                }
             grand_bit = 1;
             logo_nur(39);
             grand_bit = 0;
             };
          };
       if (ct == F_CHKIN) {           /* check declaration */
          nur=chckdcl;
          if (nur != 0) {
             logo_nur(38);
             nur=chckdcl - rep2[chkindw].totall;
             rmtotlh = rep2[chkindw].totalh;
             if(rmtotlh)
                {
                tfg = 0;
                if(nur >= 0)
                    {
                    while(nur >= 0)
                        {
                        if(rmtotlh == 0)
                            {
                            tfg = 1;
                            break;
                            }
                        nur = 100000000 - nur;
                        rmtotlh--;
                        }
                    if(!tfg)
                        nur = -nur;
                    }
                else
                    {
                    nur = -nur;
                    rmtotlh = -rmtotlh;
                    }
                }
             grand_bit = 1;
             logo_nur(39);
             grand_bit = 0;
             };
          };

       if (ct == 2) mkline();
       ct++;
       }

/*  prn();*/
 feeding1();
 mkstar();
 nur=grand;                                 /* grand */
 rmtotlh=grandh;
 if (memoryup%2 == 1) {       /* X1,Z1 */
    llong_add();
    };
 if (((PRT_OPT.OPT7_1) && (mode_id == XMODE)) || ((PRT_OPT.OPT7_2) && (mode_id == ZMODE))) {
    sprintf(prt_buffer,s_grttl);/*dwl_prn(); temp delete yoo0826*/
//    des_prn();
    grand_bit = 1;
    sep_prn();
    grand_bit = 0;
    feeding1();
    };

 if (memoryup >= 3) {           /* memory update */
    s_dim=podept;             /* financial */
#ifdef SPECIAL_REP
    e_dim=c_base;
#else
    e_dim=d_base;
#endif
    if (memoryup == 3) {    /* Z1 */
       grandh=rmtotl;
       grand=nur;
       };
    add_rep();
    };
 if (memoryup == 3){
    zcnt++;
//    order_no=0;
    if (SYS_OPT.OPT7_2) {grandh=0;grand=0;};
    if (SYS_OPT.OPT7_1) cons0_flg=1;
    if (grandh >= 9000) grandh -=9000;
    };
 if (memoryup == 4)
    zcnt2++;
// if (PRT_OPT.OPT2_5) {
//    clk_com(0,MAX_CLERK-1);
//    mkstar();
// }
 /*------------------------------------------------*/
// flg_concid = 0;
 endlogo();
 if (cons0_flg) consno=0;
 return;
}

void rep_fin()
{
 char ct=0;
 char cons0_flg=0;

 logo_prn(39);

#if 0
 if (pdept_no != 0 && (pdept_no <= 10)) dptplu_com(IS_DEPT,0,pdept_no-1,0);
 else dptplu_com(IS_DEPT,0,MAX_DEPT-1,0);
#endif
 dptplu_com(IS_DEPT,0,MAX_DEPT-1,0);
 mkline();

 ct=0;
 while (ct < USE_FIN) {              /* except grand total */
       if (((ct == F_GROSS) && (((!PRT_OPT.OPT8_1) && (mode_id == XMODE))
          || ((!PRT_OPT.OPT8_2) && (mode_id == ZMODE)))) || (!PRT_OPT.OPT1_4 && (ct == F_AUDACT))
          || (!PRT_OPT.OPT1_3 && (ct == F_RTN || ct == F_MODEVOID))){ct++; continue; };
       rmcnt=rep[ct].cnt;
       rmtotl=rep[ct].total;

       if ((PRT_OPT.OPT2_1) && rmcnt == 0 && rmtotl == 0) {ct++;continue;};
       if((ct == trainttl) && !PRT_OPT.OPT12_1) {ct++; continue;} //971009
#if 0
       if (ct == F_NONTAXA) {
           nur = rmtotl;
           flogo_prn(ct);
           sep_prn();
           ct++;
           continue;
       }
#endif
       if (cntprn_chk(ct)) {
          nur=rmcnt;
          flogo_prn(ct);
          if (ct <= 2)
              {
              if((nur%100) == 0)                 /* PKR1128 */
                  {
                  nur /= 100;
                  xcnt_bit = 1;
                  }
              xxsep_prn();       /*cnt - 0.00*/
              }
          else xsep_prn();
          };

       nur=rmtotl;
       if (!cntprn_chk(ct)) {
          flogo_prn(ct);
          if((ct >= F_CONV1) && (ct <= F_CONV4))
            {
            lgol_bit = 1;
            conv_bit = 1;
            convnk = (ct - F_CONV1)/6;  /* 981219 */
            }
          sep_prn();
          lgol_bit = 0;
          conv_bit = 0;
          convnk = 0;
       }
       else if (ct == F_NOSALE) xlogo_nur(40); /* NON-ADD# */
       else logo_nur(LOGO_BLANK);

       if ((ct >= F_TAXFROM && ct < F_TAXTO) && (ct <= tax4abl)) {    /* yoo 1001 */
          if((tax_table[ct-F_TAXFROM].taxstat & 0x0f) != 1)
             {
             nur=tax_table[ct-F_TAXFROM].taxrate;
             prn_gcpt(1,3,0);
             }
          };

       if (ct == F_CASHIND) {           /* cash declaration */
          nur=cashdcl;
          if (nur != 0) {
             logo_nur(37);
             nur=cashdcl - rep[cshindw].total;
             logo_nur(39);
             };
          };
       if (ct == F_CHKIN) {           /* check declaration */
          nur=chckdcl;
          if (nur != 0) {
             logo_nur(38);
             nur=chckdcl - rep[chkindw].total;
             logo_nur(39);
             };
          };

       if (ct == 2) mkline();
       ct++;
       }

/*  prn();*/
 feeding1();
 mkstar();
 nur=grand;                                 /* grand */
 rmtotlh=grandh;
 if (memoryup%2 == 1) {       /* X1,Z1 */
    llong_add();
    };
 if (((PRT_OPT.OPT7_1) && (mode_id == XMODE)) || ((PRT_OPT.OPT7_2) && (mode_id == ZMODE))) {
    sprintf(prt_buffer,s_grttl);/*dwl_prn(); temp delete yoo0826*/
//    des_prn();
    grand_bit = 1;
    sep_prn();
    grand_bit = 0;
//       llong_prn(grandh,grand);
/*  prn();*/
    feeding1();
    };

 if (memoryup >= 3) {           /* memory update */
    s_dim=podept;               /* financial */
    e_dim=c_base;
    if (memoryup == 3) {        /* Z1 */
       grandh=rmtotlh;
       grand=nur;
       };
    add_rep();
    };
 if (memoryup == 3){
    zcnt++;
//    order_no=0;
    if (SYS_OPT.OPT7_2) {grandh=0;grand=0;};
    if (SYS_OPT.OPT7_1) cons0_flg=1;
    if (grandh >= 9000) grandh -=9000;
    };
 if (memoryup == 4)
    zcnt2++;
 if (PRT_OPT.OPT2_5) {
    clk_com(0,MAX_CLERK-1);
    if (memoryup >= 3) {           /* memory update */
        s_dim=c_base;
        e_dim=c_base+MAX_CLERK*MAX_CLKITEM;
        add_rep();
        };
    mkstar();
 }
 /*------------------------------------------------*/
// flg_concid = 0;
 endlogo();
 if (cons0_flg) consno=0;
 return;
}
/*****************************************************************************/
/***                  CASH & CHECK IN DRAWER REPORT                        ***/
/*****************************************************************************/
void rep_drawer()
{
    if (mode_id == ZMODE) {errmsg=E_KEY;ERR}

    logo_prn(37);

    nur=rep[cshindw].total;
    prn_tend(DINX_CASH,0,0);
    nur=rep[chkindw].total;
    prn_tend(DINX_CHECK,0,0);
/*    prn();*/
    feeding1();
    endlogo();
    return;
}

/****************************************************/
/***              CLERK TIME REPORT               ***/
/****************************************************/
void time_sub(UBYTE ss, int time)
{
    prt_buffer[ss++]=(time/1000)+'0';
    prt_buffer[ss++]=((time%1000)/100)+'0';
    prt_buffer[ss++]=':';
    prt_buffer[ss++]=((time%100)/10)+'0';
    prt_buffer[ss++]=(time%10)+'0';
}

void time_sub2(UBYTE ss, int time, UBYTE min)  /* 980326 */
{
    prt_buffer[ss++]=(time/100)+'0';
    prt_buffer[ss++]=((time%100)/10)+'0';
    prt_buffer[ss++]=(time%10)+'0';
    prt_buffer[ss++]=':';
    prt_buffer[ss++]=(min/10)+'0';
    prt_buffer[ss++]=(min%10)+'0';
}

void clk_time(UBYTE clkno)
{
    UBYTE ct, cc, ss, pm_f;
    int time;

//    if (mode_id == ZMODE) {errmsg=E_KEY;ERR}

    EJ_FLAG = EJ_REPORT;
    clk_tmttl = 0;
    clk_min = 0;                       /* 980326 */
    logo_prn(27);

    if(clkno == 99)
        ct = 0;
    else
        ct = clkno;
    for (; ct < MAX_CLERK; ct++)
        {
        if (CLKIO[ct].T_IDX)
            {
            prn_clkdec(ct);
            ej_prn();
            for (cc = 0; cc < CLKIO[ct].T_IDX ; cc++)
                {
                time = CLKIO[ct].T_LOG[cc];
                pm_f = 0;
                if (time >= 1200)
                    pm_f = 1;
                if ((time >= 1300) && (time < 2400))
                    time -= 1200;
                if (cc & 0x01)
                    cmemcpy(prt_buffer,code_mem->LOGMSG[7],15);
                else
                    cmemcpy(prt_buffer,code_mem->LOGMSG[5],15);
                if(CLKIO[ct].D_LOG[cc])
                    fill_date(prt_buffer, 7, CLKIO[ct].D_LOG[cc]);
                time_sub(19, time);
                ss = 24;
                if(pm_f) prt_buffer[ss++] = 'P';
                else prt_buffer[ss++] = 'A';
                prt_buffer[ss] = 'M';
                des_prn();
                }
            nur = (long)CLKIO[ct].W_TIME/100;
            clk_tmttl += nur;
            clk_min += (CLKIO[ct].W_TIME%100);  /* 980326 */
            if(clk_min >= 60)
                {
                clk_tmttl++;
                clk_min -= 60;
                }
            lblk_bit = 1;
//            logo_nur(32);
            cmemcpy(prt_buffer,code_mem->nur_str[15],15);
            time_sub(21, CLKIO[ct].W_TIME);
            des_prn();
            }
        if(clkno != 99)
            break;
        }
    feeding1();
//    nur = clk_tmttl;
    lblk_bit = 1;
//    logo_nur(36);
    cmemcpy(prt_buffer,code_mem->nur_str[19],15);
    time_sub2(20, (int)clk_tmttl, clk_min);  /* 980326 */
    des_prn();
    if (memoryup >= 3)
        {
        if(clkno == 99)
            {
            memset((UBYTE*)CLKIO, 0, sizeof(CLKIO));
            }
        else
            {
            memset((UBYTE*)&CLKIO[ct], 0, sizeof(S_CLKIO));
            }
        zcnt_ct++;
        }
    endlogo();
//    EJ_FLAG = EJ_NORMAL;
    return;
}

void dspr_sub(UBYTE type)
{
    clr_lcd();
    cnbclr();
    rep_disp=1;
    rept_step=2;
    date_prn();
    dsp_str(0,1,prt_buffer);
    cnbclr();
    dsp_str(0,2,prt_buffer);
    memset(prt_buffer, 0x20, MAX_CLM);
    if (rept_ptd == 3)
        {
        pmemcpy(prt_buffer,s_x2report,strlen(s_x2report));
        nur=zcnt2+1;
        }
    else
        {
        pmemcpy(prt_buffer,s_xreport,strlen(s_xreport));
        switch(type)
            {
            case 27: nur = zcnt_ct + 1; break;
            case 40:
            case 29: nur = zcnt_c + 1;  break;
            case 34: nur = zcnt_t + 1;  break;
            case 35: nur = zcnt_d + 1;  break;
            case 36: nur = zcnt_g + 1;  break;
            case 38: nur = zcnt_p + 1;  break;
            case 39: nur = zcnt + 1;    break;
            case 46: nur = zcnt_sp + 1; break;
            case 47: nur = zcnt_sd + 1; break;
            default: nur = 0;           break;
            }
        }
//    dsp_rep(prt_buffer,nur,3,0,0);
    mkrandom(nur,MAX_CLM-1,3);
    dsp_str(0,3,prt_buffer);
    mkline();
    dsp_str(0,4,prt_buffer);
    cnbclr();
//    dsp_line(prt_buffer,0);
}

void disp_tmio(UBYTE clkno)
{
    long temp;

    temp=nur;
    dspr_sub(27);
    nur=temp;
    rept_con = 1;
    logo_only(27);
    dsp_str(0,5,prt_buffer);
    cnbclr();
    dsp_str(0,6,prt_buffer);
    xdisp_step = DISP_TMIOD;
    xdisp_cnt = 0;
    if(clkno == 99)
        xdisp_cnt2 = 0;
    else
        {
        xdisp_cnt2 = clkno;
        }
    xdisp_cnt3 = clkno;
    name_prt = 0;
    xdisp_start = 1;
    clk_tmttl = 0;
    clk_min = 0;                       /* 980326 */
    return;
}

void prc_clktm()
{
    if(nur == 0)
        {
        if(menu_no == MENU_CNO2)
            disp_tmio(99);
        else
            clk_time(99);
        }
    else
        rep_clk_s();
}

void xmode_fun(int cnt)
{
  int x_no,i,j;
  UBYTE buf[22];                       /* PKR0829 */

    x_no = cnt;
    switch(x_no)
        {
        case MENU_CASHDE:
            drawopn();
            m_no = 0;
            l_no = 4;
            xm_step = XM_DECL;
            break;
        case MENU_RCONT:
            if (r_cont == 1) {
               m_no = 29;
               l_no = 5;
               xm_step = XM_RCONTS;
            }
            else {
               m_no = 24;
               l_no = 5;
               xm_step = XM_RCONT;
            }
            break;
        case MENU_RONOF:
            if (r_off == 1) {
               m_no = 14;
               l_no = 5;
               xm_step = XM_RONOFFS;
            }
            else {
               m_no = 4;
               l_no = 5;
               xm_step = XM_RONOFF;
            }
            break;
        case MENU_TRAIN:
            if (!train_flg) {
               m_no = 9;
               l_no = 5;
            }
            else {
               m_no = 19;
               l_no = 5;
            }
            xm_step = XM_TRAIN;
            break;
        case MENU_REJ:
            m_no = 34;
            l_no = 2;
            xm_step = ZM_REJ;
            break;
        case MENU_CLRTTL:
            m_no = 34;
            l_no = 2;
            mm_step = MM_CLRTTL;
            break;
        case MENU_CLRGT:
            m_no = 34;
            l_no = 2;
            mm_step = MM_CLRGT;
            break;
        }
    rept_step = 3;
    clr_lcd();
    cmemcpy(buf,code_mem->title_str[x_no],21);  /* PKR0829 */
    dsp_str(0,0,buf);
    cmemcpy(buf,code_mem->xmenu_str[2],21);
    dsp_str(0,1,buf);
    for(i=m_no,j=2;i<m_no+l_no;i++,j++)
        {
        cmemcpy(buf,code_mem->xmenu_str[i],21);
        dsp_str(0,j,buf);
        }
}

void rep_ej()
{

    if(mode_id == ZMODE)
        {
        EJ_FLAG = EJ_NOPRT;
        EJ_TINX = 0;
        start_prn();
        sprintf(prt_buffer, s_ejreset);
        ej_prn();
        EJ_INDEX = 0;
        EJ_FULLF = 0;
        endlogo();
        }
    else
        start_menu(MENU_EJ);
#if 0
        {
        sprintf(prt_buffer, s_sejs);
        prn();
        prn();
        for(i=0;i<EJ_INDEX;i++)
            {
            pmemcpy(prt_buffer, EJ_BUF[i], 26);
            prn();
            }
        endlogo();
        }
#endif
}

void prc_ej()
{
    int i;
    char type=nur, loop=1;

    if(nur && (nur != 9))
        type = 1 << (nur-1);

    EJ_FLAG = EJ_NOPRT;
    start_prn();
    sprintf(prt_buffer, s_sejs);
    prn();
    prn();
//970925    for(i=0;i<EJ_INDEX;i++)
    if(EJ_FULLF)
        i = EJ_INDEX;
    else
        {
        i = 0;
        if(EJ_INDEX == 0)
            loop = 0;
        }
    while(loop)
        {
        if(type == 9) /* cancel */
            {
            if(EJ_BUF[i][MAX_RJ] == TYPE_CANCEL)
                {
                pmemcpy(prt_buffer, EJ_BUF[i], 26);
                prn();
                }
            }
        else
            {
            if(!(type && (!(EJ_BUF[i][MAX_RJ] & type) ||
                    (EJ_BUF[i][MAX_RJ] == TYPE_CANCEL))))
                {
                pmemcpy(prt_buffer, EJ_BUF[i], 26);
                prn();
                }
            }
        i++;
        if(i >= MAX_EJLINE)
            {
            if(EJ_FULLF)
                i = 0;
            else
                break;
            }
        if(i == EJ_INDEX)
            break;
        }
    prn();
    endlogo();
}

void prn_stp()
{
  logo_prn(46);

  stock_bit = 1;
  dptplu_com(IS_PLU,0,MAX_PLU-1,0);
  stock_bit = 0;
/*  prn();*/
  feeding1();

  if (memoryup >= 3) {          /* memory update */
     memset((UBYTE*)&stock_p[0], 0, sizeof(stock_p));
     zcnt_sp++;
     };

  endlogo();
}

void prn_std()
{
  logo_prn(47);

  stock_bit = 1;
  dptplu_com(IS_DEPT,0,MAX_DEPT-1,0);
  stock_bit = 0;
/*  prn();*/
  feeding1();

  if (memoryup >= 3) {          /* memory update */
     memset((UBYTE*)&stock_d[0], 0, sizeof(stock_d));
     zcnt_sd++;
     };

  endlogo();
}

void disp_stpt()
{
    logo_only(46);
    dsp_str(0,5,prt_buffer);
    cnbclr();
    dsp_str(0,6,prt_buffer);
    xdisp_step = DISP_STP;
    xdisp_cnt = 0;
    xdisp_start = 1;
}

void disp_stdt()
{
    logo_only(47);
    dsp_str(0,5,prt_buffer);
    cnbclr();
    dsp_str(0,6,prt_buffer);
    xdisp_step = DISP_STD;
    xdisp_cnt = 0;
    xdisp_start = 1;
}

void menu_man()
{
    switch(nur)
        {
        case 0:            /* Print Report */
            start_menu(MENU_PRINT);
            rept_step = 1;
            break;
        case 1:            /* Display Report */
            start_menu(MENU_DISPLAY);
            rept_step = 1;
            break;
        case 2:            /* Cash Declaration */
            xmode_fun(MENU_CASHDE);
            rept_step = 3;
            break;
        case 3:            /* Turn Receipt On/Off */
            xmode_fun(MENU_RCONT);
            rept_step = 3;
            break;
        case 4:            /* Stamp printing control */
            xmode_fun(MENU_RONOF);
            rept_step = 3;
            break;
        case 5:            /* Training Mode */
            xmode_fun(MENU_TRAIN);
            rept_step = 3;
            break;
        }
}

void menu_prn()
{
    if (rept_ptd && (nur != 0)){errmsg = E_KEY; ERR};
    if((nur != 9) && EJ_FULLF &&
                SYS_OPT.OPT11_2 && SYS_OPT.OPT10_3)
        {
        errmsg = E_EJFULLS;
        err_bit = 1;
        return;
        }
    EJ_FLAG = EJ_REPORT;
    if (rept_ptd) {
        ptd_fin();
//        EJ_FLAG = EJ_NORMAL;
        return;
    }
//    if((mode_id == ZMODE) && (nur > 8))
//        {errmsg = E_KEY; ERR};
    switch(nur)
        {
        case 0:            /* Financial */
            rep_fin();
            break;
        case 1:            /* Time */
            rep_com();
            break;
        case 2:            /* Daily */
            rpt_kind = 1;
            rep_com();
            break;
        case 3:            /* PLU */
            rep_plu();
            break;
        case 4:            /* ALL CLERK */
            rep_allclk();
            break;
        case 5:            /* INDIVIDUAL CLERK */
            rep_clk_s();
            break;
        case 6:            /* Group */
            rpt_kind = 2;
            rep_com();
            break;
        case 7:            /* Stock (PLU) */
            prn_stp();
            break;
        case 8:            /* Stock (Dept.) */
            prn_std();
            break;
        case 9:            /* clerk time report */
            start_menu(MENU_CNO);
            break;
        case 10:            /* Cash in Drawer */
            rep_drawer();
            break;
        }
//    EJ_FLAG = EJ_NORMAL;
}

void disp_gt(int cont)
{
 if (((PRT_OPT.OPT7_1) && (mode_id == XMODE)) || ((PRT_OPT.OPT7_2) && (mode_id == ZMODE))) {
    sprintf(prt_buffer,s_star);
    dsp_str(0,cont,prt_buffer);
    cont++;
    cnbclr();
    sprintf(prt_buffer,s_gts);
    nur=grand;                                 /* grand */
    rmtotlh=grandh;
    if(xdisp_step != FIN_ITEMP)
        llong_add();
    grand_bit = 1;
    dsp_rep(prt_buffer,nur,cont,2,0);
    grand_bit = 0;
    cont++;
    cnbclr();
 }
 xdisp_step = REPT_DEND;
}

#ifdef SPECIAL_REP
void fin_dptp()
{
 char i, cnt, flag, start=0, tfg;

 cnt = 0;

 flag = PRT_OPT.OPT3_1;
 for(i=xdisp_cnt;i<MAX_DEPT;i++, xdisp_cnt++) {
    if ((!stock_bit || cnt < 8) &&
            (stock_bit || flag || cnt < 7) &&
            (stock_bit || !flag || cnt < 6))
       {
       rmcnt=rep2[i+MAX_FIN].cnt;
       rmtotl=rep2[i+MAX_FIN].totall;
       rmtotlh=rep2[i+MAX_FIN].totalh;
       if  ((PRT_OPT.OPT2_1) && ((rmcnt == 0) && (rmtotl == 0) && (rmtotlh == 0)))
          continue;
       else {
          if(!start)
             {
             clr_lcd();
             start = 1;
             }
          if (dept[i].desc[0] != 0) {
             make_desc(dept[i].desc,MAX_DEPT_DESC);
             sprintf(prt_buffer,"%s ",prt_desc);
          }
          else
             sprintf(prt_buffer,s_deptpd,i+1);
          if(!stock_bit)
             {
             func = i;
             load_dstat();
             rstep1_id=dptstp_id;
             prn_dtlogo(rstep1_id);
             dsp_str(0,cnt,prt_buffer);
             cnbclr();
             cnt++;
             sprintf(prt_buffer,s_qtys);
             if(preset_bit)
                {
                prt_buffer[4] = '@';
                mk_dnum(dept[i].price, &prt_buffer[5], 0);
                }
             }
          if((rmcnt % 100) == 0)
             {
             rmcnt /= 100;
             dsp_rep(prt_buffer,rmcnt,cnt,0,0);
             }
          else
             dsp_rep(prt_buffer,rmcnt,cnt,2,0);
          cnt++;
          cnbclr();

          sprintf(prt_buffer,s_samt);
          grand_bit = 1;
          dsp_rep(prt_buffer,rmtotl,cnt,2,0);
          grand_bit = 0;
          cnt++;
          cnbclr();
          if(flag)
            {
            per_calp(0,rmtotl,0,rep[adjdpt].total,1,99);
            sprintf(prt_buffer,s_srates);
            grand_bit = 1;
            dsp_rep(prt_buffer,ionur,cnt,2,'%');
            grand_bit = 0;
            cnt++;
            }
          xdisp_start=0;
          continue;
       }
    }
    return;
 }
 xdisp_step = FIN_ITEMP; /*12*/
 xdisp_cnt = 0;
 if (cnt < 7) {
    for(i=xdisp_cnt;i<USE_FIN;i++, xdisp_cnt++) {
       if (cnt < 7) {
          rmcnt=rep2[i].cnt;
          rmtotl=rep2[i].totall;
          rmtotlh=rep2[i].totalh;
          if (((PRT_OPT.OPT2_1) && (rmcnt == 0) && (rmtotl == 0) && (rmtotlh == 0)) ||
              ((i == F_GROSS) && (((!PRT_OPT.OPT8_1) && (mode_id == XMODE)) ||
                ((!PRT_OPT.OPT8_2) && (mode_id == ZMODE)))) || (!PRT_OPT.OPT1_4 && (i == F_AUDACT))
                  || (!PRT_OPT.OPT1_3 && (i == F_RTN || i == F_MODEVOID)))
             continue;
          else {
             if((i == trainttl) && !PRT_OPT.OPT12_1) continue;   //971009
             if(!start)
                 {
                 clr_lcd();
                 start = 1;
                 }
             flogo_prn(i);
             if (cntprn_chk(i) || (i == F_NOSALE)) {
                if (cnt >= 7){
                   cnt++;
                   return;
                }
                else {
                   if (i <= 2)
                      {
                      if((rmcnt % 100) == 0)
                          {
                          rmcnt /= 100;
                          dsp_rep(prt_buffer,rmcnt,cnt,0,0);
                          }
                      else
                          dsp_rep(prt_buffer,rmcnt,cnt,2,0);
                      }
                   else
                      dsp_rep(prt_buffer,rmcnt,cnt,0,0);
                   cnt++;
                   cnbclr();
                   grand_bit = 1;
                   if (i == F_NOSALE) {
                      cmemcpy(prt_buffer,FUNCKEY[NONADD-CASH].DESC,15);
                      dsp_rep(prt_buffer,rmtotl,cnt,0,0);
                   }
                   else
                      dsp_rep(prt_buffer,rmtotl,cnt,2,0);
                   grand_bit = 0;
                   cnt++;
                   cnbclr();
                   xdisp_start=0;
                   continue;
                }
             }
             if (!cntprn_chk(i) && ((i == F_CASHIND) || (i == F_CHKIN))) {
                if (cnt >= 6 ) {
                   cnt += 2;
                   return;
                }
                else {
                   grand_bit = 1;
                   dsp_rep(prt_buffer,rmtotl,cnt,2,0);
                   grand_bit = 0;
                   cnt++;
                   cnbclr();
                   if (i == F_CASHIND) {           /* cash declaration */
                      nur=cashdcl;
                      if (nur != 0) {
                         cmemcpy(prt_buffer,code_mem->nur_str[20],15);
                         dsp_rep(prt_buffer,nur,cnt,2,0);
                         cnt++;
                         cnbclr();
                         nur=cashdcl - rep2[cshindw].totall;
                         rmtotlh = rep2[cshindw].totalh;
                         if(rmtotlh)
                            {
                            tfg = 0;
                            if(nur >= 0)
                                {
                                while(nur >= 0)
                                    {
                                    if(rmtotlh == 0)
                                        {
                                        tfg = 1;
                                        break;
                                        }
                                    nur = 100000000 - nur;
                                    rmtotlh--;
                                    }
                                if(!tfg)
                                    nur = -nur;
                                }
                            else
                                {
                                nur = -nur;
                                rmtotlh = -rmtotlh;
                                }
                            }
                         cmemcpy(prt_buffer,code_mem->nur_str[22],15);
                         grand_bit = 1;
                         dsp_rep(prt_buffer,nur,cnt,2,0);
                         grand_bit = 0;
                         cnt++;
                         cnbclr();
                      }
                   }
                   else if (i == F_CHKIN) {           /* check declaration */
                      nur=chckdcl;
                      if (nur != 0) {
                         cmemcpy(prt_buffer,code_mem->nur_str[21],15);
                         dsp_rep(prt_buffer,nur,cnt,2,0);
                         cnt++;
                         cnbclr();
                         nur=chckdcl - rep2[chkindw].totall;
                         rmtotlh = rep2[chkindw].totalh;
                         if(rmtotlh)
                            {
                            tfg = 0;
                            if(nur >= 0)
                                {
                                while(nur >= 0)
                                    {
                                    if(rmtotlh == 0)
                                        {
                                        tfg = 1;
                                        break;
                                        }
                                    nur = 100000000 - nur;
                                    rmtotlh--;
                                    }
                                if(!tfg)
                                    nur = -nur;
                                }
                            else
                                {
                                nur = -nur;
                                rmtotlh = -rmtotlh;
                                }
                            }
                         cmemcpy(prt_buffer,code_mem->nur_str[22],15);
                         grand_bit = 1;
                         dsp_rep(prt_buffer,nur,cnt,2,0);
                         grand_bit = 0;
                         cnt++;
                         cnbclr();
                      }
                   }
                   xdisp_start=0;
                   continue;
                }
             }
             if (!cntprn_chk(i)) {
                grand_bit = 1;
                dsp_rep(prt_buffer,rmtotl,cnt,2,0);
                grand_bit = 0;
                cnt++;
                cnbclr();
                xdisp_start=0;
                if ((i >= F_TAXFROM && i < F_TAXTO) && (i <= tax4abl)) {    /* yoo 1001 */
                    if((tax_table[i-F_TAXFROM].taxstat & 0x0f) != 1)
                        {
                        nur=tax_table[i-F_TAXFROM].taxrate;
                        prn_gcpt(1,3,2);
                        }
                    dsp_str(0,cnt,lcdbuf);
                    cnt++;
                    };
                continue;
             }
          }
       }
       return;
    }
    if (cnt <= 6)
       {
       if(!start)
           clr_lcd();
       disp_gt(cnt);
       }
 }
}
#endif

void fin_dptd()
{
 char i, cnt, flag, start=0;

 cnt = 0;

 flag = PRT_OPT.OPT3_1;
 for(i=xdisp_cnt;i<MAX_DEPT;i++, xdisp_cnt++) {
    if ((!stock_bit || cnt < 8) &&
            (stock_bit || flag || cnt < 6) &&  /* 980326 */
            (stock_bit || !flag || cnt < 5))
       {
       if(stock_bit)
            {
            rmcnt = stock_d[i];
            rmtotl = 0;
            }
       else
            {
            rmcnt=rep[i+MAX_FIN].cnt;
            rmtotl=rep[i+MAX_FIN].total;
            }
       if  ((PRT_OPT.OPT2_1) && ((rmcnt == 0) && ((rmtotl == 0) || (stock_bit))))
          continue;
       else {
          if(stock_bit && !(dept[i].status[1] & 0x10))  /* invent_bit */
             continue;
          if(!start)
             {
             clr_lcd();
             start = 1;
             }
          if (dept[i].desc[0] != 0) {
             make_desc(dept[i].desc,MAX_DEPT_DESC);
             sprintf(prt_buffer,"%s ",prt_desc);
          }
          else
             sprintf(prt_buffer,s_deptpd,i+1);
          if(!stock_bit)
             {
             func = i;
             load_dstat();
             rstep1_id=dptstp_id;
             prn_dtlogo(rstep1_id);
             dsp_str(0,cnt,prt_buffer);
             cnbclr();
             cnt++;
             sprintf(prt_buffer,s_qtys);
             if(preset_bit)
                {
                prt_buffer[4] = '@';
                mk_dnum(dept[i].price, &prt_buffer[5], 0);
                }
             }
          if((rmcnt % 100) == 0)
             {
             rmcnt /= 100;
             dsp_rep(prt_buffer,rmcnt,cnt,0,0);
             }
          else
             dsp_rep(prt_buffer,rmcnt,cnt,2,0);
          cnt++;
          cnbclr();
          if(stock_bit)
             continue;
          sprintf(prt_buffer,s_samt);
          dsp_rep(prt_buffer,rmtotl,cnt,2,0);
          cnt++;
          cnbclr();
          if(flag)
            {
            per_calp(0,rmtotl,0,rep[adjdpt].total,1,99);
            sprintf(prt_buffer,s_srates);
            dsp_rep(prt_buffer,ionur,cnt,2,'%');
            cnt++;
            }
          xdisp_start=0;
          continue;
       }
    }
    return;
 }
 if(stock_bit)
    {
    xdisp_step = REPT_DEND;
    return;
    }
 xdisp_step = FIN_ITEMD; /*12*/
 xdisp_cnt = 0;
 if (cnt < 7) {
    for(i=xdisp_cnt;i<USE_FIN;i++, xdisp_cnt++) {
       if (cnt < 7) {
          rmcnt=rep[i].cnt;
          rmtotl=rep[i].total;
          if (((PRT_OPT.OPT2_1) && (rmcnt == 0) && (rmtotl == 0)) ||
               ((i == F_GROSS) && (((!PRT_OPT.OPT8_1) && (mode_id == XMODE)) ||
                 ((!PRT_OPT.OPT8_2) && (mode_id == ZMODE)))) || (!PRT_OPT.OPT1_4 && (i == F_AUDACT))
                   || (!PRT_OPT.OPT1_3 && (i == F_RTN || i == F_MODEVOID)))
             continue;
          else {
             if((i == trainttl) && !PRT_OPT.OPT12_1) continue;    //971009
             if(!start)
                 {
                 clr_lcd();
                 start = 1;
                 }
             flogo_prn(i);
             if (cntprn_chk(i) || (i == F_NOSALE)) {
                if (cnt >= 7){
                   cnt++;
                   return;
                }
                else {
                   if (i <= 2)
                      {
                      if((rmcnt % 100) == 0)
                          {
                          rmcnt /= 100;
                          dsp_rep(prt_buffer,rmcnt,cnt,0,0);
                          }
                      else
                          dsp_rep(prt_buffer,rmcnt,cnt,2,0);
                      }
                   else
                      dsp_rep(prt_buffer,rmcnt,cnt,0,0);
                   cnt++;
                   cnbclr();
                   if (i == F_NOSALE) {
                      pmemcpy(prt_buffer,FUNCKEY[NONADD-CASH].DESC,12);
                      dsp_rep(prt_buffer,rmtotl,cnt,0,0);
                   }
                   else
                      dsp_rep(prt_buffer,rmtotl,cnt,2,0);
                   cnt++;
                   cnbclr();
                   xdisp_start=0;
                   continue;
                }
             }
             if (!cntprn_chk(i) && ((i == F_CASHIND) || (i == F_CHKIN))) {
                if (cnt >= 6 ) {
                   cnt += 2;
                   return;
                }
                else {
                   dsp_rep(prt_buffer,rmtotl,cnt,2,0);
                   cnt++;
                   cnbclr();
                   if (i == F_CASHIND) {           /* cash declaration */
                      nur=cashdcl;
                      if (nur != 0) {
                         cmemcpy(prt_buffer,code_mem->nur_str[20],15);
                         dsp_rep(prt_buffer,nur,cnt,2,0);
                         cnt++;
                         cnbclr();
                         nur=cashdcl - rep[cshindw].total;
                         cmemcpy(prt_buffer,code_mem->nur_str[22],15);
                         dsp_rep(prt_buffer,nur,cnt,2,0);
                         cnt++;
                         cnbclr();
                      }
                   }
                   else if (i == F_CHKIN) {           /* check declaration */
                      nur=chckdcl;
                      if (nur != 0) {
                         cmemcpy(prt_buffer,code_mem->nur_str[21],15);
                         dsp_rep(prt_buffer,nur,cnt,2,0);
                         cnt++;
                         cnbclr();
                         nur=chckdcl - rep[chkindw].total;
                         cmemcpy(prt_buffer,code_mem->nur_str[22],15);
                         dsp_rep(prt_buffer,nur,cnt,2,0);
                         cnt++;
                         cnbclr();
                      }
                   }
                   xdisp_start=0;
                   continue;
                }
             }
             if (!cntprn_chk(i)) {
                dsp_rep(prt_buffer,rmtotl,cnt,2,0);
                cnt++;
                cnbclr();
                xdisp_start=0;
                if ((i >= F_TAXFROM && i < F_TAXTO) && (i <= tax4abl)) {    /* yoo 1001 */
                    if((tax_table[i-F_TAXFROM].taxstat & 0x0f) != 1)
                        {
                        nur=tax_table[i-F_TAXFROM].taxrate;
                        prn_gcpt(1,3,2);
                        }
                    dsp_str(0,cnt,lcdbuf);
                    cnt++;
                    };
                continue;
             }
          }
       }
       return;
    }
    if (xdisp_start || (cnt <= 6))
       {
       if(!start)
           clr_lcd();
       disp_gt(cnt);
       }
 }
}

void fin_itemd()
{
 char i, cnt, start=0;

 cnt = 0;

    for(i=xdisp_cnt;i<USE_FIN;i++, xdisp_cnt++) {
       if (cnt < 7) {
          rmcnt=rep[i].cnt;
          rmtotl=rep[i].total;
          if (((PRT_OPT.OPT2_1) && (rmcnt == 0) && (rmtotl == 0)) ||
              ((i == F_GROSS) && (((!PRT_OPT.OPT8_1) && (mode_id == XMODE)) ||
                ((!PRT_OPT.OPT8_2) && (mode_id == ZMODE)))) || (!PRT_OPT.OPT1_4 && (i == F_AUDACT))
                  || (!PRT_OPT.OPT1_3 && (i == F_RTN || i == F_MODEVOID)))
             continue;
          else {
             if((i == trainttl) && !PRT_OPT.OPT12_1) continue;    //971009
             if(!start)
                 {
                 clr_lcd();
                 start = 1;
                 }
             flogo_prn(i);
             if (cntprn_chk(i) || (i == F_NOSALE)) {
                if (cnt >= 7){
                   cnt++;
                   return;
                }
                else {
                   if (i <= 2)
                      {
                      if((rmcnt % 100) == 0)
                          {
                          rmcnt /= 100;
                          dsp_rep(prt_buffer,rmcnt,cnt,0,0);
                          }
                      else
                          dsp_rep(prt_buffer,rmcnt,cnt,2,0);
                      }
                   else
                      dsp_rep(prt_buffer,rmcnt,cnt,0,0);
                   cnt++;
                   cnbclr();
                   if (i == F_NOSALE) {
                      pmemcpy(prt_buffer,FUNCKEY[NONADD-CASH].DESC,15);
                      dsp_rep(prt_buffer,rmtotl,cnt,0,0);
                   }
                   else
                      dsp_rep(prt_buffer,rmtotl,cnt,2,0);
                   cnt++;
                   cnbclr();
                   xdisp_start=0;
                   continue;
                }
             }
             if (!cntprn_chk(i) && ((i == F_CASHIND) || (i == F_CHKIN))) {
                if (cnt >= 6 ) {
                   cnt += 2;
                   return;
                }
                else {
                   dsp_rep(prt_buffer,rmtotl,cnt,2,0);
                   cnt++;
                   cnbclr();
                   if (i == F_CASHIND) {           /* cash declaration */
                      nur=cashdcl;
                      if (nur != 0) {
                         cmemcpy(prt_buffer,code_mem->nur_str[20],15);
                         dsp_rep(prt_buffer,nur,cnt,2,0);
                         cnt++;
                         cnbclr();
                         nur=cashdcl - rep[cshindw].total;
                         cmemcpy(prt_buffer,code_mem->nur_str[22],15);
                         dsp_rep(prt_buffer,nur,cnt,2,0);
                         cnt++;
                         cnbclr();
                      }
                   }
                   else if (i == F_CHKIN) {           /* check declaration */
                      nur=chckdcl;
                      if (nur != 0) {
                         cmemcpy(prt_buffer,code_mem->nur_str[21],15);
                         dsp_rep(prt_buffer,nur,cnt,2,0);
                         cnt++;
                         cnbclr();
                         nur=chckdcl - rep[chkindw].total;
                         cmemcpy(prt_buffer,code_mem->nur_str[22],15);
                         dsp_rep(prt_buffer,nur,cnt,2,0);
                         cnt++;
                         cnbclr();
                      }
                   }
                   xdisp_start=0;
                   continue;
                }
             }
             if (!cntprn_chk(i)) {
                dsp_rep(prt_buffer,rmtotl,cnt,2,0);
                cnt++;
                cnbclr();
                xdisp_start=0;
                if ((i >= F_TAXFROM && i < F_TAXTO) && (i <= tax4abl)) {    /* yoo 1001 */
                    if((tax_table[i-F_TAXFROM].taxstat & 0x0f) != 1)
                        {
                        nur=tax_table[i-F_TAXFROM].taxrate;
                        prn_gcpt(1,3,2);
                        dsp_str(0,cnt,lcdbuf);
                        cnt++;
                        }
                    };
                continue;
             }
          }
       }
       return;
    }
    if (cnt <= 6)
       {
       if(!start)
           clr_lcd();
       disp_gt(cnt);
       }
}

void fin_itemp()
{
 char i, cnt, tfg, start=0;

 cnt = 0;

    for(i=xdisp_cnt;i<USE_FIN;i++, xdisp_cnt++) {
       if (cnt < 7) {
          rmcnt=rep2[i].cnt;
          rmtotl=rep2[i].totall;
          rmtotlh=rep2[i].totalh;
          if (((PRT_OPT.OPT2_1) && (rmcnt == 0) && (rmtotl == 0) && (rmtotlh == 0)) ||
              ((i == F_GROSS) && (((!PRT_OPT.OPT8_1) && (mode_id == XMODE)) ||
                ((!PRT_OPT.OPT8_2) && (mode_id == ZMODE)))) || (!PRT_OPT.OPT1_4 && (i == F_AUDACT))
                  || (!PRT_OPT.OPT1_3 && (i == F_RTN || i == F_MODEVOID)))
             continue;
          else {
             if((i == trainttl) && !PRT_OPT.OPT12_1) continue;    //971009
             if(!start)
                 {
                 clr_lcd();
                 start = 1;
                 }
             flogo_prn(i);
             if (cntprn_chk(i) || (i == F_NOSALE)) {
                if (cnt >= 7){
                   cnt++;
                   return;
                }
                else {
                   if (i <= 2)
                      {
                      if((rmcnt % 100) == 0)
                          {
                          rmcnt /= 100;
                          dsp_rep(prt_buffer,rmcnt,cnt,0,0);
                          }
                      else
                          dsp_rep(prt_buffer,rmcnt,cnt,2,0);
                      }
                   else
                      dsp_rep(prt_buffer,rmcnt,cnt,0,0);
                   cnt++;
                   cnbclr();
                   grand_bit = 1;
                   if (i == F_NOSALE) {
                      cmemcpy(prt_buffer,FUNCKEY[NONADD-CASH].DESC,15);
                      dsp_rep(prt_buffer,rmtotl,cnt,0,0);
                   }
                   else
                      dsp_rep(prt_buffer,rmtotl,cnt,2,0);
                   grand_bit = 0;
                   cnt++;
                   cnbclr();
                   xdisp_start=0;
                   continue;
                }
             }
             if (!cntprn_chk(i) && ((i == F_CASHIND) || (i == F_CHKIN))) {
                if (cnt >= 6 ) {
                   cnt += 2;
                   return;
                }
                else {
                   grand_bit = 1;
                   dsp_rep(prt_buffer,rmtotl,cnt,2,0);
                   grand_bit = 0;
                   cnt++;
                   cnbclr();
                   if (i == F_CASHIND) {           /* cash declaration */
                      nur=cashdcl;
                      if (nur != 0) {
                         cmemcpy(prt_buffer,code_mem->nur_str[20],15);
                         dsp_rep(prt_buffer,nur,cnt,2,0);
                         cnt++;
                         cnbclr();
                         nur=cashdcl - rep2[cshindw].totall;
                         rmtotlh = rep2[cshindw].totalh;
                         if(rmtotlh)
                            {
                            tfg = 0;
                            if(nur >= 0)
                                {
                                while(nur >= 0)
                                    {
                                    if(rmtotlh == 0)
                                        {
                                        tfg = 1;
                                        break;
                                        }
                                    nur = 100000000 - nur;
                                    rmtotlh--;
                                    }
                                if(!tfg)
                                    nur = -nur;
                                }
                            else
                                {
                                nur = -nur;
                                rmtotlh = -rmtotlh;
                                }
                            }
                         cmemcpy(prt_buffer,code_mem->nur_str[22],15);
                         grand_bit = 1;
                         dsp_rep(prt_buffer,nur,cnt,2,0);
                         grand_bit = 0;
                         cnt++;
                         cnbclr();
                      }
                   }
                   else if (i == F_CHKIN) {           /* check declaration */
                      nur=chckdcl;
                      if (nur != 0) {
                         cmemcpy(prt_buffer,code_mem->nur_str[21],15);
                         dsp_rep(prt_buffer,nur,cnt,2,0);
                         cnt++;
                         cnbclr();
                         nur=chckdcl - rep2[chkindw].totall;
                         rmtotlh = rep2[chkindw].totalh;
                         if(rmtotlh)
                            {
                            tfg = 0;
                            if(nur >= 0)
                                {
                                while(nur >= 0)
                                    {
                                    if(rmtotlh == 0)
                                        {
                                        tfg = 1;
                                        break;
                                        }
                                    nur = 100000000 - nur;
                                    rmtotlh--;
                                    }
                                if(!tfg)
                                    nur = -nur;
                                }
                            else
                                {
                                nur = -nur;
                                rmtotlh = -rmtotlh;
                                }
                            }
                         cmemcpy(prt_buffer,code_mem->nur_str[22],15);
                         grand_bit = 1;
                         dsp_rep(prt_buffer,nur,cnt,2,0);
                         grand_bit = 0;
                         cnt++;
                         cnbclr();
                      }
                   }
                   xdisp_start=0;
                   continue;
                }
             }
             if (!cntprn_chk(i)) {
                grand_bit = 1;
                dsp_rep(prt_buffer,rmtotl,cnt,2,0);
                grand_bit = 0;
                cnt++;
                cnbclr();
                xdisp_start=0;
                if ((i >= F_TAXFROM && i < F_TAXTO) && (i <= tax4abl)) {    /* yoo 1001 */
                    if((tax_table[i-F_TAXFROM].taxstat & 0x0f) != 1)
                        {
                        nur=tax_table[i-F_TAXFROM].taxrate;
                        prn_gcpt(1,3,2);
                        }
                    dsp_str(0,cnt,lcdbuf);
                    cnt++;
                    };
                continue;
             }
          }
       }
       return;
    }
    if (cnt <= 6)
       {
       if(!start)
           clr_lcd();
       disp_gt(cnt);
       }
}

void disp_timed()
{
 int i, cnt;

 cnt = 0;

 for(i=xdisp_cnt;i<25;i++, xdisp_cnt++) {
    if (cnt < 8) {
       if (i == 24) {
          rmcnt=rep[t_base+i].cnt;
          rmtotl=rep[t_base+i].total;
          sprintf(prt_buffer,s_ttlcnt);
          dsp_rep(prt_buffer,rmcnt,cnt,0,0);
          cnt++;
          cnbclr();
          sprintf(prt_buffer,s_ttlamt);
          dsp_rep(prt_buffer,rmtotl,cnt,2,0);
          cnt++;
          cnbclr();
          continue;
       }
       else {
          rmcnt=rep[i+t_base].cnt;
          rmtotl=rep[i+t_base].total;
          if  ((rmcnt == 0) && (rmtotl == 0))
             continue;
          else {
             sprintf(prt_buffer,s_timepd,i);
             dsp_str(0,cnt,prt_buffer);
             cnbclr();
             cnt++;
             sprintf(prt_buffer,s_cnts);
             dsp_rep(prt_buffer,rmcnt,cnt,0,0);
             cnt++;
             cnbclr();
             sprintf(prt_buffer,s_samt);
             dsp_rep(prt_buffer,rmtotl,cnt,2,0);
             cnt++;
             cnbclr();
             per_calp(0,rmtotl,0,rep[tmtotl].total,1,99);
             sprintf(prt_buffer,s_srates);
             dsp_rep(prt_buffer,ionur,cnt,2,'%');
             cnt++;
             cnbclr();
             continue;
          }
       }
    }
    return;
 }
 xdisp_step = REPT_DEND;
}

void disp_dayd()
{
 int i, cnt;

 cnt = 0;

 for(i=xdisp_cnt;i<32;i++, xdisp_cnt++) {
    if (cnt < 8) {
       if (i == 31) {
          rmcnt=rep[da_base+i].cnt;
          rmtotl=rep[da_base+i].total;
          sprintf(prt_buffer,s_ttlcnt);
          dsp_rep(prt_buffer,rmcnt,cnt,0,0);
          cnt++;
          cnbclr();
          sprintf(prt_buffer,s_ttlamt);
          dsp_rep(prt_buffer,rmtotl,cnt,2,0);
          cnt++;
          cnbclr();
          continue;
       }
       else {
          rmcnt=rep[i+da_base].cnt;
          rmtotl=rep[i+da_base].total;
          if  ((rmcnt == 0) && (rmtotl == 0))
             continue;
          else {
             sprintf(prt_buffer,s_daypd,i+1);
             dsp_str(0,cnt,prt_buffer);
             cnbclr();
             cnt++;
             sprintf(prt_buffer,s_cnts);
             dsp_rep(prt_buffer,rmcnt,cnt,0,0);
             cnt++;
             cnbclr();
             sprintf(prt_buffer,s_samt);
             dsp_rep(prt_buffer,rmtotl,cnt,2,0);
             cnt++;
             cnbclr();
             per_calp(0,rmtotl,0,rep[tmtotl].total,1,99);
             sprintf(prt_buffer,s_srates);
             dsp_rep(prt_buffer,ionur,cnt,2,'%');
             cnt++;
             cnbclr();
             continue;
          }
       }
    }
    return;
 }
 xdisp_step = REPT_DEND;
}

void disp_plud()
{
 int i, cnt, m_plu, start=0;
 char flag;

 cnt = 0;
 if(stock_bit)
    m_plu = MAX_PLU;
 else
    m_plu = MAX_PLU+1;

 flag = PRT_OPT.OPT3_2;
 for(i=xdisp_cnt;i<m_plu;i++, xdisp_cnt++) {
    if ((!stock_bit || cnt < 8) &&
            (stock_bit || flag || cnt < 6) &&
            (stock_bit || !flag || cnt < 5))
       {
       if (i == MAX_PLU) {
          if(!start)
             {
             clr_lcd();
             start = 1;
             }
          rmcnt=rep[tplu].cnt;
          rmtotl=rep[tplu].total;
          sprintf(prt_buffer,s_ttlcnt);
          if((rmcnt % 100) == 0)
             {
             rmcnt /= 100;
             dsp_rep(prt_buffer,rmcnt,cnt,0,0);
             }
          else
             dsp_rep(prt_buffer,rmcnt,cnt,2,0);
          cnt++;
          cnbclr();
          sprintf(prt_buffer,s_ttlamt);
          dsp_rep(prt_buffer,rmtotl,cnt,2,0);
          cnt++;
          cnbclr();
          continue;
       }
       else {
          if(stock_bit)
             {
             rmcnt = stock_p[i];
             rmtotl = 0;
             }
          else
             {
             rmcnt=rep[i+p_base].cnt;
             rmtotl=rep[i+p_base].total;
             }
//          if  ((rmcnt == 0) && ((rmtotl == 0) || (stock_bit)))
          if(!no_skip(IS_PLU))
             continue;
          else {
             if(stock_bit && !(plu[i].status[1] & 0x10))  /* invent_bit */
                continue;
             if(!start)
                 {
                 clr_lcd();
                 start = 1;
                 }
             if (plu[i].desc[0] != 0) {
                make_desc(plu[i].desc,MAX_PLU_DESC);
                sprintf(prt_buffer,"%s",prt_desc);
             }
             else
                sprintf(prt_buffer,s_plupd,i+1);
             if(!stock_bit)
                {
                pcode = i;
                load_pstat();
                rstep1_id=dptstp_id;
                prn_dtlogo(rstep1_id);
                dsp_str(0,cnt,prt_buffer);
                cnbclr();
                cnt++;
                if(PRT_OPT.OPT2_6)
                    {
                    sprintf(prt_buffer,s_ldeptpd,plu[i].link_dept);
                    dsp_str(0,cnt,prt_buffer);
                    cnbclr();
                    cnt++;
                    }
                sprintf(prt_buffer,s_qtys);
                if(preset_bit)
                    {
                    prt_buffer[4] = '@';
                    mk_dnum(plu[i].price, &prt_buffer[5], 0);
                    }
                }
             if((rmcnt % 100) == 0)
                {
                rmcnt /= 100;
                dsp_rep(prt_buffer,rmcnt,cnt,0,0);
                }
             else
                dsp_rep(prt_buffer,rmcnt,cnt,2,0);
             cnbclr();
             cnt++;
             if(!stock_bit)
                {
                sprintf(prt_buffer,s_samt);
                dsp_rep(prt_buffer,rmtotl,cnt,2,0);
                cnt++;
                cnbclr();
                if(flag)
                    {
                    per_calp(0,rmtotl,0,rep[tplu].total,1,99);
                    sprintf(prt_buffer,s_srates);
                    dsp_rep(prt_buffer,ionur,cnt,2,'%');
                    cnt++;
                    cnbclr();
                    }
                }
             continue;
          }
       }
    }
    return;
 }
 xdisp_step = REPT_DEND;
}

void disp_clkd()
{
 int i, cnt, bb, start=0;

 cnt = 0;
 while (clk_s <= clk_e) {
    bb=c_base+(clk_s - 1)*MAX_CLKITEM;

    for(i=xdisp_cnt;i<USE_CLKITEM;i++, xdisp_cnt++) {
       if (cnt < 7) {
          rmcnt=rep[bb+i].cnt;
          rmtotl=rep[bb+i].total;
          if  ((PRT_OPT.OPT2_4) && (rmcnt == 0) && (rmtotl == 0)) {
             if ((!PRT_OPT.OPT1_1) && (i == 0))
                i = USE_CLKITEM - 2;
             continue;
          }

          if(!start)
             {
             clr_lcd();
             start = 1;
             }
          if (name_prt == 0 && i != 0){
                sprintf(prt_buffer,s_clkpd,clk_s);
                dsp_rep(prt_buffer,rep[bb].cnt,cnt,0,0);
                cnbclr();
                cnt++;
                name_prt=1;
                if (cnt >= 8)
                   return;
          }

          if (ccntprn_chk(i)){
             if (cnt >= 7) {
                cnt = 8;
                return;
             }
             if (i == 0) {
                sprintf(prt_buffer,s_clkpd,clk_s);
                dsp_rep(prt_buffer,rmcnt,cnt,0,0);
                cnbclr();
                cnt++;
                name_prt=1;
             }
             else {
                clogo_prn(i);
                dsp_rep(prt_buffer,rmcnt,cnt,0,0);
                cnbclr();
                cnt++;
             }
          }

          if (i != FC_NOSALE){
             if (i == 0 || !ccntprn_chk(i))
                clogo_prn(i);
             dsp_rep(prt_buffer,rmtotl,cnt,2,0);
             cnbclr();
             cnt++;
          }
          clk_rpt = 0;
          if (!PRT_OPT.OPT1_1 && (i == 0))
             i = USE_CLKITEM - 2;
       }
       else
          return;
    }
    clk_s++;
    xdisp_cnt = name_prt = 0;
 }
 xdisp_step = REPT_DEND;
}

void disp_groupd()
{
 int i, cnt, start=0;

 cnt = 0;

 for(i=xdisp_cnt;i<=MAX_GROUP;i++, xdisp_cnt++) {
    if (cnt < 8) {
       if (i == MAX_GROUP) {
          if(!start)
             {
             clr_lcd();
             start = 1;
             }
          rmcnt=rep[grp_total].cnt;
          rmtotl=rep[grp_total].total;
          sprintf(prt_buffer,s_ttlcnt);
          if((rmcnt % 100) == 0)
             {
             rmcnt /= 100;
             dsp_rep(prt_buffer,rmcnt,cnt,0,0);
             }
          else
             dsp_rep(prt_buffer,rmcnt,cnt,2,0);
          cnt++;
          cnbclr();
          sprintf(prt_buffer,s_ttlamt);
          dsp_rep(prt_buffer,rmtotl,cnt,2,0);
          cnt++;
          cnbclr();
          continue;
       }
       else {
          rmcnt=rep[i+g_base].cnt;
          rmtotl=rep[i+g_base].total;
          if  ((rmcnt == 0) && (rmtotl == 0))
             continue;
          else {
             if (cnt >= 6) {
                cnt = 8;
                return;
             }
             else {
                if(!start)
                    {
                    clr_lcd();
                    start = 1;
                    }
                prn_grpdec(i);
                dsp_str(0,cnt,prt_buffer);
                cnbclr();
                cnt++;
                sprintf(prt_buffer,s_cnts);
                if((rmcnt % 100) == 0)
                    {
                    rmcnt /= 100;
                    dsp_rep(prt_buffer,rmcnt,cnt,0,0);
                    }
                else
                    dsp_rep(prt_buffer,rmcnt,cnt,2,0);
                cnt++;
                cnbclr();
                sprintf(prt_buffer,s_samt);
                dsp_rep(prt_buffer,rmtotl,cnt,2,0);
                cnt++;
                cnbclr();
                continue;
             }
          }
       }
    }
    return;
 }
 xdisp_step = REPT_DEND;
}

void disp_tmiod()
{
    int i, j, cnt, time;
    UBYTE ss, pm_f;

    cnt = 0;

    clr_lcd();
    for(i=xdisp_cnt2;i<=MAX_CLERK; i++, xdisp_cnt2++)
        {
        if (cnt < 8)
            {
            if (i == MAX_CLERK)
                {
                sprintf(prt_buffer,s_ttlwork);
                dsp_rep(prt_buffer,clk_tmttl*100+clk_min,cnt,12,0);  /* 980326 */
                cnt++;
                cnbclr();
                name_prt = 0;
                continue;
                }
            else
                {
                if(CLKIO[i].T_IDX)
                    {
                    if (!name_prt)
                        {
                        sprintf(prt_buffer,s_clkpd,i+1);
                        dsp_str(0,cnt,prt_buffer);
                        cnbclr();
                        cnt++;
                        xdisp_cnt = 0;
                        name_prt=1;
                        if (cnt >= 8)
                        return;
                        }
                    for(j=xdisp_cnt;j<=CLKIO[i].T_IDX; j++, xdisp_cnt++)
                        {
                        pm_f = 0;
                        if (cnt < 8)
                            {
                            if (j == CLKIO[i].T_IDX)
                                {
                                sprintf(prt_buffer,s_tworked);
                                dsp_rep(prt_buffer,CLKIO[i].W_TIME,cnt,12,0);  /* 980326 */
                                cnt++;
                                cnbclr();
                                name_prt = 0;
                                clk_tmttl += (CLKIO[i].W_TIME / 100);
                                clk_min += (CLKIO[i].W_TIME % 100);  /* 980326 */
                                if(clk_min >= 60)
                                    {
                                    clk_tmttl++;
                                    clk_min -= 60;
                                    }
                                if (cnt >= 8)
                                    continue;
                                }
                            else
                                {
                                time = CLKIO[i].T_LOG[j];
                                if (time >= 1200)
                                    pm_f = 1;
                                if (time >= 1300)
                                    time -= 1200;
                                if (j & 0x01)
                                    sprintf(prt_buffer,s_tmoutss);
                                else
                                    sprintf(prt_buffer,s_tminss);
                                ss = 13;
                                prt_buffer[ss++]=(time/1000)+'0';
                                prt_buffer[ss++]=((time%1000)/100)+'0';
                                prt_buffer[ss++]=':';
                                prt_buffer[ss++]=((time%100)/10)+'0';
                                prt_buffer[ss++]=(time%10)+'0';
                                if(pm_f) prt_buffer[ss++] = 'P';
                                else prt_buffer[ss++] = 'A';
                                prt_buffer[ss] = 'M';
                                dsp_str(0,cnt,prt_buffer);
                                cnbclr();
                                cnt++;
                                }
                            }
                        else
                            return;
                        }
                    }
                }
            }
        else
            return;
        if(xdisp_cnt3 != 99)
            i = xdisp_cnt2 = MAX_CLERK;
        }
    xdisp_step = REPT_DEND;
}

void x_disp()
{
//   clr_lcd();

   switch(xdisp_step)
   {
      case FIN_DEPTD:
         fin_dptd();
         break;
#ifdef SPECIAL_REP
      case FIN_DEPTP:
         fin_dptp();
         break;
#endif
      case FIN_ITEMD:
         fin_itemd();
         break;
      case FIN_ITEMP:
         fin_itemp();
         break;
      case DISP_TIMED:
         disp_timed();
         break;
      case DISP_DAYD:
         disp_dayd();
         break;
      case DISP_PLUD:
         disp_plud();
         break;
      case DISP_CLKD:
         disp_clkd();
         break;
      case DISP_GROUPD:
         disp_groupd();
         break;
      case DISP_TMIOD:
         disp_tmiod();
         break;
      case DISP_STP:
         stock_bit = 1;
         disp_plud();
         stock_bit = 0;
         break;
      case DISP_STD:
         stock_bit = 1;
         fin_dptd();
         stock_bit = 0;
         break;
      default:
         break;
   }
}

void disp_finr()
{
    logo_only(39);
    dsp_str(0,5,prt_buffer);
    cnbclr();
    dsp_str(0,6,prt_buffer);
    xdisp_step = FIN_DEPTD;
    xdisp_cnt = 0;
    xdisp_start = 1;
//    flg_concid = 0;
    return;
}

void disp_finp()
{
    dspr_sub(39);
    rept_con = 1;
    logo_only(39);
    dsp_str(0,5,prt_buffer);
    cnbclr();
    dsp_str(0,6,prt_buffer);
#ifdef SPECIAL_REP
    xdisp_step = FIN_DEPTP;
#else
    xdisp_step = FIN_ITEMP;
#endif
    xdisp_cnt = 0;
    xdisp_start = 1;
//    flg_concid = 0;
    return;
}

void disp_timer()
{
    logo_only(34);
    dsp_str(0,5,prt_buffer);
    cnbclr();
    dsp_str(0,6,prt_buffer);
    xdisp_step = DISP_TIMED;
    xdisp_cnt = 0;
    xdisp_start = 1;
    return;
}

void disp_dayr()
{
    logo_only(35);
    dsp_str(0,5,prt_buffer);
    cnbclr();
    dsp_str(0,6,prt_buffer);
    xdisp_step = DISP_DAYD;
    xdisp_cnt = 0;
    xdisp_start = 1;
    return;
}

void disp_plur()
{
    logo_only(38);
    dsp_str(0,5,prt_buffer);
    cnbclr();
    dsp_str(0,6,prt_buffer);
    xdisp_step = DISP_PLUD;
    xdisp_cnt = 0;
    xdisp_start = 1;
    return;
}

void one_clkr()
{
    long temp;

    EJ_FLAG = EJ_REPORT;
    if ((menu_no == MENU_PRINT2) || (mode_id == ZMODE)) {
        rep_clk();
    }
    else {
        temp=nur;
        dspr_sub(40);
        nur=temp;
        logo_only(40);
        dsp_str(0,5,prt_buffer);
        cnbclr();
        dsp_str(0,6,prt_buffer);
        xdisp_step = DISP_CLKD;
        xdisp_cnt = 0;
        xdisp_start = 1;
        rept_con = 1;
        name_prt = 0;
        clk_s = clk_e = (char)nur;
    }
    lcd_dsp(1);                            /* PKR 0229 */
    clk_rpt=1;
    rpt_kind=0;
    post_tamt=0;
    init_mdchg();
    initseq();
//    EJ_FLAG = EJ_NORMAL;
}

void disp_clkall()
{
    logo_only(29);
    dsp_str(0,5,prt_buffer);
    cnbclr();
    dsp_str(0,6,prt_buffer);
    xdisp_step = DISP_CLKD;
    xdisp_cnt = 0;
    xdisp_start = 1;
    clk_s = 1;
    clk_e = MAX_CLERK;
    name_prt = 0;
}

void disp_caindr()
{
#if 0
 logo_only(37);
 dsp_str(0,5,prt_buffer);
 cnbclr();
#endif
 nur=rep[cshindw].total;
 sprintf(prt_buffer,s_cashind);
 dsp_rep(prt_buffer,nur,5,2,0);
 nur=rep[chkindw].total;
 sprintf(prt_buffer,s_chind);
 dsp_rep(prt_buffer,nur,6,2,0);
 cnbclr();
 page_stat=5;
}

void disp_groupr()
{

 logo_only(36);
 dsp_str(0,5,prt_buffer);
 cnbclr();
 dsp_str(0,6,prt_buffer);
 xdisp_step = DISP_GROUPD;
 xdisp_cnt = 0;
 xdisp_start = 1;
 return;
}

void menu_dsp()
{
    long temp;

    if (mode_id == XMODE)
        {
        if ((rept_ptd == 3) && (nur != 0)) {errmsg = E_KEY; ERR};
        if(rept_ptd)
            {
            disp_finp();
            return;
            }

        switch(nur)
            {
            case 0:            /* Financial */
                temp=nur;   dspr_sub(39);   nur=temp;
                rept_con = 1;
                disp_finr();
                break;
            case 1:            /* Time */
                temp=nur;   dspr_sub(34);   nur=temp;
                rept_con = 1;
                disp_timer();
                break;
            case 2:            /* Daily */
                temp=nur;   dspr_sub(35);   nur=temp;
                rept_con = 1;
                disp_dayr();
                break;
            case 3:            /* PLU */
                temp=nur;   dspr_sub(38);   nur=temp;
                rept_con = 1;
                disp_plur();
                break;
            case 4:            /* ALL CLERK */
                temp=nur;   dspr_sub(29);   nur=temp;  /* 980326 */
                rept_con = 1;                          /* 980326 */
                disp_clkall();
                break;
            case 5:            /* INDIVIDUAL CLERK */
                temp=nur;   dspr_sub(40);   nur=temp;
                rept_con = 1;
                rep_clk_s();
                break;
            case 6:            /* Group */
                temp=nur;   dspr_sub(36);   nur=temp;
                rept_con = 1;
                disp_groupr();
                break;
            case 7:
                temp=nur;   dspr_sub(46);   nur=temp;
                rept_con = 1;
                disp_stpt();
                break;
            case 8:
                temp=nur;   dspr_sub(47);   nur=temp;
                rept_con = 1;
                disp_stdt();
                break;
            case 9:            /* Time in-out */
                start_menu(MENU_CNO2);
                break;
            case 10:            /* Cash/Check in Drawer */
                temp=nur;   dspr_sub(37);   nur=temp;
                rept_con = 1;
                disp_caindr();
                rept_con = 0;
                break;
            }
        }
    else
        {
        memoryup = 3;

        switch(nur)
            {
            case 1:            /* Financial */
                s_dim = podept;
                e_dim = c_base;
                break;
            case 2:            /* Time */
                s_dim = t_base;
                e_dim = da_base;
                break;
            case 3:            /* PLU */
                s_dim = p_base;
                e_dim = e_base;
                break;
            case 4:            /* CLERK */
                s_dim = c_base;
                e_dim = t_base;
                break;
            }
        clr_rep();
//        page_stat=2;
//        start_menu(MENU_DISPLAY);
    }
    rep_disp=0;
}

void menu_rst()
{
// unsigned char tmp_menu;

//  tmp_menu = menu_no;
  if (rept_step == 1)
     menu_prn();
  else if (rept_step == 0) {
     if ((nur < 0) || (nur > 3)) {errmsg = E_KEY; ERR};
     if (nur == 0) {
        page_stat=1;
        rept_step = 1;
        rept_ptd = 0;
        start_menu(MENU_PRINT2);
     }
     else if(nur == 1) {
        rept_ptd = 1;
        rept_step = 1;
        start_menu(MENU_PTDPRN);
     }
     else if(nur == 2)
        xmode_fun(MENU_REJ);
#ifdef PCCOMM
     else if(nur == 3)
        {
        comm_sior(1);
        start_menu(MENU_RESET);
        }
#endif
  }
//  menu_no = tmp_menu;
}

/*****************************************************************************/
/***                           REPORT                                      ***/
/*****************************************************************************/
void report()
{
    char rno;

    rno=(char)nur;
    if ((clerk == 0) && !((mode_id == ZMODE) && !clrk_step && (menu_no == MENU_RESET) && (nur == 3)))
        {cl_out();errmsg=E_REQCLK;ERR};
    if ((train_flg && mode_id == ZMODE)) {errmsg=E_TRAIN;ERR}
    if ((SYS_OPT.OPT6_1) && !clrk_step && (flg_concid != 2) && (rno < 2))
//        (((mode_id == XMODE) && (rept_step == 2)) || ((mode_id == ZMODE) && (rept_step == 1))))
        { errmsg=E_COMPDEC; ERR };
    if ((rept_step == 0) && (flg_concid == 2) && (nur == 2)) {errmsg=E_KEY;ERR};
    if (xm_step != 0)
        {
        if(mode_id == XMODE)
            {errmsg=E_KEY;ERR}
        else
            xm_step = 0;
        }

    if (clrk_step) {
        if ((!rno && knur_bit) || (rno > 20)) {errmsg = E_KEY; ERR}
        if(menu_no == MENU_CNO)
            clk_time(rno-1);
        else if(menu_no == MENU_CNO2)
            disp_tmio(rno-1);
        else
            one_clkr();
//        clrk_step = 0;
        nur = 0;
        return;
    }
    else {
        rno=(char)nur;

    if (rept_con || (rept_con && knur_bit) || !ncnt) {errmsg=E_KEY;ERR};

    switch(menu_no)
        {
        case MENU_MANAGER:
            menu_man();
            break;
        case MENU_PRINT:
            if (nur == 0) {
                start_menu(MENU_PRINT2);
                page_stat=1;
                rept_ptd = index = 0;
                }
            else if (nur == 1) {
                start_menu(MENU_PTDPRN);
                rept_ptd = 2;
                index = 1;
                }
            else if (nur == 2)
                rep_ej();      /* Electronic Journal */
            rept_step = 2;
            break;
        case MENU_PRINT2:
            menu_prn();
            break;
        case MENU_DISPLAY:
            if (nur == 0) {
                start_menu(MENU_DISPLAY2);
                page_stat = 2;
                rept_ptd = index = 0;
                }
            else if(nur == 1) {
                start_menu(MENU_PTDDSP);
                rept_ptd = 3;
                index = 1;
                }
            rept_step = 2;
            break;
        case MENU_DISPLAY2:
            menu_dsp();
            break;
        case MENU_RESET:
            menu_rst();
            break;
        case MENU_EJ:
            prc_ej();
            break;
        case MENU_CNO:
        case MENU_CNO2:
            prc_clktm();
            break;
        }
    }
    clk_rpt=1;
    rpt_kind=0;
    post_tamt=0;
    init_mdchg();
    initseq();
    return;
}

void page_down()
{
    if ((mode_id == XMODE) && rept_con) {
        if (xdisp_step != REPT_DEND)
            x_disp();
        return;
    }
    if ((page_stat < 0) || (page_stat >= 5) ||
            knur_bit || (rept_ptd == 1)) return;
    if((l_no > 7) && !rept_con && !menu_st)
        {
        menu_st = 1 - menu_st;
        dsp_menu();
        }
}

void page_up()
{
    if((l_no > 7) && !rept_con && menu_st)
        {
        menu_st = 1 - menu_st;
        dsp_menu();
        }
}
/*****************************************************************************/
/***                        CASH DECLARATION                               ***/
/*****************************************************************************/
void x_enter()
{
   long tmp_ttl,diff;

   if (((xm_step != XM_DECL) && (func == CHECK)) ) {errmsg=E_KEY;ERR};
   if (xm_step == XM_DECL) {
      if ((rept_step != 3) || (!nur && (func == CHECK))) {errmsg=E_KEY;ERR};
      if (!flg_concid)
         cashdcl = chckdcl = 0;
      if (knur_bit) {
         if (mul_bit) nur*=mul;
         lcd_rec(2);
         if (func == CHECK) {
            chckdcl +=nur;
            sprintf(prt_buffer,"%s ",get_fdesc(CHECK));
            dsp_rep(prt_buffer,chckdcl,3,2,0);
//            nur = chckdcl;
            prn_tend(DINX_CHECK,CHECK,0);
         }
         else {
            cashdcl +=nur;
            sprintf(prt_buffer,"%s ",get_fdesc(CASH));
            dsp_rep(prt_buffer,cashdcl,2,2,0);
//            nur = cashdcl;
            prn_tend(DINX_CASH,CASH,0);
         }
         mkdnur(0);
         initseq();
         tmp_ttl = cashdcl + chckdcl;
         sprintf(prt_buffer,s_ttls);
         dsp_rep(prt_buffer,tmp_ttl,5,2,0);
         flg_concid = 1;
      }
      else {
         if (func != CASH) {errmsg=E_KEY;ERR};
         nur=cashdcl+chckdcl;
         sprintf(prt_buffer,s_ipamt);
         dsp_rep(prt_buffer,nur,2,2,0);
         mkdnur(0);
         prn_tend(DINX_TOTAL,0,0);
         tmp_ttl = rep[cshindw].total + rep[chkindw].total;
         sprintf(prt_buffer,s_dwrttl);
         dsp_rep(prt_buffer,tmp_ttl,3,2,0);
         diff = nur-tmp_ttl;
         sprintf(prt_buffer,s_diff);
         dsp_rep(prt_buffer,diff,5,2,0);

         sprintf(prt_buffer,s_ipamt);
         sep_prn();
         nur=tmp_ttl;
         sprintf(prt_buffer,s_dwrttl);
         sep_prn();
         nur=diff;
         sprintf(prt_buffer,s_diff);
         sep_prn();
         endlogo();
         xm_step = XM_DECLF;
         flg_concid = 2;
         rept_step = page_stat = 0;
         ini_outdtx();
         initseq();
#if 0
         start_menu(MENU_MANAGER);
#endif
      }
   }
   else if ((xm_step == XM_RCONT) || (xm_step == XM_RCONTS)) {
      if (knur_bit) {errmsg = E_KEY; ERR};
      if (((xm_step == XM_RCONTS) && (r_cont == 0)) ||
            ((xm_step == XM_RCONT) && (r_cont == 1))) {
         sprintf(prt_buffer,s_rctps,r_cont?s_on:s_off);
         r_cont ^= 1;
            des_prn();
            endlogo();
      }
      rept_step = page_stat = xm_step = 0;
      ini_outdtx();
      initseq();
      start_menu(MENU_MANAGER);
   }
   else if (xm_step >= XM_RONOFF) {
      if ((nur && ((xm_step == XM_RONOFF) || (xm_step == XM_RONOFFS))) ||
               (!knur_bit && (xm_step == XM_TRAIN)) || ((xm_step == XM_TRAIN) && (nur >= 10000))) {errmsg=E_KEY;ERR};
      menu_no = MENU_MANAGER;
      if (((xm_step == XM_RONOFFS) && (r_off == 0)) ||
            ((xm_step == XM_RONOFF) && (r_off == 1))) {
         sprintf(prt_buffer,s_regprt,r_off?s_on:s_off);
         r_off ^= 1;
         des_prn();
         endlogo();
      }
      else if (xm_step == XM_TRAIN) {
/*       if (nur != SYS_OPT.OPT9) {errmsg=E_KEY;ERR};*/
         if (train_flg) {
            if (nur || !knur_bit) {errmsg=E_NUMOVER;ERR};
            train_flg = 0;
         }
         else {
            if (!nur || (nur != SYS_OPT.OPT9)) {errmsg=E_NUMOVER;ERR};
            train_flg = 1;
         }
      }
      else if (xm_step == ZM_REJS)
         {
         menu_no = MENU_RESET;
         rep_ej();
         }
      else if (xm_step == ZM_REJ)
         menu_no = MENU_RESET;
      rept_step = page_stat = xm_step = 0;
      ini_outdtx();
      initseq();
      start_menu(menu_no);
   }
   else
      report();
}

void dsp_xfunc(UBYTE m_no, UBYTE l_no)
{
    UBYTE i, j;
    UBYTE buf[22];

    for(i=m_no,j=2;i<l_no;i++,j++)
        {
        cmemcpy(buf,code_mem->xmenu_str[i],21);
        dsp_str(0,j,buf);
        }
}

void x_yesno()
{
  if (nur) {errmsg=E_KEY;ERR};
  if (xm_step == XM_RONOFF)
     {
     xm_step = XM_RONOFFS;
     dsp_xfunc(14, 19);
     }
  else if (xm_step == XM_RONOFFS)
     {
     xm_step = XM_RONOFF;
     dsp_xfunc(4, 9);
     }
  else if (xm_step == XM_RCONT)
     {
     xm_step = XM_RCONTS;
     dsp_xfunc(29, 34);
     }
  else if (xm_step == XM_RCONTS)
     {
     xm_step = XM_RCONT;
     dsp_xfunc(24, 29);
     }
  else if (xm_step == ZM_REJ)
     {
     dsp_str(16,3,s_yes);
     xm_step = ZM_REJS;
     }
  else if (xm_step == ZM_REJS)
     {
     dsp_str(16,3,s_no);
     xm_step = ZM_REJ;
     }
  else if (mm_step == MM_CLRTTL)
     {
     dsp_str(16,3,s_yes);
     mm_step = MM_CLRTTLS;
     }
  else if (mm_step == MM_CLRTTLS)
     {
     dsp_str(16,3,s_no);
     mm_step = MM_CLRTTL;
     }
  else if (mm_step == MM_CLRGT)
     {
     dsp_str(16,3,s_yes);
     mm_step = MM_CLRGTS;
     }
  else if (mm_step == MM_CLRGTS)
     {
     dsp_str(16,3,s_no);
     mm_step = MM_CLRGT;
     }
  else {errmsg=E_KEY;ERR}
}

void x_xtime()
{
    if(dcnt || (ncnt > 3)) { errmsg = E_NUMOVER; ERR}
    if(mul_bit) {errmsg=E_KEY;ERR}
    mul_bit = 1;
    mul = nur;
    sdcnt1=dcnt;
    fdec_inx = 0;
    prn_fdec(sdcnt1,P_X);
    pop_menu(prt_buffer,'|');
    memset(prt_buffer,0x20,sizeof(prt_buffer));
    nur=0;
    dcnt=0;
    ncnt=0;
    kdec_bit=0;
    knur_bit=0;
}
