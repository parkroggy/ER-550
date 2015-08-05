/***************************************************************/
/********        <er0io51.h> for ER-5100  europe         *******/
/********   i/o map and contants define  95.10.10        *******/
/***************************************************************/
#include      <er1def.h>

#define TP_BIT          1
#define TP_BYTE         2
#define TP_WORD         3
#define TP_LONG         4
#define TP_STRING       5
#define TP_REAL         6
#define TP_DLONG        7
#define TP_ELONG        8
#define TP_TIME         9
#define TP_DATE         10
#define TP_TARE         11

#define       ERR           { err_bit = 1; return; }
#define       VALIDC        0x51   /* absolute kcode */
#define       CASHKEY       0x24   /* absolute kcode */
/******************************************************/
/**                relocatable key                   **/
/******************************************************/
#define       DEPT1         0x01
#define       DEPT5         0x05
#define       DEPT6         0x06
#define       DEPT10        0x0a
#define       DEPT11        0x0b
#define       DEPT12        0x0c
#define       DEPT15        0x0f
#define       DEPT_START    0x01
#define       DEPT_END      0x0c
/************** 0x110 = 272(256+16) **********/
#define       CASH          0x110     /**0x30 = 16 = (0x10)**/
#define       SUBTOTAL      0x111     /**0x32**/
#define       CHECK         0x112     /**0x22**/
#define       MISCTND1      0x113     /**0x20* PKR0710 */
#define       MISCTND2      0x114     /**0x20* PKR0710 */
#define       MISCTND3      0x115     /**0x20* PKR0710 */
#define       MISCTND4      0x116     /**0x20* PKR0710 */
#define       RA            0x117     /**0x42**/
#define       PO            0x118     /**0x40**/
#define       CONV1         0x119     /**0x02**/
#define       CONV2         0x11a     /**0x12**/
#define       CONV3         0x11b     /**0x66**/
#define       CONV4         0x11c     /**0x63**/
#define       HELP          0x11d     /**0x65**//* yoo0820 */
#define       PLU           0x11e     /**0x53**/
#define       XTIME         0x11f     /**0x41**/
#define       NOSALE        0x120     /**0x46**/
#define       NONADD        0x121     /**0x46**/
#define       RETURN        0x122     /**0x71**/
#define       VOID          0x123     /**0x76**/
#define       ERR_CORR      0x124     /**0x76**/
#define       CANCEL        0x125     /**0x73**/
#define       TAX           0x126     /**0x61**/
#define       PER1          0x127     /**0x77**/
#define       PER2          0x128     /**0x67**/
#define       PER3          0x129     /**0x77**/
#define       PER4          0x12a     /**0x67**/
#define       DEPT_SFT      0x12b
#define       SCALE         0x12c
#define       TIMEIO        0x12d
#define       CLK1          0x12e     /**0x55**/
#define       MENU          0x12f     /**0x57**/
#define       PAGEUP        0x130     /**0x52**/
#define       PAGEDOWN      0x131     /**0x50**/
#define       YES_NO        0x132     /* PKR0629 */
#define       MISCMENU      0x133
#define       MAX_FKEY      0x33
#define       TARE          0x134
/******************************************************/
/**                   mode   key                     **/
/******************************************************/
#define       VMODE         0x01
#define       MMODE         0x02
#define       PMODE         0x04
#define       ZMODE         0x08
#define       XMODE         0x10
#define       RMODE         0x20
#define       OMODE         0x40

#define      VORXZM         0x7b
#define      VORXZ          0x79
#define      PMMODE         0x06
#define      RVMODE         0x21
#define      RVPMODE        0x25
#define      RVXMODE        0x31
#define      RVXPMODE       0x35
#define      RXMODE         0x30
#define      RPMMODE        0x26
#define      XZMODE         0x18
#define      VXMODE         0x11
#define      ZPMODE         0x0c
#define      ZPMMODE        0x0e
#define      XPMMODE        0x16
#define      OPMMODE        0x46
/******************************************************/
/**                   static key                     **/
/******************************************************/
#define       ONE           0x13
#define       TWO           0x23
#define       THREE         0x33
#define       FOUR          0x43
#define       FIVE          0x53
#define       SIX           0x05
#define       SEVEN         0x15
#define       EIGHT         0x35
#define       NINE          0x25
#define       ZERO          0x03
#define       DZERO         0x55
#define       DECIMAL       0x45

