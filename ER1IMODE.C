#include <stdio.h>
#include <er1io51.h>
#include <er1cdef.h>
#include <er1exmpx.h>
#ifndef BCDBG
#include  <exs03.h>
#else                                  /* BCDBG */
#include  <exdbg.h>
#endif                                 /* BCDBG */

extern void set_dtm();
extern void delay();
extern void des_prn();
extern void mkline();
extern void logo_only(char type);
extern void endlogo();
extern void mkdeach(char type);
extern void pmemcpy(unsigned char *dest, unsigned char *src, unsigned int len);
extern void dsp_str(UBYTE x, UBYTE y, unsigned char *str);
extern void rep_sub(int);
extern void llong_add();

/**********************************************************/
/***                                                    ***/
/***            PC - ECR TRANSMIT  ROUTINE              ***/
/***                   Roggy Park                       ***/
/***                                                    ***/
/**********************************************************/
void comm_trans(unsigned char pnt)
{
    int bcc_sum;
    char bccl_sum;
    char bcch_sum;
    int att;

    comm_buff[pnt++]=DLE;
    comm_buff[pnt++]=ETX;
    trx_buf_cnt=pnt+2;            /* ADD CRC */

    comm_buff[0]=DLE;
    comm_buff[1]=STX;
    comm_buff[2]=trx_buf_cnt-6;       /* data cnt  */
    comm_buff[3]=block_cnt;           /* block cnt */
    ionur=command;
    mkdeach(0);
    comm_buff[4]=eachbuf[3];  /* command   */
    comm_buff[5]=eachbuf[2];
    comm_buff[6]=eachbuf[1];
    comm_buff[7]=eachbuf[0];

    comm_buff[9]=st_rec%0x100;
    comm_buff[10]=st_rec/0x100;
    comm_buff[11]=end_rec%0x100;
    comm_buff[12]=end_rec/0x100;
    comm_buff[15]=t_zcnt%0x100;
    comm_buff[16]=(t_zcnt/0x100)%0x100;

    bcc_sum=0;bccl_sum=bcch_sum=0;
    for(att=2;att <= comm_buff[2]+1;att++)
        {
        bcc_sum+=comm_buff[att];
        if(bcc_sum>=256) {bcc_sum-=256;bcch_sum++;};
        }
    bccl_sum=(char)bcc_sum;
    comm_buff[pnt++]=(bccl_sum & 0x7f); /* crc 1 */
    comm_buff[pnt++]=(bcch_sum & 0x7f); /* crc 2 */

    comm_status=0;

    sio_trans();
    delay();
    if (comm_status == COMM_FAIL) logo_only(50);
}

void set_modem()
{
    trx_buf_cnt = 0;
    comm_buff[trx_buf_cnt++] = 'A';
    comm_buff[trx_buf_cnt++] = 'T';
    comm_buff[trx_buf_cnt++] = 'Z';
    comm_buff[trx_buf_cnt++] = '\r';
    comm_buff[trx_buf_cnt++] = '\n';
    comm_status=0;
    modem_trans();
    delay();
    delay();
    delay();

    trx_buf_cnt = 0;
    comm_buff[trx_buf_cnt++] = 'A';
    comm_buff[trx_buf_cnt++] = 'T';
    comm_buff[trx_buf_cnt++] = 'S';
    comm_buff[trx_buf_cnt++] = '0';
    comm_buff[trx_buf_cnt++] = '=';
    comm_buff[trx_buf_cnt++] = '1';
    comm_buff[trx_buf_cnt++] = '\r';
    comm_buff[trx_buf_cnt++] = '\n';
    comm_status=0;
    modem_trans();
    delay();
    delay();
    delay();
    delay();
}

void clr_modem()
{
    trx_buf_cnt = 0;
    comm_buff[trx_buf_cnt++] = '+';
    comm_buff[trx_buf_cnt++] = '+';
    comm_buff[trx_buf_cnt++] = '+';
    comm_status=0;
    modem_trans();
    delay();
    delay();
    delay();
    delay();

    trx_buf_cnt = 0;
    comm_buff[trx_buf_cnt++] = 'A';
    comm_buff[trx_buf_cnt++] = 'T';
    comm_buff[trx_buf_cnt++] = 'S';
    comm_buff[trx_buf_cnt++] = '0';
    comm_buff[trx_buf_cnt++] = '=';
    comm_buff[trx_buf_cnt++] = '0';
    comm_buff[trx_buf_cnt++] = '\r';
    comm_buff[trx_buf_cnt++] = '\n';
    comm_status=0;
    modem_trans();
    delay();
    delay();
    delay();
}

