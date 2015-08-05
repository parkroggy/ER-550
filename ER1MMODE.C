#include <stdio.h>
#include <er1io51.h>
#include <er1exm.h>
#ifndef BCDBG
#include  <exs03.h>
#else                                  /* BCDBG */
#include  <exdbg.h>
#endif                                 /* BCDBG */

extern const UBYTE s_ttlreset[17];
extern const UBYTE s_gtreset[18];

const UBYTE s_first[7] = "First ";
const UBYTE s_second[7] = "Second";
const UBYTE s_success[15] = "  Success     ";

extern void ej_prn();
extern void sio_trans1();
extern void date_prn();
extern void delay();
extern void des_prn();
extern void dis9_out(char what);
//PKR0624 extern void drawopn();
extern void endlogo();
//PKR0624 extern void initseq();
//PKR0624 extern void inidtx();
extern void ini_outdtx();
extern void logo_only(char type);
extern void mkline();
extern void mkdnur(char inf);
extern void mkdeach(char type);
//PKR0624 extern void testmscan();
//PKR0624 extern void outdtx();
extern void p_init();
//PKR0624 extern void prn();
extern void prn_dsystem();
extern void test_kbbz();
extern void test_mode();
extern void time_prn();
extern void wait_pover();
extern void xlogo_nur(char type);
extern void dsp_str(UBYTE, UBYTE, UBYTE*);
extern void mode_dsp();
extern void mode_chg();
extern void dsp_long(long, UBYTE, UBYTE, UBYTE, UBYTE);
extern void mkstar();
extern void xmode_fun(int cnt);
extern void start_prn();
extern void start_menu(UBYTE cc);
extern void cmemcpy(UBYTE *, UBYTE *, UBYTE);
extern void scr_prt();

/* TEST */
//PKR0624 extern void fst_write();
//PKR0624 extern void fs_read();
/* PKR Temporary 
extern void read_clerk();*/
void read_clerk()
{
}

void wait_clear()
{
    UBYTE ret_val, old_mode=mode_id;

    while(1)
        {
#ifdef BCDBG
        modescan();
#endif
        if(mode_id != old_mode)
            break;
        if (flg_key_pend <= 0)
            continue;
        ret_val = flg_key_buf[flg_key_pend--];
        if(ret_val == CLEAR)
            break;
        else if(ret_val == RXTIME)
            scr_prt();
        }
}

void prn_sub()
{
    UBYTE i, j;

    memset(prt_buffer, 0x20, MAX_RJ);
    for(i=0;i<26;i++)
        {
        prt_buffer[0] = 'H';
        for(j=1;j<=i;j++)
            prt_buffer[j] = 'A' + j - 1;
        prn();
        }
#if 0
    for(i=0;i<6;i++)
        {
        for(j=0;j<16;j++)
            prt_buffer[j] = i*16 + j + 0x20;
        prn();
        }
#endif
    endlogo();
}

void tst_prn()
{
    UBYTE i;

    while(1)
        {
        prn_sub();
//        drawopn();
        delay();
#ifdef BCDBG
        modescan();
#endif
        if ( flg_key_pend > 0 )
            break;
        for(i=0;i<5;i++)
            feeding();
//            prn();
        }
}

void test_if()
{
    char i;

    clr_lcd();
    dsp_str(1,1,"Testing Port");
    for (i = 1;i < 20;i++)
        {
        sprintf(lcdbuf, "Port Test(%d)", i);
        dsp_str(1, 3, lcdbuf);
        tbuff[0] = i;
        trx_buf_cnt = 1;
        sio_trans1();
        if (rbuff[0] != i)
            {
            dsp_str(1, 3, "Port Error   ");
sprintf(lcdbuf, "%d %d", (int)i, (int)rbuff[0]);
dsp_str(1, 4, lcdbuf);
            wait_clear();
            return;
            }
        delay();
        }
    dsp_str(1, 3, "Port Test OK ");
    wait_clear();
}
#if 0
void wrt_rom2()
{
    blk_time = 10;
    high_add = 0;
    low_add = 0;
    fs_t_buf[0] = 0;
    fs_t_buf[1] = 1;
    fs_t_buf[2] = 2;
    fs_t_buf[3] = 4;
    fs_t_buf[4] = 8;
    fs_t_buf[5] = 0x10;
    fs_t_buf[6] = 0x20;
    fs_t_buf[7] = 0x40;
    fs_t_buf[8] = 0x80;
    fst_write();
}

