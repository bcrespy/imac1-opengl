/*!
 * Le renderer s'occupe de toute la partie affichage avec openGL
 * Il s'occupe aussi de gérer le chargement correct des textures en fonction des
 * besoins de l'affichage
 * Il gère aussi le changement de repère jeu <-> openGL
 */

#ifndef RENDERER_H
#define RENDERER_H

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
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
#include "ScoreManager.h"


#define GL_CLAMP_TO_EDGE 0x812F


void dessinRepere();


/*!
 * \brief Initialise les paramètes openGL
 */
void initGraphics();


/*!
 * \brief Libères les ressources graphiques utilisées
 */
void freeGraphics();


/*!
 * \brief Charge les ressources graphiques des objets
 * @params objects Pointeur vers les objets du jeu auxquels il faut assigner une texture
 */
void loadGraphics( GameObjects* objects );


/*!
 * \brief Charge une police font, génère la texture correspondant
          et stocke les informations dans texture
 * @param texture Pointeur vers les informations de texture
 * @param text Texte à rendre
 * @param font Pointeur vers la police chargée à utilise
 * @param color Couleur de la police
 */
void renderFont( TextureInformations* texture, const char* text, TTF_Font* font, SDL_Color color );


/*!
 * \brief Parcourt tous les items du menu pour rendre la texture correspondant au texte de l'item
 * @param menu Pointeur vers le menu
 */
void renderMenuFonts( MenuObject* menu );


/*!
 * \brief Rends le texte du score
 * @param sm Pointeur vers le score manager
 */
void renderScoreFonts( ScoreManager* sm );


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
 * @param sm Pointeur vers le score manager
 * @param windowSize Taille de la fenêtre
 * @param onPause Booléen qui indique si le jeu est en pause ou non
 */
void updateGameRender( GameObjects* objects, ScoreManager* sm, Vector2i windowSize, int onPause );


/*!
 * \brief Fonction appelée lors du rendu d'un menu
 * @param menu Pointeur vers le menu principal
 * @param windowSize Taille de la fenêtre
 * @param background Booléen s'il faut dessiner un fond ou non
 */
void updateMenuRender( MenuObject menu, Vector2i windowSize, int drawBackground );


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
