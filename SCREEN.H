#define MAX_SYS_OPT     13
#define MAX_PRT_OPT     12             /* 980605  981210*/
#define MAX_TAX0_OPT    1
#define MAX_TAX1_OPT    1
#define MAX_TAX2_OPT    1
#define MAX_TAX3_OPT    1
#define MAX_CNO_OPT     1
#define MAX_DNO_OPT     1
#define MAX_PNO_OPT     1
#define MAX_PLU_OPT     3
#define MAX_DEPT_OPT    3
#define MAX_DTM_OPT     1
#define MAX_CONV_OPT    1
#define MAX_PCNT_OPT    2
#define MAX_CLK_OPT     1
#define MAX_MSG_OPT     2
#define MAX_VOID_OPT    2
#define MAX_CAN_OPT     1
#define MAX_NS_OPT      2
#define MAX_SFT_OPT     1
#define MAX_CASH_OPT    2
#define MAX_MISC_OPT    2
#define MAX_SCALE_OPT   2
#define MAX_TARE_OPT    1
#define MAX_CIO_OPT     3
#define MAX_INV_OPT     1
#define MAX_GRP_OPT     2
#define MAX_OTH_ALPH    2

/*************************************************************************/

const int sys_ss01[] = {
    1, 2, 3, 4, 5, 6, 7};
const int sys_ss02[] = {
    8, 9, 10, 11, 12, 13, 14};
const int sys_ss03[] = {
    26, 15, 16, 17, 18, 214, 215};
const int sys_ss04[] = {
    21, 22, 23, 24, 23, 25, 216};
const int sys_ss05[] = {
#ifdef PCCOMM
    27, 28, 29, 30, 31, 32, 247};
#else
    27, 28, 29, 30, 31, 32};
#endif
const int sys_ss07[] = {
    33, 34, 35, 36, 37, 38, 39};
const int sys_ss08[] = {
    40, 39, 41, 42, 43, 44, 45};
const int sys_ss09[] = {
    46, 47, 48, 49, 19, 20, 0};
const int sys_ss12[] = {
    50, 51, 0, 52, 53, 54, 55};
const int sys_ss13[] = {
    227, 228, 229, 230, 231, 235, 236};
const int sys_ss14[] = {
    237, 238, 240, 238, 241, 238};
const int sys_ss15[] = {
    242, 243, 244, 243, 251, 252};
const int sys_ss16[] = {
    258, 259};  /* 981024 */

const S_SYS_ITEM sys_ipg01[] = {
    {1, 1, 0x01, TP_BIT, 0l, 0},
    {3, 20, 0x00, TP_BYTE, 1l, 1},
    {7, 0, 0x01, TP_BYTE, 20l, 2}};
const S_SYS_ITEM sys_ipg02[] = {
    {1, 24, 0x01, TP_BIT, 0l, 0},
    {4, 1, 0x02, TP_BIT, 0l, 0},
    {5, 1, 0x04, TP_BIT, 0l, 0},
    {7, 21, 0x01, TP_BYTE, 99l, 2}};
const S_SYS_ITEM sys_ipg03[] = {
    {1, 4, 0x01, TP_BIT, 0l, 0},
    {3, 4, 0x02, TP_BIT, 0l, 0},
    {5, 4, 0x04, TP_BIT, 0l, 0},
    {7, 2, 0x01, TP_BIT, 0l, 0}};
const S_SYS_ITEM sys_ipg04[] = {
    {2, 9, 0x01, TP_BIT, 0l, 0},
    {4, 9, 0x02, TP_BIT, 0l, 0},
    {6, 9, 0x04, TP_BIT, 0l, 0},
    {7, 2, 0x02, TP_BIT, 0l, 0}};
const S_SYS_ITEM sys_ipg05[] = {
    {2, 10, 0x01, TP_BIT, 0l, 0},
    {4, 10, 0x02, TP_BIT, 0l, 0},
#ifdef PCCOMM
    {6, 13, 0x13, TP_WORD, 9999l, 4},
    {7, 28, 0x13, TP_WORD, 9999l, 4}};
#else
    {6, 13, 0x13, TP_WORD, 9999l, 4}};
#endif
const S_SYS_ITEM sys_ipg07[] = {
    {1, 15, 0x01, TP_BIT, 0l, 0},
    {3, 15, 0x02, TP_BIT, 0l, 0},
    {5, 15, 0x04, TP_BIT, 0l, 0},
    {7, 16, 0x01, TP_BIT, 0l, 0}};
const S_SYS_ITEM sys_ipg08[] = {
    {2, 16, 0x02, TP_BIT, 0l, 0},
    {4, 17, 0x01, TP_BIT, 0l, 0},
    {5, 22, 0x00, TP_BYTE, 2l, 1},
    {7, 23, 0x00, TP_BYTE, 3l, 1}};
const S_SYS_ITEM sys_ipg09[] = {
    {2, 17, 0x02, TP_BIT, 0l, 0},
    {4, 19, 0x01, TP_BIT, 0l, 0},
    {7, 5, 0x02, TP_REAL, 999999999l, 9}};
const S_SYS_ITEM sys_ipg12[] = {
    {1, 26, 0x00, TP_BYTE, 2l, 1},
    {2, 27, 0x00, TP_BYTE, 2l, 1}};
const S_SYS_ITEM sys_ipg13[] = {
    {3, 1, 0x08, TP_BIT, 0l, 0},
    {5, 1, 0x10, TP_BIT, 0l, 0},
#ifdef PLU70
    {6, 3, 0x00, TP_BYTE, 2l, 1}};
#else
    {6, 3, 0x00, TP_BYTE, 3l, 1}};
#endif
const S_SYS_ITEM sys_ipg14[] = {
    {2, 18, 0x02, TP_BIT, 0l, 0},
    {4, 11, 0x00, TP_BYTE, 99l, 2},
    {6, 12, 0x00, TP_BYTE, 99l, 2}};
