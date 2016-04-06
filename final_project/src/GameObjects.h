#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H


#include <GL/gl.h>
#include "MathsComponents.h"


struct playerobject
{
    Vector2f position;
    Vector2f velocity;
    Vector2f motor;
    float angle;
    float motorAcceleration;
    GLuint texture;
};

typedef struct playerobject PlayerObject;


//! \brief Initialise les donnée du player
void initPlayerData( PlayerObject* player );


struct gameobjects
{
    PlayerObject player;
};

typedef struct gameobjects GameObjects;


#endif
