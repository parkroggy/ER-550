#include <stdio.h>
#include <er1io51.h>
#include <er1exm.h>
#ifndef BCDBG
#include  <exs03.h>

extern void pkr_cpyc();
extern UBYTE fnt_tbll[5*0x60];
#else                                  /* BCDBG */
#include  <exdbg.h>
#include  <conio.h>

extern  S_CODE_MEM real_code;
extern void window_lcd(UBYTE);
#endif                                 /* BCDBG */

const UBYTE s_blanks[21]    = "                    ";
const UBYTE s_closed[7]     = "CLOSED";
const UBYTE s_sbtl[5]       = "SBTL";
const UBYTE s_clkshp[7]     = "CLERK#";
const UBYTE s_clkpd[10]     = "CLERK %d ";
const UBYTE s_deptpd[8]     = "DEPT.%d";
const UBYTE s_ldeptpd[15]   = "LINKED DEPT %d";
const UBYTE s_plupd[7]      = "PLU %d";
const UBYTE s_galcnt[8]     = "GAL CNT";
const UBYTE s_galamt[8]     = "GAL AMT";
const UBYTE s_ltrcnt[8]     = "LTR CNT";
const UBYTE s_ltramt[8]     = "LTR AMT";
const UBYTE s_eprice[12]    = "ENTER PRICE";
const UBYTE s_escode[18]    = "ENTER SECRET CODE";
const UBYTE s_tinout[18]    = "TIME CLOCK IN/OUT";
const UBYTE s_inout[11]     = "IN     OUT";
const UBYTE s_apcash[15]    = "AND PRESS CASH";
const UBYTE s_scanall[17]   = "CASH TO SCAN ALL";
const UBYTE s_sys[4]        = " Y ";
const UBYTE s_sns[4]        = " N ";
const UBYTE s_sya[4]        = " Y}";
const UBYTE s_sna[4]        = " N}";
const UBYTE s_larrow[2]     = "}";
const UBYTE s_recacc[18]    = "** REC ON ACCT **";
const UBYTE s_padout[15]    = "** PAID OUT **";
const UBYTE s_amount[7]     = "AMOUNT";
const UBYTE s_escsp[21]     = "ESC                 ";
const UBYTE s_warning[8]    = "WARNING";
const UBYTE s_pcleark[15]   = "PUSH CLEAR KEY";
const UBYTE s_tmodek[14]    = "TURN MODE KEY";
const UBYTE s_vmode[10]     = "VOID MODE";
const UBYTE s_smode[13]     = "SERVICE MODE";
const UBYTE s_rmode[14]     = "REGISTER MODE";
const UBYTE s_omode[9]      = "OFF MODE";
const UBYTE s_cnts[5]       = "CNT ";
const UBYTE s_qtys[5]       = "QTY ";
const UBYTE s_samt[11]      = "SALES AMT ";
const UBYTE s_srate[11]     = " SALE RATE";
const UBYTE s_srates[11]    = "SALE RATE ";
const UBYTE s_scnt[5]       = " QTY";
const UBYTE s_scnt2[7]      = " QTY @";
const UBYTE s_iclkno[21]    = "INPUT CLERK NUMBER :";
const UBYTE s_rclkno[20]    = "  1 - 20  < ENTER >";
const UBYTE s_grttl[13]     = "GRAND TOTAL ";
const UBYTE s_ejreset[25]   = "ELECTRONIC JOURNAL RESET";
const UBYTE s_ttlreset[17]  = "ALL TOTALS RESET";
const UBYTE s_gtreset[18]   = "GRAND TOTAL RESET";
const UBYTE s_sejs[27]      = "*** ELECTRONIC JOURNAL ***";
const UBYTE s_gts[4]        = "GT ";
const UBYTE s_ttlcnt[11]    = "TOTAL CNT ";
const UBYTE s_ttlamt[11]    = "TOTAL AMT ";
const UBYTE s_ttls[7]       = "TOTAL ";
const UBYTE s_ttblp[21]     = "  TAX TABLE PROG.   ";
const UBYTE s_ttbls[21]     = " TAX  SALE AMT RANGE";
const UBYTE s_ttblsp[23]    = "TAX     SALE AMT RANGE";
const UBYTE s_space[2]      = " ";
const UBYTE s_pfkey[21]     = "PUSH FUNCTION KEY TO";
const UBYTE s_fkscan[19]    = " FUNCTION KEY SCAN";
const UBYTE s_bescan[12]    = "BE SCANNED.";
const UBYTE s_fkpgm[21]     = "FUNCTION KEY PROGRAM";
const UBYTE s_bepgm[15]     = "BE PROGRAMMED.";
const UBYTE s_allscan[13]   = "ALL PLU SCAN";
const UBYTE s_adptscan[15]  = "ALL DEPT. SCAN";
const UBYTE s_aclkscan[15]  = "ALL CLERK SCAN";
const UBYTE s_taxpd[7]      = "TAX %d";
const UBYTE s_tablepd[10]   = "TAXABLE%d";
const UBYTE s_netpdamt[10]  = "NET%d AMT";
const UBYTE s_tpdrate[11]   = "TAX%d RATE";
const UBYTE s_tpdamt[10]    = "TAX%d AMT";
const UBYTE s_trainmd[21]   = " *** TRAIN  MODE ***";
const UBYTE s_bgalamt[11]   = " <GAL> AMT";
const UBYTE s_bltramt[11]   = " <LTR> AMT";
const UBYTE s_grppd[8]      = "GROUP%d";
const UBYTE s_tax[4]        = "TAX";
const UBYTE s_tworked[15]   = "TIME WORKED : ";
const UBYTE s_tsftpd[13]    = "TAX SHIFT %d";
const UBYTE s_tarepd[9]     = "TARE #%d";
const UBYTE s_8tmio[15]     = "8. TIME IN/OUT";
const UBYTE s_chrate[12]    = "CHANGE RATE";
const UBYTE s_date[5]       = "DATE";
const UBYTE s_xpdreport[12] = "X%d  REPORT";
const UBYTE s_xreport[13]   = "X    REPORT ";
const UBYTE s_x2report[13]  = "X2   REPORT ";
const UBYTE s_timepd[13]    = "TIME : %d:00";
const UBYTE s_daypd[9]      = "DAY : %d";
const UBYTE s_ttlwork[15]   = "TOTAL WORKED: ";
const UBYTE s_tmoutss[22]   = " TIME OUT:           ";
const UBYTE s_tminss[22]    = " TIME IN:            ";
const UBYTE s_cashind[11]   = "CASH-IN-D ";
const UBYTE s_chind[12]     = "CHECK-IN-D ";
const UBYTE s_ipamt[11]     = "INPUT AMT ";
const UBYTE s_dwrttl[11]    = "DRAWER TTL";
const UBYTE s_diff[11]      = "DIFFERENCE";
const UBYTE s_rctps[21]     = " *** RECEIPT %s *** ";
const UBYTE s_on[3]         = "ON";
const UBYTE s_off[4]        = "OFF";
const UBYTE s_regprt[27]    = " # REGISTER PRINTING %s # ";
const UBYTE s_yes[4]        = "YES";
const UBYTE s_no[4]         = "NO ";
const UBYTE logo_flg[7][4]={"SUN","MON","TUE","WED","THU","FRI","SAT"};

const UBYTE s_star[21]      = "********************";

//PKR0624 extern void clr_lcd();
//PKR0624 extern void pkr_cpy();
//PKR0624 extern void feeding();
extern void des_prn();
//PKR0624 extern void drawopn();
//PKR0624 extern void endclr();
//PKR0624 extern void inidtx();
extern void ini_outdtx();
//PKR0624 extern void initseq();
extern void logo_nur(char type);
extern void mkline();
extern void make_desc(char *temps,char max);
extern void mk_lprn(int iinx);
//PKR0624 extern void outdtx();
//PKR0624 extern void prn();
extern long round_func(char sys_no,long value,char frac);
extern void wait_pover();
extern void desc2pbuf();
extern void mkstar();
extern void menu_man();
extern void menu_prn();
extern void menu_dsp();
extern void menu_rst();
extern void sign_off(char type);
extern void dsp_soff();
extern void make_time(UBYTE *, int);
extern void make_date(UBYTE *, long);
extern void prn_fdec(char dec,char type);

void mk_lline(unsigned char *rbuf,UBYTE x,int end);
signed char kp_prt(UBYTE *sendptr,UWORD len);
void fill_ch(UBYTE *buf, UBYTE ch);

/**********************************************************/
/***      MAKE DISPLAY DEPT PLU REPEAT & FUNC CODE      ***/
/**********************************************************/

void pmemcpy(unsigned char *dest, unsigned char *src, unsigned int len)
{
#ifndef BCDBG
    mem_dest = dest;
    mem_src = src;
    mem_len = len;
    pkr_cpy();
#else                                  /* BCDBG */
    memcpy(dest, src, len);
#endif                                 /* BCDBG */
}

void cmemcpy(unsigned char *dest, unsigned char *src, UBYTE len)
{
#ifndef BCDBG
    mem_dest = dest;
    mem_src = src;
    mem_len = (unsigned int)len;
    pkr_cpyc();
#else                                  /* BCDBG */
    memcpy(dest, src, len);
#endif                                 /* BCDBG */
}

void liq_cpy()
{
    char i;

    if(flg_key_pend >= MAX_KEYBUF - 6)
        return;
    if(flg_key_pend)
        {
    	for(i=flg_key_pend;i>0;i--)
            flg_key_buf[i+5] = flg_key_buf[i];
        }
    flg_key_buf[1] = 0x02;
    flg_key_buf[2] = comm_buff[2];
    flg_key_buf[3] = comm_buff[1];
    flg_key_buf[4] = comm_buff[0];
    flg_key_buf[5] = 0xee;
    flg_key_pend += 5;
}

void l2c(long no, unsigned char *buf, UBYTE pos)
{
    unsigned char ltmp[12];
    int i=0, j, sign=0;

    if((no == 0) && !pos)
        {
        buf[0] = 0x30;
        buf[1] = 0;
        return;
        }
    else if(no < 0)
        {
        no = -no;
        sign = 1;
        }

    while(no > 0)
        {
        if((i == pos) && (pos != 0))
            ltmp[i++] = '.';
        ltmp[i++] = (no % 10) + 0x30;
        no /= 10;
        }
    if((pos != 0) && (i <= pos))
        {
        for(;i<pos;)
            ltmp[i++] = '0';
        ltmp[i++] = '.';
        ltmp[i++] = '0';
        }
    if(sign == 1)
        ltmp[i++] = '-';

    for(j=0;j<i;j++)
        {
        buf[j] = ltmp[i-j-1];
        }
    buf[j] = 0;
}
void sv_str(UBYTE x, UBYTE y, unsigned char *str)
{
    UBYTE ch;

    if(y > MAX_LINE-1)
        return;
    while(1)
        {
        ch = *str;
        if((ch == 0) || (x >= MAX_CLM))
            break;
        dsp_buf[y][x] = *str;
    x++;
        str++;
        }
}
#ifndef BCDBG
void dsp_str(UBYTE x, UBYTE y, unsigned char *str)
{
    UBYTE ch;

    if(y > MAX_LINE-1)
        return;
    lcd_x = y;
    while(1)
        {
        ch = *str;
        if((ch == 0) || (x >= MAX_CLM))
            break;
        if(ch > 0x20)
            lcd_ch = (ch - 0x20) * 5;  /* PKR0710 */
        else
            lcd_ch = 0;
        if(x >= HALF_CLM)
            {
            lcd_y = (x - HALF_CLM) * 6;
            lcdwrt2();
            }
        else
            {
            lcd_y = x * 6 + 4;
            lcdwrt1();
            }
//        cmemcpy(&bit_buf[y][x*6+4],&fnt_tbll[lcd_ch],5);
        dsp_buf[y][x] = ch;
        x++;
        str++;
        }
}
#else                                  /* BCDBG */
void dsp_str(UBYTE x, UBYTE y, unsigned char *str)
{
    if(y > MAX_LINE-1)
        return;
    window_lcd(0);
    gotoxy(x+1, y+1);
    while(1)
        {
        if((*str == 0) || (x >= MAX_CLM))
            break;
        if((*str > 0x20) && (*str < 0x7c))
            putch(*str);
        else if(*str == 0x7c)
            putch('Û');
        else if(*str == 0x7d)
            putch('');
        else if(*str == 0x7e)
            putch('');
        else if(*str == 0x7f)
            putch('');
        else
            putch(*str);
        dsp_buf[y][x++] = *str;
        str++;
        }
    window(1,1,80,25);
    gotoxy(1,1);
    textattr(0x07);
}
#endif                                 /* BCDBG */
void sv_lcd()
{
    pmemcpy(dsp_erc[0],dsp_buf[0],MAX_LINE*(MAX_CLM+1));
    sdsp_y = dsp_y;
}

void sv_lcd1()
{
    if( (mode_id == PMODE) || ((mode_id & RVXMODE) && (regstep != RSTEP_END))) {
        if(!pop_lcd) {
            sv_lcd();
            pop_lcd = 1;
            }
    }
    else
        pop_lcd = 0;
}

void lcd_rec(char type)
{
    int i;

    if( ((type == 2) && (pop_lcd == 0)) || (mode_id == OMODE) )
        return;

    pop_lcd = 0;

    if(type == 0)
        {
        for(i=0;i<MAX_LINE;i++)
            dsp_str(0,i,dsp_buf[i]);
        }
    else
        {
        for(i=0;i<MAX_LINE;i++)
            dsp_str(0,i,dsp_erc[i]);
        dsp_y = sdsp_y;
        }
}

void help_dsp()
{
    UBYTE i, buf[22];

    if(hpage_max == 0)
        {
        help_flg = 0;
        return;
        }
    dsp_str(0,7,s_escsp);
    for (i=0; i<7; i++)
        {
        cmemcpy(buf,code_mem->help_str[(help_stp+hpage_off)*7+i],21);  /* PKR0829 */
        dsp_str(0,i,buf);
        }
    if((hpage_max > 1) && (hpage_off < hpage_max-1))
        {
        buf[0] = 0x7e;
        buf[1] = 0;
        dsp_str(19,MAX_LINE - 1,buf);
        }
    if((hpage_max > 1) && (hpage_off > 0))
        {
        buf[0] = 0x7f;
        buf[1] = 0;
        dsp_str(19,1,buf);
        }
}

#if 0
UBYTE OPT10_1:1;        /* Electronic journal */
UBYTE OPT10_2:1;        /* Send only negative entries to E.J. */
UBYTE OPT10_3:1;        /* Send reports to E.J. */
UBYTE FILLER10:5;

