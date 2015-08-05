/*******************************************************************/
/********           <er0table.h>                           *********/
/********                                                  *********/
/*******************************************************************/
/* Clear area while initial clear - flg_dis_txt ~ temp_area        */
/* Clear area while clear total - report_start ~ report_end        */
/* font_buffer should be at 200H                                   */
/*-----------------------------------------------------------------*/
/*      internal data ram for system control                       */
/*      020h - 0ffh                                                */
/*-----------------------------------------------------------------*/
#include     <er1io51.h>
#ifndef BCDBG
#pragma   memory = data
unsigned     char   key_id      ;   /*  020h  */
unsigned     char   twostep_id  ;   /*  021h  */
unsigned     char   dptstp_id   ;   /*  022h  */
unsigned     char   dptstp1_id  ;   /*  023h  */
unsigned     char   rstep_id    ;   /*  024h  */
unsigned     char   rstep1_id   ;   /*  025h  */
unsigned     char   recover_id  ;   /*  026h  */
unsigned     char   perstp_id   ;   /*  027h  */
unsigned     char   repot_id    ;   /*  028h  */
unsigned     char   progm_id    ;   /*  029h  */
unsigned     char   rec_id      ;   /*  02ah  */
unsigned     char   etc_id      ;   /*  02bh  */
unsigned     char   disp_id     ;   /*  02ch  */
unsigned     char   print_id    ;   /*  02dh  */
unsigned     char   icon_id     ;   /*  02eh  */
unsigned     char   dddd4       ;   /*  02fh  */
#else                                  /* BCDBG */
bit_v bit_v20, bit_v21, bit_v22, bit_v23, bit_v24, bit_v25, bit_v26, bit_v27,
      bit_v28, bit_v29, bit_v2a, bit_v2b, bit_v2c, bit_v2d, bit_v2e, bit_v2f;
#endif                                 /* BCDBG */
/*--------------------------------------------*/
unsigned     char   dph_add     ;   /*  030h  */
unsigned     char   dpl_add     ;   /*  031h  */
unsigned     char   dph0_add    ;   /*  032h  */
unsigned     char   dpl0_add    ;   /*  033h  */
unsigned     char   dph1_add    ;   /*  034h  */
unsigned     char   dpl1_add    ;   /*  035h  */
unsigned     char   dph2_add    ;   /*  036h  */
unsigned     char   dpl2_add    ;   /*  037h  */
unsigned     char   compd_flg   ;   /*  038h  */
unsigned     char   timd_cnt    ;   /*  039h  */
unsigned     char   dig_cnt     ;   /*  03ah  */
unsigned     char   buzz_cnt    ;   /*  03bh  */
unsigned     char   jam_cnt     ;   /*  03ch  */
unsigned     char   jam_flg     ;   /*  03dh  */
unsigned     char   scnl_cnt    ;   /*  03eh  */
unsigned     char   decimal     ;   /*  03fh  */
unsigned     char   prntask     ;   /*  040h  */
unsigned     char   doubf_flg   ;   /*  041h  */
unsigned     char   tmp_cnt     ;   /*  042h  */
unsigned     char   tmp1_cnt    ;   /*  043h  */
unsigned     char   jtmp_cnt    ;   /*  044h  */
unsigned     char   jtmp1_cnt   ;   /*  045h  */
unsigned     char   font_data   ;   /*  046h  */
unsigned     char   fonte_data  ;   /*  047h  */
unsigned     char   pfail_flg   ;   /*  048h  */
unsigned     char   prn_stat    ;   /*  049h  */
unsigned     char   prt_chatt   ;   /*  04ah  */

unsigned     char   prt_rstm    ;   /*  04bh  */
unsigned     char   xoff_flg    ;   /*  04ch  */
unsigned     char   pend_flg    ;   /*  04dh  */
unsigned     char   prgt_flag   ;   /*  04eh  */
unsigned     char   pskp_flag   ;   /*  04fh  */