const S_SYS_ITEM sys_ipg15[] = {
    {2, 18, 0x08, TP_BIT, 0l, 0},
    {4, 18, 0x10, TP_BIT, 0l, 0},
    {6, 2, 0x04, TP_BIT, 0l, 0}};
const S_SYS_ITEM sys_ipg16[] = {
    {2, 23, 0x04, TP_BIT, 0l, 0}};     /* 981024 */

const S_SYS_PGM sys_pgm[MAX_SYS_OPT] = {
    {(sizeof(sys_ss01))/2, sys_ss01,
            (UBYTE)(sizeof(sys_ipg01)/sizeof(S_SYS_ITEM)), sys_ipg01},
    {(sizeof(sys_ss02))/2, sys_ss02,
            (UBYTE)(sizeof(sys_ipg02)/sizeof(S_SYS_ITEM)), sys_ipg02},
    {(sizeof(sys_ss03))/2, sys_ss03,
            (UBYTE)(sizeof(sys_ipg03)/sizeof(S_SYS_ITEM)), sys_ipg03},
    {(sizeof(sys_ss04))/2, sys_ss04,
            (UBYTE)(sizeof(sys_ipg04)/sizeof(S_SYS_ITEM)), sys_ipg04},
    {(sizeof(sys_ss05))/2, sys_ss05,
            (UBYTE)(sizeof(sys_ipg05)/sizeof(S_SYS_ITEM)), sys_ipg05},
    {(sizeof(sys_ss07))/2, sys_ss07,
            (UBYTE)(sizeof(sys_ipg07)/sizeof(S_SYS_ITEM)), sys_ipg07},
    {(sizeof(sys_ss08))/2, sys_ss08,
            (UBYTE)(sizeof(sys_ipg08)/sizeof(S_SYS_ITEM)), sys_ipg08},
    {(sizeof(sys_ss09))/2, sys_ss09,
            (UBYTE)(sizeof(sys_ipg09)/sizeof(S_SYS_ITEM)), sys_ipg09},
    {(sizeof(sys_ss12))/2, sys_ss12,
            (UBYTE)(sizeof(sys_ipg12)/sizeof(S_SYS_ITEM)), sys_ipg12},
    {(sizeof(sys_ss13))/2, sys_ss13,
            (UBYTE)(sizeof(sys_ipg13)/sizeof(S_SYS_ITEM)), sys_ipg13},
    {(sizeof(sys_ss14))/2, sys_ss14,
            (UBYTE)(sizeof(sys_ipg14)/sizeof(S_SYS_ITEM)), sys_ipg14},
    {(sizeof(sys_ss15))/2, sys_ss15,
            (UBYTE)(sizeof(sys_ipg15)/sizeof(S_SYS_ITEM)), sys_ipg15},
    {(sizeof(sys_ss16))/2, sys_ss16,
            (UBYTE)(sizeof(sys_ipg16)/sizeof(S_SYS_ITEM)), sys_ipg16}};

/*************************************************************************/

const int prt_ss01[] = {
    56, 57, 58, 59, 60, 61, 62};
const int prt_ss02[] = {
    63, 64, 63, 65, 66, 67};
const int prt_ss0b[] = {
    68, 69, 70, 69, 71, 72};
const int prt_ss03[] = {
    74, 75, 76, 75, 77, 223, 224};
const int prt_ss04[] = {
    73, 78, 79, 80, 81, 82, 83};
const int prt_ss05[] = {
    248, 249, 84, 85, 84, 86};
const int prt_ss06[] = {
    87, 85, 87, 86, 88};
const int prt_ss07[] = {
    89, 90, 91, 92, 93, 94};
const int prt_ss08[] = {
    95, 225, 226, 96, 97, 99, 100};
const int prt_ss09[] = {
    245, 246, 101, 102, 103, 104, 105};
const int prt_ss10[] = {
    255, 256, 257};          /* 980605 */
const int prt_ss11[] = {
    260, 261, 262, 263, 264};          /* 981210 */

const S_SYS_ITEM prt_ipg01[] = {
    {2, 0, 0x01, TP_BIT, 0l, 0},
    {3, 0, 0x02, TP_BIT, 0l, 0},
    {5, 0, 0x04, TP_BIT, 0l, 0},
    {7, 0, 0x08, TP_BIT, 0l, 0}};
const S_SYS_ITEM prt_ipg02[] = {
    {2, 1, 0x01, TP_BIT, 0l, 0},
    {4, 1, 0x08, TP_BIT, 0l, 0},
    {5, 1, 0x10, TP_BIT, 0l, 0}};
const S_SYS_ITEM prt_ipg0b[] = {
    {2, 1, 0x02, TP_BIT, 0l, 0},
    {4, 1, 0x04, TP_BIT, 0l, 0},
    {6, 10, 0x02, TP_BIT, 0l, 0}};
const S_SYS_ITEM prt_ipg03[] = {
    {1, 10, 0x01, TP_BIT, 0l, 0},
    {3, 2, 0x01, TP_BIT, 0l, 0},
    {5, 2, 0x02, TP_BIT, 0l, 0},
    {7, 1, 0x20, TP_BIT, 0l, 0}};
const S_SYS_ITEM prt_ipg04[] = {
    {1, 2, 0x04, TP_BIT, 0l, 0},
    {2, 3, 0x01, TP_BIT, 0l, 0},
    {3, 3, 0x02, TP_BIT, 0l, 0},
    {4, 4, 0x00, TP_BYTE, 99l, 2},
    {6, 3, 0x04, TP_BIT, 0l, 0},
    {7, 5, 0x12, TP_STRING, 0l, 1}};
const S_SYS_ITEM prt_ipg05[] = {
    {2, 0, 0x10, TP_BIT, 0l, 0},
    {4, 6, 0x01, TP_BIT, 0l, 0},
    {6, 6, 0x02, TP_BIT, 0l, 0}};
