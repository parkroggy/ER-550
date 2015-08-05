#include <stdio.h>
#include <er1io51.h>
#include <er1exmn.h>
#ifndef BCDBG
#include  <exs03.h>
#else                                  /* BCDBG */
#include  <exdbg.h>
#include  <conio.h>

extern void init_dbg();
extern  S_CODE_MEM real_code;
#endif                                 /* BCDBG */

extern const UBYTE s_closed[7];
extern const UBYTE s_deptpd[8];
extern const UBYTE s_plupd[7];
extern const UBYTE s_escode[18];
extern const UBYTE s_blanks[21];

/***** external region *******/
extern void set_dtm();
extern void clr_dec();
//PKR0624 extern void compdchk();
extern void d_close();
extern void delay();
extern void err_mess(char type);
//PKR0624 extern void endclr();
extern void endlogo();
//PKR0624 extern void feeding();
//PKR0624 extern void feedkscan();
extern void feed_view();
//PKR0624 extern void initseq();
extern void ini_outdtx();
//PKR0624 extern void init_mdchg();
extern void logo_only(char type);
extern void mkdnur(char inf);
extern void mkline();
extern void mkstar();
//PKR0624 extern void outdtx();
extern void p_init();
extern void prn_tend(char dinx,unsigned int kfunc,char lcd_f);
//PKR0624 extern void pend_chk();
//extern void pmd_end();
extern void valid_chk();
extern void ser_rvx(int ffunc);
/*extern char rapo_chk();*/
extern void mv_decbuf();
extern void read_clerk();
extern void mode_chg();
extern void mode_dsp();
extern void lcd_dsp(char clr_f);
extern void pop_menu(unsigned char *msg, unsigned char ch);
extern void lcd_rec(char type);
extern void sv_lcd();
extern void mode_line();
extern void start_menu(UBYTE no);        /* PKR0709 */
extern void pgm_chr(UBYTE);            /* PKR0722 */
extern void x_yesno();                 /* YOO0812 */
extern void dsp_str(UBYTE, UBYTE, UBYTE*);
extern void start_prn();
extern void prn_clklog(UBYTE, UBYTE);
extern void scr_prt();
extern void r_menu();
extern void r_misc();
extern void blk_prs();
extern void plu_pop(char pnum);
extern char opn_alarm(char type);
extern void help_dsp();
extern void pmemcpy(UBYTE *, UBYTE *, unsigned int);
extern UBYTE is_xfirst();
extern void dsp_tax(int type);
extern void sub_psoA();
extern void endlogr();
extern void send_kp();
extern int read_time();
extern void comm_sior(UBYTE);
extern void taxexm_set(int kfunc);

/***************************************/
/***      external register mode     ***/
/***************************************/
extern void r_tare();
extern void  r_dept();
extern void  r_plu();
extern void  r_tender();
extern void  r_subt();
extern void  r_etd();
/*extern void  r_open();*/
extern void  r_addck();
/*extern void  r_chktnd(char type);*/
/*extern void  r_clkopen();
extern void  r_clkclose();*/
extern void  r_conv();
extern void  r_xtime();
extern void  r_nosale();
extern void  r_scale();

extern void  r_rtn();
extern void  r_void();
extern void  r_cancel();
extern void  r_reissue();
extern void  r_tax();
extern void  r_level();
extern void  r_price();
extern void  r_per();
extern void  r_rapo();
extern void  r_timeio();
extern void  r_timeiom();

/***************************************/
/***      external report mode       ***/
/***************************************/
extern void report();
extern void rep_dpt();
extern void rep_clk();
extern void x_plu();
extern void x_cashdec();
extern void x_level();
extern void page_up();
extern void page_down();
extern void x_enter();                 /* yoo0719 */
extern void x_xtime();                 /* yoo0719 */
extern char passin_chk();

void clrk_prs();


/***************************************/
/***      external program mode      ***/
/***************************************/
extern void p_decim();                 /* PKR 0626 */
extern void p_dlvl();
extern void p_cash();
extern void p_enter();                 /* PKR0706 */
extern void p_dept();
extern void p_conv();
extern void p_desc();
extern void p_charge();
extern void p_check();
extern void p_level();
extern void p_open();
extern void p_yes_no();
extern void p_page_up();
extern void p_page_dn();
extern void p_void();
extern void pgm_fkey();
extern void cmemcpy(UBYTE *, UBYTE *, UBYTE);
extern void recov_v();
extern void tmio_sub();

extern void test_clerk();
extern void test_fread();
extern void test_fwrite();
extern void test_ptdp();
extern void test_mmode();
extern UBYTE *get_fdesc(unsigned int);
extern void make_taxtbl(UBYTE taxno);
extern void dsp_rev(char index);
extern void chk_kpend();
extern void mk_chksum(UBYTE*);


#include <er1file.h>    /* r,p,m,i pgm       */

/***********************************************************************/
/*****                                                             *****/
/*****                        MAIN   ROUTINE                       *****/
/*****                                                             *****/
/***********************************************************************/
/**                     ER-5100 STANDARD PROGRAM                      **/
/***********************************************************************/
extern void wait_clear();
//void dsp_step(UBYTE step)
//{
//    UBYTE temp[10];
//    sprintf(temp,"step %d", step);
//    dsp_str(0,step,temp);
//    wait_clear();
//    dsp_str(0,step,"      ");
//}

void help_prc()
{
    if(!help_flg)
        pmemcpy(dsp_bak[0],dsp_buf[0],MAX_LINE*(MAX_CLM+1));
    help_flg = 1;
    switch(mode_id) {
        case VMODE: help_stp = H_V_ST;
                    hpage_off = 0;
                    hpage_max = 2;
                    break;
        case RMODE: help_stp = H_R_ST;
                    hpage_off = 0;
                    hpage_max = 2;
                    break;
                    
        case XMODE:
                if(menu_no == 0)
                    {
                    switch(xm_step)
                        {
                        case XM_DECL:
                        case XM_DECLF:
                            help_stp = H_DECL;
                            hpage_off = 0;
                            hpage_max = 2;
                            break;
                        case XM_RCONT:
                        case XM_RCONTS:
                            help_stp = H_RCT_C;
                            hpage_off = 0;
                            hpage_max = 1;
                            break;
                        case XM_RONOFF:
                        case XM_RONOFFS:
                            help_stp = H_RONOFF;
                            hpage_off = 0;
                            hpage_max = 1;
                            break;
                        case XM_TRAIN:
                            help_stp = H_TRAIN;
                            hpage_off = 0;
                            hpage_max = 2;
                            break;
                        default:
                            help_stp = H_X_ST;
                            hpage_off = 0;
                            hpage_max = 11;
                        }
                    }
                else if(((rept_step == 1) || (rept_step == 2)) &&
                        ((menu_no == MENU_PRINT) || (menu_no == MENU_DISPLAY)))
                    {
                    help_stp = H_FINAN;
                    hpage_off = 0;
                    if(rept_ptd)
                        hpage_max = 6;
                    else
                        hpage_max = 13;
                    }
                break;
        case ZMODE:
                if(rept_step == 1)
                    {
                    help_stp = H_FINAN;
                    hpage_off = 0;
                    if(rept_ptd)
                        hpage_max = 6;
                    else
                        hpage_max = 13;
                    }
                else
                    {
                    help_stp = H_Z_ST;
                    hpage_off = 0;
                    hpage_max = 2;
                    }
                    break;
        case PMODE:
                switch(paddr)
                    {
                    case PADD_TAX0:
                    case PADD_TAX1:
                    case PADD_TAX2:
                    case PADD_TAX3:
                        help_stp = 33;
                        hpage_off = 0;
                        hpage_max = 1;
                        break;
                    case PADD_SYSTEM:
                        help_stp = 34;
                        hpage_off = 0;
                        hpage_max = 1;
                        break;
                    case PADD_PRINT:
                        help_stp = 35;
                        hpage_off = 0;
                        hpage_max = 1;
                        break;
                    case PADD_DEPT:
                    case PADD_DNO:
                        help_stp = 31;
                        hpage_off = 0;
                        hpage_max = 1;
                        break;
                    case PADD_PLU:
                    case PADD_PNO:
                        help_stp = 32;
                        hpage_off = 0;
                        hpage_max = 1;
                        break;
                    case PADD_CLK:
                        help_stp = 38;
                        hpage_off = 0;
                        hpage_max = 1;
                        break;
                    case PADD_DTM:
                        help_stp = 46;
                        hpage_off = 0;
                        hpage_max = 1;
                        break;
                    case PADD_DESC:
                        help_stp = 39;
                        hpage_off = 0;
                        hpage_max = 1;
                        break;
                    case PADD_CIO:
                        help_stp = 43;
                        hpage_off = 0;
                        hpage_max = 1;
                        break;
                    case PADD_INVD:
                    case PADD_DNO2:
                        help_stp = 45;
                        hpage_off = 0;
                        hpage_max = 1;
                        break;
                    case PADD_INVP:
                    case PADD_PNO2:
                        help_stp = 44;
                        hpage_off = 0;
                        hpage_max = 1;
                        break;
                    case PADD_GRP:
                        help_stp = 40;
                        hpage_off = 0;
                        hpage_max = 1;
                        break;
                    case PADD_TARE:
                        help_stp = 41;
                        hpage_off = 0;
                        hpage_max = 2;
                        break;
                    case PADD_PER   :
                    case PADD_CNV   :
                    case PADD_NS    :
                    case PADD_CASH  :
                    case PADD_CHECK :
                    case PADD_MISC  :
                    case PADD_VOID  :
                    case PADD_RETURN:
                    case PADD_CANCEL:
                    case PADD_PO    :
                    case PADD_RA    :
                    case PADD_SFT   :
                    case PADD_SCALE :
                        help_stp = 36;
                        hpage_off = 0;
                        hpage_max = 2;
                        break;
                    default :
                        help_stp = H_P_ST;
                        hpage_off = 0;
                        hpage_max = 19;
                        break;
                    }
                break;
        case MMODE: help_stp = H_M_ST;
                    hpage_off = 0;
                    hpage_max = 6;
                    break;
        }
    help_dsp();
}

