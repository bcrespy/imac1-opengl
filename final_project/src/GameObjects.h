#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H


#include "MathsComponents.h"


struct playerobject
{
    Vector2f position;
    Vector2f velocity;
    Vector2f motor;
    float angle;
    float motorAcceleration;
};

typedef struct playerobject PlayerObject;


struct gameobjects
{
    PlayerObject player;
};

typedef struct gameobjects GameObjects;


#endif
