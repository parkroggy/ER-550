#include <stdio.h>
#include <er1io51.h>
#include <er1exmpx.h>
#ifndef BCDBG
#include  <exs03.h>
#else                                  /* BCDBG */
#include  <exdbg.h>
#endif                                 /* BCDBG */
#include <screen.h>

#define MAX_SHIFT   37

extern const UBYTE s_plupd[7];
extern const UBYTE s_scanall[17];
extern const UBYTE s_sys[4];
extern const UBYTE s_sns[4];
extern const UBYTE s_sya[4];
extern const UBYTE s_sna[4];
extern const UBYTE s_larrow[2];
extern const UBYTE s_ttblp[21];
extern const UBYTE s_ttbls[21];
extern const UBYTE s_ttblsp[23];
extern const UBYTE s_space[2];
extern const UBYTE s_pfkey[21];
extern const UBYTE s_fkscan[19];
extern const UBYTE s_bescan[12];
extern const UBYTE s_fkpgm[21];
extern const UBYTE s_bepgm[15];
extern const UBYTE s_allscan[13];
extern const UBYTE s_adptscan[15];
extern const UBYTE s_aclkscan[15];
extern const UBYTE s_taxpd[7];

const char engtbl[10] = {'A', 'D', 'G', 'J', 'M', 'P', 'T', 'W', 0, ' '};
const char eng_sft[MAX_SHIFT][2] = {
              {' ', '.'}, {'.', '0'}, {'0', ' '},
              {'A', 'B'}, {'B', 'C'}, {'C', '2'}, {'2', 'A'},
              {'D', 'E'}, {'E', 'F'}, {'F', '3'}, {'3', 'D'},
              {'G', 'H'}, {'H', 'I'}, {'I', '4'}, {'4', 'G'},
              {'J', 'K'}, {'K', 'L'}, {'L', '5'}, {'5', 'J'},
              {'M', 'N'}, {'N', 'O'}, {'O', '6'}, {'6', 'M'},
              {'P', 'Q'}, {'Q', 'R'}, {'R', 'S'}, {'S', '7'}, {'7', 'P'},
              {'T', 'U'}, {'U', 'V'}, {'V', '8'}, {'8', 'T'},
              {'W', 'X'}, {'X', 'Y'}, {'Y', 'Z'}, {'Z', '9'}, {'9', 'W'}};

const char oth_tbl[MAX_SPECIAL] =
   {'0', '1', '!', '@', '#', '$', '%', '^',
    '&', '*', '(', ')', '-', '_', '+', '=',
    '`', '[', ']', '\\',':', ';', '"', '\'',
    '<', ',', '>', '.', '?', '/', 'œ', 'î'};

extern const UBYTE s_blanks[21];
extern void ej_prn();
extern void mk_tdmsg( unsigned char *desc, long amt, int x, int y, int end);
extern void sv_str(UBYTE x, UBYTE y, UBYTE *str);
extern void sv_lcd1();
extern void dsp_str(UBYTE x, UBYTE y, UBYTE *str);
extern void dis9_out(char what);
extern void date_prn();
extern void des_prn();
extern void desc2pbuf();
extern void dsp_logo(char type);
extern void endlogo();
//PKR0624 extern void initseq();
//PKR0624 extern void inidtx();
extern void logo_nur(char type);
extern void mkrandom(long value,char ofst,char st);
extern void mkfunc();
extern void mkdsp();
extern void mkdnur(char inf);
extern void mkdeach(char type);
extern void mkline();
extern void mkstar();
extern void start_prn();
//PKR0624 extern void prn();
extern void p_init();
extern void sep_prn();
extern void time_prn();
/*extern void train_onoff(char type);*/
extern char tbl_act();
extern void make_desc(char *temps,char max);
extern char level_err();
extern void load_dpstat();
extern void prn_dtlogo();       /* tax1 / tax2 / tax3 / tax4 /tax1&3 */
extern void xlogo_nur(char type);
extern void xsep_prn();
extern void dsp_menu();
extern void start_menu(UBYTE no);
extern void l2c(long, unsigned char *, UBYTE);
extern void pmemcpy(UBYTE *, UBYTE *, unsigned int);
extern void cmemcpy(UBYTE *, UBYTE *, UBYTE);
extern int  cnv_tm(int time);
extern void prn_clksub(UBYTE *buffer, int time1, UBYTE prn_f);
extern int time_diff(int, int);
extern int time_add(int, int);

void sub_pso2();
void sub_pso3();
void sub_pso6();
void dpgm_chr(UBYTE);

