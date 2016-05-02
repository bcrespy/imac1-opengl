/*!
 * Gestion avancée des menus
 * Propose une interface de création des menus
 * et les fonctions permettant de gérer cette dernière
 */

#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include <GL/gl.h>
#include <SDL/SDL.h>

#include "VideoManager.h"
#include "EventManager.h"
#include "MathsComponents.h"
#include "GeometryComponents.h"
#include "Graphics.h"
#include "ScoreManager.h"
#include "GameObjects.h"


static const unsigned int SEPARATION_BETWEEN_BUTTONS = 50;
static const Vector2i BUTTON_SIZE = { 560, 83 };


/*!
 * L'objectif du menu manager est de gérer le menu pincipal du jeu
 * Il permet de gérer les options du jeu et l'affichage du menu
 * Il gère les évènements liés au menu et interragit avec le reste du jeu
 * -----------
 * Le menu est composé de groupes d'entrées, chaque entrée appelant une action particulière (ex: lancer le jeu)
 */

/*!
 * Liste des id des items des menus
 * --------------
 * 10 : Bouton Start Game
 * 11 : Bouton Options
 * 12 : Bouton Highscores
 * 13 : Bouton Quit game
 * --------------
 * 21 : Liste des scores
 * 22 : Bouton Back to main menu
 * --------------
 * 31 : Pause menu
 * 32 : Back to game button
 * 33 : Back to main menu button
 * 34 : Exit game
 * --------------
 * 40 : Game Over Menu
 * 41 : Restart
 * 42 : Back to main menu
 * 43 : Exit game
 * --------------
 * 50 : Win menu
 * 51 : Affichage score
 * 52 : Restart
 * 53 : Back to main menu
 * 54 : exit game
 *
 */


/*!
 * Liste des différents types d'item que l'on peut avoir dans un menu
 */
typedef enum menuitemtype
{
    ITEM_BUTTON,    //!< Bouton cliquable
    ITEM_CHECKBOX,  //!< Checkbox cochable
    ITEM_TEXT       //!< Simple texte sans action spécifique
}
MenuItemType;


/*!
 * Liste des différents états dans lequel peut être un ITEM
 */
typedef enum menuitemstate
{
    ITEM_DEFAULT,
    ITEM_HOVER,
    ITEM_CLICKED,
    ITEM_CHECKED
}
MenuItemState;


/*!
 * Structure d'un item du Menu
 */
typedef struct menuitem
{
    unsigned int id; //!< En fonction de l'id de l'item, il aura une action spécifique
    MenuItemType type; //!< En fonction du type d'item, il aura un affichage/comportement différent
    MenuItemState state; //!< En fonction de l'état dans lequel l'item est, il apparaitra différemment
    Rectanglei boundingRect; //!< Boite de collision de l'item, définit la zone d'intérêt
    unsigned int marginTop; //!< Marge supérieur de l'item
    SDL_Color fontColor; //!< Couleur du texte de l'item
    unsigned int fontSize; //!< Taille de la police de l'item
    char text[255]; //!< Texte correspondant au menu
    TextureInformations fontTexture; //!< Informations sur la texture de la police
    Vector2i fontTexturePosition; //!< Nécessaire pour centrer le texte dans le bouton
}
MenuItem;

/*!
 * \brief Initialise un bouton en fonction des paramètres
 *        Fonction plus utilisée mais toujours présente en cas de besoin
 *        d'initialisation rapide d'un bouton
 * @param button Pointeur vers le bouton à initialiser
 * @param id Identifiant unique du bouton
 * @param boundingRect Boite de collisions du bouton
 * @param text Texte affiché dans le bouton
 */
void initButton( MenuItem* button, unsigned int id, Rectanglei boundingRect, const char* text );


/*!
 * Structure d'un Menu
 */
