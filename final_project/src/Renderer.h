#ifndef RENDERER_H
#define RENDERER_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GameManager.h"


void dessinCarre();
void dessinRepere();


/*!
 * \brief Initialise les paramètes openGL
 */
void initGraphics();


/*!
 * \brief Charge les ressources graphiques des objets
 * @params objects Pointeur vers les objets du jeu auxquels il faut assigner une texture
 */
void loadGraphics( GameObjects* objects );


/*!
 * \brief Charge une texture dans openGL et retourne son ID
 * @param filename Chemin relatif ou absolu du fichier image à charger
 * @return ID de la texture retourné par OpenGL
 */
GLuint loadTexture( const char filename[] );


/*!
 * \brief Function called at each frame of the context
 *        Renders all the objects of the game
 * @param gm Game Manager
 */
void updateRender( GameObjects* objects );


#endif
