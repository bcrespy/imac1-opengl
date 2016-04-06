#ifndef RENDERER_H
#define RENDERER_H

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GameManager.h"


void dessinCarre();
void dessinRepere();

/*!
 * \brief Function called at each frame of the context
 *        Renders all the objects of the game
 * @param gm Game Manager
 */
void updateRender( GameObjects* objects );


#endif
