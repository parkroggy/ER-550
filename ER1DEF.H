              //PLU70, PLU300, PLU500
#define         PLU70
//#define         SPECIAL_REP

#ifdef SPECIAL_REP
#ifdef PLU70
#define         VER_STR     "aSP"
#endif
#ifdef PLU300
#define         VER_STR     "bSP"
#endif
#ifdef PLU500
#define         VER_STR     "cSP"
#endif
#else       // SPECIAL_REP
#ifdef PLU70
#define         VER_STR     "aP "
#endif
#ifdef PLU300
#define         VER_STR     "bP "
#endif
#ifdef PLU500
#define         VER_STR     "cP "
#endif
#endif      // else

#define         KP      1
#define         PCCOMM  1

#define         UBYTE unsigned char
#define         UWORD unsigned int

#define         STR_ADDR       0x02aa00

#define         SUCCESS         0
#define         FAIL            1
#define         FAULT           -99999999

#define         _SP_OPN         0
#define         _KP_OPN         1

#define         EJ_NORMAL       0x0
#define         EJ_CASH         0x1
#define         EJ_CHECK        0x2
#define         EJ_MISC         0x4
#define         EJ_PER          0x8
#define         EJ_RAPO         0x10
#define         EJ_RET          0x120
#define         EJ_ECV          0x140
#define         EJ_NS           0x80
#define         EJ_TEND         0x7 /* (EJ_CASH+EJ_CHECK+EJ_MISC) */
#define         EJ_PERM         0x108
#define         EJ_MINUS        0x100
#define         EJ_END          0x200
#define         EJ_NOPRT        0x298
#define         EJ_REPORT       0x299
#define         EJ_CANCEL       0x3FF
#define         TYPE_CANCEL     0xFF

#ifdef BCDBG
#define         BLK_PRD     0x800
#else
#define         BLK_PRD     0x100
#endif

#define         _TM_290II       1
#define         _TM_300         2
#define         _TM_T80         3
#define         _IDP_3540       4

#define         LOGO_VOID       95
#define         LOGO_MODEL      96
#define         LOGO_H          97
#define         LOGO_STAR       98
#define         LOGO_LINE       99
#define         LOGO_BLANK      100

/***** errmsg define *****/
#define     E_GENERAL   1
#define     E_CLKCODE   2
#define     E_KEY       3
#define     E_XONLY     4
#define     E_COMPDEC   5
#define     E_AMTTND    6
#define     E_HALO      7
#define     E_INACTDEPT 8
#define     E_INACT     9
#define     E_OPEN      10
#define     E_PRESET    11
#define     E_VOID      12
#define     E_AMTOVER   13
#define     E_SPLITPR   14
#define     E_PGM       15
#define     E_CNONADD   16
#define     E_NUMOVER   17
#define     E_DRWOVER   18
#define     E_REQCLK    19
#define     E_OVERRIDE  20
#define     E_UNDERTND  21
#define     E_OPNDRW    22
#define     E_TIMEIO    23
#define     E_EJFULLW   24
#define     E_EJFULLS   25
#define     E_TIMEOUT   26
#define     E_SCALE     27
#define     E_COMPTARE  28
#define     E_IN_TARE   29
#define     E_MANSCL    30
#define     E_COMPSCL   31
#define     E_MODE      32
#define     E_NOTINV    33
#define     E_TRAIN     34
#define     E_BUZZER    39

/***** display symbol *****/
#define         D_SUBTOTAL      5
#define         D_A             10
#define         D_CHANGE        12
#define         D_DEPT          13
#define         D_E             14
#define         D_F             15
#define         D_L             16
#define         D_PLU           18
#define         D_MINUS         20
#define         D_TENDER        21
#define         D_BLANK         22

#define         P_X             0
#define         P_LB            1
#define         P_KG            2
#define         P_SLASH         3
#define         P_FOR           4
#define         P_No            5

#define         IS_DEPT         0
#define         IS_PLU          1