UBYTE OPT11_1:1;        /* Prompt operator when E.J. is full */
UBYTE OPT11_2:1;        /* Stop operations when E.J. is full */

#define         EJ_NORMAL       0
#define         EJ_MINUS        1
#define         EJ_REPORT       2

#endif
void ej_prn()
{
    int i;

    if(SYS_OPT.OPT13_1 == 1) {
        prt_buffer[MAX_RJ] = '\n';
        fill_ch(prt_buffer,0x20);
        kp_prt(prt_buffer,MAX_RJ+1);
        prt_buffer[MAX_RJ] = 0x20;
        }


    while(1)
        {
        if(EJ_FLAG == EJ_NOPRT) break;
        if(!SYS_OPT.OPT10_1) break;
        if(mode_id & OPMMODE) break;
        if((mode_id == XMODE) && (EJ_FLAG == EJ_REPORT)) break;
        if(vd1_bit || vd2_bit)
            EJ_FLAG |= EJ_ECV;
        if(negat_bit)
            EJ_FLAG |= EJ_MINUS;

        if(rtn_bit ||(mode_id == VMODE))
            EJ_FLAG |= EJ_RET;

        if((EJ_FLAG == EJ_REPORT) && (!SYS_OPT.OPT10_3)) break;

        if(EJ_INDEX < MAX_EJLINE)
            {
            pmemcpy(EJ_BUF[EJ_INDEX], prt_buffer, MAX_RJ);
//970926            if(EJ_FLAG == EJ_REPORT)
                EJ_BUF[EJ_INDEX][MAX_RJ] = EJ_NORMAL;
            EJ_INDEX++;
            }
        else if(SYS_OPT.OPT11_1)
            {errmsg = E_EJFULLW; err_bit = 1;}
        else            //970925
            {
            EJ_INDEX = 0;
            EJ_FULLF = 1;
            pmemcpy(EJ_BUF[EJ_INDEX], prt_buffer, MAX_RJ);
//970926            if(EJ_FLAG == EJ_REPORT)
                EJ_BUF[EJ_INDEX][MAX_RJ] = EJ_NORMAL;
            EJ_INDEX++;
            }

        if(EJ_FLAG & EJ_END) {
            if(!(EJ_FLAG & EJ_MINUS) && SYS_OPT.OPT10_2) {
                 EJ_INDEX = EJ_TINX;
                 }
            else if(EJ_FLAG != EJ_REPORT) {
//970925                 for(i=EJ_TINX; i < EJ_INDEX; i++)
//                     EJ_BUF[i][MAX_RJ] = (UBYTE)EJ_FLAG;
                i = EJ_TINX;
                while(1)
                    {
                    if(i == EJ_INDEX)
                        break;
                    EJ_BUF[i][MAX_RJ] = (UBYTE)EJ_FLAG;
                    i++;
                    if(i > MAX_EJLINE)
                        i = 0;
                    }
                 }
            }

        break;
        }
    prn();
}

void scr_prt()
{
    int i;

    for(i=0;i<MAX_LINE;i++) {
        pmemcpy(prt_buffer,dsp_buf[i],MAX_CLM);
        prt_buffer[MAX_CLM] = 0;
        prn();
        }
}
void blk_prs()
{

    if(blink % BLK_PRD)
    {
    blink++;
    return;
    }

    if((blink/BLK_PRD) & 0x1)
        dsp_str(0,0,s_blanks);
    else
        dsp_str(7,0,s_warning);

    if(errmsg != E_MODE) {
        if((blink/BLK_PRD & 0x1) || opndwr_flg)
            dsp_str(0,7,s_blanks);
         else
            dsp_str(1,7,s_pcleark);
        }
    else  {
        if((blink/BLK_PRD) & 0x1)
            dsp_str(0,7,s_blanks);
        else {
            dsp_str(1,7,s_tmodek);
            }
      }
    blink++;
}

void pop_menu(unsigned char *msg, unsigned char ch)
{
    char    len,x;
    if(errmsg == E_BUZZER) ERR;

    len = strlen(msg);
    x = (MAX_CLM - len-4)/2;
    if(pop_lcd == 0) {
    sv_lcd();
    }
    else if( (pop_lcd == 1) && !modelcd && !pop_err)
    lcd_rec(1);
    pop_lcd = 1;
    if(ch == 0xff) {
    clr_lcd();
//        blk_prs();
    if(!errmsg) errmsg = E_GENERAL;
    x = (6 - ERR_TBL[errmsg-1].msg_no)/2 +1;
    for(len = 0; len < ERR_TBL[errmsg-1].msg_no; len++,x++)
        {
    cmemcpy(lcdbuf1,code_mem->ERRMSG[ERR_TBL[errmsg-1].offset+len],19);
    dsp_str(1,x,lcdbuf1);
    }
    }
    else {
    memset(lcdbuf1,ch,4 + len);
    lcdbuf1[4 + len] = 0;
    dsp_str(x, 3,lcdbuf1);
    dsp_str(x, 5,lcdbuf1);
    sprintf(lcdbuf1,"%c %s %c",ch,msg,ch);
    dsp_str(x, 4,lcdbuf1);
    }
}

int mk_dnum(long num, unsigned char *rmsg, char sym)
{
    int dec_pos,cnt,cnt1;
    int upamt,jat,sign;
    long orgamt1;

//    if(mode_id == PMODE)               /* PKR0709 */
//        {
//        dec_pos = 0;
//        upamt = 1;
//        }
//    else
        {
        switch(SYS_OPT.OPT18_1)
            {
            case 0 : dec_pos = 0; upamt = 1;
                    break;
            case 1 : dec_pos = 1; upamt = 10;
                    break;
            case 3 : dec_pos = 3; upamt = 1000;
                    break;
            default : dec_pos = 2; upamt = 100;
                    break;
            }
        }

    if(num < 0)
        orgamt1 = -num;
    else
        orgamt1 = num;

    jat = (int) (orgamt1 % upamt);

    sprintf(rmsg,"%d",jat);
    cnt = strlen(rmsg);

    if(sym) {
        sign = 1;
        if (iosign_bit)
            rmsg[0] = '-';
        else if (lgol_bit) {
            if(conv_bit)
                rmsg[0] = PRT_OPT.OPT13[convnk];
            else rmsg[0] = '@';
        }
        else if (lblk_bit) rmsg[0] = ' ';
        else if (lsharp_bit) rmsg[0] = '#';
        else sign = 0;
    }
    else {
        if(num < 0) {
            rmsg[0] = '-';
            sign = 1;
        }
        else
            sign = 0;
    }

    l2c(orgamt1 / upamt, &rmsg[sign],0);
    cnt1 = strlen(rmsg);

    if(dec_pos) {
        if(cnt == dec_pos)
            sprintf(&rmsg[cnt1],".%d",jat);
        else if((dec_pos - cnt) == 1)
            sprintf(&rmsg[cnt1],".0%d",jat);
        else
            sprintf(&rmsg[cnt1],".00%d",jat);
    }

    return(strlen(rmsg));
}

char passin_chk()
{
        if(((mode_id & RVMODE) && (!clerk || clk_kin || (regstep == RSTEP_TMIO))) ||
                ((mode_id & XMODE) && ((xm_step == XM_TRAIN) || (regstep == RSTEP_TMIO))))
                return(1);
        else
                return(0);
}
void lcd_dsp(char clr_f)
{
    int i,j;
    unsigned char buf[21], buf2[21];

    if(mode_id == OMODE) return;
    if((mode_id == XMODE) && (xm_step != XM_DECL) && (xm_step != XM_TRAIN) && !clrk_step && (regstep == RSTEP_END) &&
        !rtn_bit && !tare_flg && !scale_bit )
        return;
    if((mode_id == ZMODE) && !clrk_step)
        return;

    if(!clr_f)
#if 0
        {
        j = mk_dnum(0,buf2,0);
        }
    else
#endif
    {
    if(!kdec_bit) {
        i = SYS_OPT.OPT18_1;
        if( passin_chk() || (mode_id == PMODE) ) {
            SYS_OPT.OPT18_1 = 0;
            }
        j = mk_dnum(nur,buf2,0);
        SYS_OPT.OPT18_1 = i;
        }
    else
        {
        i = SYS_OPT.OPT18_1;
        if( passin_chk() )
            SYS_OPT.OPT18_1 = 0;
        else
            SYS_OPT.OPT18_1 = dcnt;
        j = mk_dnum(nur,buf2,0);
        SYS_OPT.OPT18_1 = i;
        }
    }
    if(mode_id == PMODE)               /* PKR0704 */
        {
        if(clr_f)
            j = mk_dnum(0,buf2,0);
        memset(buf, 0x20, 20);
        buf[sys_len+1] = 0;
        if(sys_type == TP_TIME)
            {
            make_time(buf2, (int)nur);
            j = 5;
            i = sys_mask+1;
            }
        if(sys_type == TP_DATE)
            {
            make_date(buf2, nur);
            j = 8;
            i = sys_mask+1;
            }
        else if((sys_type == TP_WORD) || (sys_type == TP_LONG))
            i = sys_mask+1;
        else
            i = MAX_CLM;
        dsp_str(i-2-sys_len,sys_lno,buf);
        dsp_str(i-j-1,sys_lno,buf2);
        }
    else
        {
        if(regstep != RSTEP_MENU1)
                dsp_str(0,MAX_LINE-1,s_blanks);
        if(!clr_f) {
            if( passin_chk() )
                { j = ncnt;
                memset(buf2,'*',ncnt);
                }
            dsp_str(MAX_CLM-j,MAX_LINE-1,buf2);
            }
        }
}

void chk_kpend()
{
    UBYTE i;

    if(scroll_pend)
        {
        for(i=0;i<MAX_LINE;i++)
            dsp_str(0,i,dsp_buf[i]);
        scroll_pend = 0;
        }
}

//#ifndef BCDBG
//void scroll()
//{
//    int i;
//
//    if(rep_disp || (regstep == RSTEP_RA) || (regstep == RSTEP_PO))
//        {
//        i = 1;
//        pmemcpy(&dsp_buf[1][0],&dsp_buf[2][0],(MAX_CLM+1)*5);
//        pmemcpy(&bit_buf[1][0],&bit_buf[2][0],128*5);
//        }
//    else
//        {
//        i = 0;
//        pmemcpy(&dsp_buf[0][0],&dsp_buf[1][0],(MAX_CLM+1)*5);
//        pmemcpy(&bit_buf[0][0],&bit_buf[1][0],128*5);
//        }
//    dsp_scr();
//}
//#else
void scroll()
{
    int i;

    if(rep_disp || (regstep == RSTEP_RA) || (regstep == RSTEP_PO))
        {
        i = 1;
        pmemcpy(&dsp_buf[1][0],&dsp_buf[2][0],(MAX_CLM+1)*5);
        }
    else
        {
        i = 0;
        pmemcpy(&dsp_buf[0][0],&dsp_buf[1][0],(MAX_CLM+1)*5);
        }

    if(flg_key_pend > 0)
        {
        scroll_pend = 1;
        return;
        }
    for(;i<MAX_LINE-2;i++)
        dsp_str(0,i,dsp_buf[i]);
}
//#endif

void dsp_line(UBYTE *str, UBYTE stay)
{
    UBYTE buf[MAX_CLM+1];
    int i, j, max_s;

    if (rep_disp == 1)
       max_s=6;
    else {
       if(stay)
            sv_put = (sv_put-1 + MAX_SV_LINE) % MAX_SV_LINE;
       else {
            sv_put %= MAX_SV_LINE;
            if(sv_put == sv_get)
            sv_get = (sv_get+1)%MAX_SV_LINE;
            if(sv_get == MAX_SV_LINE)
            sv_get = 0;
            }
       pmemcpy(lcd_save[sv_put],str,MAX_CLM);
       lcd_save[sv_put][MAX_CLM] = 0;
       sv_put++;

       max_s=5;
       }

    for(i=0,j=0;i<MAX_CLM;i++)
        {
        if(*str == 0)
            j = 1;
        if(j == 0)
            buf[i] = *str++;
        else
            buf[i] = 0x20;
        }
    buf[MAX_CLM] = 0;

    if(stay)
        {
        if(dsp_y > max_s)
            dsp_y = max_s;
        }
    else
        {
        if(dsp_y < max_s)
            dsp_y++;
        else
            {
            scroll();
            dsp_y = max_s;
            }
        }

    dsp_str(0, dsp_y, buf);
}

void dsp_rev(char index)
{
    UBYTE i,j;

    index = (index + MAX_SV_LINE) % MAX_SV_LINE;
    for(i=index,j=0; j < MAX_LINE-2;j++) {
        dsp_str(0,j,lcd_save[i]);
        i = (i+1) % MAX_SV_LINE;
        }
}

void dsp_menu()
{
    int i,j,k=0,l;
    unsigned char buf[22];
    unsigned char temp_menu;

    temp_menu = menu_no;
    if (mode_id == ZMODE) {
       if (rept_step == 1)
          menu_no += 8;
    }

    j = m_no;
    l = l_no;
    if(l_no > MAX_LINE - 1)
    {
        k=1;
        if(menu_st)
            {
#if 0
            j = m_no + l_no - MAX_LINE + 1;
#endif
            j = m_no + 7;
            l -= 7;
            k = 2;
            }
        }
//    clr_lcd();
    if(menu_no == MENU_CNO2)
        cmemcpy(buf,code_mem->title_str[MENU_CNO],21);
    else
        cmemcpy(buf,code_mem->title_str[menu_no],21);
    dsp_str(0,0,buf);
    for(i=0;(i<l) && (i<MAX_LINE - 1);i++)
        {
        cmemcpy(buf,code_mem->menu_str[i+j],21);
        dsp_str(0,i+1,buf);
        }
    for(;i<MAX_LINE-1;i++)
        dsp_str(0,i+1,s_blanks);

    if(k == 1)
        {
        buf[0] = 0x7e;
        buf[1] = 0;
        dsp_str(19,MAX_LINE - 1,buf);
        }
    else if(k == 2)
        {
        buf[0] = 0x7f;
        buf[1] = 0;
        dsp_str(19,1,buf);
        }
    menu_no = temp_menu;
}

