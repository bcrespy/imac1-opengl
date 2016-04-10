#ifndef VIDEOMANAGER_H
#define VIDEOMANAGER_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>

#include "MathsComponents.h"


// Nombre de bits par pixel de la fenÃªtre
static const unsigned int BIT_PER_PIXEL = 32;

// Dimensions de base de la fenêtre
static const int WINDOW_WIDTH = 1280;
static const int WINDOW_HEIGHT = 720;


/*!
 * Contient les informations de la fenêtre
 */
struct window
{
    Vector2i size; //!< Taille de la fenêtre en pixels
};
typedef struct window Window;


/*!
 * \brief Initialisation de la taille de la fenêtre
 *  @param window Pointeur vers les informations de la fenêtre à intitialiser
 */
void initWindow( Window* window );


/*!
 * \brief Redimensionne la fenêtre et le contexte openGL
 * @param window Pointeur vers l'objet de la fenêtre
 */
void resizeWindow( Window *window );

void reshape( Vector2i windowSize );

void setVideoMode( Vector2i windowSize );


#endif