void rd_rom2()
{
    UBYTE buf[21];

    blk_time = 10;
    high_add = 0;
    low_add = 0;
    fs_read();
    sprintf(buf, "%x, %x ", fs_t_buf[0], fs_t_buf[1]);
    dsp_str(1,1,buf);
    sprintf(buf, "%x, %x ", fs_t_buf[2], fs_t_buf[3]);
    dsp_str(1,2,buf);
    sprintf(buf, "%x, %x ", fs_t_buf[4], fs_t_buf[5]);
    dsp_str(1,3,buf);
    sprintf(buf, "%x, %x ", fs_t_buf[6], fs_t_buf[7]);
    dsp_str(1,4,buf);
    sprintf(buf, "%x, %x ", fs_t_buf[8], fs_t_buf[9]);
    dsp_str(1,5,buf);
    wait_clear();
}

void wrt_rom()
{
    UBYTE add_h, add_l, i, j, data_b, buf[21];

    blk_time = 32;
    for(i=0;i<1;i++)
        {
        if(i)
            {
            f1m_bit = 1;
            data_b = 0xaa;
            dsp_str(1,2,s_second);
            }
        else
            {
            f1m_bit = 0;
            data_b = 0x55;
            dsp_str(1,2,s_first);
            }
        add_h = 0;
        while(1)
            {
            j = 0;
            high_add = add_h;
            add_l = 0;
            sprintf(buf, "Writing to %x00",add_h);
            dsp_str(1,3,buf);
            while(1)
                {
                fs_t_buf[j++] = data_b;
                if(j == 32)
                    {
                    low_add = add_l - 31;
                    fst_write();
                    j = 0;
                    }
                data_b ^= 0xff;
                if(add_l == 0xff)
                    break;
                add_l++;
                }
            if(add_h == 0xff)
                break;
            add_h++;
            }
        }
}

int rd_rom()
{
    UBYTE add_h, add_l, i, j, data_b, buf[21];

    blk_time = 32;
    for(i=0;i<1;i++)
        {
        if(i)
            {
            f1m_bit = 1;
            data_b = 0xaa;
            dsp_str(1,2,s_second);
            }
        else
            {
            f1m_bit = 0;
            data_b = 0x55;
            dsp_str(1,2,s_first);
            }
        add_h = add_l = 0;
        while(1)
            {
            j = 0;
            high_add = add_h;
            sprintf(buf, "Reading at %x00",add_h);
            dsp_str(1,3,buf);
            for(add_l=0;add_l<8;add_l++)
                {
                low_add = add_l * 32;
                fs_read();
                for(j=0;j<32;j++)
                    {
                    if(fs_t_buf[j] != data_b)
                        {
                        sprintf(buf, "Read %x -> %x",fs_t_buf[j], data_b);
                        dsp_str(1,4,buf);
                        return -1;
                        }
                    data_b ^= 0xff;
                    }
                }
            if(add_h == 0xff)
                break;
            add_h++;
            }
        }
    dsp_str(1,3,s_success);
    return 0;
}
#endif
#if 0
void wrt_rom()
{
    blk_time = 1;
    f1m_bit = 0;
    high_add = 0xff;
    low_add = 0xfe;
    fs_t_buf[0] = 0x5a;
    fst_write();
}

void rd_rom()
{
    blk_time = 1;
    f1m_bit = 0;
    high_add = 0xff;
    low_add = 0xfe;
    fs_read();
    if(fs_t_buf[0] == 0x5a)
        dsp_str(1,3,s_success);
    else
        {
        dsp_str(1,3,"  Fail        ");
        sprintf(lcdbuf, "Read %x -> 5a",fs_t_buf[0]);
        dsp_str(1,4,lcdbuf);
        }
}