/**********************************************************/
/***                                                    ***/
/***            PC - ECR RECEIVE ROUTINE                ***/
/***                                                    ***/
/**********************************************************/
void head_read()
{
    data_cnt=comm_buff[0];             /* data counter */
    block_cnt=comm_buff[1];            /* block counter*/
    cmd_1=comm_buff[2];                /* comm type    */
    cmd_2=comm_buff[3];                /* comm kind 2  */
    cmd_4=comm_buff[4]*10+comm_buff[5];/* comm kind 1  */
    st_rec = comm_buff[7] + (int)comm_buff[8] * 0x100;
    end_rec = comm_buff[9] + (int)comm_buff[10] * 0x100;
    command=cmd_1*1000 + cmd_2*100 + cmd_4;
}

UBYTE make_ptr()
{
    switch(cmd_4)
        {
        case UD_PLU :
            ud_ptr = (UBYTE*)plu;
            rec_size = sizeof(S_PLU_PGM);
            rec_no = MAX_PLU;
            break;
        case UD_DEPT :
            ud_ptr = (UBYTE*)dept;
            rec_size = sizeof(S_DEPT_PGM);
            rec_no = MAX_DEPT;
            break;
        case UD_GROUP :
            ud_ptr = (UBYTE*)grp_desc[0];
            rec_size = MAX_GRP_DESC;
            rec_no = MAX_GROUP;
            break;
        case UD_SYS_OPT :
            ud_ptr = (UBYTE*)&SYS_OPT;
            rec_size = sizeof(S_SYS_OPT);
            rec_no = 1;
            break;
        case UD_PRT_OPT :
            ud_ptr = (UBYTE*)&PRT_OPT;
            rec_size = sizeof(S_PRT_OPT);
            rec_no = 1;
            break;
        case UD_FUNCKEY :
            ud_ptr = (UBYTE*)FUNCKEY;
            rec_size = sizeof(S_FUNCKEY);
            rec_no = MAX_FUNCKEY;
            break;
        case UD_TAX_TBL :
            ud_ptr = (UBYTE*)tax_table;
            rec_size = sizeof(S_TAX_TBL);
            rec_no = MAX_TAX;
            break;
        case UD_CLERK :
            ud_ptr = (UBYTE*)CLERK_P;
            rec_size = sizeof(S_CLK_PGM);
            rec_no = MAX_CLERK;
            break;
        case UD_MESSDEC :
            ud_ptr = (UBYTE*)messdec[0];
            rec_size = MAX_MSG_DESC;
            rec_no = MAX_MSG;
            break;
        case UD_TARE :
            ud_ptr = (UBYTE*)tare_weight;
            rec_size = 2;
            rec_no = MAX_TARE;
            break;
        case UD_STP :
            ud_ptr = (UBYTE*)stock_p;
            rec_size = 4;
            rec_no = MAX_PLU;
            break;
        case UD_STD :
            ud_ptr = (UBYTE*)stock_d;
            rec_size = 4;
            rec_no = MAX_DEPT;
            break;
        case UD_DTM :
            ud_ptr = (UBYTE*)&dtm_buf;
            rec_size = sizeof(S_DTM_PGM);
            rec_no = 1;
            break;
        }
    if((st_rec > rec_no) || (end_rec > rec_no))
        return 1;
    ud_ptr += (rec_size * st_rec);
    return 0;
}