void start_menu(UBYTE no)
{
    menu_no = no;
    pop_lcd = 0;
    sys_type = 0;
    switch(menu_no)
        {
        case MENU_PRINT:
            m_no = 17;
            l_no = 3;
            break;
        case MENU_DISPLAY:
            m_no = 17;
            l_no = 2;
            break;
        case MENU_MANAGER:
            m_no = 0;
            l_no = 6;
            break;
        case MENU_PRINT2:
            m_no = 6;
            if(mode_id == ZMODE)
                l_no = 10;
            else
                l_no = 11;
            break;
        case MENU_DISPLAY2:
            m_no = 6;
            l_no = 11;
            break;
        case MENU_RESET:
            m_no = 20;
#ifdef PCCOMM
            l_no = 4;
#else
            l_no = 3;
#endif
            break;
        case MENU_PTDPRN:
            menu_no = MENU_PRINT2;
            m_no = 6;
            l_no = 1;
            break;
        case MENU_PTDDSP:
            menu_no = MENU_DISPLAY2;
            m_no = 6;
            l_no = 1;
            break;
        case MENU_PGM:
            m_no = 24;
            l_no = 11;
            break;
        case MENU_PGM2:
            m_no = 35;
            l_no = 6;
            break;
        case MENU_PGMS:
            m_no = 24;
            l_no = 10;
            break;
        case MENU_MMODE:
            m_no = 41;
            l_no = 4;
            break;
        case MENU_MTEST:
            m_no = 45;
            l_no = 6;
            break;
        case MENU_EJ:
            m_no = 51;
            l_no = 10;
            break;
        case MENU_CNO2:
        case MENU_CNO:
            m_no = 61;
            l_no = 2;
            break;
        }
    menu_st = 0;
    dsp_menu();
}

void mode_line()
{
    unsigned char *buf,x,len;

    switch(mode_id)
    {
        case VMODE: buf = s_vmode;
                    break;
        case MMODE: buf = s_smode;
                    break;
        case PMODE:
        case ZMODE:
        case XMODE:
                    return;
        case RMODE: if(regstep != RSTEP_END)
                                return;
                    buf = s_rmode;
                    break;
        case OMODE: buf = s_omode;
            break;
    }

    len = strlen(buf);
    x = (MAX_CLM - len)/2;

    memset(lcdbuf,0x20,MAX_CLM);
    pmemcpy(lcdbuf+x,buf,len);
    lcdbuf[MAX_CLM] = 0;

    dsp_str(0,0,lcdbuf);
#if 0
    if( (clerk == 0) && (mode_id & RVMODE)) {
        pop_lcd = 2;
        pop_menu(s_closed,'|');
        pop_lcd = 0;
        }
#endif
}

void mode_dsp()
{
    unsigned char inhi_clr = 0;

    if(((regstep != RSTEP_END) || ((mode_id == modesave) && pfail_flg && !allramclr_bit)) && (mode_id & RVXMODE) ) {
        inhi_clr = 1;
    }

    if( (mode_id == OMODE) && !err_bit) {
        if(!offlcd && (regstep != RSTEP_END) && !menu_flg && !pop_lcd) {
            sv_lcd();
            pop_lcd = 1;
            }
        }

    if( (!err_bit && !inhi_clr) || (mode_id == OMODE) ){
        clr_lcd();
        }

    if( offlcd && (/* (mode_id & RVMODE) || */ ((regstep != RSTEP_END) && (mode_id & RVXMODE) )) ) {
        lcd_rec(1);
    modelcd = 0;
    }
    if(mode_id == OMODE) {
    if(!err_bit)
           offlcd = 1;
    }
    else offlcd = 0;
    mode_line();
}

UBYTE *norm_str(UBYTE *src, UBYTE len)
{
    pmemcpy(lcdbuf,src,len);

    lcdbuf[len] = 0;
    return(lcdbuf);
}

UBYTE *get_fdesc(unsigned int kfunc)
{
    norm_str(FUNCKEY[kfunc-CASH].DESC,12);
    return(lcdbuf);
}

void prn_sfd(unsigned int kfunc, unsigned char ch)
{
    char len;

    get_fdesc(kfunc);
    len = strlen(lcdbuf);
    strcpy(prt_buffer,lcdbuf);
    memset(prt_buffer+len+1,ch,MAX_RJ-len);
    des_prn();
}

void func_menu()
{
    UBYTE msg[8][17], temp[2];
    unsigned char i,j;

    clr_lcd();
//    mode_dsp();
//    lcd_dsp(1);

    if(menu_flg == 1) {
        for(j=0; j < 4;j++)
            sprintf(msg[j],"%d. %s", j+1,get_fdesc(PER1+j));
        sprintf(msg[4],"5. %s", get_fdesc(RA));
        sprintf(msg[5],"6. %s", get_fdesc(PO));
        sprintf(msg[6],"7. %s", get_fdesc(RETURN));
        sprintf(msg[7],s_8tmio);
        dsp_str(19,7,"~");
        j =8;
        }
    else if(menu_flg == 2) {
        sprintf(msg[0],"9. %s", get_fdesc(SCALE));
        sprintf(msg[1],"00. TARE#");
        temp[0] = 0x7f;
        temp[1] = 0;
        dsp_str(19,0,temp);
        j=2;
        }
    else  {
        for(j=0; j < 4;j++)
            sprintf(msg[j],"%d. %s", j+1,get_fdesc(MISCTND1+j));
        for(j=4; j < 8;j++)
            sprintf(msg[j],"%d. %s", j+1,get_fdesc(CONV1+j-4));
        j =8;
        }
    for(i=0; i < j ; i++) {
    dsp_str(0,i,msg[i]);
    }

//    dsp_str(0,6,"SELECT Number");
}

void mode_chg()
{
    if(regstep == RSTEP_END)
        clk_kin = 0;
    if(!(mode_id & XZMODE))
        flg_concid = 0;
    if(mode_id != PMODE)
        {
        pfkey_bit = 0;
        paddr = 0;
        }
    if((regstep == RSTEP_END) && !(mode_id & RVMODE))
        initseq();
    if(mode_id != MMODE)
        mm_step = 0;
    switch(mode_id)
    {
        case OMODE:
        case RMODE:
        case VMODE:
            mode_dsp();
            break;
        case XMODE:
            if(regstep != RSTEP_END)
                mode_dsp();
            else {
                start_menu(MENU_MANAGER);
                rept_step = page_stat = clrk_step = 0;
                xm_step = 0;
            }
            break;
        case ZMODE:
            rept_step = page_stat = 0;
            start_menu(MENU_RESET);
            break;
        case PMODE:
            start_menu(MENU_PGM);
            break;
        case MMODE:
            start_menu(MENU_MMODE);
            break;
        }
#if 0
    if(last_mode == PMODE)
        {
        pgm_end();
        }
#endif
    last_mode = mode_id;
}

/**********************************************************/
void mkdsp()
{
 int ia;

 ia=0;
 if (!pluon_bit) ia=func+1;                    /* func code make */
 else if (price_flg == 1) ia=pcode+1;
 else ia=plu[pcode].link_dept;

 if (price_flg == 1) flg_dis_txtmp[7]=D_BLANK;
 flg_dis_txtmp[8]/*=flg_dis_txtmp[9]*/=D_BLANK;

 if (ia <= 9) flg_dis_txtmp[9]= ia;      /* 1 place */
 else if (ia <= 99) {   /* 2 place */
    flg_dis_txtmp[8]= ia % 10 ;
    flg_dis_txtmp[9]= ia/10;
    }
 else {                 /* 3 place */
    flg_dis_txtmp[7]= ia % 10;
    flg_dis_txtmp[8]= ia/10 % 10;
    flg_dis_txtmp[9]= ia/100;
    };

 if (price_flg == 0 && (mode_id & RVXMODE) && (regstep != RSTEP_END) && (!void_bit)
//      && (rpt_flg || (mul_bit && mul != 1) || (spl_bit && SYS_OPT.OPT24_1)) )
      && (rpt_flg || (mul_bit && mul != 1) || spl_bit) )
    flg_dis_txtmp[7]= rcnt%10;     /* repeat count */
 outdtx();
 return;
}

/**********************************************************/
void mk_ptxpnt(char type)
{
 *(ptxpnt++) = (char)((ionur%10)+('0'*type));
 ionur /= 10;
 return;
}

/**********************************************************/
/***                 MAKE EACH NUMERIC FORM             ***/
/**********************************************************/
void mkdeach(char type)
{
 char a;

 for (a=0;a<=19;a++) eachbuf[a]=0;
 ptxpnt=&eachbuf[0];
 while (ionur) {
    mk_ptxpnt(type);
    if (ptxpnt > &eachbuf[18]) break;
    }
 return;
}
/**********************************************************/
/***                 MAKE DISPLAY NUMERIC               ***/
/**********************************************************/
void ionur_sign()
{
 ionur=nur;
 if (ionur < 0) { iosign_bit=1;ionur = -ionur;};
 return;
}

void mkdnur(char inf)
{
 char bb,pt;

 if(clk_kin) return;

 if (!vd1_bit && !vd2_bit) void_bit=0;
 if (kdec_bit && (inf == 0))
    for (bb=0;bb<=9;bb++) flg_dis_txtmp[bb]=decbuf[bb];
 else {

    inidtx();

    ptxpnt=&flg_dis_txtmp[0];

    ionur_sign();
    while(ionur){
///////////////////////////////////////////////////////
//         mk_ptxpnt(0);
         *(ptxpnt++) = (char)(ionur%10);
         ionur /= 10;
///////////////////////////////////////////////////////
         }

    pt=SYS_OPT.OPT18_1;
    if (inf != 0) pt=inf;
    while(ptxpnt <= &flg_dis_txtmp[pt]) *(ptxpnt++)=0;

    if (iosign_bit) *(ptxpnt++)=D_MINUS;
    iosign_bit=0;
    };

 if (inf == 0) outdtx();
// outdtx();
 return;
}

/**********************************************************/
/**       RTC TIME DATE WRITE & PRINTING SUBROUTINE      **/
/**********************************************************/
void lead0()
{
 for (;ta>=0 && eachbuf[ta]==0;ta--);
 return;
}
/******************************************************************************/
void prn_gcpt(char type,char dec,char lcd_f)
{
 char d,l;
 int  bb;
 unsigned char temp[15];

 sprintf(lcdbuf," %s",prt_buffer);

 iosign_bit=0;
 ionur_sign();

 mkdeach(0);
 ta=9;
 lead0();
 if (ta < dec) ta=dec;

 d=MAX_RJ-1; /* =20 */
 l = 13;
 temp[14] = 0;
 if (type == 1) {
    prt_buffer[d--]='%';
    temp[l--] = '%';
    }

 for (bb=0;bb<=ta;bb++) {
     if (bb == dec && dec != 0) {
         prt_buffer[d--]=temp[l--]='.';
         }
     prt_buffer[d--]=temp[l--]=eachbuf[bb]+'0';
     }
 if (lsharp_bit) {
    prt_buffer[d--]=temp[l--]='#';
    }
 else if (iosign_bit) {
    prt_buffer[d--]=temp[l--]='-';
    }
 else if (lgol_bit) {
    prt_buffer[d--]=temp[l--]='@';
    }
 if((lcd_f == 1) && (vd1_bit == 0)) {
    mk_lline(&temp[l+1],0,MAX_CLM);
    dsp_line(lcdbuf,0);
    }
 if(lcd_f == 2)
    {
    mk_lline(&temp[l+1],0,MAX_CLM);
    cnbclr();
    }
 else
    des_prn();
 etc_id=0;
 return;
}
/*****************************************************************************/
/***                       CALCULATION FUNCTION                            ***/
/*****************************************************************************/
void pow10(char ii)
{
  char  j;

  pow_val=1;
  for (j=0; j<ii; j++) pow_val*=10;
  return;
}

/************************************************************************/
/***            long1 * long2_1.long2_2 = mvalue.mvalue2              ***/
/************************************************************************/
void cal_multi(long long1, char d1, long long2_1, long long2_2, char d2)
{
  float fl=0;
  long  value1[15];
  char  eachval[15];
  long  ten1, ten2;
  char  i, j, eachlen;

  cal_nega=0;
  mvalue=0;
  mvalue2=0;

  if (long1 < 0){ cal_nega++; long1=-long1; };
  if (long2_1 < 0){ cal_nega++; long2_1=-long2_1; };
  if (long2_2 < 0){ cal_nega++; long2_2=-long2_2; };

  for (j=0; j<d2; j++){
      eachval[j]=long2_2%10;
      long2_2/=10;
      }
  for (eachlen=j; long2_1!=0; eachlen++){
      eachval[eachlen]=long2_1%10;
      long2_1/=10;
      }

  pow10(d1+d2);
  ten2=pow_val;
  ten1=1;
  for (j=0; j<eachlen; j++){
      value1[j]=long1*eachval[j];
      mvalue2+=((value1[j]%ten2)*ten1);
      value1[j]/=ten2;
      if (ten2 == 1) break;
      ten2/=10;
      ten1*=10;
      }
  for (i=j+1; i<eachlen; i++){
      ten2*=10;
      value1[i]=long1*eachval[i];
      value1[i]*=ten2;
      }

  for (j=0; j<eachlen; j++){
      fl+=value1[j];
      if (fl > 50000000) { errmsg = E_AMTOVER; ERR}
      mvalue+=value1[j];
      }

  mvalue+=mvalue2/pow_val; /* carrier */
  mvalue2%=pow_val;

  /* for round_func */
  if (pow_val == 1) moksub[0]=0; /* no decimal */
  else moksub[0]=mvalue2/(pow_val/10);

  if (cal_nega == 1) {
     if (mvalue != 0) mvalue=-mvalue;
     else mvalue2=-mvalue2;
     };

  return;
}

/***************************************************************************/
/***  long1_1.long1_2 / long2 = mvalue.moksub[0]moksub[1]....moksub[10]  ***/
/***************************************************************************/
void cal_divi(long long1_1, long long1_2, char d1, long long2, char d2)
{
  char  j;
  char  namsub[25];
  long  nam;
  float fl;
  char  nega=0;

  /* more think : sign */
  if (long1_1 < 0){ nega++; long1_1=-long1_1; };
  if (long2 < 0){ nega++; long2=-long2; };

  mvalue=long1_1/long2;
  nam=long1_1%long2;

  for (j=0; j<d1; j++){
      namsub[d1-(j+1)]=long1_2%10;
      long1_2/=10;
      }
  for (j=d1; j<25; j++) namsub[j]=0;

  for (j=0; j<11+d2; j++){
      nam=(nam*10) + namsub[j];
      moksub[j]=nam/long2;
      nam%=long2;
      }

  fl=(float)mvalue;
  for (j=0; j<d2; j++){
      fl=(fl*10) + (float)moksub[j];
      if (fl > 500000000) { errmsg = E_AMTOVER; ERR}
      mvalue=(mvalue*10) + moksub[j];
      }

  for (j=0; j<11; j++) moksub[j]=moksub[d2+j];

  cal_nega=0;
  if (nega == 1){
     cal_nega=1;
     mvalue=-mvalue;
     };
  return;
}

