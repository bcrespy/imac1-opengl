#include "VideoManager.h"


void reshape( Vector2i windowSize )
{
    int height = (9/16.0f) * windowSize.x;
    glViewport(0, 0, windowSize.x, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1., 1., -1.*(float)height/(float)windowSize.x, 1.*(float)height/(float)windowSize.x);
}


void setVideoMode( Vector2i windowSize )
{
    int height = (9/16.0f) * windowSize.x;
    if( NULL == SDL_SetVideoMode( windowSize.x, height, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE ) )
    {
        fprintf( stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n" );
        exit( EXIT_FAILURE );
    }
}
