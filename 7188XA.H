#ifndef __MINIOS7__
#define __MINIOS7__

typedef unsigned int  uint;
typedef unsigned int  WORD;
typedef unsigned char uchar;
typedef unsigned char BYTE;
typedef unsigned long ulong;
typedef unsigned long DWORD;

#ifdef __TURBOC__
  #if (__TURBOC__ < 0x0300)
    #define inpw   inport
    #define outpw  outport
  #endif
#endif

#define    NoError	    0
#define    InitPinIsOpen    0
#define    InitPinIsNotopen 1
#define    QueueIsEmpty     0
#define    QueueIsNotEmpty  1
#define    PortError	   -1
#define    DataError	   -2
#define    ParityError	   -3
#define    StopError	   -4
#define    TimeOut	   -5
#define    QueueEmpty	   -6
#define    QueueOverflow   -7
#define    PosError	   -8
#define    AddrError	   -9
#define    BlockError	   -10
#define    WriteError	   -11
#define    SegmentError    -12
#define    BaudRateError   -13
#define    CheckSumError   -14
#define    ChannelError    -15
#define    BaudrateError   -16
#define    TriggerLevelError   -17
#define    DateError    -18
#define    TimeError    -19
#define    TimeIsUp        1

#ifdef __cplusplus
extern "C" {
#endif

/* FOR WDT */
void EnableWDT(void);
void DisableWDT(void);
void RefreshWDT(void);

/* FOR INIT* pin */
int ReadInitPin(void);

/* For SCLK pin */
void ClockHigh(void);
void ClockHighLow(void);
void ClockLow(void);

/* For red LED */
void LedOn(void);
void LedOff(void);
void LedToggle(void);

/* FOR 5* 7-segments LED */
extern unsigned char ShowData[19];
void pascal Show5DigitLed(int pos, int data);
void pascal Show5DigitLedWithDot(int pos, int data);
void Init5DigitLed(void);
void pascal Show5DigitLedSeg(int pos, unsigned char data);
void pascal Set5DigitLedTestMode(int mode);
void pascal Set5DigitLedIntensity(int mode);
void Disable5DigitLed(void);
void Enable5DigitLed(void);

/* For STDIO */
void Putch(int data);
void Puts(char *str);
int Getch(void);
int Gets(char *str);
int Kbhit(void);
int LineInput(char *buf,int maxlen);
void ResetScanBuffer(void);
void SetScanBuffer(unsigned char *buf,int len);
int Scanf(char *fmt, ...); /* for TC/BC only */
int Print(const char *fmt, ...);
int _Printf(const char *fmt, ...); /* for TC/BC only */
int UngetchI(int key);
int Ungetch(int key);

/* For RTC/NVRAM */
void GetTime(int *hour,int *minute,int *sec);
void GetDate(int *year,int *month,int *day);
int GetWeekDay(void);
int SetDate(int year,int month,int day);
int SetTime(int hour,int minute,int sec);
int ReadNVRAM(int addr);
int WriteNVRAM(int addr, int data);

/* for Timer */
extern const unsigned long far *TimeTicks;

/* For old version EEPROM functions compatible */
#define WriteEEP	EE_RandomWrite
#define ReadEEP		EE_RandomRead
#define EnableEEP	EE_WriteEnable
#define ProtectEEP	EE_WriteProtect

/* for EEPROM(24LC16/1024)*/
void EE_WriteProtect(void);
void EE_WriteEnable(void);
/* for 24LC16 use */
unsigned char EE_RandomRead(int Block,unsigned Addr);
unsigned char EE_ReadNext(int Block);
int EE_MultiRead(int StartBlock,unsigned StartAddr,int no,char *databuf);
int EE_RandomWrite(int Block,unsigned Addr,int Data);
int EE_MultiWrite(int Block,unsigned Addr,int no,char *Data);
int EE_MultiWrite_A(int Block,unsigned Addr,unsigned no,char *Data);
int EE_MultiWrite_A(int Block,unsigned Addr,unsigned no,char *Data);
int EE_MultiWrite_L(unsigned address,unsigned no,char *Data);
int EE_MultiRead_L(unsigned address,unsigned no,char *Data);

/* for 24LC1024 (only when 24LC16 is replaced by 24LC1024 can be used)*/
unsigned char EE1024_RandomRead(int Block,unsigned Addr);
unsigned char EE1024_ReadNext(int Block);
int EE1024_MultiRead(int StartBlock,unsigned StartAddr,int no,char *databuf);
int EE1024_RandomWrite(int Block,unsigned Addr,int Data);
int EE1024_MultiWrite(int Block,unsigned Addr,int no,char *Data);

/* for 24LC16 or 24LC1024 use, NEED call InitEEPROM() first.*/
extern int EepType; /* 1024:24LC1024,16:24LC16; */
extern int EepBlockOffset;
extern unsigned EepAddrOffset;
void InitEEPROM(void);
extern unsigned char (*EE1_RandomRead)(int Block,unsigned Addr);
extern unsigned char (*EE1_ReadNext)(int Block);
extern int (*EE1_MultiRead)(int StartBlock,unsigned StartAddr,int no,char *databuf);
extern int (*EE1_RandomWrite)(int Block,unsigned Addr,int Data);
extern int (*EE1_MultiWrite)(int Block,unsigned Addr,int no,char *Data);

/* for system */
extern unsigned long far *IntVect;
int IsMiniOS7(void);
#define Is7188xa	Is7188Xa
int Is7188Xa(void);
int IsResetByPowerOn(void);
int IsResetByWatchDogTimer(void);

/* for FLASH MEMORY */
int FlashReadId(void);
int FlashErase(unsigned int FlashSeg);
int FlashWrite(unsigned int seg, unsigned int offset, char data);

#define FlashRead FlashReadB
unsigned char FlashReadB(unsigned seg, unsigned offset);
unsigned FlashReadI(unsigned seg, unsigned offset);
unsigned long FlashReadL(unsigned seg, unsigned offset);
void far *_MK_FP_(unsigned s,unsigned off);

/* Timer functions */
int TimerOpen(void);
int TimerClose(void);
void TimerResetValue(void);
unsigned long TimerReadValue(void);
int StopWatchReset(int channel);
int StopWatchStart(int channel);
int StopWatchStop(int channel);
int StopWatchPause(int channel);
int StopWatchContinue(int channel);
int StopWatchReadValue(int channel,unsigned long *value);
int CountDownTimerStart(int channel,unsigned long count);
int CountDownTimerReadValue(int channel,unsigned long *value);
void InstallUserTimer(void (*fun)(void));
void InstallUserTimer1C(void (*fun)(void));

/* StopWatch [計時碼表] */

#ifndef _T_STOPWATCH_
#define _T_STOPWATCH_
typedef struct {
 ulong ulStart,ulPauseTime;
 uint  uMode;  /* 0: pause, 1:run(start) */
} STOPWATCH;
#endif

/* CountDown Timer[倒數計時] */
#ifndef _T_COUNTDOWNTIMER_
#define _T_COUNTDOWNTIMER_
typedef struct {
 ulong ulTime,ulStartTime,ulPauseTime;
 uint  uMode;  /* 0: pause, 1:run(start) */
} COUNTDOWNTIMER;
#endif

void T_StopWatchStart(STOPWATCH *sw);
ulong T_StopWatchGetTime(STOPWATCH *sw);
void T_StopWatchPause(STOPWATCH *sw);
void T_StopWatchContinue(STOPWATCH *sw);

void T_CountDownTimerStart(COUNTDOWNTIMER *cdt,ulong timems);
void T_CountDownTimerPause(COUNTDOWNTIMER *cdt);
void T_CountDownTimerContinue(COUNTDOWNTIMER *cdt);
int T_CountDownTimerIsTimeUp(COUNTDOWNTIMER *cdt);
ulong T_CountDownTimerGetTimeLeft(COUNTDOWNTIMER *cdt);

/* Timer functions II */
void T2_UpdateCurrentTimeTicks(void); /* every loop must call T2_UpdateCurrentTimeTicks() to get new time.*/
void T2_StopWatchStart(STOPWATCH *sw);
ulong T2_StopWatchGetTime(STOPWATCH *sw);
void T2_StopWatchPause(STOPWATCH *sw);
void T2_StopWatchContinue(STOPWATCH *sw);

void T2_CountDownTimerStart(COUNTDOWNTIMER *cdt,ulong timems);
void T2_CountDownTimerPause(COUNTDOWNTIMER *cdt);
void T2_CountDownTimerContinue(COUNTDOWNTIMER *cdt);
int T2_CountDownTimerIsTimeUp(COUNTDOWNTIMER *cdt);
ulong T2_CountDownTimerGetTimeLeft(COUNTDOWNTIMER *cdt);

extern const unsigned long far *TimeTicks;
void Delay(unsigned ms); /* delay unit is ms, use CPU Timer 1. */
void Delay_1(unsigned ms); /* delay unit is 0.1 ms ,use CPU Timer 1.*/
void Delay_2(unsigned ms); /* delay unit is 0.01 ms ,use CPU Timer 1.*/
void DelayMs(unsigned t);/* delay unit is ms, use system timeticks. */

/* for MiniOS7 FLASH file system */
#ifndef __FILE_DATA__
#define __FILE_DATA__
typedef struct  {
  unsigned mark;   /* 0x7188 -> is file */
  unsigned char fname[12];
  unsigned char year;
  unsigned char month;
  unsigned char day;
  unsigned char hour;
  unsigned char minute;
  unsigned char sec;
  unsigned long size;
  char far *addr;
  unsigned CRC;
  unsigned CRC32;
} FILE_DATA;
#endif

#ifndef _DISK_AB_
#define _DISK_AB_

typedef struct {
  unsigned sizeA:3;
  unsigned sizeB:3;
  unsigned sizeC:3;
  unsigned sum:7;
} SIZE_AB;
#endif

extern SIZE_AB SizeAB;
extern FILE_DATA far *fdata;

#define DISKA	0
#define DISKB	1

/* int GetFileNo(void); */
#define GetFileNo()	GetFileNo_AB(DISKA)

/* int GetFileName(int no,char *fname); */
#define GetFileName(no,fname)	GetFileName_AB(DISKA,no,fname)

/* FILE_DATA far * GetFileInfoByNo(int no) */
#define GetFileInfoByNo(no)	GetFileInfoByNo_AB(DISKA,no)

/* FILE_DATA far * GetFileInfoByName(char *fname) */
#define GetFileInfoByName(fname)	GetFileInfoByName_AB(DISKA,fname)

/* char far * GetFilePositionByNo(int no) */
#define GetFilePositionByNo(no)	GetFilePositionByNo_AB(DISKA,no)

/* char far * GetFilePositionByName(char *fname) */
#define GetFilePositionByName(fname)	GetFilePositionByName_AB(DISKA,fname)

int GetFileNo_AB(int disk);
int GetFileName_AB(int disk,int no,char *fname);
FILE_DATA far * GetFileInfoByNo_AB(int disk,int no);
FILE_DATA far *GetFileInfoByName_AB(int disk,char *fname);
char far * GetFilePositionByNo_AB(int disk,int no);
char far * GetFilePositionByName_AB(int disk,char *fname);

#define	COM1	0
#define	COM2	1
#define	COM3	2
#define	COM4	3
#define	COM5	4
#define	COM6	5
#define	COM7	6

#define FLOW_CONTROL_DISABLE	0
#define FLOW_CONTROL_ENABLE	1
#define FLOW_CONTROL_AUTO_BY_HW 2
#define FLOW_CONTROL_AUTO_BY_SW	3

/* for COM1 */
/* WITH CTS & RTS control */

#define	ClearTxBuffer1		ClearTxBuffer_1
#define GetTxBufferFreeSize1	GetTxBufferFreeSize_1
#define PushDataToCom1		PushDataToCom_1

#define CheckInputBufSize1	CheckInputBufSize_1
#define InstallCom1		InstallCom_1
#define RestoreCom1		RestoreCom_1
#define SetBaudrate1		SetBaudrate_1
#define SetDataFormat1		SetDataFormat_1
#define ClearCom1		ClearCom_1
#define DataSizeInCom1		DataSizeInCom_1
#define IsCom1			IsCom_1
#define IsCom1OutBufEmpty	IsComOutBufEmpty_1
#define ReadCom1		ReadCom_1
#define ToCom1Bufn		ToComBufn_1
#define ToCom1Str		ToComStr_1
#define SetCom1Timeout		SetComTimeout_1
#define ToCom1			ToCom_1
#define IsTxBufEmpty1		IsTxBufEmpty_1
#define WaitTransmitOver1	WaitTransmitOver_1
#define ReadCom1n		ReadComn_1
#define printCom1		printCom_1
#define SetBreakMode1		SetBreakMode_1
#define SendBreak1		SendBreak_1
#define IsDetectBreak1		IsDetectBreak_1

#define SetRtsActive1		SetRtsActive_1
#define SetRtsInactive1		SetRtsInactive_1
#define GetCtsStatus1		GetCtsStatus_1
#define SetCtsControlMode1	SetCtsControlMode_1
#define SetRtsControlMode1	SetRtsControlMode_1

void ClearTxBuffer_1(void);
int GetTxBufferFreeSize_1(void);
int PushDataToCom_1(int data);
void CheckInputBufSize_1(void);
int InstallCom_1(unsigned long baud, int data, int parity,int stop);
int RestoreCom_1(void);
int SetBaudrate_1(unsigned long baud);
int SetDataFormat_1(int databit,int parity,int stopbit);
int ClearCom_1(void);
int ClearCom_DMA_1(void);
int DataSizeInCom_1(void);
int IsCom_1(void);
int IsComOutBufEmpty_1(void);
int ReadCom_1(void);
int ToComBufn_1(char *buf,int no);
int ToComStr_1(char *str);
void SetComTimeout_1(unsigned t);
int ToCom_1(int data);
int IsTxBufEmpty_1(void);
int WaitTransmitOver_1(void);
int ReadComn_1(unsigned char *buf,int no);
int printCom_1(char *fmt,...);

void SetBreakMode_1(int mode);
void SendBreak_1(unsigned TimeMs);
int IsDetectBreak_1(void);

void SetRtsActive_1(void);
void SetRtsInactive_1(void);
int GetCtsStatus_1(void);
void CheckCtsStatus_1(void);
void SetCtsControlMode_1(int mode);
void SetRtsControlMode_1(int mode);

void SetComPortBufferSize_1(int in_size,int out_size);
void InstallComInputData_1(int (*DoInputData)(unsigned char data));


/* for COM2 (in normal RS-485)*/
/* WITHOUT CTS & RTS control */

#define	ClearTxBuffer2		ClearTxBuffer_2
#define GetTxBufferFreeSize2	GetTxBufferFreeSize_2
#define PushDataToCom2		PushDataToCom_2

#define CheckInputBufSize2	CheckInputBufSize_2
#define InstallCom2		InstallCom_2
#define RestoreCom2		RestoreCom_2
#define SetBaudrate2		SetBaudrate_2
#define SetDataFormat2		SetDataFormat_2
#define ClearCom2		ClearCom_2
#define DataSizeInCom2		DataSizeInCom_2
#define IsCom2			IsCom_2
#define IsCom2OutBufEmpty	IsComOutBufEmpty_2
#define ReadCom2		ReadCom_2
#define ToCom2Bufn		ToComBufn_2
#define ToCom2Str		ToComStr_2
#define SetCom2Timeout		SetComTimeout_2
#define ToCom2			ToCom_2
#define IsTxBufEmpty2		IsTxBufEmpty_2
#define WaitTransmitOver2	WaitTransmitOver_2
#define ReadCom2n		ReadComn_2
#define printCom2		printCom_2
#define SetBreakMode2		SetBreakMode_2
#define SendBreak2		SendBreak_2
#define IsDetectBreak2		IsDetectBreak_2

void ClearTxBuffer_2(void);
int GetTxBufferFreeSize_2(void);
int PushDataToCom_2(int data);
void CheckInputBufSize_2(void);
int InstallCom_2(unsigned long baud, int data, int parity,int stop);
int RestoreCom_2(void);
int SetBaudrate_2(unsigned long baud);
int SetDataFormat_2(int databit,int parity,int stopbit);
int ClearCom_2(void);
int ClearCom_DMA_2(void);
int DataSizeInCom_2(void);
int IsCom_2(void);
int IsComOutBufEmpty_2(void);
int ReadCom_2(void);
int ToComBufn_2(char *buf,int no);
int ToComStr_2(char *str);
void SetComTimeout_2(unsigned t);
int ToCom_2(int data);
int IsTxBufEmpty_2(void);
int WaitTransmitOver_2(void);
int ReadComn_2(unsigned char *buf,int no);
int printCom_2(char *fmt,...);

void SetBreakMode_2(int mode);
void SendBreak_2(unsigned TimeMs);
int IsDetectBreak_2(void);

void SetComPortBufferSize_2(int in_size,int out_size);
void InstallComInputData_2(int (*DoInputData)(unsigned char data));

/*
 Functions for COM3 (WITHOUT RTS/CTS)
*/
#define InstallCom3	InstallCom_3
#define RestoreCom3	RestoreCom_3
#define IsCom3		IsCom_3
#define ToCom3		ToCom_3
#define ToCom3Str	ToComStr_3
#define ToCom3Bufn	ToComBufn_3
#define printCom3	printCom_3
#define ClearTxBuffer3	ClearTxBuffer_3
#define SetCom3FifoTriggerLevel		SetComFifoTriggerLevel_3
#define SetBaudrate3	SetBaudrate_3
#define ReadCom3	ReadCom_3
#define ClearCom3	ClearCom_3
#define DataSizeInCom3  DataSizeInCom_3
#define WaitTransmitOver3	WaitTransmitOver_3
#define IsTxBufEmpty3		IsTxBufEmpty_3
#define IsCom3OutBufEmpty	IsComOutBufEmpty_3
#define ReadCom3n		ReadComn_3
#define SetDataFormat3		SetDataFormat_3
#define SetBreakMode3		SetBreakMode_3
#define SendBreak3		SendBreak_3
#define IsDetectBreak3		IsDetectBreak_3

int InstallCom_3(unsigned long baud, int data, int parity, int stop);
int RestoreCom_3(void);
int IsCom_3(void);
int ToCom_3(int data);
int ToComStr_3(char *str);
int ToComBufn_3(char *buf,int no);
int printCom_3(char *fmt,...);
void ClearTxBuffer_3(void);
int SetComFifoTriggerLevel_3(int level);
int SetBaudrate_3(unsigned long baud);
int ReadCom_3(void);
int ClearCom_3(void);
int DataSizeInCom_3(void);
int WaitTransmitOver_3(void);
int IsTxBufEmpty_3(void);
int IsComOutBufEmpty_3(void);
int SetDataFormat_3(int databit,int parity,int stopbit);
int ReadComn_3(unsigned char *buf,int n);
void SendBreak_3(unsigned timems);
void SetBreakMode_3(int mode);
int IsDetectBreak_3(void);

void SetComPortBufferSize_3(int in_size,int out_size);
void InstallComInputData_3(int (*DoInputData)(unsigned char data));

int DataSizeInCom_DMA_3(void);
int ReadComn_DMA_3(unsigned char *buf,int maxsize);
int InstallCom_DMA_3(unsigned long baud, int data, int parity,int stop);
int ClearCom_DMA_3(void);
int IsCom_DMA_3(void);
int DataSizeInCom_DMA_3(void);
int ReadCom_DMA_3(void);

/*
 Functions for COM4 (without RTS/CTS)
*/
#define InstallCom4	InstallCom_4
#define RestoreCom4	RestoreCom_4
#define IsCom4		IsCom_4
#define ToCom4		ToCom_4
#define ToCom4Str	ToComStr_4
#define ToCom4Bufn	ToComBufn_4
#define printCom4	printCom_4
#define ClearTxBuffer4	ClearTxBuffer_4
#define SetCom4FifoTriggerLevel		SetComFifoTriggerLevel_4
#define SetBaudrate4	SetBaudrate_4
#define ReadCom4	ReadCom_4
#define ClearCom4	ClearCom_4
#define DataSizeInCom4  DataSizeInCom_4
#define WaitTransmitOver4	WaitTransmitOver_4
#define IsTxBufEmpty4		IsTxBufEmpty_4
#define IsCom4OutBufEmpty	IsComOutBufEmpty_4
#define ReadCom4n		ReadComn_4
#define SetDataFormat4		SetDataFormat_4
#define SetBreakMode4		SetBreakMode_4
#define SendBreak4		SendBreak_4
#define IsDetectBreak4		IsDetectBreak_4

int InstallCom_4(unsigned long baud, int data, int parity, int stop);
int RestoreCom_4(void);
int IsCom_4(void);
int ToCom_4(int data);
int ToComStr_4(char *str);
int ToComBufn_4(char *buf,int no);
int printCom_4(char *fmt,...);
void ClearTxBuffer_4(void);
int SetComFifoTriggerLevel_4(int level);
int SetBaudrate_4(unsigned long baud);
int ReadCom_4(void);
int ClearCom_4(void);
int DataSizeInCom_4(void);
int WaitTransmitOver_4(void);
int IsTxBufEmpty_4(void);
int IsComOutBufEmpty_4(void);
int SetDataFormat_4(int databit,int parity,int stopbit);
int ReadComn_4(unsigned char *buf,int n);
void SendBreak_4(unsigned timems);
void SetBreakMode_4(int mode);
int IsDetectBreak_4(void);

void SetComPortBufferSize_4(int in_size,int out_size);
void InstallComInputData_4(int (*DoInputData)(unsigned char data));

int DataSizeInCom_DMA_4(void);
int ReadComn_DMA_4(unsigned char *buf,int maxsize);
int InstallCom_DMA_4(unsigned long baud, int data, int parity,int stop);
int ClearCom_DMA_4(void);
int IsCom_DMA_4(void);
int DataSizeInCom_DMA_4(void);
int ReadCom_DMA_4(void);

/*
 Functions for COM5(7188XA+X560),WITHOUT RTS/CTS
*/
#define InstallCom5	InstallCom_5
#define RestoreCom5	RestoreCom_5
#define IsCom5		IsCom_5
#define ToCom5		ToCom_5
#define ToCom5Str	ToComStr_5
#define ToCom5Bufn	ToComBufn_5
#define printCom5	printCom_5
#define ClearTxBuffer5	ClearTxBuffer_5
#define SetCom5FifoTriggerLevel		SetComFifoTriggerLevel_5
#define SetBaudrate5	SetBaudrate_5
#define ReadCom5	ReadCom_5
#define ClearCom5	ClearCom_5
#define DataSizeInCom5  DataSizeInCom_5
#define WaitTransmitOver5	WaitTransmitOver_5
#define IsTxBufEmpty5		IsTxBufEmpty_5
#define IsCom5OutBufEmpty	IsComOutBufEmpty_5
#define ReadCom5n		ReadComn_5
#define SetDataFormat5		SetDataFormat_5
#define SetRtsActive5		SetRtsActive_5
#define SetRtsInactive5		SetRtsInactive_5
#define GetCtsStatus5		GetCtsStatus_5
#define SetBreakMode5		SetBreakMode_5
#define SendBreak5		SendBreak_5
#define IsDetectBreak5		IsDetectBreak_5

int InstallCom_5(unsigned long baud, int data, int parity, int stop);
int RestoreCom_5(void);
int IsCom_5(void);
int ToCom_5(int data);
int ToComStr_5(char *str);
int ToComBufn_5(char *buf,int no);
int printCom_5(char *fmt,...);
void ClearTxBuffer_5(void);
int GetTxBufferFreeSize_5(void);
int SetComFifoTriggerLevel_5(int level);
int SetBaudrate_5(unsigned long baud);
int ReadCom_5(void);
int ClearCom_5(void);
int DataSizeInCom_5(void);
int WaitTransmitOver_5(void);
int IsTxBufEmpty_5(void);
int IsComOutBufEmpty_5(void);
int SetDataFormat_5(int databit,int parity,int stopbit);
int ReadComn_5(unsigned char *buf,int n);
void SetRtsActive_5(void);
void SetRtsInactive_5(void);
int GetCtsStatus_5(void);
void SendBreak_5(unsigned timems);
void SetBreakMode_5(int mode);
int IsDetectBreak_5(void);
int GetTxBufferFreeSize_5(void);

void SetComPortBufferSize_5(int in_size,int out_size);
void InstallComInputData_5(int (*DoInputData)(unsigned char data));

/*
 Functions for COM6(7188XA+X560),WITHOUT RTS/CTS
*/
#define IsCom6		IsCom_6
#define ToCom6		ToCom_6
#define ToCom6Str	ToComStr_6
#define ToCom6Bufn	ToComBufn_6
#define printCom6	printCom_6
#define ClearTxBuffer6	ClearTxBuffer_6
#define SetCom6FifoTriggerLevel		SetComFifoTriggerLevel_6
#define SetBaudrate6	SetBaudrate_6
#define ReadCom6	ReadCom_6
#define ClearCom6	ClearCom_6
#define DataSizeInCom6  DataSizeInCom_6
#define WaitTransmitOver6	WaitTransmitOver_6
#define IsTxBufEmpty6		IsTxBufEmpty_6
#define IsCom6OutBufEmpty	IsComOutBufEmpty_6
#define ReadCom6n		ReadComn_6
#define SetDataFormat6		SetDataFormat_6
#define SetBreakMode6		SetBreakMode_6
#define SendBreak6		SendBreak_6
#define IsDetectBreak6		IsDetectBreak_6

int InstallCom_6(unsigned long baud, int data, int parity, int stop);
int RestoreCom_6(void);
int IsCom_6(void);
int ToCom_6(int data);
int ToComStr_6(char *str);
int ToComBufn_6(char *buf,int no);
int printCom_6(char *fmt,...);
void ClearTxBuffer_6(void);
int GetTxBufferFreeSize_6(void);
int SetComFifoTriggerLevel_6(int level);
int SetBaudrate_6(unsigned long baud);
int ReadCom_6(void);
int ClearCom_6(void);
int DataSizeInCom_6(void);
int WaitTransmitOver_6(void);
int IsTxBufEmpty_6(void);
int IsComOutBufEmpty_6(void);
int SetDataFormat_6(int databit,int parity,int stopbit);
int ReadComn_6(unsigned char *buf,int n);
void SendBreak_6(unsigned timems);
void SetBreakMode_6(int mode);
int IsDetectBreak_6(void);
int GetTxBufferFreeSize_6(void);

void SetComPortBufferSize_6(int in_size,int out_size);
void InstallComInputData_6(int (*DoInputData)(unsigned char data));

/*
 Functions for COM7(7188XA+X560),WITHOUT RTS/CTS
*/
#define IsCom7		IsCom_7
#define ToCom7		ToCom_7
#define ToCom7Str	ToComStr_7
#define ToCom7Bufn	ToComBufn_7
#define printCom7	printCom_7
#define ClearTxBuffer7	ClearTxBuffer_7
#define SetCom7FifoTriggerLevel		SetComFifoTriggerLevel_7
#define SetBaudrate7	SetBaudrate_7
#define ReadCom7	ReadCom_7
#define ClearCom7	ClearCom_7
#define DataSizeInCom7  DataSizeInCom_7
#define WaitTransmitOver7	WaitTransmitOver_7
#define IsTxBufEmpty7		IsTxBufEmpty_7
#define IsCom7OutBufEmpty	IsComOutBufEmpty_7
#define ReadCom7n		ReadComn_7
#define SetDataFormat7		SetDataFormat_7
#define SetBreakMode7		SetBreakMode_7
#define SendBreak7		SendBreak_7
#define IsDetectBreak7		IsDetectBreak_7

int InstallCom_7(unsigned long baud, int data, int parity, int stop);
int RestoreCom_7(void);
int IsCom_7(void);
int ToCom_7(int data);
int ToComStr_7(char *str);
int ToComBufn_7(char *buf,int no);
int printCom_7(char *fmt,...);
void ClearTxBuffer_7(void);
int GetTxBufferFreeSize_7(void);
int SetComFifoTriggerLevel_7(int level);
int SetBaudrate_7(unsigned long baud);
int ReadCom_7(void);
int ClearCom_7(void);
int DataSizeInCom_7(void);
int WaitTransmitOver_7(void);
int IsTxBufEmpty_7(void);
int IsComOutBufEmpty_7(void);
int SetDataFormat_7(int databit,int parity,int stopbit);
int ReadComn_7(unsigned char *buf,int n);
void SendBreak_7(unsigned timems);
void SetBreakMode_7(int mode);
int IsDetectBreak_7(void);
int GetTxBufferFreeSize_7(void);

void SetComPortBufferSize_7(int in_size,int out_size);
void InstallComInputData_7(int (*DoInputData)(unsigned char data));


/*
  For Send command to I-7000/I-87K series.
*/
extern char hex_to_ascii[16];
int ascii_to_hex(char ascii);

int SendCmdTo7000(int iPort, unsigned char *cCmd, int iChksum);
/*
(INPUT)iPort:can be 1~7.
(INPUT)lTimeout: unit is ms.
(INPUT) cCmd: cmd for send to COM port(I-7000/I-87K).
              DON'T add '\r' at the end of cCmd, SendCmdTo7000() will add check sum(if needed) & '\r' after cCmd .
(INPUT) iChksum: 0: disable, 1: enable.
*/

int ReceiveResponseFrom7000(int iPort, unsigned char *cCmd, long lTimeout, int iChksum);
/*
(INPUT)iPort:can be 1~7.
(INPUT)lTimeout: unit is check times.
(OUTPUT) cCmd: response from COM port(I-7000/I-87K).
(INPUT) iChksum: 0: disable, 1: enable.
*/

#define ReceiveResponseFrom7000_ms	ReceiveResponseFrom7000_1
int ReceiveResponseFrom7000_1(int iPort, unsigned char *cCmd, long lTimeout, int iChksum);
/*
(INPUT)iPort:can be 1~7.
(INPUT)lTimeout: unit is ms. (*****)
(OUTPUT) cCmd: response from COM port(I-7000/I-87K).
(INPUT) iChksum: 0: disable, 1: enable.
*/

/* for ALL COM PORT */
int printCom(int port,char *fmt,...);
int IsDetectBreak(int port);
int SendBreak(int port,unsigned timems);
int SetBreakMode(int port,int mode);
int ClearCom(int port);
int ClearTxBuffer(int port);
int InstallCom(int port, unsigned long baud, int data, int parity,int stop);
int ToComBufn(int port,char *buf,int no);
int RestoreCom(int port);
int ToComStr(int port,char *str);
int DataSizeInCom(int port);
int IsCom(int port);
int ReadComn(int port,unsigned char *buf,int n);
int ReadCom(int port);
int SetBaudrate(int port,unsigned long baud);
int ToCom(int port,int data);
int IsTxBufEmpty(int port);
int GetTxBufferFreeSize(int port);
int WaitTransmitOver(int port);
int SetRtsActive(int port);
int SetRtsInactive(int port);
int GetCtsStatus(int port);

/*  function table for up functions except printCom */
/*
  For example if want to call:
   if(IsCom(port)){
   	data=ReadCom(port);
   }
  also can use :
   if(IsCom_[port]()){
   	data=ReadCom_[port]();
   }

  IsCom(port)/ReadCom(port) just for backword compatible, it also will call IsCom_[port]()/ReadCom_[port]()

  and so on.
*/

#define COM_PORT_NO	7
/* 4 base com port, and for X-560(COM 5/6/7)*/

extern int (*IsDetectBreak_[COM_PORT_NO+1])(void);
extern void (*SendBreak_[COM_PORT_NO+1])(unsigned timems);
extern void (*SetBreakMode_[COM_PORT_NO+1])(int mode);
extern int (*ClearCom_[COM_PORT_NO+1])(void);
extern void (*ClearTxBuffer_[COM_PORT_NO+1])(void);
extern int (*InstallCom_[COM_PORT_NO+1])(unsigned long baud, int data, int parity,int stop);
extern int (*ToComBufn_[COM_PORT_NO+1])(char *buf,int no);
extern int (*RestoreCom_[COM_PORT_NO+1])(void);
extern int (*ToComStr_[COM_PORT_NO+1])(char *str);
extern int (*DataSizeInCom_[COM_PORT_NO+1])(void);
extern int (*IsCom_[COM_PORT_NO+1])(void);
extern int (*ReadComn_[COM_PORT_NO+1])(unsigned char *buf,int n);
extern int (*ReadCom_[COM_PORT_NO+1])(void);
extern int (*SetBaudrate_[COM_PORT_NO+1])(unsigned long baud);
extern int (*ToCom_[COM_PORT_NO+1])(int data);
extern int (*IsTxBufEmpty_[COM_PORT_NO+1])(void);
extern int (*GetTxBufferFreeSize_[COM_PORT_NO+1])(void);
extern int (*WaitTransmitOver_[COM_PORT_NO+1])(void);
extern void (*SetRtsActive_[COM_PORT_NO+1])(void);
extern void (*SetRtsInactive_[COM_PORT_NO+1])(void);
extern int (*GetCtsStatus_[COM_PORT_NO+1])(void);

int GetComportNumber(void);
extern int TriggerLevel[COM_PORT_NO];

/* for DI & DO */
#define SetDoHigh()	SetDo1(1)
#define SetDoLow()	SetDo1(0)
#define SetDo1High()	SetDo1(1)
#define SetDo1Low()	SetDo1(0)

#define SetDo1On()	SetDo1(1)
#define SetDo1Off()	SetDo1(0)
#define SetDo2On()	SetDo2(1)
#define SetDo2Off()	SetDo2(0)
/*
  DO1/2 is open collector output,
  	SetDo1On()/SetDo2On() will set the output Tx On.
  	SetDo1Off()/SetDo2Off() will set the output Tx Off.

	GetDo1()/GetDo2() will get the output Tx status.
		return value:
		0: the output Tx is Off.
		others(!=0):the output Tx is On.
*/

void SetDo1(int mode);
int GetDo1(void);
void SetDo2(int mode);
int GetDo2(void);

int GetDi1(void);
/*
  return value:
  0: the input is Low.
  others(!=0):the input is Low.
*/
int GetDi2(void);
/*
  return value:
  0: the input is Low.
  others(!=0):the input is Low.
*/

void InitLib(void);
/*
  for I-7188XC, InitLib() do nothing.
*/
void GetLibDate(char *date);
unsigned GetLibVersion(void);
/*
 Current version is 2.01 (return 0x0201)
*/

/* [11/06/2003] add Software flow control(Xon/Xoff) for COM1~COM8 except COM2
	COM2 is RS-485, used in half-duplex mode, need not software flow control.
*/
void SetXonXoffControlMode_1(int mode);
void SetXonXoffControlMode_3(int mode);
void SetXonXoffControlMode_4(int mode);
void SetXonXoffControlMode_5(int mode);
void SetXonXoffControlMode_6(int mode);
void SetXonXoffControlMode_7(int mode);
/*
  mode=0 --> disable Xon/Xoff control
  mode=1 --> enable Xon/Xoff control
*/

/*
 [2003/12/01]
 Add function for debug, using STDIO COM PORT.
 Even after all InstallCom_1() also can use these 3 functions to send message to STDIO COM port.
*/
void pascal _dPutch(int data1);
void _dPuts(char *str);
int _dPrint(char *fmt,...);

/*
 [2003/12/10]
 Add function for read system timeticks.
*/
long GetTimeTicks(void);
long GetTimeTicks_ISR(void); /* use this one in ISR */
/*
  The return value is *TimeTicks.
*/

int InstallUserTimerFunction_us(unsigned time,void (*fun)(void));
/*
  time unit is 0.1 us.

  for example:
	If want timer generate interrupt for every 0.5ms(500 us=5000*0.1us)
	(That is to say system will call your function once every 0.5 ms)
	just use

	void fun(void)
	{
		...
	}
	...
	InstallUserTimerFunction_us(5000,fun);
*/

int InstallUserTimerFunction_ms(unsigned time,void (*fun)(void));
/*
  time unit is ms.

  for example:
	If want timer generate interrupt for every 1 second(1 sec=1000 ms)
	(That is to say system will call your function once every 1 sec.)
	just use

	void fun(void)
	{
		...
	}
	...
	InstallUserTimerFunction_ms(1000,fun);
*/

void StopUserTimerFun(void);

/* For PIO pins on I/O expansion BUS */
void SetDio4Dir(int dir);
void SetDio4High(void);
void SetDio4Low(void);
int GetDio4(void);

void SetDio9Dir(int dir);
void SetDio9High(void);
void SetDio9Low(void);
int GetDio9(void);

void SetDio14Dir(int dir);
void SetDio14High(void);
void SetDio14Low(void);
int GetDio14(void);

void SetTi0Dir(int dir);
void SetTi0High(void);
void SetTi0Low(void);
int GetTi0(void);

void SetTi1Dir(int dir);
void SetTi1High(void);
void SetTi1Low(void);
int GetTi1(void);

void SetTo0Dir(int dir);
void SetTo0High(void);
void SetTo0Low(void);
int GetTo0(void);

void SetTo1Dir(int dir);
void SetTo1High(void);
void SetTo1Low(void);
int GetTo1(void);

/* general purpose functions for all PIO pins
   Please be carefully for using these 3 functions.
   !!! NOT ALL 32 PIO pins can use used by user. !!!
*/
void SetPioDir(unsigned pin,int dir);
void SetPio(int pin,int mode);
int GetPio(int pin);
/*
  input:
    pin : 0~31.
    mode: 0 or 1
    dir:
        0: set the PIO pin to output mode
        1: set the PIO pin to input with pull high(for some pin is pull low.)
        2: set the PIO pin to input without pull high/low.
    	3: set the PIO pin to normal mode

  output for GetPio():
	0: for input mode: the input is low.
	   for output mode: current output is low.
	non zero:   for input mode: the input is high.
	   for output mode: current output is high.
*/

/* 2004/02/26 add function usr burst mode to read date/time from RTC chip(DS-1302) */
typedef struct {
	int year;
	char month,day,weekday;
	char hour,minute,sec;
}TIME_DATE;

void GetTimeDate(TIME_DATE *timedate);
int SetTimeDate(TIME_DATE *timedate);
/*
  when call SetTimeDate(), need set the right year,month,day and the function
  will auto set the weekday.
*/

/* [2004/09/09] add */
extern int bLfMode;
/*
By default bLfMode=0.
If set bLfMode to 1, Putch() will translate '\n' to '\r'+'\n'.
Puts() will call Putch() will be affected by bLfMode.
Print() will call Puts() also will be affected by bLfMode.
*/

extern const unsigned char far * const SystemSerialNumber;
int GetSerialNumber(char *Serial);
/*
[2004/10/13] Add
  GetSerialNumber() is used to read system serial number from hardware.
  on sucess return 0, and the serial number store to Serial.
  on fail return -1: cannot find the hardware IC
	  return -2: CRC error
*/

/*
[2005/02/21] Add
*/
void far * AllocateTopMemory(unsigned long size);

extern int LsrError_1;
extern int LsrError_2;
extern int LsrError_5;
extern int LsrError_6;
extern int LsrError_7;

/*
[2005/05/27] add functions for using timer functions
*/
int SetDelayTimer(int no);
/*
The delay functions(Dealy()/Delay_1()/Delay_2() by default using system's timer 0.
user can call SetDelayTimer(1); set it to use timer 1.

return : 0 for using timer 0, 1 for using timer 1. 
*/
int SetUserTimer(int no);
/*
The user timer functions(InstallUserTimerFunction_us()/InstallUserTimerFunction_ms()
 by default using system's timer 0.
user can call SetUserTimer(1); set it to use timer 1.

return : 0 for using timer 0, 1 for using timer 1. 
*/

#ifdef __cplusplus
}
#endif

#endif
