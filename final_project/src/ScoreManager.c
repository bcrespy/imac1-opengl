#include "ScoreManager.h"


void initScoreManager( ScoreManager* sm )
{
    sm->scorefile = "bin/scores";
    sm->currentScore = 1;
    sm->scoreRendered = 0;
    sm->fontColor.r = 255;
    sm->fontColor.g = 255;
    sm->fontColor.b = 255;
}


void updateScorePosition( ScoreManager* sm, Window* window )
{
    sm->position.x = -window->screenSize.x + 10;
    sm->position.y = window->screenSize.y - 2*sm->texture.size.y - 5;
}


void saveScore( ScoreManager* sm )
{
    FILE* file = fopen( sm->scorefile, "r" );
    unsigned long scoreFileLen;
    char* scoreFileContent = fileToString( file, &scoreFileLen );
    char* decryptedScoreFileContent = decryptString( scoreFileContent, scoreFileLen );
    fclose( file );

    char* newScoreFileContent = appendIntToString( decryptedScoreFileContent, &scoreFileLen, (unsigned int) sm->currentScore );
    char* cryptedScoreFile = encryptString( newScoreFileContent, scoreFileLen );

    file = fopen( sm->scorefile, "w" );
    writeStringToFile( file, cryptedScoreFile );
    fclose( file );
}


void getScoreList( ScoreList* sl )
{
    FILE* scoreFile = fopen( sl->filename, "r" );
    unsigned long scoreFileLen;
    char* scoreFileContent = fileToString( scoreFile, &scoreFileLen );
    char* decryptedScoreFileContent = decryptString( scoreFileContent, scoreFileLen );
    fclose( scoreFile );

    FILE* tempfile = fopen("bin/temp", "w");
    writeStringToFile( tempfile, decryptedScoreFileContent );
    fclose( tempfile );


    FILE* file = fopen( "bin/temp", "r" );
    if( file != NULL )
    {
        sl->scoresNb = 0;
        char buf[20];
        unsigned int t;

        while( fgets( buf, sizeof(buf), file ) != NULL )
            if( sscanf( buf, "%i", &t ) == 1 )
                sl->scoresNb++;

        fclose( file );
        file = fopen( "bin/temp", "r" );

        sl->scores = malloc( sl->scoresNb * sizeof(unsigned int) );

        int i = 0;

        while( fgets( buf, sizeof(buf), file ) != NULL )
            sscanf( buf, "%i", &sl->scores[i++] );

        fclose( file );
    }

    sortScores( sl );
    remove( "bin/temp" );
}


void addScore( ScoreList* sl, unsigned int newScore )
{
    if( sl->scoresNb > 10 )
    {
        if( sl->scores[9] > newScore )
        {
            sl->scores[9] = newScore;
            sortScores( sl );
        }
    }
    else
    {
        sl->scoresNb++;
        sl->scores = (unsigned int*)realloc( sl->scores, sl->scoresNb*sizeof(unsigned int) );
        sl->scores[sl->scoresNb-1] = newScore;
        sortScores( sl );
    }
}


void sortScores( ScoreList* sl )
{
    int i, _i;
    for( _i = 0; _i < sl->scoresNb; _i++ )
        for( i = 0 ; i < sl->scoresNb-1; i++ )
            if( sl->scores[i] > sl->scores[i+1] )
            {
                unsigned int inter = 0;
                inter = sl->scores[i];
                sl->scores[i] = sl->scores[i+1];
                sl->scores[i+1] = inter;
            }
}
