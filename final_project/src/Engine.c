#include "Engine.h"


void updatePlayerPosition( PlayerObject* player )
{
    // Force du moteur en pixels / s
    player->motor.x = sin( -player->angle * M_PI / 180 ) * ( INITIAL_SPEED + (MAX_SPEED-INITIAL_SPEED) * player->motorAcceleration );
    player->motor.y = cos( -player->angle * M_PI / 180 ) * ( INITIAL_SPEED + (MAX_SPEED-INITIAL_SPEED) * player->motorAcceleration );
    player->velocity.x = 0.985*player->velocity.x + 0.015*player->motor.x;
    player->velocity.y = 0.985*player->velocity.y + 0.015*player->motor.y;

    player->position.x+= (1.0/60.0) * player->velocity.x;
    player->position.y+= (1.0/60.0) * player->velocity.y;
}


void updateCameraPosition( CameraObject* camera, PlayerObject player )
{
    camera->position.x+= ( player.position.x - camera->position.x ) / (float)FRAMES_NB_TO_MOVE_CAMERA;
    camera->position.y+= ( player.position.y - camera->position.y ) / (float)FRAMES_NB_TO_MOVE_CAMERA;
}


GroundType** loadMAP( const char filename[], GameObjects* objects )
{
    SDL_Surface* surface = SDL_LoadBMP( filename );
    if( surface == NULL )
    {
        printf( "Error: \"%s\"\n",SDL_GetError() );
    }

    int x, y;
    unsigned int nbPortals = 0;

    // On alloue
    GroundType** ground = malloc( surface->w * sizeof( GroundType* ) );

    int i, j;

    for( i = 0; i < surface->w; i++ )
    {
        ground[i] = malloc( surface->h * sizeof( GroundType ) );

        // Parours des pixels de la ligne
        for( j = 0; j < surface->h; j++ )
        {
            Uint32 pixel = getPixelFromSurface( surface, i, j );
            Uint8 r, g, b, a;
            SDL_GetRGBA( pixel, surface->format, &r, &g, &b, &a );

            // Si le pixel est rouge = mur
            if( r == 173 && g == 0 && b == 0 )
            {
                // On inverse le repère y pour correspondre au repère du jeu
                ground[i][surface->h - j] = WALL;
            }

            // Si le pixel est vert = portail
            if( r == 0 && g == 255 && b == 0 )
            {
                objects->portals[nbPortals].position.x = i;
                objects->portals[nbPortals].position.y = surface->h - j;
                nbPortals++;
            }

            // Si le pixel est bleu = ligne arrivée
            if( r == 0 && g == 0 && b == 255 )
            {
                ground[i][surface->h-j] = END_LINE;
            }

            // Si le pixel est jaune = point de départ
            if( r == 255 && g == 255 && b == 0 )
            {
                objects->map.startPosition.x = i;
                objects->map.startPosition.y = surface->h - j;
            }
        }
    }

    objects->portalsNb = nbPortals;

    /*
    for( y = 0; y < surface->h; y++ )
    {
        for( x = 0; x < surface->w; x++ )
        {
            Uint32 pixel = getPixelFromSurface( surface, x, y );
            Uint8 r, g, b, a;
            SDL_GetRGBA( pixel, surface->format, &r, &g, &b, &a );

            // traitement des objets en fonction de la couleur du pixel
            if( r == 255 && b == 0 && g == 0 )
            {
                objects->walls[objects->wallsNb].position.x = x;
                objects->walls[objects->wallsNb].position.x = y;
                objects->wallsNb++;
            }
        }
    }*/

    printf( "Map %s loaded.\n", filename );

    return ground;
}


Polygonei getColliderFromFile( const char filename[] )
{
    Polygonei collider;
    Vector2i pointList[255];

    int blocks;
    char buf[255];
    FILE* fp;
    int xPos, yPos;

    int nbPoints = 0;

    if( (fp = fopen( filename, "r" )) == NULL )
    { /* Open source file. */
        printf( "Can't open player collifer %s\n", filename );
    }

    while( fgets( buf, sizeof(buf), fp ) != NULL )
    {
        sscanf( buf, "%i %i", &xPos, &yPos );
        pointList[nbPoints].x = xPos;
        pointList[nbPoints].y = yPos;
        nbPoints++;
    }

    fclose( fp );

    Vector2i* finalPointList = malloc( nbPoints * sizeof(Vector2i) );

    int i = 0;
    for( ; i < nbPoints; i++ )
    {
        finalPointList[i].x = pointList[i].x;
        finalPointList[i].y = pointList[i].y;
    }

    collider.points = finalPointList;
    collider.nbPoints = nbPoints;

    printf( "Collider %s loaded, %i edges.\n", filename, nbPoints-1 );

    return collider;
}


