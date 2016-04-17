#include "GameManager.h"


void initGameManager( GameManager* gm )
{
    initWindow( &gm->window );
    gm->isLooping = 1;
    initGameObjects( &gm->objects );

    gm->objects.player.collider = getColliderFromFile( "bin/playercollider.collider" );

    initEventManager( &gm->eventManager );
    initGraphics();
    gm->objects.map.ground = loadMAP( "bin/map.bmp", &gm->objects );
    loadGraphics( &gm->objects );
}


void closeGameManager( GameManager* gm )
{
    gm->isLooping = 0;
    free( gm->objects.player.sprite.texturesList );
    //! TODO free gm objects map ground
}


void updateFrame( GameManager* gm )
{
    updateEvents( &gm->eventManager, &gm->window );
    handleEvents( gm );
    updatePlayerPosition( &gm->objects.player, gm->window.size );
    updateCameraPosition( &gm->objects.camera, gm->objects.player );

    Vector2i collid;


    updateRender( &gm->objects, gm->window.size );
    if( isPlayerCollidingWall( &gm->objects, &collid ) )
        closeGameManager( gm );
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