#define         MAX_SPECIAL     32
#define         MAX_PRTBUF      100
#define         MAX_RJ          26
#define         MAX_TARE        5
#define         MAX_PGMKEY      60
#define         MAX_TAX         4
#define         MAX_TAX_DESC    12
#define         MAX_KIND        7
#define         MAX_TAXBRK      60
#define         MAX_CLERK       20
#define         MAX_GROUP       10
#define         MAX_GRP_DESC    12
#define         MAX_DPT_KEY     12
#define         MAX_DEPT        24
#define         MAX_DEPT_DESC   12
#ifdef SPECIAL_REP
#ifdef BCDBG
#define         MAX_PLU         100
#define         MAX_EJLINE      30
#else                                  /* BCDBG */
#ifdef PLU500
#define         MAX_PLU         490
#define         MAX_EJLINE      820
#endif
#ifdef PLU300
#define         MAX_PLU         290
#define         MAX_EJLINE      1070
#endif
#ifdef PLU70
#define         MAX_PLU         60
#define         MAX_EJLINE      1350
#endif                                 /* PLU70 */
#endif                                 /* else - BCDBG*/
#else                                  /* SPECIAL_REP */
#ifdef BCDBG
#define         MAX_PLU         100
#define         MAX_EJLINE      30
#else                                  /* BCDBG */
#ifdef PLU500
#define         MAX_PLU         500
#define         MAX_EJLINE      820
#endif
#ifdef PLU300
#define         MAX_PLU         300
#define         MAX_EJLINE      1070
#endif
#ifdef PLU70
#define         MAX_PLU         70
#define         MAX_EJLINE      1350
#endif                                 /* PLU70 */
#endif                                 /* else - BCDBG*/
#endif                                 /* else - SPECIAL_REP */
#define         S_PCODE         MAX_PLU
#define         MAX_PLU_DESC    12
#define         MAX_FUNC        40
#define         USE_FUNC        MAX_CLERK+MAX_GROUP+10
#define         MAX_FUNC_DESC   12
#define         MAX_MSG         5
#define         MAX_MSG_DESC    MAX_RJ
#define         MAX_PERCENT     4
#define         MAX_CONV        4
#define         MAX_CHARGE      2
#define         MAX_PRECASH     1
#define         MAX_ROUND       5
#define         MAX_SYSTEM      70
#define         USE_SYSTEM      54      /* now using option */
#define         MAX_TABLE       1
#define         MAX_TITEM       1
#define         MAX_KITEM       30
#define         MAX_KEYBUF      25
#define         MAX_RTBUF       300
#define         MAX_CBUF        2300
#define         MAX_FIN         80        /* 981219 */
#define         MAX_DEPT_REP    MAX_DEPT
#define         MAX_CLKITEM     50
#define         USE_CLKITEM     34
#define         MAX_STUB        1650
#define         MAX_ERR_MSG     41
#define         MAX_ERR_STR     81
#define         MAX_CIO         16
#define         MAX_FUNCKEY     0x1d

/***** display report step define *****/
#define         FIN_DEPTD       11
#define         FIN_ITEMD       12
#define         FIN_ITEMP       13
#define         FIN_DEPTP       14
#define         DISP_TIMED      21
#define         DISP_DAYD       22
#define         DISP_PLUD       31
#define         DISP_STP        32
#define         DISP_STD        33
#define         DISP_CLKD       41
#define         DISP_GROUPD     71
#define         DISP_TMIOD      81
#define         REPT_DEND       99
/******         TAX DEFINE      ******/
#define         T_ADDON         0
#define         T_TABLE         1
#define         T_VAT           2

#define         TAX_KIND        7
#define         TAX1            0
#define         TAX2            1
#define         TAX3            2
#define         TAX4            3
#define         TAX14           4
#define         TAX24           5
#define         TAX34           6
#define         TAX_LEN         28
#define     P_TAX       0x7b
/***** register step define *****/
#define         RSTEP_END       0
#define         RSTEP_SRT       1
#define         RSTEP_DPT       2
#define         RSTEP_PLU       3
#define         RSTEP_RTN       4
#define         RSTEP_CPN       5
#define         RSTEP_PER       6
#define         RSTEP_VD1       7
#define         RSTEP_VD2       8
#define         RSTEP_CVD1      9
#define         RSTEP_PVD1      10
#define         RSTEP_ADDCK     11
#define         RSTEP_CLKON     12
#define         RSTEP_CLKOF     13
#define         RSTEP_TBLON     14
#define         RSTEP_TBLOF     15

#define         RSTEP_RA        16
#define         RSTEP_PO        17
#define         RSTEP_BACKRA    18
#define         RSTEP_STEND     19

#define         RSTEP_SPL       21
#define         RSTEP_TRI       22
#define         RSTEP_DIS       23
#define         RSTEP_SUR       24
#define         RSTEP_MENU1     25
#define         RSTEP_MENU2     26

