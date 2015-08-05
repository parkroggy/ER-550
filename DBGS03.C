#include <h:\tc\include\stdio.h>
#include <dos.h>
#include <conio.h>
#include <er1io51.h>
#include <fcntl.h>
#include <sys\stat.h>

#define MAX_STUB 1650

#define PORT1   0x3f8
#define PORT2   0x2f8

#define DATA    0
#define IER     1
#define IIR     2
#define LCR     3
#define MCR     4
#define LSR     5
#define MSR     6
#define ONMASK  0xe7
#define OFFMASK 0x18
#define PICMASK 0x21
#define PICEOI  0x20
#define IRQ4    0x0c
#define IRQ3    0x0b
#define DATA7   0x02
#define DATA8   0x03
#define STOP1   0x00
#define STOP2   0x04
#define NOPA    0x00
#define ODDP    0x08
#define EVENP   0x18
#define B1200   0x80
#define B2400   0xa0
#define B4800   0xc0
#define B9600   0xe0

#define ETX     0x03

extern  char r_off, regstep, buf_cnt, buft_cnt;
extern  char stubbuf[MAX_STUB];
extern  unsigned char   comm_buff[MAX_RTBUF];
unsigned char   PC_PORT=1;
unsigned int    if1=0, ir1=0;
void interrupt  (*oldvect1)();

int py=1;
FILE *fp;
UBYTE bufbc[0x400];

extern  S_CLK_PGM CLERK_P[MAX_CLERK];
extern  S_DEPT_PGM dept[MAX_DEPT];
extern  S_PLU_PGM plu[MAX_PLU];
extern  S_SYS_OPT SYS_OPT;
extern  S_PRT_OPT PRT_OPT;
extern  S_FUNCKEY FUNCKEY[MAX_FUNCKEY];
extern  S_TAX_TBL tax_table[MAX_TAX];
extern  rep_z rep[MAX_FIN+MAX_DEPT+(MAX_CLERK*MAX_CLKITEM)
                                      +25+32+(MAX_GROUP+1)+(MAX_PLU+1)];
extern  rep_z2 rep2[MAX_FIN];


extern  char    mode_id, scale_bit;
extern  char    flg_key_pend;                    /*entered key count      */
extern  char    flg_key_buf[MAX_KEYBUF];                 /*15 byte                */
extern  char    dcnt;                           /* count of fraction part */
extern  char    ncnt;                           /* count of numeric */
extern  char    rcnt;                           /* dept repeat counter */
extern  long    nur;                            /* numeric txt */
extern  char    zero_flg;
extern  char    flg_dis_txtmp[10];              /* display text 10 byte */
extern  char    decp_buf[10];                   /* decimal & cap display in the outdtx(); */
extern  char    tnd_clrs;
extern  char    tnd_clre;
extern  char    prt_buffer[200];                /* address value  9ch            */
extern  unsigned char   dsp_y;
extern  unsigned char dsp_buf[MAX_LINE][MAX_CLM+1];
extern  char    numtxt[50];                     /* address should be not changed */
extern  int     func;                           /* function key code */
extern  int     sfunc;                          /* function key save */
extern  long    dnur;                           /* float decimal nur */
extern  int     pcode;                          /* plu function key code */
extern  int     spcode;                         /* plu function key code save */
extern  char    dptsav_id;
extern  char    dptsav1_id;
extern  char    twosave_id;
extern  char    rtcb_flg[25];
extern  long    pfail_amt;
extern  unsigned     char   blk_time    ;   /*  071h  */
extern  unsigned     char   low_add     ;   /*  072h  */
extern  unsigned     char   high_add    ;   /*  073h  */
extern  char    fs_t_buf[40];
extern  S_SYS_OPT SYS_OPT;
extern  S_PRT_OPT PRT_OPT;
extern  S_CODE_MEM real_code;
extern  char rstepold_id;
extern  char r_cont;
extern  char romsum_low;
extern  char romsum_hig;

void    prn();

