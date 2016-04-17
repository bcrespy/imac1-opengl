#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H


#include <GL/gl.h>
#include "MathsComponents.h"
#include "GeometryComponents.h"


#define MAX_WALL_OBJECTS 5000


/*!
 * Type de sol
 */
enum groundtype
{
    NO_GROUND,
    WALL
};
typedef enum groundtype GroundType;


/*!
 * Structure d'une caméra
 */
struct cameraobject
{
    Vector2f position; //!< Position de la caméra dans le repère du jeu
};
typedef struct cameraobject CameraObject;

/*!
 * \brief Initialise les coordonnées de la caméra
 * @param camera Pointeur vers la caméra à initialiser
 */
void initCameraData( CameraObject* camera );


/*!
 * Structure qui contient une séquence de textures et les informations
 * nécessaires à leur affichage
 */
struct sequence
{
    GLuint* texturesList; //!< Liste des IDs openGL des textures de la séquence
    int nbTextures; //!< Nombre de textures de la séquence
    int currentTexture; //!< Texture de la séquence actuellement affichée
};
typedef struct sequence Sequence;


/*!
 * Structure de l'objet joueur, contient les informations
 * sur le joueur
 */
struct playerobject
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
};
typedef struct playerobject PlayerObject;

/*!
 * \brief Initialise les différentes variables du joueur à t0
 * @param player Référence vers l'objet du joueur
 */
void initPlayerData( PlayerObject* player );


/*!
 * Contient les informations sur la carte en cours
 */
struct mapobject
{
    //Vector2f position;
    Vector2i size; //!< Taille de la carte
    GLuint texture; //!< ID openGL lié à la texture de la carte
    float proportion; //!< height/width
    GroundType** ground; //!< Tableau 2D des informations de la carte
};
typedef struct mapobject MapObject;


/*!
 * Contient les informations sur la position d'un mur
 */
struct wallobject
{
    Vector2f position; //!<< Position du pixel mur
};
typedef struct wallobject WallObject;


/*!
 * Division d'une map,
 * optimise les calcules de collisions
 */
struct mapdivision
{
    Vector2i position;
    Vector2i size;
    WallObject walls;
    unsigned int nbWalls;
};
typedef struct mapdivision MapDivision;


/*!
 * Contient tous les différents objets que le jeu doit gérer
 */
struct gameobjects
{
    CameraObject camera; //!< Caméra principale
    PlayerObject player; //!< Joueur principal
    MapObject map; //!< Map courante

    MapDivision** mapDivision; //!< Tableau 2D de la division de la map en carrés

    WallObject walls[MAX_WALL_OBJECTS]; //!< Liste des murs pour les collisions
    int wallsNb; //!< Nombre d'objets mur
};
typedef struct gameobjects GameObjects;

/*!
 * \brief Initialise variables des objets du jeu
 * @param go Pointeur vers le GameObjects principal
 */
void initGameObjects( GameObjects* go );


#endif
