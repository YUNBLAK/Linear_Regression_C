#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "csvlinkedlist.h"


extern EQUATION equation();
extern void printRMSE();
int main(int argc, const char * argv[]) {
    
    EQUATION lst = equation(1000, 0.000001);
    printf("%.16f %.16f\n", lst.w, lst.b);
    printRMSE(lst.w, lst.b);
    
    return 0;
    
}
