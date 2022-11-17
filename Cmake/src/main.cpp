#include <stdio.h>
#include "smart_card.h"
#include "scard_factory.h"
#include "public.h"


void test() {

	char name[41]; memset(name, 0, sizeof(name));
	STRCPY(name, sizeof(name), "勇士总冠军!!!");
	printf("name : %s\n", name);

}






int main() {

	test();


    CSCardFactory *fac = new CConcreteFactory;

    int nums = fac->ListReaders();
    printf("读卡器的数量为:%d\n", nums);

    // 连接读卡器
    if (!fac->ReaderConnect(2)) {
		printf("ReaderConnect() Failed.\n");
		return -1;
	}

    // 连接卡片
    fac->CardOpen();
    
    // 根据编号获取ATR
    char atr[256], ATR[256], state[256], protocol[256];
	memset(atr, 0, sizeof(atr)); memset(ATR, 0, sizeof(ATR));  memset(state, 0, sizeof(state));  memset(protocol, 0, sizeof(protocol));
	if (fac->CardReset(ATR, state, protocol)) {
		printf("ATR: %s\n", ATR);
	}
   
	// 发送指令
	unsigned char command[] = { 0xA0, 0xA4, 0x00, 0x00, 0x02, 0x3F, 0x00 };
	char result[260];  memset(result, 0, sizeof(result));
	int comLen = 7, resultLength = sizeof(result);
	int statue_code = fac->CardApdu(command, comLen, result, &resultLength);
	printf("result: %s\n", result);

	// 断开智能卡的连接
	fac->CardClsoe();

	// 断开读卡器的连接	
	if (fac->ReaderClose()) {
		printf("DisConnectReader OK!\n");
	}

    delete fac;
    fac = NULL;


    return 0;
}