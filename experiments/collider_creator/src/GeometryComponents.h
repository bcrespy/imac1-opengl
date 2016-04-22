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

/*!
 * \Brief Calcule s'il y a une intersection entre deux segments
 * @param seg1 Premier segment
 * @param seg2 Second segment
 * @return 1 s'il y a au moins une intersection entre les segments
 *         0 s'il n'y a aucune intersection entre les segments
 */
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

/*!
 * \brief Calcule le translaté d'un polygone suivant un vecteur
 * @param poly Polygone à translater
 * @param translation Vecteur selon lequel le polygone doit être translaté
 * @param polyRet Référence vers la structure qui va contenir le polygone translaté
 */
void getTranslatedPolygone( Polygonei poly, Vector2i translation, Polygonei* polyRet );

/*!
 * \brief Calcule le transformé d'un polygone suivant sa rotation autour d'un point
 * @param poly Polygone à transformer
 * @param center Centre de rotation de la transformation
 * @param angle Angle de rotation du polygone
 * @param polyRet Référence vers la structure qui va contenir le polygone transformé
 */
void getRotatedPolygone( Polygonei poly, Vector2i center, float angle, Polygonei* polyRet );


#endif
