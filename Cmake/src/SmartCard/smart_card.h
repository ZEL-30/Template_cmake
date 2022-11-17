#pragma once

#include "winscard.h"
#include <stdio.h>
#include <string.h>



// ����������
class CSCardReader {

public:

	// �뵱ǰ��������������
	// ReaderName ��Ҫ�������ӵĶ��������
	// Return hCard���ܿ��������������
	virtual int ConnectReader(SCARDCONTEXT hSC, char *ReaderName) = 0;

	// ��������Ͽ�
	// hCard ���ܿ��������������
	// Return 0:ʧ�� ��0:�ɹ�
	virtual int DisConnectReader(int hCard) = 0;

	//Get Atr
    //hCard ��� 
    //ATR���õ���ATRֵ
    //state��������״̬
    //protocolͨѶЭ��
    //Return:�Ƿ�ɹ� 0��ʧ�� ��0���ɹ�
	virtual int GetATR(int hCard, char* ATR, char* state, char* protocol) = 0;

	//�������������������շ��ص����ݡ�
	//hCard ��� 
	//command�����͵�ָ�� 
	//comLen:ָ��� 
	//result������ֵ 
	//resultLength������ֵ����
	//Return:״̬�� 
	virtual long SendCommand(int hCard, unsigned char* command, int comLen, char* result, int* resultLengt) = 0;

	virtual bool ReaderGetSerial(bool compare_id) = 0;

	void AscToBcd(unsigned char* bcd, unsigned char* asc, int asc_len);

    //bcd����һ��Ϊ���飬������һ���ֽ�
	void BcdToAsc(char* asc, char* bcd, int asc_len);

	virtual ~CSCardReader() {};

protected:

    SCARDCONTEXT        hSC_;
	LONG                lReturn_;
	char                mszReaders_[1024];         // ϵͳ�а�װ�Ķ�����������, ��������֮����'\0'�ָ�, ���һ�����ֺ���Ϊ����������'\0'	
	LPTSTR              pReader_, pReaderName_[2];
	DWORD               mszReaders_len_;           // mszReaders�ĳ���
	int                 nReaders_, nCurrentReader_;
	SCARDHANDLE         hCardHandle_[1024];
	DWORD               protocol_;
	int                 reader_nums_;              // ����������
	int                 reader_name_;              // ����������
	WCHAR               szReader_[200];
	DWORD               cch_;
	DWORD               cByte_;                    // ATR�ĳ���
	BYTE                sw1_, sw2_;                // SWֵ
};







// �Ӵ�ʽ������
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