void HideCursor(void)
{
   union REGS r;

   r.h.ah = 1;
   r.h.ch = 0x20;
   r.h.cl = 0x07;
   int86(0x10, &r, &r);
}

/**************************************************************************/
void ShowCursor(void)
{
   union REGS r;

   r.h.ah = 1;
   r.h.ch = 0x06;
   r.h.cl = 0x07;
   int86(0x10, &r, &r);
}

void recv_chk(UBYTE ch)
{
    while(1)
        {
	dsave_flg = 0;
        if(data_s_end != 1)
            {                          /* chk_stx */
            if(stx_flg != 1)
                {                      /* chk_dle0 */
                if(ch != DLE)
                    {                  /* chk_dle1 */
                    if(dle_flg != 1)
                        {
                        return;
                        }
                    else
                        {
			if(ch != STX)
                            {          /* chk_ack */
                            if(ch != ACK)
                                {      /* chk_nack */
                                if(ch == NACK)
                                    nack_flg = 1;
                                return;
                                }
                            else
                                {
                                ack_flg = 1;
                                return;
                                }
			    }
                        else
                            {
                            stx_flg = 1;
                            return;
                            }
                        }
                    }
                else
                    {
                    dle_flg = 1;
                    return;
                    }
		}
            else
                {
                if(io_cnt != 0)
                    {                  /* ld_itm_cnt */
                    if(comm_buff[0] <= io_cnt)
                        {              /* mk_s_end */
                        data_s_end = 1;
                        continue;
                        }
                    else
                        {              /* sv_drecv */
                        dsave_flg = 1;
			return;
                        }
                    }
                else
                    {                  /* sv_drecv */
                    dsave_flg = 1;
                    return;
                    }
                }
            }
        else
            {                          /* end_del_chk */
            if(etx_flg != 1)
		{                      /* ck_e_del */
                if(ch != DLE)
                    {                  /* go_drecv */
                    if(ch != ETX)
                        {              /* chk_crc */
                        if(rend_flg != 0)
                            {          /* crc2_sv */
                            crc2_data = ch;
                            rend_flg = 2;
                            }
                        else
                            {
                            crc1_data = ch;
			    rend_flg = 1;
                            }
                        return;
                        }
                    else
                        {
                        etx_flg = 1;
                        return;
                        }
                    }
                else
                    return;
                }
	    else
                {                      /* chk_crc */
                if(rend_flg != 0)
                    {          /* crc2_sv */
                    crc2_data = ch;
                    rend_flg = 2;
                    }
                else
                    {
                    crc1_data = ch;
                    rend_flg = 1;
                    }
                return;
		}
            }
        }
}

void interrupt intsr()
{
    UBYTE ch;
    int i;

    ir1 %= MAX_RTBUF;
    if(PC_PORT == 1)
        ch = inportb(DATA+PORT1);
    else
        ch = inportb(DATA+PORT2);
    outportb(PICEOI, 0x20);

    if(comm_kind == 0)                 /* PC */
        {
        if(s_in_flg == 0)
            return;
        recv_chk(ch);
        if(dsave_flg == 1)
            comm_buff[io_cnt++] = ch;
        }
    else if(comm_kind == 2)            /* Scale */
	{
        ch = comm_buff[ir1++] = ch & 0x7f;
        if(ch == ETX)
            rend_flg = 1;
        }
    else if(comm_kind == 3)
        {
        ch = comm_buff[ir1++] = ch & 0x7f;
        if(ch == 0x0a) {
            if(ir1 > 5)
                {
                ir1 = 0;
                return;
		}
            ir1 = 0;
            rend_flg = 2;
            liq_cpy();
            }
        }
}

void rsout(unsigned char ch)
{
    if(PC_PORT == 1)
        {
        do{}while(!(inportb(LSR+PORT1) & 0x20));
	outportb(DATA+PORT1,ch);
        }
    else
        {
        do{}while(!(inportb(LSR+PORT2) & 0x20));
        outportb(DATA+PORT2,ch);
        }
}

