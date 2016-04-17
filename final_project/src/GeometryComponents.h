#ifndef GEOMETRYCOMPONENTS_H
#define GEOMETRYCOMPONENTS_H

#include <stdlib.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "MathsComponents.h"


/*!
 * Segment dans N
 */
struct segmenti
{
    Vector2i pt1; //!< Premier point
    Vector2i pt2; //!< Second point
};
typedef struct segmenti Segmenti;


int intersectSegment( Segmenti seg1, Segmenti seg2 );
/*!
 * Segment dans R
 */
struct segmentf
{
    Vector2f pt1; //!< Premier point
    Vector2f pt2; //!< Second point
};
typedef struct segmentf Segmentf;


/*!
 * Polygone non convexe dans R
 * Composé de points
 */
struct polygonef
{
    Vector2f* points; //!< Liste des points du polygone
    unsigned int nbPoints; //!< Nombre de points du polygone
};
typedef struct polygonef Polygonef;


/*!
 * Polygone non convexe dans N
 * Composé de points
 */
struct polygonei
{
    Vector2i* points; //!< Liste des points du polygone
    unsigned int nbPoints; //!< Nombre de points du polygone
};
typedef struct polygonei Polygonei;


void getTranslatedPolygone( Polygonei poly, Vector2i translation, Polygonei* polyRet );
void getRotatedPolygone( Polygonei poly, Vector2i center, float angle, Polygonei* polyRet );


#endif