UBYTE make_rptr()
{
    nur=grand;                                 /* grand */
    rmtotlh=grandh;
    t_zcnt = 0;
    switch(cmd_4)
        {
        case REP_FIN :
            llong_add();
            ud_ptr = (UBYTE*)&rep;
            rec_size = sizeof(rep_z);
            rec_no = MAX_FIN;
            rep[USE_FIN].cnt = nur;
            rep[USE_FIN].total = rmtotlh;
            t_zcnt = zcnt + 1;
            break;
        case REP_DEPT :
            ud_ptr = (UBYTE*)&rep[d_base];
            rec_size = sizeof(rep_z);
            rec_no = MAX_DEPT;
            break;
        case REP_CLERK :
            ud_ptr = (UBYTE*)&rep[c_base];
            rec_size = sizeof(rep_z);
            rec_no = MAX_CLERK*MAX_CLKITEM;
            t_zcnt = zcnt_c + 1;
            break;
        case REP_TIME :
            ud_ptr = (UBYTE*)&rep[t_base];
            rec_size = sizeof(rep_z);
            rec_no = 25;
            t_zcnt = zcnt_t + 1;
            break;
        case REP_DAY :
            ud_ptr = (UBYTE*)&rep[da_base];
            rec_size = sizeof(rep_z);
            rec_no = 32;
            t_zcnt = zcnt_d + 1;
            break;
        case REP_GROUP :
            ud_ptr = (UBYTE*)&rep[g_base];
            rec_size = sizeof(rep_z);
            rec_no = MAX_GROUP+1;
            t_zcnt = zcnt_g + 1;
            break;
        case REP_PLU :
            ud_ptr = (UBYTE*)&rep[p_base];
            rec_size = sizeof(rep_z);
            rec_no = MAX_PLU+1;
            t_zcnt = zcnt_p + 1;
            break;
        case REP_FIN2 :
            ud_ptr = (UBYTE*)rep2;
            rec_size = sizeof(rep_z2);
            rep2[50].cnt = nur;
            rep2[50].totall = rmtotlh;
            rec_no = MAX_FIN;
            t_zcnt = zcnt2 + 1;
            break;
        case REP_STP  :
            ud_ptr = (UBYTE*)&stock_p[0];
            rec_size = 4;
            rec_no = MAX_PLU;
            t_zcnt = zcnt_sp + 1;
            break;
        case REP_STD  :
            ud_ptr = (UBYTE*)&stock_d[0];
            rec_size = 4;
            rec_no = MAX_DEPT;
            t_zcnt = zcnt_sd + 1;
            break;
        case REP_EJ   :
            ud_ptr = (UBYTE*)EJ_BUF[0];
            rec_size = MAX_RJ + 1;
            rec_no = EJ_INDEX;
            break;
        case REP_CIO  :
            ud_ptr = (UBYTE*)&CLKIO[0];
            rec_size = sizeof(S_CLKIO);
            rec_no = MAX_CLERK;
            t_zcnt = zcnt_ct + 1;
            break;
#ifdef SPECIAL_REP
        case REP_DEPT2:
            ud_ptr = (UBYTE*)&rep2[d_base];
            rec_size = sizeof(rep_z2);
            rec_no = MAX_DEPT;
            break;
#endif
        }
    if((st_rec > rec_no) || (end_rec > rec_no))
        return 1;
    ud_ptr += (rec_size * st_rec);
    return 0;
}

void pgm_up()
{
    int i, j, k, l;
#ifdef BCDBG
    int ll;
#endif

    if(make_ptr() != 0)
        {
        comm_status = COMM_FAIL;
        return;
        }
    i = MAX_CDATA / rec_size;          /* rec # in a packet */
    j = (rec_no - 1) / i + 1;          /* # of packet */

    l = i * rec_size;
    for(k=0;k<j;k++)
        {
#ifdef BCDBG
        for(ll=0;ll<0xfff;ll++)
#endif
            delay();
            delay();

        rflg_init();
        st_rec = k * i;
        if(make_ptr() != 0)
            {
            comm_status = COMM_FAIL;
            return;
            }
        if(k + 1 == j)
            {
            l = (rec_no - st_rec) * rec_size;
            end_rec = rec_no;
            }
        else
            end_rec = st_rec + i;
        pmemcpy(&comm_buff[DATA_USTART], ud_ptr, l);
        block_cnt = j - k;
        comm_trans((UBYTE)(DATA_USTART+l));
        if (comm_status == COMM_FAIL)
            break;
        }
}