#define       RCASH         0x24
#define       RXTIME        0x42

#define       CLEAR         0x37
#define       RECEIPT       0x54

#define       R_HELP        0x57
#define       R_PGUP        0x00
#define       R_PGDN        0x32

#define       RFEED         0x54
#define       JFEED         0x64
#define       KLOGIC        0xff
/******************************************************/
#define       SOH          0x01      /*;start of head            */
#define       STX          0x02      /*;start of text            */
#define       EOB          0x17      /*;end of block             */
#define       ETX          0x03      /*;end of text              */
#define       EOT          0x04      /*;%end of transmission     */
#define       ENQ          0x05      /*;%enquiry                 */
#define       ACK          0x06      /*;%acknowledge             */
#define       DLE          0x10      /*;data link escape         */
#define       NACK         0x15      /*;negative acknowledge     */
/******************************************************/
/**          REAL KEY CODE                           **/
/******************************************************/
#define       REAL_KEY1    191
#define       REAL_KEY2    254
#define       REAL_KEY3    190
#define       REAL_KEY4    223
/************ Display Definition ***********/
#define     MAX_CLM     20    /* Must be changed with the contents in TABLE.C */
#define     HALF_CLM    10
#define	    MAX_SV_LINE 50
#define     MAX_LINE    8
#define     MAX_SCROLL  5
#define     MAX_MENU    63
#define     MAX_TITLE   27
#define     MAX_XMENU   36

#define     MENU_MANAGER    0
#define     MENU_PRINT      1
#define     MENU_DISPLAY    2
#define     MENU_RESET      3
#define     MENU_PGM        4
#define     MENU_PGMS       5
#define     MENU_CASHDE     6
#define     MENU_RONOF      7
#define     MENU_TRAIN      8
#define     MENU_PGM2       9
#define     MENU_PRINT2     10
#define     MENU_DISPLAY2   11
#define     MENU_REPTP      12  /* yoo 0923 */
#define     MENU_REPTD      13  /* yoo 0923 */
#define     MENU_MMODE      14
#define     MENU_MTEST      15
#define     MENU_EJ         16
#define     MENU_CNO        17


#define     MENU_RCONT      (MENU_CNO+2)
#define     MENU_REJ        (MENU_CNO+3)
#define     MENU_CLRTTL     (MENU_CNO+4)
#define     MENU_CLRGT      (MENU_CNO+5)
#define     MENU_PTDPRN     30
#define     MENU_PTDDSP     31
#define     MENU_CNO2       35

#define     MAX_HELP        55


typedef struct code_mem_tag {
    UBYTE menu_str[MAX_MENU][MAX_CLM+1];
    UBYTE title_str[MAX_TITLE][MAX_CLM+1];
    UBYTE xmenu_str[MAX_XMENU][MAX_CLM+1];
    UBYTE help_str[MAX_HELP*7][MAX_CLM+1];
    UBYTE logo_str[40][22];
    UBYTE logo_strs[5][27];
    UBYTE nur_str[25][15];
    UBYTE pttl_str[20][21];
    UBYTE sttl_str[10][25];
    UBYTE key_desc[MAX_FUNCKEY][12];
    UBYTE ERRMSG[MAX_ERR_STR][19];
    UBYTE finlogo[USE_FIN][12];
    UBYTE strb[265][21];
    UBYTE clklogo[34][12];
    UBYTE LOGMSG[8][15];
} S_CODE_MEM;