#define         RSTEP_TMIO      27
//#define         RSTEP_TMIO2     28
//#define         RSTEP_TMIO3     29

/***** power fail step define *****/
#define         POWER_NOR       1
#define         POWER_CLK       2
#define         POWER_TBL       3
#define         POWER_RA        4
#define         POWER_PO        5

/***** paddr define *****/
#define         PADD_TAX0       1       /* tax pgm */
#define         PADD_TAX1       2       /* tax pgm */
#define         PADD_TAX2       3       /* tax pgm */
#define         PADD_TAX3       4       /* tax pgm */

#define         PADD_SYSTEM     10      /* system option pgm */
#define         PADD_PRINT      11      /* print option pgm */
#define         PADD_DEPT       12      /* dept. pgm */
#define         PADD_PLU        13
#define         PADD_DTM        14
#define         PADD_CLK        15      /* clerk pgm */
#define         PADD_DESC       16      /* dept desc pgm */
#define         PADD_CIO        17      /* clerk i/o pgm */
#define         PADD_INVP       18
#define         PADD_INVD       19
#define         PADD_GRP        20
#define         PADD_TARE       21

#define         PADD_CNO        25
#define         PADD_CNO2       26
#define         PADD_DNO        27
#define         PADD_DNO2       28
#define         PADD_PNO        29
#define         PADD_PNO2       30

#define         PADD_PER        41      /* % key pgm */
#define         PADD_CNV        42      /* conversion key pgm */
#define         PADD_NS         43      /* no sale key pgm */
#define         PADD_CASH       44      /* cash key pgm */
#define         PADD_CHECK      45      /* check key pgm */
#define         PADD_MISC       46      /* misc tend key pgm */
#define         PADD_VOID       47      /* void key pgm */
#define         PADD_RETURN     48      /* return key pgm */
#define         PADD_CANCEL     49      /* cancel key pgm */
#define         PADD_PO         50      /* po key pgm */
#define         PADD_RA         51      /* ra key pgm */
#define         PADD_SFT        52      /* Dept shift key pgm */
#define         PADD_SCALE      53

#define         PADD_ALPH       55      /* Other alpha program */

#define         PADD_SCAN       60      /* pgm contents scan */

/***** index in clkdec[][] *******/
#define         DINX_CASH       14
#define         DINX_CHECK      15
//#define         DINX_CHG1       16
//#define         DINX_CHG2       17
#define         DINX_CNG        16
#define         DINX_TOTAL      17
#define         DINX_RA         18
#define         DINX_PO         19
//#define         DINX_CHKNO      22
//#define         DINX_CHKTND     23
#define         DINX_NONADD     20
#define         DINX_ADDCK      21
#define         DINX_MISC1  22
#define         DINX_MISC2  23
#define         DINX_MISC3  24
#define         DINX_MISC4  25