/******************************************************************************/
/** long1 - mvalue.moksub[0]....moksub[10] = mvalue.moksub[0]....moksub[10]  **/
/******************************************************************************/
void cal_sub(long long1)
{
  int  cc=10;
  char ten=10;

  while (1){
        moksub[cc]=ten-moksub[cc];
        if (moksub[cc] == 10){
           moksub[cc]=0;
           ten=10;
           }
        else ten=9;
        if (cc == 0) break;
        cc--;
        }
  if (ten == 10){
     moksub[0]=0;
     mvalue=long1-mvalue;
     }
  else{
     if (long1 < 0) mvalue=long1-mvalue+1;
     else mvalue=long1-mvalue-1;
     };
  return;
}

/**********************************************************/
/**     RTC TIME AND DATE READ & PRINTING SUBROUTINE     **/
/**********************************************************/
void fill_time(char ss)
{
    unsigned char time,pm_f;

    time = rtcb_flg[5] * 10 + rtcb_flg[4];

    if(time > 11 ) pm_f = 1;
    else pm_f = 0;
    if(time > 12) {
        time -= 12;
        rtcb_flg[5] = time / 10;
        rtcb_flg[4] = time % 10;
        }
    if(rtcb_flg[5])
            prt_buffer[ss++]=rtcb_flg[5]+'0';
    else
            prt_buffer[ss++]=0x20;
    prt_buffer[ss++]=rtcb_flg[4]+'0';
    prt_buffer[ss++]=':';
    prt_buffer[ss++]=rtcb_flg[3]+'0';
    prt_buffer[ss++]=rtcb_flg[2]+'0';
    if(pm_f) prt_buffer[ss++] = 'P';
    else prt_buffer[ss++] = 'A';
    prt_buffer[ss] = 'M';
}

void time_prn()
{
    rtc_read();           /* rtc read target routine */
    prt_buffer[0]='T';
    prt_buffer[1]='I';
    prt_buffer[2]='M';
    prt_buffer[3]='E';

    fill_time(5);
//    if (mode_id == MMODE) {
//        prt_buffer[10]=':';
//        prt_buffer[11]=rtcb_flg[1]+'0';
//        prt_buffer[12]=rtcb_flg[0]+'0';
//        };
}

void fill_date(UBYTE *buffer, char ss, long date)
{
 char st,y[2];

 if(!date)
    rtc_read();    /* ddmmyy */
 else
    {
    rtcb_flg[11] = date % 10;          /* Y1 */
    date /= 10;
    rtcb_flg[12] = date % 10;          /* Y0 */
    date /= 10;
    rtcb_flg[7] = date % 10;           /* D1 */
    date /= 10;
    rtcb_flg[8] = date % 10;           /* D0 */
    date /= 10;
    rtcb_flg[9] = date % 10;           /* M1 */
    date /= 10;
    rtcb_flg[10] = date % 10;          /* M0 */
    }

 st = rtcb_flg[12]*10 + rtcb_flg[11];
 if(st < 96) {
        y[0] = '2';
        y[1] = '0';
        }
 else {
    y[0] = '1';
    y[1] = '9';
    }
  st = ss;

 buffer[st++]=rtcb_flg[10]+'0';            /*    56   89   23 */
 buffer[st++]=rtcb_flg[9]+'0';             /*  0 mm - dd - yy */
 buffer[st++]='/';
 buffer[st++]=rtcb_flg[8]+'0';             /*  1 dd - mm - yy */
 buffer[st++]=rtcb_flg[7]+'0';            /*  2 yy - mm - dd */
 buffer[st++]='/';
 buffer[st++]=y[0];           /*    21   09   87 */
 buffer[st++]=y[1];
 buffer[st++]=rtcb_flg[12]+'0';           /*    21   09   87 */
 buffer[st++]=rtcb_flg[11]+'0';
 if (SYS_OPT.OPT17_1 == 1) {                  /* dd-mm-yy */
    st = ss;
    buffer[st++]=rtcb_flg[8]+'0';
    buffer[st++]=rtcb_flg[7]+'0';
    st++;
    buffer[st++]=rtcb_flg[10]+'0';
    buffer[st++]=rtcb_flg[9]+'0';
    };
 if (SYS_OPT.OPT17_1 == 2) {                  /* yy-mm-dd */
    st = ss;
    buffer[st++]=y[0];           /*    21   09   87 */
    buffer[st++]=y[1];
    buffer[st++]=rtcb_flg[12]+'0';
    buffer[st++]=rtcb_flg[11]+'0';
    buffer[st++]='/';
    buffer[st++]=rtcb_flg[10]+'0';
    buffer[st++]=rtcb_flg[9]+'0';
    buffer[st++]='/';
    buffer[st++]=rtcb_flg[8]+'0';
    buffer[st++]=rtcb_flg[7]+'0';
    };
 return;
}
#if 0
void fill_date(char ss,char point)
{
 rtc_read();    /* ddmmyy */

 prt_buffer[ss++]=rtcb_flg[10]+'0';            /*    56   89   23 */
 prt_buffer[ss++]=rtcb_flg[9]+'0';             /*  0 mm - dd - yy */
 if (point) prt_buffer[ss++]='.';
 prt_buffer[ss++]=rtcb_flg[8]+'0';             /*  1 dd - mm - yy */
 prt_buffer[ss++]=rtcb_flg[7]+'0';            /*  2 yy - mm - dd */
 if (point) prt_buffer[ss++]='.';
 prt_buffer[ss++]=0x27;
 prt_buffer[ss++]=rtcb_flg[12]+'0';           /*    21   09   87 */
 prt_buffer[ss++]=rtcb_flg[11]+'0';
}
#endif
/*--------------------------------------------------------*/
void date_prn()
{
 char i;

 pmemcpy(prt_buffer, s_date, 4);

 fill_date(prt_buffer, 6, 0);

 i=rtcb_flg[6];
 prt_buffer[23]=logo_flg[i][0];
 prt_buffer[24]=logo_flg[i][1];
 prt_buffer[25]=logo_flg[i][2];

 return;
}
/**********************************************************/
/**                    MEMORY UPDATE                     **/
/**********************************************************/
void adcntl(int dd)
{
  if (train_flg){
     if (dd == F_NETSALE) { dd=trainttl;
        rep[dd].cnt +=cntint;
        rep[dd].total +=result;
        }
     return;
     };

  rep[dd].cnt +=cntint;
  rep[dd].total +=result;
  if(rep[dd].total >= 1000000000)
    rep[dd].total -= 1000000000;

  if ((regstep != RSTEP_RA) && (regstep != RSTEP_PO) && (regstep == RSTEP_STEND || func == CASH || func == CHECK ||
      ((func >= MISCTND1) && (func <= MISCTND4)) ||
      /* func == CHARGE1 || func == CHARGE2 || */ cantime > 30)) return; /* CANCEL CAL */

  cancl[canclcnt].roder=dd;
  cancl[canclcnt].rcnt +=cntint;
  cancl[canclcnt].rtotl +=result;
  canclcnt +=1;
  return;
}

/**********************************************************/
/**         DIRECT PRINT NUMERIC INPUT SUBROUTINE        **/
/**********************************************************/
void mkrandom(long value,char ofst,char st)
{
 int aa;

 for (aa=0;aa<=st;aa++) {
     prt_buffer[ofst-aa]=(char)(value % 10) + '0';
     value /=10;
     }
 return;
}
/****************************************************************************/
/***                    EXEMPT TAX EXTRATE                                ***/
/****************************************************************************/
void taxexm_set(int kfunc)
{
    if( kfunc != -1) {
        if (tax1_bit) taxexm_flg |=0x01;
        if (tax2_bit) taxexm_flg |=0x02;
        if (tax3_bit) taxexm_flg |=0x04;
        if (tax4_bit) taxexm_flg |=0x08;
        }

    if((kfunc == CASH) || (kfunc == CHECK) ) {
        if(FUNCKEY[kfunc-CASH].KEY_ST.CASH_KEY.EXMT_TAX1) taxexm_flg |= 1;
        if(FUNCKEY[kfunc-CASH].KEY_ST.CASH_KEY.EXMT_TAX2) taxexm_flg |= 2;
        if(FUNCKEY[kfunc-CASH].KEY_ST.CASH_KEY.EXMT_TAX3) taxexm_flg |= 4;
        if(FUNCKEY[kfunc-CASH].KEY_ST.CASH_KEY.EXMT_TAX4) taxexm_flg |= 8;
        }
    else if((kfunc >= MISCTND1) && (kfunc <= MISCTND4) ) {
        if(FUNCKEY[kfunc-CASH].KEY_ST.MISC_KEY.EXMT_TAX1) taxexm_flg |= 1;
        if(FUNCKEY[kfunc-CASH].KEY_ST.MISC_KEY.EXMT_TAX2) taxexm_flg |= 2;
        if(FUNCKEY[kfunc-CASH].KEY_ST.MISC_KEY.EXMT_TAX3) taxexm_flg |= 4;
        if(FUNCKEY[kfunc-CASH].KEY_ST.MISC_KEY.EXMT_TAX4) taxexm_flg |= 8;
        }
}
long tax_sum(int kfunc,long *tax_amt)
{
    long t_sum=0;

    taxexm_flg=0;
    taxexm_set(kfunc);

    if (taxexm_flg & 0x08) {
        *(&tax_amt[TAX1]) -=mix_taxamt[TAX1];
        *(&tax_amt[TAX2]) -=mix_taxamt[TAX2];
        *(&tax_amt[TAX3]) -=mix_taxamt[TAX3];
        };

    if (vat_inp[0] != 1 && !(taxexm_flg & 0x01)) t_sum +=(*(&tax_amt[TAX1]));
    if (vat_inp[1] != 1 && !(taxexm_flg & 0x02)) t_sum +=(*(&tax_amt[TAX2]));
    if (vat_inp[2] != 1 && !(taxexm_flg & 0x04)) t_sum +=(*(&tax_amt[TAX3]));
    if (vat_inp[3] != 1 && !(taxexm_flg & 0x08)) t_sum +=(*(&tax_amt[TAX4]));
    return(t_sum);
}
/****************************************************************************/
/***                         TAX CALCULATION                              ***/
/****************************************************************************/
long tax_ext(char tx,long amount)
{
    long taxamt,temp;
    char ca,sign=0;
    long modd;
    char tax_kind;

    if (amount == 0) return(0);
    if (amount < 0) {amount= -amount;sign=1;};
    tax_kind=tax_table[tx].taxstat % 0x10;

    /* TAX TABLE */
    if (tax_kind == T_TABLE) {
        if (tax_table[tx].nrtotal == 0 && tax_table[tx].rtotal == 0) taxamt=0;
        else
         while (1) {                  /* 1 */            /* rmtotl1=tax amount */
            if (amount <= tax_table[tx].taxnamt) {taxamt=0;break;};
            if (amount <= tax_table[tx].nrtotal) {       /* less nrtotal */
                taxamt=tax_table[tx].taxfamt;
                for (ca=0;ca < tax_table[tx].nrbreak; ca++) {
                    amount=amount-tax_table[tx].ttable[ca];
                    if (amount <= tax_table[tx].taxnamt) break;
                    taxamt +=1;
                    }
                break;
                };
            if (amount > tax_table[tx].nrtotal) {                  /* 2 */
                taxamt=(long)tax_table[tx].nrbreak+tax_table[tx].taxfamt-1;
                temp=(amount-tax_table[tx].nrtotal) / tax_table[tx].rtotal;
                taxamt=taxamt+(temp*(long)(tax_table[tx].rbreak));
                modd=(amount-tax_table[tx].nrtotal) % tax_table[tx].rtotal;
                for (ca=0;ca < tax_table[tx].rbreak;ca++) {
                    if (modd <= 0) break;
                    taxamt +=1;
                    modd=modd - tax_table[tx].ttable[tax_table[tx].nrbreak+ca];
                    }
                break;
                };            /* 2 */
            break;
            }                /* while */
        }                       /* tax table */
    else {
        /* VAT    */
        if (tax_kind == T_VAT) {
            cal_divi(amount,0,0,100000+tax_table[tx].taxrate,5);
            cal_sub(amount); /* taxable - net = tax amt */
            }
        /* ADD ON */
        else {
            /* long1 * long2_1.long2_2 = mvalue.mvalue2 */
            cal_multi(tax_table[tx].taxrate,5,amount,0,0);
            };

        /* rounding */
        taxamt=round_func(27,mvalue,moksub[0]);
        };
    if (sign) taxamt=-taxamt;
    return(taxamt);
}

void taxcal(long *tax_able,long *tax_amt)
{
    char ti;
    long temp_tax;
    char tax_kind;
    char tax4_kind;
    char tax_gst;
    long mix_tax[3];

    mix_taxamt[TAX1]=mix_taxamt[TAX2]=mix_taxamt[TAX3]=0;
    mix_tax[0]=tax_able[TAX14];
    mix_tax[1]=tax_able[TAX24];
    mix_tax[2]=tax_able[TAX34];

    vat_inp[0]=vat_inp[1]=vat_inp[2]=vat_inp[3]=0;
    for (ti=0; ti<MAX_TAX; ti++){
        tax_kind=tax_table[ti].taxstat % 0x10;
        tax4_kind=tax_table[TAX4].taxstat % 0x10;
        tax_gst=tax_table[TAX4].taxstat / 0x10;

        *tax_amt=0;
        temp_tax=0;
        if (tax_kind == T_VAT) vat_inp[ti]=1;
        if (*tax_able != 0) {
            if (ti == TAX1 && tax4_kind != T_TABLE && (tax_gst & 0x01) && mix_tax[0] != 0)
            temp_tax=tax_ext(TAX4,mix_tax[0]);
            if (ti == TAX2 && tax4_kind != T_TABLE && (tax_gst & 0x02) && mix_tax[1] != 0)
            temp_tax=tax_ext(TAX4,mix_tax[1]);
            if (ti == TAX3 && tax4_kind != T_TABLE && (tax_gst & 0x04) && mix_tax[2] != 0)
            temp_tax=tax_ext(TAX4,mix_tax[2]);
            *tax_amt=tax_ext(ti,(*tax_able+temp_tax));
            /* for tax4 exempt */
            if (temp_tax != 0) mix_taxamt[ti]=tax_ext(ti,temp_tax);
            };
        tax_amt++;
        tax_able++;
        }
    return;
}

