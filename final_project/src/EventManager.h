#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H


#include <SDL/SDL.h>
#include "VideoManager.h"

#define NB_KEYS 500

typedef unsigned char Byte;

struct eventmanager
{
    Byte keysDown[NB_KEYS];
    unsigned int closeEvent;
    unsigned int leftClick;
};

typedef struct eventmanager EventManager;


/*!
 * \brief Initialize the event manager
 */
void initEventManager( EventManager* em );


/*!
 * \brief Retourne true si la touche est enfoncée
 */
unsigned int isKeyDown( EventManager* em, unsigned int keyCode );


void updateEvents( EventManager* em );


#endif
