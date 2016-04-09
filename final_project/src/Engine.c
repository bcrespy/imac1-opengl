#include "Engine.h"


void updatePlayerPosition( PlayerObject* player, Vector2i window )
{
    // Force du moteur en pixels / s
    player->motor.x = sin( -player->angle * M_PI / 180 ) * ( INITIAL_SPEED + (MAX_SPEED-INITIAL_SPEED) * player->motorAcceleration );
    player->motor.y = cos( -player->angle * M_PI / 180 ) * ( INITIAL_SPEED + (MAX_SPEED-INITIAL_SPEED) * player->motorAcceleration );
    player->velocity.x = 0.98*player->velocity.x + 0.02*player->motor.x;
    player->velocity.y = 0.98*player->velocity.y + 0.02*player->motor.y;

    // Passage dans le repère openGL
    Vector2f movement;
    movement.x = (player->velocity.x / (float)window.x);
    movement.y = (player->velocity.y / (float)window.x);

    //player->position.x+= (FRAMERATE_MILLISECONDS / 1000.0) * movement.x;
    //player->position.y+= (FRAMERATE_MILLISECONDS / 1000.0) * movement.y;

    player->position.x = 0.1f;
    player->position.y = 0.1f;

    printf( "[%f;%f]\n", player->position.x, player->position.y );
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
