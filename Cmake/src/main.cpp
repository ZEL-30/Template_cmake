#include "zel.h"
#include "mode.h"

int main() {

    char name[256];

    STRCPY(name, sizeof(name), "hello world");

    printf("%s\n", name);


    return 0;
}