typedef union bitf_tag {
    struct bit_tag {
        UBYTE bit0:1;
        UBYTE bit1:1;
        UBYTE bit2:1;
        UBYTE bit3:1;
        UBYTE bit4:1;
        UBYTE bit5:1;
        UBYTE bit6:1;
        UBYTE bit7:1;
        } bit_s;
    UBYTE byte_s;
} bit_v;
/******************************************************/
/**          REPORT CODE                             **/
/******************************************************/
#define       REPT_FIN      1
#define       REPT_TIME     2
#define       REPT_PLU      3
#define       REPT_CLK      4
#define       REPT_CAIND    5
#define       REPT_CKIND    6
#define       REPT_GROUP    7
#define       REPT_ELEJ     8

/******************************************************/
/**          bit allocate for system control         **/
/******************************************************/
#ifndef BCDBG
/*         key_id        0x20    */
bit           knur_bit      = 0x00;
bit           kdec_bit      = 0x01;
bit           kclr_bit      = 0x02;
bit           ksub_bit      = 0x03;
bit           clear_bit     = 0x04;
bit           none05        = 0x05;
bit           none06        = 0x06;
bit           none07        = 0x07;

/*         twostep_id    0x21    */
bit           rtn_bit       = 0x08;
bit           vd1_bit       = 0x09;
bit           vd2_bit       = 0x0a;
bit           pluon_bit     = 0x0b;
bit           mul_bit       = 0x0c;
bit           spl_bit       = 0x0d;
bit           kopen_bit     = 0x0e;
bit           taxsft_bit    = 0x0f;

/*         dptstp_id     0x22    */
bit           dptax1_bit    = 0x10;
bit           dptax2_bit    = 0x11;
bit           dptax3_bit    = 0x12;
bit           dptax4_bit    = 0x13;
bit           negat_bit     = 0x14;
bit           singl_bit     = 0x15;
bit           reqscl_bit    = 0x16;
bit           none17        = 0x17;

/*         dptstp1_id    0x23    */
bit           preset_bit    = 0x18;
bit           inact_bit     = 0x19;
bit           autoscl_bit   = 0x1a;
bit           kp_bit        = 0x1b;
bit           invent_bit    = 0x1c;
bit           gas_bit       = 0x1d;
bit           nadd_bit      = 0x1e;
bit           kpred_bit     = 0x1f;

/*         rstep_id      0x24    */
bit           tax1_bit      = 0x20;
bit           tax2_bit      = 0x21;
bit           tax3_bit      = 0x22;
bit           tax4_bit      = 0x23;
bit           vatbk_bit     = 0x24;
bit           sall_bit      = 0x25;    /* Not used */
bit           stock_bit     = 0x26;
bit           grand_bit     = 0x27;

/*         rstep1_id     0x25    */
bit           emtax1_bit    = 0x28;
bit           emtax2_bit    = 0x29;
bit           emtax3_bit    = 0x2a;
bit           emtax4_bit    = 0x2b;
bit           cupn_bit      = 0x2c;
bit           pluact_bit    = 0x2d;
bit           nodtax_bit    = 0x2e;
bit           vmark_flg     = 0x2f;

/*         recover_id    0x26    */
bit           conv_bit      = 0x30;              /* clear at the tendering */
bit           tnd_bit       = 0x31;
bit           nona_bit      = 0x32;
bit           sign_bit      = 0x33;
bit           cng_bit       = 0x34;
bit           audct_bit     = 0x35;
bit           pksub_bit     = 0x36;
bit           yyyyy_bit     = 0x37;              /* 95.10.12 */

/*         perstp_id     0x27    */
bit           pitem_bit     = 0x38;              /* 1 sale      */
bit           ppercnt_bit   = 0x39;              /* 1 after cal */
bit           pinact_bit    = 0x3a;              /* 1 after cal */
bit           none_3b       = 0x3b;              /* Not used    */
bit           pdiscnt_bit   = 0x3c;              /* 1 amount    */
bit           popen_bit     = 0x3d;              /* 1 surcharge */
bit           pdirect_bit   = 0x3e;              /* direct      */
bit           f1m_bit       = 0x3f;              /* 1M fiscal eprom  */

