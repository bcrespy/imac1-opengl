#include "GameManager.h"


void initGameManager( GameManager* gm )
{
    initWindow( &gm->window );
    gm->isLooping = 1;
    initGameObjects( &gm->objects );
    initEventManager( &gm->eventManager );
    initGraphics();
    loadMAP( "bin/map.bmp", &gm->objects );
    loadGraphics( &gm->objects );
}


void closeGameManager( GameManager* gm )
{
    gm->isLooping = 0;
}


void updateFrame( GameManager* gm )
{
    updateEvents( &gm->eventManager, &gm->window );
    handleEvents( gm );
    updatePlayerPosition( &gm->objects.player, gm->window.size );
    updateCameraPosition( &gm->objects.camera, gm->objects.player );
    updateRender( &gm->objects, gm->window.size );
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
        resizeWindow( &gm->window );
        gm->eventManager.resized = 0;
    }

    if( gm->eventManager.closeEvent )
        closeGameManager( gm );
}