void credttaxcal()
{
 long taxtemp[MAX_TAX];
 char ti;

 taxcal(ctaxable,taxtemp);

 for (ti=0; ti<MAX_TAX; ti++){
     if (vat_inp[ti] != 1 && taxtemp[ti] != 0) {
    if (mode_id != VMODE) cntint=1;
    else cntint=-1;
    result = taxtemp[ti];
    adcntl(crtax1amt+ti);
    adcntl(ccrtax1amt+ti);
    result = -result;
    cntint = 0;
    adcntl(gross);
    };
     }
 return;
}
/*-----------------------------------------------------------*/
void d_close()
{
 inidtx();
 flg_dis_txtmp[5]=12;  /* C */
 flg_dis_txtmp[4]=16;  /* L */
 flg_dis_txtmp[3]=0;   /* O */
 flg_dis_txtmp[2]=5;   /* S */
 flg_dis_txtmp[1]=14;  /* E */
 flg_dis_txtmp[0]=13;  /* d */
 outdtx();
 return;
}

/*****************************************************************************/
void dis9_out(char what)
{
  flg_dis_txtmp[9]=what;
  if(what == D_SUBTOTAL) {
        flg_dis_txtmp[8]=23;
        if(flg_dis_txtmp[7] == 0x16)
            flg_dis_txtmp[7]=11;
        }
  outdtx();
  return;
}

/**********************************************************/
/***                    DELAY TIME                      ***/
/**********************************************************/
void delay()         /* 96.04.17 cho */
{
  int dtime=0;

  while (dtime++ <= 800) {
    if (drwr_bit) continue;
    };
  return;
}

void start_prn()
{
// char ak;

// for (ak=0;ak<=29;ak++) sprt_buffer[ak]=prt_buffer[ak];
 pmemcpy(sprt_buffer, prt_buffer, 30);
 end_mark=0;

 cnbclr();

  if(messdec[0][0] != 0) {
     if (!r_cont)
        prn();
     }
 if (PRT_OPT.OPT4_1) {date_prn(); ej_prn();}
/* else feeding1();*/
 if (!r_cont/* && !((mode_id & RVMODE) && r_off)*/) 
    prn();
 if (PRT_OPT.OPT12_1 && train_flg &&
     (regstep != RSTEP_END || xoff_flg == 1)){
    /* train mode title */
    sprintf(prt_buffer,s_trainmd);ej_prn();
    };
// for (ak=0;ak<=29;ak++) prt_buffer[ak]=sprt_buffer[ak];
 pmemcpy(prt_buffer, sprt_buffer, 30);
 return;
}
/**********************************************************/
/***              SEPARATION ALPH & NUMERIC             ***/
/**********************************************************/
void t_buf_clr()
{
 memset(numtxt, ' ', 36);
 return;
}

void prn_com(char type)
{
 UBYTE mid_len;
 char DEC_INF=2;

 if ((SYS_OPT.OPT18_1 == 2 && !xcnt_bit) || xxcnt_bit) DEC_INF=2;   /* two decimal */
 else if (SYS_OPT.OPT18_1 == 3 && !xcnt_bit)           DEC_INF=3;   /* three decimal */
 else if (SYS_OPT.OPT18_1 == 1 && !xcnt_bit)           DEC_INF=1;   /* one decimal */
 else if (SYS_OPT.OPT18_1 == 0)                        DEC_INF=0;   /* no decimal */

 iosign_bit=0;
 if (xcnt_bit) {notdot_bit=1;lblk_bit=1;};
 ptxpnt=&numtxt[0];
 ionur_sign();

 while (ionur) {
    mk_ptxpnt(1);
    /* system option check */
    if (!xcnt_bit) {
       if (DEC_INF != 0) {
          if (ptxpnt == &numtxt[DEC_INF] && !notdot_bit) {
             numtxt[DEC_INF]='.';ptxpnt++;
             };
          };
       };
    if ((type == 1 && (ptxpnt >= &numtxt[15])) ||
        (type == 0 && (ptxpnt == &numtxt[12]))) break;
    };

 if ((DEC_INF != 0) && (!xcnt_bit)) {
    while (ptxpnt <= &numtxt[DEC_INF+1]) {
          if (ptxpnt == &numtxt[DEC_INF] && !notdot_bit) {
             numtxt[DEC_INF]='.';ptxpnt++;
             continue;
             };
          *(ptxpnt++) = '0';
          }
    };

 if((mode_id & XZMODE) && rmtotlh && (rept_ptd || grand_bit))
    {
    if (DEC_INF == 0 || xcnt_bit)
        mid_len = 8;
    else
        mid_len = 9;

    while(ptxpnt < &numtxt[mid_len])
        *(ptxpnt++) = '0';
    ionur = rmtotlh;
    while (ionur)
        mk_ptxpnt(1);
    }

 if (DEC_INF == 0 || xcnt_bit) {while(ptxpnt <= &numtxt[0]) *(ptxpnt++) = '0';}
 return;
}

void sub_sep_prn()
{
 char two_line;
 char a;
 int aa;
/*
 if (end_mark == 1) start_prn();
*/
 prn_com(0);

 if (ptxpnt < &numtxt[14]) {
    if (iosign_bit) *(ptxpnt++) = '-';
    else if (lgol_bit) { if(conv_bit) *(ptxpnt++) = PRT_OPT.OPT13[convnk];
            else *(ptxpnt++) = '@';
            }
#if 0
    else if (lgol_bit) *(ptxpnt++) = '@';
#endif
    else if (lblk_bit) *(ptxpnt++) = ' ';
    else if (lsharp_bit) *(ptxpnt++) = '#';
    else if (PRT_OPT.OPT6 == 0) *(ptxpnt++) =0x60; /*::*/
    else *(ptxpnt++) = PRT_OPT.OPT6;
    };

 two_line=0;
 while (numtxt[two_line] != ' ') {
       two_line++;
       if (two_line >=18) break;  /*testtttttt*/
       }
 a=0;
 /*while(prt_buffer[a] != NULL) {a++;two_line++;} * NULL = 0 */
 while(prt_buffer[a] != 0) {a++;two_line++;}  /*NULL*/

 /* two line print_chk */
 if (two_line >= MAX_RJ && !gnd_bit) ej_prn();   /* only description print */

 aa=MAX_RJ-1;a=0;                    /* desc & price or only price */
 while (numtxt[a] != ' ') {
     prt_buffer[aa]=numtxt[a];
     aa--;a++;
     }
#if 0
 if (valset_bit) {
    pmemcpy(valdbuf, prt_buffer, MAX_RJ);
    valset_bit=0;
    };
#endif
 if (!gnd_bit) {
    ej_prn();
    }
 else if (cng_bit) cnbclr();

 t_buf_clr();
 iosign_bit=0;
 etc_id=0;

 return;
}

void sep_prn()
{
    if (end_mark == 1)
        start_prn();
    sub_sep_prn();
}

void des_prn()
{                               /* test */
    if (!rep_disp)
        {
        if (end_mark == 1)
            start_prn();
        ej_prn();
        }
    t_buf_clr();
}

/**********************************************************/
/***              RECEIPT LOGO MESSAGE PRINT            ***/
/**********************************************************/
void message()
{
  char a;

  if (okbuf_bit || !rpoff_bit || !xoff_flg) {
      /* receipt only */
     for (a=0;a<MAX_MSG;a++) {
         if (messdec[a][0] != 0) {
             make_desc(messdec[a],MAX_MSG_DESC);
             desc2pbuf();
             };
         prn();
         }
     };
  if(messdec[0][0] == 0)
      feeding();
  return;
}

/**********************************************************/
/***                    clear decimal buf               ***/
/**********************************************************/
void clr_dec()
{
 memset(decbuf, D_BLANK, 10);
 return;
}

/**********************************************************/
#if 0
void prn_post()
{
  if (system[SINX_44] & 0x01) {
     if (okbuf_bit || !rpoff_bit || !xoff_flg) {
        make_desc(messdec[4],MAX_MSG_DESC);
        desc2pbuf();des_prn();
        make_desc(messdec[5],MAX_MSG_DESC);
        desc2pbuf();des_prn();
        };
     };
  return;
}
#endif
/**********************************************************/
/**       MAKE DESC TO PRINTING TYPE                     **/
/**********************************************************/
void make_desc(char *temps,char max)
{
 pmemcpy(prt_desc, temps, max);
 prt_desc[max]=0;
 return;
}
/**********************************************************/
/**                   ending logo issue                  **/
/**********************************************************/
void desc2pbuf()
{
  sprintf(prt_buffer,"%s",prt_desc);
  return;
}
void mk_cprn(char cinx)
{
  make_desc(CLERK_P[cinx].name,MAX_FUNC_DESC);
  desc2pbuf();
  return;
}

void endlogo()   /* asem */
{
  char sv_dsft;

  EJ_FLAG |= EJ_END;
  pgm_flg = 0;
/*  if (func != ADDCHK) {
     addcktnd=0;
     };
*/
//  if (addcktnd == 0){
     sv_dsft = dsft_flg;
     endclr(); snona_flg=0;
     if(FUNCKEY[DEPT_SFT-CASH].KEY_ST.SFT_KEY.POP_UP)
        dsft_flg = sv_dsft;
//     };

  perstp_id=0x00;
  recover_id=0x00;
  rstep_id=0x00;
  rstep1_id=0x00;
  rec_id=0x00;
  sv_get=MAX_SV_LINE;
  sv_put=0;
  revd_index = -1;
  initseq();

  if (!notbuf_bit) {
     if (train_flg != 1) {consno++; sub_endr=1;}
/*     else tconsno++;*/
     };
  notbuf_bit=1;          /* receipt buffering can't flg */

#if 0
  prn_post();
  if ((system[SINX_STAMP-1] & 0x01) && !(system[SINX_STAMP-1] & 0x02)) {
     wait_pover();
     stamp_bit=1;
     ej_prn();
     };
#endif
  if(PRT_OPT.OPT4_3) {
          if ((clerk >= 1 && clerk <= MAX_CLERK) && CLERK_P[clerk-1].name[0] != 0) {
                 mk_cprn(clerk-1);
                 }
          else {
                 sprintf(prt_buffer,s_clkshp);mkrandom((long)clerk,7,1);
                 };
         }

  if (PRT_OPT.OPT3_3) {
     prt_buffer[17]='N';prt_buffer[18]='O';prt_buffer[19]='.';
/*     if (train_flg != 1) {*/
    mkrandom(consno,MAX_RJ-1,5);
/*        if (okbuf_bit) mkrandom(t_consno,MAX_RJ-1,5);
    }
     else {
    mkrandom(tconsno,MAX_RJ-1,5);
    if (okbuf_bit) mkrandom(t_tconsno,MAX_RJ-1,5);
    };*/
     };

  if (!reissue && ((mode_id & RVMODE) || (mode_id == XMODE && xoff_flg == 1)))
     pmemcpy(stub_end,prt_buffer,MAX_RJ);
  if (reissue) pmemcpy(prt_buffer,stub_end,MAX_RJ);
  des_prn();

  if (PRT_OPT.OPT4_2) time_prn();
/*  if (train_flg == 1) prt_buffer[19]='*';*/
/*  if (okbuf_bit) prt_buffer[19]='#'; */
  if (PRT_OPT.OPT5)
     mkrandom((long)PRT_OPT.OPT5,MAX_RJ-1,1); /* 2 char machine no */

  if (!reissue && ((mode_id & RVMODE) || (mode_id == XMODE && xoff_flg == 1)))
     pmemcpy(&stub_end[MAX_RJ],prt_buffer,MAX_RJ);
  if (reissue) pmemcpy(prt_buffer,&stub_end[MAX_RJ],MAX_RJ);
  des_prn();
  feeding1();
  if(messdec[0][0] != 0)
     feeding1();

#if 0
  if (system[SINX_STAMP-1] & 0x01) {des_prn();}; /* recep only*/

  if (!(system[SINX_STAMP-1] & 0x02)) {
     if (system[SINX_STAMP-1] & 0x01) {
        wait_pover();
        };
     };
  des_prn();

  if (system[SINX_STAMP-1] & 0x03) message();
#endif
  if (!r_cont)
     message();

  wait_pover();
  if (prgt_flag == 1) {
     vnfd_bit=1;pskp_flag=1;ej_prn();
     wait_pover();
     vnfd_bit=0;
     pskp_flag=0;
     };

  if ((SYS_OPT.OPT19_1) && (mode_id & RVXMODE) && xoff_flg && (regstep == RSTEP_END)) {
        sign_off(0);
     };

  buf_cnt=0;
  notbuf_bit=0;
  onlytd_bit=0;

  end_mark=1;
  xoff_flg=0;
  pfend_flg=0;
  clr_flg = 1;
  pmenu_inx = 0;
  EJ_TINX = EJ_INDEX;
  EJ_FLAG = EJ_NORMAL;

return;
}

void endlogr() /* no feed for stop print mode */
{
    sfeed_bit = 1;
    endlogo();
    sfeed_bit = 0;
}

/**********************************************************/
/**                   COMMON SUBROUTINE                  **/
/**********************************************************/
void p_init()
{
 progm_id=0x00;
 rec_id=0x00;
 endclr();
 post_tamt=0;
 initseq();
 return;
}
#if 0
void pmd_end()
{
 des_prn();
 endlogo();
 p_init();
 return;
}
#endif
/*****************************************************************************/
/**             LOAD DEPT ?PLU STAT    KEY                                  **/
/*****************************************************************************/
/**********************************  dptstp_id  ******************************/
/*       ÚÄÄÄÄÄÄÂÄÄÄÄÄÄÂÄÄÄÄÄÄÂÄÄÄÄÄÄÂÄÄÄÄÄÄÂÄÄÄÄÄÄÂÄÄÄÄÄÄÂÄÄÄÄÄÄ¿           */
/*       ³pluact³valid ³singl ³negat ³dptax4³dptax3³dptax2³dptax1³           */
/*       ÀÄÄÄÄÄÄÁÄÄÄÄÄÄÁÄÄÄÄÄÄÁÄÄÄÄÄÄÁÄÄÄÄÄÄÁÄÄÄÄÄÄÁÄÄÄÄÄÄÁÄÄÄÄÄÄÙ           */
/*********************************  dptstp1_id  ******************************/
/*       ÚÄÄÄÄÄÄÂÄÄÄÄÄÄÂÄÄÄÄÄÄÂÄÄÄÄÄÄÂÄÄÄÄÄÄÂÄÄÄÄÄÄÂÄÄÄÄÄÄÂÄÄÄÄÄÄ¿           */
/*       ³sglok ³ nadd ³ gas  ³ hash ³ crst ³ cinc ³inact ³preset³           */
/*       ÀÄÄÄÄÄÄÁÄÄÄÄÄÄÁÄÄÄÄÄÄÁÄÄÄÄÄÄÁÄÄÄÄÄÄÁÄÄÄÄÄÄÁÄÄÄÄÄÄÁÄÄÄÄÄÄÙ           */
/*****************************************************************************/
#if 0
void load_dpstat()
{
 mkdeach(0);

 dptstp_id=(char)((eachbuf[2] << 4) | eachbuf[0]);
 dptstp1_id=(char)((eachbuf[3] << 4) | eachbuf[1]);

 cinc_bit=eachbuf[4]/2;

 dptstp_id&=0xf0;
 if (eachbuf[0] & 1) dptax1_bit=1;
 if (eachbuf[0] & 2) dptax2_bit=1;
 if (eachbuf[0] & 4) dptax3_bit=1;
 if (eachbuf[0] & 8) dptax4_bit=1;
 return;
}
#endif

