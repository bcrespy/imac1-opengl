#ifndef ENGINE_H
#define ENGINE_H


#include "MathsComponents.h"
#include "GameObjects.h"
#include <math.h>
#include <SDL/SDL.h>

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;


// Vitesse en unité par seconde
static const float INITIAL_SPEED = 5.;
static const float MAX_SPEED = 12.;


struct gameengine
{
};

typedef struct gameengine GameEngine;


/*!
 * \brief Updates the player position
 * @param player Reference to the structure containing player's informations
 */
void updatePlayerPosition( PlayerObject* player );


#endif