void init_port()
{
return;
    if(PC_PORT == 1)
	{
        oldvect1 = getvect(IRQ4);
        setvect(IRQ4, intsr);
        bioscom(0, DATA8 | STOP1 | NOPA | B9600, 0);
        outportb(MCR+PORT1, 0x0b);  outportb(IER+PORT1, 0x01);
        }
    else
        {
        oldvect1 = getvect(IRQ3);
        setvect(IRQ3, intsr);
        bioscom(0, DATA8 | STOP1 | NOPA | B9600, 1);
        outportb(MCR+PORT2, 0x0b);  outportb(IER+PORT2, 0x01);
        }
    outportb(PICMASK, inportb(PICMASK) & ONMASK);
}

void close_port()
{
return;
    if(PC_PORT == 1)
        {
        outportb(MCR+PORT1, 0x00);  outportb(IER+PORT1, 0x00);
        }
    else
        {
        outportb(MCR+PORT2, 0x00);  outportb(IER+PORT2, 0x00);
	}
        outportb(PICMASK, inportb(PICMASK) | OFFMASK);
    if(PC_PORT == 1)
        setvect(IRQ4, oldvect1);
    else
        setvect(IRQ3, oldvect1);
}

void window_lcd(UBYTE box)
{
    int i;
    window(54,2,75,12);
    textattr(0x1f);
    if(box)
	{
	for(i=0;i<20;i++)
	    {
	    gotoxy(i+2,1);  putch('Í');
	    gotoxy(i+2,10);  putch('Í');
	    }
	for(i=0;i<8;i++)
	    {
	    gotoxy(1,i+2);  putch('º');
	    gotoxy(22,i+2);  putch('º');
	    }
	gotoxy(1,1);  putch('É');
	gotoxy(1,10);  putch('È');
	gotoxy(22,1);  putch('»');
	gotoxy(22,10);  putch('¼');
	}
    window(55,3,74,11);
}

void window_turret()
{
    int i;
    window(35,2,50,5);
    textattr(0x1f);
    for(i=0;i<10;i++)
	{
	gotoxy(i+2,1);  putch('Í');
	gotoxy(i+2,3);  putch('Í');
	}
    gotoxy(1,2);  putch('º');
    gotoxy(12,2);  putch('º');
    gotoxy(1,1);  putch('É');
    gotoxy(1,3);  putch('È');
    gotoxy(12,1);  putch('»');
    gotoxy(12,3);  putch('¼');
    window(36,3,49,4);
}

void pkr_cpy()                         /* OK */
{
}

void clr_lcd()                         /* OK */
{
    window_lcd(1);
    clrscr();
    window_lcd(1);
    dsp_y = 0;
    memset(dsp_buf, 0x20, 0xa8);
}

void lcdwrt1()                         /* OK */
{
}

void lcdwrt2()                         /* OK */
{
}

void init_mdchg()                      /* OK */
{
    rcnt = 0;
    zero_flg = 0;
    clear_bit = err_bit = 0;
    nur = 0;
    ncnt = dcnt = 0;
    knur_bit = kdec_bit = 0;
}

void compdchk()
{
    char far *kptr;

    kptr = (char far *)0x00400017;
    if(*kptr & 0x10)
        compd_flg = 1;
    else
        compd_flg = 0;
}

void endclr()                          /* OK */
{
    int i;

    i = &tnd_clrs - &tnd_clre;
    memset(&tnd_clre, 0, i);
}

void exramclr()
{
}

