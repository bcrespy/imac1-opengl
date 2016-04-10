#include "GameManager.h"


void initGameManager( GameManager* gm, Vector2i windowSize )
{
    setVideoMode( windowSize );
    reshape( windowSize );
    gm->isLooping = 1;
    initGameObjects( &gm->objects );
    initEventManager( &gm->eventManager, windowSize );
    initGraphics();
    loadMAP( "bin/map.bmp", &gm->objects );
    loadGraphics( &gm->objects );
}


void closeGameManager( GameManager* gm )
{
    gm->isLooping = 0;
}


void updateFrame( GameManager* gm, Vector2i windowSize )
{
    updateEvents( &gm->eventManager );
    handleEvents( gm );
    updatePlayerPosition( &gm->objects.player, windowSize );
    updateRender( &gm->objects, windowSize );
}


void handleEvents( GameManager* gm )
{
    if( isKeyDown( &gm->eventManager, SDLK_LEFT ) )
        gm->objects.player.angle+= 4;
    if( isKeyDown( &gm->eventManager, SDLK_RIGHT ) )
        gm->objects.player.angle-= 4;
    if( isKeyDown( &gm->eventManager, SDLK_SPACE ) )
        gm->objects.player.motorAcceleration = 1;
    else
        gm->objects.player.motorAcceleration = 0;

    // gestion de la taille de la fenêtre
    if( gm->eventManager.resized )
    {
        setVideoMode( gm->eventManager.windowSize );
        reshape( gm->eventManager.windowSize );
        gm->eventManager.resized = 0;
    }

    if( gm->eventManager.closeEvent )
        closeGameManager( gm );
}