unsigned int isPlayerColliding( GameObjects* objects, Vector2i* position, GroundType* type )
{
    int xStart = objects->player.position.x - BOX_SIZE_COLLISION / 2;
    int yStart = objects->player.position.y - BOX_SIZE_COLLISION / 2;

    Polygonei rotatedPolygone;

    Vector2i center = { 0, 0 };

    getRotatedPolygone( objects->player.collider, center, objects->player.angle, &rotatedPolygone );

    Vector2i translation = { objects->player.position.x , objects->player.position.y };

    Polygonei playerColliderTranslated;
    getTranslatedPolygone( rotatedPolygone, translation, &playerColliderTranslated );

    int i, j;

    for( i = xStart; i < xStart + BOX_SIZE_COLLISION; i++ )
    {
        for( j = yStart; j < yStart + BOX_SIZE_COLLISION; j++ )
        {
            i = (i<0)?0:i;
            j = (j<0)?0:j;

            if( objects->map.ground[i][j] == WALL )
            {
                // Si le joueur est aux alentours d'un mur, on teste s'il est en collision avec ce dernier
                Vector2i wallPosition = { i, j };

                if( isPointInPolygonei( wallPosition, playerColliderTranslated ) )
                {
                    printf("COLLID en [%i;%i]\n", i, j);
                    *type = WALL;
                    return 1;
                }
            }
            else if( objects->map.ground[i][j] == END_LINE )
            {
                Vector2i linePosition = { i, j };

                if( isPointInPolygonei( linePosition, playerColliderTranslated ) )
                {
                    *type = END_LINE;
                    return 1;
                }
            }
        }
    }

    return 0;
}


unsigned int isPlayerCollidingPortal( GameObjects* objects, unsigned int* portalID )
{
    int i;
    for( i = 0; i < objects->portalsNb; i++ )
    {
        // Si les deux objets sont suffisemment proche pour traiter la collision, on la traite
        if( objects->portals[i].state == PORTAL_ON &&
            sqrt( pow((objects->portals[i].position.x - objects->player.position.x), 2) + pow((objects->portals[i].position.y - objects->player.position.y), 2) ) <=
            BOX_SIZE_COLLISION/2 + objects->portals[i].bounding.size.x/2 )
        {
            // Test de collision approfondi
            Polygonei rotatedPolygone;

            Vector2i center = { 0, 0 };

            getRotatedPolygone( objects->player.collider, center, objects->player.angle, &rotatedPolygone );

            Vector2i translation = { objects->player.position.x , objects->player.position.y };

            Polygonei playerColliderTranslated;
            getTranslatedPolygone( rotatedPolygone, translation, &playerColliderTranslated );

            // On teste s'il y a une collision entre le polygone et le cercle
            Circlei portalCollider;
            portalCollider.radius = objects->portals[i].bounding.size.x/2;
            portalCollider.position.x = objects->portals[i].position.x;
            portalCollider.position.y = objects->portals[i].position.y;

            if( isPolygoneCollidingCircle(playerColliderTranslated, portalCollider) )
            {
                *portalID = i;
                return 1;
            }
        }
    }
    return 0;
}


unsigned int isPointInPolygonei( Vector2i point, Polygonei poly )
{
    // On utilise un point nécessairement en dehors du polygone
    Segmenti testSegment;
    testSegment.pt1.x = 1;
    testSegment.pt1.y = 9999;
    testSegment.pt2.x = point.x;
    testSegment.pt2.y = point.y;

    //printf( "point: [%i; %i]\npoly: [%i; %i]\n\n", point.x, point.y, poly.points[0].x, poly.points[0].y );

    // On parcourt les segments
    unsigned int nbInter = 0;
    int i = 0;

    for( i = 0; i < poly.nbPoints; i++ )
    {
        unsigned int lastPointIndex = (i==poly.nbPoints-1) ? 0 : i+1;
        Segmenti polySegment;
        polySegment.pt1.x = poly.points[i].x;
        polySegment.pt1.y = poly.points[i].y;
        polySegment.pt2.x = poly.points[lastPointIndex].x;
        polySegment.pt2.y = poly.points[lastPointIndex].y;

        if( intersectSegment( testSegment, polySegment ) )
            nbInter++;
    }

    // C'est pair
    if( nbInter%2 == 0 )
        return 0;
    else
        return 1;
}


Uint32 getPixelFromSurface( SDL_Surface *surface, int x, int y )
{
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * surface->format->BytesPerPixel;

    switch( surface->format->BytesPerPixel )
    {
        case 1:
            return *p;

        case 2:
            return *(Uint16 *)p;

        case 3:
            if( SDL_BYTEORDER == SDL_BIG_ENDIAN )
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;

        case 4:
            return *(Uint32 *)p;
    }
}