void save_mem()
{
    int hd;
#if 0
    hd = open("rep1.zzz", O_RDWR | O_BINARY | O_CREAT | O_TRUNC, S_IWRITE);
    if(hd >= 0)
        {
	write(hd, rep, sizeof(rep));
        close(hd);
        }

    hd = open("rep2.zzz", O_RDWR | O_BINARY | O_CREAT | O_TRUNC, S_IWRITE);
    if(hd >= 0)
        {
        write(hd, rep2, sizeof(rep2));
        close(hd);
        }
#endif
    hd = open("clerk.zzz", O_RDWR | O_BINARY | O_CREAT | O_TRUNC, S_IWRITE);
    if(hd >= 0)
	{
        write(hd, CLERK_P, sizeof(CLERK_P));
        close(hd);
        }

    hd = open("dept.zzz", O_RDWR | O_BINARY | O_CREAT | O_TRUNC, S_IWRITE);
    if(hd >= 0)
        {
        write(hd, dept, sizeof(dept));
        close(hd);
        }

    hd = open("plu.zzz", O_RDWR | O_BINARY | O_CREAT | O_TRUNC, S_IWRITE);
    if(hd >= 0)
        {
        write(hd, plu, sizeof(plu));
        close(hd);
        }

    hd = open("funckey.zzz", O_RDWR | O_BINARY | O_CREAT | O_TRUNC, S_IWRITE);
    if(hd >= 0)
        {
        write(hd, FUNCKEY, sizeof(FUNCKEY));
        close(hd);
        }

    hd = open("tax.zzz", O_RDWR | O_BINARY | O_CREAT | O_TRUNC, S_IWRITE);
    if(hd >= 0)
        {
        write(hd, tax_table, sizeof(tax_table));
        close(hd);
        }

    hd = open("sysopt.zzz", O_RDWR | O_BINARY | O_CREAT | O_TRUNC, S_IWRITE);
    if(hd >= 0)
        {
        write(hd, &SYS_OPT, sizeof(SYS_OPT));
        close(hd);
        }

    hd = open("prtopt.zzz", O_RDWR | O_BINARY | O_CREAT | O_TRUNC, S_IWRITE);
    if(hd >= 0)
        {
        write(hd, &PRT_OPT, sizeof(PRT_OPT));
        close(hd);
        }
}

void load_mem()
{
    int hd;
#if 0
    hd = open("rep1.zzz", O_RDWR | O_BINARY, S_IREAD);
    if(hd >= 0)
        {
        read(hd, rep, sizeof(rep));
        close(hd);
        }

    hd = open("rep2.zzz", O_RDWR | O_BINARY, S_IREAD);
    if(hd >= 0)
        {
        read(hd, rep2, sizeof(rep2));
        close(hd);
        }
#endif
    hd = open("clerk.zzz", O_RDWR | O_BINARY, S_IREAD);
    if(hd >= 0)
        {
        read(hd, CLERK_P, sizeof(CLERK_P));
        close(hd);
        }

    hd = open("dept.zzz", O_RDWR | O_BINARY, S_IREAD);
    if(hd >= 0)
        {
        read(hd, dept, sizeof(dept));
        close(hd);
	}

    hd = open("plu.zzz", O_RDWR | O_BINARY, S_IREAD);
    if(hd >= 0)
        {
        read(hd, plu, sizeof(plu));
        close(hd);
        }

    hd = open("funckey.zzz", O_RDWR | O_BINARY, S_IREAD);
    if(hd >= 0)
        {
        read(hd, FUNCKEY, sizeof(FUNCKEY));
	close(hd);
        }

    hd = open("tax.zzz", O_RDWR | O_BINARY, S_IREAD);
    if(hd >= 0)
        {
        read(hd, tax_table, sizeof(tax_table));
        close(hd);
        }

    hd = open("sysopt.zzz", O_RDWR | O_BINARY, S_IREAD);
    if(hd >= 0)
        {
	read(hd, &SYS_OPT, sizeof(SYS_OPT));
        close(hd);
        }

    hd = open("prtopt.zzz", O_RDWR | O_BINARY, S_IREAD);
    if(hd >= 0)
        {
        read(hd, &PRT_OPT, sizeof(PRT_OPT));
        close(hd);
        }
}

