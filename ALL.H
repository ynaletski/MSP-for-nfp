#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <dos.h>
#include <io.h>
#include <time.h>
#include <sys\types.h>
#include <sys\timeb.h>
#include"7188xa.h"

#define TimeStamp  *TimeTicks

int ComPortHost=4;
int ComPortICP=1;

int quit=0;

char  cmd[120];

int ilength=0;

int hour, minute, sec;
int year, month, day;

int week;
void CommHost();
void KeyBoard();
void DisplayMMI();
void DisplayClear();

unsigned char KeyBuf[50];

//long int timeouticp=0, erroricp=0;

int key= -1;
#define F1 31
#define F2 32
#define F3 33
#define ESC 34

#define Enter 55

#define i1 1
#define i2 2
#define i3 3
#define i4 4
#define i5 5
#define i6 6
#define i7 7
#define i8 8
#define i9 9
#define i0 0

#define SHT_F1 41
#define SHT_F2 42
#define SHT_F3 43
#define SHT_ESC 44

#define SHT_1 21
#define SHT_2 22
#define SHT_3 23
#define SHT_4 24
#define SHT_5 25
#define SHT_6 26
#define SHT_7 27
#define SHT_8 28
#define SHT_9 29
#define SHT_0 20

int display = 0;
int MMI_addr = 1;
int page_MMI = 2;
unsigned char dis_buf[120];

//void MmiPuts (char *str);
int proverka;
int str_dis=0;

char half_one[15];
char half_too[15];
int half_count=0;

float dens = 823.54;
float temp = 17.0;
float press = 0.;
float mass = 1000.;
float dens_15 = 0.;
float vol_15 = 0.;

char char_float[15];
char char_int[15];
int ch_fl_c=0;

#include "ref_t.h"
#include "ref_t.c"

float enter_f = -555;

void f_size();

#include "MD5.H"
#include "MD5C.C"
char sw_ver_nm[20] = "01  May 2020";

int com_4_vkl=0;