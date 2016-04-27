#include "GameManager.h"


void initGameManager( GameManager* gm )
{
    initWindow( &gm->window );
    gm->isLooping = 1;
    gm->onPause = 0;
    gm->state = ON_MAIN_MENU;

    initEventManager( &gm->eventManager );

/**/
    printf( "\n\n---------- Loading menus ----------\n" );

    gm->scoreList.filename = "bin/scores";
    getScoreList( &gm->scoreList );
    initMenus( &gm->menuManager, &gm->scoreList );

    printf( "---------- Menus Loaded ----------\n\n" );
/**/

/**/
    printf( "---------- Loading game components ----------\n" );

    initGameObjects( &gm->objects );
    initScoreManager( &gm->scoreManager );

    gm->objects.player.collider = getColliderFromFile( "bin/playercollider.collider" );

    initGraphics();
    renderMenuFonts( &gm->menuManager.mainMenu );
    renderMenuFonts( &gm->menuManager.scoresMenu );
    renderMenuFonts( &gm->menuManager.inGamePauseMenu );
    renderMenuFonts( &gm->menuManager.gameOvermenu );

    gm->objects.map.ground = loadMAP( "bin/map.bmp", &gm->objects );
    loadGraphics( &gm->objects );

    printf( "---------- Game components loaded ----------\n\n" );
/**/
}


void startGame( GameManager* gm )
{
    gm->state = ON_GAME;
    initGameObjects( &gm->objects );
    initScoreManager( &gm->scoreManager );
}


void closeGameManager( GameManager* gm )
{
    gm->isLooping = 0;
    free( gm->objects.player.sprite.texturesList );
    freeGraphics();
    freeMapObject( &gm->objects.map );
    freePlayerData( &gm->objects.player );
    saveScore( &gm->scoreManager );
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
            updateMenuRender( gm->menuManager.mainMenu, gm->window.screenSize, 1 );

        break;

        case ON_SCORELIST_MENU :

            action = handleMenuEvents( &gm->menuManager.scoresMenu, gm->window, &gm->eventManager );
            if( action )
                itemAction( action, gm );
            updateMenuRender( gm->menuManager.scoresMenu, gm->window.screenSize, 1 );

        break;

        case ON_GAME :

            handleGameEvents( gm );
            updatePlayerPosition( &gm->objects.player );
            updateCameraPosition( &gm->objects.camera, gm->objects.player );
/*SCORE*/
            gm->scoreManager.currentScore+= 0.1;
            renderScoreFonts( &gm->scoreManager );
            updateScorePosition( &gm->scoreManager, &gm->window );
/*SCORE*/
            Vector2i collid;

            updateGameRender( &gm->objects, &gm->scoreManager, gm->window.screenSize, 0 );

            if( isPlayerCollidingWall( &gm->objects, &collid ) )
                gm->state = ON_DEATH_SCREEN;

        break;

        case ON_PAUSE :

            action = handleMenuEvents( &gm->menuManager.inGamePauseMenu, gm->window, &gm->eventManager );
            if( action )
                itemAction( action, gm );

            updateGameRender( &gm->objects, &gm->scoreManager, gm->window.screenSize, 1 );
            updateMenuRender( gm->menuManager.inGamePauseMenu, gm->window.screenSize, 0 );

        break;

        case ON_DEATH_SCREEN :
            action = handleMenuEvents( &gm->menuManager.gameOvermenu, gm->window, &gm->eventManager );
            if( action )
                itemAction( action, gm );

            updateGameRender( &gm->objects, &gm->scoreManager, gm->window.screenSize, 1 );
            updateMenuRender( gm->menuManager.gameOvermenu, gm->window.screenSize, 0 );
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
        gm->state = ON_PAUSE;

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
        // Bouton Start game
        case 10 :
            startGame( gm );
        break;

        // Bouton High scores
        case 12 :
            clearMenuItems( &gm->menuManager.mainMenu );
            gm->state = ON_SCORELIST_MENU;
        break;

        // Bouton Quit Game
        case 13:
            closeGameManager( gm );
        break;

        // Bouton back ton main menu
        case 22:
            clearMenuItems( &gm->menuManager.scoresMenu );
            gm->state = ON_MAIN_MENU;
        break;

        // Bouton resume game
        case 32:
            clearMenuItems( &gm->menuManager.inGamePauseMenu );
            gm->state = ON_GAME;
        break;

        // Bouton back to game menu
        case 33:
            clearMenuItems( &gm->menuManager.inGamePauseMenu );
            gm->state = ON_MAIN_MENU;
        break;

        // Bouton exit game
        case 34:
            clearMenuItems( &gm->menuManager.inGamePauseMenu );
            closeGameManager( gm );
        break;

        // Restart game
        case 41:
            clearMenuItems( &gm->menuManager.gameOvermenu );
            startGame( gm );
        break;

        // Back to main menu
        case 42:
            clearMenuItems( &gm->menuManager.gameOvermenu );
            gm->state = ON_MAIN_MENU;
        break;

        // exit game
        case 43:
            clearMenuItems( &gm->menuManager.gameOvermenu );
            closeGameManager( gm );
        break;
    }
}
