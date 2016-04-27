/*!
 * Le video manager s'occupe de la gestion de la fenêtre et du contexte openGL
 * Il est séparé du renderer afin de facilité l'approche logique du programme
 */

#ifndef VIDEOMANAGER_H
#define VIDEOMANAGER_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <SDL/SDL_video.h>

#include "MathsComponents.h"


// Nombre de bits par pixel de la fenÃªtre
static const unsigned int BIT_PER_PIXEL = 32;

// Dimensions de base de la fenêtre
static const int WINDOW_WIDTH = 1280;
static const int WINDOW_HEIGHT = 720;

static const unsigned int WINDOW_MIN_WIDTH = 600;


/*!
 * Contient les informations de la fenêtre
 */
typedef struct window
{
    Vector2i size; //!< Taille de la fenêtre en pixels
    Vector2i screenSize; //!< Taille maximum que peut prendre la fenêtre - taille de l'écran
    float screenRatio; //!< Rapport largeur/hauteur de l'écran
}
Window;


/*!
 * \brief Retourne la résolution de l'écran
 * @return Résolution de l'écran en pixels
 */
Vector2i getScreenSize();


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
