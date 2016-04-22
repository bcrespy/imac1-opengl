#include "GameManager.h"


void initGameManager( GameManager* gm )
{
    initWindow( &gm->window );
    gm->isLooping = 1;
    gm->onPause = 0;
    gm->state = ON_MAIN_MENU;

    initEventManager( &gm->eventManager );
    initMenus( &gm->menuManager, gm->window.screenSize );

    printf("----------\nLoading game components\n----------\n");

    initGameObjects( &gm->objects );

    gm->objects.player.collider = getColliderFromFile( "bin/playercollider.collider" );

    initGraphics();
    gm->objects.map.ground = loadMAP( "bin/map.bmp", &gm->objects );
    loadGraphics( &gm->objects );

    printf("----------\nGame components loaded\n----------\n");
}


void startGame( GameManager* gm )
{
    gm->state = ON_GAME;
}


void closeGameManager( GameManager* gm )
{
    gm->isLooping = 0;
    free( gm->objects.player.sprite.texturesList );
    freeMapObject( &gm->objects.map );
    freePlayerData( &gm->objects.player );
}


void updateFrame( GameManager* gm )
{
    updateEvents( &gm->eventManager, &gm->window );
    handleGameEvents( gm );

    unsigned int action = 0;

    switch( gm->state )
    {
        case ON_MAIN_MENU :

            action = handleMenuEvents( &gm->menuManager.mainMenu, gm->window, &gm->eventManager );
            if( action )
                itemAction( action, gm );
            updateMainMenuRender( gm->menuManager.mainMenu, gm->window.screenSize );

        break;

        case ON_GAME :

            handleGameEvents( gm );

            updatePlayerPosition( &gm->objects.player );
            updateCameraPosition( &gm->objects.camera, gm->objects.player );

            Vector2i collid;

            updateGameRender( &gm->objects, gm->window.screenSize );

            if( isPlayerCollidingWall( &gm->objects, &collid ) )
                gm->state = ON_PAUSE;

        break;

        case ON_PAUSE :
            
        break;
    }

    /*
    if( gm->onPause == 0 )
    {
        updatePlayerPosition( &gm->objects.player );
        updateCameraPosition( &gm->objects.camera, gm->objects.player );

        Vector2i collid;

        updateGameRender( &gm->objects, gm->window.screenSize );

        if( isPlayerCollidingWall( &gm->objects, &collid ) )
            gm->onPause = 1;
    }*/
}


void handleGameEvents( GameManager* gm )
{
    if( isKeyDown( &gm->eventManager, SDLK_LEFT ) )
        gm->objects.player.angle+= 4;

    if( isKeyDown( &gm->eventManager, SDLK_RIGHT ) )
        gm->objects.player.angle-= 4;

    if( isKeyDown( &gm->eventManager, SDLK_SPACE ) )
        gm->objects.player.motorAcceleration = 1;
    else
        gm->objects.player.motorAcceleration = 0;

    if( isKeyDown( &gm->eventManager, SDLK_ESCAPE ) )
        gm->onPause = 0;

    if( isKeyDown( &gm->eventManager, SDLK_q ) )
        closeGameManager( gm );

    // gestion de la taille de la fenêtre
    if( gm->eventManager.resized )
    {
        resizeWindow( &gm->window );
        gm->eventManager.resized = 0;
    }

    if( gm->eventManager.closeEvent )
        closeGameManager( gm );
}


void itemAction( unsigned int itemID, GameManager* gm )
{
    switch( itemID )
    {
        case 10 :
            startGame( gm );
        break;
    }
}
