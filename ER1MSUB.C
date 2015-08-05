#include <stdio.h>
#include <er1io51.h>
#include <er1exmn.h>
#ifndef BCDBG
#include  <exs03.h>
#else                                  /* BCDBG */
#include  <exdbg.h>
#endif                                 /* BCDBG */

extern const UBYTE s_escode[18];
extern const UBYTE s_tinout[18];
extern const UBYTE s_inout[11];
extern const UBYTE s_apcash[15];
extern const UBYTE s_tablepd[10];
extern const UBYTE s_netpdamt[10];
extern const UBYTE s_tpdrate[11];
extern const UBYTE s_tpdamt[10];

/***************************************/
/***      external register mode     ***/
/***************************************/
extern void  r_dept();
extern void  r_plu();
extern void  r_tender();
extern void  r_subt();
/*extern void  r_etd();*/
/*extern void  r_open();*/
extern void  r_addck();
/*extern void  r_chktnd(char type);*/
/*extern void  r_clkopen();
extern void  r_clkclose();*/
extern void  r_conv();
extern void  r_xtime();
extern void  r_nosale();

extern void  r_rtn();
extern void  r_void();
extern void  r_cancel();
extern void  r_reissue();
extern void  r_tax();
/*extern void  r_level();*/
extern void  r_price();
extern void  r_per();
extern void  r_rapo();
extern void  r_menu();
extern void  r_dptsft();
extern void  r_misc();
extern void  r_scale();
extern void  r_tare();
extern void  help_s(); /* yoo0820 */
extern UBYTE *norm_str(UBYTE *, UBYTE);

/***************************************/
/***      external report mode       ***/
/***************************************/
extern void report();
extern void rep_dpt();
extern void rep_clk();
extern void x_plu();
extern void x_level();


extern void sep_prn();
extern void prn_gcpt(char type,char dec,char lcd_f);
extern void logo_nur(char type);
extern void mkline();
//PKR0624 extern void feeding();
extern void mkrandom(long value,char ofst,char st);
extern void wait_pover();
//PKR0624 extern void drawopn();
extern void delay();
extern void mkdeach(char type);
extern void lead0();
extern void mk_cprn(char cinx);
extern void des_prn();
extern void prn_clklog(UBYTE idx, UBYTE);
extern void mode_dsp();
extern void lcd_dsp(char clr_f);
extern void dsp_str(UBYTE, UBYTE, UBYTE *);
extern void start_prn();
extern void pmemcpy(unsigned char *dest, unsigned char *src, unsigned int len);
extern int  cnv_tm(int time);
extern void prn_clksub(UBYTE *buffer, int time1, UBYTE prn_f);
extern void fill_date(UBYTE *, char, long);
extern void sign_off(char type);

void  r_timeio();
void  r_timeiom();
void  r_pgup();
void  r_pgdn();