/*         repot_id      0x28    */
bit           rep1_bit      = 0x40;
bit           rep2_bit      = 0x41;
bit           rep3_bit      = 0x42;
bit           rep4_bit      = 0x43;
bit           rep5_bit      = 0x44;
bit           rep6_bit      = 0x45;
bit           rep7_bit      = 0x46;
bit           rep8_bit      = 0x47;

/*         progm_id      0x29    */
bit           pro1_bit      = 0x48;
bit           pro2_bit      = 0x49;
bit           pro3_bit      = 0x4a;
bit           pro4_bit      = 0x4b;
bit           pro5_bit      = 0x4c;
bit           pro6_bit      = 0x4d;
bit           pro7_bit      = 0x4e;
bit           pro8_bit      = 0x4f;

/*         rec_id        0x2a    */
bit           rec1_bit      = 0x50;
bit           rec2_bit      = 0x51;
bit           rec3_bit      = 0x52;
bit           rec4_bit      = 0x53;
bit           rec5_bit      = 0x54;
bit           rec6_bit      = 0x55;
bit           rec7_bit      = 0x56;
bit           rec8_bit      = 0x57;

/*            etc_id     0x2b    */
bit           lgol_bit      = 0x58;
bit           lsharp_bit    = 0x59;
bit           lstar_bit     = 0x5a;
bit           lblk_bit      = 0x5b;
bit           notdot_bit    = 0x5c;
bit           xcnt_bit      = 0x5d;
bit           xxcnt_bit     = 0x5e;
bit           gnd_bit       = 0x5f;

/*         disp_id       0x2c    */
bit           void_bit      = 0x60;              /* display control bit */
bit           taxs_bit      = 0x61;
bit           pfkey_bit     = 0x62;
bit           ronoff_bit    = 0x63;
bit           err_bit       = 0x64;
bit           drwr_bit      = 0x65;
bit           iosign_bit    = 0x66;
bit           vnfd_bit      = 0x67;

/*         print_id      0x2d    */
bit           rfkey_bit     = 0x68;              /* printer control bit */
bit           jfkey_bit     = 0x69;
bit           rhome_bit     = 0x6a;
bit           jhome_bit     = 0x6b;
bit           lastl_bit     = 0x6c;
bit           ffeed_bit     = 0x6d;
bit           jurn_bit      = 0x6e;
bit           rept_bit      = 0x6f;

/*         icon_id       0x2e    */
bit           pover_bit     = 0x70;
bit           rlfeed_bit    = 0x71;
bit           dumytm_bit    = 0x72;
bit           sfeed_bit     = 0x73;
bit           nfeed_bit     = 0x74;
bit           rpoff_bit     = 0x75;
bit           ffedoff_bit   = 0x76;
bit           kin_bit       = 0x77;              /* buffering only tend line */

/*         dddd4         0x2f    */
bit           okbuf_bit     = 0x78;
bit           onlytd_bit    = 0x79;
bit           notbuf_bit    = 0x7a;
bit           bmmm_bit      = 0x7b;
bit           double_bit    = 0x7c;              /* alarm sounr start bit */
bit           allramclr_bit = 0x7d;
bit           tempramclr_bit= 0x7e;
bit           stamp_bit     = 0x7f;             /* stamp_bit */
#else                                  /* BCDBG */
#define key_id               (bit_v20.byte_s)
#define knur_bit             (bit_v20.bit_s.bit0)
#define kdec_bit             (bit_v20.bit_s.bit1)
#define kclr_bit             (bit_v20.bit_s.bit2)
#define ksub_bit             (bit_v20.bit_s.bit3)
#define clear_bit            (bit_v20.bit_s.bit4)
#define none05               (bit_v20.bit_s.bit5)
#define none06               (bit_v20.bit_s.bit6)
#define none07               (bit_v20.bit_s.bit7)

