S_CODE_MEM real_code = {
   /* menu_str */
   {"0.PRINT REPORTS     ", /* Manager Mode*/
    "1.DISPLAY REPORTS   ",
    "2.PERFORM DECLARA.  ",
    "3.REG. PRINT FORMAT ",
    "4.STOP REG PRINTING ",
    "5.TRAINING MODE     ",
    "0.FINANCIAL         ", /*Print/Display Report Screen*/
    "1.TIME              ",
    "2.DAY               ",
    "3.PLU               ",
    "4.ALL CLERKS        ",
    "5.INDIVIDUAL CLERK  ",
    "6.GROUPS            ",
    "7.STOCK (PLU)       ",
    "8.STOCK (DEPT)      ",
    "9.CLERK TIME REPORT ",
    "00.CASH/CHECK TOTALS",
    "0.DAILY REPORTS     ",
    "1.PERIOD REPORT     ",
    "2.ELECTRONIC JOURNAL",
    "0.DAILY REPORTS     ",
    "1.PERIOD REPORT     ",
    "2.RESET E.J.        ",
    "3.PC COMMUNICATION  ",
    "0. DEPARTMENT       ", /*PGM Mode*/
    "1. PLU              ",
    "2. SALES TAX        ",
    "3. SYSTEM OPTION    ",
    "4. PRINT OPTION     ",
    "5. FUNCTION KEYS    ",
    "6. CLERK            ",
    "7. LOGO DESC.       ",
    "8. GROUP DESC       ",
    "9. TARE WEIGHT      ",
    "00. MORE            ",
    "0. CLERK I/O        ",
    "1. INVENTORY (PLU)  ",
    "2. INVENTORY (DEPT) ",
    "3. TIME & DATE      ",
    "4. PROGRAM SCAN     ",
    "5. ALL PGM SCAN     ",
    "0. HW TEST          ",
    "1. CLEAR ALL TOTALS ",
    "2. CLEAR GRAND TOTAL",
    "3. EPROM INFO.      ",
    "0. TEST PRINTER     ",
    "1. TEST DISPLAY     ",
    "2. TEST KEYBOARD    ",
    "3. TEST PORT        ",
    "4. TEST PRINTER,    ",
    "    DISPLAY, DRAWER ",
    "0. PRT ALL EJ       ",
    "1. PRT ONLY CASH    ",
    "2. PRT ONLY CHECK   ",
    "3. PRT ONLY MISC/T  ",
    "4. PRT ONLY %       ",
    "5. PRT ONLY RA/PO   ",
    "6. PRT ONLY RETURN  ",
    "7. PRT ONLY EC/VOID ",
    "8. PRT ONLY #/NS    ",
    "9. PRT ONLY CANCEL  ",
    "0. ALL CLERKS       ",
    "1. INDIVIDUAL CLERK ",
    },
   /* title_str */
   {"    MANAGER MODE    ", /*Title*/
    " PRINT REPORT page1 ",
    "DISPLAY REPORT page1",
    "RESET REPORTS page1 ",
    "    PROGRAM MODE    ",
    "    PROGRAM SCAN    ",
    " DECLARATION SCREEN ",
    "REG. PRINTING ON/OFF",
    " ENTER/EXIT TRAINING",
    " PROGRAM MODE page2 ",
    " PRINT REPORT page2 ",
    "DISPLAY REPORT page2",
    " PRINT REPORT page3 ",
    "DISPLAY REPORT page3",
    "    SERVICE MODE    ",
    "    HW TEST MODE    ",
    " ELECTRONIC JOURNAL ",
    " CLERK TIME REPORT  ",
    "RESET REPORTS page2 ",
    "REG. PRINTING FORMAT",
    "RESET ELECT. JOURNAL",
    "  CLEAR ALL TOTALS  ",
    " CLEAR GRAND TOTAL  ",
    "                    ",
    " CLERK TIME REPORT  "},
   /* xmenu_str */
   {" CASH           0.00", /* X mode 3 - 6 */
    " CHECK          0.00",
    "                    ",
    " TOTAL          0.00",

    " REGISTER PRINTING  ",
    "  IS CURRENTLY ON   ",
    "                    ",
    "    TO TURN OFF     ",
    "PRESS YES AND ENTER ",

    "REGIST. IS CURRENTLY",
    "  NOT IN TRAINING   ",
    " TO ENTER TRAINING, ",
    "ENTER 4 DIGIT PASSWD",
    "  AND PRESS ENTER   ",

    " REGISTER PRINTING  ",
    "  IS CURRENTLY OFF  ",
    "                    ",
    "     TO TURN ON     ",
    "PRESS YES AND ENTER ",

    "REGIST. IS CURRENTLY",
    "    IN TRAINING     ",
    " TO EXIT TRAINING,  ",
    "   ENTER 0000 AND   ",
    "    PRESS ENTER     ",

    "REGISTER PRINTING IS",
    " CURRENTLY RECEIPT  ",
    "                    ",
    " TO SET TO JOURNAL  ",
    "PRESS YES AND ENTER ",

    "REGISTER PRINTING IS",
    " CURRENTLY JOURNAL  ",
    "                    ",
    " TO SET TO RECEIPT  ",
    "PRESS YES AND ENTER ",

    "ARE YOU SURE?       ",
    "                NO  "},
   /* help_str */
   {" * VOID MODE HELP * ",            /* 0 */
    "                    ",
    "THIS MODE IS USED TO",
    " CORRECT SALES FROM ",
    "  DEPARTMENT'S AND  ",
    "PLU'S THAT WERE EN- ",
    " TERED INCORRECTLY. ",

    " * VOID MODE HELP * ",            /* 1 */
    "                    ",
    " ALL OR PART OF THE ",
    "    SALE CAN BE     ",
    " CORRECTED IN THIS  ",
    "       MODE.        ",
    "                    ",

    "*REGISTER MODE HELP*",            /* 2 */
    "                    ",
    "THIS MODE IS USED TO",
    "   ENTER SALES IN   ",
    "  DEPARTMENT'S AND  ",
    "       PLU'S.       ",
    "                    ",

    "*REGISTER MODE HELP*",            /* 3 */
    "                    ",
    "   THE COUNT AND    ",
    " AMOUNT IS TRACKED  ",
    "  FOR EACH ENTRY.   ",
    "                    ",
    "                    ",

    "* MANAGER MODE HELP*",            /* 4 */
    "                    ",
    "THIS MODE IS USED TO",
    " PERFORM FUNCTIONS  ",
    "  THAT ARE USUALLY  ",
    "    PERFORMED BY    ",
    "     A MANAGER.     ",

    "* MANAGER MODE HELP*",            /* 5 */
    "                    ",
    " THIS MODE IS ALSO  ",
    "  USED TO PRINT OR  ",
    "DISPLAY THE REPORTS ",
    " WITHOUT RESETTING  ",
    "     THE TOTALS.    ",

    " * PRINT/DISPLAY *  ",            /* 6 */
    "  * REPORT HELP *   ",
    "THIS SCREEN IS USED ",
    "TO PRINT THE REPORTS",
    "  THE REPORTS CAN   ",
    " ALSO BE VIEWED ON  ",
    "    THE DISPLAY.    ",

    "* DECLARATION HELP *",            /* 7 */
    "                    ",
    "IN THIS AREA YOU CAN",
    " DECLARE THE MONEY  ",
    "   IN THE DRAWER    ",
    "  BEFORE A REPORT   ",
    "       IS RUN.      ",

    "* DECLARATION HELP *",            /* 8 */
    "                    ",
    "   THESE ENTERED    ",
    "     TOTALS ARE     ",
    " COMPARED WITH THE  ",
    "   ACTUAL TOTALS.   ",
    "                    ",

    "  * REG. PRINTING * ",            /* 9 */
    "   * FORMAT HELP *  ",
    " IN THIS SCREEN YOU ",
    "   CAN CHANGE THE   ",
    "  PRINTING  FORMAT  ",
    "  FROM RECEIPT TO   ",
    "  JOURNAL OR BACK.  ",

    "    * STOP REG. *   ",            /* 10 */
    "  * PRINTING HELP * ",
    "                    ",
    " IN THIS SCREEN YOU ",
    "    CAN STOP ALL    ",
    "   REGISTER MODE    ",
    "      PRINTING.     ",

    "*TRAINING MODE HELP*",            /* 11 */
    "                    ",
    " IN THIS SCREEN YOU ",
    "CAN PUT THE REGISTER",
    " IN TRAINING MODE OR",
    " EXIT TRAINING MODE.",
    "                    ",

    "*TRAINING MODE HELP*",            /* 12 */
    "                    ",
    "  IN TRAINING MODE  ",
    "TOTALS WILL NOT ADD ",
    "TO THE NORMAL SALES ",
    "       TOTALS.      ",
    "                    ",

    "*ELECTRONIC JOURNAL*",            /* 13 */
    "      * HELP *      ",
    "   THE ELECTRONIC   ",
    " JOURNAL IS LIKE A  ",
    "  PRINTED JOURNAL   ",
    " THAT IS STORED IN  ",
    "     THE MEMORY.    ",

    "*ELECTRONIC JOURNAL*",            /* 14 */
    "      * HELP *      ",
    "   THE ELECTRONIC   ",
    "   JOURNAL CAN BE   ",
    "PRINTED AT ANY TIME ",
    "  TO SEE THE SALES  ",
    "      ACTIVITY.     ",

    "* FINANCIAL REPORT *",            /* 15 */
    "      * HELP *      ",
    "THE FINANCIAL REPORT",
    "CONTAINS THE TOTALS ",
    " NEEDED TO BALANCE  ",
    "    THE REGISTER.   ",
    "                    ",

    "* FINANCIAL REPORT *",            /* 16 */
    "      * HELP *      ",
    "THE FINANCIAL REPORT",
    "INCLUDES THE DEPART-",
    "MENTS TOTALS. WHICH ",
    " ARE PRINTED AT THE ",
    "     BEGINNING.     ",

    "* FINANCIAL REPORT *",            /* 17 */
    "      * HELP *      ",
    " BALANCE PROCEDURE  ",
    " FOR THE FINANCIAL  ",
    "  REPORT IS ON THE  ",
    "  FOLLOWING PAGES. ",
    "                    ",

    "* FINANCIAL REPORT *",            /* 18 */
    "      * HELP *      ",
    "ADJUSTED DEPT. TOTAL",
    "+   TAX COLLECTED   ",
    "+   ITEM DISCOUNTS  ",
    "=   NET SALES TOTAL ",
    "                    ",

    "* FINANCIAL REPORT *",            /* 19 */
    "      * HELP *      ",
    "NET SALES TOTAL     ",
    "+ ALL DISCOUNTS     ",
    "+ NEG. DEPARTMENTS  ",
    "+ CREDIT TAX TOTALS ",
    "                    ",

    "* FINANCIAL REPORT *",            /* 20 */
    "      * HELP *      ",
    "+  RETURN TOTALS    ",
    "+  ITEM VOID TOTALS ",
    "+  VOID MODE TOTALS ",
    "=  GROSS SALES TTL  ",
    "                    ",

    "* TIME REPORT HELP *",            /* 21 */
    "                    ",
    "  THE TIME REPORT   ",
    "  TRACKS SALES BY   ",
    " HOUR TIME PERIODS. ",
    "                    ",
    "                    ",

    "* PLU REPORT HELP * ",            /* 22 */
    "                    ",
    " THE PRICE LOOK UP  ",
    " REPORT TRACKS THE  ",
    " INDIVIDUAL TOTALS  ",
    "  FOR THE SPECIFIC  ",
    "    PLU NUMBERS.     ",

    "* CLERK REPORT HELP*",            /* 23 */
    "                    ",
    "  THE CLERK REPORT  ",
    "  WILL TRACK SALES  ",
    " FOR EACH SEPARATE  ",
    "       CLERK.       ",
    "                    ",

    " * CASH-IN-DRAWER * ",            /* 24 */
    "      * HELP *      ",
    "  THIS REPORT WILL  ",
    "   GIVE THE CASH    ",
    " AMOUNT THAT IS IN  ",
    "     THE DRAWER.    ",
    "                    ",

    "* CHECK-IN-DRAWER * ",            /* 25 */
    "      * HELP *      ",
    "  THIS REPORT WILL  ",
    "   GIVE THE CHECK   ",
    " AMOUNT THAT IS IN  ",
    "     THE DRAWER.    ",
    "                    ",

    "* GROUP REPORT HELP*",            /* 26 */
    "                    ",
    "  THE GROUP REPORT  ",
    "  WILL TRACK SALES  ",
    " FOR EACH SEPARATE  ",
    "       GROUP.       ",
    "                    ",

    "* CLERK TIME REPORT*",            /* 27 */
    "      * HELP *      ",
    "  THIS REPORT WILL  ",
    "GIVE THE BREAK DOWN ",
    " OF THE TIME WORKED ",
    "   FOR EACH CLERK.  ",
    "                    ",

    "* CLEAR TOTALS HELP*",            /* 28 */
    "                    ",
    "THIS MODE IS USED TO",
    "  PRINT AND RESET   ",
    "     REPORT AND     ",
    " ELECTRONIC JOURNAL ",
    "       TOTALS.      ",

    "* CLEAR TOTALS HELP*",            /* 29 */
    "                    ",
    "  ONCE A REPORT IS  ",
    " PRINTED THE TOTALS ",
    "FOR THAT REPORT ARE ",
    "      CLEARED.       ",
    "                    ",

    "* PROGRAM MODE HELP*",            /* 30 */
    "                    ",
    "  IN THIS MODE ALL  ",
    "  PROGRAMMING STEPS ",
    "   ARE PERFORMED.   ",
    "                    ",
    "                    ",

    "* DEPT.PROGRAM HELP*",            /* 31 */
    "                    ",
    "IN THESE SCREENS ARE",
    " ALL STEPS NEEDED TO",
    "    PROGRAM THE     ",
    "    DEPARTMENTS.    ",
    "                    ",

    "    * PLU HELP *    ",            /* 32 */
    "                    ",
    "IN THESE SCREENS ARE",
    " ALL STEPS NEEDED TO",
    "    PROGRAM THE     ",
    "       PLU'S.       ",
    "                    ",

    " * SALES TAX HELP * ",            /* 33 */
    "                    ",
    " IN THIS SECTION THE",
    "  SALES TAX IS PRO- ",
    " GRAMMED. EITHER A  ",
    " TABLE OR STRAIGHT %",
    " TAX CAN BE ENTERED.",

    "*SYSTEM OPTION HELP*",            /* 34 */
    "                    ",
    "IN THESE SCREENS ARE",
    " WHERE THE OPTIONS  ",
    "     ARE SET TO     ",
    " DETERMINE HOW THE  ",
    " REGISTER OPERTATES.",
              
    "* PRINT OPTION HELP*",            /* 35 */
    "                    ",
    "IN THESE SCREENS ARE",
    " WHERE THE OPTIONS  ", 
    "     ARE SET TO     ",
    " DETERMINE HOW THE  ",
    "  REGISTER PRINTS.  ",

    "* FUNCTION KEY HELP*",            /* 36 */
    "                    ",
    " IN THIS SECTION THE",
    " INDIVIDUAL FUNCTION",
    "      KEYS ARE      ",
    "     PROGRAMMED.    ",
    "                    ",

    "* FUNCTION KEY HELP*",            /* 37 */
    "                    ",
    " THESE ARE KEYS LIKE",
    "  CASH/TEND,CHECK   ",
    "      OR #/NS.      ",
    "                    ",
    "                    ",

    "   * CLERK HELP *   ",            /* 38 */
    "                    ",
    "  THIS IS WHERE THE ",
    "  CLERKS ARE GIVEN  ",
    "  SECRET CODES AND  ",
    "    UNIQUE NAMES.   ",
    "                    ",

    "    * LOGO HELP *   ",            /* 39 */
    " IN THIS SECTION UP ",
    "  TO 5 LINE PRINTED ",
    "  LOGO CAN BE SET.  ",
    "THIS LOGO WILL PRINT",
    " AT THE BEGINNING OF",
    "     EACH SALE.     ",

    "* GROUP DESC. HELP *",            /* 40 */
    "IN THIS SECTION SOME",
    "  OR ALL OF THE 20  ",
    " GROUPS CAN BE GIVEN",
    " UNIQUE NAMES. THIS ",
    " WILL MAKE IT EASIER",
    "  TO IDENTIFY THEM. ",

    "* TARE WEIGHT HELP *",            /* 41 */
    "                    ",
    " IN THIS SECTION UP ",
    " TO 5 TARE WEIGHTS  ",
    "   CAN BE PRESET.   ",
    "                    ",
    "                    ",

    "* TARE WEIGHT HELP *",            /* 42 */
    "                    ",
    "THIS TARE IS USUALLY",
    "  THE WEIGHT OF A   ",
    " CONTAINER THAT IS  ",
    "  SUBTRACTED FROM   ",
    " THE TOTAL WEIGHT.  ",

    " * CLERK I/O HELP * ",            /* 43 */
    "                    ",
    " IN THIS SECTION IS ",
    " WHERE THE TIME IN/ ",
    " OUTS CAN BE EDITED ",
    " FOR SOME OR ALL OF ",
    "   THE 20 CLERKS.   ",

    "*PLU INVENTORY HELP*",            /* 44 */
    "                    ",
    " IN THIS SECTION IS ",
    " WHERE THE INVENTORY",
    "  LEVELS ARE SET OR ",
    "  ADJUSTED FOR THE  ",
    "       PLU'S.       ",

    "DEPT. INVENTORY HELP",            /* 45 */
    "                    ",
    " IN THIS SECTION IS ",
    " WHERE THE INVENTORY",
    "  LEVELS ARE SET OR ",
    "  ADJUSTED FOR THE  ",
    "    DEPARTMENTS.    ",

    "*TIME AND DATE HELP*",            /* 46 */
    "                    ",
    " IN THIS SECTION IS ",
    " WHERE THE TIME OR  ",
    " DATE CAN BE SET OR ",
    "      CHANGED.      ",
    "                    ",

    "* PROGRAM SCAN HELP*",            /* 47 */
    "                    ",
    " IN THIS SECTION IS ",
    " WHERE THE PROGRAM  ",
    " SETTINGS FOR EACH  ",
    "    PART CAN BE     ",
    "SELECTED AND PRINTED",

    "* ALL PGM SCAN HELP*",            /* 48 */
    "                    ",
    " IN THIS SECTION IS ",
    " WHERE THE PROGRAM  ",
    "  SETING FOR ALL    ",
    " PARTS ARE PRINTED. ",
    "                    ",

    "  * SERVICE HELP *  ",            /* 49 */
    "                    ",
    "THIS MODE IS USED TO",
    " PERFORM FUNCTIONS  ",
    "  THAT ARE USUALLY  ",
    "  DONE BY A SEVICE  ",
    "    TECHNICIAN.     ",

    "* TEST PRINTER HELP*",            /* 50 */
    "                    ",
    " THIS SELECTION WILL",
    "  PRINT OUT A TEST  ",
    "   PATTERN ON THE   ",
    "      PRINTER.      ",
    "                    ",

    "* TEST DISPLAY HELP*",            /* 51 */
    "                    ",
    " THIS SELECTION WILL",
    "   DISPLAY A TEST   ",
    "   PATTERN ON THE   ",
    "  OPERATOR DISPLAY. ",
    "                    ",

    "* CLEAR TOTALS HELP*",            /* 52 */
    "                    ",
    " THIS SELECTION IS  ",
    " USED TO CLEAR ALL  ",
    "  TOTALS INCLUDING  ",
    "  THE GRAND TOTAL.  ",
    "                    ",

    "* CLEAR GRAND TOTAL*",            /* 53 */
    "      * HELP *      ",
    "                    ",
    "  THIS SELECTION IS ",
    "  USED TO CLEAR THE ",
    "  GRAND TOTAL ONLY. ",
    "                    ",

    "*EPROM DISPLAY HELP*",            /* 54 */
    "                    ",
    " THIS SELECTION WILL",
    "DISPLAY THE CHECKSUM",
    " DATE AND VERSION # ",
    "   FOR THE EPROM.   ",
    "                    ",

    },
   /* logo_str */
   {"- INACTIVE !         ",
    "   DESCRIPTOR SCAN   ",
    " MISCELLANEOUS SCAN  ",
    "   DEPARTMENT SCAN   ",
    "      PLU SCAN       ",
    "EUROPEAN ROUND :     ",
    "- NOT PROGRAMMED !   ",
    "NO SALES ------------",
    "RETURN **************",
    "ERROR CORRECT -------",
    "PREVIOUS VOID -------",
    "** CHECK CASHING **  ",
    "ALL CANCEL **********",
    " TIME CLERK REPORT   ",
    " ALL Z REPORT ISSUE  ",
    "ALL CLERKS           ",
    "OPEN CLERK           ",
    "* CASH  DECLARATION *",
    "FROM/TO PLU          ",
    "FROM/TO DEPT         ",
    "TIME                 ",
    "DAILY SALES          ",
    "GROUP                ",
    "IN-DRAWER            ",
    "ALL PLU              ",
    "FINANCIAL            ",
    "INDIVIDUAL CLERK     ",
    "INITIAL CLEAR !      ",
    "RESET ALL CNT/TOTAL !",
    "RESET GRAND TOTAL !  ",
    "RAM ALL CLEAR !      ",
    " ### POWER  FAIL ### ",
    "ALL PLU (STOCK)      ",
    "DEPARTMENT (STOCK)   ",
    "V0.90"VER_STR" JAN.12 1999 ",
    "* PC-ECR COMM. MODE *",
    "** TRANSMIT  ERROR **",
    "**  RECEIVE ERROR  **",
    "= LINE DISCONNECTION ", 
    "**   COMM. ERROR   **"},
   /* logo_strs */
   {"VOID MODE ****************",
    "ER-550:STD 01             ",
    "HHHHHHHHHHHHHHHHHHHHHHHHHH",
    "**************************",
    "--------------------------"},
   /* nur_str */
   {"DWR LIMIT AMT ",                  /* 0 */
    "CASH HALO     ",
    "CHECK TND HALO",
    "CHECK CNG HALO",
    " CNT -        ",
    " CNT +        ",                  /* 5 */
    " PRESET AMT   ",
    " HALO AMT     ",
    " LINKED DEPT  ",
    "DEPT SYSTEM   ",
    "SUBTOTAL      ",                  /* 10 */
    "FOREIGN AMT   ",
    "HOME AMT      ",
    "TAX AMT       ",
    " QTY          ",
    "TIME WORKED:  ",                  /* 15 */
    " SALES AMT    ",
    "TOTAL CNT     ",
    "TOTAL AMT     ",
    "TOTAL WORKED: ",
    "CASH DEC AMT  ",                  /* 20 */
    "CHK DEC AMT   ",
    "OVER/SHORT    ",
    "NON-ADD#      ",                  /* 23 */
    ""},
   /* pttl_str */
   {"     TAX PROG.      ",
    "  SET TIME & DATE   ",
    "   MESSAGE PROG.    ",
    "    CLERK NUMBER    ",
    " DEPARTMENT NUMBER  ",
    "     PLU NUMBER     ",
    "   #/NS KEY PROG.   ",
    "   CASH KEY PROG.   ",
    "  CHECK KEY PROG.   ",
    " ERR COR/VOID PROG. ",
    "  RETURN KEY PROG.  ",
    "  CANCEL KEY PROG.  ",
    "    PO KEY PROG.    ",
    "    RA KEY PROG.    ",
    "DEPT SHIFT KEY PROG.",
    "  OTHER ALPHA MENU  ",
    "  CLERK I/O PROG.   ",
    " GROUP DESC. PROG.  ",
    "  SCALE KEY PROG.   ",
    " TARE WEIGHT PROG.  "},
   /* sttl_str */
   {"** SYSTEM OPTION SCAN **",
    "** PRINT OPTION SCAN ***",
    "******* PLU SCAN *******",
    "****** DEPT. SCAN ******",
    "****** CLERK SCAN ******",
    "****** LOGO SCAN *******",
    "** FUNCTION KEY SCAN ***",
    "* TAX PROGRAMMING SCAN *",
    "*** GROUP DESC. SCAN ***",
    "*** TARE WEIGHT SCAN ***"},
   /* key_desc */
   {"CASH",
    "SUBTOTAL",
    "CHECK",
    "MISCTND 1",
    "MISCTND 2",
    "MISCTND 3",
    "MISCTND 4",
    "REC ON ACCT.",
    "PAID OUT",
    "EURO",                            /* 980605 */
    "CONV 2",
    "CONV 3",
    "CONV 4",
    "HELP",
    "PLU",
    "XTIME",
    "NOSALE",
    "NON-ADD#",
    "RETURN",
    "VOID",
    "ERR CORR",
    "CANCEL",
    "TAX",
    "% 1",
    "% 2",
    "% 3",
    "% 4",
    "DEPT SHIFT",
    "SCALE"},
   /* ERRMSG */
   {"       ERROR      ",

    "    CLERK CODE    ",
    "      ENTERED     ",
    "  IS NOT CORRECT  ",

    "     INVALID      ",
    "      ENTRY       ",

    " MANAGER REQUIRED ",
    "FOR THIS OPERATION",

    " CASH DECLARATION ",
    "    IS REQUIRED   ",
    "  BEFORE REPORTS  ",
    "    CAN BE RUN    ",

    "  AMOUNT TENDER   ",
    "   IS REQUIRED    ",
    "  BEFORE TENDER   ",

    "ENTRY HAS EXCEEDED",
    "   POUND AMOUNT   ",
    "     LOCKOUT      ",

    "       ITEM       ",
    "  IS NOT ACTIVE   ",

    "     FUNCTION     ",
    "  IS NOT ACTIVE   ",

    " WILL NOT ACCEPT  ",
    "    OPEN ENTRY    ",

    " WILL NOT ACCEPT  ",
    "   PRESET ENTRY   ",

    "    ITEM VOID     ",
    " CAN NOT BE DONE  ",

    "   TOTAL AMOUNT   ",
    " HAS EXCEEDED THE ",
    "       LIMIT      ",

    "  SPLIT PRINCING  ",
    "  CAN NOT BE DONE ",

    "  ENTRY DOES NOT  ",
    " MEET WITH OPTION ",
    "  OR OPTION HAS   ",
    " THE WRONG VALUE  ",

    "   NON-ADD# IS    ",
    "      NEEDED      ",

    "  ENTRY HAS THE   ",
    "  INVALID NUMBER  ",

    "   DRAWER TOTAL   ",
    " HAS EXCEEDED THE ",
    "   POUND AMOUNT   ",
    "     LOCKOUT      ",

    "     CASHIER     ",
    "     REQUIRED    ",

    "     CAN NOT     ",
    "     OVERRIDE    ",

    "   UNDER TENDER  ",
    "  IS NOT ALLOWED ",

    "  DRAWER SHOULD  ",
    "    BE CLOSED    ",

    "  CLERK TIME IN  ",
    "     IS FULL     ",  

    "ELETRONIC JOURNAL",
    "     IS FULL     ",

    "ELETRONIC JOURNAL",
    " IS FULL (STOP)  ",

    "    PERIPHERAL   ",
    " DOES NOT RESPOND",
    
    " SCALE OPERATION ",
    "   IS NOT VALID  ",

    "  TARE SHOULD BE ",
    "   INPUT BEFORE  ",
    " SCALE OPERATION ",

    "    TARE INPUT   ",
    "  IS NOT ALLOWED ",

    " SCALE OPERATION ",
    " CAN NOT BE DONE ",
    "    BY MANUAL    ",

    " SCALE OPERATION ",
    "  SHOULD BE DONE ",
    "BEFORE ITEM ENTRY",

    "     MODE KEY    ",
    "    SHOULD NOT   ",
    "     BE TURNED   ",
    
    "  NOT INVENTORY  ",
    "      ITEM       ",

    "   NOT ALLOWED   ",
    "  IN TRAIN MODE  "
    },
   /* finlogo */
   {"+DEPT TTL  ",       /* 0 */
    "-DEPT TTL  ",       /* 1 */
    "ADJST TTL  ",       /* 2 */
    "NON-TAX AMT",       /* 3 */     /* yoo start 1001 */
    "TAX 1 SALES",       /* 4 */
    "TAX 2 SALES",       /* 5 */
    "TAX 3 SALES",       /* 6 */
    "TAX 4 SALES",       /* 7 */
    "TAX1 AMT   ",       /* 8 */
    "TAX2 AMT   ",       /* 9 */
    "TAX3 AMT   ",       /* 10 */
    "TAX4 AMT   ",       /* 11 */
    "% 1        ",       /* 12 */
    "% 2        ",       /* 13 */
    "% 3        ",       /* 14 */
    "% 4        ",       /* 15 */
    "NET TOTAL  ",       /* 16 */   /* yoo end 1001 */
    "TAX1 CREDIT",       /* 17 */
    "TAX2 CREDIT",       /* 18 */
    "TAX3 CREDIT",       /* 19 */
    "TAX4 CREDIT",       /* 20 */
    "RTN        ",       /* 21 */
    "ERRCORR    ",       /* 22 */
    "PREV VD    ",       /* 23 */
    "MODE VD    ",       /* 24 */
    "CANCEL     ",       /* 25 */
    "GROSS TTL  ",       /* 26 */
    "CASH       ",       /* 27 */
    "CHECK      ",       /* 28 */
    "MISC 1 SALE",       /* 29 */
    "MISC 2 SALE",       /* 30 */
    "MISC 3 SALE",       /* 31 */
    "MISC 4 SALE",       /* 32 */
    "RECD ACCT  ",       /* 33 */
    "PAID OUT   ",       /* 34 */
    /*     "HASH AMT   ",     *//* 35 */
    "NPLU-PDPT  ",       /* 35 */
    "AUDACT     ",       /* 36 */
    "NOSALE     ",       /* 37 */
    "CASH-IN-D  ",       /* 38 */
    "CHECK-IN-D ",       /* 39 */
    "MISC1-IN-DR",       /* 40 */
    "MISC2-IN-DR",       /* 41 */
    "MISC3-IN-DR",       /* 42 */
    "MISC4-IN-DR",       /* 43 */
    "CONV1(CA   ",       /* 44 */
    "CONV1(CH   ",       /* 44  981219 */
    "CONV1(M1   ",       /* 44  981219 */
    "CONV1(M2   ",       /* 44  981219 */
    "CONV1(M3   ",       /* 44  981219 */
    "CONV1(M4   ",       /* 44  981219 */
    "CONV2(CA   ",       /* 45 */
    "CONV2(CH   ",       /* 44  981219 */
    "CONV2(M1   ",       /* 44  981219 */
    "CONV2(M2   ",       /* 44  981219 */
    "CONV2(M3   ",       /* 44  981219 */
    "CONV2(M4   ",       /* 44  981219 */
    "CONV3(CA   ",       /* 46 */
    "CONV3(CH   ",       /* 44  981219 */
    "CONV3(M1   ",       /* 44  981219 */
    "CONV3(M2   ",       /* 44  981219 */
    "CONV3(M3   ",       /* 44  981219 */
    "CONV3(M4   ",       /* 44  981219 */
    "CONV4(CA   ",       /* 47 */
    "CONV4(CH   ",       /* 44  981219 */
    "CONV4(M1   ",       /* 44  981219 */
    "CONV4(M2   ",       /* 44  981219 */
    "CONV4(M3   ",       /* 44  981219 */
    "CONV4(M4   ",       /* 44  981219 */
    "DRAWER TTL ",       /* 48 */
    "TRAIN TTL  "},      /* 49 */
   /* strb */
   {"                    ",              /* 000 */
    "BEEPER ACTIVE?      ",              /* 001 */
    "CLERK ENTRY         ",              /* 002 */
    " METHOD?            ",              /* 003 */
    " 0:PUSH 1:CODE      ",              /* 004 */
    "CLERK ASSIGNED WHEN ",              /* 005 */
    " CLERK KEY IS       ",              /* 006 */
    " PUSHED (1-20)      ",              /* 007 */
    "CLERK IS Y:POP-UP   ",              /* 008 */
    "     N:STAY-DOWN    ",              /* 009 */
    "DRAWER NEEDS TO BE  ",              /* 010 */
    " SHUT TO OPERATE    ",              /* 011 */
    "OPEN DRAWER ALARM   ",              /* 012 */
    "SECONDS TO ALLOW    ",              /* 013 */
    " DRAWER OPEN        ",              /* 014 */
    "OPEN DRAWER ON      ",              /* 015 */
    " POST TENDER        ",              /* 016 */
    "ALLOW MULTIPLE      ",              /* 017 */
    " RECEIPT            ",              /* 018 */
    "CASH-IN-DRAWER LIMIT",              /* 019 */
    " (0:NO LIMIT)       ",              /* 020 */
    "CASH DECLARATION REQ",              /* 021 */
    " BEFORE REPORTS     ",              /* 022 */
    "MGR CONTROL TO TEND.",              /* 023 */
    " NEGATIVE BALANCE   ",              /* 024 */
    " ZERO BALANCE       ",              /* 025 */
    "ALLOW POST TENDER   ",              /* 026 */
    "RESET TRANSACTION # ",              /* 027 */
    " ON Z REPORT        ",              /* 028 */
    "RESET GRAND TOTAL   ",              /* 029 */
    " AFTER Z REPORT     ",              /* 030 */
    "TRAINING PASSWORD   ",              /* 031 */
    " XXXX               ",              /* 032 */
    "ELEC. JOURNAL       ",              /* 033 */
    "SEND ONLY NEGATIVE  ",              /* 034 */
    " ENTRIES TO E.J.    ",              /* 035 */
    "SEND RESET REPORTS  ",              /* 036 */
    " TO E.J.            ",              /* 037 */
    "PROMPT OPERATOR WHEN",              /* 038 */
    " E.J. IS FULL       ",              /* 039 */
    "STOP OPERATIONS WHEN",              /* 040 */
    "OPEN DRAWER WHEN    ",              /* 041 */
    " REPORTS ARE RUN    ",              /* 042 */
    "DATE FORMAT IS      ",              /* 043 */
    " 0:MDY 1:DMY 2:YMD  ",              /* 044 */
    "DECIMAL PLACE       ",              /* 045 */
    "OPEN DRAWER DURING  ",              /* 046 */
    " TRAIN MODE         ",              /* 047 */
    "DISABLE DEPT        ",              /* 048 */
    " PRESET OVERRIDE    ",              /* 049 */
    "% AND TAX CAL.      ",              /* 050 */
    "SPLIT PRICE CAL.    ",              /* 051 */
    "CALCULATION CHART   ",              /* 052 */
    " 0:ROUND UP AT 0.50 ",              /* 053 */
    " 1:ROUND UP         ",              /* 054 */
    " 2:ROUND DOWN       ",              /* 055 */
    "PRINT MEDIA TOTALS  ",              /* 056 */
    " ON CLERK REPORT    ",              /* 057 */
    "PRINT TAX SYMBOL    ",              /* 058 */
    "PRINT VOID MODE AND ",              /* 059 */
    " RETURN ON REPORT   ",              /* 060 */
    "PRINT AUDACTION     ",              /* 061 */
    " ON REPORT          ",              /* 062 */
    "SKIP ZERO TOTALS ON ",              /* 063 */
    " FINANCIAL REPORT   ",              /* 064 */
    " CLERK REPORT       ",              /* 065 */
    "PRT CLERK REPORT    ",              /* 066 */
    " AFT FINANCIAL RPT  ",              /* 067 */
    "PRINT PLU WITH ZERO ",              /* 068 */
    " TOTALS ON REPORT   ",              /* 069 */
    "PRINT DEPT WITH ZERO",              /* 070 */
    "PRINT SUBTOTAL WHEN ",              /* 071 */
    " PRESSED            ",              /* 072 */
    "PRINT CONS. NO.     ",              /* 073 */
    "PRT SALE ITEM NO.   ",              /* 074 */
    "PRINT % OF SALES    ",              /* 075 */
    " ON DEPT. REPORT    ",              /* 076 */
    " ON PLU REPORT      ",              /* 077 */
    "PRINT DATE          ",              /* 078 */
    "PRINT TIME          ",              /* 079 */
    "MACHINE NO.         ",              /* 080 */
    " (0 : NO PRINT)     ",              /* 081 */
    "PRINT CLERK NAME    ",              /* 082 */
    "HOME CURRENCY SYM   ",              /* 083 */
    "PRINT GRAND TOTAL   ",              /* 084 */
    " ON X REPORT        ",              /* 085 */
    " ON Z REPORT        ",              /* 086 */
    "PRINT GROSS TOTAL   ",              /* 087 */
    "PRINT Z COUNTER     ",              /* 088 */
    "PRINT SUBTOTAL W/O  ",              /* 089 */
    " TAX                ",              /* 090 */
    "PRINT TAX AMOUNT    ",              /* 091 */
    "TAX AMOUNT IS       ",              /* 092 */
    " Y:COMBINE N:ITEMIZE",              /* 093 */
    "PRT TAXABLE TOTAL   ",              /* 094 */
    "PRINT TAX % RATE    ",              /* 095 */
    "PRINT NET SALE      ",              /* 096 */
    " AMOUNT (INCL. VAT) ",              /* 097 */
    "STOCK QUANTITY      ",              /* 098 */
    "PRINT TRAIN MODE    ",              /* 099 */
    " TITLE IN TRAIN MODE",              /* 100 */
    "CURRENCY SYMBOL     ",              /* 101 */
    " CONV. #1           ",              /* 102 */
    " CONV. #2           ",              /* 103 */
    " CONV. #3           ",              /* 104 */
    " CONV. #4           ",              /* 105 */
    "TAX NUMBER (1-4)    ",              /* 106 */
    "TAX TYPE (0-2)      ",              /* 107 */
    " 0 : ADD-ON         ",              /* 108 */
    " 1 : TAX TABLE      ",              /* 109 */
    " 2 : VAT            ",              /* 110 */
    "TAX RATE            ",              /* 111 */
    "FIRST TAX AMOUNT    ",              /* 112 */
    "NON-TAXable AMOUNT  ",              /* 113 */
    "# OF REPEAT BRK     ",              /* 114 */
    "# OF NON-REPEAT     ",              /* 115 */
    " BREAK              ",              /* 116 */
    "ENTER PLU NUMBER    ",              /* 117 */
    "AND PUSH PLU KEY    ",              /* 118 */
    "PUSH DEPT TO BE     ",              /* 119 */
    "PROGRAMMED.         ",              /* 120 */
    "USE DEPT. SHIFT     ",              /* 121 */
    "IF NEEDED           ",              /* 122 */
    "CLERK NO? (1-20)    ",              /* 123 */
    "DESC:               ",              /* 124 */
    "PRICE/HALO          ",              /* 125 */
    "LINK DEPT(1-24)     ",              /* 126 */
#ifdef SPECIAL_REP
#ifdef PLU500
    "LINK PLU(0-490)     ",              /* 127 */
#endif
#ifdef PLU300
    "LINK PLU(0-290)     ",              /* 127 */
#endif
#ifdef PLU70
    "LINK PLU(0-60)      ",              /* 127 */
#endif
#else
#ifdef PLU500
    "LINK PLU(0-500)     ",              /* 127 */
#endif
#ifdef PLU300
    "LINK PLU(0-300)     ",              /* 127 */
#endif
#ifdef PLU70
    "LINK PLU(0-70)      ",              /* 127 */
#endif
#endif
    "LINK GROUP(0-9)     ",              /* 128 */
    "DISABLE             ",              /* 129 */
    "PRESET              ",              /* 130 */
    "GALLONAGE ITEM      ",              /* 131 */
    "NON-ADD # COMP.     ",              /* 132 */
    "NEGATIVE ITEM       ",              /* 133 */
    "SINGLE ITEM         ",              /* 134 */
    "TAXable BY TAX1     ",              /* 135 */
    "TAXable BY TAX2     ",              /* 136 */
    "TAXable BY TAX3     ",              /* 137 */
    "TAXable BY TAX4     ",              /* 138 */
    "INVENTORY ITEM      ",              /* 139 */
    "SET TIME :    HH:MM ",              /* 140 */
    "SET DATE : MM.DD.YY ",              /* 141 */
    "NUMBER OF DEC.      ",              /* 142 */
    "RATE                ",              /* 143 */
    "PRESET:Y OPEN:N     ",              /* 144 */
    "SALE:Y ITEM:N       ",              /* 145 */
    "AMOUNT:Y %:N        ",              /* 146 */
    "OVERRIDEABLE        ",              /* 147 */
    "POS.:Y NEG.:N       ",              /* 148 */
    "NAME                ",              /* 149 */
    "PASSWORD            ",              /* 150 */
    "MESSAGE 1 :         ",              /* 151 */
    "MESSAGE 2 :         ",              /* 152 */
    "MESSAGE 3 :         ",              /* 153 */
    "MESSAGE 4 :         ",              /* 154 */
    "MESSAGE 5 :         ",              /* 155 */
    "KEY DISABLE         ",              /* 156 */
    "UNDER MGR CONTROL   ",              /* 157 */
    "KEY HALO            ",              /* 158 */
    "INHIBIT NO SALE     ",              /* 159 */
    " AFTER NON-ADD #    ",              /* 160 */
    "ENFORCE # ENTRY     ",              /* 161 */
    "INHIBIT PRINTING    ",              /* 162 */
    " ON NO SALE         ",              /* 163 */
    "KEY IS N:POP-UP     ",              /* 164 */
    "     Y:STAY-DOWN    ",              /* 165 */
    "AMOUNT TEND COMP.   ",              /* 166 */
    "OVER TENDER UNDER   ",              /* 167 */
    " MGR CONTROL        ",              /* 168 */
    "ALLOW UNDER TEND.   ",              /* 169 */
    "DOES DRAWER OPEN    ",              /* 170 */
    "EXEMPT TAX 1        ",              /* 171 */
    "EXEMPT TAX 2        ",              /* 172 */
    "EXEMPT TAX 3        ",              /* 173 */
    "EXEMPT TAX 4        ",              /* 174 */
    " 1. 0   7. %  13. - ",              /* 175 */
    " 2. 1   8. ^  14. _ ",              /* 176 */
    " 3. !   9. &  15. + ",              /* 177 */
    " 4. @  10. *  16. = ",              /* 178 */
    " 5. #  11. (  17. ` ",              /* 179 */
    " 6. $  12. )  18. [ ",              /* 180 */
    "19. ]  24. '  29. ? ",              /* 181 */
    "20. \\  25. <  30. / ",             /* 182 */
    "21. :  26. ,  31. œ ",              /* 183 */
    "22. ;  27. >  32. î ",              /* 184 */
    "23. \"  28. .        ",             /* 185 */
    "AMOUNT              ",              /* 186 */
    "GRP 0:              ",              /* 187 */
    "GRP 1:              ",              /* 188 */
    "GRP 2:              ",              /* 189 */
    "GRP 3:              ",              /* 190 */
    "GRP 4:              ",              /* 191 */
    "GRP 5:              ",              /* 192 */
    "GRP 6:              ",              /* 193 */
    "GRP 7:              ",              /* 194 */
    "GRP 8:              ",              /* 195 */
    "GRP 9:              ",              /* 196 */
    "GST IS TAXABLE BY   ",              /* 197 */
    "  RATE 1            ",              /* 198 */
    "  RATE 2            ",              /* 199 */
    "  RATE 3            ",              /* 200 */
    "SCALABLE            ",              /* 201 */
    "KEY IS MAN. ENTRY   ",              /* 202 */
    "INHIBIT TARE WEIGHT ",              /* 203 */
    "  ENTRY             ",              /* 204 */
    "TARE ENTRY IN X     ",              /* 205 */
    "TARE-WEIGHT COMP.   ",              /* 206 */
    "WEIGHT SYM FOR MAN. ",              /* 207 */
    " (N:lb Y:kg)        ",              /* 208 */
    "TARE 1              ",              /* 209 */
    "TARE 2              ",              /* 210 */
    "TARE 3              ",              /* 211 */
    "TARE 4              ",              /* 212 */
    "TARE 5              ",              /* 213 */
    "PLU SALES AFFECT    ",              /* 214 */
    " DEPT. ACTIVITY     ",              /* 215 */
    "ALLOW CHECK-CASH.   ",              /* 216 */
    "IN                  ",              /* 217 */
    "OUT                 ",              /* 218 */
    "AUTO SCALE          ",              /* 219 */
    "AUTO TARE (0-5)     ",              /* 220 */
    "DESC1:              ",              /* 221 */
    "DESC2:              ",              /* 222 */
    "PRINT LINK DEPT     ",              /* 223 */
    " IN PLU REPORT      ",              /* 224 */
    "INCLUDE VAT TAX     ",              /* 225 */
    " IN TAX AMT         ",              /* 226 */
    "ALLOW POUND ENTRY   ",              /* 227 */
    " W/O SCALE ON       ",              /* 228 */
    " SCALABLE ITEM      ",              /* 229 */
    "MANAGER REQUIRED    ",              /* 230 */
    " FOR TIME IN/OUT    ",              /* 231 */
    " (MILITARY)         ",              /* 232 */
    "SEND TO KITCHEN     ",              /* 233 */
    "PRINT RED ON KP     ",              /* 234 */
    "PORT IS  SCALE:0    ",              /* 235 */
#ifdef PLU70
    "         RJ:1 KP:2  ",              /* 236 */
#else
    " RJ:1 KP:2 LIQUOR:3 ",              /* 236 */
#endif
    "COMBINE SAME ITEM   ",              /* 237 */
    " ON KP              ",              /* 238 */
    "SEND TOTAL TO KP    ",              /* 239 */
    "INITIAL FEEDING LINE",              /* 240 */
    "ENDING FEEDING LINE ",              /* 241 */
    "SEND TO KP IN VOID  ",              /* 242 */
    " MODE               ",              /* 243 */
    "SEND TO KP IN TRAIN ",              /* 244 */
    "PRT KP ORDER # ON   ",              /* 245 */
    " RECEIPT            ",              /* 246 */
    "ECR ON TIME         ",              /* 247 */
    "PRINT RECEIPT WHEN  ",              /* 248 */
    " SIGN ON/OFF        ",              /* 249 */
    "LITTER ITEM         ",              /* 250 */
    "VOLUME UNIT         ",              /* 251 */
    "  N:GAL Y:LTR       ",              /* 252 */
    "                    ",              /* 253 */
    "                    ",              /* 254 */
    "PRT EURO TOTAL      ",              /* 255 980605*/
    "PRT EURO TEND       ",              /* 256 */
    "PRT EURO CHANGE     ",              /* 257 */
    "CURRENCY BASE IS    ",              /* 258 981024*/
    " N:HOME Y:EURO      ",              /* 259 981024*/
    "PRT FOREIGN AMT     ",              /* 260 981210 */
    "PRT HOME AMT        ",              /* 261 981210 */
    "PRT FOR BOTH CONV.  ",              /* 262 981210 */
    "  TOTAL             ",              /* 263 981210 */
    "  CHANGE            ",              /* 264 981210 */
    },
   /* clklogo */
   {"NET TOTAL  ",       /* 1 */   /* yoo start 1004 */
    "NON-TAX AMT",       /* 2 */
    "TAX 1 SALES",       /* 3 */
    "TAX 2 SALES",       /* 4 */
    "TAX 3 SALES",       /* 5 */
    "TAX 4 SALES",       /* 6 */
    "TAX1 AMT   ",       /* 7 */
    "TAX2 AMT   ",       /* 8 */
    "TAX3 AMT   ",       /* 9 */
    "TAX4 AMT   ",       /* 10 */
    "% 1        ",       /* 11 */
    "% 2        ",       /* 12 */
    "% 3        ",       /* 13 */
    "% 4        ",       /* 14 */
    "TAX1 CREDIT",       /* 15 */
    "TAX2 CREDIT",       /* 16 */
    "TAX3 CREDIT",       /* 17 */
    "TAX4 CREDIT",       /* 18 */
    "RTN        ",       /* 19 */
    "ERRCORR    ",       /* 20 */
    "PREV VD    ",       /* 21 */
    "MODE VD    ",       /* 22 */
    "CANCEL     ",       /* 23 */
    "RECD ACCT  ",       /* 24 */
    "PAID OUT   ",       /* 25 */
    "CASH-IN-D  ",       /* 26 */
    "CHECK-IN-D ",       /* 27 */
    "MISC1-IN-DR",       /* 28 */
    "MISC2-IN-DR",       /* 29 */
    "MISC3-IN-DR",       /* 30 */
    "MISC4-IN-DR",       /* 31 */
    "DRAWER TTL ",       /* 32 */
    "TRAIN TTL  ",       /* 33 */
    "NOSALE     "},      /* 34 */
   /* LOGMSG */
   {"CLERK LOGIN   ",
    "LOG IN TIME   ",
    "CLERK LOGOUT  ",
    "LOG OUT TIME  ",
    "CLERK TIME IN ",
    "IN  :         ",
    "CLERK TIME OUT",
    "OUT :         "}
};

