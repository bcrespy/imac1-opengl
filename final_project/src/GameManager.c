#include "GameManager.h"


void initGameManager( GameManager* gm )
{
    initWindow( &gm->window );
    gm->isLooping = 1;
    gm->onPause = 0;
    gm->state = ON_MAIN_MENU;

    initEventManager( &gm->eventManager );

    // chargement du curseur
    gm->cursor.id = loadTexture( "bin/cursor.png", &gm->cursor.size, 1 );

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
    initMenuGraphics( &gm->menuManager );

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
    setAllPortalState( &gm->objects, PORTAL_ON );
}


void initMenuGraphics( MenuManager* mm )
{
    renderMenuFonts( &mm->mainMenu );
    renderMenuFonts( &mm->scoresMenu );
    renderMenuFonts( &mm->inGamePauseMenu );
    renderMenuFonts( &mm->gameOvermenu );
    renderMenuFonts( &mm->winMenu );

    renderMenuGraphics( &mm->mainMenu );
    mm->scoresMenu.backgroundSprite = mm->mainMenu.backgroundSprite;
    mm->scoresMenu.spriteSize = mm->mainMenu.spriteSize;
    mm->scoresMenu.buttonTexture.id = loadTexture( "bin/buttonTexture.png", &mm->scoresMenu.buttonTexture.size, 1 );
    mm->scoresMenu.buttonTextureHover.id = loadTexture( "bin/buttonTextureHover.png", &mm->scoresMenu.buttonTextureHover.size, 1 );
    renderMenuGraphics( &mm->inGamePauseMenu );
    renderMenuGraphics( &mm->gameOvermenu );
    renderMenuGraphics( &mm->winMenu );
}


void closeGameManager( GameManager* gm )
{
    gm->isLooping = 0;
    free( gm->objects.player.sprite.texturesList );
    freeGraphics();
    freeMapObject( &gm->objects.map );
    freePlayerData( &gm->objects.player );
}


