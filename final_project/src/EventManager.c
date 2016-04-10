#include "EventManager.h"


void initEventManager( EventManager* em )
{
    em->closeEvent = 0;
    em->leftClick = 0;

    int key_nb;
    for( key_nb = 0; key_nb < NB_KEYS; key_nb++ )
        em->keysDown[key_nb] = 0;
}


unsigned int isKeyDown( EventManager* em, unsigned int keyCode )
{
    return em->keysDown[keyCode];
}


void updateEvents( EventManager* em, Window* window )
{
    /* Boucle traitant les evenements */
    SDL_Event e;

    while( SDL_PollEvent(&e) )
    {
        /* L'utilisateur ferme la fenÃªtre : */
        if( e.type == SDL_QUIT )
        {
            em->closeEvent = 1;
            break;
        }

        switch( e.type )
        {
                /* Clic souris */
            case SDL_MOUSEBUTTONUP:
                em->leftClick = 1;
                break;

            case SDL_MOUSEBUTTONDOWN:
                em->leftClick = 0;
                break;

                /* Touche clavier */
            case SDL_KEYDOWN:
                em->keysDown[e.key.keysym.sym] = 1;
                break;

            case SDL_KEYUP:
                em->keysDown[e.key.keysym.sym] = 0;
                break;

            case SDL_VIDEORESIZE:
                em->resized = 1;
                window->size.x = e.resize.w;
                window->size.y = e.resize.h;
                break;


            default:
                break;
        }
    }
}
