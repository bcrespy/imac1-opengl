#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "VideoManager.h"
#include "MathsComponents.h"
#include "GameManager.h"
#include "Renderer.h"



// Dimensions de la fenêtre
static const int WINDOW_WIDTH = 1280;
static const int WINDOW_HEIGHT = 720;


int main( int argc, char** argv )
{
    // Initialisation de la SDL
    if( -1 == SDL_Init( SDL_INIT_VIDEO ) )
    {
        fprintf( stderr, "Impossible d'initialiser la SDL. Fin du programme.\n" );
        return EXIT_FAILURE;
    }

    // Redirection du flux de sortie pour qu'il s'affiche dans la console
    //( "CON", "w", stdout );

    // Initialisation du GameManager
    GameManager gm;
    Vector2i window; window.x = WINDOW_WIDTH; window.y = WINDOW_HEIGHT;
    initGameManager( &gm, window );

    // Titre de la fenÃªtre
    SDL_WM_SetCaption( "Jeu super bien", NULL );

    Uint32 startTime;

    while( gm.isLooping )
    {
        // Récupération du temps au début de la boucle */
        startTime = SDL_GetTicks();

        // On update la frame
        updateFrame( &gm, gm.eventManager.windowSize );

        // Calcul du temps écoulé
        Uint32 elapsedTime = SDL_GetTicks() - startTime;

        // Si trop peu de temps s'est écoulé, on met en pause le programme
        if( elapsedTime < FRAMERATE_MILLISECONDS )
            SDL_Delay( FRAMERATE_MILLISECONDS - elapsedTime );
    }

    // Liberation des ressources associées Ã  la SDL
    SDL_Quit();

    return EXIT_SUCCESS;
}
