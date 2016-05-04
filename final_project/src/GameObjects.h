/*!
 * Structures de données pour les objets du jeu
 * Contient aussi quelques fonctions de bases permettant la bonne
 * initialisation des objets de jeu
 */

#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H


#include <GL/gl.h>
#include "MathsComponents.h"
#include "GeometryComponents.h"


#define MAX_WALL_OBJECTS 5000
#define MAX_PORTAL_OBJECTS 60


/*!
 * Type de sol
 */
typedef enum groundtype
{
    NO_GROUND,
    WALL,
    END_LINE
}
GroundType;


/*!
 * Structure d'une caméra
 */
typedef struct cameraobject
{
    Vector2f position; //!< Position de la caméra dans le repère du jeu
}
CameraObject;

/*!
 * \brief Initialise les coordonnées de la caméra
 * @param camera Pointeur vers la caméra à initialiser
 * @param position Position à laquelle le joueur doit être initialisée
 */
void initCameraData( CameraObject* camera, Vector2i playerPos );


/*!
 * Structure qui contient une séquence de textures et les informations
 * nécessaires à leur affichage
 */
typedef struct sequence
{
    GLuint* texturesList; //!< Liste des IDs openGL des textures de la séquence
    int nbTextures; //!< Nombre de textures de la séquence
    int currentTexture; //!< Texture de la séquence actuellement affichée
}
Sequence;


/*!
 * Structure de l'objet joueur, contient les informations
 * sur le joueur
 */
typedef struct playerobject
{
    Vector2f position; //!< Position du joueur dans le repère du jeu
    Vector2f velocity; //!< Vecteur vitesse appliqué au joueur en temps réel
    Vector2f motor; //!< Force générée par le moteur
    float angle; //!< Angle d'orientation du joueur en dégrés
    float motorAcceleration; //!< Facteur d'accélération du moteur
    GLuint texture; //!< ID openGL lié à la texture du joueur
    Vector2i size; //!< Taille de la texture du joueur
    Sequence sprite; //!< Sprite du joueur
    Polygonei collider; //!< Boite de collision du joueur
}
PlayerObject;

/*!
 * \brief Initialise les différentes variables du joueur à t0
 * @param player Référence vers l'objet du joueur
 */
void initPlayerData( PlayerObject* player, Vector2i position );

/*!
 * \brief Désalloue les informations de la structure joueur
 * @param player Référence vers l'objet du joueur à désallouer
 */
void freePlayerData( PlayerObject* player );


/*!
 * Contient les informations sur la carte en cours
 */
typedef struct mapobject
{
    Vector2i size; //!< Taille de la carte
    GLuint texture; //!< ID openGL lié à la texture de la carte
    float proportion; //!< height/width
    GroundType** ground; //!< Tableau 2D des informations de la carte
    Vector2i startPosition; //!< Position de départ du joueur
}
MapObject;

/*!
 * \brief Désalloue les informations de la map
 * @param map Pointeur vers la structure map à désallouer
 */
void freeMapObject( MapObject* map );



typedef enum portalstate
{
    PORTAL_ON, PORTAL_DESTROYED, PORTAL_OFF
}
PortalState;

/*!
 * Contient les informations d'un portail
 */
typedef struct portalobject
{
    Vector2i position; //!< Centre du portail
    Vector2i size; //!< Taille du portail (le rayon est déterminé à partir de ça)
    GLuint texture; //!< Texture du portail
    Rectanglei bounding; //!< Rectangle de collision du portail
    PortalState state; //!< Statut du portail
}
PortalObject;


/*!
 * Contient les informations sur la position d'un mur
 */
typedef struct wallobject
{
    Vector2f position; //!< Position du pixel mur
}
WallObject;


/*!
 * Division d'une map,
 * optimise les calcules de collisions
 */
typedef struct mapdivision
{
    Vector2i position;
    Vector2i size;
    WallObject walls;
    unsigned int nbWalls;
}
MapDivision;


/*!
 * Contient tous les différents objets que le jeu doit gérer
 */
typedef struct gameobjects
{
    CameraObject camera; //!< Caméra principale
    PlayerObject player; //!< Joueur principal
    MapObject map; //!< Map courante
    PortalObject portals[MAX_PORTAL_OBJECTS]; //!< Liste des portails
    unsigned int portalsNb; //!< Nombre de portails
    unsigned int portalsTaken; //!< Nombre de portails pris
}
GameObjects;

/*!
 * \brief Initialise variables des objets du jeu
 * @param go Pointeur vers le GameObjects principal
 * @param playerPos Position de départ du joueur
 */
void initGameObjects( GameObjects* go );

/*!
 * \brief Change le state d'un portal
 * @param portal Pointeur vers le portail à modifier
 * @param state Nouvel état du portail
 */
void setPortalState( PortalObject* portal, PortalState state );

/*!
 * \brief Change le statut de tous les portails
 * @param go Pointeur vers le Game Object
 * @param state Nouveau statut
 */
void setAllPortalState( GameObjects* go, PortalState state );


#endif
