#ifndef ENGINE_H
#define ENGINE_H


#include "MathsComponents.h"
#include "GameObjects.h"
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>


// Nombre minimal de millisecondes separant le rendu de deux images
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;


// Vitesse en pixels / s
static const float INITIAL_SPEED = 1000.;
static const float MAX_SPEED = 1000.;


struct gameengine
{
};

typedef struct gameengine GameEngine;


/*!
 * \brief Updates the player position
 * @param player Reference to the structure containing player's informations
 */
void updatePlayerPosition( PlayerObject* player, Vector2i windowSize );


/*!
 * \brief Parse la map et crée les Game Objects correspondant
 * @param filename Chemin vers le fichier MAP
 * @param objects Pointeur vers la liste d'objets du jeu
 */
void loadMAP( const char filename[], GameObjects* objects );


/*!
 * \brief Récupère le pixel d'une surface en [x;y]
 * @param surface Pointeur vers la surface contenant les informations de l'image à parcourir
 * @param x coordonnée X du pixel
 * @param y coordonnée Y du pixel
 * @return Le pixel aux coordonnées [x;y]
 */
Uint32 getPixelFromSurface( SDL_Surface *surface, int x, int y );


#endif