unsigned     char   io_cnt      ;   /*  050h  */
unsigned     char   tend_flg    ;   /*  051h  */
unsigned     char   rend_flg    ;   /*  052h  */
unsigned     char   siotm_cnt0  ;   /*  053h  */
unsigned     char   siotm_cnt1  ;   /*  054h  */
unsigned     char   s_in_flg    ;   /*  055h  */
unsigned     char   s_out_flg   ;   /*  056h  */
unsigned     char   dsave_flg   ;   /*  057h  */
unsigned     char   stx_flg     ;   /*  058h  */
unsigned     char   etx_flg     ;   /*  059h  */
unsigned     char   dle_flg     ;   /*  05ah  */
unsigned     char   ack_flg     ;   /*  05bh  */
unsigned     char   nack_flg    ;   /*  05ch  */
unsigned     char   crc1_data   ;   /*  05dh  */
unsigned     char   crc2_data   ;   /*  05eh  */
unsigned     char   trx_buf_cnt ;   /*  05fh  */
unsigned     char   data_s_end  ;   /*  050h  */
unsigned     char   comm_status ;   /*  051h  */
unsigned     char   comm_pnt    ;   /*  062h  */
unsigned     char   comm_kind   ;   /*  063h  */
unsigned     char   comm_err    ;   /*  064h  */
unsigned     char   temp1_flg   ;   /*  065h  */
unsigned     char   selkey_flg  ;   /*  066h  */
unsigned     char   rom_flg     ;   /*  067h  */
unsigned     char   fs_data     ;   /*  068h  */
unsigned     char   blk_time    ;   /*  069h  */
unsigned     char   low_add     ;   /*  06ah  */
unsigned     char   high_add    ;   /*  06bh  */
unsigned     char   brom_flg    ;   /*  06ch  */
unsigned     char   disc_flg    ;   /*  06dh  */
unsigned     char   timeol      ;   /*  06eh  */
unsigned     char   timeoh      ;   /*  06fh  */
unsigned     char   lcd_reflg   ;   /*  070h  */
unsigned     char   almstart_flg;   /*  071h  */
#pragma   memory = default
/*-----------------------------------------------------------------*/
/*    next stack area                                              */
/*-----------------------------------------------------------------*/
/*                    TEMP BUFFER(I/O)                             */
/*-----------------------------------------------------------------*/

#pragma   memory = no_init
/*----------------------------------------------------------------*/
char    prt_buffer[MAX_PRTBUF];         /* address value  00h */
char nots[18];
char    flg_dis_txt[10];                /* display text 10 byte */
unsigned char menu_st, menu_no;
S_DTM_PGM dtm_buf;
int   lcd_ch;
unsigned char   lcd_x;
unsigned char   lcd_y;
int m_no, l_no;
UBYTE  flg_logo, flg_caps, flg_dbl, chr_idx, sft_idx, last_chr, bak_dbl, bak_logo, bak_sft;
int sys_pgno, sys_line, sys_type, sys_len, sys_lno, sys_para;      /* PKR0628 */
UBYTE sys_mask;
int sys_cont, max_page, ppluno;
int bak_pgno, bak_line, bak_idx, bak_len, bak_lno, bak_para;
int bak_cont, bak_page, bak_ppluno;
unsigned char lcdbuf[MAX_CLM+1],lcdbuf1[MAX_CLM+1];
unsigned char    jam1_cnt;
char    flg_dis_txtmp[10];              /* display text 10 byte */
char    decbuf[10];                     /* with decimal display */
char    decp_buf[10];                   /* decimal & cap display in the outdtx(); */
char    numtxt[50];
char    sprt_buffer[50];
char    prt_desc[30];                   /* buffer for make_desc(); */
UBYTE   help_stp;
UBYTE   hpage_off;
UBYTE   hpage_max;
unsigned long blink;
signed  char    flg_key_pend;
char    flg_key_buf[MAX_KEYBUF];
char    rtcb_flg[25];
UBYTE msg_buf[MAX_MSG_DESC+2];
UBYTE bak_buf[MAX_MSG_DESC+2];

