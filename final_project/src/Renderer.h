#ifndef RENDERER_H
#define RENDERER_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GameManager.h"
#include "MathsComponents.h"


#define GL_CLAMP_TO_EDGE 0x812F


void dessinCarre( Vector2f playerSize );
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
 * @param textureSize Pointeur vers un Vecteur 2D, out : taille de la texture chargée
 * @param alpha S'il y a un channel alpha sur l'image
 * @return ID de la texture retourné par OpenGL
 */
GLuint loadTexture( const char filename[], Vector2i *textureSize, int alpha );


/*!
 * \brief Transforme un vecteur aux coordonnées du jeu dans le
 *        repère openGL
 * @param vec Vecteur qui doit être transformé
 * @param windowSize Taille de la fenêtre -- la taille du joueur dans le repère
 *                   openGL est proportionnelle à la taille de la fenêtre
 * @return Vecteur 2f dans le repère openGL
 */
Vector2f gameCoorToGLCoor( Vector2i vec, Vector2i windowSize );


/*!
 * \brief Fonction appelée à chaque frame du contexte
 *        Met à jour le rendu en fonction des nouveaux paramètres
 * @param gm Game Manager
 */
void updateRender( GameObjects* objects, Vector2i windowSize );


/*!
 * \brief Charge l'image de la map
 *        Définit les propriétés de cette dernière
 * @param map Référence vers l'objet de la map courante
 * @param filename Chemin vers le fichier contenant la texture de la map
 */
void loadMapGraphics( MapObject* map, const char filename[] );


/*!
 * \brief Affiche la map avec la texture correcpondante
 * @param mapSize Taille de la MAP dans le repère openGL
 */
void renderMap( Vector2f mapSizeGL );


#endif
