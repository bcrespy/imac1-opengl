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
    Vector2i D = { seg1.pt2.x - seg1.pt1.x, seg1.pt2.y - seg1.pt1.y },
             E = { seg2.pt2.x - seg2.pt1.x, seg2.pt2.y - seg2.pt1.y };

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


unsigned int isPointCollidingCircle( Vector2i A, Circlei C )
{
    if( sqrt( (C.position.x - A.x)*(C.position.x - A.x)  + (C.position.y - A.y)*(C.position.y - A.y) ) <= C.radius )
        return 1;
    else
        return 0;
}


unsigned int isLineCollidingCircle( Vector2i A, Vector2i B, Circlei circle )
{
    Vector2i u;
    u.x = B.x - A.x;

    Vector2i AC;
    AC.x = circle.position.x - A.x;
    AC.y = circle.position.y - A.y;

    float num = u.x*(float)AC.y -u.y*(float)AC.x;
    if( num < 0 )
        num = -num;
    float denom = sqrt( u.x*u.x + u.y*u.y );
    float CI = num / denom;
    if( CI < circle.radius )
        return 1;
    else
        return 0;
}


unsigned int isSegmentCollidingCircle( Vector2i A, Vector2i B, Circlei circle )
{
    if( isLineCollidingCircle( A, B, circle ) == 0 )
        return 0;

    Vector2i AB, AC, BC;
    AB.x = B.x - A.x;
    AB.y = B.y - A.y;
    AC.x = circle.position.x - A.x;
    AC.y = circle.position.y - A.y;
    BC.x = circle.position.x - B.x;
    BC.y = circle.position.y - B.y;

    float pscal1 = AB.x*AC.x + AB.y*AC.y;  // produit scalaire
    float pscal2 = (-AB.x)*BC.x + (-AB.y)*BC.y;  // produit scalaire

    if( pscal1 >= 0 && pscal2 >= 0 )
        return 1;

    if( isPointCollidingCircle(A, circle) )
        return 1;
    if( isPointCollidingCircle(B, circle) )
        return 1;

    return 0;
}


unsigned int isPolygoneCollidingCircle( Polygonei poly, Circlei circle )
{
    int i;
    for( i = 0; i < poly.nbPoints; i++ )
    {
        unsigned int lastPointIndex = (i==poly.nbPoints-1) ? 0 : i+1;
        Segmenti polySegment;
        polySegment.pt1.x = poly.points[i].x;
        polySegment.pt1.y = poly.points[i].y;
        polySegment.pt2.x = poly.points[lastPointIndex].x;
        polySegment.pt2.y = poly.points[lastPointIndex].y;

        if( isSegmentCollidingCircle( poly.points[i], poly.points[lastPointIndex], circle ) )
            return 1;
    }
    return 0;
}