char    flg_offcht;
char    flg_oncht;
char    flag_fis2;
char    mode_id;                        /* now mode */
char    tmode_id;                        /* now mode */

char    font_buffer[512];              /* Should located in 0x200 */
char    fonte_buffer[512];             /* Should located in 0x400 */
/*----------------------------------------------------------------*/
/*----------------------------------------------------------------*/
/*-----------------------------------------------------------------*/
/*                       WORK VARIABLE                             */
/*-----------------------------------------------------------------*/
/*-----------------*/

char    tnd_clrs;
char    eachbuf[20];                    /* buffer for mkdeach(); */
char    romsum_low;
char    romsum_hig;

long    ionur;                          /* print disp nur */
char    *ptxpnt;
char    *point;
char    paddr, bak_paddr;               /* program address */
char    memoryup;
int     s_dim;
int     e_dim;
char    clk_rpt;
char    desc_lvl;

char    rpt_kind;
char    index;
char    index1;
char    p_tmp;
int     first;

long    rmtotlx;
long    rmtotlh;
long    rmtotl;
long    rmcnt;
long    rmtotl1;
long    amount1;
long    change_amt;
char    dptsav_id;
char    dptsav1_id;
char    twosave_id;
char    rstepsv_id;
char    rstepold_id;
char    keyv;
int     ta;
unsigned char    comm_buff[MAX_RTBUF];
char    fsbuf[5];
int     len;
int     idx;
char    block_cnt;
int     data_cnt;
long    command;
char    cmd_1;
char    cmd_2;
char    cmd_3;
char    cmd_4;
char    cmd_5, *ud_ptr;
unsigned int st_rec, end_rec, rec_size, rec_no;
int     temp_int;
long    temp_long;
//char    comm_save[MAX_CBUF];
char    scale_logo;
char    rpt_flg;                        /* repeat entry */
char    zero_flg;
char    price_flg;
char    char_level;
char    dsft_flg;
char    rep_disp;
char    ret_ldata;
char    rept_con;
char    xdisp_step;
char    xdisp_cnt;
char    xdisp_cnt2;
char    xdisp_cnt3;
char    xdisp_start;

/* test */
char    fs_t_buf[40], sub_endr;
char    work_end; /* when power-on, clear all parameters */
unsigned char rbuff[1];                /* 265 */
unsigned char tbuff[1];                /* 265 */
/*-----------------------------------------------------------------*/
/*                       ITEMMIZER  (Permanent area)               */
/*-----------------------------------------------------------------*/
char    tare_flg;
long    gas_cnt;
long    gas_amt;
char    fdec_inx;
char    convnk;
long    conv_amt;
long    cntint;                         /* memory update count */
long    calmul;
long    mul;
long    smul;
long    upmul;
long    quant;
long    squant;
long    pow_val;
long    mvalue;
long    mvalue2;
int     moksub[20];
char    cal_nega;
/*    percent variable */
long    spnur;
/*float   f_temp;*/
char    spdcnt;
int     cpnfunc;
char    persav_id;
char    dcnt, pdcnt;                    /* count of fraction part */
char    ncnt;                           /* count of numeric */
long    nur;                            /* numeric txt */
char    sdcnt1;                         /* dcnt save of mul */
char    sdcnt2;                         /* dcnt save of quant */
char    sncnt1;                         /* ncnt save of mul */
long    snur;                           /* numeric txt save  */
long    dnur;                           /* float decimal nur */
char    rcnt;                           /* dept repeat counter */
int     pcode;                          /* plu function key code */
int     spcode;                         /* plu function key code save */
int     mst_pluno;
int     smst_pluno;
char    lplu_flg;
char    m_plu_two;
char    m_plu_rstep;
long    pluvsnur;
char    repeat_flg;
char    plu_rpt_flg;
int     func;                           /* function key code */
int     sfunc;                          /* function key save */
int     perno;                          /* Percent index */
int     deptno;                         /* dept no. */
UBYTE   tax_brk;