void tst_fiscal()
{
    wrt_rom();
    rd_rom();
    wait_clear();
}
#endif
void test_key()
{
    int sum;
    UBYTE ret_val, buf[21];

    sum = 0;
    clr_lcd();
    dsp_str(0,0,"Press All Keys once");
    dsp_str(2,1,"Except CLEAR Key");
    dsp_str(0,2,"And Press CLEAR Key");
    dsp_str(1,3,"Checksum should be");
    dsp_str(8,4,"065B");
    while(1)
        {
#ifdef BCDBG
        modescan();
#endif
        if (flg_key_pend <= 0)
            continue;
        ret_val = flg_key_buf[flg_key_pend--];
        if(ret_val == CLEAR)
            break;
        sum += ret_val;
        sprintf(buf, "The Key was %x", ret_val);
        dsp_str(1, 6, buf);
        }
    clr_lcd();
    dsp_str(3, 0, "KEYBOARD TEST");
    sprintf(buf, "The Sum is %x", sum);
    dsp_str(1, 6, buf);
    dsp_str(4, 7, "Press CLEAR Key");
    wait_clear();
}

void test_dsp()
{
    yyyyy_bit = 1;
    clr_lcd();

    yyyyy_bit = 0;
    wait_clear();
    clr_lcd();
    mode_dsp();
}

void test_pld()
{
    yyyyy_bit = 1;
    clr_lcd();
    memset(flg_dis_txtmp, 8, 10);
    outdtx();
    prn_sub();
    drawopn();
    inidtx();
    outdtx();
    yyyyy_bit = 0;
    clr_lcd();
}

#if 0
void test_pldl()
{
    UBYTE ret_val, old_mode=mode_id;

    while(1)
        {
        test_pld();
#ifdef BCDBG
        modescan();
#endif
        if(mode_id != old_mode)
            break;
        if (flg_key_pend <= 0)
            continue;
        ret_val = flg_key_buf[flg_key_pend--];
        if(ret_val == CLEAR)
            break;
        }
}

void wrt_ram(UBYTE ch)
{
    UBYTE *ptr;

//    dsp_str(1,1,"Writing 1");
//    memset((UBYTE*)dsp_buf[0], ch, 8 * 21 * 3);
//    dsp_str(1,1,"Writing 2");
//    memset((UBYTE*)&rep[0], ch, 13648);
//    dsp_str(1,1,"Writing 3");
//    memset((UBYTE*)comm_buff, ch, MAX_RTBUF);
//    dsp_str(1,1,"Writing 4");
//    memset((UBYTE*)comm_save, ch, MAX_CBUF);
//    dsp_str(1,1,"Writing 5");
//    memset((UBYTE*)rbuff, ch, 530);
//    dsp_str(1,1,"Writing 6");
//    memset((UBYTE*)&cancl[0], ch, 3500);
//    dsp_str(1,1,"Writing 7");
//    memset((UBYTE*)stubbuf, ch, MAX_STUB);
//    dsp_str(1,1,"Writing 8");
//    memset((UBYTE*)&dept[0], ch, 8216);

    ptr = (UBYTE*)0x019000;
    dsp_str(1,1,"Writing...");
    memset((UBYTE*)ptr, ch, 0x6000);
    mode_dsp();
}