void updateFrame( GameManager* gm )
{
    updateEvents( &gm->eventManager, &gm->window );
    handleGlobalEvents( gm );

    unsigned int action = 0;

    switch( gm->state )
    {
        case ON_MAIN_MENU :

            action = handleMenuEvents( &gm->menuManager.mainMenu, gm->window, &gm->eventManager );
            if( action )
                itemAction( action, gm );
            updateMenuRender( &gm->menuManager.mainMenu, gm->window.screenSize, 1 );
            updateCursorRender( gm->cursor, gm->eventManager.mousePos, gm->window.size );
            SDL_GL_SwapBuffers();

        break;

        case ON_SCORELIST_MENU :

            action = handleMenuEvents( &gm->menuManager.scoresMenu, gm->window, &gm->eventManager );
            if( action )
                itemAction( action, gm );
            updateMenuRender( &gm->menuManager.scoresMenu, gm->window.screenSize, 1 );
            updateCursorRender( gm->cursor, gm->eventManager.mousePos, gm->window.size );
            SDL_GL_SwapBuffers();

        break;

        case ON_GAME :

            handleGameEvents( gm );
            updatePlayerPosition( &gm->objects.player );
            updateCameraPosition( &gm->objects.camera, gm->objects.player );
/*SCORE*/
            gm->scoreManager.currentScore+= 0.7;
            renderScoreFonts( &gm->scoreManager );
            updateScorePosition( &gm->scoreManager, &gm->window );
/*SCORE*/
            Vector2i collid;

            updateGameRender( &gm->objects, &gm->scoreManager, gm->window.screenSize );
            SDL_GL_SwapBuffers();

            GroundType gdType;
            if( isPlayerColliding( &gm->objects, &collid, &gdType ) )
            {
                if( gdType == WALL )
                {
                    char* t = "You hit a wall";
                    strncpy( gm->menuManager.gameOvermenu.items[1].text, t, sizeof(gm->menuManager.gameOvermenu.items[1].text) );
                    renderMenuFonts( &gm->menuManager.gameOvermenu );
                    renderMenuGraphics( &gm->menuManager.gameOvermenu );
                    gm->state = ON_DEATH_SCREEN;
                }
                else if( gdType == END_LINE )
                {
                    // DECLENCHER ECRAN WIN
                    if( gm->objects.portalsTaken / (float)gm->objects.portalsNb > 0.5f )
                    {
                        addScore( &gm->scoreList, (int)gm->scoreManager.currentScore );
                        saveScore( &gm->scoreManager );

                        MenuObject newScores;
                        initScoreListMenu( &newScores, &gm->scoreList );
                        gm->menuManager.scoresMenu = newScores;
                        renderMenuFonts( &gm->menuManager.scoresMenu );
                        gm->menuManager.scoresMenu.backgroundSprite = gm->menuManager.mainMenu.backgroundSprite;
                        gm->menuManager.scoresMenu.spriteSize = gm->menuManager.mainMenu.spriteSize;
                        gm->menuManager.scoresMenu.buttonTexture.id = loadTexture( "bin/buttonTexture.png", &gm->menuManager.scoresMenu.buttonTexture.size, 1 );
                        gm->menuManager.scoresMenu.buttonTextureHover.id = loadTexture( "bin/buttonTextureHover.png", &gm->menuManager.scoresMenu.buttonTextureHover.size, 1 );

                        char t[20];
                        sprintf( t, "Score : %i", (int)gm->scoreManager.currentScore );
                        strncpy( gm->menuManager.winMenu.items[1].text, t, sizeof(gm->menuManager.winMenu.items[1].text) );
                        renderMenuFonts( &gm->menuManager.winMenu );
                        renderMenuGraphics( &gm->menuManager.winMenu );
                        gm->state = ON_WIN;
                    }
                    else
                    {
                        char* t = "You have to take at least half of the portals";
                        strncpy( gm->menuManager.gameOvermenu.items[1].text, t, sizeof(gm->menuManager.gameOvermenu.items[1].text) );
                        renderMenuFonts( &gm->menuManager.gameOvermenu );
                        renderMenuGraphics( &gm->menuManager.gameOvermenu );
                        gm->state = ON_DEATH_SCREEN;
                    }
                }
            }

            unsigned int portalID;
            if( isPlayerCollidingPortal( &gm->objects, &portalID ) )
            {
                setPortalState( &gm->objects.portals[portalID], PORTAL_OFF );
                gm->objects.portalsTaken++;
                gm->scoreManager.currentScore-= 13;
            }

        break;

        case ON_PAUSE :

            action = handleMenuEvents( &gm->menuManager.inGamePauseMenu, gm->window, &gm->eventManager );
            if( action )
                itemAction( action, gm );

            updateGameRender( &gm->objects, &gm->scoreManager, gm->window.screenSize );
            updateMenuRender( &gm->menuManager.inGamePauseMenu, gm->window.screenSize, 0 );
            updateCursorRender( gm->cursor, gm->eventManager.mousePos, gm->window.size );
            SDL_GL_SwapBuffers();

        break;

        case ON_WIN :

            handleDeathscreenEvents( gm );
            action = handleMenuEvents( &gm->menuManager.winMenu, gm->window, &gm->eventManager );
            if( action )
                itemAction( action, gm );
            updateMenuRender( &gm->menuManager.winMenu, gm->window.screenSize, 1 );
            updateCursorRender( gm->cursor, gm->eventManager.mousePos, gm->window.size );
            SDL_GL_SwapBuffers();

        break;

        case ON_DEATH_SCREEN :
            handleDeathscreenEvents( gm );
            action = handleMenuEvents( &gm->menuManager.gameOvermenu, gm->window, &gm->eventManager );
            if( action )
                itemAction( action, gm );

            updateGameRender( &gm->objects, &gm->scoreManager, gm->window.screenSize );
            updateMenuRender( &gm->menuManager.gameOvermenu, gm->window.screenSize, 0 );
            updateCursorRender( gm->cursor, gm->eventManager.mousePos, gm->window.size );
            SDL_GL_SwapBuffers();
        break;
    }
}


void handleGlobalEvents( GameManager* gm )
{
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
}


void handleDeathscreenEvents( GameManager* gm )
{
    if( isKeyDown( &gm->eventManager, SDLK_r ) )
    {
        clearMenuItems( &gm->menuManager.gameOvermenu );
        startGame( gm );
    }
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
        case 52:
            clearMenuItems( &gm->menuManager.gameOvermenu );
            startGame( gm );
        break;

        // Back to main menu
        case 42:
        case 53:
            clearMenuItems( &gm->menuManager.gameOvermenu );
            gm->state = ON_MAIN_MENU;
        break;

        // exit game
        case 43:
        case 54:
            clearMenuItems( &gm->menuManager.gameOvermenu );
            closeGameManager( gm );
        break;

        // restart game
    }
}
