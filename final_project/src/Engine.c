#include "Engine.h"


void updatePlayerPosition( PlayerObject* player )
{
    player->motor.x = sin(-player->angle * M_PI / 180) * (INITIAL_SPEED+(MAX_SPEED-INITIAL_SPEED)*player->motorAcceleration);
    player->motor.y = cos(-player->angle * M_PI / 180) * (INITIAL_SPEED+(MAX_SPEED-INITIAL_SPEED)*player->motorAcceleration);
    player->velocity.x = 0.99*player->velocity.x + 0.01*player->motor.x;
    player->velocity.y = 0.99*player->velocity.y + 0.01*player->motor.y;
    player->position.x+= (FRAMERATE_MILLISECONDS / 1000.0) * player->velocity.x;
    player->position.y+= (FRAMERATE_MILLISECONDS / 1000.0) * player->velocity.y;
}
