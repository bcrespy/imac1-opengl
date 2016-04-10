#include "VideoManager.h"


void initWindow( Window* window )
{
    window->size.x = WINDOW_WIDTH;
    window->size.y = WINDOW_HEIGHT;
    SDL_WM_SetCaption( "Jeu super bien", NULL );
    resizeWindow( window );
}


void resizeWindow( Window *window )
{
    window->size.y = (9/16.0f) * window->size.x;
    reshape( window->size );
    setVideoMode( window->size );
}


void reshape( Vector2i windowSize )
{
    glViewport(0, 0, windowSize.x, windowSize.y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1., 1., -1.*(float)windowSize.y/(float)windowSize.x, 1.*(float)windowSize.y/(float)windowSize.x);
}


void setVideoMode( Vector2i windowSize )
{
    if( NULL == SDL_SetVideoMode( windowSize.x, windowSize.y, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE ) )
    {
        fprintf( stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n" );
        exit( EXIT_FAILURE );
    }
}
