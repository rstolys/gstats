#include <stdio.h>
#include <string.h>

int main()
{
    char        szMsgBuf[100];
    char        szMsgBuf2[100];

    char        szSndBuf[100];

    strcpy(szMsgBuf, "Hello\0");
    strcpy(szMsgBuf2, "Ryan\n\0");



    strcat(szMsgBuf, szMsgBuf2);

    printf( "%s", szMsgBuf);
    

    return 0;
}

