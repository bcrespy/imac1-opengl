#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H


#include <SDL/SDL.h>

#include "GameObjects.h"
#include "Engine.h"
#include "Renderer.h"
#include "EventManager.h"
#include "VideoManager.h"
#include "MenuManager.h"


/*!
    Statut dans lequel le jeu se trouve
*/
typedef enum GameState
{
    ON_MAIN_MENU,
    ON_GAME,
    ON_PAUSE,
    ON_DEATH_ANIMATION,
    ON_DEATH_SCREEN
}
GameState;


/*!
 * Le Game Manager contient les informations
 * et fonctions nécessaires à sa bonne
 * éxécution
 */
typedef struct gamemanager
{
    int isLooping; //!< true tant que le jeu est en fonctionnement
    int onPause; //!< true tant que le jeu est en pause
    GameObjects objects; //!< Main player
    GameEngine engine; //!< Physic engine of the game
    EventManager eventManager; //!< Object évènement principal
    Window window; //!< Informations sur la fenêtre
    MenuManager menuManager; //!< Informations sur les menus
    GameState state; //!< Statut du jeu (menu principal, en jeu, en pause...)
}
GameManager;


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
 * @param windowSize Taille de la fenêtre
 */
void updateFrame( GameManager* gm );


/*!
 * \brief Recupère les évènements et leur associe une action
 * @param gm Pointeur vers le Game Manager
 */
void handleGameEvents( GameManager* gm );


/*!
 * \brief Lance l'action correspondant à un bouton
 * @param itemID ID du bouton dont l'action doit être lancée
 * @param gm Pointeur vers le game manager principal
 */
void itemAction( unsigned int itemID, GameManager* gm );


#endif
