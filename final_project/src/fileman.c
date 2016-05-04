
#include "fileman.h"


unsigned long filesize( FILE* file )
{
    char c = getc( file );
    int i = 0;
    while( c != EOF )
    {
        i++;
        c = getc(file);
    }
    return i;
}


char* fileToString( FILE* file, unsigned long* len )
{
    *len = filesize( file );
    char *ret = malloc( (*len)+1 );
    fseek( file, 0, SEEK_SET );
    fread( ret, 1, (*len), file );
    fclose( file );
    ret[(*len)] = 0;
    return ret;
}


void writeStringToFile( FILE* file, const char* str )
{
    fputs( str, file );
}


char* appendIntToString( char* str, unsigned long* len, unsigned int i )
{
    int k = (int)log10(i)+1;
    unsigned long newLen = (*len) + k;

    char* ret = malloc( newLen+1 );
    int c = 0;
    for( c = 0; c < *len; c++ )
        ret[c] = str[c];
    ret[*len] = 0;

    char* intToStr = malloc(k);
    sprintf( intToStr, "%d\n", i );
    strcat( ret, intToStr );
    *len = newLen;

    return ret;
}