typedef struct menuobject
{
    char* texturePath; //!< Titre du menu -- sera affiché tout en haut
    MenuItem* items; //!< Liste des items du menu
    unsigned int nbItems; //!< Nombre d'items du menu
    const char* font; //!< Police des items du menu
    unsigned int hoveredItem; //!< ID du bouton hovered - 0 si aucun
    unsigned int isSequence; //!< Si le background est une séquence ou non
    TextureInformations background; //!< Informations sur la texture background du menu
    int backgroundAlpha; //!< Si le background a une couche Alpha
    Sequence backgroundSprite; //!< Séquence de background du menu
    Vector2i spriteSize; //!< Taille du background
    TextureInformations buttonTexture; //!< Texture générique d'un bouton
    TextureInformations buttonTextureHover; //!< Texture générique d'un bouton lors du hover
}
MenuObject;

/*!
 * \brief Ajoute un item dans un objet menu
 * @param menu Pointeur vers le mnu dans lequel un item doit être ajouté
 * @param item Item déjà initialisé
 */
void addItemToMenu( MenuObject* menu, MenuItem item );

/*!
 * \brief Nettoie le statut des items du menu
 * @param menu Pointeur vers le menu à clear
 */
void clearMenuItems( MenuObject* menu );

/*!
 * \brief Initialise le mnu principal du jeu
 * @param menu Pointeur vers l'objet menu à initialiser
 */
void initMainMenu( MenuObject* menu );

/*!
 * \brief Initialise le menu de la liste des scores
 * @param menu Pointeur vers l'objet menu à initialiser
 * @param scoreList Pointeur vers la liste des scores
 */
void initScoreListMenu( MenuObject* menu, ScoreList* scoreList );

/*!
 * \brief Initialise le menu de pause in-game
 * @param menu Pointeur vers l'objet menu à initialiser
 */
void initInGamePauseMenu( MenuObject* menu );

/*!
 * \brief Initialise le menu Game Over
 * @param menu Pointeur vers l'objet menu à initialiser
 */
void initGameOverMenu( MenuObject* menu );

/*!
 * \brief Agence le menu de façon proportionnée
 * @param menu Pointeur vers le menu à agencer
 * @param windowSize Taille de la fenêtre de rendu
 */
void agenceMenu( MenuObject* menu );

/*!
 * \brief Gère les évènements du menu
 * @param menu Pointeur vers le menu à tester
 * @param window Informations sur la fenêtre
 * @param em Pointeur vers le manager d'events
 * @param gm Pointeur vers le game manager principal, permet le lancement des actions des boutons
 * @return L'id du bouton sur lequel une action doit être déclenchée
 */
unsigned int handleMenuEvents( MenuObject* menu, Window window, EventManager* em );

/*!
 * \brief Retourne l'id du bouton sur lequel l'utilisateur est
 * @param menu Pointeur vers le menu à tester
 * @param position Coordonnées du curseur dans le repère du menu
 * @return ID de l'item survolé
 */
unsigned int getHoveringItem( MenuObject* menu, Vector2i position );

/*!
 * \brief Retourne les coordonnées du menu correspondant aux coordonnées de la fenêtre
 * @param position Position du point dans le repère de la fenêtre
 * @param window Informations sur la fenêtre
 * @return Position du point dans le repère du menu, 0 si aucun élément
 */
Vector2i getMenuCoor( Vector2i position, Window window );


/*!
 * Stocke les différents menus
 */
typedef struct menumanager
{
    MenuObject mainMenu; //!< Menu principal
    MenuObject scoresMenu; //!< Menu des top scores
    MenuObject inGamePauseMenu; //!< Menu de pause in-game
    MenuObject gameOvermenu; //!< Menu game over
    MenuObject winMenu; //!< Menu de victoire de fin de parcours
}
MenuManager;

/*!
 * \brief Initialise toutes les données des menus et les Stocke
 * @param menuManager Pointeur vers le conteneur des informations des menus
 * @param scoreList Pointeur vers la liste des scores
 */
void initMenus( MenuManager* menuManager, ScoreList* scoreList );



#endif
