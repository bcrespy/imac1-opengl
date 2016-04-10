#include "Engine.h"


void updatePlayerPosition( PlayerObject* player, Vector2i window )
{
    // Force du moteur en pixels / s
    player->motor.x = sin( -player->angle * M_PI / 180 ) * ( INITIAL_SPEED + (MAX_SPEED-INITIAL_SPEED) * player->motorAcceleration );
    player->motor.y = cos( -player->angle * M_PI / 180 ) * ( INITIAL_SPEED + (MAX_SPEED-INITIAL_SPEED) * player->motorAcceleration );
    player->velocity.x = 0.985*player->velocity.x + 0.015*player->motor.x;
    player->velocity.y = 0.985*player->velocity.y + 0.015*player->motor.y;

    // Passage dans le repère openGL
    /*Vector2f movement;
    movement.x = (player->velocity.x / window.x/2.0);
    movement.y = (player->velocity.y / window.x/2.0);*/

    player->position.x+= (1.0/60.0) * player->velocity.x;
    player->position.y+= (1.0/60.0) * player->velocity.y;

    //printf( "[%f;%f]\n", player->velocity.x, player->velocity.y );
}


void updateCameraPosition( CameraObject* camera, PlayerObject player )
{
    camera->position.x+= ( player.position.x - camera->position.x ) / (float)FRAMES_NB_TO_MOVE_CAMERA;
    camera->position.y+= ( player.position.y - camera->position.y ) / (float)FRAMES_NB_TO_MOVE_CAMERA;
}


void loadMAP( const char filename[], GameObjects* objects )
{
    SDL_Surface* surface = SDL_LoadBMP( filename );
    if( surface == NULL )
    {
        printf( "Error: \"%s\"\n",SDL_GetError() );
        return;
    }

    int x, y;

    for( y = 0; y < surface->h; y++ )
    {
        for( x = 0; x < surface->w; x++ )
        {
            Uint32 pixel = getPixelFromSurface( surface, x, y );
            Uint8 r, g, b, a;
            SDL_GetRGBA( pixel, surface->format, &r, &g, &b, &a );

            // traitement des objets en fonction de la couleur du pixel
            if( r == 255 && b == 0 && g == 0 )
            {
                objects->walls[objects->wallsNb].position.x = x;
                objects->walls[objects->wallsNb].position.x = y;
                objects->wallsNb++;
            }
        }
    }

    printf( "Map loaded : %d murs\n", objects->wallsNb );
}


Uint32 getPixelFromSurface( SDL_Surface *surface, int x, int y )
{
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * surface->format->BytesPerPixel;

    switch( surface->format->BytesPerPixel )
    {
        case 1:
            return *p;

        case 2:
            return *(Uint16 *)p;

        case 3:
            if( SDL_BYTEORDER == SDL_BIG_ENDIAN )
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;

        case 4:
            return *(Uint32 *)p;
    }
}
