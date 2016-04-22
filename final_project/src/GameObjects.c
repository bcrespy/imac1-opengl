#include "GameObjects.h"


void initCameraData( CameraObject* camera )
{
    camera->position.x = 0;
    camera->position.y = 0;
}


void initPlayerData( PlayerObject* player )
{
    player->position.x = 200;
    player->position.y = 200;
    player->velocity.x = 0;
    player->velocity.y = 0;
    player->motor.x = 0;
    player->motor.y = 0;
    player->angle = 0;
    player->motorAcceleration = 0;
}


void freePlayerData( PlayerObject* player )
{
    free( player->collider.points );
}


void initGameObjects( GameObjects* go )
{
    initCameraData( &go->camera );
    initPlayerData( &go->player );
    go->wallsNb = 0;
}


void freeMapObject( MapObject* map )
{
    int i;
    for( i = 0; i < map->size.x; i++ )
        free( map->ground[i] );
    free( map->ground );
}