/*****************************************************************************/
void load_dstat()
{
 dptstp_id = dept[func].status[0];
 dptstp1_id= dept[func].status[1];
 return;
}
/*****************************************************************************/
void load_pstat()
{
 dptstp_id = plu[pcode].status[0];
 dptstp1_id= plu[pcode].status[1];
 return;
}
#if 0
/*****************************************************************************/
/**             PRN PLU CODE           KEY                                  **/
/*****************************************************************************/
void prn_plucode(char st_code,char type)
{
 int i;
 char bufinx;

 if (plu[pcode].plu_code != 0){
    ionur=plu[pcode].plu_code;
    mkdeach(1);
    bufinx=st_code;
    prt_buffer[bufinx++]='P';
    prt_buffer[bufinx++]='L';
    prt_buffer[bufinx++]='U';
    prt_buffer[bufinx++]='#';
    if (type == 0) bufinx++;
    for (i=7; i>=0; i--){
    if (eachbuf[i] != 0) prt_buffer[bufinx++]=eachbuf[i];
    }
    prt_buffer[bufinx]=0;
    if (st_code == 1) des_prn();
    };
 return;
}
#endif
/*****************************************************************************/
/**             PRN TAX LOGO           KEY                                  **/
/*****************************************************************************/
void prn_dtlogo(char tax_inf)       /* tax1 / tax2 / tax3 / tax4 /tax1&3 */
{
 char k=0;

 while(1) {
  if (prt_buffer[k] == 0) { /*NULL*/
     prt_buffer[k++]=' ';
     if (tax_inf & 0x0f) prt_buffer[k++]=P_TAX;
     if (tax_inf & 0x01) prt_buffer[k++]='1';
     if (tax_inf & 0x02) prt_buffer[k++]='2';
     if (tax_inf & 0x04) prt_buffer[k++]='3';
     if (tax_inf & 0x08) prt_buffer[k++]='4';
     /* coupon */
     if(regstep == RSTEP_END) {
          if (cupn_bit) prt_buffer[k++]='N';
          }
     else {
          if (cupn_bit) prt_buffer[k++]='C';
          }
     prt_buffer[k++]=0; /*null*/
     break;
     };
  k++;
  } /* while */
 return;
}
/*****************************************************************************/
void xlogo_nur(char type)
{
 xcnt_bit=1;
 logo_nur(type);
 return;
}
/*****************************************************************************/
void xsep_prn()
{
 xcnt_bit=1;sep_prn();
 return;
}

/***********************************************************************/
/***    DECIMAL SHIFT                                                ***/
/***********************************************************************/
void mv_decbuf()
{
  int ibb;
  for (ibb=9;ibb>=1;ibb--) decbuf[ibb]=decbuf[ibb-1];
  return;
}
/*****************************************************************************/
/***    DISP / OUT                                                   ***/
/*****************************************************************************/
void ini_outdtx()
{
 inidtx();outdtx();
 return;
}
/*****************************************************************************/
/***    ROUNDING                                                           ***/
/*****************************************************************************/
long round_func(char opt,long value,char frac)
{
 if (cal_nega == 1) value=-value;
 if (opt == 1) value+=(long)((frac+9)/10);
 else
 if (opt == 2) value=value;
 else
 value+=(long)((frac+5)/10);

 if (cal_nega == 1) value=-value;
 return(value);
}

/*****************************************************************************/
/***    WAIT PRINTING END                                                  ***/
/*****************************************************************************/
void wait_pover()
{
#ifndef BCDBG
  while(!pover_bit);
#endif                                 /* BCDBG */
  return;
}
/*****************************************************************************/
/***    PLU DEPT OPTIOn PRN                                                ***/
/*****************************************************************************/
void prn_xdptplu(char type, char rep_flg)
{
  if (type == IS_DEPT) nur=dept[func].price;
  else nur=plu[pcode].price;
  if (negat_bit) nur= -nur;
  lgol_bit=1;
  if (gas_bit) {
     if(SYS_OPT.OPT3_3)
         sprintf(prt_buffer,s_bltramt);
     else
         sprintf(prt_buffer,s_bgalamt);
     prn_gcpt(0,3,0);
     return;
     };
//  if (hash_bit && rep_flg) logo_nur(32);
  if (!rep_flg){
     if (preset_bit) logo_nur(9);
     else logo_nur(10);
     };
  lgol_bit=0;
  return;
}

/*****************************************************************************/
/***    CLERK DESC PRN                                                     ***/
/*****************************************************************************/
void prn_clkdec(char cc)
{
  if (CLERK_P[cc].name[0] != 0) mk_cprn(cc);
  else {
     if (cc < MAX_CLERK) sprintf(prt_buffer,s_clkpd,(int)cc+1);
     };
  return;
}

void prn_grpdec(char cc)
{
    if(grp_desc[cc][0] == 0)
        sprintf(prt_buffer,s_grppd,cc);
    else
        {
        pmemcpy(prt_buffer,grp_desc[cc],MAX_GRP_DESC);
        prt_buffer[MAX_GRP_DESC] = 0;
        }
}

void mk_lline(unsigned char *rbuf, UBYTE x, int end)
{
    long cnt1,cnt;
    cnt1 = strlen(lcdbuf);
    cnt = strlen(rbuf);

    if( (cnt1 + cnt + x) >= end )
        lcdbuf[end-cnt-x-1] = 0x20;
    else
        memset(&lcdbuf[cnt1],0x20,end-cnt1-cnt-x);
    strcpy(&lcdbuf[end-cnt-x],rbuf);
}

void dsp_rep(unsigned char *lmsg, long amt, UBYTE y, unsigned char dot_pos, unsigned char esym)
{
    unsigned char temp[25], tmp2[10],svdot, tt, cc;

    pmemcpy(&lcdbuf[MAX_CLM-12],lmsg,12);

    lcdbuf[MAX_CLM] = 0;
    sprintf(lcdbuf," %s",&lcdbuf[MAX_CLM-12]);
    svdot = SYS_OPT.OPT18_1;
    if(dot_pos == 0)
        SYS_OPT.OPT18_1 = dot_pos;
    else if(dot_pos > 10)              /* 980326 */
        SYS_OPT.OPT18_1 = dot_pos - 10;
    if(grand_bit && rmtotlh)
        {
        l2c(rmtotlh, temp, 0);
        mk_dnum(amt,tmp2,0);
        tt = 8 + (dot_pos != 0) - strlen(tmp2);
        memset(&temp[cc=strlen(temp)], '0', tt);
        pmemcpy(&temp[cc+tt], tmp2, strlen(tmp2)+1);
        }
    else
        mk_dnum(amt,temp,0);
    if(dot_pos > 10)              /* 980326 */
        temp[strlen(temp)+10-1-dot_pos] = ':';
    SYS_OPT.OPT18_1 = svdot;
    svdot = strlen(temp);
    temp[svdot++] = esym;
    temp[svdot] = 0;
    mk_lline(temp,0,MAX_CLM);

    dsp_str(0,y,lcdbuf);
}

void mk_idamt(long amt, UBYTE x, UBYTE y, UBYTE end , UBYTE stay, UBYTE sp, char sym)
{
    unsigned char temp[12];
    if(sp == 3) sym = 1;
    mk_dnum(amt,temp,sym);
    mk_lline(temp,x,end);

    if(sp == 2)
        dsp_str(x,y,lcdbuf);
    else
        dsp_line(lcdbuf,stay);
}

void mk_tdmsg( unsigned char *desc, long amt, UBYTE x, UBYTE y, UBYTE end)
{
 unsigned char temp[12];

 mk_dnum(amt,temp,0);
/*
 if(!(flg_dpt & 0x01))
    clr_lcd();
*/
 pmemcpy(lcdbuf,desc,12);

 lcdbuf[12] = 0;

 mk_idamt(amt,x,y,end,0,2,0);
}

void dsp_tax(int type)
{
    long taxl;
    if(nodtax_bit) {
//       nodtax_bit = 0;
       return;
       }
    taxcal(taxable,tnd_tax);
    taxl = tax_sum(type,tnd_tax);

    mk_tdmsg(s_tax,taxl,0,6,8);
    if((type == -1) || (type == -2)) {
        if((regstep == RSTEP_RA) || (regstep == RSTEP_PO))
            mk_tdmsg(s_sbtl,rapo_total,9,6,MAX_CLM);
        else
            mk_tdmsg(s_sbtl,gamt+taxl,9,6,MAX_CLM);
        }
}

void mk_idmsg( unsigned char *desc, long amt, UBYTE stay, UBYTE sp)
{
 int i;
 UBYTE *ptr;

 if(!(mode_id & RVXMODE))
    return;
 ptr = &lcdbuf[MAX_CLM-12];
 pmemcpy(ptr,desc,12);

 lcdbuf[MAX_CLM] = 0;
 if(!sp)
     {
     i = rcnt%10;
     sprintf(lcdbuf,"%d %s",i,ptr);
     }
 else
     sprintf(lcdbuf," %s",ptr);

 mk_idamt(amt,0,0,MAX_CLM,stay,sp,0);
 if(!sp)
    dsp_tax(-1);
}

void dp_idmsg(long amt, UBYTE stay)
{
    int i;
    UBYTE *ptr;
    unsigned char temp[12];
    long taxl;

    if(!(mode_id & RVXMODE))
        return;
    ptr = &lcdbuf[MAX_CLM-12];
    pmemcpy(ptr,prt_buffer,12);

    lcdbuf[MAX_CLM] = 0;
    i = rcnt%10;
    sprintf(lcdbuf,"%d %s",i,ptr);

///////////////////////////////////////////////////////////////////////
//    mk_idamt(amt,0,0,MAX_CLM,stay,sp,0);
    mk_dnum(amt,temp,0);
    mk_lline(temp,0,MAX_CLM);

    dsp_line(lcdbuf,stay);
//    mk_idamt(amt,0,0,MAX_CLM,stay,sp,0);
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
//    dsp_tax(-1);
    taxcal(taxable,tnd_tax);
    taxl = tax_sum(-1,tnd_tax);

  ///////////////////////////////////////////////////////////////////////
  //    mk_tdmsg(s_tax,taxl,0,6,8);
    mk_dnum(taxl,temp,0);
    pmemcpy(lcdbuf,s_tax,12);
    lcdbuf[12] = 0;
    ///////////////////////////////////////////////////////////////////////
    //    mk_idamt(taxl,0,6,8,0,2,0);
/*    mk_dnum(taxl,temp,0); */
    mk_lline(temp,0,8);
    dsp_str(0,6,lcdbuf);
    //    mk_idamt(taxl,0,6,8,0,2,0);
    ///////////////////////////////////////////////////////////////////////
  //    mk_tdmsg(s_tax,taxl,0,6,8);
  ///////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////
  //    mk_tdmsg(s_sbtl,gamt+taxl,9,6,MAX_CLM);
    mk_dnum(gamt+taxl,temp,0);
    pmemcpy(lcdbuf,s_sbtl,12);
    lcdbuf[12] = 0;
    ///////////////////////////////////////////////////////////////////////
    //    mk_idamt(gamt+taxl,9,6,MAX_CLM,0,2,0);
/*    mk_dnum(gamt+taxl,temp,0); */
    mk_lline(temp,9,MAX_CLM);
    dsp_str(9,6,lcdbuf);
    //    mk_idamt(gamt+taxl,9,6,MAX_CLM,0,2,0);
    ///////////////////////////////////////////////////////////////////////
  //    mk_tdmsg(s_sbtl,gamt+taxl,9,6,MAX_CLM);
  ///////////////////////////////////////////////////////////////////////
//    dsp_tax(-1);
///////////////////////////////////////////////////////////////////////
}

void prn_clksub(UBYTE *buffer, int time1, UBYTE prn_f)
{
    int time2;
    UBYTE i;

    time2 = time1 % 100;
    time1 /= 100;
    sprintf(buffer,s_tworked);
    i = strlen(buffer);
    if(time1 > 9)
        buffer[i++] = (time1 / 10) + 0x30;
    buffer[i++] = (time1 % 10) + 0x30;
    buffer[i++] = ':';
    buffer[i++] = (time2 / 10) + 0x30;
    buffer[i++] = (time2 % 10) + 0x30;
    if(prn_f)
        {
        buffer[i++] = ' ';
        buffer[i++] = 'h';
        buffer[i++] = 'o';
        buffer[i++] = 'u';
        buffer[i++] = 'r';
        buffer[i++] = 's';
        }
    buffer[i++] = 0;
}

void prn_clklog(UBYTE idx, UBYTE clerk)
{
 char sv_opt;
 UBYTE msg1[20], msg2[20];

 cmemcpy(msg1,code_mem->LOGMSG[idx*2],15);
 cmemcpy(msg2,code_mem->LOGMSG[idx*2+1],15);

 sprintf(prt_buffer,"%s",msg1);
 ej_prn();
 if(!r_cont)
     prn();
 if ((clerk >= 1 && clerk <= MAX_CLERK) && CLERK_P[clerk-1].name[0] != 0) {
     mk_cprn(clerk-1);
 }
 else {
     sprintf(prt_buffer,s_clkshp);mkrandom((long)clerk,7,1);
 };
 if(clerk < 10)
         sprintf(&prt_buffer[23],"#0%d",clerk);
 else
         sprintf(&prt_buffer[23],"#%d",clerk);
 ej_prn();

 sprintf(prt_buffer,"%s:",msg2);
 rtc_read();
 if(idx < 2)
    fill_time(strlen(prt_buffer)+1);
 else
    {
    fill_date(prt_buffer, 8, 0);
    fill_time(19);
    }
 ej_prn();

 if(idx == 3)                          /* CLERK TIME OUT */
    {
    prn_clksub(prt_buffer, CLKIO[IO_CLK].W_TIME, 1);
    ej_prn();
    }

 sv_opt = SYS_OPT.OPT19_1;
 SYS_OPT.OPT19_1 = 0;
 endlogr();
 SYS_OPT.OPT19_1 = sv_opt;
}