void ini_opt()
{
    int i;

    SYS_OPT.OPT1 = 1;
    SYS_OPT.OPT2_1 = 1;     SYS_OPT.OPT2_2 = 1;
    SYS_OPT.OPT3_2 = 1;
    SYS_OPT.OPT12_1 = 1;
    SYS_OPT.OPT13_2 = 1;
    SYS_OPT.OPT13_4 = 1;
    SYS_OPT.OPT16 = 30;
    SYS_OPT.OPT18_1 = 2;
    SYS_OPT.OPT23 = 9999;

    PRT_OPT.OPT1_2 = 1;     PRT_OPT.OPT1_3 = 1;
    PRT_OPT.OPT1_5 = 1;
    PRT_OPT.OPT2_1 = 1;     PRT_OPT.OPT2_4 = 1;
    PRT_OPT.OPT3_3 = 1;
    PRT_OPT.OPT4_1 = 1;     PRT_OPT.OPT4_2 = 1;
    PRT_OPT.OPT4_3 = 1;     PRT_OPT.OPT5 = 1;
    PRT_OPT.OPT6 = 'œ';     PRT_OPT.OPT7_1 = 1;
    PRT_OPT.OPT7_2 = 1;     PRT_OPT.OPT8_1 = 1;
    PRT_OPT.OPT8_2 = 1;     PRT_OPT.OPT8_3 = 1;
    PRT_OPT.OPT9_2 = 1;     PRT_OPT.OPT12_1 = 1;
//    PRT_OPT.OPT12_2 = 1;    PRT_OPT.OPT12_3 = 1;  /* 980605 */
//    PRT_OPT.OPT12_4 = 1;
    PRT_OPT.OPT12_5 = 1;    PRT_OPT.OPT12_6 = 1;  /* 981210 */

    FUNCKEY[CASH-CASH].KEY_ST.CASH_KEY.OPEN_DRW = 1;
    FUNCKEY[CHECK-CASH].KEY_ST.CASH_KEY.OPEN_DRW = 1;
    FUNCKEY[MISCTND1-CASH].KEY_ST.MISC_KEY.OPEN_DRW = 1;
    FUNCKEY[MISCTND2-CASH].KEY_ST.MISC_KEY.OPEN_DRW = 1;
    FUNCKEY[MISCTND3-CASH].KEY_ST.MISC_KEY.OPEN_DRW = 1;
    FUNCKEY[MISCTND4-CASH].KEY_ST.MISC_KEY.OPEN_DRW = 1;

    FUNCKEY[CASH-CASH].KEY_ST.CASH_KEY.UNDER_T = 1;
    FUNCKEY[CHECK-CASH].KEY_ST.CASH_KEY.UNDER_T = 1;
    FUNCKEY[MISCTND1-CASH].KEY_ST.MISC_KEY.UNDER_T = 1;
    FUNCKEY[MISCTND2-CASH].KEY_ST.MISC_KEY.UNDER_T = 1;
    FUNCKEY[MISCTND3-CASH].KEY_ST.MISC_KEY.UNDER_T = 1;
    FUNCKEY[MISCTND4-CASH].KEY_ST.MISC_KEY.UNDER_T = 1;
    memset(PRT_OPT.OPT13, 0x60, MAX_CONV);
    PRT_OPT.OPT13[0] = 'î';            /* 980605 */

    for(i=0;i<MAX_GROUP;i++)
        sprintf(grp_desc[i], "GROUP %d", i);
    for(i=0;i<MAX_TAX;i++)
        sprintf(tax_table[i].desc, "TAX%d AMT", i+1);
    for(i=0;i<MAX_FUNCKEY;i++)
        cmemcpy(FUNCKEY[i].DESC, code_mem->key_desc[i], 12);
    for(i=0;i<MAX_DEPT;i++)
        sprintf(dept[i].desc,s_deptpd,i+1);
    for(i=0;i<MAX_PLU;i++)
        sprintf(plu[i].desc,s_plupd,i+1);
    for(i=0;i<MAX_PLU;i++)
        plu[i].link_dept = 1;
    for(i=1;i<=MAX_CLERK;i++)
        if(i < 10)
            sprintf(CLERK_P[i-1].name, "CLERK#0%d", i);
        else
            sprintf(CLERK_P[i-1].name, "CLERK#%d", i);
    pmemcpy(messdec[1], "    T H A N K   Y O U     ", 26);
    pmemcpy(messdec[2], "   C A L L   A G A I N    ", 26);
    messdec[1][5] = messdec[1][7] = messdec[1][9] = messdec[1][11] =
        messdec[1][13] = messdec[1][17] = messdec[1][19] = messdec[1][21] = 0x11;
    messdec[2][4] = messdec[2][6] = messdec[2][8] = messdec[2][10] =
        messdec[2][14] = messdec[2][16] = messdec[2][18] =
        messdec[2][20] = messdec[2][22] = 0x11;
}

void reset_menu(char type)
{
    if(type != 2)
        lcd_rec(2);
    pmenu_inx = 0;
    menu_flg = 0;
    if(type)
        regstep = svrstep;
    if(regstep == RSTEP_END)
        voidmd_flg = 0;

}
void dsp_soff()
{
    d_close();
//    clr_lcd();
//    mode_dsp();
    pop_lcd = 2;
    pop_menu(s_closed,'|');
    pop_lcd = 0;
}