#define twostep_id           (bit_v21.byte_s)
#define rtn_bit              (bit_v21.bit_s.bit0)
#define vd1_bit              (bit_v21.bit_s.bit1)
#define vd2_bit              (bit_v21.bit_s.bit2)
#define pluon_bit            (bit_v21.bit_s.bit3)
#define mul_bit              (bit_v21.bit_s.bit4)
#define spl_bit              (bit_v21.bit_s.bit5)
#define kopen_bit            (bit_v21.bit_s.bit6)
#define taxsft_bit           (bit_v21.bit_s.bit7)

#define dptstp_id            (bit_v22.byte_s)
#define dptax1_bit           (bit_v22.bit_s.bit0)
#define dptax2_bit           (bit_v22.bit_s.bit1)
#define dptax3_bit           (bit_v22.bit_s.bit2)
#define dptax4_bit           (bit_v22.bit_s.bit3)
#define negat_bit            (bit_v22.bit_s.bit4)
#define singl_bit            (bit_v22.bit_s.bit5)
#define reqscl_bit           (bit_v22.bit_s.bit6)
#define none17               (bit_v22.bit_s.bit7)

#define dptstp1_id           (bit_v23.byte_s)
#define preset_bit           (bit_v23.bit_s.bit0)
#define inact_bit            (bit_v23.bit_s.bit1)
#define autoscl_bit          (bit_v23.bit_s.bit2)
#define kp_bit               (bit_v23.bit_s.bit3)
#define invent_bit           (bit_v23.bit_s.bit4)
#define gas_bit              (bit_v23.bit_s.bit5)
#define nadd_bit             (bit_v23.bit_s.bit6)
#define kpred_bit            (bit_v23.bit_s.bit7)

#define rstep_id             (bit_v24.byte_s)
#define tax1_bit             (bit_v24.bit_s.bit0)
#define tax2_bit             (bit_v24.bit_s.bit1)
#define tax3_bit             (bit_v24.bit_s.bit2)
#define tax4_bit             (bit_v24.bit_s.bit3)
#define vatbk_bit            (bit_v24.bit_s.bit4)
#define sall_bit             (bit_v24.bit_s.bit5)
#define stock_bit            (bit_v24.bit_s.bit6)
#define grand_bit            (bit_v24.bit_s.bit7)

#define rstep1_id            (bit_v25.byte_s)
#define emtax1_bit           (bit_v25.bit_s.bit0)
#define emtax2_bit           (bit_v25.bit_s.bit1)
#define emtax3_bit           (bit_v25.bit_s.bit2)
#define emtax4_bit           (bit_v25.bit_s.bit3)
#define cupn_bit             (bit_v25.bit_s.bit4)
#define pluact_bit           (bit_v25.bit_s.bit5)
#define nodtax_bit           (bit_v25.bit_s.bit6)
#define vmark_flg            (bit_v25.bit_s.bit7)

#define recover_id           (bit_v26.byte_s)
#define conv_bit             (bit_v26.bit_s.bit0)
#define tnd_bit              (bit_v26.bit_s.bit1)
#define nona_bit             (bit_v26.bit_s.bit2)
#define sign_bit             (bit_v26.bit_s.bit3)
#define cng_bit              (bit_v26.bit_s.bit4)
#define audct_bit            (bit_v26.bit_s.bit5)
#define pksub_bit            (bit_v26.bit_s.bit6)
#define yyyyy_bit            (bit_v26.bit_s.bit7)

#define perstp_id            (bit_v27.byte_s)
#define pitem_bit            (bit_v27.bit_s.bit0)
#define ppercnt_bit          (bit_v27.bit_s.bit1)
#define pinact_bit           (bit_v27.bit_s.bit2)
#define none_3b              (bit_v27.bit_s.bit3)
#define pdiscnt_bit          (bit_v27.bit_s.bit4)
#define popen_bit            (bit_v27.bit_s.bit5)
#define pdirect_bit          (bit_v27.bit_s.bit6)
#define f1m_bit              (bit_v27.bit_s.bit7)

