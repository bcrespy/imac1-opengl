#ifndef VIDEOMANAGER_H
#define VIDEOMANAGER_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>

#include "MathsComponents.h"


/* Nombre de bits par pixel de la fenÃªtre */
static const unsigned int BIT_PER_PIXEL = 32;

void reshape( Vector2i windowSize );

void setVideoMode( Vector2i windowSize );

#endif
