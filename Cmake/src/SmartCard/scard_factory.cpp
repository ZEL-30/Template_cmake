#include "scard_factory.h"





// ���幤��
CConcreteFactory::CConcreteFactory() {
    // ��ʼ����Ա����
	lReturn_ = 0, nReaders_ = 0, nCurrentReader_ = 0;
	memset(mszReaders_, 0, sizeof(mszReaders_));
	pReader_ = NULL, mszReaders_len_ = 1024, reader_nums_ = 0;
	memset(pReaderName_, 0, sizeof(pReaderName_));
    reader_ = this->CreateReader();

    // ��ʼ���豸�����Ĳ���þ��
	lReturn_ = SCardEstablishContext(SCARD_SCOPE_USER, NULL, NULL, &hSC_);
	if (lReturn_ != SCARD_S_SUCCESS) {
		printf("Failed SCardEstablishContext!");
	}


}


CSCardReader* CConcreteFactory::CreateReader() {
    return new CConcreteReader();
}


bool CConcreteFactory::ReaderConnect(int reader_seq) {

	if (reader_seq > 0 && reader_seq_ <= reader_nums_) {
	    reader_seq_ = reader_seq;
	    return true;
	}
	return false;
}


int CConcreteFactory::ListReaders() {

    // ��ȡϵͳ�а�װ�Ķ������б�
	lReturn_ = SCardListReaders(hSC_, NULL, (LPTSTR)mszReaders_, &mszReaders_len_);
	if (lReturn_ == SCARD_S_SUCCESS) {
		pReader_ = (LPTSTR)mszReaders_;
		while (*pReader_ != '\0') {
			if (nReaders_ < 2)
				pReaderName_[nReaders_++] = pReader_;

			// ��һ����������
			pReader_ = pReader_ + strlen(pReader_) + 1;
			reader_nums_++;
		}
	}
	return reader_nums_;
}

int CConcreteFactory::GetReaderName(int Number, char* ReaderName) {
    // ��ָ���Ķ��������Ʒ���
	memcpy(ReaderName, pReaderName_[Number - 1], strlen(pReaderName_[Number - 1]));

	return 1;
}


bool CConcreteFactory::ReaderClose () {
	// �ͷ�������
	lReturn_ = SCardReleaseContext(hSC_);
	if (lReturn_ != SCARD_S_SUCCESS) {
		printf("Failed SCardReleaseContext!\n");
		return false;
	}

	return true;
}


bool CConcreteFactory::CardOpen() {

	char reader_name[256]; memset(reader_name, 0, sizeof(reader_name));
	this->GetReaderName(reader_seq_, reader_name);
	hCardHandle_[0] = reader_->ConnectReader(hSC_, reader_name);

	return true;

}


bool CConcreteFactory::CardClsoe() {
	reader_->DisConnectReader(hCardHandle_[0]);
	return true;
}



bool CConcreteFactory::CardReset(char *ATR, char *state, char *protocol) {

	if (reader_->GetATR(hCardHandle_[0], ATR, state, protocol))
		return true;
   
	return false;
}


long CConcreteFactory::CardApdu(unsigned char *command, int comLen, char *result, int *resultLength) {
	return reader_->SendCommand(hCardHandle_[0], command, comLen, result, resultLength);
}

CConcreteFactory::~CConcreteFactory() {

}


