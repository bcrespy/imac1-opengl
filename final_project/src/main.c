/*
    TODO : Background des boutons
    TODO : Background des menus
    TODO : Implantation des portails
*/

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




int main( int argc, char** argv )
{
    // Initialisation de la SDL
    if( -1 == SDL_Init( SDL_INIT_VIDEO ) )
    {
        fprintf( stderr, "Impossible d'initialiser la SDL. Fin du programme.\n" );
        return EXIT_FAILURE;
    }

    // Redirection du flux de sortie pour qu'il s'affiche dans la console
    freopen( "CON", "w", stdout );

    // Initialisation du GameManager
    GameManager gm;
    initGameManager( &gm );

    Uint32 startTime;

    while( gm.isLooping )
    {
        // Récupération du temps au début de la boucle */
        startTime = SDL_GetTicks();

        // On update la frame
        updateFrame( &gm );

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