void modescan()
{
    UBYTE key_in;
    int i;

    if(!kbhit())
        return;
    switch(getch())
        {
        case 0:
            switch(getch())
                {
                case 0x2c:             /* Alt-Z */
                    flg_key_pend = 0x7f;
		    return;
                case 0x2d:             /* Alt-X */
                    fclose(fp);
                    close_port();
                    ShowCursor();
                    exit();
                case 0x3b:             /* F1 */
                    mode_id = VMODE;
                    break;
                case 0x3c:             /* F2 */
                    mode_id = OMODE;
                    break;
                case 0x3d:             /* F3 */
		    mode_id = RMODE;
                    break;
                case 0x3e:             /* F4 */
                    mode_id = XMODE;
                    break;
                case 0x3f:             /* F5 */
                    mode_id = ZMODE;
                    break;
                case 0x40:             /* F6 */
                    mode_id = PMODE;
                    break;
                case 0x41:             /* F7 */
                    mode_id = MMODE;
		    break;
                case 0x43:             /* F9 */
                    save_mem();
                    return;
                case 0x44:             /* F10 */
                    load_mem();
                    return;
                }
            return;
        case 0x1b:
            return;
        case 'f':
        case 'F':
	    key_in = ONE;
	    break;
        case 'g':
        case 'G':
            key_in = TWO;
            break;
        case 'h':
        case 'H':
            key_in = THREE;
            break;
        case 'r':
        case 'R':
            key_in = FOUR;
	    break;
        case 't':
        case 'T':
            key_in = FIVE;
            break;
        case 'y':
        case 'Y':
            key_in = SIX;
	    break;
        case '4':
            key_in = SEVEN;
            break;
        case '5':
	    key_in = EIGHT;
            break;
        case '6':
            key_in = NINE;
            break;
        case 'v':
        case 'V':
            key_in = ZERO;
            break;
        case 'b':
        case 'B':
            key_in = DZERO;
            break;
	case 'n':
        case 'N':
            key_in = DECIMAL;
            break;
        case '1':                       /* Paper Feed */
            key_in = 0xff;
            break;
        case '2':                       /* Help Screen */
            key_in = 0x57;
            break;
        case '3':                       /* PLU */
            key_in = 0x02;
            break;
	case 'q':                       /* No Sale */
        case 'Q':
            key_in = 0x44;
            break;
        case 'w':                       /* Cancel */
        case 'W':
            key_in = 0x27;
            break;
        case 'e':                       /* Void Item */
        case 'E':
            key_in = 0x52;
            break;
        case 'a':                       /* Tax Shift */
	case 'A':
            key_in = 0x47;
            break;
        case 's':                       /* % */
        case 'S':
            key_in = 0x17;
            break;
        case 'd':                       /* X/Time */
        case 'D':
            key_in = 0x42;
            break;
        case 'z':                       /* Menu */
        case 'Z':
	    key_in = 0x04;
            break;
        case 'x':                       /* Clerk */
        case 'X':
            key_in = 0x07;
            break;
        case 'c':                       /* Clear */
        case 'C':
            key_in = 0x37;
            break;
        case '7':                       /* 4 */
            key_in = 0x01;
            break;
	case '8':                       /* 8 */
            key_in = 0x06;
            break;
        case '9':                       /* 12 */
            key_in = 0x20;
            break;
        case 'u':                       /* 3 */
        case 'U':
            key_in = 0x11;
            break;
        case 'i':                       /* 7 */
        case 'I':
            key_in = 0x16;
	    break;
        case 'o':                       /* 11 */
        case 'O':
            key_in = 0x30;
            break;
        case 'j':                       /* 2 */
        case 'J':
            key_in = 0x21;
            break;
        case 'k':                       /* 6 */
        case 'K':
            key_in = 0x26;
            break;
	case 'l':                       /* 10 */
        case 'L':
            key_in = 0x12;
            break;
        case 'm':                       /* 1 */
        case 'M':
            key_in = 0x31;
            break;
        case ',':                       /* 5 */
            key_in = 0x36;
            break;
        case '.':                       /* 9 */
            key_in = 0x50;
	    break;
        case '0':                       /* Dept Shift */
            key_in = 0x10;
            break;
        case '-':                       /* Page Up */
            key_in = 0x00;
            break;
        case 'p':                       /* Yes/No */
        case 'P':
            key_in = 0x22;
            break;
        case '[':                       /* Page Down */
            key_in = 0x32;
	    break;
        case ';':                       /* Misc. Tend */
            key_in = 0x40;
            break;
        case 0x27:                      /* Check Tend */
            key_in = 0x34;
            break;
        case '/':                       /* Cash */
            key_in = 0x24;
            break;

        default:
            return;
	}
    if(flg_key_pend)
        {
    	for(i=flg_key_pend;i>0;i--)
            flg_key_buf[i+1] = flg_key_buf[i];
        }
    flg_key_buf[1] = key_in;
    flg_key_pend++;
}