const S_SYS_ITEM prt_ipg06[] = {
    {2, 7, 0x01, TP_BIT, 0l, 0},
    {4, 7, 0x02, TP_BIT, 0l, 0},
    {5, 7, 0x04, TP_BIT, 0l, 0}};
const S_SYS_ITEM prt_ipg07[] = {
    {2, 8, 0x01, TP_BIT, 0l, 0},
    {3, 8, 0x02, TP_BIT, 0l, 0},
    {4, 8, 0x04, TP_BIT, 0l, 0},
    {6, 9, 0x01, TP_BIT, 0l, 0}};
const S_SYS_ITEM prt_ipg08[] = {
    {1, 9, 0x02, TP_BIT, 0l, 0},
    {3, 9, 0x08, TP_BIT, 0l, 0},
    {4, 9, 0x04, TP_BIT, 0l, 0},
    {6, 11, 0x01, TP_BIT, 0l, 0}};
const S_SYS_ITEM prt_ipg09[] = {
    {2, 3, 0x08, TP_BIT, 0l, 0},
    {4, 12, 18, TP_STRING, 0l, 1},
    {5, 13, 18, TP_STRING, 0l, 1},
    {6, 14, 18, TP_STRING, 0l, 1},
    {7, 15, 18, TP_STRING, 0l, 1}};
const S_SYS_ITEM prt_ipg10[] = {
    {1, 11, 0x02, TP_BIT, 0l, 0},      /* 980605 */
    {2, 11, 0x04, TP_BIT, 0l, 0},
    {3, 11, 0x08, TP_BIT, 0l, 0}};
const S_SYS_ITEM prt_ipg11[] = {       /* 981210 */
    {1, 11, 0x10, TP_BIT, 0l, 0},
    {2, 11, 0x20, TP_BIT, 0l, 0},
    {4, 11, 0x40, TP_BIT, 0l, 0},
    {5, 11, 0x80, TP_BIT, 0l, 0}};

const S_SYS_PGM prt_pgm[MAX_PRT_OPT] = {
    {(sizeof(prt_ss01))/2, prt_ss01,
            (UBYTE)(sizeof(prt_ipg01)/sizeof(S_SYS_ITEM)), prt_ipg01},
    {(sizeof(prt_ss02))/2, prt_ss02,
            (UBYTE)(sizeof(prt_ipg02)/sizeof(S_SYS_ITEM)), prt_ipg02},
    {(sizeof(prt_ss0b))/2, prt_ss0b,
            (UBYTE)(sizeof(prt_ipg0b)/sizeof(S_SYS_ITEM)), prt_ipg0b},
    {(sizeof(prt_ss03))/2, prt_ss03,
            (UBYTE)(sizeof(prt_ipg03)/sizeof(S_SYS_ITEM)), prt_ipg03},
    {(sizeof(prt_ss04))/2, prt_ss04,
            (UBYTE)(sizeof(prt_ipg04)/sizeof(S_SYS_ITEM)), prt_ipg04},
    {(sizeof(prt_ss05))/2, prt_ss05,
            (UBYTE)(sizeof(prt_ipg05)/sizeof(S_SYS_ITEM)), prt_ipg05},
    {(sizeof(prt_ss06))/2, prt_ss06,
            (UBYTE)(sizeof(prt_ipg06)/sizeof(S_SYS_ITEM)), prt_ipg06},
    {(sizeof(prt_ss07))/2, prt_ss07,
            (UBYTE)(sizeof(prt_ipg07)/sizeof(S_SYS_ITEM)), prt_ipg07},
    {(sizeof(prt_ss08))/2, prt_ss08,
            (UBYTE)(sizeof(prt_ipg08)/sizeof(S_SYS_ITEM)), prt_ipg08},
    {(sizeof(prt_ss09))/2, prt_ss09,
            (UBYTE)(sizeof(prt_ipg09)/sizeof(S_SYS_ITEM)), prt_ipg09},
    {(sizeof(prt_ss10))/2, prt_ss10,   /* 980605 */
            (UBYTE)(sizeof(prt_ipg10)/sizeof(S_SYS_ITEM)), prt_ipg10},
    {(sizeof(prt_ss11))/2, prt_ss11,   /* 981210 */
            (UBYTE)(sizeof(prt_ipg11)/sizeof(S_SYS_ITEM)), prt_ipg11}};

/*************************************************************************/

const int tax_ss00[] = {
    106, 124, 107, 108, 109, 110};

const S_SYS_ITEM tax_ipg00[] = {
    {1, 0, 0x01, TP_BYTE, 4, 1},
    {2, 2, 0x06, TP_STRING, 0l, 12},
    {3, 1, 0x00, TP_BYTE, 2, 1}};

const S_SYS_PGM tax_pgm0[MAX_TAX0_OPT] = {
    {(sizeof(tax_ss00))/2, tax_ss00,
            (UBYTE)(sizeof(tax_ipg00)/sizeof(S_SYS_ITEM)), tax_ipg00}};

/*************************************************************************/

const int tax_ss01[] = {
    111, 197, 198, 199, 200};

const S_SYS_ITEM tax_ipg01[] = {
    {1, 138, 0x03, TP_REAL, 99999l, 5},
    {3, 142, 0x10, TP_BIT, 0l, 0},
    {4, 142, 0x20, TP_BIT, 0l, 0},
    {5, 142, 0x40, TP_BIT, 0l, 0}};

const S_SYS_PGM tax_pgm1[MAX_TAX1_OPT] = {
    {1, tax_ss01, 1, tax_ipg01}};
const S_SYS_PGM tax_pgm4[MAX_TAX1_OPT] = {
    {(sizeof(tax_ss01))/2, tax_ss01,
            (UBYTE)(sizeof(tax_ipg01)/sizeof(S_SYS_ITEM)), tax_ipg01}};

