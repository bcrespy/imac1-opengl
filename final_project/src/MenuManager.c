#include "MenuManager.h"


void agenceMenu( MenuObject* menu )
{
    int topY = 0, currentY, i;
    for( i = 0; i < menu->nbItems; i++ )
    {
        menu->items[i].boundingRect.position.x = - menu->items[i].boundingRect.size.x / 2;
        topY+= menu->items[i].marginTop + menu->items[i].boundingRect.size.y;
    }
    currentY = topY / 2 - menu->items[0].boundingRect.size.y;
    for( i = 0; i < menu->nbItems; i++ )
    {
        menu->items[i].boundingRect.position.y = currentY;
        if( i != menu->nbItems-1 )
            currentY-= menu->items[i].boundingRect.size.y + menu->items[i+1].marginTop;
    }
}


void initMainMenu( MenuObject* menu )
{
    menu->font = "bin/slimjoe.ttf";

    menu->texturePath = "bin/menu";
    menu->nbItems = 0;
    menu->items = malloc( 0 );
    menu->isSequence = 1;
    menu->backgroundAlpha = 0;

    Rectanglei buttonBox;
    buttonBox.position.x = 0;
    buttonBox.position.y = 0;
    buttonBox.size.x = BUTTON_SIZE.x;
    buttonBox.size.y = BUTTON_SIZE.y;

    MenuItem startButton = {
        10,
        ITEM_BUTTON,
        ITEM_DEFAULT,
        buttonBox,
        0,
        { 255, 255, 255 },
        30,
        "Start Game"
    };
    addItemToMenu( menu, startButton );

    MenuItem optionsButton = {
        11,
        ITEM_BUTTON,
        ITEM_DEFAULT,
        buttonBox,
        50,
        { 255, 255, 255 },
        30,
        "Options"
    };
    addItemToMenu( menu, optionsButton );

    MenuItem highscoresButton = {
        12,
        ITEM_BUTTON,
        ITEM_DEFAULT,
        buttonBox,
        50,
        { 255, 255, 255 },
        30,
        "Highscores"
    };
    addItemToMenu( menu, highscoresButton );

    MenuItem quitButton = {
        13,
        ITEM_BUTTON,
        ITEM_DEFAULT,
        buttonBox,
        50,
        { 255, 255, 255 },
        30,
        "Quit game"
    };
    addItemToMenu( menu, quitButton );

    agenceMenu( menu );
}


void initScoreListMenu( MenuObject* menu, ScoreList* sl )
{
    // chargement de la font
    menu->font = "bin/slimjoe.ttf";

    menu->texturePath = "";
    menu->nbItems = 0;
    menu->items = malloc( 0 );
    menu->isSequence = 1;
    menu->backgroundAlpha = 0;

    Rectanglei buttonBox;
    buttonBox.position.x = 0;
    buttonBox.position.y = 0;
    buttonBox.size.x = BUTTON_SIZE.x;
    buttonBox.size.y = BUTTON_SIZE.y;

    Rectanglei textBox;
    textBox.position.x = 0;
    textBox.position.y = 0;
    textBox.size.x = 400;
    textBox.size.y = 30;

    MenuItem title = {
        22,
        ITEM_TEXT,
        ITEM_DEFAULT,
        textBox,
        0,
        { 255, 255, 255 },
        50,
        "- Best scores -"
    };
    addItemToMenu( menu, title );

    int i;
    for( i = 0; i < ((sl->scoresNb<10) ? sl->scoresNb : 10); i++ )
    {
        char str[15];
        sprintf( str, "%i", sl->scores[i] );

        MenuItem item = {
            21,
            ITEM_TEXT,
            ITEM_DEFAULT,
            textBox,
            ((i==0)?30:0),
            { 255, 255, 255 },
            30
        };
        strcpy(item.text, str);
        addItemToMenu( menu, item );
    }

    MenuItem backToMenu = {
        22,
        ITEM_BUTTON,
        ITEM_DEFAULT,
        buttonBox,
        100,
        { 255, 255, 255 },
        30,
        "Back to main menu"
    };
    addItemToMenu( menu, backToMenu );

    agenceMenu( menu );
}