/***** report array define *****/
/*   finance    60 ea   */
#define  podept         0
#define  nedept         1
#define  adjdpt         2
#define  nontaxamt      3      /* start yoo 1008 */
#define  tax1abl        4
#define  tax2abl        5
#define  tax3abl        6
#define  tax4abl        7
#define  tax1amt        8
#define  tax2amt        9
#define  tax3amt        10
#define  tax4amt        11
#define  per1tl         12
#define  per2tl         13
#define  per3tl         14
#define  per4tl         15    /* end yoo 1008 */
#define  netsale        16
#define  crtax1amt      17
#define  crtax2amt      18
#define  crtax3amt      19
#define  crtax4amt      20
#define  retn           21
#define  void1          22             /* Err Corr */
#define  void2          23             /* Prev Void */
#define  void3          24             /* Mode Void */
#define  void4          25             /* Cancel */
#define  gross          26
#define  cshsale        27
#define  chksale        28
#define  misc1sale      29
#define  misc2sale      30
#define  misc3sale      31
#define  misc4sale      32
#define  ra             33
#define  po             34
/* #define  hashamt        35 */
#define  nppdpt         35
#define  audact         36
#define  nosale         37      /* no sale count & non add no. */
#define  cshindw        38
#define  chkindw        39
#define  misc1dw        40
#define  misc2dw        41
#define  misc3dw        42
#define  misc4dw        43
#define  conv1          44             /* 981219 */
#define  conv1h         45
#define  conv1m1        46
#define  conv1m2        47
#define  conv1m3        48
#define  conv1m4        49
#define  conv2          50
#define  conv2h         51
#define  conv2m1        52
#define  conv2m2        53
#define  conv2m3        54
#define  conv2m4        55
#define  conv3          56
#define  conv3h         57
#define  conv3m1        58
#define  conv3m2        59
#define  conv3m3        60
#define  conv3m4        61
#define  conv4          62
#define  conv4h         63
#define  conv4m1        64
#define  conv4m2        65
#define  conv4m3        66
#define  conv4m4        67
#define  drwtl          68
#define  trainttl       69
/*------------------------*/
#define         USE_FIN         trainttl+1
#define         F_NONTAXA       nontaxamt    /*yoo 1001 */
#define         F_TAXFROM       tax1abl
#define         F_TAXTO         tax4amt
#define         F_CRTAX1        crtax1amt
#define         F_CRTAX4        crtax4amt
#define         F_NETSALE       netsale
#define         F_RTN           retn
#define         F_MODEVOID      void3
#define         F_GROSS         gross
#define         F_AUDACT        audact
#define         F_DRWR          drwtl
#define         F_NOSALE        nosale
#define         F_CASHIND       cshindw
/* #define         F_CASHIN        cshindw */         /* yoo 1002 */
#define         F_CHKIN         chkindw
#define         F_MISC1D        misc1dw     /* yoo 1002 */
#define         F_CONV1         conv1
#define         F_CONV4         conv4m4     /* 981219 */
/*=======================*/
/*       deptup  15ea(15)       */
#define  d_base MAX_FIN         /* =60 */
#define  dptup  d_base+func
#define  dpt_end (d_base+MAX_DEPT_REP)
/*=======================*/
/*       clerk  15ea*10=150       */
#define  c_base (d_base+MAX_DEPT_REP)   /* =75 */
#define  clkup  (c_base+(clerk-1)*MAX_CLKITEM)
#define  cnetsale      (clkup+0 )
#define  cnontaxamt    (clkup+1 )
#define  ctax1abl      (clkup+2 )
#define  ctax2abl      (clkup+3 )
#define  ctax3abl      (clkup+4 )
#define  ctax4abl      (clkup+5 )
#define  ctax1amt      (clkup+6 )
#define  ctax2amt      (clkup+7 )
#define  ctax3amt      (clkup+8 )
#define  ctax4amt      (clkup+9 )
#define  cper1tl       (clkup+10)
#define  cper2tl       (clkup+11)
#define  cper3tl       (clkup+12)
#define  cper4tl       (clkup+13)
#define  ccrtax1amt    (clkup+14)
#define  ccrtax2amt    (clkup+15)
#define  ccrtax3amt    (clkup+16)
#define  ccrtax4amt    (clkup+17)
#define  cretn         (clkup+18)
#define  cvoid1        (clkup+19)
#define  cvoid2        (clkup+20)
#define  cvoid3        (clkup+21)
#define  cvoid4        (clkup+22)
#define  cra           (clkup+23)
#define  cpo           (clkup+24)
#define  ccshindw      (clkup+25)
#define  cchkindw      (clkup+26)
#define  cmisc1dw      (clkup+27)
#define  cmisc2dw      (clkup+28)
#define  cmisc3dw      (clkup+29)
#define  cmisc4dw      (clkup+30)
#define  cdrwtl        (clkup+31)
#define  ctrainttl     (clkup+32)
#define  cnosale       (clkup+33)
#define         FC_NETSALE       0      /*yoo 1001 */
#define         FC_NONTAXA       1
#define         FC_TAXTO         9
#define         FC_CRTAX1        14
#define         FC_CRTAX4        17
#define         FC_RTN           18
#define         FC_MODEVOID      21
#define         FC_CASHIND       25
#define         FC_DRWR          31
#define         FC_NOSALE        33
/*=======================*/
/*      time   25ea              */
#define  t_base c_base+(MAX_CLERK*MAX_CLKITEM)   /* =225 */
#define  timeup t_base+rtcb_flg[5]*10+rtcb_flg[4]
#define  tmtotl t_base+24
/*=======================*/
/*      daily  32ea              */
#define  da_base t_base+25      /* =250 */
#define  dailyup da_base+rtcb_flg[8]*10+rtcb_flg[7]
#define  datotl da_base+31
/*=======================*/
/*       group   11ea    */
#define  g_base  da_base+32            /* =282 */
#define  grp_total g_base+MAX_GROUP
/*=======================*/
/*       pluup   701ea(701)       */
#define  p_base g_base+MAX_GROUP+1   /* =293 */
#define  pluup  p_base+pcode
#define  tplu   p_base+MAX_PLU
/*=======================*/
#define  e_base  tplu+1

