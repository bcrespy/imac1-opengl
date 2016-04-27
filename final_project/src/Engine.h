/*!
 * L'engine est chargé de toute la partie physique du moteur du jeu
 * Il gère l'application des forces sur les éléments du jeu
 * Il s'occupe aussi du calcul des différentes collisions
 */

#ifndef ENGINE_H
#define ENGINE_H


#include "MathsComponents.h"
#include "GeometryComponents.h"
#include "GameObjects.h"
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>


// Nombre minimal de millisecondes separant le rendu de deux images
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;


// Nombre de frames dont la caméra a besoin pour rejoindre le Joueur
static const Uint32 FRAMES_NB_TO_MOVE_CAMERA = 20;


// Vitesse en pixels / s
static const float INITIAL_SPEED = 300.;
static const float MAX_SPEED = 800.;


// Nombre de pixels autour du joueur pour la recherche de collisions (doit être multiple de 2)
static const unsigned int BOX_SIZE_COLLISION = 60;


typedef struct gameengine
{
}
GameEngine;


/*!
 * \brief Met à jour la position du joueur
 * @param player Référence vers la structure du joueur contenant les informations de ce dernier
 */
void updatePlayerPosition( PlayerObject* player );


/*!
 * \brief Met à jour la position de la caméra en fonction de la position du joueur
 * @param camera Référence vers l'objet caméra
 * @param player Informations sur le joueur que doit suivre la caméra
 */
void updateCameraPosition( CameraObject* camera, PlayerObject player );


/*!
 * \brief Calcule si le joueur est en collision avec un mur
 * @param objects Pointeur vers la structure contenant les objets du jeu
 * @param position Position de la collsion s'il y en a une
 * @return 0 si le player n'est pas en collsion, 1 s'il l'est
 */
unsigned int isPlayerCollidingWall( GameObjects* objects, Vector2i* position );


/*!
 * \brief Calcule si un point est ou non à l'intérieur d'un polygone
 * @param point Point à tester
 * @param poly Polygone à tester
 * @return booléen si le point est dans le polygone
 */
unsigned int isPointInPolygonei( Vector2i point, Polygonei poly );


/*!
 * \brief Parse la map et crée les Game Objects correspondant
 * @param filename Chemin vers le fichier MAP
 * @param objects Pointeur vers la liste d'objets du jeu
 */
GroundType** loadMAP( const char filename[], GameObjects* objects );


/*!
 * \brief Parse le fichier filename et crée un polygone correspondant
 * @param filename Chemin vers le fichier collider
 * @return Polygone
 */
Polygonei getColliderFromFile( const char filename[] );


/*!
 * \brief Récupère le pixel d'une surface en [x;y]
 * @param surface Pointeur vers la surface contenant les informations de l'image à parcourir
 * @param x coordonnée X du pixel
 * @param y coordonnée Y du pixel
 * @return Le pixel aux coordonnées [x;y]
 */
Uint32 getPixelFromSurface( SDL_Surface *surface, int x, int y );


#endif
