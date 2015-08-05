/*******************************************************************/
/********           <er0exm.h>                             *********/
/********                                                  *********/
/*******************************************************************/

#ifndef BCDBG
#pragma   memory = no_init
#endif                                 /* BCDBG */
extern  UBYTE   xm_step, mm_step;
extern  char    rept_con;
extern  char    decp_buf[10];                   /* decimal & cap display in the outdtx(); */
extern  char    flg_dis_txtmp[10];  /*display text 10 byte   */
extern  char    decbuf[10];
extern  signed  char    flg_key_pend;
extern  char    flg_key_buf[MAX_KEYBUF];
extern  char    rtcb_flg[25];
extern  char    reissue;
extern  char    stub_end[MAX_RJ*2];
/*-----------------------------------------------------------------*/
/*                       WORK VARIABLE                             */
/*-----------------------------------------------------------------*/
extern  char    mode_id;
extern  char    tmode_id;
extern  char    modesave;
extern  char    prt_buffer[MAX_PRTBUF];         /*address value  9ch            */
extern  char    numtxt[50];                     /*address should be not changed */
extern  char    sprt_buffer[50];
extern  char    prt_desc[30];                   /* buffer for make_desc(); */
extern  char    romsum_low;
extern  char    romsum_hig;
/*-----------------*/
/*extern  char    tnd_clrs;*/
extern  char    eachbuf[20];

extern  long    ionur;                           /* print disp nur    */
extern  char    *ptxpnt;
extern  char    paddr;
extern  int     ta;
extern  char    keyv;
extern  char    rpt_flg;                        /* repeat entry */
extern char     dsft_flg;
extern  char    price_flg;                      /* repeat entry */
extern  char    fs_t_buf[40];                   /* repeat entry */
extern  char    sub_endr;
/*extern  char    work_end;*/
/*-----------------------------------------------------------------*/
/*                       ITEMMIZER  (Permanent area)               */
/*-----------------------------------------------------------------*/
extern   char    convnk;
extern  char    fdec_inx;
extern  long    cntint; /* memory up count */
extern  long    upmul;
extern  long    mul;
extern  long    pow_val;
extern  long    mvalue;
extern  long    mvalue2;
extern  int     moksub[20];
extern  char    cal_nega;
/*    percent variable */
extern  char    dcnt;
extern  char    ncnt;
extern  long    nur;                            /* numeric txt       */
extern  long    snur;                           /* numeric txt savr  */
extern  char    rcnt;                           /* dept rept counter */
extern  int     pcode;                          /* plu  function key code */
extern  int     func;                           /* function key code */

extern  long    taxable[MAX_KIND];
extern  long    staxable[MAX_KIND];
extern  long    ctaxable[MAX_KIND];
extern  long    ataxable[MAX_KIND];
extern  long    tnd_tax[MAX_TAX];
extern  long    gamt;
extern  long    mix_taxamt[MAX_TAX];
extern   long    dptamt;
extern   long    rdptamt;
extern  char     taxexm_flg;
extern  char     vat_inp[MAX_TAX];

extern  struct  cannns {
        int     roder;
        long    rcnt;
        long    rtotl;
        } cancl[350];
extern   long    rapo_total;
extern  long    canclcnt;
extern  int     cantime;
extern  long    result;
extern  long    amount;
extern  long    rmtotlh;
/*extern  char    tnd_clre;*/

/*----------------------------------------------------------------*/
/*                         permanent arear                        */
/*----------------------------------------------------------------*/
extern  char    regstep;
extern  char            dwr_min;
extern  char            dwr_sec;

extern struct  tables {
        char    t_active;
        char    t_pre_line;
        char    t_line;
        long    t_gamt;
        long    t_taxable[MAX_TAX];
        }table[MAX_TABLE+1]; /* table[0] = temporary table */
extern char    table_no_flg;
extern char    tclose_flg;

extern struct  kpstruct {
        char    k_index;
        int     k_kcode[MAX_KITEM];
        long    k_cnt[MAX_KITEM];
        }kp;
extern  char    slipt_cnt;

extern  char    stubbuf[MAX_STUB];
extern  char    buf_cnt;
extern  char    buft_cnt;

//extern  long    addcktnd;
extern  long    post_tamt;
extern  char    clerk;
extern  char    sclerk;
extern  char    end_mark;
extern  char    snona_flg;
extern  char    pfend_flg;
extern  char    errmsg;
extern  char    pop_lcd, menu_flg, pmenu_inx, modelcd, offlcd,pop_err,org_mode,clk_kin,opndwr_flg;
extern  KP_REG  kp_regr;
extern  KPEND_PACK  kppack;
extern  unsigned long blink;
extern  UBYTE   help_stp;
extern  UBYTE   hpage_off;
extern  UBYTE   hpage_max;
/*-----------------------------------------------------------------*/
/*                         PROGRAM   MEMORY                        */
/*-----------------------------------------------------------------*/
/* later... delete !! */
extern  char    train_flg;
/* later... delete !! */