/*************************************************************************/

const int tax_ss02[] = {
    112, 0, 113, 0, 115, 116, 114};

const S_SYS_ITEM tax_ipg02[] = {
    {2, 0, 0x02, TP_REAL, 99999l, 5},
    {4, 4, 0x02, TP_REAL, 99999l, 5},
    {6, 16, 0x00, TP_BYTE, MAX_TAXBRK, 2},
    {7, 17, 0x00, TP_BYTE, MAX_TAXBRK, 2}};

const S_SYS_PGM tax_pgm2[MAX_TAX2_OPT] = {
    {(sizeof(tax_ss02))/2, tax_ss02,
            (UBYTE)(sizeof(tax_ipg02)/sizeof(S_SYS_ITEM)), tax_ipg02}};

/*************************************************************************/

const S_SYS_ITEM tax_ipg03[] = {
    {2, 0, 0x02, TP_REAL, 99999l, 5},
    {3, 0, 0x02, TP_REAL, 99999l, 5},
    {4, 0, 0x02, TP_REAL, 99999l, 5},
    {5, 0, 0x02, TP_REAL, 99999l, 5},
    {6, 0, 0x02, TP_REAL, 99999l, 5},
    {7, 0, 0x02, TP_REAL, 99999l, 5}};

const S_SYS_PGM tax_pgm3[MAX_TAX3_OPT] = {
    {0, tax_ss02,
            (UBYTE)(sizeof(tax_ipg03)/sizeof(S_SYS_ITEM)), tax_ipg03}};

/*************************************************************************/

const int pno_ss01[] = {
    0, 117, 118};

const S_SYS_ITEM pno_ipg01[] = {
    {7, 0, 0x13, TP_WORD, MAX_PLU, 3}};

const S_SYS_PGM pno_pgm[MAX_PNO_OPT] = {
    {(sizeof(pno_ss01))/2, pno_ss01,
            0, pno_ipg01}};
//            (UBYTE)(sizeof(pno_ipg01)/sizeof(S_SYS_ITEM)), pno_ipg01}};

/*************************************************************************/

const int dno_ss01[] = {
    0, 119, 120, 121, 122};

//const S_SYS_ITEM dno_ipg01[] = {
//    {7, 0, 0x13, TP_WORD, MAX_DEPT, 2}};

//const S_SYS_PGM dno_pgm[MAX_DNO_OPT] = {
//    {(sizeof(dno_ss01)), dno_ss01,
//            (UBYTE)(sizeof(dno_ipg01)/sizeof(S_SYS_ITEM)), dno_ipg01}};
const S_SYS_PGM dno_pgm[MAX_DNO_OPT] = {
    {(sizeof(dno_ss01))/2, dno_ss01,
            0, pno_ipg01}};

/*************************************************************************/

const int cno_ss01[] = {
    0, 123};

const S_SYS_ITEM cno_ipg01[] = {
    {2, 0, 0x13, TP_WORD, MAX_CLERK, 2}};

const S_SYS_PGM cno_pgm[MAX_CNO_OPT] = {
    {(sizeof(cno_ss01))/2, cno_ss01,
            (UBYTE)(sizeof(cno_ipg01)/sizeof(S_SYS_ITEM)), cno_ipg01}};

/*************************************************************************/

const int plu_ss01[] = {
    124, 130, 125, 126, 135, 136, 137};
const int plu_ss02[] = {
    138, 133, 134, 132, 131, 129, 139};
const int plu_ss12[] = {
    138, 133, 134, 132, 250, 129, 139};
const int plu_ss03[] = {
    201, 219, 220, 127, 233, 234};

const S_SYS_ITEM plu_ipg01[] = {
    {1, 0, 0x06, TP_STRING, 0l, 12},
    {2, 17, 0x01, TP_BIT, 0l, 0},
    {3, 12, 0x13, TP_ELONG, 99999999l, 8},
    {4, 18, 0x01, TP_BYTE, MAX_DEPT, 2},
    {5, 16, 0x01, TP_BIT, 0l, 0},
    {6, 16, 0x02, TP_BIT, 0l, 0},
    {7, 16, 0x04, TP_BIT, 0l, 0}};
const S_SYS_ITEM plu_ipg02[] = {
    {1, 16, 0x08, TP_BIT, 0l, 0},
    {2, 16, 0x10, TP_BIT, 0l, 0},
    {3, 16, 0x20, TP_BIT, 0l, 0},
    {4, 17, 0x40, TP_BIT, 0l, 0},
    {5, 17, 0x20, TP_BIT, 0l, 0},
    {6, 17, 0x02, TP_BIT, 0l, 0},
    {7, 17, 0x10, TP_BIT, 0l, 0}};
const S_SYS_ITEM plu_ipg03[] = {
    {1, 16, 0x40, TP_BIT, 0l, 0},
    {2, 17, 0x04, TP_BIT, 0l, 0},
    {3, 21, 0x00, TP_BYTE, MAX_TARE, 1},
    {4, 19, 0x13, TP_WORD, MAX_PLU, 3},
    {5, 17, 0x08, TP_BIT, 0l, 0},
    {6, 17, 0x80, TP_BIT, 0l, 0}};

const S_SYS_PGM plu_pgm[MAX_PLU_OPT] = {
    {(sizeof(plu_ss01))/2, plu_ss01,
            (UBYTE)(sizeof(plu_ipg01)/sizeof(S_SYS_ITEM)), plu_ipg01},
    {(sizeof(plu_ss02))/2, plu_ss02,
            (UBYTE)(sizeof(plu_ipg02)/sizeof(S_SYS_ITEM)), plu_ipg02},
    {(sizeof(plu_ss03))/2, plu_ss03,
            (UBYTE)(sizeof(plu_ipg03)/sizeof(S_SYS_ITEM)), plu_ipg03}};