#define  H_V_ST     0
#define  H_R_ST     2
#define  H_X_ST     4
#define  H_DECL     7
#define  H_RCT_C    9
#define  H_RONOFF   10
#define  H_TRAIN    11
#define  H_FINAN    15
#define  H_Z_ST     28
#define  H_P_ST     30
#define  H_M_ST     49

#define  XM_DECL    1
#define  XM_DECLF   2
#define  XM_RCONT   3
#define  XM_RCONTS  4
#define  XM_RONOFF  5
#define  XM_RONOFFS 6
#define  XM_TRAIN   7
#define  ZM_REJ     8
#define  ZM_REJS    9
#define  MM_CLRTTL  10
#define  MM_CLRTTLS 11
#define  MM_CLRGT   12
#define  MM_CLRGTS  13
#define  MM_TEST    14

typedef struct sys_para {
    UBYTE OPT1;                        /* Clerk assigned when CLERK key is pushed */

    UBYTE OPT2_1:1;                    /* Is beeper active */
    UBYTE OPT2_2:1;                    /* Does drawer need to be shut for register to operate */
    UBYTE OPT2_3:1;                    /* Open drawer alarm */
    UBYTE OPT2_4:1;                    /* Allow Dollar Entry Without Scale */
    UBYTE OPT2_5:1;                    /* Manager required For Time I/O */
    UBYTE FILLER2:3;

    UBYTE OPT3_1:1;                    /* PLU SALES AFFECT DEPT COUNTER */
    UBYTE OPT3_2:1;                    /* DO NOT ALLOW CHECK CASHING */
    UBYTE OPT3_3:1;                    /* Volume Unit  0:Gal, 1:Ltr */
    UBYTE FILLER3:5;

    UBYTE OPT13_1;                     /* Port is  Scale          : 0 */
                                       /*          Remote Journal : 1 */
                                       /*          KP             : 2 */
                                       /*          Liquor         : 3 */

    UBYTE OPT4_1:1;                    /* Allow post tender */
    UBYTE OPT4_2:1;                    /* Open drawer on post tender */
    UBYTE OPT4_3:1;                    /* Allow multiple receipt */
    UBYTE FILLER4:5;

    long OPT5;                         /* Cash-in-drawer limit (0 : no limit) */

    UBYTE OPT6_1:1;                    /* Cash declaration is compulsory before X/Z reports */
    UBYTE OPT6_2:1;                    /* MGR control to tender negative balance */
    UBYTE OPT6_3:1;                    /* MGR control to tender zero balance */
    UBYTE FILLER6:5;

    UBYTE OPT7_1:1;                    /* Reset transaction # on Z report */
    UBYTE OPT7_2:1;                    /* Reset grand total after Z f. report */
    UBYTE FILLER7:6;

    UBYTE INI_FEED;                    /* Initial Feeding */
    UBYTE END_FEED;                    /* Ending Feeding */

    int OPT9;                          /* Training password */

    UBYTE OPT10_1:1;                   /* Electronic journal */
    UBYTE OPT10_2:1;                   /* Send only negative entries to E.J. */
    UBYTE OPT10_3:1;                   /* Send reset reports to E.J. */
    UBYTE FILLER10:5;

    UBYTE OPT11_1:1;                   /* Prompt operator when E.J. is full */
    UBYTE OPT11_2:1;                   /* Stop operations when E.J. is full */
    UBYTE FILLER11:6;

    UBYTE OPT12_1:1;                   /* Open cash drawer when reports are run */
    UBYTE OPT12_3:1;                   /* Open drawer during train mode */
    UBYTE FILLER12:6;

    UBYTE OPT13_0:1;                   /* --------------------------- */
    UBYTE OPT13_2:1;                   /* Combine same item on kp */
    UBYTE OPT13_3:1;                   /* --------------------------- */
    UBYTE OPT13_4:1;                   /* Send To KP in VOID mode */
    UBYTE OPT13_5:1;                   /* Send To KP in TRAIN mode */
    UBYTE FILLER13:3;

    UBYTE OPT14_1:1;                   /* Disable Dept/PLU preset override */
    UBYTE FILLER14:7;

    UBYTE OPT15_1:1;                   /* Clerk entry method is 0 : Push */
                                       /*                       1 : Code */
    UBYTE FILLER15:7;

    UBYTE OPT16;                       /* Seconds to allow drawer open */

    UBYTE OPT17_1:2;                   /* Date format is 0 : MMDDYY */
                                       /*                1 : DDMMYY */
                                       /*                2 : YYMMDD */
    UBYTE FILLER17:6;

    UBYTE OPT18_1:2;                   /* Decimal place */
    UBYTE OPT18_2:1;                   /* Base currency is 0 : Home 981024*/
                                       /*                  1 : Euro */
    UBYTE FILLER18:5;

    UBYTE OPT19_1:1;                   /* Clerk is pop-up, stay-down if 0 */
    UBYTE FILLER19:7;

    UBYTE FILLER20;

    UBYTE OPT21_1:2;                   /* % and tax calculation  0 : round up at 0.50 */
                                       /*                        1 : round up */
                                       /*                        2 : round down */
    UBYTE FILLER21:6;

    UBYTE OPT22_1:2;                   /* Split pricing, triple & decimal multiplication */
                                       /*                   0 : round up at 0.50 */
                                       /*                   1 : round up */
                                       /*                   2 : round down */
    UBYTE FILLER22:6;

    int OPT23;                         /* ECR On Time */
} S_SYS_OPT;

