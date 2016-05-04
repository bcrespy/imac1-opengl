#include <stdlib.h>
#include <stdio.h>
#include "Encrypt.h"
#include "fileman.h"



int main( int argc, char** argv )
{
    if( argc != 2 )
    {
        printf( "Nombre d'arguments incorrect. %i\n", argc);
        return -1;
    }

    FILE* file = fopen( argv[0], "r" );
    if( file != NULL )
    {
        unsigned long len;
        char* fileStr = fileToString( file, &len );
        fclose( file );
        char* enc = encryptString( fileStr, len );
        file = fopen( argv[1], "w" );
        writeStringToFile( file, enc );
        fclose( file );
    }
    else
    {
        printf( "Impossible d'ouvrir le fichier %s.\n", argv[0] );
        return -1;
    }

    return 0;
}
