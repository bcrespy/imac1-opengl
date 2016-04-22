#ifndef RENDERER_H
#define RENDERER_H

#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <dirent.h>

#ifndef WIN32
    #include <sys/types.h>
#endif

#include "GameManager.h"
#include "MathsComponents.h"
#include "GeometryComponents.h"
#include "MenuManager.h"


#define GL_CLAMP_TO_EDGE 0x812F


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
 * \brief Charge une séquence de textures
 * @param folderpath Chemin du dossier contenant les textures
 * @param nbTextures Pointeur vers la variable qui contiendra le nombre de frames de la séquence
 * @param textureSize Taille des textures chargées
 * @param alpha bool - true si l'image contient une couche alpha
 */
GLuint* loadSequence(  const char folderpath[], int* nbTextures, Vector2i* textureSize, int alpha );


/*!
 * \brief Retourne l'id de la texture correspondant à la frame suivante de la séquence
 * @param seq Séquence d'images à rendre
 * @return ID openGL de la prochaine texture de la séquence
 */
GLuint getNextTextureFromSequence( Sequence* seq );


/*!
 * \brief Transforme un vecteur aux coordonnées du jeu dans le
 *        repère openGL
 * @param vec Vecteur qui doit être transformé
 * @param windowSize Taille de la fenêtre -- la taille du joueur dans le repère
 *                   openGL est proportionnelle à la taille de la fenêtre
 * @return Vecteur 2f dans le repère openGL
 */
Vector2f gameCoorfToGLCoor( Vector2f vec, Vector2i windowSize );


/*!
 * \brief Transforme un vecteur aux coordonnées du jeu dans le
 *        repère openGL
 * @param vec Vecteur qui doit être transformé
 * @param windowSize Taille de la fenêtre -- la taille du joueur dans le repère
 *                   openGL est proportionnelle à la taille de la fenêtre
 * @return Vecteur 2f dans le repère openGL
 */
Vector2f gameCooriToGLCoor( Vector2i vec, Vector2i windowSize );


/*!
 * \brief Fonction appelée à chaque frame du contexte
 *        Met à jour le rendu en fonction des nouveaux paramètres
 * @param gm Game Manager
 */
void updateGameRender( GameObjects* objects, Vector2i windowSize );


/*!
 * \brief Fonction appelée à chaque frame du contexte lorsque
 *        le jeu est en état Menu
 * @param menu Pointeur vers le menu principal
 * @param windowSize Taille de la fenêtre
 */
void updateMainMenuRender( MenuObject menu, Vector2i windowSize );


/*!
 * \brief Charge l'image de la map
 *        Définit les propriétés de cette dernière
 * @param map Référence vers l'objet de la map courante
 * @param filename Chemin vers le fichier contenant la texture de la map
 */
void loadMapGraphics( MapObject* map, const char filename[] );


/*!
 * \brief Affiche un rectangle de la taille transmise en paramètres
 * @param rectSize Taille du rectangle
 * @param centered Bool, centré sur le repère ou non
 */
void renderRect( Vector2f rectSize, unsigned int centered );


/*!
 * \brief Affiche un rectangle à une position précise
 * @param rect Rectangle à afficher
 */
void renderRectAtExactPosition( Rectanglef rect );


/*!
 * \brief Affiche un polygone
 * @param poly Polygone à afficher
 */
void renderPolygonei( Polygonei poly, Vector2i windowSize );


#endif
