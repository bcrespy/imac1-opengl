#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H


#include <GL/gl.h>
#include "MathsComponents.h"

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
};

typedef struct playerobject PlayerObject;


/*!
 * \brief Initialise les différentes variables du joueur à t0
 * @param player Référence vers l'objet du joueur
 */
void initPlayerData( PlayerObject* player );


/*!
 * Contient tous les différents objets que le jeu doit gérer
 */
struct gameobjects
{
    PlayerObject player; //!< Joueur principal
};

typedef struct gameobjects GameObjects;


#endif