const S_SYS_PGM plu_pgm2[MAX_PLU_OPT] = {
    {(sizeof(plu_ss01))/2, plu_ss01,
            (UBYTE)(sizeof(plu_ipg01)/sizeof(S_SYS_ITEM)), plu_ipg01},
    {(sizeof(plu_ss12))/2, plu_ss12,
            (UBYTE)(sizeof(plu_ipg02)/sizeof(S_SYS_ITEM)), plu_ipg02},
    {(sizeof(plu_ss03))/2, plu_ss03,
            (UBYTE)(sizeof(plu_ipg03)/sizeof(S_SYS_ITEM)), plu_ipg03}};

/*************************************************************************/

const int dept_ss01[] = {
    124, 130, 125, 135, 136, 137, 138};
const int dept_ss02[] = {
    128, 133, 134, 132, 131, 129, 139};
const int dept_ss12[] = {
    128, 133, 134, 132, 250, 129, 139};
const int dept_ss03[] = {
    201, 219, 220, 233, 234};

const S_SYS_ITEM dept_ipg01[] = {
    {1, 0, 0x06, TP_STRING, 0l, 12},
    {2, 17, 0x01, TP_BIT, 0l, 0},
    {3, 12, 0x13, TP_ELONG, 99999999l, 8},
    {4, 16, 0x01, TP_BIT, 0l, 0},
    {5, 16, 0x02, TP_BIT, 0l, 0},
    {6, 16, 0x04, TP_BIT, 0l, 0},
    {7, 16, 0x08, TP_BIT, 0l, 0}};
const S_SYS_ITEM dept_ipg02[] = {
    {1, 18, 0x00, TP_BYTE, MAX_GROUP-1, 1},
    {2, 16, 0x10, TP_BIT, 0l, 0},
    {3, 16, 0x20, TP_BIT, 0l, 0},
    {4, 17, 0x40, TP_BIT, 0l, 0},
    {5, 17, 0x20, TP_BIT, 0l, 0},
    {6, 17, 0x02, TP_BIT, 0l, 0},
    {7, 17, 0x10, TP_BIT, 0l, 0}};
const S_SYS_ITEM dept_ipg03[] = {
    {1, 16, 0x40, TP_BIT, 0l, 0},
    {2, 17, 0x04, TP_BIT, 0l, 0},
    {3, 19, 0x00, TP_BYTE, MAX_TARE, 1},
    {4, 17, 0x08, TP_BIT, 0l, 0},
    {5, 17, 0x80, TP_BIT, 0l, 0}};

const S_SYS_PGM dept_pgm[MAX_DEPT_OPT] = {
    {(sizeof(dept_ss01))/2, dept_ss01,
            (UBYTE)(sizeof(dept_ipg01)/sizeof(S_SYS_ITEM)), dept_ipg01},
    {(sizeof(dept_ss02))/2, dept_ss02,
            (UBYTE)(sizeof(dept_ipg02)/sizeof(S_SYS_ITEM)), dept_ipg02},
    {(sizeof(dept_ss03))/2, dept_ss03,
            (UBYTE)(sizeof(dept_ipg03)/sizeof(S_SYS_ITEM)), dept_ipg03}};

const S_SYS_PGM dept_pgm2[MAX_DEPT_OPT] = {
    {(sizeof(dept_ss01))/2, dept_ss01,
            (UBYTE)(sizeof(dept_ipg01)/sizeof(S_SYS_ITEM)), dept_ipg01},
    {(sizeof(dept_ss12))/2, dept_ss12,
            (UBYTE)(sizeof(dept_ipg02)/sizeof(S_SYS_ITEM)), dept_ipg02},
    {(sizeof(dept_ss03))/2, dept_ss03,
            (UBYTE)(sizeof(dept_ipg03)/sizeof(S_SYS_ITEM)), dept_ipg03}};

/*************************************************************************/

const int dtm_ss01[] = {
    140, 232, 0, 141, 0};

const S_SYS_ITEM dtm_ipg01[] = {
    {2, 0, 0x13, TP_TIME, 2359, 4},
    {5, 2, 0x13, TP_DATE, 123199, 6}};

const S_SYS_PGM dtm_pgm[MAX_DTM_OPT] = {
    {(sizeof(dtm_ss01))/2, dtm_ss01,
            (UBYTE)(sizeof(dtm_ipg01)/sizeof(S_SYS_ITEM)), dtm_ipg01}};

/*************************************************************************/

const int pcnt_ss00[] = {
    124, 146, 143, 156, 157, 144, 145};
const int pcnt_ss01[] = {
    124, 146, 186, 156, 157, 144, 145};
const int pcnt_ss02[] = {
    147, 148, 135, 136, 137, 138};

const S_SYS_ITEM pcnt_ipg00[] = {
    {1, 0, 0x06, TP_STRING, 0l, 12},
    {2, 16, 0x20, TP_BIT, 0, 0},
    {3, 12, 0x03, TP_REAL, 99999, 5},
    {4, 16, 0x01, TP_BIT, 0, 0},
    {5, 16, 0x02, TP_BIT, 0, 0},
    {6, 16, 0x04, TP_BIT, 0, 0},
    {7, 16, 0x10, TP_BIT, 0, 0}};

const S_SYS_ITEM pcnt_ipg01[] = {
    {1, 0, 0x06, TP_STRING, 0l, 12},
    {2, 16, 0x20, TP_BIT, 0, 0},
    {3, 12, 0x02, TP_REAL, 99999, 5},
    {4, 16, 0x01, TP_BIT, 0, 0},
    {5, 16, 0x02, TP_BIT, 0, 0},
    {6, 16, 0x04, TP_BIT, 0, 0},
    {7, 16, 0x10, TP_BIT, 0, 0}};