typedef struct prt_para {
    UBYTE OPT1_1:1;                    /* Print media totals on clerk report */
    UBYTE OPT1_2:1;                    /* Print tax symbols on printer */
    UBYTE OPT1_3:1;                    /* Print MODE VOID and RETURN on f. report */
    UBYTE OPT1_4:1;                    /* Print AUDACTION on f. report */
    UBYTE OPT1_5:1;                    /* Print receipt when clerk sign on/off */
    UBYTE FILLER1:3;

    UBYTE OPT2_1:1;                    /* Skip zero totals on f. report */
    UBYTE OPT2_2:1;                    /* Print PLUs with zero totals on report */
    UBYTE OPT2_3:1;                    /* Print Dept. with zero totals on report */
    UBYTE OPT2_4:1;                    /* Skip zero totals on clerk report */
    UBYTE OPT2_5:1;                    /* Print clerk report after f. report */
    UBYTE OPT2_6:1;                    /* Print linked PLU in PLU report */
    UBYTE FILLER2:2;

    UBYTE OPT3_1:1;                    /* Print % of sales on Dept. report */
    UBYTE OPT3_2:1;                    /* Print % of sales on PLU report */
    UBYTE OPT3_3:1;                    /* Print consecutive number */
    UBYTE FILLER3:5;

    UBYTE OPT4_1:1;                    /* Print date on printer */
    UBYTE OPT4_2:1;                    /* Print time on printer */
    UBYTE OPT4_3:1;                    /* Print clerk name */
    UBYTE OPT4_4:1;                    /* Print KP order # on receipt */
    UBYTE FILLER4:4;

    UBYTE OPT5;                        /* Print machine no on printer */

    UBYTE OPT6;                        /* Home Currency symbol */

    UBYTE OPT7_1:1;                    /* Print grand total on X report */
    UBYTE OPT7_2:1;                    /* Print grand total on Z report */
    UBYTE FILLER7:6;

    UBYTE OPT8_1:1;                    /* Print gross total on X report */
    UBYTE OPT8_2:1;                    /* Print gross total on Z report */
    UBYTE OPT8_3:1;                    /* Print Z report issuing counter */
    UBYTE FILLER8:5;

    UBYTE OPT9_1:1;                    /* Print subtotal without tax */
    UBYTE OPT9_2:1;                    /* Print tax amount */
    UBYTE OPT9_3:1;                    /* Tax amount at final is combined */
                                       /*                    0 : itemized */
    UBYTE FILLER9:5;

    UBYTE OPT10_1:1;                   /* Print taxable total */
    UBYTE OPT10_2:1;                   /* Print tax percent rate */
    UBYTE OPT10_3:1;                   /* Print net sale amount (inclusive VAT) */
    UBYTE OPT10_4:1;                   /* Include VAT tax in tax amount */
    UBYTE FILLER10:4;

    UBYTE OPT11_1:1;                   /* Print sale item no */
    UBYTE OPT11_2:1;                   /* Subtotal is printed when the SUBTL key is pressed */
    UBYTE FILLER11:6;

    UBYTE OPT12_1:1;                   /* Print train mode title during train mode */
    UBYTE OPT12_2:1;                   /* Print Euro total  980605 */
    UBYTE OPT12_3:1;                   /* Print Euro tend   980605 */
    UBYTE OPT12_4:1;                   /* Print Euro change 980605 */
    UBYTE OPT12_5:1;                   /* Print Foreign Amount 981210 */
    UBYTE OPT12_6:1;                   /* Print Home Amount 981210 */
    UBYTE OPT12_7:1;                   /* Print TOTAL for both conversion 981210 */
    UBYTE OPT12_8:1;                   /* Print CHANGE for both conversion 981210 */

    UBYTE OPT13[MAX_CONV];             /* Currency Conversion symbol */
} S_PRT_OPT;

