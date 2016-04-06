#include "GameManager.h"


void initGameManager( GameManager* gm )
{
    gm->isLooping = 1;

    gm->objects.player.position.x = 0;
    gm->objects.player.position.y = 0;
    gm->objects.player.velocity.x = 0;
    gm->objects.player.velocity.y = 0;
    gm->objects.player.motor.x = 0;
    gm->objects.player.motor.y = 0;
    gm->objects.player.angle = 0;
    gm->objects.player.motorAcceleration = 0;

    initEventManager( &gm->eventManager );
}


void closeGameManager( GameManager* gm )
{
    gm->isLooping = 0;
}


void updateFrame( GameManager* gm )
{
    updateEvents( &gm->eventManager );
    handleEvents( gm );
    updatePlayerPosition( &gm->objects.player );
    updateRender( &gm->objects );
}


void handleEvents( GameManager* gm )
{
    if( isKeyDown( &gm->eventManager, SDLK_LEFT ) )
        gm->objects.player.angle+= 3;
    if( isKeyDown( &gm->eventManager, SDLK_RIGHT ) )
        gm->objects.player.angle-= 3;
    if( isKeyDown( &gm->eventManager, SDLK_SPACE ) )
        gm->objects.player.motorAcceleration = 1;
    else
        gm->objects.player.motorAcceleration = 0;

    if( gm->eventManager.closeEvent )
        closeGameManager( gm );
}
