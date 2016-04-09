#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H


#include <SDL/SDL.h>
#include "VideoManager.h"
#include "MathsComponents.h"

#define NB_KEYS 500

typedef unsigned char Byte;


/*!
 * Contient les différentes variable permettant la gestion des évènements
 */
struct eventmanager
{
    Byte keysDown[NB_KEYS]; //!< Tableau de booléens pour chaque touche du clavier
    unsigned int resized; //!< True s'il y a eu un resize à la frame précédente
    Vector2i windowSize; //!< Taille de la fenêtre
    unsigned int closeEvent; //!< Passe à true si l'utilisateur a trigger une fermeture
    unsigned int leftClick; //!< True tant que l'utilisateur clique sur le bouton gauche
};

typedef struct eventmanager EventManager;


/*!
 * \brief Initialize the event manager
 * @param em Pointeur vers le manager d'évènements principal
 */
void initEventManager( EventManager* em );


/*!
 * \brief Retourne true si la touche keyCode est enfoncée
 * @param em Manager d'évènements principal
 * @param keyCode SDL_Keycode de la touche à tester
 */
unsigned int isKeyDown( EventManager* em, unsigned int keyCode );


/*!
 * \biref Fonction appelée à chaque frame du contexte OpengGL
 *        Gère la modification du Manager d'évènements en fonction des inputs de l'utilisateur
 */
void updateEvents( EventManager* em );


#endif
