#include "Renderer.h"


void loadGraphics( GameObjects* objects )
{
    // Load player's texture
    objects->player.texture = loadTexture( "bin/logo_br.png" );
}


GLuint loadTexture( const char filename[] )
{
    SDL_Surface* surface = IMG_Load( filename );
    if( surface == NULL )
    {
        printf( "Error: \"%s\"\n",SDL_GetError() );
        return;
    }

    GLuint textureID;

    glGenTextures( 1, &textureID );
    glBindTexture( GL_TEXTURE_2D, textureID );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGBA, 20, 20, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels );

    SDL_FreeSurface( surface );

    return textureID;
}


void dessinCarre()
{
    glBegin( GL_POLYGON );
    glTexCoord2f( 0.0, 1.0 );
    glVertex2f( -0.5, 0.5);
    glTexCoord2f( 1.0, 1.0 );
    glVertex2f( 0.5 , 0.5);
    glTexCoord2f( 1.0, 0.0 );
    glVertex2f( 0.5 , -0.5);
    glTexCoord2f( 0.0, 0.0 );
    glVertex2f( -0.5 , -0.5);
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


void updateRender( GameObjects* objects )
{
    glClear(GL_COLOR_BUFFER_BIT);

    /* Placer ici le code de dessin */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef( -objects->player.position.x*2.f, -objects->player.position.y*2.f, 0 );
    dessinRepere();

    glPushMatrix();
    glTranslatef( objects->player.position.x, objects->player.position.y, 0 );
    glTranslatef( objects->player.position.x, objects->player.position.y, 0 );
    glRotatef( objects->player.angle, 0, 0, 1 );


    glEnable (GL_TEXTURE_2D);
    // ... et on indique quelle texture utiliser (celle qui a été créée précédemment).
    glBindTexture (GL_TEXTURE_2D, objects->player.texture );
    // On peut enfin créer un objet (ici un simple carré).
    dessinCarre();
    // Fin de l'application de la texture.
    glDisable (GL_TEXTURE_2D);


    glPopMatrix();

    /* Echange du front et du back buffer : mise Ã  jour de la fenÃªtre */
    SDL_GL_SwapBuffers();
}