void testmscan()
{
}

void erroron()
{
}

void keyscan()
{
}

void feedkscan()
{
}

void feeding()
{
}

void feeding1()
{
	if(!r_cont)
		prn();
}

void rtc_read()                        /* OK */
{
   struct dosdate_t d;
   struct  time t;

   _dos_getdate(&d);
   gettime(&t);

   rtcb_flg[0] = t.ti_sec % 10;
   rtcb_flg[1] = t.ti_sec / 10;
   rtcb_flg[2] = t.ti_min % 10;
   rtcb_flg[3] = t.ti_min / 10;
   rtcb_flg[4] = t.ti_hour % 10;
   rtcb_flg[5] = t.ti_hour / 10;
   rtcb_flg[6] = d.dayofweek % 10;
   rtcb_flg[7] = d.day % 10;
   rtcb_flg[8] = d.day / 10;
   rtcb_flg[9] = d.month % 10;
   rtcb_flg[10] = d.month / 10;
   rtcb_flg[11] = d.year % 10;
   rtcb_flg[12] = (d.year / 10) % 10;
}

void rtc_write()
{
}

UBYTE t_conv[24] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
        'A', 'b', 'C', 'd', 'E', 'F', 'L', 'n', 'P', 'y','-', '=', ' ','u'};

void outdtx()                          /* OK */
{
    int i;

    window_turret();
    gotoxy(1,1);
    for(i=9;i>=0;i--)
        putch(t_conv[flg_dis_txtmp[i]]);
    window(1,1,80,25);
    gotoxy(1,1);
    textattr(0x07);
}

void inidtx()                          /* OK */
{
    int i;

    memset(flg_dis_txtmp, 22, 10);
    i = SYS_OPT.OPT18_1 + 1;
    memset(flg_dis_txtmp, 0, i);
}

void init_omode()
{
    memset(flg_dis_txtmp, 22, 10);
    memset(decp_buf, 0, 10);
    outdtx();
}

/* test1 */
void test1()
{
   flg_dis_txtmp[4]= 18;
   flg_dis_txtmp[3]= 13;
   outdtx();
}

void prtb_clr()
{
    memset(prt_buffer, 0x20, 40);
}

void cnbclr()
{
    memset(prt_buffer, 0x20, 26);
}

void prn()
{
    int i;

    while(1)
    {
      if(okbuf_bit)
        break;
      if((r_off != 1) && (SYS_OPT.OPT4_3 == 0))
        break;
      if((mode_id != RMODE) && (mode_id != VMODE))
      {
        if(mode_id != XMODE)
          break;
        if((regstep == 0) && (xoff_flg != 1))
          break;
      }
      if(notbuf_bit)
      {
        if(r_off != 1)
          break;
        cnbclr();
        return;
      }
      if(regstep == 0)
      {
        if(xoff_flg != 1)
          break;
      }
      memcpy(&stubbuf[26*buf_cnt], prt_buffer, 26);
      buf_cnt++;
      buft_cnt = buf_cnt;
      break;
    }
    window(2,1,28,25);
    textattr(0x70);
    gotoxy(1,py);
    for(i=0;i<26;i++)
        if(prt_buffer[i] == 0)
            prt_buffer[i] = 0x20;
    prt_buffer[26] = 0;
    cprintf("%s\n",prt_buffer);
    fprintf(fp,"%s\n",prt_buffer);
    if(py != 25)
        py++;
//    memset(numtxt,0x20,30);
    cnbclr();
    textattr(0x07);
}