void dead_run(UBYTE ch1, UBYTE ch2, UBYTE no, unsigned int id, UBYTE *ptr)
{
    sprintf(lcdbuf, "%x - %x : %x", ch1, ch2, no);
    dsp_str(1,1,lcdbuf);
    sprintf(lcdbuf, "   %x", id);
    dsp_str(1,2,lcdbuf);
    sprintf(lcdbuf,"%x %x %x %x",ptr[0], ptr[1], ptr[2], ptr[3]);
    dsp_str(0,3,lcdbuf);
    sprintf(lcdbuf,"%x %x %x %x",ptr[4], ptr[5], ptr[6], ptr[7]);
    dsp_str(0,4,lcdbuf);
    sprintf(lcdbuf,"%x %x %x %x",ptr[8], ptr[9], ptr[10], ptr[11]);
    dsp_str(0,5,lcdbuf);
    sprintf(lcdbuf,"%x %x %x %x",ptr[12], ptr[13], ptr[14], ptr[15]);
    dsp_str(0,6,lcdbuf);
    sprintf(lcdbuf,"%x %x %x %x",ptr[16], ptr[17], ptr[18], ptr[19]);
    dsp_str(0,7,lcdbuf);
    while(1)
        ;
}

UBYTE chk_ram(UBYTE *ptr, UBYTE ch, unsigned int len, UBYTE step)
{
    unsigned int i;

    for(i=0;i<len;i++)
        {
        if(ptr[i] != ch)
            dead_run(ptr[i], ch, step, i, &ptr[i]);
        }
    return 0;
}

void rd_ram(UBYTE ch)
{
    UBYTE *ptr;

//    dsp_str(1,1,"Reading 1");
//    chk_ram((UBYTE*)dsp_buf[0], ch, 8 * 21 * 3, 1);
//    dsp_str(1,1,"Reading 2");
//    chk_ram((UBYTE*)&rep[0], ch, 13648, 2);
//    dsp_str(1,1,"Reading 3");
//    chk_ram((UBYTE*)comm_buff, ch, MAX_RTBUF, 3);
//    dsp_str(1,1,"Reading 4");
//    chk_ram((UBYTE*)comm_save, ch, MAX_CBUF, 4);
//    dsp_str(1,1,"Reading 5");
//    chk_ram((UBYTE*)rbuff, ch, 530, 5);
//    dsp_str(1,1,"Reading 6");
//    chk_ram((UBYTE*)&cancl[0], ch, 3500, 6);
//    dsp_str(1,1,"Reading 7");
//    chk_ram((UBYTE*)stubbuf, ch, MAX_STUB, 7);
//    dsp_str(1,1,"Reading 8");
//    chk_ram((UBYTE*)&dept[0], ch, 8216, 8);

    ptr = (UBYTE*)0x019000;
    dsp_str(1,1,"Reading...");
    chk_ram((UBYTE*)ptr, ch, 0x6000, 10);
}

void h_pat()
{
    UBYTE i;

    for(i=0;i<26;i++)
        {
        memset(prt_buffer,'H',26);
        prn();
        }
}

void test_mmode()
{
    switch(nur)
        {
        case 101:
            test_pld();
            break;
        case 102:
            test_key();
            break;
        case 103:
            test_dsp();
            break;
        case 104:
            test_if();
            break;
        case 105:
            tst_fiscal();
            break;
        case 110:
            h_pat();
            break;
        case 111:
            tst_prn();
            break;
//#if 0
        case 120:
            wrt_ram(0);
            break;
        case 121:
            wrt_ram(0x55);
            break;
        case 122:
            wrt_ram(0xaa);
            break;
        case 123:
            wrt_ram(0xff);
            break;
        case 130:
            rd_ram(0);
            break;
        case 131:
            rd_ram(0x55);
            break;
        case 132:
            rd_ram(0xaa);
            break;
        case 133:
            rd_ram(0xff);
            break;
//#endif
#if 0
        case 112:
            wrt_rom2();
            rd_rom2();
            break;
#endif
        }
    clr_lcd();
    mode_dsp();
    nur = 0;
    dcnt = ncnt = 0;
    kdec_bit = 0;
}
#endif
UBYTE mk_16(char n)
{
    if (n >= 0x0a) return (n+0x37);
    else return(n+0x30);
}

void clr_ttl()
{
#ifndef BCDBG
    memset(&report_start, 0, (int)((long)&report_end - (long)&report_start));
#else
    memset(&report_end, 0, (int)((long)&report_start - (long)&report_end));
#endif
    start_prn();
    sprintf(prt_buffer, s_ttlreset);
    ej_prn();
    endlogo();
}