const S_SYS_ITEM pcnt_ipg02[] = {
    {1, 16, 0x40, TP_BIT, 0, 0},
    {2, 17, 0x01, TP_BIT, 0, 0},
    {3, 17, 0x02, TP_BIT, 0, 0},
    {4, 17, 0x04, TP_BIT, 0, 0},
    {5, 17, 0x10, TP_BIT, 0, 0},
    {6, 17, 0x20, TP_BIT, 0, 0}};

const S_SYS_PGM pcnt_pgm0[MAX_PCNT_OPT] = {
    {(sizeof(pcnt_ss00))/2, pcnt_ss00,
            (UBYTE)(sizeof(pcnt_ipg00)/sizeof(S_SYS_ITEM)), pcnt_ipg00},
    {(sizeof(pcnt_ss02))/2, pcnt_ss02,
            (UBYTE)(sizeof(pcnt_ipg02)/sizeof(S_SYS_ITEM)), pcnt_ipg02}};
const S_SYS_PGM pcnt_pgm1[MAX_PCNT_OPT] = {
    {(sizeof(pcnt_ss01))/2, pcnt_ss01,
            (UBYTE)(sizeof(pcnt_ipg01)/sizeof(S_SYS_ITEM)), pcnt_ipg01},
    {(sizeof(pcnt_ss02))/2, pcnt_ss02,
            (UBYTE)(sizeof(pcnt_ipg02)/sizeof(S_SYS_ITEM)), pcnt_ipg02}};


/*************************************************************************/

const int conv_ss01[] = {
    124, 143, 142};

const S_SYS_ITEM conv_ipg01[] = {
    {1, 0, 0x06, TP_STRING, 0l, 12},
    {2, 12, 0x13, TP_LONG, 99999999l, 8},  /* 981210 */
    {3, 16, 0x00, TP_BYTE, 9, 1}};

const S_SYS_PGM conv_pgm[MAX_CONV_OPT] = {
    {(sizeof(conv_ss01))/2, conv_ss01,
            (UBYTE)(sizeof(conv_ipg01)/sizeof(S_SYS_ITEM)), conv_ipg01}};

/*************************************************************************/

const int clk_ss01[] = {
    149, 150};

const S_SYS_ITEM clk_ipg01[] = {
    {1, 0, 0x06, TP_STRING, 0l, 12},
    {2, 12, 0x13, TP_LONG, 999999l, 6}};

const S_SYS_PGM clk_pgm[MAX_CLK_OPT] = {
    {(sizeof(clk_ss01))/2, clk_ss01,
            (UBYTE)(sizeof(clk_ipg01)/sizeof(S_SYS_ITEM)), clk_ipg01}};

/*************************************************************************/

const int msg_ss01[] = {
    151, 0, 152, 0, 153, 0};
const int msg_ss02[] = {
    154, 0, 155, 0};

const S_SYS_ITEM msg_ipg01[] = {
    {2, 0, 0x00, TP_STRING, 0l, MAX_MSG_DESC},
    {4, 26, 0x00, TP_STRING, 0l, MAX_MSG_DESC},
    {6, 52, 0x00, TP_STRING, 0l, MAX_MSG_DESC}};
const S_SYS_ITEM msg_ipg02[] = {
    {2, 78, 0x00, TP_STRING, 0l, MAX_MSG_DESC},
    {4, 104, 0x00, TP_STRING, 0l, MAX_MSG_DESC}};

const S_SYS_PGM msg_pgm[MAX_MSG_OPT] = {
    {(sizeof(msg_ss01))/2, msg_ss01,
            (UBYTE)(sizeof(msg_ipg01)/sizeof(S_SYS_ITEM)), msg_ipg01},
    {(sizeof(msg_ss02))/2, msg_ss02,
            (UBYTE)(sizeof(msg_ipg02)/sizeof(S_SYS_ITEM)), msg_ipg02}};

/*************************************************************************/

const int grp_ss01[] = {
    187, 188, 189, 190, 191};
const int grp_ss02[] = {
    192, 193, 194, 195, 196};

const S_SYS_ITEM grp_ipg01[] = {
    {1, 0, 0x07, TP_STRING, 0l, MAX_GRP_DESC},
    {2, 12, 0x07, TP_STRING, 0l, MAX_GRP_DESC},
    {3, 24, 0x07, TP_STRING, 0l, MAX_GRP_DESC},
    {4, 36, 0x07, TP_STRING, 0l, MAX_GRP_DESC},
    {5, 48, 0x07, TP_STRING, 0l, MAX_GRP_DESC}};
const S_SYS_ITEM grp_ipg02[] = {
    {1, 60, 0x07, TP_STRING, 0l, MAX_GRP_DESC},
    {2, 72, 0x07, TP_STRING, 0l, MAX_GRP_DESC},
    {3, 84, 0x07, TP_STRING, 0l, MAX_GRP_DESC},
    {4, 96, 0x07, TP_STRING, 0l, MAX_GRP_DESC},
    {5, 108, 0x07, TP_STRING, 0l, MAX_GRP_DESC}};

const S_SYS_PGM grp_pgm[MAX_GRP_OPT] = {
    {(sizeof(grp_ss01))/2, grp_ss01,
            (UBYTE)(sizeof(grp_ipg01)/sizeof(S_SYS_ITEM)), grp_ipg01},
    {(sizeof(grp_ss02))/2, grp_ss02,
            (UBYTE)(sizeof(grp_ipg02)/sizeof(S_SYS_ITEM)), grp_ipg02}};

/*************************************************************************/

const int void_ss01[] = {
    124, 156, 157, 158, 20};

const S_SYS_ITEM void_ipg01[] = {
    {1, 18, 0x06, TP_STRING, 0l, 12},
    {2, 34, 0x01, TP_BIT, 0, 0},
    {3, 34, 0x02, TP_BIT, 0, 0},
    {4, 30, 0x13, TP_DLONG, 99999999l, 8}};