char opn_alarm(char type)
{
 char cur_sec;
 char cur_min;
 char pgm_tm;
 int  temp;

 /* type = 0 : only read
           1 : check   */

 rtc_read();

 cur_sec=rtcb_flg[1]*10 + rtcb_flg[0]; /* present second */
 cur_min=rtcb_flg[3]*10 + rtcb_flg[2]; /* present minute */
 if (type == 0) {
    dwr_min=cur_min;
    dwr_sec=cur_sec;
    return(SUCCESS);
    };

 if (cur_sec < dwr_sec) {
    cur_sec +=60;
    if (cur_min == 0) cur_min=59;
       else cur_min -=1;
    cur_sec -=dwr_sec;
    } else cur_sec -=dwr_sec;
 if (cur_min < dwr_min) {
    cur_min +=60;
    cur_min -=dwr_min;
    } else cur_min -=dwr_min;

 temp=(int)cur_min*60;
 temp +=(int)cur_sec;

 if (SYS_OPT.OPT16 == 0) pgm_tm=30;
    else pgm_tm=SYS_OPT.OPT16;
 if (temp >= pgm_tm) return(FAIL);
 return(SUCCESS);
 }

char chk_dwrlimit()
{
    if (SYS_OPT.OPT5 != 0 &&
        (SYS_OPT.OPT5 < rep[cshindw].total+rep[chkindw].total)) {
      return(FAIL);
                }
   return(SUCCESS);
}
void plu_pop(char pnum)
{
    char i;
    long dprice;                       /* 980528 */

    if(pop_lcd == 0) {
        sv_lcd();
        }
    pop_lcd = 1;
    clr_lcd();
    for(i=0; i < 7; i++,pnum++) {
        if(pnum < 10)
                sprintf(lcdbuf1,"0%d",pnum);
        else
                sprintf(lcdbuf1,"%d",pnum);

        sprintf(&lcdbuf1[2]," %s",norm_str(plu[pnum-1].desc,11));
        strcpy(lcdbuf,lcdbuf1);
        dprice = plu[pnum-1].price%100000;
        if(plu[pnum-1].status[0] & 0x10)  /* negat_bit */
                dprice = -dprice;
        mk_idamt((long)dprice, 0, i, 20, 0, 2,0);
        }
}

UBYTE is_xfirst()
{
    if((mode_id == XMODE) && (regstep == RSTEP_END) && (menu_no == 0) &&
            (xm_step == 0))
        return 1;
    return 0;
}

/**********************************************************/
/***                                                    ***/
/***         ECR <-> SCALE OPERATION ROUTINE            ***/
/***                                                    ***/
/**********************************************************/
void dsp_scl()
{
     fdec_inx = 0;
     prn_fdec(dcnt,scale_logo);
//     prt_buffer[fdec_inx-2] = 0;
     pop_menu(prt_buffer,'|');
     memset(prt_buffer,0x20,sizeof(prt_buffer));
     fdec_inx = 0;
}
void comm_scale(char auto_f)
{
    char aa;
    char stat1,stat2;
    long wt = -1L;
    /*char status1,status2;*/
    /*----------------------------------
                    0  1 2 3 4 5 6 7 8 9  10 11121314 15
    RETURN FORMAT : LF-X-X-.-X-X-X-K-G-CR-LF-S-h-h-CR-ETX
    KG = XX.XXX
    LB = XXX.XX
    return status : status 1(h) = 0 / 2 : ok
                    status 2(h) = 0     : ok
    -----------------------------------*/

    if (knur_bit) { errmsg = E_KEY; ERR }

    memset(comm_buff, 0, 20);
    while (1) {
        scale_trans();
        if (err_bit) {errmsg=E_TIMEOUT;ERR};               /* time out 5 sec*/

        aa=0;
        while (comm_buff[aa] != ETX) {
        if (comm_buff[aa++] == 'S') {stat1=comm_buff[aa++];
                                        stat2=comm_buff[aa++];
                                        break;
                                        };
        }
        if (stat1 & 0x01) {delay();continue;};
        if (stat2 & 0x03) {errmsg=E_SCALE;ERR};

        if (comm_buff[7] == 'K') scale_logo=P_KG;
        else if (comm_buff[7] == 'L') scale_logo=P_LB;
        else { errmsg=E_SCALE; ERR}

        nur=0;dcnt=0;
        for (aa=1;aa<=6;aa++) {
            if (comm_buff[aa] == '.') {dcnt=6-aa;continue;}
            nur= nur * 10 + (comm_buff[aa]-'0');
            };

        kdec_bit=1;
//        if (dcnt == 4) nur=nur/10;
//        if (dcnt == 2) nur=nur*10;

        if (tare_flg != 0) {
           if(dcnt == 2)
                   nur *= 10;
           nur -=tare_weight[tare_flg-1];
           if(nur <= 0) { errmsg = E_NUMOVER; ERR }
           if(nur % 10)
                  dcnt = 3;
           else
                  nur /= 10;
           }
        if (nur < 0) {errmsg=E_SCALE;ERR};
        if((wt != nur) && !auto_f) {

                wt = nur;
                dsp_scl();
                mkdnur(dcnt);
                flg_dis_txtmp[9]=5;   /* S */
                flg_dis_txtmp[8]=12;  /* C */
                outdtx();
                }

        if (/*macro_flg != 0 ||*/ (flg_key_pend > 0) || auto_f) break;
        modescan();
        if ((mode_id != modesave) && ((modesave != RMODE) || (mode_id != XMODE))) break;
        delay();
        }

    return;
}
signed char set_lfeed(char line, UBYTE *buf)
{
#if 0
    WORD retval=0;

    switch(PERI_OPT.PORT_P[port-1].OPT6)
        {
        case PRN_CITIZEN :
            buf[0] = 0x0c;
            buf[1] = (UBYTE)line;
            return 2;
        case PRN_TM300 :
        case PRN_TMT80 :
        case PRN_TM290 :
            buf[0] = 0x1b;
            buf[1] = 0x64;
            buf[2] = (UBYTE)line;
            return 3;
        case PRN_SP200 :
            buf[0] = 0x1b;
            buf[1] = 0x61;
            buf[2] = (UBYTE)line;
            return 3;
        }

    return retval;
    #endif
    buf[0] = 0x1b;
    buf[1] = 0x64;
    buf[2] = (UBYTE)line;
    return 3;
}

signed char set_can(UBYTE *buf)
{
#if 0
    WORD retval=0;

    switch(PERI_OPT.PORT_P[port-1].OPT6)
        {
        case PRN_CITIZEN :
            buf[0] = 0x18;
            return 1;
        case PRN_TM300 :
            buf[0] = 0x1b;
            buf[1] = 0x40;
            buf[2] = 0x1b;
            buf[3] = 0x21;
            buf[4] = 0x01;
            return 5;
        case PRN_TMT80 :
        case PRN_TM290 :
            buf[0] = 0x1b;
            buf[1] = 0x40;
            buf[2] = 0x1b;
            buf[3] = 0x21;
            buf[4] = 0x00;
            return 5;
        case PRN_SP200 :
            buf[0] = 0x1b;
            buf[1] = 0x40;
            return 2;
        }

    return retval;
#endif
    buf[0] = 0x1b;
    buf[1] = 0x40;
    buf[2] = 0x1b;
    buf[3] = 0x21;
    buf[4] = 0x01;
    return 5;
}

signed char set_red(UBYTE *buf)
{
#if 0
    WORD retval=0;

    switch(PERI_OPT.PORT_P[port-1].OPT6)
        {
        case PRN_CITIZEN :
            buf[0] = 0x13;
            return 1;
        case PRN_TM300 :
            buf[0] = 0x1b;
            buf[1] = 0x72;
            buf[2] = 0x01;
            return 3;
        case PRN_SP200 :
            buf[0] = 0x1b;
            buf[1] = 0x34;
            return 2;
        }

    return retval;
#endif
    buf[0] = 0x1b;
    buf[1] = 0x72;
    buf[2] = 0x01;
    return 3;
}

signed char can_red(UBYTE *buf)
{
#if 0
    WORD retval=0;

    switch(PERI_OPT.PORT_P[port-1].OPT6)
        {
        case PRN_TM300 :
            buf[0] = 0x1b;
            buf[1] = 0x72;
            buf[2] = 0x00;
            return 3;
        case PRN_SP200 :
            buf[0] = 0x1b;
            buf[1] = 0x35;
            return 2;
        }
    return retval;
#endif
    buf[0] = 0x1b;
    buf[1] = 0x72;
    buf[2] = 0x00;
    return 3;
}

signed char set_dbl(UBYTE *buf)
{
#if 0
    WORD retval=0;

    switch(PERI_OPT.PORT_P[port-1].OPT6)
        {
        case PRN_CITIZEN :
            buf[0] = 0x0e;
            return 1;
        case PRN_TM300 :
            buf[0] = 0x1b;
            buf[1] = 0x21;
            buf[2] = 0x21;        /* PKR 0905 */
            return 3;
        case PRN_TMT80 :
        case PRN_TM290 :
            buf[0] = 0x1b;
            buf[1] = 0x21;
            buf[2] = 0x20;        /* PKR 0905 */
            return 3;
        case PRN_SP200 :
            buf[0] = 0x1b;
            buf[1] = 0x57;
            buf[2] = 0x31;
            return 3;
        }

    return retval;
#endif
    buf[0] = 0x1b;
    buf[1] = 0x21;
    buf[2] = 0x21;        /* PKR 0905 */
    return 3;
}

signed char can_dbl(UBYTE *buf)
{
#if 0
    WORD retval=0;

    switch(PERI_OPT.PORT_P[port-1].OPT6)
        {
        case PRN_CITIZEN :
            buf[0] = 0x0f;
            return 1;
        case PRN_TM300 :
            buf[0] = 0x1b;
            buf[1] = 0x21;
            buf[2] = 0x01;                 /* PKR 0905 */
            return 3;
        case PRN_TMT80 :
        case PRN_TM290 :
            buf[0] = 0x1b;
            buf[1] = 0x21;
            buf[2] = 0x00;                 /* PKR 0905 */
            return 3;
        case PRN_SP200 :
            buf[0] = 0x1b;
            buf[1] = 0x57;
            buf[2] = 0x30;
            return 3;
        }

    return retval;
#endif
    buf[0] = 0x1b;
    buf[1] = 0x21;
    buf[2] = 0x01;                 /* PKR 0905 */
    return 3;
}

signed char set_cut(char full_f, UBYTE *buf)
{
#if 0
    WORD retval=0;

    switch(PERI_OPT.PORT_P[port-1].OPT6)
        {
        case PRN_CITIZEN :
            buf[0] = 0x1b;
            buf[1] = 0x50;
            buf[2] = (full_f?0:1);
            return 3;
        case PRN_TM300 :
        case PRN_TMT80 :
            buf[0] = 0x1b;
            buf[1] = (full_f?0x69:0x6d);
            return 2;
        }

    return retval;
#endif
    buf[0] = 0x1b;
    buf[1] = (full_f?0x69:0x6d);
    return 2;
}

UBYTE CL_TBL[][12] = {
    /*  20  21  22  23  24  25  26  27  28  29  30  31 */
    /*      ‚   ¡   ¢   š      £   ¥   ¤      Tx  Fs */
#if 0
    {   220,190,195,200,176,204,205,211,212,186,185,'F'},  /* Citizen */
    {   160,130,161,162,154,129,163,165,164,157,'T','F'},  /* TM-300 */
    {   160,130,161,162,154,129,163,165,164,157,'T','F'},  /* TM-T80 */
    {   160,130,161,162,154,129,163,165,164,157,'T','F'},  /* TM-290 */
    {   206,176,181,186,162,190,191,197,198,172,171,'F'}   /* SP-200 */
#endif
    {   160,130,161,162,154,129,163,165,164,157,'T','F'},  /* TM-300 */
    };

UBYTE CH_TBL[][44] = {
    /* 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  A,  B,  C,  D,  E,  F*/
#if 0
    {209,204,190,223,219,221, 32,209,193,189,191,194,198,196,174,216,
      32, 32, 32,203,199,201,208,206, 32,175,176,168,160,186, 32, 32,
     220,195,200,205,212,211,179,180,210, 32, 32,177},
    {128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,
     144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,
     160,161,162,163,164,165,166,167,168,254,224,225},
    {128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,
     144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,
     160,161,162,163,164,165,166,167,168,254,224,225},
    {128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,
     144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,
     160,161,162,163,164,165,166,167,168,254,224,225},
    {128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,
     144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,
     160,161,162,163,164,165,166,167,168,254,224,225}
#endif
    {128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,
     144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,
     160,161,162,163,164,165,166,167,168,254,224,225},
     };

UBYTE conv_ch(UBYTE c_ch)
{
    if( c_ch == 0x11 ) /* double delimeter */
        return 0x20;

    if(((c_ch >= 0x20) && (c_ch <= 0x7e)) /* || (PERI_OPT.PORT_P[port-1].OPT6 == 0) */)
        return c_ch;

    if(c_ch == 0x7f)                     /* Pound */
        {
#if 0
        switch(PERI_OPT.PORT_P[port-1].OPT6)
            {
            case PRN_CITIZEN :
                return 0xa0;
            case PRN_TM300 :
            case PRN_TMT80 :
            case PRN_TM290 :
                return 0x9c;
            case PRN_SP200 :
                return 'L';
            }
#endif
        return 0x9c;
        }
    else if((c_ch > 0x7f) && (c_ch < 0xac))
        return CH_TBL[0][c_ch - 0x80];
    else if(c_ch > 0xa8)
        return 0x20;
    else if(c_ch > 0x1D)
        return CL_TBL[0][c_ch - 0x14];
    else if(c_ch <= 0x1D)
        return c_ch;

    return 0x20;
}

signed char kp_prt(UBYTE *sendptr,UWORD len)
{
        UBYTE c_ch, dbl_f = 0;
        UBYTE i;

        if(len > (sizeof(KPEND_PACK)-2))
            len = sizeof(KPEND_PACK) - 2;

        trx_buf_cnt = 0;
        for(i=0;i<len;i++)
            {
            c_ch = sendptr[i];
            switch(c_ch)
                {
                case 0x0c:             /* Long Feed */
                    trx_buf_cnt += set_lfeed(sendptr[++i], &comm_buff[trx_buf_cnt]);
                    break;
                case 0x0e:             /* Double */
                    trx_buf_cnt += set_dbl(&comm_buff[trx_buf_cnt]);
                    break;
                case KP_CUT:           /* Paper cut */
                    trx_buf_cnt += set_cut(1,&comm_buff[trx_buf_cnt]);
                    break;
                case 0x13:             /* Red printing */
                    trx_buf_cnt += set_red(&comm_buff[trx_buf_cnt]);
                    break;
                case KP_CAN:           /* Cancel */
                    trx_buf_cnt += set_can(&comm_buff[trx_buf_cnt]);
                    break;
                case 0x11:
                    if((sendptr[0] != 0x0e) && (sendptr[1] != 0x0e))
                        {
                        trx_buf_cnt += set_dbl(&comm_buff[trx_buf_cnt]);
                        dbl_f = 1;
                        break;
                        }
                default:
                    comm_buff[trx_buf_cnt++] = conv_ch(c_ch);
                    if(dbl_f == 1)
                        {
                        trx_buf_cnt += can_dbl(&comm_buff[trx_buf_cnt]);
                        dbl_f = 0;
                        }
                    break;
                }
            }
    trx_buf_cnt += can_dbl(&comm_buff[trx_buf_cnt]);
    trx_buf_cnt += can_red(&comm_buff[trx_buf_cnt]);
    slip_trans();
    if(err_bit) {
        err_bit = 0;
        return(-1);
        }
    return(1);
}