long    gamt;
long    sgamt;
long    ssgamt;
long    agamt;
long    asgamt;

long    taxable[MAX_KIND];
long    staxable[MAX_KIND];
long    ctaxable[MAX_KIND];
//long    ataxable[MAX_KIND];
//long    astaxable[MAX_KIND];
long    tnd_tax[MAX_TAX];
long    mix_taxamt[MAX_TAX];

long    dptamt;
long    rdptamt;
long    adgamt;
long    unit;
long    sunit;
long    result;                         /* memory update amount */
long    amount;
long    cngback_amt;
long    rapo_total;

long    tnd_total;
long    tndtotal;
long    nettotal;

char            vat_inp[MAX_TAX];
char            taxexm_flg;

struct  cannns {
        int     roder;
        long    rcnt;
        long    rtotl;
        } cancl[350];

long    canclcnt;
int     cantime;
char    voidmd_flg;
long    item_time;
/*char    pa[21];*/
/*char    pb[21];*/
/*char    pc[21];*/
char    tnd_clre;
/*----------------------------------------------------------------*/
/*                         permanent area                         */
/*----------------------------------------------------------------*/
long    clk_tmttl; /* yoo 1012 */
UBYTE   clk_min;                       /* 980326 */
char    regstep;
char    rept_step;   /* yoo0826 */
signed  char    page_stat;   /* yoo0826 */
char    clrk_step;   /* yoo0917 */
char    flg_concid;
char    rept_ptd;    /* yoo 1015 */
char    clk_s, clk_e, name_prt;
char            dwr_min;
char            dwr_sec;
REG_MAP         reg;
#if 0
struct  tables {
        char    t_active;
        char    t_pre_line;
        char    t_line;
        long    t_gamt;
        long    t_taxable[MAX_TAX];
        }table[MAX_TABLE+1]; /* table[0] = temporary table */
char    table_no_flg;
char    stable_no;
char    tclose_flg;

struct  kpstruct {
        char    k_index;
        int     k_kcode[MAX_KITEM];
        long    k_cnt[MAX_KITEM];
        }kp;
struct slipt   {
       long     amt;
       char     step;
       }slip_tend[16];
char    slipt_cnt;
#endif                                 /* PKR 0924 */
char    stubbuf[MAX_STUB];              /* location change  95.01.14 */
char    buf_cnt;
char    buft_cnt;

/* .................. */
//long    addcktnd;
long    hash_amt;
long    post_tamt;
char    clerk;
char    sclerk;
char    roff_flg;
char    end_mark;
UBYTE   xm_step, mm_step;
long    cashdcl;
long    chckdcl;