const S_SYS_ITEM void_ipg02[] = {
    {1, 0, 0x06, TP_STRING, 0l, 12},
    {2, 16, 0x01, TP_BIT, 0, 0},
    {3, 16, 0x02, TP_BIT, 0, 0},
    {4, 12, 0x13, TP_DLONG, 99999999l, 8}};

const S_SYS_PGM void_pgm[MAX_VOID_OPT] = {
    {(sizeof(void_ss01))/2, void_ss01,
            (UBYTE)(sizeof(void_ipg01)/sizeof(S_SYS_ITEM)), void_ipg01},
    {(sizeof(void_ss01))/2, void_ss01,
            (UBYTE)(sizeof(void_ipg02)/sizeof(S_SYS_ITEM)), void_ipg02}};

/*************************************************************************/

const int ns_ss01[] = {
    221, 222, 156, 159, 160, 161};
const int ns_ss02[] = {
    162, 163};

const S_SYS_ITEM ns_ipg01[] = {
    {1, 0, 0x07, TP_STRING, 0l, 12},
    {2, 18, 0x07, TP_STRING, 0l, 12},
    {3, 16, 0x01, TP_BIT, 0, 0},
    {5, 16, 0x02, TP_BIT, 0, 0},
    {6, 16, 0x04, TP_BIT, 0, 0}};

const S_SYS_ITEM ns_ipg02[] = {
    {2, 16, 0x10, TP_BIT, 0, 0}};

const S_SYS_PGM ns_pgm[MAX_NS_OPT] = {
    {(sizeof(ns_ss01))/2, ns_ss01,
            (UBYTE)(sizeof(ns_ipg01)/sizeof(S_SYS_ITEM)), ns_ipg01},
    {(sizeof(ns_ss02))/2, ns_ss02,
            (UBYTE)(sizeof(ns_ipg02)/sizeof(S_SYS_ITEM)), ns_ipg02}};

/*************************************************************************/

const int scale_ss01[] = {
    124, 156, 157, 202, 203, 204, 205};
const int scale_ss02[] = {
    206, 207, 208};

const S_SYS_ITEM scale_ipg01[] = {
    {1, 0, 0x06, TP_STRING, 0l, 12},
    {2, 16, 0x01, TP_BIT, 0, 0},
    {3, 16, 0x02, TP_BIT, 0, 0},
    {4, 16, 0x04, TP_BIT, 0, 0},
    {6, 16, 0x10, TP_BIT, 0, 0},
    {7, 16, 0x20, TP_BIT, 0, 0}};

const S_SYS_ITEM scale_ipg02[] = {
    {1, 16, 0x40, TP_BIT, 0, 0},
    {3, 17, 0x01, TP_BIT, 0, 0}};

const S_SYS_PGM scale_pgm[MAX_SCALE_OPT] = {
    {(sizeof(scale_ss01))/2, scale_ss01,
            (UBYTE)(sizeof(scale_ipg01)/sizeof(S_SYS_ITEM)), scale_ipg01},
    {(sizeof(scale_ss02))/2, scale_ss02,
            (UBYTE)(sizeof(scale_ipg02)/sizeof(S_SYS_ITEM)), scale_ipg02}};

/*************************************************************************/

const int tare_ss01[] = {
    209, 210, 211, 212, 213};

const S_SYS_ITEM tare_ipg01[] = {
    {1, 0, 0x13, TP_TARE, 9999l, 4},
    {2, 2, 0x13, TP_TARE, 9999l, 4},
    {3, 4, 0x13, TP_TARE, 9999l, 4},
    {4, 6, 0x13, TP_TARE, 9999l, 4},
    {5, 8, 0x13, TP_TARE, 9999l, 4}};

const S_SYS_PGM tare_pgm[MAX_TARE_OPT] = {
    {(sizeof(tare_ss01))/2, tare_ss01,
            (UBYTE)(sizeof(tare_ipg01)/sizeof(S_SYS_ITEM)), tare_ipg01}};

/*************************************************************************/

const int sft_ss01[] = {
    124, 156, 164, 165};

const S_SYS_ITEM sft_ipg01[] = {
    {1, 0, 0x06, TP_STRING, 0l, 12},
    {2, 16, 0x01, TP_BIT, 0, 0},
    {3, 16, 0x02, TP_BIT, 0, 0}};

const S_SYS_PGM sft_pgm[MAX_SFT_OPT] = {
    {(sizeof(sft_ss01))/2, sft_ss01,
            (UBYTE)(sizeof(sft_ipg01)/sizeof(S_SYS_ITEM)), sft_ipg01}};

/*************************************************************************/

const int cash_ss01[] = {
    124, 158, 20, 166, 167, 168};
const int cash_ss02[] = {
    169, 170, 171, 172, 173, 174};

const S_SYS_ITEM cash_ipg01[] = {
    {1, 0, 0x06, TP_STRING, 0l, 12},
    {2, 12, 0x13, TP_DLONG, 99999999l, 8},
    {4, 16, 0x01, TP_BIT, 0, 0},
    {6, 16, 0x02, TP_BIT, 0, 0}};

const S_SYS_ITEM cash_ipg02[] = {
    {1, 16, 0x04, TP_BIT, 0, 0},
    {2, 16, 0x10, TP_BIT, 0, 0},
    {3, 17, 0x01, TP_BIT, 0, 0},
    {4, 17, 0x02, TP_BIT, 0, 0},
    {5, 17, 0x04, TP_BIT, 0, 0},
    {6, 17, 0x10, TP_BIT, 0, 0}};

const S_SYS_PGM cash_pgm[MAX_CASH_OPT] = {
    {(sizeof(cash_ss01))/2, cash_ss01,
            (UBYTE)(sizeof(cash_ipg01)/sizeof(S_SYS_ITEM)), cash_ipg01},
    {(sizeof(cash_ss02))/2, cash_ss02,
            (UBYTE)(sizeof(cash_ipg02)/sizeof(S_SYS_ITEM)), cash_ipg02}};