signed char kp_lfeed(UWORD lfeed)
{

        UBYTE        buf[3];

        if(!lfeed) return 1;

        memset(buf,0,3);

            if(lfeed > 1)
            {
                buf[0] = KP_NLF;
                buf[1] = lfeed;
            }
        else
                buf[0] = KP_LF;

        return(kp_prt(buf,strlen(buf)));
}

signed char kp_out(KPEND_PACK *buff, UBYTE port, UBYTE cutf)
{
    UBYTE        buf = KP_CUT;  /* Cutting */
    KP_PACK      *kpack;
    char         i,lfnum;

    kpack = (KP_PACK*)buff;

    if(!port) {
        if(strlen(kpack->DATA))
            {
            memset(prt_buffer,0x20,sizeof(prt_buffer));
            pmemcpy(prt_buffer,kpack->DATA,strlen(kpack->DATA));
            prn();
            }
        for(i=0; i<kpack->LF;i++)
                feeding1();
        if(cutf == 1) {
            feeding1();
            endlogo();
            }
        return(1);
        }

    if(kp_prt((UBYTE*)kpack,strlen((UBYTE*)kpack)) < 0)
            return(-1);
    if(cutf == 1)
        lfnum  = buff->LF;
    else
        lfnum = kpack->LF;

    if(kp_lfeed(lfnum) < 0)
        return(-1);

    if(cutf == 1)
    {
        if(kp_lfeed(SYS_OPT.END_FEED) < 0)
                return(-1);
        if(kp_prt(&buf,1) < 0)
                return(-1);
    }

    return(1);
}

void fill_ch(UBYTE *buf, UBYTE ch)
{
    while(*buf != '\n')
        {
        if(*buf == 0)
            *buf = ch;
        buf++;
        }
}

signed char kp_end(UWORD d_port, long ttl)
{
    KP_PACK *tpack1;

    memset((UBYTE*)&kppack,0,sizeof(KPEND_PACK));
#if 0
    if(SYS_OPT.OPT13_3 && ttl)
        {
        tpack1 = (KP_PACK*)&kppack;
        tpack1->RED = (UBYTE)'\n';
        tpack1->DBL = KP_DBL;
        mk_dnum(ttl,lcdbuf1,0);
        sprintf(lcdbuf,"TOTAL");
        mk_lline(lcdbuf1,0,18);
        if(d_port)
            sprintf(tpack1->DATA,"%s\n", lcdbuf);
        else
            sprintf(tpack1->DATA,"%s", lcdbuf);
        tpack1->LF = 0;
        if(!d_port)
                   feeding1();
        if(kp_out((KPEND_PACK*)tpack1,d_port, 0) < 0)
            return(-1);
        }
#endif

    if(d_port)
    {
        fill_date(lcdbuf1, 0, 0);
        lcdbuf1[10] = 0;
        fill_time(0);
        prt_buffer[7] = 0;


        kppack.RED = KP_CAN;
        kppack.DBL = (UBYTE)'\n';

        make_desc(CLERK_P[clerk-1].name,MAX_FUNC_DESC);
        sprintf(lcdbuf,prt_desc);
        mk_lline(lcdbuf1,0,23);
        mk_lline(prt_buffer,0,31);
        sprintf(kppack.DATA,"%s\n",lcdbuf);
        kppack.LF = 0;
    }
    else    memset((UBYTE*)&kppack,0,sizeof(KPEND_PACK));

    if(kp_out(&kppack,d_port, 1) < 0)
          return(-1);
    return(1);
}

void kp_madj(UBYTE *des, UBYTE *src, char d_port)
{
    UWORD offset;

    offset = (20 - strlen(src)) / 2;
    memset(des,0x20,offset);
    if(d_port)
        sprintf(&des[offset],"%s\n",src);
    else
        sprintf(&des[offset],"%s",src);
}

signed char kp_head(char d_port)
{
    KP_PACK *hpack;
    if(d_port) {
        if(kp_lfeed(SYS_OPT.INI_FEED) < 0)
            return(-1);
        }
    else
        start_prn();
    hpack = (KP_PACK*)&kppack;
    hpack->RED = KP_CAN;
    hpack->DBL = KP_DBL;

    sprintf(lcdbuf," ORDER#");
    mkrandom((long)PRT_OPT.OPT5,1,1);
    if((regstep == RSTEP_END) && (sub_endr == 1))
        mkrandom(consno % 100,3,1);
    else
        mkrandom((consno+1) % 100,3,1);
    prt_buffer[4] = 0;
    if(d_port) {
        mk_lline(prt_buffer,0,20);
        sprintf(hpack->DATA,"%s\n", lcdbuf);
        }
    else {
        mk_lline(prt_buffer,0,MAX_CLM);
        sprintf(hpack->DATA,"%s", lcdbuf);
        }
    hpack->LF = 1;
    if(kp_out((KPEND_PACK*)hpack,d_port, 0) < 0)
        return(-1);

    if (PRT_OPT.OPT12_1 && train_flg ) {
        /* train mode title */
        sprintf(prt_buffer,s_trainmd);
        kp_madj(hpack->DATA,prt_buffer,d_port);
        hpack->LF = 1;
        if(kp_out((KPEND_PACK*)hpack,d_port, 0) < 0)
               return(-1);
     }

    if(mode_id == VMODE)
    {
        sprintf(prt_buffer,"*** VOID MODE ***");
        kp_madj(hpack->DATA,prt_buffer,d_port);
        hpack->LF = 1;
        hpack->RED = KP_RED;
        if(kp_out((KPEND_PACK*)hpack,d_port, 0) < 0)
           return(-1);
     }
     return 1;
}

signed char mk_kpl(char inx, char port, long *dest_ttl)
{
      UWORD     bcnt,pcode;

      memset((UBYTE*)&kppack, 0, sizeof(KP_PACK));
      if(kp_regr.pack[inx].RED)
               kppack.RED = KP_RED;
      else
               kppack.RED = KP_DBL;
      kppack.DBL = KP_DBL;

      if(kp_regr.pack[inx].QTY == 0)
          { 
          (*dest_ttl) += kp_regr.pack[inx].AMT;
          return(1);
              }
       bcnt=kp_regr.pack[inx].QTY;
      if(kp_regr.pack[inx].QTY < 0)
            bcnt = -bcnt;

       memset(kppack.DATA, 0, MAX_KP_CLM+1);
       mkrandom((long)bcnt,2,2);
       prt_buffer[3] = 0;
       pcode = kp_regr.pack[inx].PCODE;
       if (pcode >= S_PCODE) {
            pcode = pcode - S_PCODE;
            if (plu[pcode].desc[0] != 0){
                sprintf(kppack.DATA,"%s %s",prt_buffer,norm_str(plu[pcode].desc,MAX_PLU_DESC));
                }
            else {
                sprintf(kppack.DATA,"%s PLU %d",prt_buffer,pcode+1);
                }
            }
       else {
            if (dept[pcode].desc[0] != 0){
                sprintf(kppack.DATA,"%s %s",prt_buffer,norm_str(dept[pcode].desc,MAX_DEPT_DESC));
                }
            else {
                sprintf(kppack.DATA,"%s DEPT.%d",prt_buffer,pcode+1);
                }
            }
#if 0
       if (kp_regr.pack[inx].VD2)
               {
               kppack.RED = KP_RED;
               kppack.DATA[MAX_KP_CLM-3]='V';
               kppack.DATA[MAX_KP_CLM-2]='D';
               }
      else if (kp_regr.pack[inx].RTN)
#endif
      if (kp_regr.pack[inx].RTN)
               {
               kppack.RED = KP_RED;
               kppack.DATA[MAX_KP_CLM-3]='R';
               kppack.DATA[MAX_KP_CLM-2]='T';
               }

         else if(mode_id == VMODE)
               kppack.RED = KP_RED;


       if(port /* || kp_regr.pack[inx].VD2 */ || kp_regr.pack[inx].RTN )
        {
            kppack.DATA[MAX_KP_CLM-1]='\n';

            fill_ch(kppack.DATA,0x20);

        if(!port)
            kppack.DATA[MAX_KP_CLM-1] = 0;
        }

        kppack.LF = 0;
        if(kp_out(&kppack,port, 0) < 0)
               return(-1);

        (*dest_ttl) += kp_regr.pack[inx].AMT;
         return(1);
}

void con_kitem(char inx)
{
    char i;

    if(!SYS_OPT.OPT13_2)
        return;

    for(i = inx+1; i < kp_regr.pack_no; i++)
        {
        if(kp_regr.pack[i].SKIP)
            continue;

        if((kp_regr.pack[inx].PCODE == kp_regr.pack[i].PCODE)
            && (kp_regr.pack[inx].RTN == kp_regr.pack[i].RTN)
                        && (kp_regr.pack[i].VD2 == kp_regr.pack[inx].VD2) )
            {
            kp_regr.pack[inx].QTY += kp_regr.pack[i].QTY;
            kp_regr.pack[inx].AMT += kp_regr.pack[i].AMT;
            kp_regr.pack[i].SKIP = 1;
            }
        }
        return;
}

void vd_kitem()
{
   signed char i,k;
   int  base_qty;
   long base_amt;
    
   for(i = 0; i < kp_regr.pack_no; i++) {

        if(!kp_regr.pack[i].VD2)
            continue;

        base_amt = 0L; base_qty = 0;

        for(k = i-1; k >= 0; k--)
           {
           if(kp_regr.pack[k].SKIP || kp_regr.pack[k].VD2)
             continue;

            if((kp_regr.pack[k].PCODE == kp_regr.pack[i].PCODE)
            && (kp_regr.pack[k].RTN == kp_regr.pack[i].RTN))
//          && !kp_regr.pack[k].VD2 && kp_regr.pack[i].VD2 )
                   {
                   if(kp_regr.pack[k].QTY >= -(kp_regr.pack[i].QTY + base_qty))
                      {
                      kp_regr.pack[k].QTY += (kp_regr.pack[i].QTY + base_qty);
                      kp_regr.pack[k].AMT += (kp_regr.pack[i].AMT + base_amt);
                      kp_regr.pack[i].SKIP = 1;

                      if((kp_regr.pack[k].QTY == 0) &&
                                     (kp_regr.pack[k].AMT == 0L) )
                           kp_regr.pack[k].SKIP = 1;
                       break;
                       }
                    else {
                       base_amt += kp_regr.pack[k].AMT;
                       base_qty += kp_regr.pack[k].QTY;
                       kp_regr.pack[k].SKIP = 1;
                       }
                    }
                }

            }  
        return;
}

signed char mng_kp(char port)
{
    signed char    i,prt_f=0;
    long    dest_ttl = 0L;

    if(!kp_regr.pack_no) return(1);

    vd_kitem();

    for(i=0; i<kp_regr.pack_no; i++) {
        if(kp_regr.pack[i].SKIP)
            continue;
        con_kitem(i);
        if(!prt_f) {
            if(kp_head(port) < 0)
            return(-1);
            }
        prt_f = 1;
        if(mk_kpl(i, port,&dest_ttl) < 0)
            return(-1);
    }

    if(prt_f)
        i = kp_end(port,dest_ttl);
    else i =1;
    kp_regr.pack_no = 0;
    return(i);
}
void send_kp()
{
    if(SYS_OPT.OPT13_1 != 2)
        mng_kp(0);
    else {
        if(mng_kp(1) < 0)
            mng_kp(0);
         }
    memset(prt_buffer,0x20,sizeof(prt_buffer));
}
void send_kp1()
{
    if(SYS_OPT.OPT13_1 == 2) {
        mng_kp(1);
        }
    memset(prt_buffer,0x20,sizeof(prt_buffer));
}

void make_kp()
{
        UBYTE       indx;
        int     tcnt;

        if ((mode_id == VMODE) && !SYS_OPT.OPT13_4)
            return;

        if (train_flg && !SYS_OPT.OPT13_5)
            return;

        if (cupn_bit)
            return;

        if (vd1_bit){ /* ERRCORR CASE */
            kp_regr.pack_no--;
            return;
            }

        if (kp_regr.pack_no >= MAX_KP_CNT) {
            send_kp1();
            if (kp_regr.pack_no) 
                    return ;
            }

       indx=kp_regr.pack_no;
       if (pluon_bit) {
            kp_regr.pack[indx].PCODE=pcode+S_PCODE;
#if 0
            if (plu[pcode].desc[0] != 0){
                pmemcpy(kp_regr.pack[indx].DESC,plu[pcode].desc,MAX_PLU_DESC);
                }
            else {
                sprintf(kp_regr.pack[indx].DESC,s_plupd,pcode+1);
                }
#endif
            }
       else {
            kp_regr.pack[indx].PCODE=func;
#if 0
            if (dept[func].desc[0] != 0){
                pmemcpy(kp_regr.pack[indx].DESC,dept[func].desc,MAX_DEPT_DESC);
                }
            else {
                sprintf(kp_regr.pack[indx].DESC,s_deptpd,func+1);
                }
#endif
            }

    tcnt = (int)(upmul/100L);
    if(tcnt == 0)
        tcnt = 1;
    kp_regr.pack[indx].QTY = tcnt;

   kp_regr.pack[indx].AMT = nur;
   kp_regr.pack[indx].RED = kpred_bit;
   kp_regr.pack[indx].VD2 = vd2_bit;
   kp_regr.pack[indx].RTN = rtn_bit;
   kp_regr.pack[indx].SKIP = 0;

   kp_regr.pack_no++;

   return;
}

int read_time()
{
    int ret_time=0;

    rtc_read();
    ret_time=(int)rtcb_flg[5] * 1000;
    ret_time=ret_time+(int)rtcb_flg[4] * 100;
    ret_time=ret_time+(int)rtcb_flg[3] * 10;
    ret_time=ret_time+(int)rtcb_flg[2];
    return(ret_time);
}

