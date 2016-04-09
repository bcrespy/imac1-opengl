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
    loadMapGraphics( &objects->map, "bin/map.png" );
}


void loadMapGraphics( MapObject* map, const char filename[] )
{
    Vector2i mapSize;
    map->texture = loadTexture( filename, &mapSize, 0 );
    map->size.x = mapSize.x;
    map->size.y = mapSize.y;
    map->proportion = map->size.y / ((float)map->size.x);
}


GLuint loadTexture( const char filename[], Vector2i *textureSize, int alpha )
{
    SDL_Surface* surface = IMG_Load( filename );
    if( surface == NULL )
    {
        printf( "Error: \"%s\"\n",SDL_GetError() );
        return;
    }

    GLint type = (alpha) ? GL_RGBA : GL_RGB;

    GLuint textureID;
    textureSize->x = surface->w;
    textureSize->y = surface->h;

    glGenTextures( 1, &textureID );
    glBindTexture( GL_TEXTURE_2D, textureID );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D( GL_TEXTURE_2D, 0, type, surface->w, surface->h, 0, type, GL_UNSIGNED_BYTE, surface->pixels );

    printf( "Texture %s [%d;%d] loaded\n", filename, surface->w, surface->h );

    SDL_FreeSurface( surface );

    return textureID;
}


void dessinCarre( Vector2i playerSize, Vector2i window )
{
    Vector2f playerSizeGL;
    playerSizeGL.x = ( ((float)playerSize.x) / window.x );
    playerSizeGL.y = playerSizeGL.x * ( ((float)playerSize.y) / playerSize.x );

    glBegin( GL_POLYGON );
    glTexCoord2f( 1.0, 1.0 );
    glVertex2f( -playerSizeGL.x, playerSizeGL.y );
    glTexCoord2f( 0.0, 1.0 );
    glVertex2f( playerSizeGL.x, playerSizeGL.y );
    glTexCoord2f( 0.0, 0.0 );
    glVertex2f( playerSizeGL.x, -playerSizeGL.y );
    glTexCoord2f( 1.0, 0.0 );
    glVertex2f( -playerSizeGL.x, -playerSizeGL.y );
    glEnd();
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


void renderMap( MapObject* map, Vector2i windowSize )
{
    Vector2f mapSizeGL;
    mapSizeGL.x = ( ((float)map->size.x) / windowSize.x );
    mapSizeGL.y = mapSizeGL.x * ( ((float)map->size.y) / map->size.x );

    glEnable( GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D, map->texture );
    glBegin( GL_POLYGON );
    glTexCoord2f( 0.0, 0.0 );
    glVertex2f( -mapSizeGL.x, mapSizeGL.y );
    glTexCoord2f( 1.0, 0.0 );
    glVertex2f( mapSizeGL.x, mapSizeGL.y );
    glTexCoord2f( 1.0, 1.0 );
    glVertex2f( mapSizeGL.x, -mapSizeGL.y );
    glTexCoord2f( 0.0, 1.0 );
    glVertex2f( -mapSizeGL.x, -mapSizeGL.y );
    glEnd();
    glDisable (GL_TEXTURE_2D);
}


void updateRender( GameObjects* objects, Vector2i windowSize )
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //glTranslatef( -objects->player.position.x, -objects->player.position.y, 0 );
    dessinRepere();

    renderMap( &objects->map, windowSize );

    glPushMatrix();
    //glTranslatef( objects->player.position.x, objects->player.position.y, 0 );
    //glTranslatef( objects->player.position.x, objects->player.position.y, 0 );
    //glRotatef( objects->player.angle, 0, 0, 1 );


    glEnable (GL_TEXTURE_2D);
    glBindTexture (GL_TEXTURE_2D, objects->player.texture );
    dessinCarre( objects->player.size, windowSize );
    glDisable (GL_TEXTURE_2D);


    glPopMatrix();

    /* Echange du front et du back buffer : mise Ã  jour de la fenÃªtre */
    SDL_GL_SwapBuffers();
}
