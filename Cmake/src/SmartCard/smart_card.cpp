#include "smart_card.h"


void CSCardReader::BcdToAsc(char* asc, char* bcd, int asc_len) {
	unsigned char ch1, ch2;
	for (int i = 0; i < asc_len; i++)
	{
		ch1 = (bcd[i] & 0xF0) >> 4;
		ch2 = bcd[i] & 0x0F;
		ch1 += ((ch1 > 9) ? 0x37 : 0x30);
		ch2 += ((ch2 > 9) ? 0x37 : 0x30);
		asc[i * 2] = ch1;
		asc[i * 2 + 1] = ch2;
	}
}


void CSCardReader::AscToBcd(unsigned char* bcd, unsigned char* asc, int asc_len) {
	char  ch1, ch2;
	for (int i = 0; i < (asc_len / 2); i++)
	{
		ch1 = bcd[i * 2];
		ch2 = bcd[i * 2 + 1];
		(ch1 >= 'a' && ch1 <= 'z') ? (ch1 -= 32) : (ch1);
		(ch2 >= 'a' && ch2 <= 'z') ? (ch2 -= 32) : (ch2);
		ch1 -= ((ch1 > '9') ? 0x37 : 0x30);
		ch2 -= ((ch2 > '9') ? 0x37 : 0x30);
		asc[i] = (ch1 << 4) | ch2;
	}
}












CConcreteReader::CConcreteReader() {

    // 初始化成员属性
	lReturn_ = 0, nReaders_ = 0, nCurrentReader_ = 0;
	memset(mszReaders_, 0, sizeof(mszReaders_));
	pReader_ = NULL, mszReaders_len_ = 1024, reader_nums_ = 0;
	memset(pReaderName_, 0, sizeof(pReaderName_));
	cch_ = 0, cByte_ = 0;
  
}




int CConcreteReader::ConnectReader(SCARDCONTEXT hSC, char *ReaderName) {

	// 校验参数
	if (reader_name_ > reader_nums_) {
		printf("Number is wrong!\n");
		return 0;
	}

	// lReturn_ = SCardConnect(hSC_, pReaderName_[ReaderName - 1], SCARD_SHARE_EXCLUSIVE, SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1, &hCardHandle_[ReaderName - 1], &protocol_);
	lReturn_ = SCardConnect(hSC, ReaderName, SCARD_SHARE_EXCLUSIVE, SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1, &hCardHandle_[0], &protocol_);
	if (lReturn_ != SCARD_S_SUCCESS) {
		printf("Failed ConnectReader!\n");
		return 0;
	}
	
	return hCardHandle_[0];

}


int CConcreteReader::DisConnectReader(int hCard) {

	// 断开智能卡的连接
	lReturn_ = SCardDisconnect(hCard, SCARD_LEAVE_CARD);
	if (lReturn_ != SCARD_S_SUCCESS) {
		printf("Failed SCardDisconnect!\n");
		return 0;
	}

	return 1;
}


bool CConcreteReader::ReaderGetSerial(bool compare_id) {

	return true;
}


int CConcreteReader::GetATR(int hCard, char *ATR, char *state, char *protocol) {

	// 获取智能卡状态和协议
	cch_ = 200, cByte_ = 32;
	char atr[260]; memset(atr, 0, sizeof(atr));
    lReturn_ = SCardStatus(hCard, (LPSTR)szReader_, &cch_, (LPDWORD)state, (LPDWORD)protocol, (LPBYTE)&atr, &cByte_);
	if (lReturn_ != SCARD_S_SUCCESS) {
		printf("Failed SCardStatus\n");
		return 0;
	}

	// 把ATR转为ASCII码
	BcdToAsc(ATR, atr, cByte_);

	return 1;
}


long CConcreteReader::SendCommand(int hCard, unsigned char* command, int comLen, char* result, int* resultLength) {

	// 该函数在开始之前等待所有其他事务完成。事务启动后，在事务进行过程中，将阻止所有其他应用程序访问智能卡。
	lReturn_ = SCardBeginTransaction(hCard);
	if (lReturn_ != SCARD_S_SUCCESS) {
		printf("Failed  SCardBeginTransaction\n");
		return 0;
	}

	// 发送指令
	char tmp[256]; memset(tmp, 0, sizeof(tmp));
	if (protocol_ == SCARD_PROTOCOL_T0)
	    lReturn_ = SCardTransmit(hCard, SCARD_PCI_T0, (LPCBYTE)command, comLen, NULL, (LPBYTE)tmp, (LPDWORD)resultLength);
	else if (protocol_ == SCARD_PROTOCOL_T1)
	    lReturn_ = SCardTransmit(hCard, SCARD_PCI_T1, (LPCBYTE)command, comLen, NULL, (LPBYTE)tmp, (LPDWORD)resultLength);
	if (lReturn_ != SCARD_S_SUCCESS) {
		printf("Failed SCardTransmit\n");
		return 0;
	}

	sw1_ = result[*resultLength - 2];
	sw2_ = result[*resultLength - 1];

    for (int i = 0; i < 7; i++) {
		printf("%x ", command[i]);
	}
	printf("\n");


	BcdToAsc(result, tmp, *resultLength);

	return sw1_;
}


CConcreteReader::~CConcreteReader() {

};


