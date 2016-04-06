#ifndef VIDEOMANAGER_H
#define VIDEOMANAGER_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>


/* Nombre de bits par pixel de la fenÃªtre */
static const unsigned int BIT_PER_PIXEL = 32;

void reshape( unsigned int windowWidth, unsigned int windowHeight );

void setVideoMode( unsigned int windowWidth, unsigned int windowHeight );

#endif
