/*Второй .ехе файл для Систем учета отпуска нефтепродуктов
   состоит из двух страниц:
   1. проверка приведения плотности
   2. расчет MD5 для фторого файла в корневом сегменте (для входа в это меню необходимо нажать "F1")
   3. реализована выгрузка .exe файла при помощи программы VRFHost (для выгрузки необходимо включить 
    СОМ4 на передачу, для этого необходимо нажать "SHT_0" на клавиатуре ВРФ. СOM откроется с настройками 115200,8,N,1)*/

#include "ALL.h"

int MmiPuts(int x, int y, char *str)
{
    if (TimeStamp > 5)
    {
        if (strlen(str)>15)
        {
            strncpy(half_one, str, 15);
            strcpy(half_too, (str + 15));
            if(!half_count)
            {
                sprintf(dis_buf,"$%02XGS%02X%02X%s",MMI_addr,x,y*8,half_one);
                SendCmdTo7000(ComPortICP,dis_buf,1);                
                ReceiveResponseFrom7000_ms(ComPortICP,KeyBuf,1000,1);
                memset(KeyBuf, 0, sizeof(KeyBuf));
                memset(dis_buf, 0, sizeof(dis_buf)); 
                *(long int *)&(TimeStamp)=0;
                half_count = 1;
                //printCom(ComPortHost,"\n=>!");
                return 1;
            }
            else
            {
                sprintf(dis_buf,"$%02XGS%02X%02X%s",MMI_addr,x+15,y*8,half_too);
                SendCmdTo7000(ComPortICP,dis_buf,1);                
                ReceiveResponseFrom7000_ms(ComPortICP,KeyBuf,1000,1);
                memset(KeyBuf, 0, sizeof(KeyBuf));
                memset(dis_buf, 0, sizeof(dis_buf)); 
                *(long int *)&(TimeStamp)=0;
                str_dis++;
                half_count=0;
                return 1;
            }            
        }
        else
        {
            sprintf(dis_buf,"$%02XGS%02X%02X%s",MMI_addr,x,y*8,str);
            SendCmdTo7000(ComPortICP,dis_buf,1);                
            ReceiveResponseFrom7000_ms(ComPortICP,KeyBuf,1000,1);
            //printCom(ComPortHost,"\n=>%s",KeyBuf);
            memset(KeyBuf, 0, sizeof(KeyBuf));
            memset(dis_buf, 0, sizeof(dis_buf)); 
            *(long int *)&(TimeStamp)=0;
            str_dis++;
            return 1;
        }
    }
    return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////
char BufferMmiPrintf[128];
int  MmiPrintf(int x, int y, char *format , ...)
{
  va_list marker;
  va_start( marker, format);
  vsprintf(BufferMmiPrintf, format, marker);
  MmiPuts(x, y, BufferMmiPrintf);
  return (strlen(BufferMmiPrintf));
}
///////////////////////////////////////////////////////////////////////////////////////////
void EnterValue (float min, float max)
{
        enter_f = -555;
        if(key == ESC && strlen(char_float) == 0) {display = 0; str_dis = 0;}
        if(key == ESC && char_float) {memset(char_float, 0, sizeof(char_float)); MmiPrintf(7,3,"_       ");}
        if(key == i1 || key == i2 || key == i3 || key == i4 || key == i5 || key == i6 || key == i7 || key == i8
                || key == i9 || key == i0) 
        {
            if(strlen(char_float) < 8)
            {
                itoa(key,char_int,10);
                strcat(char_float,char_int);
                //printCom(ComPortHost,"\n=>%s",char_float);
                MmiPrintf(7,3,"%s       ", char_float);
            }
            else
            {
                itoa(key,char_int,10);
                char_float[7] = char_int[0]; 
                MmiPrintf(7,3,"%s", char_float);              
            }
        }
        if(key == SHT_7)
        {
            if(strlen(char_float) < 5)
            {
                strcat(char_float,".");
                MmiPrintf(7,3,"%s", char_float);
            }
        }
        if(key == SHT_4)
        {
            if(char_float > 0)
            {
                char_float[strlen(char_float)-1] = '\0'; 
                MmiPrintf(7,3,"%s ", char_float);
            }
        }
        if(key == Enter && char_float != 0)
        {
            float fff = atof (char_float);
            if(fff>(min) && fff<(max)) enter_f = fff;
            else enter_f = -555;
            display = 0; 
            str_dis = 0;
            memset(char_float, 0, sizeof(char_float));
        }
}
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
void main (void)
{
    InitLib();
    *(long int *)&(TimeStamp)=0;
    Print("\n");
    Print("=>");
    memset(cmd, 0, sizeof(cmd));

    //InstallCom(ComPortHost,115200L,8,0,1);
    InstallCom(ComPortICP,9600L,8,0,1);

    while(!quit)
    {
        if(com_4_vkl) CommHost();
        KeyBoard();
        DisplayMMI();
    }
    RestoreCom(ComPortHost);
    RestoreCom(ComPortICP);
}
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

void DisplayMMI()
{
    switch (display)
    {
    case 0:
        DisplayClear();
        display++;
        str_dis=0;
        break;
    case 1: 
        switch (str_dis) //формирует страницу
        {
                              /*   "---------------+++++++++++++++" */  // Размер строки не должен превышать это поле
            case 0:  MmiPuts(0,0,  "Пров-ка.приведения.плотности"); break;
            case 1:  MmiPuts(0,1,  " 1. Текущая плотность"); break;
            case 2:  MmiPuts(0,2,  " 2. Текущая температура"); break;
            case 3:  MmiPuts(0,3,  " 3. Текущее давление"); break;
            case 4:  MmiPuts(0,4,  " 4. Отпущенная масса"); break;
            case 5:  MmiPuts(0,5,  " 5. Тип нефтепродукта"); break;

            case 6:  MmiPrintf(0,7,  "Тек. плотность: %3.3f кг/м3", dens); break;
            case 7:  MmiPrintf(0,8,  "Тек. темпер-ра: %4.2f   С", temp); break;
            case 8:  MmiPrintf(0,9,  "Тек. давление : %3.3f   Мпа", press); break;
            case 9:  MmiPrintf(0,10, "Отпущен. масса: %3.2f кг", mass);
                     dens_15= f_get_ref_Dns(dens, temp , press, 15.);
                     vol_15= mass/dens_15; break;
            case 10: switch (type_liq)
                     {
                        case 0: MmiPuts(0,11,  "Нефтепродукт  : Crude Oils"); break;
                        case 1: MmiPuts(0,11,  "Нефтепродукт  : Crude Oils"); break;
                        case 2: MmiPuts(0,11,  "Нефтепродукт  : дизтопливо"); break;
                        case 3: MmiPuts(0,11,  "Нефтепродукт  : Jet  group"); break;
                        case 4: MmiPuts(0,11,  "Нефтепродукт  : Керосин"); break;
                        case 5: MmiPuts(0,11,  "Нефтепродукт  : Бензин"); break;
                        case 6: MmiPuts(0,11,  "Нефтепродукт  : Lubric. Oils"); break;                       
                     } 
                     break;
            case 11: MmiPrintf(0,13, "Плотность 15С : %3.3f кг/м3", dens_15); break;
            case 12: MmiPrintf(0,14, "Объем при 15С : %3.3f м3", vol_15); break;
            case 13: MmiPuts(0,15, "ESC  Возврат"); break;
            case 14: display++; str_dis=0; break;
        }
        break;
    case 2: 
        if(key == ESC) quit=1;
        if(key == i1) display = 3; //отобразит страницу ввода плотности и перейдет на display=4
        if(key == i2) display = 5; //отобразит страницу ввода температуры и перейдет на display=6
        if(key == i3) display = 7; //отобразит страницу ввода давления и перейдет на display=8
        if(key == i4) display = 9; //отобразит страницу ввода массы и перейдет на display=10
        if(key == F1) display = 11;//отобразит страницу MD5 начало, перейдет на display=12 и отобра-
                                            //зит страницу MD5 конец затем на display=13 для ожидания ESC
        if(key == i5) display = 14;//отобразит страницу ввода типа нефтепродукта и перейдет на display=15
        if(key == SHT_0) {com_4_vkl = 1; RestoreCom(ComPortHost); InstallCom(ComPortHost,115200L,8,0,1);}
        break;
    case 3: //плотность отображение
        switch (str_dis)
        {                    /*   "---------------++++++++++++++" */  // Размер строки не должен превышать это поле
            case 0: DisplayClear(); str_dis++; break;
            case 1: MmiPuts(0,1,  "Введите плотность кг/м3:"); break;
            case 2: MmiPrintf(7,3,"%4.3f", dens); break;
            case 3: MmiPuts(0,14, "'1...9,SHT-7'-Ввод,'SHT-4'-УД"); break;
            case 4: MmiPuts(0,15, "ESC  Возврат"); break;
            case 5: display++; str_dis=0; break;
        }
        break;
    case 4: //плотность ввод
        EnterValue(600,1100);
        if(enter_f > (-555)) dens = enter_f;
        break;
    case 5:  //температура отображение
        switch (str_dis)
        {                    /*   "---------------++++++++++++++" */  // Размер строки не должен превышать это поле
            case 0: DisplayClear(); str_dis++; break;
            case 1: MmiPuts(0,1,  "Введите температуру С:"); break;
            case 2: MmiPrintf(7,3,"%3.3f", temp); break;
            case 3: MmiPuts(0,14, "'1...9,SHT-7'-Ввод,'SHT-4'-УД"); break;
            case 4: MmiPuts(0,15, "ESC  Возврат"); break;
            case 5: display++; str_dis=0; break;
        }
        break;
    case 6:  //температура ввод
        EnterValue(-40,50);
        if(enter_f > (-555)) temp = enter_f;
        break;
    case 7:  //давление отображение
        switch (str_dis)
        {                    /*   "---------------++++++++++++++" */  // Размер строки не должен превышать это поле
            case 0: DisplayClear(); str_dis++; break;
            case 1: MmiPuts(0,1,  "Введите давление МПа:"); break;
            case 2: MmiPrintf(8,3,"%3.3f", press); break;
            case 3: MmiPuts(0,14, "'1...9,SHT-7'-Ввод,'SHT-4'-УД"); break;
            case 4: MmiPuts(0,15, "ESC  Возврат"); break;
            case 5: display++; str_dis=0; break;
        }
        break;
    case 8:  //давление ввод
        EnterValue(-0.01,1.6);
        if(enter_f > (-555)) press = enter_f; 
        break;
    case 9:  //масс отображение
        switch (str_dis)
        {                    /*   "---------------++++++++++++++" */  // Размер строки не должен превышать это поле
            case 0: DisplayClear(); str_dis++; break;
            case 1: MmiPuts(0,1,  "Введите отп. массу кг:"); break;
            case 2: MmiPrintf(8,3,"%3.3f", mass); break;
            case 3: MmiPuts(0,14, "'1...9,SHT-7'-Ввод,'SHT-4'-УД"); break;
            case 4: MmiPuts(0,15, "ESC  Возврат"); break;
            case 5: display++; str_dis=0; break;
        }
        break;
    case 10: //масса ввод
        EnterValue(0,3000);
        if(enter_f > (-555)) mass = enter_f; 
        break;
    case 11: //Страница MD5 начало
        switch (str_dis)
        {                   /*    "---------------++++++++++++++" */  // Размер строки не должен превышать это поле
            case 0: DisplayClear(); str_dis++; break;
            case 1: MmiPuts(0,0,  "    ООО Факом технолоджиз  ");break;
            case 2: MmiPrintf(0,2,"   Версия %s",sw_ver_nm);break;    
            case 3: MmiPuts(0,4,  "   MD5 идет расчет ...");break;
            case 4: MmiPuts(0,15, "         ESC - возврат в меню");break;
            case 5: f_md5(1); display++; str_dis=0; break;
        }
        break;
    case 12: //Страница MD5 конец
        if(fl_md_fst)
        {
            switch (str_dis)
            {
            case 0: MmiPrintf(3,4,"MD5 (%s,%ld) = ", filename,lgth_fl); break;
            case 1: MmiPrintf(6,6,"%02x%02x%02x%02x%02x%02x%02x%02x", digest[0],digest[1],digest[2],digest[3],digest[4],digest[5],digest[6],digest[7]); break;
            case 2: MmiPrintf(6,7,"%02x%02x%02x%02x%02x%02x%02x%02x", digest[8],digest[9],digest[10],digest[11],digest[12],digest[13],digest[14],digest[15]); break;
            case 3: display++; str_dis=0; break;
            }
        }
        break;
    case 13: //выход на главную страницу
        if(key == ESC) {display = 0; str_dis = 0;}
        break;
    case 14: //отображение тип нефтепродукта
        switch (str_dis)
        {                    /*   "---------------++++++++++++++" */  // Размер строки не должен превышать это поле
            case 0:  DisplayClear(); str_dis++; break;
            case 1:  MmiPuts(0,1,  "Введите тип.нефтепродукта:"); break;
            case 2:  MmiPrintf(8,3,"%d", type_liq); break;
            case 3:  MmiPuts(0,5,  " 0 - Crude Oils"); break;
            case 4:  MmiPuts(0,6,  " 1 - Crude Oils"); break;
            case 5:  MmiPuts(0,7,  " 2 - дизтопливо"); break;
            case 6:  MmiPuts(0,8,  " 3 - Jet  group"); break;
            case 7:  MmiPuts(0,9,  " 4 - Керосин"); break;
            case 8:  MmiPuts(0,10, " 5 - Бензин"); break;
            case 9:  MmiPuts(0,11, " 6 - Lubricating Oils"); break;
            case 10: MmiPuts(0,14, "'1...9,SHT-7'-Ввод,'SHT-4'-УД"); break;
            case 11: MmiPuts(0,15, "ESC  Возврат"); break;
            case 12: display++; str_dis=0; break;
        }
        break;
    case 15: //ввод тип нефтепродукта
        if(key == ESC && strlen(char_float) == 0) {display = 0; str_dis = 0;}
        if(key == ESC && char_float) {memset(char_float, 0, sizeof(char_float)); MmiPrintf(8,3,"_   ");}
        if(key == i1 || key == i2 || key == i3 || key == i4 || key == i5 || key == i6 || key == i7 || key == i8
                || key == i9 || key == i0) 
        {
            itoa(key,char_int,10);
            char_float[0] = char_int[0]; 
            char_float[1] = char_int[1];
            MmiPrintf(8,3,"%s", char_float);              
        }
        if(key == SHT_4)
        {
            if(char_float > 0)
            {
                char_float[strlen(char_float)-1] = '\0'; 
                MmiPrintf(8,3,"%s ", char_float);
            }
        }
        if(key == Enter && char_float != 0)
        {
            int iii = atoi (char_float);
            if(iii>(-1) && iii<7) type_liq = iii;
            display = 0; 
            str_dis = 0;
            memset(char_float, 0, sizeof(char_float));
        }
        break;
    }
}
///////////////////////////////////////////////////////////////////////////

void DisplayClear()
{
    sprintf(dis_buf,"$%02XP%02X",MMI_addr,page_MMI);
    SendCmdTo7000(ComPortICP,dis_buf,1);
    ReceiveResponseFrom7000_ms(ComPortICP,KeyBuf,1000,1);
    /*if(KeyBuf)
    {
        switch(KeyBuf[0])
	    {
			case '?':   erroricp++;
                        //printCom(ComPortHost,"\n=>%s  -!",KeyBuf);
                    break;
        }
        //printCom(ComPortHost,"\n=>%s  !",KeyBuf);
    }
    else
    {
        timeouticp++;
    }*/
    memset(dis_buf, 0, sizeof(dis_buf));
    memset(KeyBuf, 0, sizeof(KeyBuf));
    *(long int *)&(TimeStamp)=0;
}
///////////////////////////////////////////////////////////////////////////

void CommHost() 
{
    ilength=0;
        ilength=Receive_Data(ComPortHost,cmd,0x0D,5000);
        if(ilength>0)
        {
            if (ReadInitPin())    quit=1;
			if(!stricmp(cmd,"q")) quit=1;
		    if(!stricmp(cmd,"Q")) quit=1;
            if(!stricmp(cmd,"SIZE"))
            {
                f_size();
            }
            if(!stricmp(cmd,"MD5"))
            {
                f_md5(0);
            }
            if(!strncmp(cmd,"MDS ", 4))
            {
                int r1 = atoi(cmd+4);
                if(r1>-1 && r1<500)
                { 
                    count_mds=r1;
                    f_md5_sent(count_mds);
                }
            }
            memset(cmd, 0, sizeof(cmd));
		    cmd[0]=0x0A;
			cmd[1]='=';
			cmd[2]='>';
			ToComBufn(ComPortHost,cmd,3);
            //while(!IsCom4OutBufEmpty()) ;  /* Wait all message sent out of COM4 */
			memset(cmd, 0, sizeof(cmd));
        }
}
///////////////////////////////////////////////////////////////////////////

void KeyBoard()
{
    SendCmdTo7000(ComPortICP,"$01K",1);
    ReceiveResponseFrom7000_ms(ComPortICP,KeyBuf,100,1);
    if(KeyBuf)
    {
        switch(KeyBuf[0])
	    {
			//case '?': erroricp++; break; 
			case '!': if(strlen(KeyBuf)>6)
                        {
                            switch(KeyBuf[4])
                            {
                                case '0': switch(KeyBuf[5])
                                            {
                                                case '4': key = F1;break;
                                                case '5': key = F2;break;
                                                case '7': key = F3;break;
                                                case '6': key = ESC;break;
                                                case '2': key = Enter;break;
                                                case 'C': key = i1;break;
                                                case 'D': key = i2;break;
                                                case 'F': key = i3;break;
                                                case 'E': key = i4;break;
                                                case '8': key = i5;break;
                                                case '9': key = i6;break;
                                                case 'B': key = i7;break;
                                                case 'A': key = i8;break;
                                                case '1': key = i9;break;
                                                case '3': key = i0;break;
                                            };
                                break;
                                case '1': switch(KeyBuf[5])
                                            {
                                                case '4': key = SHT_F1;break;
                                                case '5': key = SHT_F2;break;
                                                case '7': key = SHT_F3;break;
                                                case '6': key = SHT_ESC;break;
                                                case 'C': key = SHT_1;break;
                                                case 'D': key = SHT_2;break;
                                                case 'F': key = SHT_3;break;
                                                case 'E': key = SHT_4;break;
                                                case '8': key = SHT_5;break;
                                                case '9': key = SHT_6;break;
                                                case 'B': key = SHT_7;break;
                                                case 'A': key = SHT_8;break;
                                                case '1': key = SHT_9;break;
                                                case '3': key = SHT_0;break;
                                            };
                                break;
                            }
                            if(display == 1)
                            {
                                if(key == i1) {display = 3; str_dis = 0; half_count = 0;}
                                if(key == i2) {display = 5; str_dis = 0; half_count = 0;}
                                if(key == i3) {display = 7; str_dis = 0; half_count = 0;}
                                if(key == i4) {display = 9; str_dis = 0; half_count = 0;}
                                if(key == i5) {display = 14; str_dis = 0; half_count = 0;}
                                if(key == F1) {display = 11; str_dis = 0; half_count = 0;}
                                if(key == ESC) {quit=1;}
                                if(key == SHT_0) {{com_4_vkl = 1; RestoreCom(ComPortHost); InstallCom(ComPortHost,115200L,8,0,1);}}
                                key = -1;
                            }
                        }
                        else
                        {
                            key = -1;
                        }
                        
            break;
        }
    }
    else 
    {
        //timeouticp++;
    }
    memset(KeyBuf, 0, sizeof(KeyBuf));
}
///////////////////////////////////////////////////////////////////////////

int Receive_Data(int iport, unsigned char* cinbuf, char cterminator, long itimeout)
	 {
	  unsigned char cchar;
	  int iindex=0;
	  unsigned long istarttime;
	  if(IsCom(iport))
	  	{
		 istarttime=*TimeTicks;
		 for(;;)
		    {
			 while(IsCom(iport))
			   {
				cchar=ReadCom(iport);
				if(cchar==0x08) 
					{
					if(iindex)
					     {
						  printCom(iport,"%c",cchar);
                          iindex--;
						 } 
					}
				else printCom(iport,"%c",cchar);
				if(cchar==cterminator)
				  {
				   cinbuf[iindex]=0;
				   return iindex+=1;
				  }
				else if(cchar!=0x08) cinbuf[iindex++]=cchar;
				istarttime=*TimeTicks;  
			   }
			 if((*TimeTicks-istarttime) >= itimeout) return -1;
			 //RefreshWDT();  
			}		
		 }
	  	 else return 0;
	 }