/*********************************************************/
/***    REG/X MODE KEY SERVICE                         ***/
/***       Roggy Park                                  ***/
/*********************************************************/
void ser_rvx(int ffunc)
{
  if(!ksub_bit && (ffunc == MISCMENU) )
	ffunc = SUBTOTAL;

  switch(ffunc) {
	case  MISCTND1 :
	case  MISCTND2:
	case  MISCTND3:
	case  MISCTND4:
	case  CASH     :
//            if((regstep >= RSTEP_TMIO1) && (regstep <= RSTEP_TMIO3))
            if(regstep == RSTEP_TMIO)
                {
                r_timeiom();
                break;
                }
	case  CHECK    : r_tender(); break;
//        case  CHARGE1  :
//       case  CHARGE2  : r_tender()  ;break;
	case  SUBTOTAL : r_subt()    ;break;
//        case  CHECKTND : r_chktnd(0)  ;break;
//	case  HELP     : help_s()    ;break;/* yoo0820 */
	case  XTIME    : r_xtime()   ;break;
	case  NOSALE   : r_nosale()  ;break;
	case  RETURN   : r_rtn()     ;break;
	case  VOID     : r_void()    ;break;
	case  CANCEL   : r_cancel()  ;break;
//	case  REISSUE  : r_reissue() ;break;
	case  TAX      : r_tax()     ;break;
//        case  PRICE    : r_price()   ;break;
	case  PER1     :
	case  PER2     :
	case  PER3     :
	case  PER4     : r_per()     ;break;
	case  MENU     : r_menu()    ;break;
	case  DEPT_SFT : r_dptsft()  ;break;
	case  MISCMENU : r_misc()    ;break;
	case  CONV1    :
	case  CONV2    :
	case  CONV3    :
	case  CONV4    : r_conv()    ;break;
    case  SCALE    : r_scale()   ;break;
    case  TARE     : r_tare()    ;break;
    case  TIMEIO   : r_timeio()  ;break;
    case  PAGEUP   : r_pgup()    ;break;
    case  PAGEDOWN : r_pgdn()    ;break;
	default        : err_bit=1; errmsg = E_KEY;break;
	}
/*
  if(tmio_flg > 3)
    tmio_flg -= 3;
  else
    tmio_flg = 0;
*/
  return;
}
/****************************************************************************/
/***    TAX FORM PRINT                                               ***/
/***********************************************************************/
void ttax_prn(long *tax_able,long *tax_amt)
{
  char ti;
  long tax_ttl=0;

  for (ti=0; ti<MAX_TAX; ti++,tax_able++,tax_amt++){
      if(!PRT_OPT.OPT10_4 && (vat_inp[ti] == 1)) continue;
      nur=*tax_able;
      if (nur != 0) {
         if (PRT_OPT.OPT10_1){
            sprintf(prt_buffer,s_tablepd,(int)ti+1);sep_prn();
            };
         if ((vat_inp[ti] == 1) && (vatbk_bit || (PRT_OPT.OPT10_3))) {
            nur=*tax_able - *tax_amt;
            sprintf(prt_buffer,s_netpdamt,(int)ti+1);sep_prn();
            };
         if (PRT_OPT.OPT10_2 && !(tax_table[ti].taxstat & 0x1)){
            sprintf(prt_buffer,s_tpdrate,ti+1);nur=tax_table[ti].taxrate;prn_gcpt(1,3,0);
            };
         if ((PRT_OPT.OPT9_2) || vatbk_bit || (PRT_OPT.OPT10_3)){
            if (PRT_OPT.OPT9_3) /* combined */
               tax_ttl+=*tax_amt;
            else{       /* itemized */
               nur=*tax_amt;
               if(tax_table[(int)ti].desc[0] == 0)
                   sprintf(prt_buffer,s_tpdamt,(int)ti+1);
               else
                   {
                   norm_str(tax_table[(int)ti].desc,12);
                   strcpy(prt_buffer,lcdbuf);
                   }
               sep_prn();
               };
            };
         };
     }
  if ((PRT_OPT.OPT9_2) || vatbk_bit || (PRT_OPT.OPT10_3)){
     if ((PRT_OPT.OPT9_3) && tax_ttl != 0){ nur=tax_ttl; logo_nur(21); };
     };
  return;
}
/**********************************************************/
/**                   OPEN DRAWER                        **/
/**********************************************************/
void open_drw()
{
  if (SYS_OPT.OPT12_3 || !train_flg){ drawopn();delay();};
  return;
}
/**********************************************************/
/***                FRONT DECIMAL PRINT                 ***/
/**********************************************************/
void prn_fdec(char dec,char type)
{
  int bb,cc;

  cc = 0;
  ionur=nur;
  if (ionur < 0) ionur=-ionur;

  mkdeach(0);
  ta=7;
  lead0();
  if (ta < dec) ta=dec;

  if(type == P_No) {
	for(bb=0; bb < dec; bb++) {
		if(eachbuf[bb]) break;
		}
	if(bb >= dec) cc = dec;
	}
  for (bb=ta;bb>=cc;bb--) {
	  prt_buffer[fdec_inx++]=eachbuf[bb]+'0';
	  if (bb == dec) prt_buffer[fdec_inx++]='.';
	  }
/* KLY */
  if (prt_buffer[fdec_inx-1] == '.') fdec_inx--;

  if (type == P_LB) {
     prt_buffer[fdec_inx++]=' ';
     prt_buffer[fdec_inx++]='l';
     prt_buffer[fdec_inx++]='b';
	 }
  else if (type == P_KG) {
     prt_buffer[fdec_inx++]=' ';
     prt_buffer[fdec_inx++]='k';
     prt_buffer[fdec_inx++]='g';
	 }
  else if (type == P_SLASH) {
     prt_buffer[fdec_inx++]='/';
	 }
  else if (type == P_FOR) {
     prt_buffer[fdec_inx++]='F';
     prt_buffer[fdec_inx++]='O';
     prt_buffer[fdec_inx++]='R';
	 }
  else if (type == P_No) {
	 prt_buffer[fdec_inx++]=' ';
	 prt_buffer[fdec_inx++]='I';
	 prt_buffer[fdec_inx++]='T';
	 prt_buffer[fdec_inx++]='E';
	 prt_buffer[fdec_inx++]='M';
	 prt_buffer[fdec_inx++]='S';
	 }
  else prt_buffer[fdec_inx++]='X';

  prt_buffer[fdec_inx]=0;  /*null*/
  return;
}