void sign_off( char type)
{
//    r_chktnd(1);if (err_bit) continue;
    zero_flg=0;
    nur=0;
    pop_plu_flg = 0;
    tmio_flg = 0;
    pop_lcd = 0;
    clerk=0;
    clk_kin = 0;
    if(!SYS_OPT.OPT19_1 && (type != 2))
            dsp_soff();
    else
            r_dsoff = 1;
    if(type == 1) {
    if(PRT_OPT.OPT1_5)
        {
        regstep = RSTEP_CLKOF;     /* 981211 */
        okbuf_bit = 0;             /* 981211 */
        notbuf_bit = 1;            /* 981211 */
        start_prn();
        prn_clklog(1, clerk);
        }
    regstep = RSTEP_END;
    }
}

void end_help()
{
    UBYTE i;

    for(i=0;i<MAX_LINE;i++)
        dsp_str(0,i,dsp_bak[i]);
    help_flg = 0;
    hpage_max = 0;
}

void main()
{
    int kk;
    unsigned char func_work;
    unsigned char func_nur,sv_dft_f;
//    long ck_sum=0;
//    long ck_sum1=0;
    char m2_func = 0,pskip = 0,p;

#ifdef BCDBG
    init_dbg();
while(1)
{
#endif
    r_dsoff = 0;
    svclk=0;
    mm_step = 0;

//    if((regstep == RSTEP_MENU1) || (regstep == RSTEP_MENU2) ) {
    if(regstep == RSTEP_MENU1) {
       regstep = svrstep;
       pmenu_inx = 0;
       }
    menu_flg = 0;

    flg_logo = 0;
    ini_outdtx();
    clr_dec();
    for(kk=0;kk<MAX_TAX;kk++)
        make_taxtbl(kk);

    blink = 0;

    while (1) {

#ifndef BCDBG
        code_mem = (S_CODE_MEM *)STR_ADDR;
        modescan();
#else
        code_mem = &real_code;
        modescan();
        if(flg_key_pend == 0x7f)
            {                          /* Something has to be done. */
            clr_lcd();
            memset((UBYTE*)&almstart_flg, 0, (long)&key_id-(long)&almstart_flg);
            pfail_flg = 1;
            flg_key_pend = 0;
            break;
            }
#endif                                 /* BCDBG */

//PKR 0626        if (!(mode_id & VORXZ)) continue;

        /************************************************/
        /**              feed & mode scan              **/
        /************************************************/
        feedkscan();
        if ((prntask & 0x23) && mode_id != OMODE) {delay();feeding();continue;};

        /***********************************************/
        /**   mode change check during transaction    **/
        /***********************************************/
        if (((voidmd_flg != 1 && mode_id == VMODE) ||
            (voidmd_flg == 1 && mode_id != VMODE)) &&
            ( mode_id != OMODE && regstep != RSTEP_END)) {
            if(mode_id == VMODE)
                org_mode = RXMODE;
            else
                org_mode = VMODE;

            if(!modelcd)
                modelcd = 1;
            err_bit = 1;
            errmsg = E_MODE;
            }
        else if ((mode_id & ZPMMODE) && regstep != RSTEP_END) {
//            if (regstep == RSTEP_TBLON) errmsg=E_TBLON;
            if(voidmd_flg)
                org_mode = VMODE;
            else
                org_mode = RXMODE;
            if(!modelcd)
                modelcd = 1;
            err_bit = 1;
            errmsg = E_MODE;
            }
        else if ((((flg_concid == 1) || (rept_con == 1)) && (mode_id != XMODE)) ||
                    ((clrk_step == 1) && (mode_id != modesave)))
            {  /* yoo0828 */
            org_mode = modesave;
            if(!modelcd)
                modelcd = 1;
            err_bit = 1;
            errmsg = E_MODE;
            }
        else if((mode_id != PMODE) && paddr)
            {
            org_mode = modesave;
            if(!modelcd)
                modelcd = 1;
            err_bit = 1;
            errmsg = E_MODE;
            }
        else if(modelcd) {
            modelcd = 0;
            clrk_prs();
            if (mode_id == OMODE )
                mode_dsp();
            }
        /************************************************/
        /**               error service                **/
        /************************************************/
        if (err_bit) {
            erroron();
//            if(EJ_FLAG != EJ_RAPO)
//                EJ_FLAG = EJ_NORMAL;
            EJ_BINX = MAX_EJLINE;
            if(modelcd==1) {
                pop_menu("",0xff);
                modelcd = 2;
                continue;
                }
            else
                if(!pop_err) {
                    pop_menu("",0xff);
                    pop_err =1;
                }
            blk_prs();
            }
/*        if (pend_flg) continue;           paper end detection */

        if ( (mode_id != modesave) && !modelcd) {              /* mode change */
#ifndef ER5115
            if(err_bit)
                clrk_prs();
            help_flg = 0;
            if((regstep != RSTEP_END) && !(mode_id & RXMODE) && (mode_id != OMODE))
                        pop_lcd = 0;
            mode_chg();
            if(mode_id != PMODE)
                lcd_dsp(1);
            else
                {
                menu_flg = 0;
                sys_lno = MAX_LINE - 1;
                sys_len = 8;
                }
#endif
            init_mdchg();
            clear_bit=0;
            pluon_bit=0;
            flg_logo = 0;
            modesave=mode_id;
            ini_outdtx();
            if( (mode_id & RVMODE) && (regstep == RSTEP_END) ) pop_lcd = 0;
            if( menu_flg && (mode_id == OMODE) ) {
                regstep = svrstep;
                menu_flg = 0;
                }
            if (clerk == 0 && (mode_id & RVMODE)) { dsp_soff(); d_close(); }
            continue;
            };

        if(on_mode)
            {
            comm_sior(0);
            mode_chg();
            continue;
            }
        if (!pfail_flg && regstep == RSTEP_END && paddr == 0 &&
                (SYS_OPT.OPT23 != 9999))
            {
            if (SYS_OPT.OPT23 <= read_time())
                {
                if (pc_on_flg == 0)
                    {
                    comm_sior(1);
                    mode_chg();
                    pc_on_flg=1;
                    continue;
                    }
                }
            else
                pc_on_flg=0;
            };

        /************************************************/
        /***                                          ***/
        /***              OFF     MODE                ***/
        /***                                          ***/
        /************************************************/
        if (mode_id == OMODE ) {
            err_bit=0;
            blink = 0;
            init_omode();
//            mode_line();
            continue;
            };

        /************************************************/
        /***          system schedule check           ***/
        /************************************************/

        if (!(mode_id & XZMODE) || pfail_flg) {
            repot_id=0;
            if (xm_step != XM_DECL) {cashdcl=chckdcl=0;xm_step=0;};
            };

        if (pfail_flg) {
            if (allramclr_bit) {
                sub_endr = 0;
                sv_put = 0;
                sv_get = MAX_SV_LINE;
                revd_index = -1;
                ini_outdtx();
                end_mark=1;
                mkstar();
                logo_only(48);
                if (tempramclr_bit) logo_only(41);
//                else if (ttlcntclr_bit) logo_only(42);
//                else if (grandclr_bit) logo_only(43);
                else {  /* all ram clear */
                    ini_opt();
                    mk_chksum(prt_buffer);
                    prn();
                    sprintf(prt_buffer, "PLU/EJ : %d/%d", MAX_PLU, MAX_EJLINE);
                    prn();
#if 0
                    pgmkey[0]=0xff;
                    for (kk=1;kk<=MAX_DEPTKEY;kk++) {pgmkey[kk]=kk;};
                    for (kk=108;kk<=111;kk++) {pgmkey[kk]=0xff;};
                    for (kk=112;kk<=148;kk++) {pgmkey[kk]=kk+256;};
                    for (kk=149;kk<=159;kk++) {pgmkey[kk]=0xff;};
#endif
                    logo_only(44);
#ifndef BCDBG
                    dtm_buf.time = 0;
                    dtm_buf.date = 10198;
                    set_dtm();
#endif
                    };
                mkline();
                endlogo();
                }
            else {
                if((regstep == RSTEP_CLKON) || (regstep == RSTEP_CLKOF) ||
                   (regstep == RSTEP_TMIO))
                        regstep = RSTEP_END;

                if(help_flg)
                    end_help();
                else if(!err_bit && ( (mode_id & RVMODE) || ((mode_id == XMODE)  && (regstep != RSTEP_END))))
                    {
                    lcd_rec(pop_lcd);
                    if(regstep != RSTEP_END)
                        dsp_tax(-1);
                    }
                if((regstep == RSTEP_MENU1) || (regstep == RSTEP_MENU2) ) {
                    regstep = svrstep;
                    pmenu_inx = 0;
                    }
                }

            if (roff_flg == 1) rpoff_bit=1;
            if (regstep != RSTEP_END) {
                logo_only(45);           /* POWER FAIL */
                if ((regstep == RSTEP_CLKOF) || (regstep == RSTEP_TBLOF)) {
                    nur=pfail_amt;
                    prn_tend(DINX_TOTAL,0,1); /* TOTAL */
                    };
                }
            else {
                endclr();
                send_kp();
                if ((mode_id & RVMODE) && pfend_flg != 0) {
/**
                    if (pfend_flg == POWER_NOR)
                    if (pfend_flg == POWER_CLK)
                    if (pfend_flg == POWER_TBL)
                    if (pfend_flg == POWER_RA)
                    if (pfend_flg == POWER_PO)
                                **/
                    logo_only(45);        /* POWER FAIL */
                    nur=pfail_amt;
                    prn_tend(DINX_TOTAL,0,1); /* TOTAL */
                    regstep = RSTEP_END;
                    endlogr();
                    };
                };
            if (clerk == 0 && (mode_id & RVMODE)) d_close();
            pfail_flg=0;
            if (regstep != RSTEP_END) r_subt();
            else if(!(mode_id & RVMODE)) mode_chg();
            continue;
            }; /* pfail_flg */
       /************************************************/
       /*****       drawer opn sound check         *****/
       /************************************************/
       if (/*pover_bit && */SYS_OPT.OPT2_3 && (mode_id != OMODE)) {
          compdchk();
          if (compd_flg != 0) {       /* drawer open */
             if (almstart_flg == 0) {
                opn_alarm(0);
                almstart_flg=1;
                };

             if (almstart_flg == 1 && err_bit == 0) {
            if (opn_alarm(1)) {
                    errmsg=E_OPNDRW;
                    err_bit=1;
                    opndwr_flg=1;                    /* drawer open flg */
                    };
            };
             } else {almstart_flg=0;                /* drawer close */
                     if (opndwr_flg == 1) {
//                        lcd_rec(2);
                        clrk_prs();
//                        ini_outdtx();
                        };
                     opndwr_flg=0;
                     };
          }
       else if(err_bit && errmsg == E_OPNDRW) {
          compdchk();
          if (!compd_flg )
             clrk_prs();
          }

        /************************************************/
        /**                  wait key                  **/
        /************************************************/
#if 0 // PKR 0813
        if (!err_bit) {
            pend_chk();
/*          if (pend_flg == 1) continue; */
            };
#endif

        func_work=0;
        if (flg_key_pend <= 0) 
            {
            chk_kpend();
            continue;
            }

        keyv=flg_key_buf[flg_key_pend--];
        func_work=(unsigned char)keyv;

        if(func_work == 0xEE) /* REQUOR SYSTEM */
             {
             knur_bit = 1;
             ncnt = 3;
             nur = 0;
             for(p =0; p < 3; p++)
                   nur= nur * 10 + (flg_key_buf[flg_key_pend--] - '0');
             continue;
             }

        if( (func_work == RXTIME) && !ncnt ) { scr_prt(); continue; }

        if( (clerk == 0) && (mode_id & RVMODE) && r_dsoff) {
            if(func_work != 0x7) /* clerk key */ {
                dsp_soff();
                }
            r_dsoff = 0;
            }

        if( (mode_id & RVMODE) && clr_flg && !err_bit && !pop_plu_flg /* && !dsft_flg */&& !mul_bit &&
                clerk)
            {
            clr_flg = 0;
            mode_dsp();
            lcd_dsp(1);
            }

//        /************************************************/
//        /*         schedule for dummy key               */
//        /************************************************/
//        if (!err_bit && clerk == 0 && (mode_id & RVMODE) &&
//            !clear_bit) d_close();
        /************************************************/
        /*****            clear key                 *****/
        /************************************************/
        if ( (func_work == CLEAR) && !modelcd ) {
            if(!opndwr_flg)
                  clrk_prs();
            continue;
            } /* CLEAR key */
//        else if(err_bit) continue;
        else if(err_bit) {
              if(modelcd) continue;
              clrk_prs();
              }

            /* for post tend & buff receipt = sign off || RSTEP_END in RVMODE */
            if ( (mode_id & RVMODE) && (func_work == 0x24 /* cash */) && (!clerk || (regstep == RSTEP_END))) {
                if(!clerk && r_off && !ncnt && buft_cnt) {
                    r_reissue(); continue;
                    }
                if (SYS_OPT.OPT4_1 || SYS_OPT.OPT4_3) {
                   if ((clerk == 0) && SYS_OPT.OPT4_1) {
                      r_dsoff = 1;
//                      mode_dsp();
                      }
                   func = CASH; r_tender();
                   continue;
                   }
                }

        /************************************************/
        /*****        compulsory drawer active      *****/
        /************************************************/
        if ((mode_id & RVMODE) && (SYS_OPT.OPT2_2) && func_work != VALIDC && func_work != KLOGIC) {
            compdchk();
            if (compd_flg != 0) {            /* drawer open */
                errmsg=E_OPNDRW;
                err_bit=1;
                continue;
                };
            };

        if(func_work == R_HELP) {
            help_prc();
            continue;
            }

        if(help_flg) {
            if(func_work == R_PGDN) {
                if(hpage_off + 1 < hpage_max)
                    hpage_off++;
                }
            else if(func_work == R_PGUP) {
                if(hpage_off > 0)
                    hpage_off--;
                }
            else
                continue;
            help_dsp();
            continue;
            }

//970925    if((EJ_INDEX >= MAX_EJLINE) && SYS_OPT.OPT11_2 && (mode_id & RVMODE) && (regstep == RSTEP_END))
    if(EJ_FULLF && SYS_OPT.OPT11_2 && (mode_id & RVMODE) && (regstep == RSTEP_END))
        {
        errmsg = E_EJFULLS;
        err_bit = 1;
        continue;
        }

        /************************************************/
        /**              error rtc check               **/
        /************************************************/
        if(err_bit) continue;

        /************************************************/
        /*****            numeric key               *****/
        /************************************************/
        if((func_nur == 10) && (func_work == 0x4) && !ncnt) /* 00 more tender check */
                {
                ncnt = 1;
                nur = 10;
                }
        else
                func_nur=(char)20;

        switch (func_work) {
            case  ONE   : func_nur=1;break;
            case  TWO   : func_nur=2;break;
            case  THREE : func_nur=3;break;
            case  FOUR  : func_nur=4;break;
            case  FIVE  : func_nur=5;break;
            case  SIX   : func_nur=6;break;
            case  SEVEN : func_nur=7;break;
            case  EIGHT : func_nur=8;break;
            case  NINE  : func_nur=9;break;
            case  ZERO  : func_nur=0;break;
            case  DZERO : func_nur=10;break;
            default     : break;
            }
        if( (ncnt && ((func_work == 0x4) || (func_work == 0x40))) || (((regstep == RSTEP_MENU1) || (menu_flg && (mode_id == PMODE)) ) && (func_nur != 20)) ) {
            if((!ncnt && !func_nur) || (regstep == RSTEP_MENU2) ) { err_bit = 1; errmsg = E_KEY; continue; }
            if(ncnt) {
                    if(!clerk && (func_work != 0x4) && (mode_id & RVMODE)) {
                        clrk_prs(); continue;
                        }
                    dsp_str(0,7,s_blanks);
                    if(func_work == 0x4) /* more menu key */
                         r_menu();
                    else /* more tender key */
                         r_misc();
                    if(err_bit) continue;
                    pmenu_inx = nur;
                    }
            else
                    pmenu_inx = func_nur;

            func_nur = 20;
            regstep = RSTEP_MENU2;
            kk = ksub_bit;
            initky();
            if( menu_flg ){
                if(pmenu_inx < 5) {
                    if(!clerk && (mode_id & RVMODE)) { clrk_prs(); continue; }
                    if(menu_flg != 3)
                        {
                        if(svrstep == RSTEP_RA || svrstep == RSTEP_PO) { errmsg = E_KEY; err_bit = 1; continue; }
                        func = PER1 + pmenu_inx-1;
                        if(kk)
                            ksub_bit = 1;
                        if(FUNCKEY[func-CASH].KEY_ST.PCNT_KEY.PRESET &&
                           !FUNCKEY[func-CASH].KEY_ST.PCNT_KEY.OVERRIDE)
                            pskip = 1;

                        }
                    else
                        func = MISCTND1 + pmenu_inx-1;

                    if( (mode_id == PMODE) || pskip) {
                        pskip = 0;
                        m2_func = 1;
                        reset_menu(1);
                        }
                    else {
                        get_fdesc(func);
                        pop_menu(lcdbuf,'|');
                        taxexm_set(func);
                        rstep_id |= (taxexm_flg & 0xF);
                        dsp_tax(-2);
                        continue;
                        }
//                    m2_func = 1;
//                    reset_menu(1);
                    }
                else {
                    if(menu_flg == 3) {
                    if(!clerk && (mode_id & RVMODE)) { clrk_prs(); continue; }
                        if(pmenu_inx > 8) {
                            err_bit = 1;
                            errmsg = E_KEY; regstep = svrstep; continue;
                            }
                         func = CONV1+pmenu_inx-5;
                         }
                    else {
                         if(!clerk && (mode_id & RVMODE) && (pmenu_inx != 8)) { clrk_prs(); continue; }
                         if((svrstep == RSTEP_RA || svrstep == RSTEP_PO) && (pmenu_inx !=5) && (pmenu_inx != 6))
                                      { errmsg = E_KEY; err_bit = 1; continue; }

                         switch(pmenu_inx) {
                         case 5: func = RA;
                               break;
                         case 6: func = PO;
                               break;
                         case 7: func = RETURN;
                               break;
                         case 8: func = TIMEIO;
                               break;
                         case 9: func = SCALE;
                               if ( (mode_id != PMODE) && FUNCKEY[SCALE-CASH].KEY_ST.SCALE_KEY.MANUAL) {
                                  get_fdesc(func);
                                  pop_menu(lcdbuf,'|');
                                  continue;
                                  }
                               break;
                         case 10:
                                  func = TARE;
                                  if(mode_id == PMODE)
                                      break;
                                  sprintf(lcdbuf,"TARE#");
                                  pop_menu(lcdbuf,'|');
                                  continue;
                         default: regstep = svrstep; err_bit = 1; errmsg = E_KEY; continue;
                               }
                         }
                    }
                    m2_func = 1;
                    if((mode_id != PMODE) && ncnt && ( (func == RA) || (func == PO) ) )
                            reset_menu(2);
                    else
                            reset_menu(1);

                }
            }

        if((func_nur < 11) && (((mode_id == PMODE) && (paddr == 0) && !pfkey_bit) ||
                ((regstep == RSTEP_END) && !rtn_bit && !tare_flg && !scale_bit && (mode_id & XZMODE) && ((rept_step <= 2) && !clrk_step)) ||
                (mode_id == MMODE)))
            {
            nur = func_nur;
            func_work = RCASH;
            ncnt = 1;
            }
        else if (func_nur < 11) {
            if(flg_logo && (mode_id == PMODE))
                {
                pgm_chr(func_nur);
                continue;
                }
            /* seq. is ended ,cap is disappeared by numeric*/
            if (!vd2_bit) void_bit=0;

            knur_bit=1;
            if(ncnt == 0 && (func_nur == 0 || func_nur == 10) && !kdec_bit && (mode_id != PMODE)) {
                if (func_nur == 0) zero_flg=1;
                if (clerk != 0 || (clerk == 0 && !(mode_id & RVMODE))) mkdnur(0);
                if ((mode_id & XPMMODE) || passin_chk()) {
                   ncnt++; /* xpm mode */
                   if(passin_chk() && (func_nur == 10)) ncnt++;
                   }
                clr_dec();
#ifndef ER5115
                if(passin_chk())
                    lcd_dsp(0);
                else
                    lcd_dsp(1);

#endif
                continue;
                };
            ncnt++;

            if (!kdec_bit && ncnt == 1) clr_dec();

            if (kdec_bit){
                if (func_nur == 10) dcnt++;
                dcnt++;
                if (dcnt >= 4) {err_bit = 1;errmsg=E_KEY;continue;};
                };

            if (func_nur != 10) nur= nur * 10 + func_nur;
            else {
                nur*=100;
                ncnt++;
                mv_decbuf();

//                if((mode_id == RMODE) && !clerk)
                    decbuf[0]=0;
                func_nur=0;
                };

            if ((mode_id == PMODE) && (ncnt > sys_len)) {err_bit = 1; errmsg=E_KEY;continue;}  /* PKR0701 */
            else if (ncnt > 8) {err_bit = 1; errmsg=E_KEY;continue;}

            if(!clk_kin) {
                mv_decbuf();
                decbuf[0]=(func_nur);
                }

            if ((clerk != 0 || !(mode_id & RVMODE) || clear_bit) &&
                    ((mode_id != XMODE) || xm_step != XM_TRAIN)) {
                if (!rec2_bit || (mode_id != RMODE)) mkdnur(0);
                };
#ifndef ER5115
            lcd_dsp(0);
#endif
            continue;
            }; /* numeric key */

        /************************************************/
        /*****            decimal key               *****/
        /************************************************/
        if (func_work == DECIMAL){
            if(flg_logo)
                {
                pgm_chr(11);
                continue;
                }
            if (kdec_bit || ncnt > 4) {err_bit = 1; errmsg=E_KEY;continue;};
            if ((mode_id == PMODE) &&
                    ((paddr == 0) ||
                        ((sys_type != TP_REAL) && (sys_type != TP_DLONG) && (sys_type != TP_ELONG) &&
                        (sys_type != TP_TARE) && (sys_type != TP_STRING))))
                {err_bit = 1; errmsg = E_KEY; continue;}
            kdec_bit=1;
            dcnt=0;

            if (nur == 0) {
                clr_dec();
                decbuf[dcnt]=0;
                };
            if ((clerk != 0 || !(mode_id & RVMODE) || clear_bit) &&
                    ((mode_id != XMODE) || xm_step != XM_TRAIN))
                mkdnur(0);
#ifndef ER5115
            lcd_dsp(0);
#endif
            continue;
            }; /* DECIMAL key */
        if((mode_id != PMODE) && !is_xfirst() && !menu_flg)
            lcd_dsp(1);
#if 0 // PKR 0812
        /************************************************/
        /*****           receipt on/off             *****/
        /************************************************/
        if (func_work == RECEIPT ){
            if (regstep != RSTEP_END) {err_bit=1;continue;};
            if (rpoff_bit) {rpoff_bit=0;roff_flg=0;}
            else  {rpoff_bit=1;roff_flg=1;};
            outdtx();
            continue;
            };
#endif
        /************************************************/
        /*****        replacable key service        *****/
        /************************************************/
#if 0
        while(kk <= 0x9f){
            if(inikey[kk] == func_work) break;
            kk++;
            }
        if (kk >= 0x95) continue;

        func=pgmkey[kk];
#endif
        if(!m2_func) {
            func=kk=0;

            while(kk <= MAX_FKEY){
                if(inikey[kk] == func_work){func=kk;break;};
                kk++;
                }
            if (!func || func > MAX_FKEY) continue;  /* PKR0709 */

            if (func >= 0x10) func+=256;
            }
        m2_func = 0;
        /************************************************/
        /*****          dept control                *****/
        /************************************************/
#if 0
        if ((func >= DEPT_START && func <= DEPT_END) &&
           (mode_id != PMODE || (paddr < PADD_DESC1) || (paddr > PADD_DESC4))) {
           if (pdept_no == 5) {
              if (func >= DEPT1 && func <= DEPT5) continue;
              if (func >= DEPT11 && func <= DEPT15) continue;
              func-=5;
              };
           if (pdept_no == 10) {
              if (func >= DEPT1 && func <= DEPT5) continue;
              func-=5;
              };
           };
#endif

        if(menu_flg && ( ((func != CLEAR) && (func != PAGEUP) && (func != PAGEDOWN) && (func != CASH) && (func != MENU)) ||
                    ((func == CASH) && (mode_id == PMODE))) ) {
                   err_bit = 1; errmsg = E_KEY; continue;
                     }


        /************************************************/
        /***          clerk input check               ***/
        /************************************************/
        if( clk_kin && (func != CLK1) ) { errmsg = E_KEY; err_bit =1; continue;}
        if ((func == CLK1) && (mode_id & RVMODE)) {
            if(regstep != RSTEP_END) { errmsg = E_KEY; err_bit = 1; continue;}
            if( !SYS_OPT.OPT15_1 ) {
                if(knur_bit) { errmsg = E_PGM; err_bit = 1; continue; }
                if(!SYS_OPT.OPT1) SYS_OPT.OPT1 = 1;
                func= SYS_OPT.OPT1 + CLK1 -1;
                }
            else if(SYS_OPT.OPT15_1) {
                    if(!knur_bit) {
                         if( (clk_kin && !knur_bit) || (!clk_kin && knur_bit) ) {
                             err_bit = 1; errmsg = E_KEY; continue;
                             }
                         if(!clk_kin)
                             {
                             clr_flg = 0;   clk_kin = 1;
                             pop_menu(s_escode,0x20);continue;
                             }
                          }
                     }
            clear_bit=0;        /* except above keys , close msg disp */

            if (regstep != RSTEP_END) {
                err_bit = 1;
                errmsg=E_KEY;
                continue;
                };
        /* sign off */
                        if (clerk != 0) {
                if (SYS_OPT.OPT15_1) {
                if (nur) {
                    err_bit=1;errmsg=E_CLKCODE;continue;
                    }
                else {
//                    if(!SYS_OPT.OPT19_1)
//                      dsp_soff();
                    sign_off(1); r_dsoff = 0; continue;
                    }
                }
            else {
//                if(SYS_OPT.OPT19_1)
//                    dsp_soff();
                sign_off(1); continue;
                }
            };

        /* sign on */
        if (SYS_OPT.OPT15_1) {    /* clerk code or direct system */
            if(!nur) { errmsg = E_NUMOVER; err_bit = 1; continue; }
            for(kk=0; kk < MAX_CLERK; kk++) {
                if(CLERK_P[kk].secret == nur)
                    break;
                }
            if( kk >= MAX_CLERK ) {err_bit=1;errmsg=E_CLKCODE;continue;}
            else {
                func = CLK1+kk;
//              if(clerk) sign_off();
                }
            };
        pop_lcd = 0;
        clr_flg = 0;
        svclk=0;
        rec_id=0;
        clk_kin = 0;
        clerk=(func - CLK1) + 1;
        mode_dsp();
        ini_outdtx();
        initseq();
        regstep = RSTEP_CLKON;
        okbuf_bit = 0;
        if(PRT_OPT.OPT1_5)
            {
            notbuf_bit = 1;
            start_prn();
            prn_clklog(0, clerk);
            }
        regstep = RSTEP_END;
        continue;
        }
        /************************************************/
        /***                                          ***/
        /***                REG   MODE                ***/
        /***                                          ***/
        /************************************************/
        /*********************************/
        /* report amount over flow check */
        /*********************************/
#if 0
        if ((regstep == RSTEP_END) && (mode_id & RVMODE) &&
            ((func == PLU) || ((func >= DEPT_START) && (func <= DEPT_END)))) {
            if (train_flg == 1)
                ck_sum=rep[0].z[trainttl].total+rep[1].z[trainttl].total;
            else {
                ck_sum=rep[0].z[gross].total+rep[1].z[gross].total;
                ck_sum1=rep[0].z[tmtotl].total+rep[1].z[tmtotl].total;
                if (ck_sum < ck_sum1) ck_sum=ck_sum1;
                ck_sum1=rep[0].z[datotl].total+rep[1].z[datotl].total;
                if (ck_sum < ck_sum1) ck_sum=ck_sum1;
                ck_sum1=rep[0].z[grp_total].total+rep[1].z[grp_total].total;
                if (ck_sum < ck_sum1) ck_sum=ck_sum1;
                ck_sum1=rep[0].z[tplu].total+rep[1].z[tplu].total;
                if (ck_sum < ck_sum1) ck_sum=ck_sum1;
            };

            if (zz_flg == 1 || zz_flg == 2 || ck_sum > 1900000000) {
                mkline();
                err_mess(10);
                feed_view();
                zz_flg=1;
                if (ck_sum > 2000000000) {zz_flg=2;endclr();initseq();};
            };
            };
#endif

        if ( ((func == PAGEUP) || (func == PAGEDOWN)) &&
           ( pop_plu_flg || (regstep != RSTEP_END) || menu_flg)
             && (regstep != RSTEP_MENU2) && (mode_id & RVXPMODE)) {
                if(func == PAGEDOWN) {
                        if(menu_flg == 1) {
                            r_menu();
                            continue;
                            }
                        if(pop_plu_flg)
                            pop_plu_flg += (MAX_LINE-1);
                        else if(revd_index >= 0) {
                            revd_index = (revd_index + (MAX_LINE-2)) % MAX_SV_LINE;
                            if(((sv_put-revd_index + MAX_SV_LINE)%MAX_SV_LINE)
                                <= (MAX_LINE-2)) {
                                dsp_rev(sv_put-(MAX_LINE-2));
                                revd_index = -1;
                                }
                            else {
                                dsp_rev(revd_index);
                                }
                            }
                        }
                else {
                        if(menu_flg == 2) {
                            r_menu();
                            continue;
                            }
                        if(pop_plu_flg) {
                            pop_plu_flg -= (MAX_LINE-1);
                            if(pop_plu_flg <= 0) {
                                pop_plu_flg = 1;
                                continue;
                                }
                            }

                        else {
                            if(revd_index < 0) {
                                kk =(sv_put-sv_get + MAX_SV_LINE) % MAX_SV_LINE;
                                if((sv_get != MAX_SV_LINE) && !kk) kk = MAX_SV_LINE;
                                if( kk >= (MAX_LINE-1)) {
                                    revd_index = (sv_put -(MAX_LINE-2) + MAX_SV_LINE) % MAX_SV_LINE;
                                    }
                                else continue;
                                }

                            if(((revd_index-sv_get + MAX_SV_LINE) % MAX_SV_LINE) >= (MAX_LINE-1)) {
                                revd_index = (revd_index - (MAX_LINE-2) + MAX_SV_LINE) % MAX_SV_LINE;
                                }
                            else {
                                revd_index = sv_get;
                                }
                            dsp_rev(revd_index);
                            }
                       }
                if(pop_plu_flg) {
                        if(pop_plu_flg > 64)
                                pop_plu_flg = 1;
                        plu_pop(pop_plu_flg);
                        }
                continue;
                }
        else if(pop_plu_flg)  {
                    pop_plu_flg = 0;
            lcd_rec(1);
            }
        else if(revd_index >= 0) {
            dsp_rev(sv_put-(MAX_LINE-2));
            revd_index = -1;
            }
        /************************/
        /* PLU/link plu service */
        /************************/
        if (func == PLU && clerk != 0 &&
           ((mode_id & RVMODE) || (regstep != RSTEP_END && mode_id == XMODE)||
           ((rtn_bit || scale_bit ) && mode_id == XMODE))) {


        /* non add # compulsory check */
        if ((FUNCKEY[NOSALE-CASH].KEY_ST.NS_KEY.COM_NADD) && snona_flg != 1) {err_bit=1;errmsg=E_CNONADD;continue;};
            if(!knur_bit) {
                if(menu_flg) {errmsg = E_KEY; err_bit = 1; continue;}
                pop_plu_flg = 1;
                plu_pop(pop_plu_flg);
                continue;
                }
            mst_pluno=0;r_plu();
            while (1) {
                if (lplu_flg == 1) {
                    r_plu();
                    if (err_bit) {lplu_flg=0;break;};
                    continue;
                    };
                if (lplu_flg == 0) {
                    if (mst_pluno != 0) {smst_pluno=mst_pluno;sfunc=PLU;};
                    break;
                    };
                }
           continue;
            };
//#if 0
        if ( regstep == RSTEP_MENU2 ) {
            if((func != CLEAR) && (func != CASH) ) {
                err_bit = 1;
                errmsg = E_KEY; continue;
                }
            if(func == CASH) {
                if((menu_flg == 1) || (menu_flg == 2)) {
                    if(pmenu_inx < 5)
                          func = PER1+pmenu_inx-1;
                    else {
                          if(pmenu_inx == 9)
                                func = SCALE;
                          else  func = TARE;
                          }
                    }
                else {
                    func = MISCTND1+pmenu_inx-1;
                    }
                reset_menu(1);
                }
            }
        else
//#endif
        if(!ncnt && (func == CASH) && ((regstep == RSTEP_RA) || (regstep == RSTEP_PO))) {
            if(regstep == RSTEP_RA)
                func = RA;
            else if(regstep == RSTEP_PO)
                func = PO;
            reset_menu(0);
            }

        if( (regstep == RSTEP_MENU1) && (func != CLEAR) && (func != MENU) && (func != MISCMENU) ) {
            err_bit = 1;
            errmsg = E_KEY; continue;
            }

        if (mode_id & RVMODE) { /* R V MODE */
            clear_bit=0; /* except above keys , close msg disp */
            if (!vd2_bit) void_bit=0;

/*            if (rapo_chk()) continue;*/
            if(!clerk && (func != MENU) && (func != TIMEIO) &&
            !((regstep == RSTEP_TMIO) && (func == CASH))) { clrk_prs (); continue; }

            if ((FUNCKEY[NOSALE-CASH].KEY_ST.NS_KEY.COM_NADD) &&
                (snona_flg != 1) && func != NOSALE) {err_bit=1;errmsg=E_CNONADD;continue;};

            if ((func >= DEPT_START) && (func <= DEPT_END)) {
                func--;
                if(dsft_flg) func += MAX_DPT_KEY;
                r_dept();
                if(!FUNCKEY[DEPT_SFT-CASH].KEY_ST.SFT_KEY.POP_UP)
                    dsft_flg = 0;
                continue;
                };

            if (func == RA || func == PO) {r_rapo();continue;};

            ser_rvx(func);
            continue;
            };
        /************************************************/
        /***                                          ***/
        /***              REPORT  MODE                ***/
        /***                                          ***/
        /************************************************/
        if (mode_id & XZMODE) {
           /****************************/
           /***     X REG MODE       ***/
           /****************************/
           if (mode_id == XMODE) {
                if (!vd2_bit) void_bit=0;

          /** RA/PO/RETURN/RETURN-LEVEL/CHECK CASHING */
/*                if (rapo_chk()) continue;*/

                if (func == RA || func == PO) {
//                    if (clerk == 0) {err_bit=1;errmsg=E_REQCLK;continue;};
                    r_rapo();continue;
                    };
                if (func == RETURN) {
//                    if (clerk == 0) {err_bit=1;errmsg=E_REQCLK;continue;};
                    r_rtn();continue;
                    };
                if (func == TARE) {
//                    if (clerk == 0) {err_bit=1;errmsg=E_REQCLK;continue;};
                    r_tare();continue;
                    };
                if (func == SCALE) {r_scale();continue;};
                if (func == TIMEIO) { r_timeio(); continue; }
                if ((regstep == RSTEP_TMIO) && (func == CASH)) { r_timeiom(); continue;}
#if 0
                if (regstep == RSTEP_END && (xm_step != XM_DECL) && (func == CHECK)) {
                    if (clerk == 0) {err_bit=1;errmsg=E_REQCLK;continue;};
                    r_tender();continue;
                    };
#endif
                if (rtn_bit || tare_flg || scale_bit || regstep != RSTEP_END) {
//                    if (xdl_flag == 1) {err_bit=1;continue;};    /* X mode flag */
                     if ((func >= DEPT_START) && (func <= DEPT_END)) {
                        func--;
                        if(dsft_flg) func += MAX_DPT_KEY;
                        r_dept();
                        if(!FUNCKEY[DEPT_SFT-CASH].KEY_ST.SFT_KEY.POP_UP)
                            dsft_flg = 0;
                        continue;
                        }
                    }

                if (regstep == RSTEP_END) {         /* 92.03.03 */
                    /* for coupon 2 */
                    if ((FUNCKEY[PER1-CASH].KEY_ST.PCNT_KEY.XONLY) &&
                        ( (func >= PER1) && (func <= PER4))) {
                        if (clerk == 0) {err_bit=1;errmsg=E_REQCLK;continue;};
                        r_per();continue;};
                        };

                    if ((regstep != RSTEP_END) || rtn_bit || scale_bit || tare_flg) {
                        ser_rvx(func);
                        continue;
                    };
                };

            /****************************/
            /***     REPORT MODE      ***/
            /****************************/
            /*if (regstep == RSTEP_CLKON) {err_bit=1;errmsg=E_CLKON;continue;};*/
//            if (regstep == RSTEP_TBLON) {err_bit=1;errmsg=E_TBLON;continue;};
            if (regstep != RSTEP_END) {err_bit=1;errmsg=E_KEY;continue;};

            /**** report control *****/
/*            if (func >= CLK1 && func <= CLK4) {
                rep_clk();continue;};

            if (func >= DEPT_START && func <= DEPT_END) {
                rep_dpt();continue;};*/

            if (mode_id == XMODE) {
                switch (func) {
                    case  PAGEUP  : page_up()       ;break;
                    case  PAGEDOWN: page_down()     ;break;
                    case  YES_NO  : x_yesno()       ;break; /* yoo0812 */
                    case  CASH    :
                    case  CHECK   : x_enter()       ;break;
                    case  XTIME   : x_xtime()       ;break;
                    default       : err_bit=1; errmsg=E_KEY;break;
                    }
                }
            else if (mode_id == ZMODE) {
                switch (func) {
                    case  PAGEUP  : page_up()       ;break;
                    case  PAGEDOWN: page_down()     ;break;
                    case  YES_NO  : x_yesno()       ;break; /* yoo0812 */
                    case  CASH    : x_enter()       ;break;
                    default       : err_bit=1; errmsg=E_KEY;break;
                    }
                }
            continue;
            };

        /************************************************/
        /***                                          ***/
        /***             PROGRAM  MODE                ***/
        /***                                          ***/
        /************************************************/
        if (mode_id == PMODE){         /* PKR 0626 */
            if(pfkey_bit)
                {
                if(func == MENU) {
                    r_menu();
                    continue;
                    }
                if(func == MISCMENU) {
                    r_misc();
                    continue;
                    }
                pfkey_bit = 0;
                pgm_fkey();
                continue;
                }
            switch(func) {
                case  YES_NO  : p_yes_no();         break;
                case  PAGEUP  : p_page_up();        break;
                case  PAGEDOWN: p_page_dn();        break;
                case  DEPT_SFT:
                                if(FUNCKEY[DEPT_SFT-CASH].KEY_ST.SFT_KEY.POP_UP)
                                        sv_dft_f = dsft_flg;
                                dsft_flg = 1;       break;
                case  VOID    :
                    if(flg_logo) p_void();
                    else { err_bit=1;errmsg=E_KEY; }
                    break;
                case  CASH    :
                    if((paddr >= PADD_DNO) && (paddr <= PADD_PNO2))
                        {
                        if((nur != 0) || (menu_no != MENU_PGMS))
                            {
                            err_bit=1;errmsg=E_KEY;break;
                            }
                        sall_bit = 1;
                        nur = 1;
                        }
                    p_enter();
                    break;
                default       :
                    if((func >= DEPT_START) && (func <= DEPT_END) && ((paddr == PADD_DNO) || (paddr == PADD_DNO2)))
                        {
                        nur = func - DEPT_START + 1;
                        if(dsft_flg)
                            nur += 12;
                        if(FUNCKEY[DEPT_SFT-CASH].KEY_ST.SFT_KEY.POP_UP)
                                dsft_flg = sv_dft_f;
                        else
                                dsft_flg = 0;
                        if(nur > 9)
                            ncnt = 2;
                        else
                            ncnt = 1;
                        p_enter();
                        }
                    else if((func == PLU) && (nur != 0) &&
                            ((paddr == PADD_PNO) || (paddr == PADD_PNO2)))
                        p_enter();
                    else
                        {err_bit=1;errmsg=E_KEY;}
                    break;
                }
            continue;
            }; /* PMODE */

        /************************************************/
        /***                                          ***/
        /***              MASTER  MODE                ***/
        /***                                          ***/
        /************************************************/
        if (mode_id == MMODE ){
            switch(func) {
                case  CASH    : test_mmode()             ;break;
                case  YES_NO  : x_yesno()       ;break; /* yoo0812 */
                case  PAGEUP  :
                case  PAGEDOWN: break;
                default       : err_bit=1;errmsg=E_KEY   ;break;
                }
            continue;
            }; /* MMODE */
        }  /** while (1) **/
#ifdef BCDBG
}
#endif
}   /** main **/

