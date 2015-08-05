/*******************************************************************/
/********           <er0exmpx.h>                           *********/
/********                                                  *********/
/*******************************************************************/

#ifndef BCDBG
#pragma   memory = no_init
#endif                                 /* BCDBG */
extern  char    flg_dis_txtmp[10];      /*display text 10 byte   */
extern  char    numtxt[50];                     /*address should be not changed */
extern  char    rtcb_flg[25];
/*-----------------------------------------------------------------*/
/*                       WORK VARIABLE                             */
/*-----------------------------------------------------------------*/
extern  char    mode_id;
extern  char    sprt_buffer[50];
extern  char    memoryup;
extern  int     s_dim;
extern  int     e_dim;
extern  char    clk_rpt;
extern  char    rpt_kind;
extern  long    rmtotlh;
extern  long    rmtotl;
extern  long    rmcnt;
extern  unsigned char    comm_buff[MAX_RTBUF];
extern  char    fsbuf[5];
extern  int     len;
extern  int     idx;
extern  int     data_cnt;
extern  unsigned int st_rec, end_rec, rec_size, rec_no;
extern  char    block_cnt;
extern  long    command;
extern  char    cmd_1;
extern  char    cmd_2;
extern  char    cmd_3;
extern  char    cmd_4;
extern  char    cmd_5;
extern  char    *ud_ptr;
extern  int     temp_int;
extern  long    temp_long;
extern  signed  char    flg_key_pend;
extern  char    flg_key_buf[MAX_KEYBUF];
extern  char    comm_save[MAX_CBUF];

extern  char    prt_buffer[MAX_PRTBUF];                 /*address value  9ch            */
extern  char    prt_desc[30];
extern  char    eachbuf[20];
extern  long    ionur;                           /* print disp nur    */
extern  char    *ptxpnt;
extern  char    *point;
extern  char    paddr, bak_paddr;
extern  char    index;
extern  int     first;
extern  char    zero_flg;
extern  char    char_level;
extern  char    rept_step;
extern  char    rept_ptd;     /* yoo 1015 */
extern  char    rep_disp;
extern  signed  char    page_stat;
extern  char    flg_concid;
extern  char    help_cnt;
extern  char    rept_con;
extern  char    xdisp_step;
extern  char    xdisp_cnt;
extern  char    xdisp_cnt2;
extern  char    xdisp_cnt3;
extern  char    xdisp_start;
extern  char    clrk_step;
extern  char    clk_s, clk_e, name_prt;
extern  long    clk_tmttl;
extern  UBYTE   clk_min;               /* 980326 */
/*-----------------------------------------------------------------*/
/*                       ITEMMIZER  (Permanent area)               */
/*-----------------------------------------------------------------*/
extern  char    fdec_inx;
extern  long    mul;
extern  long    mvalue;
extern  int     moksub[20];
extern  char    end_mark;
extern  char    cal_nega;
extern  char    dcnt, pdcnt;
extern  char    ncnt;
extern  char    sdcnt1;
extern  long    nur;                            /* numeric txt       */
extern  long    snur;                           /* numeric txt savr  */
extern  int     pcode;                          /* plu  function key code */
extern  int     spcode;
extern  int     func;                           /* function key code */
extern  int     sfunc;                          /* function key savr */
extern  int     perno;                          /* function key savr */
extern  int     deptno;                         /* dept no. */
extern  UBYTE   tax_brk;
/*----------------------------------------------------------------*/
/*                         permanent area                         */
/*----------------------------------------------------------------*/
extern struct  tables {
        char    t_active;
        char    t_pre_line;
        char    t_line;
        long    t_gamt;
        long    t_taxable[MAX_TAX];
        }table[MAX_TABLE+1]; /* table[0] = temporary table */
extern struct  kpstruct {
        char    k_index;
        int     k_kcode[MAX_KITEM];
        long    k_cnt[MAX_KITEM];
        }kp;
extern  char    stubbuf[MAX_STUB];              /* location change  95.01.14 */
extern  char    buft_cnt;
/* later... delete !! */
extern  long    post_tamt;
extern  char    clerk;
/* later... delete !! */
extern  UBYTE   xm_step, mm_step;
extern  long    cashdcl;
extern  long    chckdcl;
extern  char    zz_flg;

/*-----------------------------------------------------------------*/
/*                         PROGRAM   MEMORY                        */
/*-----------------------------------------------------------------*/
/* later... delete !! */
extern  char    train_flg;
/* later... delete !! */

