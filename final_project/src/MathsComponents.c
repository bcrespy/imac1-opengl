#include "MathsComponents.h"



Vector2i getRotatedPoint( Vector2i point, Vector2i center, float angle )
{
    Vector2i translatedPoint = { cos(angle * M_PI / 180) * (point.x-center.x) - sin(angle * M_PI / 180) * (point.y-center.y) + center.x,
                                 sin(angle * M_PI / 180) * (point.x-center.x) + cos(angle * M_PI / 180) * (point.y-center.y) + center.y };
    return translatedPoint;
}