void clrk_prs()
{
    UBYTE temp=0;
#ifndef ER5115
    if(help_flg)
        {
        end_help();
        return;
        }
    if(revd_index >= 0) {
        dsp_rev(sv_put-(MAX_LINE-2));
        revd_index = -1;
        }
//    if((regstep == RSTEP_MENU1) || (regstep == RSTEP_MENU2) )
//        m_clr = 1;
    if( (menu_flg && (!ncnt || err_bit) ) || !menu_flg)
        {
        if(pfkey_bit)
            dsp_str(0,7,s_blanks);
        if((mode_id == PMODE) && (ncnt != 0))
            pop_lcd = 1;
        if((regstep == RSTEP_MENU1) || (regstep == RSTEP_MENU2) ) {
            regstep = svrstep;
            if(regstep == RSTEP_END)
                voidmd_flg = 0;
            pmenu_inx = 0;
            }
        if((mode_id == XMODE) && (regstep == RSTEP_END)) {
            pop_lcd = 0;
            clrk_step = 0;
            xm_step = 0;
            rept_step = 0;
            start_menu(MENU_MANAGER);
            }
        else
            lcd_rec(2);
        menu_flg = 0;
        }
    pop_plu_flg = 0;
    tmio_flg = 0;
#endif
    if(!err_bit)
        {
        if (mode_id == PMODE)
            {
            if(paddr == PADD_ALPH)
                {
                recov_v();
                err_bit = 1;
                }
            else if(ncnt == 0)
                {
                sys_lno = MAX_LINE - 1;
                sys_len = 8;
                sys_type = 0;
                if((menu_no == MENU_PGM2) || (menu_no == MENU_PGMS))
                    {
                    if((menu_no == MENU_PGMS) && (pgm_flg))
                        endlogo();
                    if(paddr == 0)
                        menu_no = MENU_PGM;
                    p_init();
                    start_menu(menu_no);
                    }
                else if(paddr || pfkey_bit)
                    {
                    if(!pfkey_bit && (paddr >=PADD_PER) && (paddr <= PADD_SCALE))
                        {
                        sub_psoA();
                        temp = 1;
                        }
                    else
                        {
                        if(paddr == PADD_TAX3)
                            make_taxtbl(ppluno-1);
                        p_init();
                        start_menu(MENU_PGM);
                        }
                    }
                if(!temp)
                pfkey_bit = 0;
                }
            else if(pfkey_bit)
                dsp_str(0,7,s_blanks);
            }
        else if(mode_id == MMODE)
            start_menu(MENU_MMODE);
        }
    else if((mode_id == PMODE) && (paddr == PADD_ALPH))
        {
        recov_v();
        err_bit = 1;
        }

    if(flg_logo && !err_bit)
        flg_logo = 0;
    pop_err = 0;
    if(!FUNCKEY[DEPT_SFT-CASH].KEY_ST.SFT_KEY.POP_UP || (mode_id == PMODE))
            dsft_flg = 0;
    void_bit=0;
    mm_step = 0;
    ionur=0;
    rec_id=0;
    svclk=0;
    errmsg=0;
    blink = 0;
    conv_bit=0;
    clk_kin = 0;
    tare_flg = 0;
    rept_con = 0;
    rep_disp = 0;
    taxexm_flg = 0;
    cupn_bit = 0;
//    if ((SYS_OPT.OPT4_1) && regstep == RSTEP_END) clear_bit=1; /* post tender */

    if (clerk != 0 || !(mode_id & RVMODE) || clear_bit) ini_outdtx();
    else d_close();

    if (mode_id & XZMODE) {sfunc=0;first=0;};
    if (regstep == RSTEP_END && (mode_id & XZMODE)) {sfunc=0;first=0;/*clk_rpt=0;*/};
    if (mode_id == MMODE) rec_id=0;  /* PKR 0626 */
    if (regstep == RSTEP_TMIO) tmio_sub();

    if ((flg_concid == 1) && !nur && !err_bit)
       return;
    if ((mode_id & XZMODE) && rept_step) {
       if ((!err_bit) && !nur) {
          if (rept_step == 2) {
             if (mode_id == ZMODE) {
                if (clrk_step) {
                   start_menu(MENU_PRINT);
                   clrk_step = 0;
                }
                else {
                   rept_step = 1;
                   rept_ptd = 0;
                   start_menu(MENU_REPTP);
                }
             }
             else {
                if (rept_con || (clrk_step && (menu_no == MENU_DISPLAY2))) {
                   page_stat =0;
                   start_menu(MENU_DISPLAY2);
                   page_stat =2;
                   rept_step=2;
                   rept_con=0;
                   clrk_step=0;
                }
                else if(clrk_step && (menu_no == MENU_PRINT2)) {
                   page_stat =0;
                   start_menu(MENU_PRINT2);
                   page_stat =1;
                   rept_step=2;
                   clrk_step=0;
                }
                else {
                   if (menu_no == MENU_PRINT2) {
                      start_menu(MENU_PRINT);
                      rept_step = 1;
                   }
                   if (menu_no == MENU_DISPLAY2) {
                      start_menu(MENU_DISPLAY);
                      rept_step = 1;
                   }
                   else {
                      start_menu(MENU_MANAGER);
                      rept_step = 0;
                   }
                   page_stat = 0;
                }
             }
          }
          else {
             page_stat = rept_step = 0;
             mode_chg();
             xm_step = 0;
             if (flg_concid == 1)
                flg_concid = 0;
          }
       clrk_step = 0;
       }
//    else
//       xm_step = 0;
    }
    else if ((mode_id == XMODE) && (regstep == RSTEP_END) && !err_bit && !nur/* && !is_xfirst()*/)
        {
        mode_chg();
        clrk_step = 0;
        }
    init_mdchg();
    clr_dec();
    initseq();
    kclr_bit=1;
#ifndef ER5115
    mode_line();
//    if(!paddr)
    if((mode_id != PMODE) && !is_xfirst())
        lcd_dsp(1);
#endif
}