void ej_fup()
{
    int i, j, k, l, m, n;
#ifdef BCDBG
    int ll;
#endif

    rec_size = MAX_RJ + 1;
    rec_no = MAX_EJLINE;
    m = EJ_INDEX;

    i = MAX_CDATA / rec_size;          /* rec # in a packet */
    j = (rec_no - 1) / i + 1;          /* # of packet */

    l = i * rec_size;
    for(k=0;k<j;k++)
        {
#ifdef BCDBG
        for(ll=0;ll<0xfff;ll++)
#endif
            delay();

        rflg_init();
        st_rec = k * i;
        if((st_rec > rec_no) || (end_rec > rec_no))
            {
            comm_status = COMM_FAIL;
            return;
            }
        if(k + 1 == j)
            {
            l = (rec_no - st_rec) * rec_size;
            end_rec = MAX_EJLINE;
            }
        else
            end_rec = st_rec + i;
        for(n=0;n<i;n++)
            {
            pmemcpy(&comm_buff[DATA_USTART+rec_size*n],
                    EJ_BUF[m], rec_size);
            m++;
            if(m >= MAX_EJLINE)
                m = 0;
            }
        block_cnt = j - k;
        comm_trans((UBYTE)(DATA_USTART+l));
        if (comm_status == COMM_FAIL)
            return;
        }
    ud_ptr = (UBYTE*)EJ_BUF[0];        /* 981114 */
    if(cmd_1 == REP_ZUP)
        {
        EJ_INDEX = 0;
        EJ_FULLF = 0;               //970925  981114
        st_rec = 0;
        for(i=0;i<MAX_EJLINE;i++)
            {
            memset(ud_ptr, 0, MAX_RJ+1);
            ud_ptr += (MAX_RJ + 1);
            }
        }
}

void ej_up()                        //970925
{
    int i, j, k, l;
#ifdef BCDBG
    int ll;
#endif

    if(EJ_FULLF)
        {
        ej_fup();
        return;
        }

    rec_size = MAX_RJ + 1;
    rec_no = EJ_INDEX;

    i = MAX_CDATA / rec_size;          /* rec # in a packet */
    if(rec_no)
        j = (rec_no - 1) / i + 1;          /* # of packet */
    else
        j = 1;

    l = i * rec_size;
    for(k=0;k<j;k++)
        {
#ifdef BCDBG
        for(ll=0;ll<0xfff;ll++)
#endif
            delay();

        rflg_init();
        st_rec = k * i;
        if((st_rec > rec_no) || (end_rec > rec_no))
            {
            comm_status = COMM_FAIL;
            return;
            }
        ud_ptr = (UBYTE*)EJ_BUF[0];
        ud_ptr += (rec_size * st_rec);
        if(k + 1 == j)
            {
            l = (rec_no - st_rec) * rec_size;
            end_rec = rec_no;
            }
        else
            end_rec = st_rec + i;
        pmemcpy(&comm_buff[DATA_USTART], ud_ptr, l);
        block_cnt = j - k;
        comm_trans((UBYTE)(DATA_USTART+l));
        if (comm_status == COMM_FAIL)
            return;
        }
    ud_ptr = (UBYTE*)EJ_BUF[0];        /* 981114 */
    if(cmd_1 == REP_ZUP)
        {
        EJ_INDEX = 0;
        EJ_FULLF = 0;               //970925  981114
        st_rec = 0;
        for(i=0;i<MAX_EJLINE;i++)
            {
            memset(ud_ptr, 0, MAX_RJ+1);
            ud_ptr += (MAX_RJ + 1);
            }
        }
}