/*************************************************************************/

const int misc_ss02[] = {
    169, 170, 132, 171, 172, 173, 174};

const S_SYS_ITEM misc_ipg02[] = {
    {1, 16, 0x04, TP_BIT, 0, 0},
    {2, 16, 0x10, TP_BIT, 0, 0},
    {3, 16, 0x20, TP_BIT, 0, 0},
    {4, 17, 0x01, TP_BIT, 0, 0},
    {5, 17, 0x02, TP_BIT, 0, 0},
    {6, 17, 0x04, TP_BIT, 0, 0},
    {7, 17, 0x10, TP_BIT, 0, 0}};

const S_SYS_PGM misc_pgm[MAX_MISC_OPT] = {
    {(sizeof(cash_ss01))/2, cash_ss01,
            (UBYTE)(sizeof(cash_ipg01)/sizeof(S_SYS_ITEM)), cash_ipg01},
    {(sizeof(misc_ss02))/2, misc_ss02,
            (UBYTE)(sizeof(misc_ipg02)/sizeof(S_SYS_ITEM)), misc_ipg02}};

/*************************************************************************/

const int inv_ss01[] = {
    98};

const S_SYS_ITEM inv_ipg01[] = {
    {2, 0, 0x02, TP_REAL, 999999999l, 9}};

const S_SYS_PGM inv_pgm[MAX_INV_OPT] = {
    {(sizeof(inv_ss01))/2, inv_ss01,
            (UBYTE)(sizeof(inv_ipg01)/sizeof(S_SYS_ITEM)), inv_ipg01}};

/*************************************************************************/

const int cio_ss01[] = {
    217, 218, 217, 218, 217, 218};
const int cio_ss03[] = {
    217, 218, 217, 218};

const S_SYS_ITEM cio_ipg01[] = {
    {1, 0, 0x0c, TP_DATE, 123199, 6},
    {1,64, 0x13, TP_TIME, 2400, 4},
    {2, 4, 0x0c, TP_DATE, 123199, 6},
    {2,66, 0x13, TP_TIME, 2400, 4},
    {3, 8, 0x0c, TP_DATE, 123199, 6},
    {3,68, 0x13, TP_TIME, 2400, 4},
    {4,12, 0x0c, TP_DATE, 123199, 6},
    {4,70, 0x13, TP_TIME, 2400, 4},
    {5,16, 0x0c, TP_DATE, 123199, 6},
    {5,72, 0x13, TP_TIME, 2400, 4},
    {6,20, 0x0c, TP_DATE, 123199, 6},
    {6,74, 0x13, TP_TIME, 2400, 4}};

const S_SYS_ITEM cio_ipg02[] = {
    {1,24, 0x0c, TP_DATE, 123199, 6},
    {1,76, 0x13, TP_TIME, 2400, 4},
    {2,28, 0x0c, TP_DATE, 123199, 6},
    {2,78, 0x13, TP_TIME, 2400, 4},
    {3,32, 0x0c, TP_DATE, 123199, 6},
    {3,80, 0x13, TP_TIME, 2400, 4},
    {4,36, 0x0c, TP_DATE, 123199, 6},
    {4,82, 0x13, TP_TIME, 2400, 4},
    {5,40, 0x0c, TP_DATE, 123199, 6},
    {5,84, 0x13, TP_TIME, 2400, 4},
    {6,44, 0x0c, TP_DATE, 123199, 6},
    {6,86, 0x13, TP_TIME, 2400, 4}};

const S_SYS_ITEM cio_ipg03[] = {
    {1,48, 0x0c, TP_DATE, 123199, 6},
    {1,88, 0x13, TP_TIME, 2400, 4},
    {2,52, 0x0c, TP_DATE, 123199, 6},
    {2,90, 0x13, TP_TIME, 2400, 4},
    {3,56, 0x0c, TP_DATE, 123199, 6},
    {3,92, 0x13, TP_TIME, 2400, 4},
    {4,60, 0x0c, TP_DATE, 123199, 6},
    {4,94, 0x13, TP_TIME, 2400, 4}};

const S_SYS_PGM cio_pgm[MAX_CIO_OPT] = {
    {(sizeof(cio_ss01))/2, cio_ss01,
            (UBYTE)(sizeof(cio_ipg01)/sizeof(S_SYS_ITEM)), cio_ipg01},
    {(sizeof(cio_ss01))/2, cio_ss01,
            (UBYTE)(sizeof(cio_ipg02)/sizeof(S_SYS_ITEM)), cio_ipg02},
    {(sizeof(cio_ss03))/2, cio_ss03,
            (UBYTE)(sizeof(cio_ipg03)/sizeof(S_SYS_ITEM)), cio_ipg03}};

/*************************************************************************/

const int alph_ss01[] = {
    175, 176, 177, 178, 179, 180};
const int alph_ss02[] = {
    181, 182, 183, 184, 185};

const S_SYS_ITEM alph_ipg01[] = {
    {7, 0, 0x01, TP_BYTE, MAX_SPECIAL, 2}};
const S_SYS_ITEM alph_ipg02[] = {
    {7, 0, 0x01, TP_BYTE, MAX_SPECIAL, 2}};

const S_SYS_PGM alph_pgm[MAX_OTH_ALPH] = {
    {(sizeof(alph_ss01))/2, alph_ss01,
            (UBYTE)(sizeof(alph_ipg01)/sizeof(S_SYS_ITEM)), alph_ipg01},
    {(sizeof(alph_ss02))/2, alph_ss02,
            (UBYTE)(sizeof(alph_ipg02)/sizeof(S_SYS_ITEM)), alph_ipg02}};

