#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H


#include <SDL/SDL.h>
#include "GameObjects.h"
#include "Engine.h"
#include "Renderer.h"
#include "EventManager.h"


/*!
    Le Game Manager contient les informations
    et fonctions nécessaires à sa bonne
    éxécution
*/
struct gamemanager
{
    int isLooping; //!< true tant que le jeu est en fonctionnement
    GameObjects objects; //!< Main player
    GameEngine engine; //!< Physic engine of the game
    EventManager eventManager; //!< Handle the events
};

typedef struct gamemanager GameManager;


/*!
 * \brief Initialise le Game Manager tranmis en paramètre
 * @param gm Pointeur vers Game Manager qui doit être initialisé
 */
void initGameManager( GameManager* gm );


/*!
 * \brief S'assure que le Game Manager se ferme correctement
 * @param gm Pointeur vers Game Manager qui doit être fermé
 */
void closeGameManager( GameManager* gm );


/*!
 * \brief Fonction appelée à chaque frame du contexte OpenGL
 * @param gm Pointeur vers le Game Manager
 */
void updateFrame( GameManager* gm );


/*!
 * \brief Recupère les évènements et leur associe une action
 * @param gm Pointeur vers le Game Manager
 */
void handleEvents( GameManager* gm );


#endif