char    snona_flg;              /* If comp. non-add at sale beginning & non-add, set to 1 */
char    train_flg;
char    zz_flg;
long    pfail_amt;
char    pfend_flg;
UBYTE   tax_idx;
unsigned char   dsp_y;
unsigned char rptcntd;                 /* PSS insert */
unsigned char repeat_f;
char    clr_flg;
char    last_mode;
unsigned char sv_put, sv_get;
signed  char revd_index;
char    errmsg;
UBYTE   opndwr_flg;
char    stub_end[MAX_RJ*2];
UBYTE   pstat_f,pop_lcd, menu_flg, pmenu_inx,svrstep,modelcd,offlcd,clk_kin,sdsp_y,reissue;
UBYTE   menu_act2,svclk,pop_err,org_mode,r_dsoff,tmio_flg,help_flg;
signed  char pop_plu_flg;
char    modesave, scroll_pend;                       /* mode save */
long    conv0t, conv1t, conv0e, conv1e;   /* 981210 */
char    temp_area;
#ifdef  KP
KP_REG  kp_regr;
KPEND_PACK  kppack;
#endif
/* .................. */
/*-----------------------------------------------------------------*/
/*                         PROGRAM   MEMORY                        */
/*-----------------------------------------------------------------*/
//int     machine_no;
char    pc_on_flg, on_mode;
char    pgm_flg, sglok_flg, scale_bit;
char    tax_tmp[2+MAX_TAX_DESC];
long    tmp_long, last_long;
int     tare_weight[MAX_TARE];
S_CLK_PGM CLERK_P[MAX_CLERK];
char    messdec[MAX_MSG][MAX_MSG_DESC];
//long    drawerlimit;
S_DEPT_PGM dept[MAX_DEPT];
S_PLU_PGM plu[MAX_PLU];
UBYTE   grp_desc[MAX_GROUP][MAX_GRP_DESC];
char    r_off;
char    r_cont;
S_SYS_OPT SYS_OPT;
S_PRT_OPT PRT_OPT;
S_FUNCKEY FUNCKEY[MAX_FUNCKEY];
S_TAX_TBL tax_table[MAX_TAX];
unsigned char dsp_buf[MAX_LINE][MAX_CLM+1];
unsigned char dsp_bak[MAX_LINE][MAX_CLM+1];
unsigned char dsp_erc[MAX_LINE][MAX_CLM+1];
S_SYS_PGM *opt_pgm, *bak_pgm;
unsigned char *opt_ptr, *bak_ptr, alph;
char    pdept_no;
//UBYTE bit_buf[8][128];
/*-----------------------------------------------------------------*/
/*                         REPORT MEMORY                           */
/*-----------------------------------------------------------------*/
char    report_start;
long    consno;
long    zcnt, zcnt2;
long    zcnt_t, zcnt_d, zcnt_p, zcnt_c, zcnt_g, zcnt_sp, zcnt_sd, zcnt_ct;
//long    t_consno;
long    t_zcnt;
//long    order_no;
/*int     check_no[MAX_TABLE];*/
/*-----------------------------------------------------------------*/
/* fmode[60];dept[15];clerk[150];time[25];daily[32];group[11];plu[701] */

rep_z rep[MAX_FIN+MAX_DEPT+(MAX_CLERK*MAX_CLKITEM)
                                      +25+32+(MAX_GROUP+1)+(MAX_PLU+1)];
#ifdef SPECIAL_REP
rep_z2 rep2[MAX_FIN+MAX_DEPT];
#else
rep_z2 rep2[MAX_FIN];
#endif
long stock_p[MAX_PLU];
long stock_d[MAX_DEPT];
S_CLKIO CLKIO[MAX_CLERK];
UBYTE   IO_CLK;

UBYTE EJ_FULLF;
int EJ_INDEX,EJ_TINX,EJ_BINX;
UWORD EJ_FLAG;
UBYTE EJ_BUF[MAX_EJLINE][MAX_RJ+1];

long     grand;
long     grandh;
char     report_end;
unsigned char lcd_save[MAX_SV_LINE][MAX_CLM+1];
unsigned char *mem_dest;
unsigned char *mem_src;
unsigned int  mem_len;
char     ram_end;
/*===================================*/
S_CODE_MEM *code_mem;

#pragma   memory = default
#ifdef BCDBG
#include "dbgtable.h"
#endif
const S_ERR_TBL ERR_TBL[MAX_ERR_MSG] = {
        {0,1}, {1,3}, {4,2}, {6,2}, {8,4},
        {12,3},{15,3},{18,2},{20,2},{22,2},
        {24,2},{26,2},{28,3},{31,2},{33,4},
        {37,2},{39,2},{41,4},{45,2},{47,2},
        {49,2},{51,2},{53,2},{55,2},{57,2},
        {59,2},{61,2},{63,3},{66,2},{68,3},
        {71,3},{74,3},{77,2},{79,2}
        };

