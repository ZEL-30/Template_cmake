#pragma once

#include "winscard.h"
#include <stdio.h>
#include <string.h>



// 读卡器基类
class CSCardReader {

public:

	// 与当前读卡器建立连接
	// ReaderName 需要建立连接的读卡器编号
	// Return hCard智能卡读卡器操作句柄
	virtual int ConnectReader(SCARDCONTEXT hSC, char *ReaderName) = 0;

	// 与读卡器断开
	// hCard 智能卡读卡器操作句柄
	// Return 0:失败 非0:成功
	virtual int DisConnectReader(int hCard) = 0;

	//Get Atr
    //hCard 句柄 
    //ATR：得到的ATR值
    //state：读卡器状态
    //protocol通讯协议
    //Return:是否成功 0：失败 非0：成功
	virtual int GetATR(int hCard, char* ATR, char* state, char* protocol) = 0;

	//向读卡器发送命令，并接收返回的数据。
	//hCard 句柄 
	//command：发送的指令 
	//comLen:指令长度 
	//result：返回值 
	//resultLength：返回值长度
	//Return:状态码 
	virtual long SendCommand(int hCard, unsigned char* command, int comLen, char* result, int* resultLengt) = 0;

	virtual bool ReaderGetSerial(bool compare_id) = 0;

	void AscToBcd(unsigned char* bcd, unsigned char* asc, int asc_len);

    //bcd参数一定为数组，即大于一个字节
	void BcdToAsc(char* asc, char* bcd, int asc_len);

	virtual ~CSCardReader() {};

protected:

    SCARDCONTEXT        hSC_;
	LONG                lReturn_;
	char                mszReaders_[1024];         // 系统中安装的读卡器的名字, 各个名字之间用'\0'分隔, 最后一个名字后面为两个连续的'\0'	
	LPTSTR              pReader_, pReaderName_[2];
	DWORD               mszReaders_len_;           // mszReaders的长度
	int                 nReaders_, nCurrentReader_;
	SCARDHANDLE         hCardHandle_[1024];
	DWORD               protocol_;
	int                 reader_nums_;              // 读卡器个数
	int                 reader_name_;              // 读卡器名称
	WCHAR               szReader_[200];
	DWORD               cch_;
	DWORD               cByte_;                    // ATR的长度
	BYTE                sw1_, sw2_;                // SW值
};







// 接触式读卡器
class CConcreteReader : public CSCardReader{

public:

	CConcreteReader();

	int GetReaderName(int Number, char* ReaderName);

	int ConnectReader(SCARDCONTEXT hSC, char *ReaderName);
	
	int DisConnectReader(int hCard);

	bool ReaderGetSerial(bool compare_id);
	
	int GetATR(int hCard, char* ATR, char* state, char* protocol);
	
	long SendCommand(int hCard, unsigned char* command, int comLen, char* result, int* resultLengt);

	~CConcreteReader();
};



