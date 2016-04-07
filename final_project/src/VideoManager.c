#include "VideoManager.h"


void reshape( unsigned int windowWidth, unsigned int windowHeight )
{
    glViewport(0, 0, windowWidth, windowHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10., 10., -10.*(float)windowHeight/(float)windowWidth, 10.*(float)windowHeight/(float)windowWidth);
}


void setVideoMode( unsigned int windowWidth, unsigned int windowHeight )
{
    if( NULL == SDL_SetVideoMode( windowWidth, windowHeight, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE ) )
    {
        fprintf( stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n" );
        exit( EXIT_FAILURE );
    }
}
