#include "GameObjects.h"


void initPlayerData( PlayerObject* player )
{
    player->position.x = 0;
    player->position.y = 0;
    player->velocity.x = 0;
    player->velocity.y = 0;
    player->motor.x = 0;
    player->motor.y = 0;
    player->angle = 0;
    player->motorAcceleration = 0;
}