const UBYTE mon_day[2][12] = {{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
                      {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

/*--------------------------------------------------------*/
char time_write()    /* write to rtc chip rp5c15   5 ncnt */
{
 if( (rtcb_flg[1] > 5) || (rtcb_flg[3] > 2)
     || ((rtcb_flg[3] >= 2) && (rtcb_flg[2] > 3)) ) return(FAIL);

 rtcb_flg[7]=0x04;
 rtc_write();        /* rtc write target routine */
 return(SUCCESS);
}
/*--------------------------------------------------------*/
char date_write()    /* write to rtc chip rp5c15 */
{
 if (rtcb_flg[2] > 3 || rtcb_flg[4] > 1 ||
    (rtcb_flg[2] == 0 && rtcb_flg[1] == 0) ||
    (rtcb_flg[4] == 0 && rtcb_flg[3] == 0) ||
    (rtcb_flg[4] >= 1 && rtcb_flg[3] > 2) ||
    (rtcb_flg[2] >= 3 && rtcb_flg[1] > 1)) return(FAIL);

 rtcb_flg[7]=0x07;

 nur=rtcb_flg[6]*10+rtcb_flg[5];
 /************************************/
 /* 1988 2000 leap year              */
 /* 1901 - 2000 == 2001 - 2099       */
 /************************************/
 rtcb_flg[8]=nur%4; /* current year is leap year */

 rtc_write();          /* rtc write target routine */
 return(SUCCESS);
}

void make_taxtbl(UBYTE taxno)
{
    UBYTE i;
    long total;

    for(i=0,total=tax_table[taxno].taxnamt;i<tax_table[taxno].nrbreak;i++)
        total += tax_table[taxno].ttable[i];
    tax_table[taxno].nrtotal = total;

    for(i=0,total=0;i<tax_table[taxno].rbreak;i++)
        total += tax_table[taxno].ttable[tax_table[taxno].nrbreak+i];
    tax_table[taxno].rtotal = total;
}

void dsp_long(long k, UBYTE line_no, UBYTE sv, UBYTE mask, UBYTE end)
{
    UBYTE x;

    l2c(k, &lcdbuf[1],mask);
    lcdbuf[0] = 0x20;
    x = strlen(lcdbuf);
    lcdbuf[x] = 0x20;
    lcdbuf[x+1] = 0;
    x = end-x;
    if(sv)
        sv_str(x, line_no, lcdbuf);
    else
        dsp_str(x, line_no, lcdbuf);
}

void make_time(UBYTE *str, int tm)
{
    str[0] = (tm / 1000) + 0x30;
    tm %= 1000;
    str[1] = (tm / 100) + 0x30;
    tm %= 100;
    str[3] = (tm / 10) + 0x30;
    str[4] = (tm % 10) + 0x30;
    str[2] = ':';
    str[5] = 0;
}

void make_date(UBYTE *str, long dt)
{
    str[0] = (dt / 100000) + 0x30;
    dt %= 100000;
    str[1] = (dt / 10000) + 0x30;
    dt %= 10000;
    str[3] = (dt / 1000) + 0x30;
    dt %= 1000;
    str[4] = (dt / 100) + 0x30;
    dt %= 100;
    str[6] = (dt / 10) + 0x30;
    str[7] = (dt % 10) + 0x30;
    str[2] = str[5] = '.';
    str[8] = 0;
}

void dsp_cont(UBYTE sv)
{
    int x, offset;
    long k;
    UBYTE line_no, type, buf[30], mask, *ptr, max_len;

    offset = opt_pgm[sys_pgno].item[sys_para].offset;
    line_no = opt_pgm[sys_pgno].item[sys_para].line_no;
    type = opt_pgm[sys_pgno].item[sys_para].type;
    mask = opt_pgm[sys_pgno].item[sys_para].bit_mask;
    max_len = opt_pgm[sys_pgno].item[sys_para].max_len;

    switch(type)
        {
        case TP_BIT :
            if(opt_ptr[offset] & mask)
                {
                k = 1;
                if(sv)
                    sv_str(MAX_CLM-3, line_no, s_sys);
                else
                    dsp_str(MAX_CLM-3, line_no, s_sys);
                }
            else
                {
                k = 0;
                if(sv)
                    sv_str(MAX_CLM-3, line_no, s_sns);
                else
                    dsp_str(MAX_CLM-3, line_no, s_sns);
                }
            break;
        case TP_BYTE :
            k = (int)(opt_ptr[offset]);
            sprintf(lcdbuf, " %d ", (UBYTE)k);
            x = MAX_CLM-strlen(lcdbuf);
            if(sv)
                sv_str(x, line_no, lcdbuf);
            else
                dsp_str(x, line_no, lcdbuf);
            break;
        case TP_WORD :
        case TP_TARE :
#ifndef BCDBG
            k = opt_ptr[offset] * 0x100 +
                    opt_ptr[offset + 1];
#else                                  /* BCDBG */
            k = opt_ptr[offset + 1] * 0x100 +
                    opt_ptr[offset];
#endif                                 /* BCDBG */
            if(paddr == PADD_TARE)
                dsp_long(k, line_no, sv, 3, mask);
            else
                dsp_long(k, line_no, sv, 0, mask);
            break;
        case TP_TIME :
#ifndef BCDBG
            k = opt_ptr[offset] * 0x100 +
                    opt_ptr[offset + 1];
#else                                  /* BCDBG */
            k = opt_ptr[offset + 1] * 0x100 +
                    opt_ptr[offset];
#endif                                 /* BCDBG */
            make_time(lcdbuf, (int)k);
            x = mask-strlen(lcdbuf);
            if(sv)
                sv_str(x, line_no, lcdbuf);
            else
                dsp_str(x, line_no, lcdbuf);
            break;
        case TP_REAL :
        case TP_DLONG :
        case TP_ELONG :
        case TP_LONG :
        case TP_DATE :
#ifndef BCDBG
            ptr = &opt_ptr[offset];
            k = (long)(*ptr) * 0x1000000l;      ptr++;
            k = k + (long)(*ptr) * 0x10000l;    ptr++;
            k = k + (long)(*ptr) * 0x100l;      ptr++;
            k = k + (long)(*ptr);               ptr++;
#else                                  /* BCDBG */
            k = (long)(opt_ptr[offset + 3]) * 0x1000000l +
                    (long)(opt_ptr[offset + 2]) * 0x10000l +
                    (long)(opt_ptr[offset + 1]) * 0x100l +
                    (long)(opt_ptr[offset]);
#endif                                 /* BCDBG */
            if(type == TP_REAL)
                dsp_long(k, line_no, sv, mask, MAX_CLM - 1);
            else if(type == TP_DLONG)
                dsp_long(k, line_no, sv, SYS_OPT.OPT18_1, MAX_CLM - 1);
            else if(type == TP_ELONG)
                {                      /* Gallonage */
                if((opt_ptr[17] & 0x20) || (pdcnt == 3))
                    {
                    pdcnt = 3;
                    dsp_long(k, line_no, sv, 3, MAX_CLM - 1);
                    }
                else
                    dsp_long(k, line_no, sv, SYS_OPT.OPT18_1, MAX_CLM - 1);
                }
            else if(type == TP_LONG)
                dsp_long(k, line_no, sv, 0, mask);
            else
                {
                make_date(lcdbuf, k);
                x = mask-strlen(lcdbuf);
                if(sv)
                    sv_str(x, line_no, lcdbuf);
                else
                    dsp_str(x, line_no, lcdbuf);
                }
            break;
        case TP_STRING :
            memset(buf, 0, 30);
            if((sys_para == sys_line) && (bak_paddr == 99))
                pmemcpy(buf, msg_buf, max_len);
            else
                pmemcpy(buf, &opt_ptr[offset], max_len);
            if(sv)
                sv_str(opt_pgm[sys_pgno].item[sys_para].bit_mask, line_no, buf);
            else
                dsp_str(opt_pgm[sys_pgno].item[sys_para].bit_mask, line_no, buf);
            if(!sv &&(sys_para == sys_line))
                {
                flg_logo = flg_caps = 1;
                flg_dbl = 0;
                chr_idx = sft_idx = last_chr = 0;
                }
            break;
        }
    if(!sv && (sys_para == sys_line))
        {
        sys_lno = line_no;
        if((type == TP_TIME) || (type == TP_WORD) || (type == TP_TARE) ||
                (type == TP_LONG) || (type == TP_DATE))
            dsp_str(mask, sys_lno, s_larrow);
        else
            dsp_str(MAX_CLM-1, sys_lno, s_larrow);
        sys_type = type;
        sys_cont = k;
        sys_len = max_len;
        sys_mask = mask;
        }
}

void pttl_sub(UBYTE idx)
{
    cmemcpy(lcdbuf,code_mem->pttl_str[idx],21);
    dsp_str(0,0,lcdbuf);
}

void dsp_pttl()                        /* ------------------------------- */
{
    dsp_str(0,0,s_blanks);
    if(paddr == PADD_SYSTEM)
        {
        sprintf(lcdbuf, "SYSTEM OPTION pg %d", sys_pgno+1);
        dsp_str(1,0,lcdbuf);
        }
    else if(paddr == PADD_PRINT)
        {
        sprintf(lcdbuf, "PRINT OPTION pg %d", sys_pgno+1);
        dsp_str(1,0,lcdbuf);
        }
    else if(paddr == PADD_PER)
        {
        sprintf(lcdbuf, "%c%d PROGRAMMING", 0x25, ppluno+1);
        dsp_str(2,0,lcdbuf);
        }
    else if(paddr == PADD_CNV)
        {
        sprintf(lcdbuf, "CONVERSION #%d PROG", ppluno+1);
        dsp_str(1,0,lcdbuf);
        }
    else if((paddr == PADD_PLU) || (paddr == PADD_INVP))
        {
        sprintf(lcdbuf, "PLU #%d PROGRAMMING", ppluno);
        dsp_str(0,0,lcdbuf);
        }
    else if((paddr == PADD_DEPT) || (paddr == PADD_INVD))
        {
        sprintf(lcdbuf, "DEPT #%d PROGRAMMING", ppluno);
        dsp_str(0,0,lcdbuf);
        }
    else if(paddr == PADD_CLK)
        {
        sprintf(lcdbuf, "CLERK #%d PROGRAMMING", ppluno);
        dsp_str(0,0,lcdbuf);
        }
    else if(paddr == PADD_MISC)
        {
        sprintf(lcdbuf, "MISC TEND%d PROG pg %d", ppluno+1, sys_pgno+1);
        dsp_str(0,0,lcdbuf);
        }
    else if(paddr == PADD_TAX0)   pttl_sub(0);
    else if(paddr <= PADD_TAX3)
        {
        sprintf(lcdbuf, "TAX #%d PROGRAMMING", ppluno);
        dsp_str(1,0,lcdbuf);
        }
    else if(paddr == PADD_DTM)    pttl_sub(1);
    else if(paddr == PADD_DESC)   pttl_sub(2);
    else if((paddr == PADD_CNO) || (paddr == PADD_CNO2))    pttl_sub(3);
    else if(paddr == PADD_DNO)    pttl_sub(4);
    else if(paddr == PADD_DNO2)   pttl_sub(4);
    else if(paddr == PADD_PNO)    pttl_sub(5);
    else if(paddr == PADD_PNO2)   pttl_sub(5);
    else if(paddr == PADD_NS)     pttl_sub(6);
    else if(paddr == PADD_CASH)   pttl_sub(7);
    else if(paddr == PADD_CHECK)  pttl_sub(8);
    else if(paddr == PADD_VOID)   pttl_sub(9);
    else if(paddr == PADD_RETURN) pttl_sub(10);
    else if(paddr == PADD_CANCEL) pttl_sub(11);
    else if(paddr == PADD_PO)     pttl_sub(12);
    else if(paddr == PADD_RA)     pttl_sub(13);
    else if(paddr == PADD_SFT)    pttl_sub(14);
    else if(paddr == PADD_ALPH)   pttl_sub(15);
    else if(paddr == PADD_CIO)    pttl_sub(16);
    else if(paddr == PADD_GRP)    pttl_sub(17);
    else if(paddr == PADD_SCALE)  pttl_sub(18);
    else if(paddr == PADD_TARE)   pttl_sub(19);
}

void prn_sys_pg()
{
    UBYTE i;

    for(i=0;i<opt_pgm[sys_pgno].str_no;i++)
        {
        cmemcpy(lcdbuf,code_mem->strb[opt_pgm[sys_pgno].strb[i]],21);
        sv_str(0,i+1,lcdbuf);
        }
    for(i=0;i<opt_pgm[sys_pgno].itm_no;i++)
        {
        sys_para = i;
        dsp_cont(1);
        }
}

void dsp_sys_pg()
{
    UBYTE i;

    dsp_pttl();
    for(i=0;i<opt_pgm[sys_pgno].str_no;i++)
        {
        cmemcpy(lcdbuf,code_mem->strb[opt_pgm[sys_pgno].strb[i]],21);
        dsp_str(0,i+1,lcdbuf);
        }
    for(;i<MAX_LINE-1;i++)
        dsp_str(0,i+1,s_blanks);
    for(i=0;i<opt_pgm[sys_pgno].itm_no;i++)
        {
        sys_para = i;
        dsp_cont(0);
        }
    if(paddr == PADD_CIO)
        {
        prn_clksub(lcdbuf, CLKIO[ppluno-1].W_TIME, 0);
        dsp_str(1,7,lcdbuf);
        }
    if(paddr != PADD_ALPH)
        {
        pop_lcd = 0;
        sv_lcd1();
        }
}

void p_yes_no()
{
    int x;

    if(sys_type == TP_BIT)
        {
        sys_cont = !sys_cont;
        x = MAX_CLM - 3;
        if(sys_cont)
            dsp_str(x, opt_pgm[sys_pgno].item[sys_line].line_no, s_sya);
        else
            dsp_str(x, opt_pgm[sys_pgno].item[sys_line].line_no, s_sna);
        return;
        }
}

void p_nclr()
{
    nur = 0;
    dcnt = ncnt = 0;
    kdec_bit = 0;
}

char is_mpage()                        /* --------------------------------- */
{
    switch(paddr)
        {
        case PADD_SYSTEM :
        case PADD_TAX1  :
        case PADD_PRINT :
        case PADD_PLU   :
        case PADD_INVP  :
        case PADD_INVD  :
        case PADD_DEPT  :
        case PADD_CLK   :
        case PADD_DESC  :
        case PADD_PER   :
        case PADD_ALPH  :
        case PADD_NS    :
        case PADD_CASH  :
        case PADD_CHECK :
        case PADD_MISC  :
        case PADD_SCALE :
        case PADD_VOID  :
        case PADD_CIO   :
        case PADD_GRP   :
            return 1;
        default :
            return 0;
        }
}

UBYTE week_day(int year, int month, int day)
{
    long chk;
    int i, j;

    if((month > 12) || (year < 1993) || (year > 2099))
        return 99;

    j = year%4 == 0;

    if(day > mon_day[j][month-1])
        return 99;

    chk = (year - 1993) * 365 + (year - 1993) / 4;

    for(i=0;i<month-1;i++)
        {
        chk += mon_day[j][i];
        }
    chk += day;

    return (int)((chk+4) % 7);
}

void st_pgm()
{
    paddr = 0;
    sys_lno = MAX_LINE - 1;
    sys_len = 8;
    start_menu(MENU_PGM);
}

void load_dtm()
{
    rtc_read();
    dtm_buf.time = rtcb_flg[2] + rtcb_flg[3] * 10 +
            rtcb_flg[4] * 100 + rtcb_flg[5] * 1000;
    dtm_buf.date = rtcb_flg[11] + rtcb_flg[12] * 10l;
    dtm_buf.date += rtcb_flg[7] * 100l + rtcb_flg[8] * 1000l;
    dtm_buf.date += rtcb_flg[9] * 10000l + rtcb_flg[10] * 100000l;
}

void set_dtm()
{
    int year, month, day, y2;

    y2 = dtm_buf.time;
    rtcb_flg[0] = y2 % 10;
    rtcb_flg[1] = (y2 % 100) / 10;
    rtcb_flg[2] = (y2 % 1000) / 100;
    rtcb_flg[3] = (y2 % 10000) / 1000;
    time_write();

    year = dtm_buf.date % 100l;
    if(year < 96)
        y2 = year + 2000;
    else
        y2 = year + 1900;
    day = (dtm_buf.date % 10000l) / 100l;
    month = (dtm_buf.date % 1000000l) / 10000l;
    rtcb_flg[0] = week_day(y2, month, day);
    rtcb_flg[1] = day % 10;
    rtcb_flg[2] = day / 10;
    rtcb_flg[3] = month % 10;
    rtcb_flg[4] = month / 10;
    rtcb_flg[5] = year % 10;
    rtcb_flg[6] = year / 10;
    date_write();
}

void dsp_taxtbl()
{
    UBYTE i, j;
    long amt;

    dsp_str(0,0,s_ttblp);
    dsp_str(0,1,s_ttbls);
    j = tax_brk + 3;
    amt = tax_table[ppluno-1].taxnamt;
    for(i=2;i<j;i++)
        {
        if(i == 2)
            {
            if(tax_idx == 0)
                {
                dsp_str(0,i,s_blanks);
                dsp_long(0, i, 0, 2, 5);
                dsp_long(0, i, 0, 2, 12);
                dsp_long(amt, i, 0, 2, MAX_CLM - 1);
                dsp_str(13, i, "-");
                }
            }
        else if((i-2 >= tax_idx) && (i < MAX_LINE + tax_idx))
            {
            dsp_str(0,i-tax_idx,s_blanks);
            dsp_long(tax_table[ppluno-1].taxfamt + i - 3, i-tax_idx, 0, 2, 5);
            dsp_long(amt + 1, i-tax_idx, 0, 2, 12);
            amt += tax_table[ppluno-1].ttable[i-3];
            dsp_long(amt, i-tax_idx, 0, 2, MAX_CLM - 1);
            dsp_str(13, i-tax_idx, "-");
            }
        else
            amt += tax_table[ppluno-1].ttable[i-3];
        }
    for(;i<MAX_LINE+tax_idx;i++)
        dsp_str(0,i-tax_idx,s_blanks);
}

UBYTE chk_date(long mmddyy)
{
    int yy, mm, dd, mx;

    yy = (int)(mmddyy % 100);
    if(yy < 96)
        yy += 2000;
    else
        yy += 1900;
    mm = (int)(mmddyy / 10000);
    dd = (int)((mmddyy / 100) % 100);
    switch(mm)
        {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            mx = 31;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            mx = 30;
            break;
        case 2:
            if(yy % 4)
                mx = 28;
            else
                mx = 29;
            break;
        }
    if(dd > mx)
        return 0;
    return 1;
}

UBYTE pe_sub()
{
    int offset;
    UBYTE mask, type, i, x;

    mask = opt_pgm[sys_pgno].item[sys_line].bit_mask;
    type = opt_pgm[sys_pgno].item[sys_line].type;
    offset = opt_pgm[sys_pgno].item[sys_line].offset;

    if((type != TP_BYTE) || (nur >= mask))
        {
        switch(type)
            {
            case TP_BIT :
                if(sys_cont)
                    opt_ptr[offset] |= mask;
                else
                    opt_ptr[offset] &= (~mask);
                break;
            case TP_BYTE :
                if(ncnt)
                    {
                    if(nur > opt_pgm[sys_pgno].item[sys_line].max_inp)
                        return 0;
                    opt_ptr[offset] = (UBYTE)nur;
                    }
                break;
            case TP_WORD :
            case TP_TARE :
            case TP_TIME :
                if(ncnt)
                    {
                    if((paddr == PADD_TARE) && dcnt)
                        {
                        if(dcnt < 3)
                            {
                            for(i=dcnt;i<3;i++)
                                nur *= 10l;
                            }
                        else
                            {
                            for(i=3;i<dcnt;i++)
                                nur /= 10l;
                            }
                        }
                    if(nur > opt_pgm[sys_pgno].item[sys_line].max_inp)
                        return 0;
#ifndef BCDBG
                    opt_ptr[offset] = (UBYTE)(nur / 0x100);
                    opt_ptr[offset + 1] = (UBYTE)(nur % 0x100);
#else                                  /* BCDBG */
                    opt_ptr[offset + 1] = (UBYTE)(nur / 0x100);
                    opt_ptr[offset] = (UBYTE)(nur % 0x100);
#endif                                 /* BCDBG */
                    if(paddr == PADD_TARE)
                        dsp_long(nur, opt_pgm[sys_pgno].item[sys_line].line_no, 0, 3, MAX_CLM - 1);
                    }
                break;
            case TP_REAL :
            case TP_DLONG :
            case TP_ELONG :
            case TP_LONG :
            case TP_DATE :
                if(ncnt)
                    {
                    if(((type == TP_REAL) || (type == TP_DLONG) || (type == TP_ELONG))
                            && kdec_bit)
                        {
                        if(type == TP_DLONG)
                            mask = SYS_OPT.OPT18_1;
                        else if(type == TP_ELONG)
                            {
                            if((opt_ptr[17] & 0x20) || dcnt == 3)
                                mask = pdcnt = 3;
                            else
                                mask = pdcnt = SYS_OPT.OPT18_1;
                            }
                        if(dcnt < mask)
                            {
                            for(i=dcnt;i<mask;i++)
                                nur *= 10l;
                            }
                        else
                            {
                            for(i=mask;i<dcnt;i++)
                                nur /= 10l;
                            }
                        }
                    else if(type == TP_ELONG)
                        {
                        if(opt_ptr[17] & 0x20)
                            pdcnt = 3;
                        else
                            pdcnt = SYS_OPT.OPT18_1;
                        }
                    if(nur > opt_pgm[sys_pgno].item[sys_line].max_inp)
                        return 0;
                    if(type == TP_DATE)
                        {
                        if(!chk_date(nur))
                            return 0;
                        }
#ifndef BCDBG
                    opt_ptr[offset] = (UBYTE)(nur / 0x1000000l);
                    opt_ptr[offset + 1] = (UBYTE)((nur % 0x1000000l) / 0x10000l);
                    opt_ptr[offset + 2] = (UBYTE)((nur % 0x10000l) / 0x100l);
                    opt_ptr[offset + 3] = (UBYTE)(nur % 0x100l);
#else                                  /* BCDBG */
                    opt_ptr[offset + 3] = (UBYTE)(nur / 0x1000000l);
                    opt_ptr[offset + 2] = (UBYTE)((nur % 0x1000000l) / 0x10000l);
                    opt_ptr[offset + 1] = (UBYTE)((nur % 0x10000l) / 0x100l);
                    opt_ptr[offset] = (UBYTE)(nur % 0x100l);
#endif                                 /* BCDBG */
                    if(type == TP_REAL)
                        dsp_long(nur, opt_pgm[sys_pgno].item[sys_line].line_no, 0, mask, MAX_CLM - 1);
                    else if(type == TP_DLONG)
                        dsp_long(nur, opt_pgm[sys_pgno].item[sys_line].line_no, 0, SYS_OPT.OPT18_1, MAX_CLM - 1);
                    else if(type == TP_ELONG)
                        {              /* Gallonage */
                        if(opt_ptr[17] & 0x20)
                            pdcnt = 3;
                        dsp_long(nur, opt_pgm[sys_pgno].item[sys_line].line_no, 0, pdcnt, MAX_CLM - 1);
                        }
                    else if(type == TP_LONG)
                        dsp_long(nur, opt_pgm[sys_pgno].item[sys_line].line_no, 0, 0, mask);
                    else
                        {
                        make_date(lcdbuf, nur);
                        x = mask-strlen(lcdbuf);
                        dsp_str(x, opt_pgm[sys_pgno].item[sys_line].line_no, lcdbuf);
                        }
                    }
                break;
            case TP_STRING :
                if(flg_logo > 1)
                    {
                    if(sft_idx)
                        {
                        sft_idx = 0;
                        chr_idx++;
                        if(flg_dbl)
                            {
                            msg_buf[chr_idx] = 0x11;
                            chr_idx++;
                            }
                        return 1;
                        }
                    memset(&opt_ptr[offset], 0, opt_pgm[sys_pgno].item[sys_line].max_len);
                    pmemcpy(&opt_ptr[offset], msg_buf, chr_idx);
                    memset(msg_buf, 0, MAX_MSG_DESC + 1);
                    }
                flg_logo = 0;
                break;
            }
        }
    else if(ncnt)
        return 0;
    if((type == TP_TIME) || (type == TP_WORD) || (type == TP_TARE) ||
            (type == TP_LONG) || (type == TP_DATE))
        dsp_str(mask, opt_pgm[sys_pgno].item[sys_line].line_no, s_space);
    else
        dsp_str(MAX_CLM-1, opt_pgm[sys_pgno].item[sys_line].line_no, s_space);
    sys_line++;
    if(sys_line >= opt_pgm[sys_pgno].itm_no)
        {
        i = 99;
        sys_line = 0;
        }
    else
        i = sys_line;
    sys_para = sys_line;
    if((paddr == PADD_TAX0) && !flg_logo && (sys_line == 1))
        {
        tax_tmp[1] = tax_table[tax_tmp[0]-1].taxstat & 0x0f;
        pmemcpy(&tax_tmp[2], tax_table[tax_tmp[0]-1].desc, MAX_TAX_DESC);
        dsp_sys_pg();
        }
    else if(paddr != PADD_TAX3)
        dsp_cont(0);
    sys_line = i;
    p_nclr();
    return 1;
}

void sttl_sub(UBYTE idx)
{
    cmemcpy(prt_buffer,code_mem->sttl_str[idx],25);
    ej_prn();
    mkline();
}

void pgm_endlogo()
{
    if(menu_no == MENU_PGMS)
        {
        endlogo();
        paddr = 0;
        start_menu(MENU_PGMS);
        }
    else
        {
        ej_prn();
        mkline();
        ej_prn();
        }
}

void scan_opt()
{
    UBYTE i;

    if(end_mark == 1)
        {
        start_prn();
        if(paddr == PADD_SYSTEM)
            i = 0;
        else if(paddr == PADD_PRINT)
            i = 1;
        else if(paddr == PADD_PLU)
            i = 2;
        else if(paddr == PADD_DEPT)
            i = 3;
        else if(paddr == PADD_CLK)
            i = 4;
        else if(paddr == PADD_GRP)
            i = 8;
        else if(paddr == PADD_TARE)
            i = 9;
        else
            i = 6;
        sttl_sub(i);
        }

    pmemcpy(dsp_bak[0],dsp_buf[0],MAX_LINE*(MAX_CLM+1));

    for(sys_pgno=0;sys_pgno<max_page;sys_pgno++)
        {
        memset(dsp_buf[0],0x20,MAX_LINE*(MAX_CLM+1));
        prn_sys_pg();
        for(i=0;i<opt_pgm[sys_pgno].str_no;i++)
            {
            pmemcpy(prt_buffer, dsp_buf[i+1], 20);
            ej_prn();
            }
        }

    if(paddr >= PADD_PER)
        {
        pfkey_bit = 1;
        ej_prn();
        pgm_flg = 1;
        }
    else switch(paddr)
        {
        case PADD_DEPT :
            if(!sall_bit)
                sub_pso3();
            ej_prn();
            pgm_flg = 1;
            break;
        case PADD_PLU :
            if(!sall_bit)
                sub_pso2();
            ej_prn();
            pgm_flg = 1;
            break;
        case PADD_CLK :
            if(!sall_bit)
                sub_pso6();
            ej_prn();
            pgm_flg = 1;
            break;
        default :
            pgm_endlogo();
        }
    pmemcpy(dsp_buf[0],dsp_bak[0],MAX_LINE*(MAX_CLM+1));
}

void call_sub()
{
    if(menu_no != MENU_PGM)
        scan_opt();
    else
        dsp_sys_pg();
}

void sub_pso0()
{
    paddr = PADD_SYSTEM;
    sys_pgno = 0;
    sys_line = 0;
    opt_pgm = sys_pgm;
    opt_ptr = (UBYTE*)&SYS_OPT;
    max_page = MAX_SYS_OPT;
    call_sub();
}

void sub_pso1(UBYTE taxno)
{
    paddr = PADD_TAX0;
    sys_pgno = 0;
    sys_line = 0;
    tax_tmp[0] = taxno;
    tax_tmp[1] = tax_table[taxno-1].taxstat & 0x0f;
    pmemcpy(&tax_tmp[2], tax_table[taxno-1].desc, MAX_TAX_DESC);
    opt_pgm = tax_pgm0;
    opt_ptr = (unsigned char*)&tax_tmp[0];
    max_page = MAX_TAX0_OPT;
    dsp_sys_pg();
}

void sub_pso2()
{
    paddr = PADD_PNO;
    ppluno = 0;
    sys_pgno = 0;
    sys_line = 0;
    opt_pgm = pno_pgm;
    opt_ptr = (unsigned char*)&ppluno;
    max_page = MAX_PNO_OPT;
    dsp_sys_pg();
    sys_lno = 7;
    if(menu_no == MENU_PGMS)
        {
        dsp_str(0,6,s_scanall);
        pop_lcd = 0;
        sv_lcd1();
        }
}

void sub_pso3()
{
    paddr = PADD_DNO;
    ppluno = 0;
    sys_pgno = 0;
    sys_line = 0;
    opt_pgm = dno_pgm;
    opt_ptr = (unsigned char*)&ppluno;
    max_page = MAX_DNO_OPT;
    dsp_sys_pg();
    if(menu_no == MENU_PGMS)
        {
        dsp_str(0,6,s_scanall);
        pop_lcd = 0;
        sv_lcd1();
        }
}

void sub_pso4()
{
    paddr = PADD_DTM;
    memset((unsigned char*)&dtm_buf, 0, sizeof(dtm_buf));
    load_dtm();
    ppluno = 0;
    sys_pgno = 0;
    sys_line = 0;
    opt_pgm = dtm_pgm;
    opt_ptr = (unsigned char*)&dtm_buf;
    max_page = MAX_DTM_OPT;
    dsp_sys_pg();
}

void sub_pso6()
{
    paddr = PADD_CNO;
    sall_bit = 0;
    ppluno = 0;
    sys_pgno = 0;
    sys_line = 0;
    opt_pgm = cno_pgm;
    opt_ptr = (unsigned char*)&ppluno;
    max_page = MAX_CNO_OPT;
    dsp_sys_pg();
    sys_lno = 7;
    if(menu_no == MENU_PGMS)
        {
        dsp_str(0,6,s_scanall);
        pop_lcd = 0;
        sv_lcd1();
        }
}

void sub_pso8()
{
    UBYTE i;

    if(menu_no != MENU_PGM)
        {
        if(end_mark == 1)
            start_prn();
        sttl_sub(5);
        for(i=0;i<MAX_MSG;i++)
            {
            sprintf(prt_buffer, "MESSAGE %d :", i+1);
            ej_prn();
            sprintf(prt_buffer, messdec[i]);
            ej_prn();
            }
        }
    else
        {
        paddr = PADD_DESC;
        sys_pgno = 0;
        sys_line = 0;
        opt_pgm = msg_pgm;
        opt_ptr = (unsigned char*)messdec[0];
        max_page = MAX_MSG_OPT;
        dsp_sys_pg();
        }
}

void sub_pso9()
{
    paddr = PADD_PRINT;
    sys_pgno = 0;
    sys_line = 0;
    opt_pgm = prt_pgm;
    opt_ptr = (UBYTE*)&PRT_OPT;
    max_page = MAX_PRT_OPT;
    call_sub();
}

void sub_psoA()
{
    pfkey_bit = 1;
    clr_lcd();
    dsp_str(0,2,s_pfkey);
    if(menu_no == MENU_PGMS)
        {
        dsp_str(0,0,s_fkscan);
        dsp_str(0,3,s_bescan);
        }
    else
        {
        dsp_str(0,0,s_fkpgm);
        dsp_str(0,3,s_bepgm);
        }
}

void sub_pso20()
{
    paddr = PADD_PLU;
    sys_pgno = 0;
    sys_line = 0;
    if(SYS_OPT.OPT3_3)
        opt_pgm = plu_pgm2;
    else
        opt_pgm = plu_pgm;
    opt_ptr = (unsigned char*)&plu[ppluno-1];
    if(plu[ppluno-1].status[1] & 0x20)  /* gas_bit */
        pdcnt = 3;
    else
        pdcnt = SYS_OPT.OPT18_1;
    max_page = MAX_PLU_OPT;
    call_sub();
}

UBYTE is_dft_plu()
{
    UBYTE desc[MAX_PLU_DESC];

    memset(desc, 0, MAX_PLU_DESC);
    sprintf(desc,s_plupd,ppluno);
    if((memcmp((void *)desc, (void *)plu[ppluno-1].desc, MAX_PLU_DESC) == 0) &&
            (plu[ppluno-1].price == 0) &&
            (plu[ppluno-1].status[0] == 0) &&
            (plu[ppluno-1].status[1] == 0) &&
            (plu[ppluno-1].link_dept == 1) &&
            (plu[ppluno-1].link_plu == 0))
        return 1;
    return 0;
}

void all_plu()
{
    if(menu_no == MENU_PGMS)
        start_prn();
    sprintf(prt_buffer,s_allscan);
    ej_prn();
    mkline();
    for(ppluno=1;ppluno<=MAX_PLU;ppluno++)
        {
        if(is_dft_plu())
            continue;
        sub_pso20();
        }
    sall_bit = 0;
    endlogo();
    paddr = 0;
    if(menu_no == MENU_PGMS)
        start_menu(MENU_PGMS);
}

void sub_pso21()
{
    paddr = PADD_DEPT;
    sys_pgno = 0;
    sys_line = 0;
    if(SYS_OPT.OPT3_3)
        opt_pgm = dept_pgm2;
    else
        opt_pgm = dept_pgm;
    opt_ptr = (unsigned char*)&dept[ppluno-1];
    if(dept[ppluno-1].status[1] & 0x20)  /* gas_bit */
        pdcnt = 3;
    else
        pdcnt = SYS_OPT.OPT18_1;
    max_page = MAX_DEPT_OPT;
    call_sub();
}

void all_dept()
{
    if(menu_no == MENU_PGMS)
        start_prn();
    sprintf(prt_buffer,s_adptscan);
    ej_prn();
    mkline();
    for(ppluno=1;ppluno<=MAX_DEPT;ppluno++)
        {
        sub_pso21();
        }
    sall_bit = 0;
    endlogo();
    paddr = 0;
    if(menu_no == MENU_PGMS)
        start_menu(MENU_PGMS);
}

void sub_pso22()
{
    paddr = PADD_PER;
    sys_pgno = 0;
    sys_line = 0;
    perno = func - CASH;
    ppluno = func - PER1;
    deptno = FUNCKEY[perno].KEY_ST.PCNT_KEY.AMOUNT;
    if(deptno)
        opt_pgm = pcnt_pgm1;
    else
        opt_pgm = pcnt_pgm0;
    opt_ptr = (unsigned char*)&FUNCKEY[perno];
    max_page = MAX_PCNT_OPT;
    call_sub();
}

void sub_pso23()
{
    paddr = PADD_CLK;
    sys_pgno = 0;
    sys_line = 0;
    opt_pgm = clk_pgm;
    opt_ptr = (unsigned char*)&CLERK_P[ppluno-1];
    max_page = MAX_CLK_OPT;
    call_sub();
}

void all_clk()
{
    if(menu_no == MENU_PGMS)
        start_prn();
    sprintf(prt_buffer,s_aclkscan);
    ej_prn();
    mkline();
    sall_bit = 1;
    for(ppluno=1;ppluno<=MAX_CLERK;ppluno++)
        {
        sub_pso23();
        }
    sall_bit = 0;
    endlogo();
    paddr = 0;
    if(menu_no == MENU_PGMS)
        start_menu(MENU_PGMS);
}

void sub_pso24()
{
    paddr = PADD_NS;
    sys_pgno = 0;
    sys_line = 0;
    opt_pgm = ns_pgm;
    opt_ptr = (unsigned char*)&FUNCKEY[NOSALE-CASH];
    max_page = MAX_NS_OPT;
    call_sub();
}

void sub_pso25()
{
    paddr = PADD_CASH;
    sys_pgno = 0;
    sys_line = 0;
    opt_pgm = cash_pgm;
    opt_ptr = (unsigned char*)&FUNCKEY[CASH-CASH];
    max_page = MAX_CASH_OPT;
    call_sub();
}

void sub_pso26()
{
    paddr = PADD_CHECK;
    sys_pgno = 0;
    sys_line = 0;
    opt_pgm = cash_pgm;
    opt_ptr = (unsigned char*)&FUNCKEY[CHECK-CASH];
    max_page = MAX_CASH_OPT;
    call_sub();
}

void sub_pso27()
{
    paddr = PADD_VOID;
    sys_pgno = 0;
    sys_line = 0;
    opt_pgm = void_pgm;
    opt_ptr = (unsigned char*)&FUNCKEY[VOID-CASH];
    max_page = MAX_VOID_OPT;
    call_sub();
}

void sub_pso28()
{
    paddr = PADD_RETURN;
    sys_pgno = 0;
    sys_line = 0;
    opt_pgm = &void_pgm[1];
    opt_ptr = (unsigned char*)&FUNCKEY[RETURN-CASH];
    max_page = MAX_CAN_OPT;
    call_sub();
}

void sub_pso29()
{
    paddr = PADD_CANCEL;
    sys_pgno = 0;
    sys_line = 0;
    opt_pgm = &void_pgm[1];
    opt_ptr = (unsigned char*)&FUNCKEY[CANCEL-CASH];
    max_page = MAX_CAN_OPT;
    call_sub();
}

void sub_pso30()
{
    paddr = PADD_CNV;
    sys_pgno = 0;
    sys_line = 0;
    opt_pgm = conv_pgm;
    opt_ptr = (unsigned char*)&FUNCKEY[func-CASH];
    max_page = MAX_CONV_OPT;
    call_sub();
}

void sub_pso31()
{
    paddr = PADD_RA;
    sys_pgno = 0;
    sys_line = 0;
    opt_pgm = &void_pgm[1];
    opt_ptr = (unsigned char*)&FUNCKEY[RA-CASH];
    max_page = MAX_CAN_OPT;
    call_sub();
}

void sub_pso32()
{
    paddr = PADD_PO;
    sys_pgno = 0;
    sys_line = 0;
    opt_pgm = &void_pgm[1];
    opt_ptr = (unsigned char*)&FUNCKEY[PO-CASH];
    max_page = MAX_CAN_OPT;
    call_sub();
}

void sub_pso33()
{
    paddr = PADD_MISC;
    sys_pgno = 0;
    sys_line = 0;
    opt_pgm = misc_pgm;
    opt_ptr = (unsigned char*)&FUNCKEY[func-CASH];
    max_page = MAX_MISC_OPT;
    call_sub();
}

void sub_pso34()
{
    bak_pgno = sys_pgno;
    bak_line = sys_line;
    bak_len  = sys_len ;
    bak_lno  = sys_lno ;
    bak_para = sys_para;
    bak_page = max_page;
    bak_cont = sys_cont;
    bak_ppluno = ppluno;
    bak_pgm  = opt_pgm ;
    bak_ptr  = opt_ptr ;
    bak_idx  = chr_idx ;
    bak_paddr = paddr  ;
    bak_dbl  = flg_dbl ;
    pmemcpy(bak_buf, msg_buf, MAX_MSG_DESC+1);
    bak_logo = flg_logo;
    bak_sft  = sft_idx;

    flg_logo = 0;
    paddr = PADD_ALPH;
    sys_pgno = 0;
    sys_line = 0;
    opt_pgm = alph_pgm;
    opt_ptr = &alph;
    max_page = MAX_OTH_ALPH;
    sv_lcd1();
    dsp_sys_pg();
}

void recov_v()
{
    sys_pgno = bak_pgno;
    sys_line = bak_line;
    sys_len  = bak_len ;
    sys_lno  = bak_lno ;
    sys_para = bak_para;
    max_page = bak_page;
    sys_cont = bak_cont;
    opt_pgm  = bak_pgm ;
    opt_ptr  = bak_ptr ;
    ppluno   = bak_ppluno;
    pmemcpy(msg_buf, bak_buf, MAX_MSG_DESC+1);
    paddr = bak_paddr;

    flg_logo = bak_logo;
    sft_idx = bak_sft;
}

UBYTE sub_pso35()
{
    if((nur < 1) || (nur > MAX_SPECIAL))
        return 0;
    recov_v();
    bak_paddr = 99;
    dsp_sys_pg();
    bak_paddr = 0;
    flg_dbl = bak_dbl;
    chr_idx = bak_idx;

    msg_buf[chr_idx] = oth_tbl[(char)nur - 1];
    sft_idx = 1;
    flg_logo = 2;
    dpgm_chr(0);
    return 1;
}

void sub_pso36()
{
    paddr = PADD_TAX2;
    sys_pgno = 0;
    sys_line = 0;
    opt_pgm = tax_pgm2;
    opt_ptr = (unsigned char*)&tax_table[ppluno-1];
    max_page = MAX_TAX2_OPT;
    dsp_sys_pg();
}

void sub_pso37()
{
    paddr = PADD_TAX1;
    sys_pgno = 0;
    sys_line = 0;
    if(ppluno == MAX_TAX)
        opt_pgm = tax_pgm4;
    else
        opt_pgm = tax_pgm1;
    opt_ptr = (unsigned char*)&tax_table[ppluno-1];
    max_page = MAX_TAX1_OPT;
    dsp_sys_pg();
}

void sub_pso38()
{
    paddr = PADD_TAX3;
    sys_pgno = 0;
    sys_line = 1;
    opt_pgm = tax_pgm3;
    opt_ptr = (unsigned char*)&tmp_long;
    max_page = MAX_TAX3_OPT;
    tax_brk = tax_table[ppluno-1].nrbreak + tax_table[ppluno-1].rbreak;
    dsp_taxtbl();
    sys_lno = 3;
    dsp_str(MAX_CLM-1, sys_lno, s_larrow);
    sys_len = 5;
}

void sub_pso39()
{
    paddr = PADD_SFT;
    sys_pgno = 0;
    sys_line = 0;
    opt_pgm = sft_pgm;
    opt_ptr = (unsigned char*)&FUNCKEY[func-CASH];
    max_page = MAX_SFT_OPT;
    call_sub();
}

void sub_pso40()
{
    paddr = PADD_CNO2;
    ppluno = 0;
    sys_pgno = 0;
    sys_line = 0;
    opt_pgm = cno_pgm;
    opt_ptr = (unsigned char*)&ppluno;
    max_page = MAX_CNO_OPT;
    sys_lno = 7;
    dsp_sys_pg();
}

void sub_pso41()
{
    paddr = PADD_CIO;
    sys_pgno = 0;
    sys_line = 0;
    opt_pgm = cio_pgm;
    opt_ptr = (unsigned char*)CLKIO[ppluno-1].D_LOG;
    max_page = MAX_CIO_OPT;
    dsp_sys_pg();
    prn_clksub(lcdbuf, CLKIO[ppluno-1].W_TIME, 0);
    dsp_str(1,7,lcdbuf);
}

void sub_pso42()
{
    paddr = PADD_PNO2;
    ppluno = 0;
    sys_pgno = 0;
    sys_line = 0;
    opt_pgm = pno_pgm;
    opt_ptr = (unsigned char*)&ppluno;
    max_page = MAX_PNO_OPT;
    sys_lno = 7;
    dsp_sys_pg();
}

void sub_pso43()
{
    paddr = PADD_INVP;
    sys_pgno = 0;
    sys_line = 0;
    opt_pgm = inv_pgm;
    opt_ptr = (unsigned char*)&stock_p[ppluno-1];
    max_page = MAX_INV_OPT;
    dsp_sys_pg();
}

void sub_pso44()
{
    paddr = PADD_GRP;
    sys_pgno = 0;
    sys_line = 0;
    opt_pgm = grp_pgm;
    opt_ptr = grp_desc[0];
    max_page = MAX_GRP_OPT;
    call_sub();
}

void sub_pso45()
{
    paddr = PADD_DNO2;
    ppluno = 0;
    sys_pgno = 0;
    sys_line = 0;
    opt_pgm = dno_pgm;
    opt_ptr = (unsigned char*)&ppluno;
    max_page = MAX_DNO_OPT;
    dsp_sys_pg();
}

void sub_pso46()
{
    paddr = PADD_INVD;
    sys_pgno = 0;
    sys_line = 0;
    opt_pgm = inv_pgm;
    opt_ptr = (unsigned char*)&stock_d[ppluno-1];
    max_page = MAX_INV_OPT;
    dsp_sys_pg();
}

void sub_pso47()
{
    paddr = PADD_SCALE;
    sys_pgno = 0;
    sys_line = 0;
    opt_pgm = scale_pgm;
    opt_ptr = (unsigned char*)&FUNCKEY[func-CASH];
    max_page = MAX_SCALE_OPT;
    call_sub();
}

void sub_pso48()
{
    paddr = PADD_TARE;
    sys_pgno = 0;
    sys_line = 0;
    opt_pgm = tare_pgm;
    opt_ptr = (unsigned char*)&tare_weight[0];
    max_page = MAX_TARE_OPT;
    call_sub();
}

void pgm_fkey()
{
    ppluno = 0;
    switch(func)
        {
        case NOSALE :
            sub_pso24();
            break;
        case CASH   :
            sub_pso25();
            break;
        case CHECK  :
            sub_pso26();
            break;
        case MISCTND1 :
        case MISCTND2 :
        case MISCTND3 :
        case MISCTND4 :
            sub_pso33();
            break;
        case VOID   :
            sub_pso27();
            break;
        case RETURN :
            sub_pso28();
            break;
        case CANCEL :
            sub_pso29();
            break;
        case CONV1  :
        case CONV2  :
        case CONV3  :
        case CONV4  :
            sub_pso30();
            break;
        case RA     :
            sub_pso31();
            break;
        case PO     :
            sub_pso32();
            break;
        case PER1   :
        case PER2   :
        case PER3   :
        case PER4   :
            sub_pso22();
            break;
        case DEPT_SFT :
            sub_pso39();
            break;
        case SCALE :
            sub_pso47();
            break;
        default:
            if(menu_no == MENU_PGM)
                sub_psoA();
//            pfkey_bit = 1;
//            if(menu_no == MENU_PGMS)
//                st_pgm();
        }
}

void p_page_up()
{
    if(paddr == PADD_TAX3)
        {
        if(tax_idx && ! sys_line)
            tax_idx -= 6;
        if(tax_idx)
            {
            sys_line = 0;
            sys_lno = 2;
            }
        else
            {
            sys_line = 1;
            sys_lno = 3;
            }
        dsp_taxtbl();
        dsp_str(MAX_CLM-1, sys_lno, s_larrow);
        }
    else if(sys_line)
        {
        flg_logo = 0;
        sys_line = 0;
        dsp_sys_pg();
        }
    else if (is_mpage()) {           /* PKR0628 */
        flg_logo = 0;
        if(sys_pgno != 0)
            {
            sys_pgno--;
            sys_line = 0;
            dsp_sys_pg();
            }
        else if(paddr == PADD_PLU)
            {
            ppluno--;
            if(ppluno > 0)
                sub_pso20();
            else
                st_pgm();
            }
        else if(paddr == PADD_INVP)
            {
            while(1)
                {
                ppluno--;
                if(ppluno > 0)
                    {
                    if(plu[ppluno-1].status[1] & 0x10)  /* invent_bit */
                        {
                        sub_pso43();
                        break;
                        }
                    }
                else
                    {
                    st_pgm();
                    break;
                    }
                }
            }
        else if(paddr == PADD_INVD)
            {
            while(1)
                {
                ppluno--;
                if(ppluno > 0)
                    {
                    if(dept[ppluno-1].status[1] & 0x10)  /* invent_bit */
                        {
                        sub_pso46();
                        break;
                        }
                    }
                else
                    {
                    st_pgm();
                    break;
                    }
                }
            }
        else if(paddr == PADD_DEPT)
            {
            ppluno--;
            if(ppluno > 0)
                sub_pso21();
            else
                st_pgm();
            }
#if 0
        else if(paddr == PADD_CNV)
            {
            ppluno--;
            if(ppluno > 0)
                sub_pso30();
            else
                st_pgm();
            }
#endif
        else if(paddr == PADD_CLK)
            {
            ppluno--;
            if(ppluno > 0)
                sub_pso23();
            else
                st_pgm();
            }
        else if(paddr == PADD_TAX1)
            {
            ppluno--;
            if(ppluno > 0)
                sub_pso1(ppluno);
            else
                st_pgm();
            }
        }
    else if((paddr == 0) && menu_st)
        {
        menu_st = 1 - menu_st;
        dsp_menu();
        }
    p_nclr();
}

void p_page_dn()                       /* --------------------------- */
{
    if (is_mpage()) {           /* PKR0628 */
        if(sys_pgno < max_page-1)
            {
            flg_logo = 0;
            sys_pgno++;
            sys_line = 0;
            dsp_sys_pg();
            }
        else if(paddr == PADD_PLU)
            {
            flg_logo = 0;
            ppluno++;
            if(ppluno <= MAX_PLU)
                sub_pso20();
            else
                st_pgm();
            }
        else if(paddr == PADD_INVP)
            {
            flg_logo = 0;
            while(1)
                {
                ppluno++;
                if(ppluno <= MAX_PLU)
                    {
                    if(plu[ppluno-1].status[1] & 0x10)  /* invent_bit */
                        {
                        sub_pso43();
                        break;
                        }
                    }
                else
                    {
                    st_pgm();
                    break;
                    }
                }
            }
        else if(paddr == PADD_INVD)
            {
            flg_logo = 0;
            while(1)
                {
                ppluno++;
                if(ppluno <= MAX_DEPT)
                    {
                    if(dept[ppluno-1].status[1] & 0x10)  /* invent_bit */
                        {
                        sub_pso46();
                        break;
                        }
                    }
                else
                    {
                    st_pgm();
                    break;
                    }
                }
            }
        else if(paddr == PADD_DEPT)
            {
            flg_logo = 0;
            ppluno++;
            if(ppluno <= MAX_DEPT)
                sub_pso21();
            else
                st_pgm();
            }
#if 0
        else if(paddr == PADD_CNV)
            {
            flg_logo = 0;
            ppluno++;
            if(ppluno <= MAX_CONV)
                sub_pso30();
            else
                st_pgm();
            }
#endif
        else if(paddr == PADD_CLK)
            {
            flg_logo = 0;
            ppluno++;
            if(ppluno <= MAX_CLERK)
                sub_pso23();
            else
                st_pgm();
            }
        else if(paddr == PADD_TAX1)
            {
            flg_logo = 0;
            ppluno++;
            if(ppluno <= MAX_TAX)
                sub_pso1(ppluno);
            else
                st_pgm();
            }
        }
    else if(paddr == PADD_TAX3)
        {
        tax_idx += 6;
        sys_line = 0;
        sys_lno = 1;
        if(tax_idx + sys_line > tax_brk)
            {
            make_taxtbl(ppluno-1);
            paddr = 0;
            sys_lno = MAX_LINE - 1;
            sys_len = 8;
            start_menu(MENU_PGM);
            }
        dsp_taxtbl();
        sys_lno++;
        dsp_str(MAX_CLM-1, sys_lno, s_larrow);
        }
    else if((paddr == 0) && !menu_st)
        {
        menu_st = 1 - menu_st;
        dsp_menu();
        }
    p_nclr();
}

void scan_tbl(UBYTE tax_no)
{
    UBYTE tax_brk, i, len;
    long amt;

    tax_brk = tax_table[tax_no].nrbreak + tax_table[tax_no].rbreak + 1;
    sprintf(&prt_buffer[2],s_ttblsp);
    ej_prn();
    for(i=0,amt=0;i<tax_brk;i++)
        {
        l2c((long)i,lcdbuf,2);
        len = strlen(lcdbuf);
        pmemcpy(&prt_buffer[6-len], lcdbuf, len);

        if(i != 0)
            amt++;
        l2c(amt,lcdbuf,2);
        len = strlen(lcdbuf);
        pmemcpy(&prt_buffer[15-len], lcdbuf, len);

        if(i == 0)
            amt = tax_table[tax_no].taxnamt;
        else
            amt += (tax_table[tax_no].ttable[i-1] - 1);
        l2c(amt,lcdbuf,2);
        len = strlen(lcdbuf);
        pmemcpy(&prt_buffer[24-len], lcdbuf, len);
        prt_buffer[17] = '-';
        ej_prn();

        if(i == tax_table[tax_no].nrbreak)
            mkline();
        }
}

void scan_tax()
{
    UBYTE i, j, mask;

    if(end_mark)
        start_prn();
    sttl_sub(7);
    for(i=0;i<MAX_TAX;i++)
        {
        sprintf(prt_buffer, s_taxpd, i+1);
        ej_prn();
        pmemcpy(prt_buffer, tax_table[i].desc, MAX_TAX_DESC);
        ej_prn();
        if((tax_table[i].taxstat & 0x0f) == 1)
            scan_tbl(i);
        else
            {
            l2c(tax_table[i].taxrate, lcdbuf, 3);
            if((tax_table[i].taxstat & 0x0f) == 0)
                sprintf(prt_buffer, "ADD-ON at %s%c", lcdbuf, 0x25);
            else
                sprintf(prt_buffer, "VAT at %s%c", lcdbuf, 0x25);
            ej_prn();
            if(i == MAX_TAX-1)
                {
                for(j=0,mask = 0x10;j<3;j++,mask = mask << 1)
                    {
                    if(tax_table[i].taxstat & mask)
                        {
                        sprintf(prt_buffer, "GST IS TAXABLE BY RATE %d", j+1);
                        ej_prn();
                        }
                    }
                }
            }
        ej_prn();
        }

    pgm_endlogo();
}

void menu_pgm()
{
    switch(nur)
        {
        case 0:            /* Department */
            if(ncnt)
                sub_pso3();    /* PKR0710 */
            break;
        case 1:            /* PLU */
            sub_pso2();
            break;
        case 2:            /* Tax */
            if(menu_no == MENU_PGMS)
                scan_tax();
            else
                sub_pso1(1);
            break;
        case 3:            /* System Option */
            sub_pso0();
            break;
        case 4:            /* Print Option */
            sub_pso9();
            break;
        case 5:            /* Function Keys */
            sub_psoA();
            break;
        case 6:            /* Clerk */
            sub_pso6();                /* PKR0724 */
            break;
        case 7:            /* Logo Descriptor */
            sub_pso8();                /* PKR0724 */
            break;
        case 8:            /* Group Descriptor */
            sub_pso44();                /* PKR0710 */
            break;
        case 9:            /* Tare weight */
            sub_pso48();                /* PKR0710 */
            break;
        case 10:           /* More */
            start_menu(MENU_PGM2);
            break;
        }
    p_nclr();
}

void all_pgm_scan()
{
    sub_pso0();                        /* System Option */
    sttl_sub(1);
    sub_pso9();                        /* Print Option */
    scan_tax();                        /* Tax */

    sttl_sub(6);
    for(func=0x110;func<0x12d;func++)
        pgm_fkey();
    mkline();
    ej_prn();
    pfkey_bit = 0;

    sall_bit = 1;
    sttl_sub(4);                       /* Clerk */
    for(ppluno=1;ppluno<=MAX_CLERK;ppluno++)
        sub_pso23();
    mkline();
    ej_prn();

    sub_pso8();

    sttl_sub(8);                       /* Group Descriptor */
    sub_pso44();

    sttl_sub(9);                       /* Tare Weight */
    sub_pso48();

    all_dept();
//    all_plu();
}

void menu_pgm2()
{
    switch(nur)
        {
        case 0:            /* CLERK TIME I/O EDIT */
            if(ncnt)
                sub_pso40();
            break;
        case 1:            /* PLU INVENTORY */
            sub_pso42();
            break;
        case 2:            /* DEPT INVENTORY */
            sub_pso45();
            break;
        case 3:            /* Date & Time */
            sub_pso4();                /* PKR0710 */
            break;
        case 4:            /* Program Scan */
            start_menu(MENU_PGMS);
            break;
        case 5:
            all_pgm_scan();
            break;
        }
    p_nclr();
}

void cal_tmio()
{
    UBYTE i;
    int time1, time2;

    CLKIO[ppluno-1].W_TIME = 0;
    CLKIO[ppluno-1].T_IDX = 0;
    for(i=0;i<MAX_CIO/2;i++)
        {
        time1 = CLKIO[ppluno-1].T_LOG[i*2];
        if(time1 == 0)
            continue;
        else
            CLKIO[ppluno-1].T_IDX = i * 2 + 1;
        time2 = CLKIO[ppluno-1].T_LOG[i*2+1];
        if(time2 == 0)
            continue;
        else
            CLKIO[ppluno-1].T_IDX = (i + 1) * 2;
        time1 = time_diff(time1, time2);
        CLKIO[ppluno-1].W_TIME = time_add(CLKIO[ppluno-1].W_TIME, time1);
        }
    prn_clksub(lcdbuf, CLKIO[ppluno-1].W_TIME, 0);
    dsp_str(1,7,lcdbuf);
}

void p_enter()                         /* ------------------------- */
{
    UBYTE nnct=ncnt, i;
    int tmp;
    long last_long;

    if(!paddr)
        {
        if(menu_no == MENU_PGM2)
            menu_pgm2();
        else
            menu_pgm();
        return;
        }
    if (paddr == PADD_ALPH)
        {
        if(sub_pso35() == 0)
            {
            errmsg = E_PGM; ERR
            }
        }
    else if(pe_sub() == 0)
        {
        errmsg = E_PGM; ERR
        }
    pop_lcd = 0;
    sv_lcd1();
    if(paddr == PADD_TAX0)
        {
        if(sys_line == 99)
            {
            if(tax_tmp[0])
                {
                ppluno = tax_tmp[0];
                pmemcpy(tax_table[ppluno-1].desc, &tax_tmp[2], MAX_TAX_DESC);
                tax_table[ppluno - 1].taxstat =
                        (tax_table[ppluno - 1].taxstat & 0xf0) | tax_tmp[1];
                if(tax_tmp[1] == 1)        /* Tax Table */
                    sub_pso36();
                else
                    sub_pso37();
                }
            sys_line = 0;
            }
        }
    else if(paddr == PADD_TAX2)
        {
        if(sys_line == 99)
            {
            tax_idx = 0;
            sub_pso38();
            }
        }
    else if(paddr == PADD_TAX3)
        {
        if(tax_idx + sys_line > 1)
            {
            if(sys_line == 99)
                {
                tax_idx += 6;
                sys_line = 0;
                sys_lno = 1;
                }
            if(nnct)
                {
                last_long = tax_table[ppluno-1].taxnamt;
                for(i=0;i<tax_idx + sys_line-2;i++)
                    last_long += tax_table[ppluno-1].ttable[i];
                tax_table[ppluno-1].ttable[tax_idx + sys_line - 2] = tmp_long - last_long;
                last_long = tmp_long += tax_table[ppluno-1].ttable[tax_idx + sys_line - 1];
                }
            if(tax_idx + sys_line > tax_brk)
                {
                make_taxtbl(ppluno-1);

                flg_logo = 0;
                ppluno++;
                if(ppluno <= MAX_TAX)
                    sub_pso1(ppluno);
                else
                    st_pgm();

//                paddr = 0;
//                sys_lno = MAX_LINE - 1;
//                sys_len = 8;
//                start_menu(MENU_PGM);
                }
            }
        if((paddr != 0) && (paddr == PADD_TAX3))
            {
            dsp_taxtbl();
            sys_lno++;
            dsp_str(MAX_CLM-1, sys_lno, s_larrow);
            }
        }
    else if (paddr == PADD_PNO)
        {
        if(!sall_bit)
            sub_pso20();
        else
            all_plu();
        }
    else if (paddr == PADD_PNO2)
        {
        if(plu[ppluno-1].status[1] & 0x10)  /* invent_bit */
            sub_pso43();
        else
            { errmsg = E_NOTINV; ERR }
        }
    else if (paddr == PADD_DNO)
        {
        if(!sall_bit)
            sub_pso21();
        else
            all_dept();
        }
    else if (paddr == PADD_DNO2)
        {
        if(dept[ppluno-1].status[1] & 0x10)  /* invent_bit */
            sub_pso46();
        else
            {
            sys_line = 0;
            errmsg = E_NOTINV;
            ERR
            }
        }
    else if (paddr == PADD_CNO)
        {
        if(ppluno > 0)
            sub_pso23();
        else if(menu_no == MENU_PGMS)
            all_clk();
        else
            {
            sys_line = 0;
            errmsg = E_PGM; ERR
            }
        }
    else if ((paddr == PADD_CNO2) && (ppluno > 0))
        sub_pso41();
    else if ((paddr == PADD_DTM) && (sys_line == 99))
        {
        set_dtm();
        st_pgm();
        }
    else if((paddr == PADD_PER) && (sys_pgno == 0) && (sys_line == 2))
        {
        tmp = FUNCKEY[perno].KEY_ST.PCNT_KEY.AMOUNT;
        if(tmp != deptno)
            {
            deptno = tmp;
            if(tmp)
                opt_pgm = pcnt_pgm1;
            else
                opt_pgm = pcnt_pgm0;
            dsp_sys_pg();
            }
        }
    else if(paddr == PADD_CIO)
        {
        cal_tmio();
        if(sys_line == 99)
            {
            sys_line = 0;
            p_page_dn();
            }
        }
    else if((sys_line == 99) && (paddr != PADD_ALPH))
        {
        sys_line = 0;
        p_page_dn();
        }
    p_nclr();
}

void p_void()
{
    flg_logo = 2;
    chr_idx = sft_idx = 0;
    dpgm_chr(1);
    p_enter();
}

void dpgm_chr(UBYTE void_f)
{
    int j, k, l;
    UBYTE buf[MAX_CLM+1], line_no;

    line_no = opt_pgm[sys_pgno].item[sys_line].line_no;
    l = opt_pgm[sys_pgno].item[sys_line].bit_mask;
    j = opt_pgm[sys_pgno].item[sys_line].max_len;

    memset(buf,0x20,MAX_CLM-1);
    buf[MAX_CLM-1-l] = 0;
    if(chr_idx == 0)
        {
        memset(&msg_buf[1], 0, j - 1);
        dsp_str(l, line_no, buf);
        if(void_f)
            return;
        }

    if(chr_idx < MAX_CLM - 1)
        {
        if(j >= MAX_CLM)
            j = MAX_CLM - 1;
        pmemcpy(buf, msg_buf, j);
        }
    else
        {
        k = chr_idx - MAX_CLM + 2;
        j -= k;
        if(j > MAX_CLM)
            j = MAX_CLM - 1;
        pmemcpy(buf, &msg_buf[k], j);
        }
    dsp_str(l, line_no, buf);
}

void chr_sft()
{
    int i;
    UBYTE ch;

    for(i=0;i<MAX_SHIFT;i++)
        {
        ch = msg_buf[chr_idx];
        if((ch >= 'a') && (ch <= 'z'))
            ch -= 0x20;
        if(eng_sft[i][0] == ch)
            {
            ch = eng_sft[i][1];
            if((!flg_caps) && (ch >= 'A') && (ch <= 'Z'))
                ch += 0x20;
            msg_buf[chr_idx] = ch;
            break;
            }
        }

    dpgm_chr(0);
}

void pgm_chr(UBYTE chrno)
{
    UBYTE ch;

    if(!flg_logo)
        return;

    if(chrno == 0)
        flg_caps = 1 - flg_caps;
    else if(chrno == 1)
        {
        if(chr_idx >= sys_len-flg_dbl)
            return;
        sub_pso34();
        }
    else if(chrno == 10)
        flg_dbl = 1 - flg_dbl;
    else if(sft_idx && (last_chr == chrno))
        chr_sft();
    else
        {
        last_chr = chrno;
        if(chr_idx >= sys_len-flg_dbl)
            return;
        ch = engtbl[chrno-2];
        if((!flg_caps) && (ch >= 'A') && (ch <= 'Z'))
            ch += 0x20;
        msg_buf[chr_idx] = ch;
        sft_idx = 1;
        flg_logo = 2;
        dpgm_chr(0);
        }
}

