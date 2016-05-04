#include "Encrypt.h"


char* encryptString( const char* str, unsigned int len )
{
    char* enc = malloc(len+1);
    int i, keyParser = 0;
    for( i = 0; i < len; i++ )
    {
        if( key[keyParser] == 0 )
            keyParser = 0;
        enc[i] = str[i]+key[keyParser++];
    }
    enc[len] = 0;
    return enc;
}


char* decryptString( const char* str, unsigned int len )
{
    char* dec = malloc(len+1);
    int i, keyParser = 0;
    for( i = 0; i < len; i++ )
    {
        if( key[keyParser] == 0 )
            keyParser = 0;
        dec[i] = str[i]-key[keyParser++];
    }
    dec[len] = 0;
    return dec;
}
