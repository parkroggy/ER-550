#include <stdio.h>
#include <er1io51.h>
#include <er1exm.h>

extern void des_prn();
extern void mkrandom(long value,char ofst,char st);
extern void sep_prn();
extern void pmemcpy(UBYTE *, UBYTE *, unsigned int);
extern void cmemcpy(UBYTE *, UBYTE *, UBYTE);
extern void mk_idmsg( unsigned char *desc, long amt, UBYTE stay, UBYTE sp);

/*****************************************************************************/
void logo_sub(char type)
{
    cmemcpy(prt_buffer,code_mem->logo_strs[type],27);
    des_prn();
}

void logo_only(char type)
{
 char msg_no;

 switch(type){
    /* PMODE LOGO */
    case  1   :           /* - INACTIVE !          */
    case  2   :           /*    DESCRIPTOR SCAN    */
    case  3   :           /*  MISCELLANEOUS SCAN   */
    case  4   :           /*    DEPARTMENT SCAN    */
    case  5   :           /*       PLU SCAN        */
    case  6   :           /* EUROPEAN ROUND :      */
    case  7   :           /* - NOT PROGRAMMED !    */
        msg_no = type - 1;
        break;
    /* RMODE LOGO */
    case 15   :           /* NO SALES ------------ */
    case 16   :           /* RETURN ************** */
    case 17   :           /* ERROR CORRECT ------- */
    case 18   :           /* PREVIOUS VOID ------- */
    case 19   :           /* *   CHECK CASHING   * */
    case 20   :           /* ALL CANCEL ********** */
        msg_no = type - 8;
        break;
    /* X MODE LOGO */
    case 27   :           /* CLERK TIME            */ /*yoo 1011 */
    case 28   :           /*  ALL Z REPORT ISSUE   */
    case 29   :           /* ALL CLERKS            */
    case 30   :           /* OPEN CLERK            */
    case 31   :           /* * CASH  DECLARATION * */
    case 32   :           /* FROM/TO PLU           */
    case 33   :           /* FROM/TO DEPT          */
    case 34   :           /* TIME                  */
    case 35   :           /* DAILY SALES           */
    case 36   :           /* GROUP                 */
    case 37   :           /* IN-DRAWER             */
    case 38   :           /* ALL PLU               */
    case 39   :           /* FINANCIAL             */
    case 40   :           /* INDIVIDUAL CLERK      */
    /* main LOGO */
    case 41   :           /* INITIAL CLEAR !       */
    case 42   :           /* RESET ALL CNT/TOTAL ! */
    case 43   :           /* RESET GRAND TOTAL !   */
    case 44   :           /* RAM ALL CLEAR !       */
    case 45   :           /*  ### POWER  FAIL ###  */
    case 46   :           /* ALL PLU (STOCK)       */
    case 47   :           /* DEPARTMENT (STOCK)    */
    case 48   :           /* VERSION */
    case 49   :           /* * PC-ECR COMM. MODE * */
    case 50   :           /* ** TRANSMIT  ERROR ** */
    case 51   :           /* **  RECEIVE ERROR  ** */
    case 52   :           /* = LINE DISCONNECTION  */
    case 53   :           /* **   COMM. ERROR   ** */
        msg_no = type - 14;  /* yoo 1011*/
        break;
    /* VOID MODE LOGO */
    case LOGO_VOID  :     /* VOID MODE **************** */
    case LOGO_MODEL :     /* ER-550:STD 01              */
    case LOGO_H     :     /* HHHHHHHHHHHHHHHHHHHHHHHHHH */
    case LOGO_STAR  :     /* ************************** */
    case LOGO_LINE  :     /* -------------------------- */
        logo_sub(type - LOGO_VOID);
        return;
    default   : break;
    }

 cmemcpy(prt_buffer,code_mem->logo_str[msg_no],22);des_prn();
}
/*****************************************************************************/
void logo_nur(char type)
{
 char msg_no;

 switch(type){
    /* PMODE LOGO */
    case  2   :           /* DWR LIMIT AMT  */
    case  3   :           /* CASH HALO      */
    case  4   :           /* CHECK TND HALO */
    case  5   :           /* CHECK CNG HALO */
        msg_no = type - 2;
        break;
    case  7   :           /*  CNT -         */
    case  8   :           /*  CNT +         */
    case  9   :           /*  PRESET AMT    */
    case  10  :           /*  HALO AMT      */
    case  11  :           /*  LINKED DEPT   */
        msg_no = type - 3;
        break;
    case  13  :           /* DEPT SYSTEM    */
        msg_no = 9;
        break;
    /** REG MODE */
    case  18  :           /* SUBTOTAL       */
//    case  19  :           /* FOREIGN AMT    */
    case  20  :           /* HOME AMT       */
    case  21  :           /* TAX AMT        */
        msg_no = type - 8;
        break;
    /** X MODE */
    case  31  :           /*  QTY           */
    case  32  :           /*  TIME WORKED:  */
    case  33  :           /*  SALES AMT     */
    case  34  :           /* TOTAL CNT      */
    case  35  :           /* TOTAL AMT      */
    case  36  :           /* TOTAL WORKED:  */
    case  37  :           /* CASH DEC AMT   */
    case  38  :           /* CHK DEC AMT    */
    case  39  :           /* OVER/SHORT     */
        msg_no = type - 17;
        break;
    case  40  :           /* NON-ADD#       */
        pmemcpy(prt_buffer,FUNCKEY[NONADD-CASH].DESC,12);
        msg_no = 99;
        break;
    case  LOGO_BLANK  : msg_no = 24;    break;

    default   : break;
    }

 if(msg_no != 99)
    cmemcpy(prt_buffer,code_mem->nur_str[msg_no],15);
 if((type == 20) || (type == 21))
    mk_idmsg(prt_buffer,nur,0,1);
 sep_prn();
 return;
}

/*****************************************************************************/
void mkline()
{
 logo_only(LOGO_LINE);
 return;
}
/*****************************************************************************/
void mkstar()
{
 logo_only(LOGO_STAR);
 return;
}