#define repot_id             (bit_v28.byte_s)
#define rep1_bit             (bit_v28.bit_s.bit0)
#define rep2_bit             (bit_v28.bit_s.bit1)
#define rep3_bit             (bit_v28.bit_s.bit2)
#define rep4_bit             (bit_v28.bit_s.bit3)
#define rep5_bit             (bit_v28.bit_s.bit4)
#define rep6_bit             (bit_v28.bit_s.bit5)
#define rep7_bit             (bit_v28.bit_s.bit6)
#define rep8_bit             (bit_v28.bit_s.bit7)

#define progm_id             (bit_v29.byte_s)
#define pro1_bit             (bit_v29.bit_s.bit0)
#define pro2_bit             (bit_v29.bit_s.bit1)
#define pro3_bit             (bit_v29.bit_s.bit2)
#define pro4_bit             (bit_v29.bit_s.bit3)
#define pro5_bit             (bit_v29.bit_s.bit4)
#define pro6_bit             (bit_v29.bit_s.bit5)
#define pro7_bit             (bit_v29.bit_s.bit6)
#define pro8_bit             (bit_v29.bit_s.bit7)

#define rec_id               (bit_v2a.byte_s)
#define rec1_bit             (bit_v2a.bit_s.bit0)
#define rec2_bit             (bit_v2a.bit_s.bit1)
#define rec3_bit             (bit_v2a.bit_s.bit2)
#define rec4_bit             (bit_v2a.bit_s.bit3)
#define rec5_bit             (bit_v2a.bit_s.bit4)
#define rec6_bit             (bit_v2a.bit_s.bit5)
#define rec7_bit             (bit_v2a.bit_s.bit6)
#define rec8_bit             (bit_v2a.bit_s.bit7)

#define    etc_id            (bit_v2b.byte_s)
#define lgol_bit             (bit_v2b.bit_s.bit0)
#define lsharp_bit           (bit_v2b.bit_s.bit1)
#define lstar_bit            (bit_v2b.bit_s.bit2)
#define lblk_bit             (bit_v2b.bit_s.bit3)
#define notdot_bit           (bit_v2b.bit_s.bit4)
#define xcnt_bit             (bit_v2b.bit_s.bit5)
#define xxcnt_bit            (bit_v2b.bit_s.bit6)
#define gnd_bit              (bit_v2b.bit_s.bit7)

#define disp_id              (bit_v2c.byte_s)
#define void_bit             (bit_v2c.bit_s.bit0)
#define taxs_bit             (bit_v2c.bit_s.bit1)
#define pfkey_bit            (bit_v2c.bit_s.bit2)
#define ronoff_bit           (bit_v2c.bit_s.bit3)
#define err_bit              (bit_v2c.bit_s.bit4)
#define drwr_bit             (bit_v2c.bit_s.bit5)
#define iosign_bit           (bit_v2c.bit_s.bit6)
#define vnfd_bit             (bit_v2c.bit_s.bit7)

#define print_id             (bit_v2d.byte_s)
#define rfkey_bit            (bit_v2d.bit_s.bit0)
#define jfkey_bit            (bit_v2d.bit_s.bit1)
#define rhome_bit            (bit_v2d.bit_s.bit2)
#define jhome_bit            (bit_v2d.bit_s.bit3)
#define lastl_bit            (bit_v2d.bit_s.bit4)
#define ffeed_bit            (bit_v2d.bit_s.bit5)
#define jurn_bit             (bit_v2d.bit_s.bit6)
#define rept_bit             (bit_v2d.bit_s.bit7)

