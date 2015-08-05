/*******************************************************************/
/********           <er4table.h>                           *********/
/********                                                  *********/
/*******************************************************************/

#ifndef BCDBG
#pragma   memory = no_init
#endif                                 /* BCDBG */
extern  char    flg_dis_txtmp[10];  /*display text 10 byte   */
extern  char    decbuf[10];
extern  signed  char    flg_key_pend;                    /*entered key count      */
extern  char    flg_key_buf[MAX_KEYBUF];                 /*15 byte                */
extern  char    rtcb_flg[25];
/*-----------------------------------------------------------------*/
/*                       WORK VARIABLE                             */
/*-----------------------------------------------------------------*/
extern  char    mode_id;
extern  char    modesave;
extern  char    prt_buffer[MAX_PRTBUF];                /*address value  9ch            */
/*-----------------*/
/*extern  char    tnd_clrs;*/
extern  char    eachbuf[20];
extern  long    ionur;                           /* print disp nur    */
extern  char    paddr;
extern  int     first;
extern  char    clk_rpt;
extern  char    keyv;
extern  int     ta;
/*-----------------*/
extern  char    zero_flg;
extern  char    sub_endr;
/*extern  char    work_end;*/
extern  unsigned  char    rept_step, rep_disp;
extern  unsigned  char    rept_ptd;   /* yoo 1015 */
extern  signed  char    page_stat;
extern  unsigned  char    flg_concid;
extern   unsigned char dsp_buf[MAX_LINE][MAX_CLM+1];
extern   unsigned char dsp_bak[MAX_LINE][MAX_CLM+1];
extern  UBYTE   help_stp;
extern  UBYTE   hpage_off;
extern  UBYTE   hpage_max;
extern  unsigned  char    help_cnt; /* yoo0820 */
extern  unsigned  char    rept_con; /* yoo0828 */
extern  unsigned  char    xdisp_start; /* yoo0828 */
extern  unsigned  char    clrk_step; /* yoo0924 */
/*-----------------------------------------------------------------*/
/*                       ITEMMIZER  (Permanent area)               */
/*-----------------------------------------------------------------*/
extern  char    fdec_inx;
extern  char    dcnt;
extern  char    ncnt;
extern  long    nur;                             /* numeric txt       */
extern  int     func;                            /* function key code */
extern  int     sfunc;
extern  int     deptno;                          /* function key code */
extern  char    rcnt;                           /* dept rept counter */
extern  int     mst_pluno;                      /*09.26 crs*/
extern  int     smst_pluno;                      /*09.26 crs*/
extern  char    lplu_flg;

extern  long    gamt;
extern   char    vat_inp[MAX_TAX];
extern  char     taxexm_flg;

extern  char    voidmd_flg;
/*extern  char    tnd_clre;*/
/*----------------------------------------------------------------*/
/*                         permanent arear                        */
/*----------------------------------------------------------------*/
extern  char    regstep;
extern  char    clerk;
extern  char    sclerk;
extern  char    roff_flg;
extern  char    end_mark;
extern  UBYTE   xm_step, mm_step;
extern  long    cashdcl;
extern  long    chckdcl;
extern  char    buft_cnt;

extern  char    snona_flg;
extern  char    train_flg;
extern  long    pfail_amt;
extern  char    pfend_flg;
extern  char    zz_flg;
extern  char    dsft_flg;
extern  char    errmsg;
extern  char    pop_lcd, menu_flg,pmenu_inx,svrstep,modelcd,menu_act2,svclk,pop_err,org_mode,r_dsoff,tmio_flg,clk_kin,opndwr_flg;
extern  signed char pop_plu_flg;
extern  unsigned char clr_flg;
extern  unsigned long blink;
extern  KP_REG   kp_regr;
/*extern  char    temp_area;*/
/*-----------------------------------------------------------------*/
/*                         PROGRAM   MEMORY                        */
/*-----------------------------------------------------------------*/
extern  char    pdept_no;
extern  UBYTE   grp_desc[MAX_GROUP][MAX_GRP_DESC];
extern  long    taxrate[MAX_TAX];
extern  S_SYS_OPT SYS_OPT;
extern  S_PRT_OPT PRT_OPT;
extern  S_FUNCKEY FUNCKEY[MAX_FUNCKEY];
extern  char    pgm_flg, scale_bit, pc_on_flg, on_mode;
extern  S_DTM_PGM dtm_buf;
extern  S_CLK_PGM CLERK_P[MAX_CLERK];
extern  S_CLKIO CLKIO[MAX_CLERK];
extern  UBYTE   IO_CLK;
extern  S_TAX_TBL tax_table[MAX_TAX];
extern  char      r_off;
extern  unsigned char    comm_buff[MAX_RTBUF];
extern  S_DEPT_PGM dept[MAX_DEPT];
extern  S_PLU_PGM plu[MAX_PLU];
extern  char    messdec[MAX_MSG][MAX_MSG_DESC];
extern  rep_z rep[MAX_FIN+MAX_DEPT+(MAX_CLERK*MAX_CLKITEM)
                                      +25+32+(MAX_GROUP+1)+(MAX_PLU+1)];
extern  rep_z2 rep2[MAX_FIN];
extern  int    sys_len, sys_line, sys_lno, sys_type, ppluno;  /* PKR0701 */
extern  UBYTE  menu_no;
extern  UBYTE  flg_logo;
extern  unsigned char sv_put, sv_get;
extern  signed  char revd_index;
extern  unsigned char lcdbuf[MAX_CLM+1];
extern  unsigned char   dsp_y;
extern  unsigned char   sdsp_y;
extern  S_CODE_MEM *code_mem;
extern  char    tare_flg, help_flg, scroll_pend;
extern  UWORD EJ_FLAG;
extern  UBYTE EJ_FULLF;
extern  int EJ_INDEX,EJ_BINX;
/*
//extern   char     report_end;

extern   long     grand;
extern   long     grandh;
extern   char     ram_end;
*/
/*===================================*/
#ifndef BCDBG
#pragma   memory = default
#endif                                 /* BCDBG */