extern  char    pdept_no;
extern  int     machine_no;
extern  long    taxrate[MAX_TAX];
extern  char    messdec[MAX_MSG][MAX_MSG_DESC];
extern  char    pgm_flg, scale_bit;
extern  S_DEPT_PGM dept[MAX_DEPT];
extern  S_PLU_PGM plu[MAX_PLU];
extern  UBYTE   grp_desc[MAX_GROUP][MAX_GRP_DESC];
extern  struct  pgm_round {
                  int   start;
                  int   end;
                  int   value;
                  } eup_round[MAX_ROUND];

extern  UBYTE flg_logo;
extern  S_SYS_OPT SYS_OPT;
extern  S_PRT_OPT PRT_OPT;
extern  S_FUNCKEY FUNCKEY[MAX_FUNCKEY];
extern  S_CLK_PGM CLERK_P[MAX_CLERK];
extern  S_CLKIO CLKIO[MAX_CLERK];
extern  UBYTE   IO_CLK;
extern  S_TAX_TBL tax_table[MAX_TAX];
extern  char      r_off;
extern  char      r_cont;
/*-----------------------------------------------------------------*/
/*                         REPORT MEMORY                           */
/*-----------------------------------------------------------------*/
extern  char    report_start, report_end;
extern  long    consno;
/*-----------------------------------------------------------------*/
extern rep_z rep[MAX_FIN+MAX_DEPT+(MAX_CLERK*MAX_CLKITEM)
                                      +25+32+(MAX_GROUP+1)+(MAX_PLU+1)];
extern rep_z2 rep2[MAX_FIN];

/*extern   char     report_end;*/

extern   long     grand;
extern   long     grandh;
extern   char     ram_end;
extern   int   lcd_ch;
extern   unsigned char   lcd_x;
extern   unsigned char   lcd_y;
extern   unsigned char   dsp_y;
extern   unsigned char   sdsp_y;
extern   unsigned char dsp_buf[MAX_LINE][MAX_CLM+1];
extern   unsigned char dsp_bak[MAX_LINE][MAX_CLM+1];
extern   unsigned char dsp_erc[MAX_LINE][MAX_CLM+1];
//extern   UBYTE bit_buf[8][128];
extern   unsigned char menu_st, menu_no;
extern   int m_no, l_no;
extern   unsigned char rptcntd;                 /* PSS insert */
extern   unsigned char repeat_f;
extern   char clr_flg;
extern   char last_mode;
extern   int logo_cnt;
extern   unsigned char sv_put, sv_get;
extern   unsigned char lcd_save[MAX_SV_LINE][MAX_CLM+1];
extern   unsigned char sv_put, sv_get;
extern   signed char revd_index;
extern   unsigned char lcdbuf[MAX_CLM+1],lcdbuf1[MAX_CLM+1];
extern   unsigned char tempsv[4000];
extern   unsigned char *mem_dest;
extern   unsigned char *mem_src;
extern   unsigned int  mem_len;
extern   unsigned char rep_disp;
extern   unsigned char rept_step;
extern   unsigned char rept_ptd;    /* yoo 1015 */
extern   signed char page_stat;
extern   unsigned char clrk_step;
extern   int     sys_pgno, sys_line, sys_type, sys_len, sys_lno;     /* PKR0628 */
extern   UBYTE   sys_mask;
extern   unsigned char rbuff[1];
extern   unsigned char tbuff[1];
extern   S_CODE_MEM *code_mem;
extern   unsigned char    comm_buff[MAX_RTBUF];
extern   char    comm_save[MAX_CBUF];
extern   UBYTE EJ_FULLF;
extern   int EJ_INDEX,EJ_TINX;
extern   UWORD EJ_FLAG;
extern   UBYTE EJ_BUF[MAX_EJLINE][MAX_RJ+1];
extern   int     tare_weight[MAX_TARE];
extern   char    scale_logo, scroll_pend;
extern   char    tare_flg, help_flg, flg_concid;
/*===================================*/
#ifndef BCDBG
#pragma   memory = default
#endif                                 /* BCDBG */
extern  const UBYTE   ERRMSG[MAX_ERR_STR][19];
extern  const S_ERR_TBL ERR_TBL[MAX_ERR_MSG];
