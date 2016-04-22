#include "MenuManager.h"


void agenceMenu( MenuObject* menu, Vector2i windowSize )
{
    int itemsHeight = 0;
    int i;
    for( i = 0; i < menu->nbItems; i++ )
        itemsHeight+= menu->items[i].boundingRect.size.y;

    int actualY = 0;

    for( i = 0; i < menu->nbItems; i++ )
    {
        menu->items[i].boundingRect.position.x-= menu->items[i].boundingRect.size.x/2;
        menu->items[i].boundingRect.position.y = actualY + (itemsHeight / 2 + (menu->nbItems-1) * SEPARATION_BETWEEN_BUTTONS) / 2;
        actualY-= menu->items[i].boundingRect.size.y + SEPARATION_BETWEEN_BUTTONS;
    }
}


void initMainMenu( MenuObject* menu, Vector2i windowSize )
{
    menu->title = "";
    menu->nbItems = 0;
    menu->items = malloc( 0 );

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
        "Start Game"
    };
    addItemToMenu( menu, startButton );

    MenuItem optionsButton = {
        11,
        ITEM_BUTTON,
        ITEM_DEFAULT,
        buttonBox,
        "Options"
    };
    addItemToMenu( menu, optionsButton );

    MenuItem highscoresButton = {
        12,
        ITEM_BUTTON,
        ITEM_DEFAULT,
        buttonBox,
        "Highscores"
    };
    addItemToMenu( menu, highscoresButton );

    MenuItem quitButton = {
        13,
        ITEM_BUTTON,
        ITEM_DEFAULT,
        buttonBox,
        "Quit game"
    };
    addItemToMenu( menu, quitButton );

    agenceMenu( menu, windowSize );
}


void addItemToMenu( MenuObject* menu, MenuItem item )
{
    menu->nbItems++;
    menu->items = realloc( menu->items, menu->nbItems * sizeof(MenuItem) );
    menu->items[menu->nbItems-1] = item;
}


void initButton( MenuItem* button, unsigned int id, Rectanglei boundingRect, const char* text )
{
    button->id = id;
    button->boundingRect = boundingRect;
    button->text = text;
    button->type = ITEM_BUTTON;
}


void initMenus( MenuManager* menuManager, Vector2i windowSize )
{
    initMainMenu( &menuManager->mainMenu, windowSize );
}


unsigned int handleMenuEvents( MenuObject* menu, Window window, EventManager* em )
{
    unsigned int hoveredItem = 0;

    // S'il y a eu un mouvement de souris on recherche s'il y a une collision
    if( em->mouseMove )
    {
        // on clear d'abord le statut des boutons
        int i = 0;
        for( ; i < menu->nbItems; i++ )
            menu->items[i].state = ITEM_DEFAULT;
        em->mouseMove = 0;

        Vector2i position = getMenuCoor( em->mousePos, window );
        hoveredItem = getHoveringItem( menu, position );
    }

    // traitement du clic
    if( em->leftClick && hoveredItem != 0 )
    {
        em->leftClick = 0;
        return hoveredItem;
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
