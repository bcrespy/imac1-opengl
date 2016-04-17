#include "GeometryComponents.h"
#include "MathsComponents.h"



void getTranslatedPolygone( Polygonei poly, Vector2i translation, Polygonei* polyRet )
{
    polyRet->points = malloc( poly.nbPoints * sizeof(Vector2i) );
    polyRet->nbPoints = poly.nbPoints;
    int i;
    for( i = 0; i < poly.nbPoints; i++ )
    {
        polyRet->points[i].x = poly.points[i].x + translation.x;
        polyRet->points[i].y = poly.points[i].y + translation.y;
    }
}


void getRotatedPolygone( Polygonei poly, Vector2i center, float angle, Polygonei* polyRet )
{
    polyRet->points = malloc( poly.nbPoints * sizeof(Vector2i) );
    polyRet->nbPoints = poly.nbPoints;
    int i;
    for( i = 0; i < poly.nbPoints; i++ )
    {
        Vector2i rotated = getRotatedPoint( poly.points[i], center, angle );
        polyRet->points[i].x = rotated.x;
        polyRet->points[i].y = rotated.y;
    }
}


int intersectSegment( Segmenti seg1, Segmenti seg2 )
{
    Vector2i D, E;
    D.x = seg1.pt2.x - seg1.pt1.x;
    D.y = seg1.pt2.y - seg1.pt1.y;
    E.x = seg2.pt2.x - seg2.pt1.x;
    E.y = seg2.pt2.y - seg2.pt1.y;

    double denom = D.x*E.y - D.y*E.x;

    //printf("seg1:[%i; %i] - [%i; %i]\nseg2:[%i; %i] - [%i; %i] : %i\n\n", seg1.pt1.x, seg1.pt1.y, seg1.pt2.x, seg1.pt2.y, seg2.pt1.x, seg2.pt1.y, seg2.pt2.x, seg2.pt2.y, seg1.pt2.y - seg2.pt1.y);

    if( denom == 0 )
        return -1;   // erreur, cas limite

    double t = - (seg1.pt1.x*E.y-seg2.pt1.x*E.y-E.x*seg1.pt1.y+E.x*seg2.pt1.y) / denom;

    if( t<0 || t>=1 )
        return 0;

    double u = - (-D.x*seg1.pt1.y+D.x*seg2.pt1.y+D.y*seg1.pt1.x-D.y*seg2.pt1.x) / denom;

    if( u<0 || u>=1 )
        return 0;

    return 1;
}
