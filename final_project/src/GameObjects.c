#include "GameObjects.h"


void initCameraData( CameraObject* camera, Vector2i playerPos )
{
    camera->position.x = playerPos.x;
    camera->position.y = playerPos.y;
}


void initPlayerData( PlayerObject* player, Vector2i position )
{
    player->position.x = (float)position.x;
    player->position.y = (float)position.y;
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
    initCameraData( &go->camera, go->map.startPosition );
    initPlayerData( &go->player, go->map.startPosition );
    go->portalsTaken = 0;
}


void setPortalState( PortalObject* portal, PortalState state )
{
    portal->state = state;
}


void setAllPortalState( GameObjects* go, PortalState state )
{
    int i;
    for( i = 0; i < go->portalsNb; i++ )
        go->portals[i].state = state;
}


void freeMapObject( MapObject* map )
{
    int i;
    for( i = 0; i < map->size.x; i++ )
        free( map->ground[i] );
    free( map->ground );
}
