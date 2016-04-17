#ifndef MATHSCOMPONENTS_H
#define MATHSCOMPONENTS_H

#include <math.h>


struct vector2f
{
    float x;
    float y;
};
typedef struct vector2f Vector2f;


struct vector2i
{
    int x;
    int y;
};
typedef struct vector2i Vector2i;


/*!
 * \brief Rotation d'un point autour d'un autre point
 * @param point Point sur lequel appliquer la rotation
 * @param center Centre de la rotation
 * @param angle Angle de rotation de la transformation
 * @return Transormé du point selon la rotation
 */
Vector2i getRotatedPoint( Vector2i point, Vector2i center, float angle );



#endif