void tmio_sub()
{
    regstep = RSTEP_END;
    clr_lcd();
    mode_dsp();
    lcd_dsp(1);
}

void dsp_time(UBYTE x, UBYTE y, long date, int time)
{
    memset(lcdbuf, 0x20, MAX_CLM);
    lcdbuf[17] = 'M';
    if(time >= 1200)
        {
        if((time >= 1300) && (time < 2400))
            time -= 1200;
        lcdbuf[16] = 'P';
        }
    else
        lcdbuf[16] = 'A';
    lcdbuf[15] = (time % 10) + 0x30;
    time /= 10;
    lcdbuf[14] = (time % 10) + 0x30;
    time /= 10;
    lcdbuf[13] = ':';
    lcdbuf[12] = (time % 10) + 0x30;
    time /= 10;
    lcdbuf[11] = (time % 10) + 0x30;
    if(date)
        fill_date(lcdbuf, 0, date);
    dsp_str(x, y, lcdbuf);
}

void dsp_tmio(UBYTE idx)
{
    UBYTE i;

    clr_lcd();
    dsp_str(1,0,s_tinout);
    for(i=0;i<6;i++)
        {
        if(i+idx >= MAX_CIO)
            break;
        if(i & 0x01)
            dsp_str(0,i+1,"O");
        else
            dsp_str(0,i+1,"I");
        dsp_time(2,i+1,CLKIO[IO_CLK].D_LOG[i+idx],CLKIO[IO_CLK].T_LOG[i+idx]);
        }
    prn_clksub(lcdbuf, CLKIO[IO_CLK].W_TIME, 0);
    dsp_str(1,7,lcdbuf);
    clr_flg = 1;
}

void r_timeio()
{
    if (!(mode_id & RXMODE) || (regstep != RSTEP_END)) {errmsg = E_KEY; ERR}
    if (SYS_OPT.OPT2_5 && (mode_id != XMODE)) {errmsg = E_XONLY; ERR}
    clr_lcd();
    regstep = RSTEP_TMIO;
    dsp_str(1,0,s_tinout);
    dsp_str(1,3,s_escode);
    dsp_str(3,4,s_apcash);
}