#define icon_id              (bit_v2e.byte_s)
#define pover_bit            (bit_v2e.bit_s.bit0)
#define rlfeed_bit           (bit_v2e.bit_s.bit1)
#define dumytm_bit           (bit_v2e.bit_s.bit2)
#define sfeed_bit            (bit_v2e.bit_s.bit3)
#define nfeed_bit            (bit_v2e.bit_s.bit4)
#define rpoff_bit            (bit_v2e.bit_s.bit5)
#define ffedoff_bit          (bit_v2e.bit_s.bit6)
#define kin_bit              (bit_v2e.bit_s.bit7)

#define dddd4                (bit_v2f.byte_s)
#define okbuf_bit            (bit_v2f.bit_s.bit0)
#define onlytd_bit           (bit_v2f.bit_s.bit1)
#define notbuf_bit           (bit_v2f.bit_s.bit2)
#define bmmm_bit             (bit_v2f.bit_s.bit3)
#define double_bit           (bit_v2f.bit_s.bit4)
#define allramclr_bit        (bit_v2f.bit_s.bit5)
#define tempramclr_bit       (bit_v2f.bit_s.bit6)
#define stamp_bit            (bit_v2f.bit_s.bit7)
#endif                                 /* BCDBG */

/*========IE=========*/

/*bit   EA_BIT    = 0xAF;*/
/*bit   ET2_BIT   = 0xAD;*/
/*bit   ES_BIT    = 0xAC;*/
/*bit   ET1_BIT   = 0xAB;*/
/*bit   EX1_BIT   = 0xAA;*/
/*bit   ET0_BIT   = 0xA9;*/
/*bit   EX0_BIT   = 0xA8;*/
/*===================*/

/******************************************************/
/**     internal data ram  for system contro         **/
/**     020h - 0ffh                                  **/
/******************************************************/
#ifndef BCDBG
#pragma   memory = data
extern    unsigned     char   key_id      ;   /*  020h  */
extern    unsigned     char   twostep_id  ;   /*  021h  */
extern    unsigned     char   dptstp_id   ;   /*  022h  */
extern    unsigned     char   dptstp1_id  ;   /*  023h  */
extern    unsigned     char   rstep_id    ;   /*  024h  */
extern    unsigned     char   rstep1_id   ;   /*  025h  */
extern    unsigned     char   recover_id  ;   /*  026h  */
extern    unsigned     char   perstp_id   ;   /*  027h  */
extern    unsigned     char   repot_id    ;   /*  028h  */
extern    unsigned     char   progm_id    ;   /*  029h  */
extern    unsigned     char   rec_id      ;   /*  02ah  */
extern    unsigned     char   etc_id      ;   /*  02bh  */
extern    unsigned     char   disp_id     ;   /*  02ch  */
extern    unsigned     char   print_id    ;   /*  02dh  */
extern    unsigned     char   icon_id     ;   /*  02eh  */
extern    unsigned     char   dddd4       ;   /*  02fh  */
#else                                  /* BCDBG */
extern bit_v bit_v20, bit_v21, bit_v22, bit_v23, bit_v24, bit_v25, bit_v26, bit_v27,
      bit_v28, bit_v29, bit_v2a, bit_v2b, bit_v2c, bit_v2d, bit_v2e, bit_v2f;