UBYTE mm_sub()
{
    if(mm_step == MM_CLRTTLS)
        clr_ttl();
    else if(mm_step == MM_CLRGTS)
        {
        grand = grandh = 0;
        start_prn();
        sprintf(prt_buffer, s_gtreset);
        ej_prn();
        endlogo();
        }
    else if(mm_step == MM_TEST)
        {
        switch(nur)
            {
            case 0:
                if(ncnt)
                    prn_sub();
                break;
            case 1:
                test_dsp();
                break;
            case 2:
                test_key();
                break;
            case 3:
                test_if();
                break;
            case 4:
                test_pld();
                break;
            case 9:                    /* 981014 */
                rd_clear();
                clr_lcd();
                if(io_cnt & 0x80)
                    dsp_str(0,5,"A/C Switch NG");
                else
                    dsp_str(0,5,"A/C Switch OK");
                wait_clear();
                break;
//            case 8:
//                delay();
//                delay();
//                delay();
//                while(1)
//                    {
//                    test_chk();
//                    prt_buffer[0] = 'H';
//                    prn();
//#ifdef BCDBG
//                    modescan();
//#endif
//                    if ( flg_key_pend > 0 )
//                        break;
//                    }
//                break;
//            case 9:
//                tst_prn();
//                break;
#if 0
            case 5:
                test_pldl();
                break;
#endif
            }
        start_menu(MENU_MTEST);
        return 0;
        }
    mm_step = 0;
    return 1;
}

void mk_chksum(UBYTE *buf)
{
    sumchk();
    sprintf(buf,"CHECK SUM :  ");
    buf[16] = mk_16(romsum_low & 0x0f);
    buf[15] = mk_16((romsum_low & 0xf0) >> 4);
    buf[14] = mk_16(romsum_hig & 0x0f);
    buf[13] = mk_16((romsum_hig & 0xf0) >> 4);
    buf[17] = 0;
}

void test_mmode()
{
    UBYTE renew = 1;

    if(mm_step)
        renew = mm_sub();
    else
        {
        switch(nur)
            {
            case 0:
                if(ncnt)
                    {
                    start_menu(MENU_MTEST);
                    renew = 0;
                    mm_step = MM_TEST;
                    }
                break;
            case 1:                        /* Clear Totals */
                xmode_fun(MENU_CLRTTL);
                renew = 0;
                break;
            case 2:                        /* Clear Grand Total */
                xmode_fun(MENU_CLRGT);
                renew = 0;
                break;
            case 3:                        /* Version & Checksum */
                clr_lcd();
                dsp_str(1,0,"ER-550 EPROM INFO.");
                cmemcpy(lcdbuf,code_mem->logo_str[34],20);
                dsp_str(0,3,lcdbuf);
                dsp_str(3,4,"WAIT....");
                mk_chksum(lcdbuf);
                dsp_str(0,4,lcdbuf);
                sprintf(lcdbuf, "PLU/EJ : %d/%d", MAX_PLU, MAX_EJLINE);
                dsp_str(0,5,lcdbuf);
                dsp_str(5,7,"PRESS CLEAR KEY");
                wait_clear();
                break;
#if 0
            case 5:
                while(1)
                    {
#ifdef BCDBG
                    modescan();
#endif
                    if (flg_key_pend > 0)
                        break;
                    r232chk();
                    if(none05)
                        {
                        dsp_str(0,0,"Set  ");
                        break;
                        }
                    else
                        dsp_str(0,0,"Clear");
                    if(none06)
                        {
                        dsp_str(0,1,"Set  ");
                        break;
                        }
                    else
                        dsp_str(0,1,"Clear");
                    }
                break;
#endif
            }
        }
    if(renew)
        mode_chg();
    nur = 0;
    dcnt = ncnt = 0;
    kdec_bit = 0;
}
