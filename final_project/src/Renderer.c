#include "Renderer.h"


void initGraphics()
{
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
}


void loadGraphics( GameObjects* objects )
{
    // Load player's texture
    Vector2i size;
    objects->player.texture = loadTexture( "bin/yout.png", &size, 1 );
    objects->player.size.x = size.x;
    objects->player.size.y = size.y;
    loadMapGraphics( &objects->map, "bin/map2.png" );
    objects->player.sprite.texturesList = loadSequence( "bin/menu", &objects->player.sprite.nbTextures, &objects->player.size, 0 );
    objects->player.sprite.currentTexture = 0;
}


void loadMapGraphics( MapObject* map, const char filename[] )
{
    Vector2i mapSize;
    map->texture = loadTexture( filename, &mapSize, 0 );
    map->size.x = mapSize.x;
    map->size.y = mapSize.y;
    map->proportion = map->size.y / ((float)map->size.x);
}


Vector2f gameCooriToGLCoor( Vector2i vec, Vector2i windowSize )
{
    Vector2f vecGL;
    vecGL.x = ( ((float)vec.x) / windowSize.x );
    vecGL.y = ( ((float)vec.y) / windowSize.x );
    return vecGL;
}


Vector2f gameCoorfToGLCoor( Vector2f vec, Vector2i windowSize )
{
    Vector2f vecGL;
    vecGL.x = ( vec.x / windowSize.x );
    vecGL.y = ( vec.y / windowSize.x );
    return vecGL;
}


GLuint loadTexture( const char filename[], Vector2i *textureSize, int alpha )
{
    SDL_Surface* surface = IMG_Load( filename );
    if( surface == NULL )
    {
        printf( "Error: \"%s\"\n",SDL_GetError() );
    }

    GLint type = (alpha) ? GL_RGBA : GL_RGB;

    GLuint textureID;
    textureSize->x = surface->w;
    textureSize->y = surface->h;

    glGenTextures( 1, &textureID );
    glBindTexture( GL_TEXTURE_2D, textureID );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glTexImage2D( GL_TEXTURE_2D, 0, type, surface->w, surface->h, 0, type, GL_UNSIGNED_BYTE, surface->pixels );

    printf( "Texture %s [%d;%d] loaded\n", filename, surface->w, surface->h );

    SDL_FreeSurface( surface );

    return textureID;
}


GLuint* loadSequence( const char folderpath[], int* nbFrames, Vector2i* textureSize, int alpha )
{
    DIR* direc = NULL;
    direc = opendir( folderpath );
    struct dirent* file = NULL;

    if( direc == NULL )
    {
        printf( "Can't open the folder \"%s\"\n", folderpath );
        exit(1);
    }

    // On compte le nombre de fichiers de la séquence
    *nbFrames = 0;
    while( (file = readdir( direc )) != NULL )
        if( strcmp(file->d_name, ".") != 0 && strcmp(file->d_name, "..") != 0 )
            (*nbFrames)++;

    closedir( direc );
    direc = opendir( folderpath );

    GLuint* texturesList = malloc( (*nbFrames) * sizeof(GLuint) );
    char filepath[50];

    // On charge les textures de la séquence
    int parser = 0;
    while( (file = readdir( direc )) != NULL )
    {
        if( strcmp(file->d_name, ".") != 0 && strcmp(file->d_name, "..") != 0 )
        {
            strcat( filepath, folderpath );
            strcat( filepath, "/" );
            strcat( filepath, file->d_name );
            texturesList[parser] = loadTexture( filepath, textureSize, alpha );
            memset( filepath, 0, 50 );
            parser++;
        }
    }

    if( closedir(direc) == -1 )
    {
        printf( "Error when closing the directory \"%s\"\n", folderpath );
        exit(1);
    }

    return texturesList;
}


GLuint getNextTextureFromSequence( Sequence* seq )
{
    if( seq->currentTexture >= seq->nbTextures-1 )
        seq->currentTexture = 0;
    else
        seq->currentTexture++;

    return seq->texturesList[seq->currentTexture];
}


void dessinRepere()
{
    glBegin( GL_LINES );
    glVertex2f( 0, 0 );
    glVertex2f( 1, 0 );
    glVertex2f( 0, 0 );
    glVertex2f( 0, 1 );
    glEnd();
}


void renderRect( Vector2f rectSize )
{
    glBegin( GL_POLYGON );
    glTexCoord2f( 0.0, 0.0 );
    glVertex2f( -rectSize.x, rectSize.y );
    glTexCoord2f( 1.0, 0.0 );
    glVertex2f( rectSize.x, rectSize.y );
    glTexCoord2f( 1.0, 1.0 );
    glVertex2f( rectSize.x, -rectSize.y );
    glTexCoord2f( 0.0, 1.0 );
    glVertex2f( -rectSize.x, -rectSize.y );
    glEnd();
}


void updateRender( GameObjects* objects, Vector2i windowSize )
{
    Vector2f playerPosGL = gameCoorfToGLCoor( objects->player.position, windowSize );
    Vector2f cameraPosGL = gameCoorfToGLCoor( objects->camera.position, windowSize );

    glClear( GL_COLOR_BUFFER_BIT );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    // Gestion de la caméra
    glTranslatef( -cameraPosGL.x*2, -cameraPosGL.y*2, 0 );
    dessinRepere();

    glEnable( GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D, objects->map.texture );
    renderRect( gameCooriToGLCoor( objects->map.size, windowSize ) );
    glDisable( GL_TEXTURE_2D );

    glPushMatrix();
    glTranslatef( playerPosGL.x, playerPosGL.y, 0 );
    glTranslatef( playerPosGL.x, playerPosGL.y, 0 );
    glRotatef( objects->player.angle, 0, 0, 1 );


    glEnable( GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D, getNextTextureFromSequence( &objects->player.sprite ) );
    renderRect( gameCooriToGLCoor( objects->player.size, windowSize ) );
    glDisable( GL_TEXTURE_2D );


    glPopMatrix();

    /* Echange du front et du back buffer : mise Ã  jour de la fenÃªtre */
    SDL_GL_SwapBuffers();
}