extern  char    pdept_no;
extern  int     machine_no;
extern  char    tax_tmp[2+MAX_TAX_DESC];
extern  long    tmp_long, last_long;
extern  UBYTE   tax_idx;
extern  char    messdec[MAX_MSG][MAX_MSG_DESC];
extern  long    drawerlimit;
extern  char    pgm_flg, scale_bit;
extern  S_DEPT_PGM dept[MAX_DEPT];
extern  S_PLU_PGM plu[MAX_PLU];
extern  UBYTE   grp_desc[MAX_GROUP][MAX_GRP_DESC];
extern  struct pgm_conv {
                long     value;
                char     deci;
                } conv[MAX_CONV];
extern  struct  pgm_round {
                  int   start;
                  int   end;
                  int   value;
                  } eup_round[MAX_ROUND];

extern  char    r_off;
extern  char    r_cont;
extern  S_SYS_OPT SYS_OPT;
extern  S_PRT_OPT PRT_OPT;
extern  S_FUNCKEY FUNCKEY[MAX_FUNCKEY];
extern  int     tare_weight[MAX_TARE];
extern  S_CLK_PGM CLERK_P[MAX_CLERK];
extern  S_CLKIO CLKIO[MAX_CLERK];
extern  UBYTE   IO_CLK;
extern  S_TAX_TBL tax_table[MAX_TAX];
/*-----------------------------------------------------------------*/
/*                         REPORT MEMORY                           */
/*-----------------------------------------------------------------*/
extern  char    report_start;
extern  long    consno;
extern  long    zcnt, zcnt2;
extern  long    zcnt_t, zcnt_d, zcnt_p, zcnt_c, zcnt_g, zcnt_sp, zcnt_sd, zcnt_ct;
//extern  long    t_consno;
extern  long    t_zcnt;
//extern  long    order_no;
/*extern  int     check_no[MAX_TABLE];*/
/*extern  char     report_end;*/

extern rep_z rep[MAX_FIN+MAX_DEPT+(MAX_CLERK*MAX_CLKITEM)
                                      +25+32+(MAX_GROUP+1)+(MAX_PLU+1)];
#ifdef SPECIAL_REP
extern rep_z2 rep2[MAX_FIN+MAX_DEPT];
#else
extern rep_z2 rep2[MAX_FIN];
#endif
extern long stock_p[MAX_PLU];
extern long stock_d[MAX_DEPT];

extern  char     on_mode;
extern  long     grand;
extern  long     grandh;
extern  char     ram_end;
extern  unsigned char  menu_st;
extern  unsigned char  menu_no;
extern  int m_no;
extern  int l_no;
extern  int      sys_pgno, sys_line, sys_type, sys_len, sys_lno, sys_para;     /* PKR0628 */
extern  UBYTE    sys_mask;
extern  int      sys_cont, max_page, ppluno;
extern  int bak_pgno, bak_line, bak_idx, bak_len, bak_lno, bak_para;
extern  int bak_cont, bak_page, bak_ppluno;
extern  S_SYS_PGM *opt_pgm, *bak_pgm;
extern  unsigned char *opt_ptr, *bak_ptr, alph;
extern  S_PLU_PGM plu_buf;
extern  S_DTM_PGM dtm_buf;
extern  S_CLK_PGM clerk_buf;
extern  UBYTE msg_buf[MAX_MSG_DESC+2];
extern  UBYTE bak_buf[MAX_MSG_DESC+2];
extern  unsigned char menu_st;
extern  unsigned char lcdbuf[MAX_CLM+1];
extern  UBYTE    flg_logo, flg_caps, flg_dbl, chr_idx, sft_idx, last_chr, bak_dbl, bak_logo, bak_sft;
extern  S_CODE_MEM *code_mem;
extern   unsigned char dsp_buf[MAX_LINE][MAX_CLM+1];
extern   unsigned char dsp_bak[MAX_LINE][MAX_CLM+1];
extern  char    errmsg;
extern  char pop_lcd;
extern   UBYTE EJ_FULLF;
extern   int EJ_INDEX, EJ_TINX;
extern   UWORD EJ_FLAG;
extern   UBYTE EJ_BUF[MAX_EJLINE][MAX_RJ+1];
extern   char    convnk;
/*===================================*/
#ifndef BCDBG
#pragma   memory = default
#endif                                 /* BCDBG */
extern   const unsigned char title_str[MAX_TITLE][MAX_CLM+1];
extern   const unsigned char xmenu_str[MAX_XMENU][MAX_CLM+1];
extern   const unsigned char help_str[MAX_HELP*8][MAX_CLM+1]; /* yoo0820 */
extern   const unsigned char nur_str[25][15]; /* yoo1001 */
extern   const unsigned char LOGMSG[8][15]; /* yoo1011 */