#endif                                 /* BCDBG */
/*------------------------------------------------------*/
extern    unsigned     char   dph_add     ;   /*  030h  */
extern    unsigned     char   dpl_add     ;   /*  031h  */
extern    unsigned     char   dph0_add    ;   /*  032h  */
extern    unsigned     char   dpl0_add    ;   /*  033h  */
extern    unsigned     char   dph1_add    ;   /*  034h  */
extern    unsigned     char   dpl1_add    ;   /*  035h  */
extern    unsigned     char   dph2_add    ;   /*  036h  */
extern    unsigned     char   dpl2_add    ;   /*  037h  */
extern    unsigned     char   compd_flg   ;   /*  038h  */
extern    unsigned     char   timd_cnt    ;   /*  03ah  */
extern    unsigned     char   dig_cnt     ;   /*  03bh  */
extern    unsigned     char   buzz_cnt    ;   /*  03ch  */
extern    unsigned     char   jam_cnt     ;   /*  03dh  */
extern    unsigned     char   jam_flg     ;   /*  03eh  */
extern    unsigned     char   scnl_cnt    ;   /*  03fh  */
extern    unsigned     char   decimal     ;   /*  040h  */
extern    unsigned     char   prntask     ;   /*  041h  */
extern    unsigned     char   doubf_flg   ;   /*  042h  */
extern    unsigned     char   tmp_cnt     ;   /*  043h  */
extern    unsigned     char   tmp1_cnt    ;   /*  044h  */
extern    unsigned     char   jtmp_cnt    ;   /*  045h  */
extern    unsigned     char   jtmp1_cnt   ;   /*  046h  */
extern    unsigned     char   font_data   ;   /*  047h  */
extern    unsigned     char   fonte_data  ;   /*  048h  */
extern    unsigned     char   pfail_flg   ;   /*  04ah  */
extern    unsigned     char   prn_stat    ;   /*  04bh  */
extern    unsigned     char   prt_chatt   ;   /*  04ch  */

extern    unsigned     char   prt_rstm    ;   /*  04eh  */
extern    unsigned     char   xoff_flg    ;   /*  04fh  */
extern    unsigned     char   pend_flg    ;   /*  052h  */
extern    unsigned     char   prgt_flag   ;   /*  053h  */
extern    unsigned     char   pskp_flag   ;   /*  054h  */
extern    unsigned     char   io_cnt      ;   /*  055h  */
extern    unsigned     char   tend_flg    ;   /*  056h  */
extern    unsigned     char   rend_flg    ;   /*  057h  */
extern    unsigned     char   siotm_cnt0  ;   /*  059h  */
extern    unsigned     char   siotm_cnt1  ;   /*  059h  */
extern    unsigned     char   s_in_flg    ;   /*  059h  */
extern    unsigned     char   s_out_flg   ;   /*  05ah  */
extern    unsigned     char   dsave_flg   ;   /*  05ch  */
extern    unsigned     char   stx_flg     ;   /*  05dh  */
extern    unsigned     char   etx_flg     ;   /*  05eh  */
extern    unsigned     char   dle_flg     ;   /*  05fh  */
extern    unsigned     char   ack_flg     ;   /*  060h  */
extern    unsigned     char   nack_flg    ;   /*  061h  */
extern    unsigned     char   crc1_data   ;   /*  062h  */
extern    unsigned     char   crc2_data   ;   /*  063h  */
extern    unsigned     char   trx_buf_cnt ;   /*  064h  */
extern    unsigned     char   data_s_end  ;   /*  065h  */
extern    unsigned     char   comm_status ;   /*  066h  */
extern    unsigned     char   comm_pnt    ;   /*  067h  */
extern    unsigned     char   comm_kind   ;   /*  068h  */
extern    unsigned     char   comm_err    ;   /*  069h  */
extern    unsigned     char   temp1_flg   ;   /*  06ah  */
extern    unsigned     char   selkey_flg  ;   /*  06ah  */
extern    unsigned     char   rom_flg     ;   /*  06bh  */
/* test */
extern    unsigned     char   fs_data     ;   /*  06eh  */
extern    unsigned     char   blk_time    ;   /*  06fh  */
extern    unsigned     char   low_add     ;   /*  070h  */
extern    unsigned     char   high_add    ;   /*  071h  */
extern    unsigned     char   brom_flg    ;   /*  072h  */
extern    unsigned     char   disc_flg    ;   /*  073h  */
extern    unsigned     char   timeol      ;   /*  074h  */
extern    unsigned     char   timeoh      ;   /*  075h  */
extern    unsigned     char   lcd_reflg   ;   /*  076h  */
extern    unsigned     char   almstart_flg;   /*  072h  */

#ifndef BCDBG
#pragma   memory = default
#endif                                 /* BCDBG */
/*------------------------------------------------------*/
/*               STACK   5xh - .......... 0ffh          */
/*------------------------------------------------------*/