void initInGamePauseMenu( MenuObject* menu )
{
    // chargement de la font
    menu->font = "bin/slimjoe.ttf";

    menu->texturePath = "bin/pause_bg.png";
    menu->nbItems = 0;
    menu->items = malloc( 0 );
    menu->isSequence = 0;
    menu->backgroundAlpha = 1;

    Rectanglei buttonBox;
    buttonBox.position.x = 0;
    buttonBox.position.y = 0;
    buttonBox.size.x = BUTTON_SIZE.x;
    buttonBox.size.y = BUTTON_SIZE.y;

    Rectanglei textBox;
    textBox.position.x = 0;
    textBox.position.y = 0;
    textBox.size.x = 400;
    textBox.size.y = 30;

    MenuItem title = {
        31,
        ITEM_TEXT,
        ITEM_DEFAULT,
        textBox,
        0,
        { 255, 255, 255 },
        50,
        "- Game Paused -"
    };
    addItemToMenu( menu, title );

    MenuItem backToGame = {
        32,
        ITEM_BUTTON,
        ITEM_DEFAULT,
        buttonBox,
        100,
        { 255, 255, 255 },
        30,
        "Resume game"
    };
    addItemToMenu( menu, backToGame );

    MenuItem backToMenu = {
        33,
        ITEM_BUTTON,
        ITEM_DEFAULT,
        buttonBox,
        50,
        { 255, 255, 255 },
        30,
        "Back to main menu"
    };
    addItemToMenu( menu, backToMenu );

    MenuItem exitGame = {
        34,
        ITEM_BUTTON,
        ITEM_DEFAULT,
        buttonBox,
        50,
        { 255, 255, 255 },
        30,
        "Exit game"
    };
    addItemToMenu( menu, exitGame );

    agenceMenu( menu );
}


void initGameOverMenu( MenuObject* menu )
{
    // chargement de la font
    menu->font = "bin/slimjoe.ttf";

    menu->texturePath = "bin/menu/00300.jpg";
    menu->nbItems = 0;
    menu->items = malloc( 0 );
    menu->isSequence = 0;
    menu->backgroundAlpha = 0;

    Rectanglei buttonBox;
    buttonBox.position.x = 0;
    buttonBox.position.y = 0;
    buttonBox.size.x = BUTTON_SIZE.x;
    buttonBox.size.y = BUTTON_SIZE.y;

    Rectanglei textBox;
    textBox.position.x = 0;
    textBox.position.y = 0;
    textBox.size.x = 400;
    textBox.size.y = 30;

    MenuItem title = {
        40,
        ITEM_TEXT,
        ITEM_DEFAULT,
        textBox,
        0,
        { 255, 255, 255 },
        50,
        "- Game Over -"
    };
    addItemToMenu( menu, title );

    MenuItem overMsg = {
        600,
        ITEM_TEXT,
        ITEM_DEFAULT,
        textBox,
        20,
        { 255, 255, 255 },
        40,
        "message to be shown when game is over"
    };
    addItemToMenu( menu, overMsg );

    MenuItem restartInfo = {
        601,
        ITEM_TEXT,
        ITEM_DEFAULT,
        textBox,
        20,
        { 255, 255, 255 },
        40,
        "Press R to restart"
    };
    addItemToMenu( menu, restartInfo );

    MenuItem restart = {
        41,
        ITEM_BUTTON,
        ITEM_DEFAULT,
        buttonBox,
        100,
        { 255, 255, 255 },
        30,
        "Restart"
    };
    addItemToMenu( menu, restart );

    MenuItem backToMain = {
        42,
        ITEM_BUTTON,
        ITEM_DEFAULT,
        buttonBox,
        50,
        { 255, 255, 255 },
        30,
        "Back to main menu"
    };
    addItemToMenu( menu, backToMain );

    MenuItem exitGame = {
        43,
        ITEM_BUTTON,
        ITEM_DEFAULT,
        buttonBox,
        50,
        { 255, 255, 255 },
        30,
        "Exit game"
    };
    addItemToMenu( menu, exitGame );

    agenceMenu( menu );
}


