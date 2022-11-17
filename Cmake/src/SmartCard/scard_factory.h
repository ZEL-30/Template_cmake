#pragma once
#include "smart_card.h"


// �������� 
class CSCardFactory {

public:

    // ����������, ���麯��
    virtual CSCardReader* CreateReader() = 0;

    // ���Ӷ�����
    virtual bool ReaderConnect(int reader_seq) = 0;

    // �Ͽ�������
    virtual bool ReaderClose() = 0;

    // ���ӿ�Ƭ
    virtual bool CardOpen() = 0;

    // ��Ƭ��λ
    virtual bool CardReset(char *ATR, char *state, char *protocol) = 0;
    
    // ����APDUָ��
    virtual long CardApdu(unsigned char *command, int comLen, char *result, int *resultLength) = 0;

    // �رտ�Ƭ
    virtual bool CardClsoe() = 0;

    // �ҳ��������ĸ���
	virtual int ListReaders() = 0;

    // �õ���������������
	// Number �ڼ���������
	// ReaderName ���ض���������
	// Return 0:ʧ��, ��0:�ɹ�
	virtual int GetReaderName(int Number, char* ReaderName) = 0;

    virtual ~CSCardFactory() {}




protected:

    SCARDCONTEXT        hSC_;
	LONG                lReturn_;
	char                mszReaders_[1024];         // ϵͳ�а�װ�Ķ�����������, ��������֮����'\0'�ָ�, ���һ�����ֺ���Ϊ����������'\0'	
	LPTSTR              pReader_, pReaderName_[2];
	DWORD               mszReaders_len_;           // mszReaders�ĳ���
	int                 nReaders_, nCurrentReader_;
	SCARDHANDLE         hCardHandle_[2];
	DWORD               protocol_;
	int                 reader_nums_;              // ����������
    int                 reader_seq_;               // ����������
    CSCardReader        *reader_;                  // ����������

};


// ���幤����
class CConcreteFactory : public CSCardFactory {

public:

    CConcreteFactory();

    virtual CSCardReader* CreateReader() override;

    virtual bool ReaderConnect(int reader_seq) override;

    virtual bool ReaderClose() override;

    virtual bool CardOpen() override;

    virtual bool CardReset(char *ATR, char *state, char *protocol) override;
    
    virtual long CardApdu(unsigned char *command, int comLen, char *result, int *resultLength) override;

    virtual bool CardClsoe() override;

	virtual int ListReaders() override;

	virtual int GetReaderName(int Number, char* ReaderName) override;

    ~CConcreteFactory();
};