void initky()                          /* OK */
{
    key_id = 0;
    zero_flg = 0;
    dcnt = 0;
    ncnt = 0;
    func = 0;
    nur = 0;
    pcode = 0;
    dnur = 0;
}

void initseq()                         /* OK */
{
    initky();
    taxs_bit = 0;
    twostep_id = 0;
    dptstp_id = 0;
    dptstp1_id = 0;
    scale_bit = 0;
    rstep_id = 0;
    pskp_flag = 0;
}

void loadseq()                         /* OK */
{
    rstep_id = rstepold_id;
    dptstp_id = dptsav_id;
    dptstp1_id = dptsav1_id;
    twostep_id = twosave_id;
    func = sfunc;
    pcode = spcode;
}

void saveseq()                         /* OK */
{
    dptsav_id = dptstp_id;
    dptsav1_id = dptstp1_id;
    twosave_id = twostep_id;
    sfunc = func;
    spcode = pcode;
}

void drawopn()
{
    char far *kptr;

    kptr = (char far *)0x00400017;
//    *kptr = *kptr | 0x10;
}

void pend_chk()
{
}

void sumchk()
{
    romsum_low = 0xcd;
    romsum_hig = 0xab;
}

void sep_long()
{
}

void com_long()
{
}

void sep_int()
{
}

void com_int()
{
}

void clr_ex0()
{
}

void set_ex0()
{
}

void sio_trans1()
{
}

void rflg_init()
{
    rend_flg = 0;
    data_s_end = 0;
    stx_flg = 0;
    dsave_flg = 0;
    etx_flg = 0;
    dle_flg = 0;
    ack_flg = 0;
    nack_flg = 0;
    s_in_flg = 1;
    comm_kind = 0;
    comm_err = 0;
}

void sio_trans()
{
    int i;

    s_out_flg = 0;
    tend_flg = 0;
    io_cnt = 0;
    for(i=0;i<trx_buf_cnt;i++)
        rsout(comm_buff[i]);
    while(1)
        {
        if(ack_flg)
            {
            comm_status = 0;
            return;
            }
        if(nack_flg)
            {
            comm_status = 1;
            return;
            }
        if(kbhit() && (getch() == 'c'))
            {
            rflg_init();
            return;
            }
        }
}

UBYTE rvd_vcheck()
{
    int i, sum=0;

    for(i=0;i<io_cnt;i++)
        sum += comm_buff[i];
    if((sum & 0x007f) != crc1_data)
        return 1;
    if(((sum >> 8) & 0x007f) != crc2_data)
        return 1;
    return 0;
}

void send_ack()
{
    rsout(DLE);
    rsout(ACK);
}

void send_nack()
{
    rsout(DLE);
    rsout(NACK);
}

void sio_rvlp()
{
    UBYTE ret;

    rend_flg = 0;
    rflg_init();
    s_in_flg = 1;
    io_cnt = 0;

    while(rend_flg != 2)
        {
        if(kbhit() && getch() == 'c')
            {
            flg_key_pend = 0;
            rflg_init();
            rend_flg = 3;
            return;
            }
        }
    s_in_flg = 0;
    ret = rvd_vcheck();
    if(ret != 1)
        {
        send_ack();
        comm_status = 0;
        }
    else
        {
        send_nack();
        comm_status = 1;
        }
    trx_buf_cnt = io_cnt;
    rflg_init();
}

void slip_trans()
{
    int i;

    for(i=0;i<trx_buf_cnt;i++)
        rsout(comm_buff[i]);
}

void modem_trans()
{
    int i;

    for(i=0;i<trx_buf_cnt;i++)
        rsout(comm_buff[i]);
}

void scale_trans()
{
    long timeout;

    comm_kind = 2;
    rend_flg = 0;
    ir1 = 0;

    rsout(0xd7);
    rsout(0x8d);

    for(timeout=0;timeout<0x1000000;timeout++)
        {
        if(rend_flg)
            return;
        }
    if(timeout >= 0x1000000)
        {
        err_bit = 1;
        comm_err = 9;
        }
}

void sp_trans452()
{
}

void sc_trans452()
{
}

void pc_trans452()
{
}

