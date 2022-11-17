#pragma once
#include "smart_card.h"


// 工厂基类 
class CSCardFactory {

public:

    // 创建读卡器, 纯虚函数
    virtual CSCardReader* CreateReader() = 0;

    // 连接读卡器
    virtual bool ReaderConnect(int reader_seq) = 0;

    // 断开读卡器
    virtual bool ReaderClose() = 0;

    // 连接卡片
    virtual bool CardOpen() = 0;

    // 卡片复位
    virtual bool CardReset(char *ATR, char *state, char *protocol) = 0;
    
    // 发送APDU指令
    virtual long CardApdu(unsigned char *command, int comLen, char *result, int *resultLength) = 0;

    // 关闭卡片
    virtual bool CardClsoe() = 0;

    // 找出读卡器的个数
	virtual int ListReaders() = 0;

    // 得到单个读卡器名称
	// Number 第几个读卡器
	// ReaderName 返回读卡器名称
	// Return 0:失败, 非0:成功
	virtual int GetReaderName(int Number, char* ReaderName) = 0;

    virtual ~CSCardFactory() {}




protected:

    SCARDCONTEXT        hSC_;
	LONG                lReturn_;
	char                mszReaders_[1024];         // 系统中安装的读卡器的名字, 各个名字之间用'\0'分隔, 最后一个名字后面为两个连续的'\0'	
	LPTSTR              pReader_, pReaderName_[2];
	DWORD               mszReaders_len_;           // mszReaders的长度
	int                 nReaders_, nCurrentReader_;
	SCARDHANDLE         hCardHandle_[2];
	DWORD               protocol_;
	int                 reader_nums_;              // 读卡器个数
    int                 reader_seq_;               // 读卡器序列
    CSCardReader        *reader_;                  // 读卡器对象

};


// 具体工厂类
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