typedef struct norm_tag {              /* Void, Return, Cancel, PO, RA */
    UBYTE INACT:1;
    UBYTE XONLY:1;
    UBYTE FILLER:6;
} S_NORM_KEY;

typedef struct nosale_tag {
    UBYTE INACT:1;
    UBYTE AFT_NADD:1;                  /* Inhibit No Sale after Non-Add # */
    UBYTE COM_NADD:1;                  /* Compulsory non-add # at start of sale */
    UBYTE FILLER1:1;

    UBYTE NO_RCT:1;                    /* Do not issue a ticket on No Sale*/
    UBYTE FILLER2:3;
} S_NS_KEY;

typedef struct dptsft_tag {
    UBYTE INACT:1;
    UBYTE POP_UP:1;                    /* 1 : Pop-up, 0 : Stay down */
    UBYTE FILLER1:6;
} S_SFT_KEY;

typedef struct conv_tag {
    UBYTE DECI_NO;
} S_CONV_KEY;

typedef struct percent_tag {
    UBYTE INACT:1;
    UBYTE XONLY:1;
    UBYTE PRESET:1;
    UBYTE FILLER1:1;

    UBYTE SALE:1;
    UBYTE AMOUNT:1;
    UBYTE OVERRIDE:1;
    UBYTE FILLER2:1;

    UBYTE POSITIVE:1;
    UBYTE TAX_1:1;
    UBYTE TAX_2:1;
    UBYTE FILLER3:1;

    UBYTE TAX_3:1;
    UBYTE TAX_4:1;
    UBYTE FILLER4:2;
} S_PCNT_KEY;

typedef struct cash_tag {              /* Cash, Check */
    UBYTE COMP_AMT:1;
    UBYTE OVER_IN_X:1;
    UBYTE UNDER_T:1;
    UBYTE FILLER1:1;

    UBYTE OPEN_DRW:1;
    UBYTE FILLER2:3;

    UBYTE EXMT_TAX1:1;
    UBYTE EXMT_TAX2:1;
    UBYTE EXMT_TAX3:1;
    UBYTE FILLER3:1;

    UBYTE EXMT_TAX4:1;
    UBYTE FILLER4:3;
} S_CASH_KEY;

typedef struct misc_tag {              /* Misc. tend */
    UBYTE COMP_AMT:1;
    UBYTE OVER_IN_X:1;
    UBYTE UNDER_T:1;
    UBYTE FILLER1:1;

    UBYTE OPEN_DRW:1;
    UBYTE REQ_NONADD:1;
    UBYTE FILLER2:2;

    UBYTE EXMT_TAX1:1;
    UBYTE EXMT_TAX2:1;
    UBYTE EXMT_TAX3:1;
    UBYTE FILLER3:1;

    UBYTE EXMT_TAX4:1;
    UBYTE FILLER4:3;
} S_MISC_KEY;

typedef struct scale_tag {
    UBYTE INACT:1;
    UBYTE XONLY:1;
    UBYTE MANUAL:1;
    UBYTE FILLER1:1;

    UBYTE INHI_TARE:1;
    UBYTE TARE_IN_X:1;
    UBYTE COMP_TARE:1;
    UBYTE FILLER2:1;

    UBYTE SCALE_UNIT:1;                /* Weight symbol for manual entry, 1:Kg */
    UBYTE FILLER3:7;
} S_SCALE_KEY;

