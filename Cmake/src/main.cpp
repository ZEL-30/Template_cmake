#include <stdio.h>
#include "smart_card.h"
#include "scard_factory.h"
#include "public.h"


void test() {

	char name[41]; memset(name, 0, sizeof(name));
	STRCPY(name, sizeof(name), "��ʿ�ܹھ�!!!");
	printf("name : %s\n", name);

}






int main() {

	test();


    CSCardFactory *fac = new CConcreteFactory;

    int nums = fac->ListReaders();
    printf("������������Ϊ:%d\n", nums);

    // ���Ӷ�����
    if (!fac->ReaderConnect(2)) {
		printf("ReaderConnect() Failed.\n");
		return -1;
	}

    // ���ӿ�Ƭ
    fac->CardOpen();
    
    // ���ݱ�Ż�ȡATR
    char atr[256], ATR[256], state[256], protocol[256];
	memset(atr, 0, sizeof(atr)); memset(ATR, 0, sizeof(ATR));  memset(state, 0, sizeof(state));  memset(protocol, 0, sizeof(protocol));
	if (fac->CardReset(ATR, state, protocol)) {
		printf("ATR: %s\n", ATR);
	}
   
	// ����ָ��
	unsigned char command[] = { 0xA0, 0xA4, 0x00, 0x00, 0x02, 0x3F, 0x00 };
	char result[260];  memset(result, 0, sizeof(result));
	int comLen = 7, resultLength = sizeof(result);
	int statue_code = fac->CardApdu(command, comLen, result, &resultLength);
	printf("result: %s\n", result);

	// �Ͽ����ܿ�������
	fac->CardClsoe();

	// �Ͽ�������������	
	if (fac->ReaderClose()) {
		printf("DisConnectReader OK!\n");
	}

    delete fac;
    fac = NULL;


    return 0;
}