void rep_up()
{
    int i, j, k, l;
#ifdef BCDBG
    int ll;
#endif

    if(cmd_4 == REP_EJ)
        {
        ej_up();
        return;
        }

    if(make_rptr() != 0)
        {
        comm_status = COMM_FAIL;
        return;
        }
    i = MAX_CDATA / rec_size;          /* rec # in a packet */
    if(rec_no)
        j = (rec_no - 1) / i + 1;          /* # of packet */
    else
        j = 1;

    l = i * rec_size;
    for(k=0;k<j;k++)
        {
#ifdef BCDBG
        for(ll=0;ll<0xfff;ll++)
#endif
            delay();

        rflg_init();
        st_rec = k * i;
        if(make_rptr() != 0)
            {
            comm_status = COMM_FAIL;
            return;
            }
        if(k + 1 == j)
            {
            l = (rec_no - st_rec) * rec_size;
            end_rec = rec_no;
            }
        else
            end_rec = st_rec + i;
        pmemcpy(&comm_buff[DATA_USTART], ud_ptr, l);
        block_cnt = j - k;
        comm_trans((UBYTE)(DATA_USTART+l));
        if (comm_status == COMM_FAIL)
            return;
        }
    if(cmd_1 == REP_ZUP)
        {
        if(cmd_4 == REP_FIN)
            {
            for(i=0;i<MAX_FIN;i++)
                {
                rep2[i].cnt +=rep[i].cnt;
                rep_sub(i);
                }
            nur=grand;                                 /* grand */
            rmtotlh=grandh;
            llong_add();
            grandh=rmtotlh;
            grand=nur;
            }
        else if(cmd_4 == REP_EJ)
            {
            EJ_INDEX = 0;
            EJ_FULLF = 1;               //970925
            }
        switch(cmd_4)
            {
            case REP_FIN : zcnt++;      break;
            case REP_CLERK : zcnt_c++;  break;
            case REP_TIME : zcnt_t++;   break;
            case REP_DAY : zcnt_d++;    break;
            case REP_GROUP : zcnt_g++;  break;
            case REP_PLU : zcnt_p++;    break;
            case REP_FIN2 : zcnt2++;    break;
            case REP_STP : zcnt_sp++;   break;
            case REP_STD : zcnt_sd++;   break;
            case REP_CIO : zcnt_ct++;   break;
            }
        st_rec = 0;
        make_rptr();
        for(i=0;i<rec_no;i++)
            {
            memset(ud_ptr, 0, rec_size);
            ud_ptr += rec_size;
            }
        }
}

void comm_sior(UBYTE st)
{
    if(st)
        {
        if (knur_bit) ERR;
        mkline();
        logo_only(49);
        mkline();
        alph = SYS_OPT.OPT13_1;
        SYS_OPT.OPT13_1 = 0;
        }

    clr_lcd();
    on_mode = 1;
    /* display Online logo */
    dsp_str(4,0,"ON-LINE MODE");
    dsp_str(0,7,"PUSH ESC TO EXIT");
    set_modem();

    while (1)
        {
        while(1)
            {
            SYS_OPT.OPT13_1 = 0;
            comm_status=0;
            sio_rvlp();
            if (rend_flg == 3) break;
            delay();
            head_read();

            if (cmd_1 == PGM_DOWN)
                {
                if(make_ptr() != 0)
                    {
                    comm_status = COMM_FAIL;
                    break;
                    }
                pmemcpy(ud_ptr, &comm_buff[DATA_DSTART], data_cnt - DATA_DSTART);
                if(cmd_4 == UD_SYS_OPT)
                    alph = SYS_OPT.OPT13_1;
                };

            if (block_cnt == 1 || comm_status == COMM_FAIL) break;
            }

        /* LINE disconnection */
        if (rend_flg == 3 || cmd_1 == COMM_OFF)
            {
            logo_only(52);
            break;
            };

//        if (comm_status == COMM_FAIL) {logo_only(51);continue;};
        if (comm_status == COMM_FAIL) {continue;};

        sprintf(prt_buffer,"= COMMAND : %d",(int)command);des_prn();

        if (cmd_1 == PGM_UP)
            pgm_up();
        else if ((cmd_1 == REP_UP) || (cmd_1 == REP_ZUP))
            rep_up();
        else if ((cmd_1 == PGM_DOWN) && (cmd_4 == UD_DTM))
            set_dtm();
        else if (cmd_1 != PGM_DOWN)
            {
            logo_only(51);
            break;
            };

        continue;
        }  /* while */

    clr_modem();
    /* display End logo */
    inidtx();
    flg_dis_txtmp[2]=14;flg_dis_txtmp[1]=17;
    flg_dis_txtmp[0]=13;
    outdtx();
    prn();
    on_mode = 0;
    SYS_OPT.OPT13_1 = alph;
    endlogo();
    return;
}