void fs_read()
{
    int i, hd;
    long addr;

    hd = open("fiscal.dat", O_RDWR | O_BINARY, S_IREAD);
    if(hd < 0)
        {
        hd = open("fiscal.dat", O_RDWR | O_BINARY | O_CREAT, S_IREAD);
        memset(bufbc, 0xff, 0x400);
        for(i=0;i<0x40;i++)
            write(hd, bufbc, 0x400);
        }

    addr = (long)high_add * 0x100 + (long)low_add;
    if(f1m_bit)
        addr += 0x10000;
    lseek(hd, addr, 0);
    read(hd, fs_t_buf, blk_time);
    close(hd);
}

void fst_write()
{
    int i, hd;
    long addr;

    hd = open("fiscal.dat", O_RDWR | O_BINARY, S_IREAD | S_IWRITE);
    if(hd < 0)
        {
        hd = open("fiscal.dat", O_RDWR | O_BINARY | O_CREAT, S_IREAD | S_IWRITE);
        memset(bufbc, 0xff, 0x400);
        for(i=0;i<0x40;i++)
            write(hd, bufbc, 0x400);
        }

    for(i=0;i<blk_time;i++)
        {
        addr = (long)high_add * 0x100 + (long)low_add + i;
        if(f1m_bit)
            addr += 0x10000;
        lseek(hd, addr, 0);
        read(hd, bufbc, 1);
        bufbc[0] &= fs_t_buf[i];
        lseek(hd, addr, 0);
        write(hd, bufbc, 1);
        }
    close(hd);
}

void write_0()
{
}

void read_0()
{
}

void write_1()
{
}

void read_1()
{
}

void init_dbg()
{
    int hd1, len;
    char bbbb[80];

    HideCursor();
    init_port();
    textattr(0x07);
    clrscr();
    textattr(0x0a);
    gotoxy(43,20);
    cprintf("ER-550 Simulation Program for PC");
    gotoxy(43,22);
    cprintf("    Programmed by Park KyeongRok");
    gotoxy(43,23);
    cprintf("                   July 25, 1996");
    gotoxy(29,19);
    cprintf("_____");
    py = 24;
    clr_lcd();
    window(1,1,28,25);
    textattr(0x70);
    clrscr();
    memset(numtxt,0x20,30);
    mode_id = MMODE;
    pfail_flg = 1;
    allramclr_bit = 1;
    fp = fopen("550prn.log","a");
    if(fp == NULL)
        exit();
    fprintf(fp,"\n\n========================================\n\n");

    hd1 = open("msg.bin", O_RDWR | O_BINARY | O_CREAT | O_TRUNC, S_IWRITE);
    if(hd1 >= 0)
        {
        write(hd1, (UBYTE *)&real_code, sizeof(real_code));
        close(hd1);
        }

    hd1 = open("m.bat", O_RDWR | O_BINARY, S_IWRITE);
    len = read(hd1, bbbb, 100);
    close(hd1);
    hd1 = open("mm.bat", O_RDWR | O_BINARY | O_CREAT | O_TRUNC, S_IWRITE);
    if(hd1 >= 0)
        {
        write(hd1, bbbb, len);
#ifdef SPECIAL_REP
#ifdef PLU70
        sprintf(bbbb, "copy er5.bin er5as.bin\n");
#endif
#ifdef PLU300
        sprintf(bbbb, "copy er5.bin er5bs.bin\n");
#endif
#ifdef PLU500
        sprintf(bbbb, "copy er5.bin er5cs.bin\n");
#endif
#else
#ifdef PLU70
        sprintf(bbbb, "copy er5.bin er5a.bin\n");
#endif
#ifdef PLU300
        sprintf(bbbb, "copy er5.bin er5b.bin\n");
#endif
#ifdef PLU500
        sprintf(bbbb, "copy er5.bin er5c.bin\n");
#endif
#endif
        write(hd1, bbbb, strlen(bbbb));
        close(hd1);
        }
}

void r232chk()
{
}

void test_chk()
{
}

void rd_clear()
{
}