int time_diff(int time1, int time2)
{
    int h1, h2, m1, m2;

    if(time1 > time2)
        time2 += 2400;
    h1 = time1 / 100;
    m1 = time1 % 100;
    h2 = time2 / 100;
    m2 = time2 % 100;

    if(m1 > m2)
        {
        m2 += 60;
        h2--;
        }
    h1 = h2 - h1;
    m1 = m2 - m1;

    return (h1 * 100 + m1);
}

int time_add(int time1, int time2)
{
    int h1, h2, m1, m2;

    h1 = time1 / 100;
    m1 = time1 % 100;
    h2 = time2 / 100;
    m2 = time2 % 100;

    h1 += h2;
    m1 += m2;
    if(m1 > 59)
        {
        m1 -= 60;
        h1++;
        }

    return (h1 * 100 + m1);
}

UBYTE save_tmio()
{
    int time1;

    rtc_read();
    if(CLKIO[IO_CLK].T_IDX == MAX_CIO)
        return 1;

    CLKIO[IO_CLK].T_LOG[CLKIO[IO_CLK].T_IDX] =
            rtcb_flg[2] + rtcb_flg[3] * 10 +
            rtcb_flg[4] * 100 + rtcb_flg[5] * 1000;
    CLKIO[IO_CLK].D_LOG[CLKIO[IO_CLK].T_IDX] =
            rtcb_flg[11] + rtcb_flg[12] * 10 +
            rtcb_flg[7] * 100 + rtcb_flg[8] * 1000;
    CLKIO[IO_CLK].D_LOG[CLKIO[IO_CLK].T_IDX] +=
            (long)rtcb_flg[9] * 10000 + (long)rtcb_flg[10] * 100000;
    if(CLKIO[IO_CLK].T_IDX & 0x01)
        {
        time1 = time_diff(CLKIO[IO_CLK].T_LOG[CLKIO[IO_CLK].T_IDX-1],
                    CLKIO[IO_CLK].T_LOG[CLKIO[IO_CLK].T_IDX]);
        CLKIO[IO_CLK].W_TIME = time_add(CLKIO[IO_CLK].W_TIME, time1);
        }
    CLKIO[IO_CLK].T_IDX++;

    return 0;
}

void r_pgup()
{
    if(tmio_flg == 2)
        {
        dsp_tmio(0);
        tmio_flg = 1;
        }
    else if(tmio_flg == 3)
        {
        dsp_tmio(6);
        tmio_flg = 2;
        }
}

void r_pgdn()
{
    if(tmio_flg == 1)
        {
        dsp_tmio(6);
        tmio_flg = 2;
        }
    else if(tmio_flg == 2)
        {
        dsp_tmio(12);
        tmio_flg = 3;
        }
}

void r_timeiom()
{
    UBYTE kk;

//    if(regstep == RSTEP_TMIO1)
        {
        for(kk=0; kk < MAX_CLERK; kk++) {
            if(CLERK_P[kk].secret == nur)
                break;
            }
        regstep = RSTEP_END;
        clr_flg = 1;
        if(!clerk) sign_off(2);
        if((kk >= MAX_CLERK) || !knur_bit)
            {
            err_bit=1;
            errmsg=E_CLKCODE;
            tmio_sub();
            return;
            }
        IO_CLK = kk;
        if(save_tmio() != 0)
            {
            err_bit=1;
            errmsg=E_TIMEIO;
            tmio_sub();
            return;
            }
        if(CLKIO[IO_CLK].T_IDX <= 6)
            {
            dsp_tmio(0);
            tmio_flg = 1;
            }
        else if(CLKIO[IO_CLK].T_IDX <= 12)
            {
            dsp_tmio(6);
            tmio_flg = 2;
            }
        else
            {
            dsp_tmio(12);
            tmio_flg = 3;
            }
        okbuf_bit = 0;
        notbuf_bit = 1;
        xoff_flg = 1;
        start_prn();
        if(CLKIO[IO_CLK].T_IDX & 0x01)
            prn_clklog(2, IO_CLK+1);
        else
            prn_clklog(3, IO_CLK+1);

        }
}
