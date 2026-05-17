#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
void compact(void *start, void *end){
    unsigned char *src=(unsigned char*)start;
    unsigned char *dst=(unsigned char*)start;
    unsigned char *finish=(unsigned char*)end;

    if(!start||!end||src>finish)return;

    for(;src<finish;++src){
        if(*src!='\0'){
            if(dst!=src)*dst=*src;
                ++dst;
        }
    }

    unsigned char *new_end=(unsigned char*)start+(dst-(unsigned char*)start);
    long delta=(long)(new_end-(unsigned char*)end);
    if(delta!=0){
        (void)sbrk(delta);
    }

}
