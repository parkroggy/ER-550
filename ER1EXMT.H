/*******************************************************************/
/********           <er0exmt.h>                            *********/
/********                                                  *********/
/*******************************************************************/
/*-----------------------------------------------------------------*/
/*                    TEMP BUFFER(I/O)                             */
/*-----------------------------------------------------------------*/

#ifndef BCDBG
#pragma   memory = no_init
#endif                                 /* BCDBG */
extern   char    flg_dis_txtmp[10];  /*display text 10 byte   */
extern   char    rtcb_flg[25];
/*-----------------------------------------------------------------*/
/*                       WORK VARIABLE                             */
/*-----------------------------------------------------------------*/
extern   char    mode_id;
extern   char    prt_buffer[MAX_PRTBUF];                 /*address value  9ch            */
extern  char     numtxt[50];                     /*address should be not changed */
extern   char    prt_desc[30];
/*extern   char    tnd_clrs;*/
extern   char    reissue;

extern   char    eachbuf[20];
extern   long    ionur;                           /* print disp nur    */
extern  char     *ptxpnt;
extern   long    amount1;
extern   long    rmtotl;
extern   long    change_amt;
extern   char    dptsav_id;
extern   char    dptsav1_id;
extern   char    twosave_id;
extern   char    rstepsv_id;
extern   char    rstepold_id;
extern   char    tare_flg;
extern   char    scale_logo;
extern   char    rpt_flg;
extern   char    price_flg;
extern  unsigned char clr_flg;
extern   char    sub_endr;
/*extern   char    work_end; * when power-on, clear all parameters */
/*-----------------------------------------------------------------*/
/*                       ITEMMIZER  (Permanent area)               */
/*-----------------------------------------------------------------*/
extern   long    gas_cnt;
extern   long    gas_amt;
extern   char    fdec_inx;
extern   char    convnk;
extern   long    conv_amt;
extern   long    cntint; /* memory up count */
extern   long    calmul;
extern   long    mul;
extern   long    smul;
extern   long    upmul;
extern   long    quant;
extern   long    squant;
extern   long    pow_val;
extern   long    mvalue;
extern   long    mvalue2;
extern   int     moksub[20];
extern   char    cal_nega;
extern   long    spnur;
extern   char    spdcnt;
extern   int     cpnfunc;
extern   char    persav_id;
extern   char    dcnt;
extern   char    ncnt;
extern   long    nur;                            /* numeric txt       */
extern   char    sdcnt1;
extern   char    sdcnt2;
//extern   char    sncnt1;                         /* ncnt save of mul */
extern   long    snur;                           /* numeric txt savr  */
extern   char    rcnt;                           /* dept rept counter */
extern   int     pcode;                          /* plu  function key code */
extern   int     spcode;                          /* plu  function key code */
extern   int     mst_pluno;                      /*09.26 crs*/
extern   int     smst_pluno;                      /*09.26 crs*/
extern   char    lplu_flg;
extern   char    m_plu_two;
extern   char    m_plu_rstep;
extern   long    pluvsnur;
extern   char    repeat_flg;
extern   char    plu_rpt_flg;
extern   int     func;                           /* function key code */
extern   int     sfunc;
extern   int     perno;
extern   int     deptno;
extern   long    gamt;
extern   long    sgamt;
extern   long    ssgamt;
extern   long    agamt;
extern   long    asgamt;
extern   long    taxable[MAX_KIND];
extern   long    staxable[MAX_KIND];
extern   long    ctaxable[MAX_KIND];
extern   long    ataxable[MAX_KIND];
extern   long    astaxable[MAX_KIND];
extern   long    tnd_tax[MAX_TAX];
extern   long    mix_taxamt[MAX_TAX];

extern   long    dptamt;
extern   long    rdptamt;
extern   long    unit;
extern   long    sunit;
extern   long    result;
extern   long    cngback_amt;
extern   long    rapo_total;
extern   long    tnd_total;
extern   long    tndtotal;
extern   char	 taxexm_flg;
extern   char    vat_inp[MAX_TAX];
extern   struct  cannns {
		 int     roder;
                 long    rcnt;
                 long    rtotl;
                 } cancl[350];
extern   long    canclcnt;
extern   int     cantime;
extern   long    item_time;
extern   char    voidmd_flg;
/*----------------------------------------------------------------*/
/*                         permanent area                         */
/*----------------------------------------------------------------*/
extern   char    r_off;     /* yoo 0919 */
extern   char    regstep;
extern   REG_MAP reg;
extern struct  tables {
	char    t_active;
        char    t_pre_line;
	char    t_line;
        long    t_gamt;
        long    t_taxable[MAX_TAX];
        }table[MAX_TABLE+1]; /* table[0] = temporary table */
extern char    table_no_flg;
extern char    stable_no;
extern char    tclose_flg;

extern struct  kpstruct {
	char    k_index;
        int     k_kcode[MAX_KITEM];
        long    k_cnt[MAX_KITEM];
        }kp;
extern   char    stubbuf[MAX_STUB];              /* location change  95.01.14 */
extern   char    buf_cnt;
extern   char    buft_cnt;
//extern   long    addcktnd;
extern   long    hash_amt;
extern   long    post_tamt;
extern   char    clerk;
extern   char    sclerk;
extern   char    end_mark;
extern   char    snona_flg;
extern   long    pfail_amt;
extern   char    pfend_flg;
extern   char    train_flg;
extern   char    dsft_flg;
extern   char    errmsg;
extern   char    pop_lcd,menu_flg,menu_act2,pmenu_inx,svrstep;
extern   KP_REG  kp_regr;
/*-----------------------------------------------------------------*/
/*                         PROGRAM   MEMORY                        */
/*-----------------------------------------------------------------*/
extern  long    drawerlimit;
extern  int     tare_weight[MAX_TARE];
extern  S_DEPT_PGM dept[MAX_DEPT];
extern  S_PLU_PGM plu[MAX_PLU];
extern  char sglok_flg, scale_bit;
extern  struct pgm_conv {
                long     value;
                char     deci;
                } conv[MAX_CONV];
extern  S_SYS_OPT SYS_OPT;
extern  S_PRT_OPT PRT_OPT;
extern  S_FUNCKEY FUNCKEY[MAX_FUNCKEY];
/*-----------------------------------------------------------------*/
extern  long    consno;
extern rep_z rep[MAX_FIN+MAX_DEPT+(MAX_CLERK*MAX_CLKITEM)
                                      +25+32+(MAX_GROUP+1)+(MAX_PLU+1)];
extern rep_z2 rep2[MAX_FIN];
extern long stock_p[MAX_PLU];
extern long stock_d[MAX_DEPT];
/*extern   char     report_end;*/

/*extern  long     grand;
extern  long     grandh;
extern  char     ram_end;*/
extern  char scroll_pend;
extern  unsigned char dsp_buf[MAX_LINE][MAX_CLM+1];
extern  unsigned char sv_put, sv_get;
extern  unsigned char lcdbuf[MAX_CLM+1];
extern  unsigned char lcdbuf1[MAX_CLM+1];
extern  S_CODE_MEM *code_mem;
extern  UWORD EJ_FLAG;
extern  UBYTE EJ_FULLF;
extern  int EJ_INDEX;
extern  char flg_concid;
extern  long conv0t, conv1t, conv0e, conv1e;   /* 981210 */
#ifndef BCDBG
#pragma   memory = default
#endif                                 /* BCDBG */