void initWinMenu( MenuObject* menu )
{
    // chargement de la font
    menu->font = "bin/slimjoe.ttf";

    menu->texturePath = "bin/menu/00300.jpg";
    menu->nbItems = 0;
    menu->items = malloc( 0 );
    menu->isSequence = 0;
    menu->backgroundAlpha = 0;

    Rectanglei buttonBox;
    buttonBox.position.x = 0;
    buttonBox.position.y = 0;
    buttonBox.size.x = BUTTON_SIZE.x;
    buttonBox.size.y = BUTTON_SIZE.y;

    Rectanglei textBox;
    textBox.position.x = 0;
    textBox.position.y = 0;
    textBox.size.x = 400;
    textBox.size.y = 30;

    MenuItem title = {
        50,
        ITEM_TEXT,
        ITEM_DEFAULT,
        textBox,
        0,
        { 255, 255, 255 },
        50,
        "- You won -"
    };
    addItemToMenu( menu, title );

    MenuItem score = {
        51,
        ITEM_TEXT,
        ITEM_DEFAULT,
        buttonBox,
        50,
        { 255, 255, 255 },
        40,
        " "
    };
    addItemToMenu( menu, score );

    MenuItem restartGame = {
        52,
        ITEM_BUTTON,
        ITEM_DEFAULT,
        buttonBox,
        50,
        { 255, 255, 255 },
        30,
        "Restart"
    };
    addItemToMenu( menu, restartGame );

    MenuItem backToMain = {
        53,
        ITEM_BUTTON,
        ITEM_DEFAULT,
        buttonBox,
        50,
        { 255, 255, 255 },
        30,
        "Back to main menu"
    };
    addItemToMenu( menu, backToMain );

    MenuItem exitGame = {
        54,
        ITEM_BUTTON,
        ITEM_DEFAULT,
        buttonBox,
        50,
        { 255, 255, 255 },
        30,
        "Exit game"
    };
    addItemToMenu( menu, exitGame );

    agenceMenu( menu );
}


void addItemToMenu( MenuObject* menu, MenuItem item )
{
    menu->nbItems++;
    menu->items = realloc( menu->items, menu->nbItems * sizeof(MenuItem) );
    menu->items[menu->nbItems-1] = item;
}


void clearMenuItems( MenuObject* menu )
{
    int i = 0;
    for( ; i < menu->nbItems; i++ )
        menu->items[i].state = ITEM_DEFAULT;
}


void initButton( MenuItem* button, unsigned int id, Rectanglei boundingRect, const char* text )
{
    button->id = id;
    button->boundingRect = boundingRect;
    //button->text = text;
    button->type = ITEM_BUTTON;
}


void initMenus( MenuManager* menuManager, ScoreList* sl )
{
    initMainMenu( &menuManager->mainMenu );
    initScoreListMenu( &menuManager->scoresMenu, sl );
    initInGamePauseMenu( &menuManager->inGamePauseMenu );
    initGameOverMenu( &menuManager->gameOvermenu );
    initWinMenu( &menuManager->winMenu );
}


unsigned int handleMenuEvents( MenuObject* menu, Window window, EventManager* em )
{
    // S'il y a eu un mouvement de souris on recherche s'il y a une collision
    if( em->mouseMove )
    {
        // on clear d'abord le statut des boutons
        clearMenuItems( menu );
        em->mouseMove = 0;

        Vector2i position = getMenuCoor( em->mousePos, window );
        menu->hoveredItem = getHoveringItem( menu, position );
    }

    // traitement du clic
    if( em->leftClick )
    {
        em->leftClick = 0;
        if( menu->hoveredItem != 0 )
            return menu->hoveredItem;
    }

    return 0;
}


unsigned int getHoveringItem( MenuObject* menu, Vector2i position )
{
    int i = 0;
    for( ; i < menu->nbItems; i++ )
    {
        if( menu->items[i].boundingRect.position.x <= position.x &&
            menu->items[i].boundingRect.position.x + menu->items[i].boundingRect.size.x > position.x &&
            menu->items[i].boundingRect.position.y <= position.y &&
            menu->items[i].boundingRect.position.y + menu->items[i].boundingRect.size.y >= position.y )
        {
            menu->items[i].state = ITEM_HOVER;
            return menu->items[i].id;
        }
    }
    return 0;
}


Vector2i getMenuCoor( Vector2i position, Window window )
{
    Vector2i menuPos = { (position.x - window.size.x / 2) * (window.screenSize.x/(float)window.size.x),
                         -( (position.y - window.size.y / 2) * (window.screenSize.x/(float)window.size.x) ) };
    return menuPos;
}