typedef struct func_key_tag {
    UBYTE DESC[12];
    long HALO;

    union {
        S_NORM_KEY  NORM_KEY;
        S_NS_KEY    NS_KEY;
        S_SFT_KEY   SFT_KEY;
        S_CONV_KEY  CONV_KEY;
        S_PCNT_KEY  PCNT_KEY;
        S_CASH_KEY  CASH_KEY;
        S_MISC_KEY  MISC_KEY;
        S_SCALE_KEY SCALE_KEY;
        UBYTE       STATUS[2];
        }KEY_ST;
} S_FUNCKEY;

typedef struct error_tbl {
        UBYTE offset;
        UBYTE msg_no;
} S_ERR_TBL;
typedef struct  pgm_ttable {
                long    taxfamt;          /* tax first tax amount */
                long    taxnamt;          /* non tax amount */
                long    nrtotal;          /* non repeat total amount */
                long    rtotal;           /* repeat total amount */
                char    nrbreak;          /* non repeat break count */
                char    rbreak;           /* repeat break count */
                int     ttable[MAX_TAXBRK];
                long    taxrate;          /* tax rate */
                char    taxstat;          /* tax kind   */
                UBYTE   desc[MAX_TAX_DESC];
}S_TAX_TBL;

typedef struct clerk_io {
        int     W_TIME;
        UBYTE   T_IDX;
        long    D_LOG[MAX_CIO];
        int     T_LOG[MAX_CIO];
} S_CLKIO;

typedef struct  rep_z_tag {
               long    cnt;
               long    total;         /* 2000000000 */
               } rep_z;
typedef struct  rep_z2_tag {
               long    cnt;
               long    totall;
               long    totalh;
               } rep_z2;
#if 0
typedef struct  kcode_rtn {
                unsigned int     r_kcode:15;
                unsigned int     rtn_b:1;
                }K_RTN;
#endif
typedef struct  reg_amt {
                char    r_index;
//                K_RTN   crt[MAX_KITEM];
                int     r_kcode[MAX_KITEM];
                long    r_amt[MAX_KITEM];
                }REG_MAP;

typedef struct sys_itm_tag {
    UBYTE line_no;
    UBYTE offset;
    UBYTE bit_mask;
    UBYTE type;
    long max_inp;
    UBYTE max_len;
    } S_SYS_ITEM;

typedef struct sys_pgm_tag {
    int str_no;
    const int *strb;
    UBYTE itm_no;
    const S_SYS_ITEM *item;
    } S_SYS_PGM;

typedef struct plu_pgm_tag {
    UBYTE desc[MAX_PLU_DESC];
    long price;
    UBYTE status[2];
    UBYTE link_dept;
    int link_plu;
    UBYTE auto_tare;
    } S_PLU_PGM;

typedef struct dept_pgm_tag {
    UBYTE desc[MAX_DEPT_DESC];
    long price;
    UBYTE status[2];
    char group;
    UBYTE auto_tare;
    } S_DEPT_PGM;

typedef struct clk_pgm_tag {
    UBYTE name[MAX_FUNC_DESC];
    long secret;
    } S_CLK_PGM;

typedef struct dtm_pgm_tag {
    int time;
    long date;
    } S_DTM_PGM;

#define	KP_RED	0x13
#define	KP_DBL	0x0E
#define	KP_LF	0x0A
#define	KP_NLF	0x0C
#define	KP_CUT	0x12
#define	KP_CAN	0x14
typedef struct kp_info_r {
//        UBYTE   DESC[MAX_PLU_DESC];

        UWORD   PCODE;
        int     QTY;
        long    AMT;

        UBYTE   RED:1;
        UBYTE   VD2:1;
        UBYTE   RTN:1;
        UBYTE   SKIP:1;
    	UBYTE	FILLER1:4;
} KP_INFO;

/* Kitchen printer pack REG format */
#define MAX_KP_CNT 80
typedef struct  kp_r    {
        KP_INFO pack[MAX_KP_CNT];
        UWORD   pack_no;
}KP_REG;

/* Kitchen printer pack format */
#define    MAX_KP_CLM   21
typedef	struct	kp_data {
	UBYTE	RED;
	UBYTE 	DBL;
	UBYTE	DATA[MAX_KP_CLM+1];
	UBYTE	LF;
} KP_PACK;

#define MAX_KP_END	32
typedef	struct	kpend_data {
	UBYTE	RED;
	UBYTE 	DBL;
	UBYTE	DATA[MAX_KP_END+1];
	UBYTE	LF;
} KPEND_PACK;
