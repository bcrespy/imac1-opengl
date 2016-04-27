/*!
 * Le Score Manager est chargé de gérer le score de la partie en cours
 * et propose des fonctions qui permettent la sauvegarde des scores et
 * la récupération des scores sauvegardés
 */

#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

#include <SDL/SDL.h>
#include <stdio.h>

#include "MathsComponents.h"
#include "Graphics.h"

#include "VideoManager.h"

/*!
 * Structure ScoreManager
 * Stocke le score courant et les informations nécessaires
 * à la récupération / sauvegarde des scores
 */
typedef struct scoremanager
{
    const char* scorefile; //!< Chemin vers le fichier de gestion des scores
    float scoreRendered; //!< Score actuellement rendu dans la texture
    float currentScore; //!< Score de la partie en cours
    TextureInformations texture; //!< Informations sur la texture (texte)
    Vector2i position; //!< Position du score
    SDL_Color fontColor; //!< Couleur du texte du score
}
ScoreManager;

/*!
 * \brief Initialise le score manager
 * @param sm Pointeur vers le manager de Score
 */
void initScoreManager( ScoreManager* sm );

/*!
 * \brief Met à jour le score avec le nouveau score
 * @param sm Pointeur vers le score manager à update
 * @param newScore Nouveau score à mettre à jour
 */
void updateScore( ScoreManager* sm, unsigned int newScore );

/*!
 * \brief Met à jour la position du score en fonction de sa taille
 * @param sm Pointeur vers le score manager
 * @param window Pointeur vers les informations de la fenêtre
 */
void updateScorePosition( ScoreManager* sm, Window* window );

/*!
 * \brief Sauvegarde le score dans le fichier score
 * @param sm Pointeur vers le Score manager
 */
void saveScore( ScoreManager* sm );


/*!
 * Structure contenant la liste des scores triés par ordre décroissant
 */
typedef struct scorelist
{
    const char* filename; //!< Chemin du fichier de la liste des scores
    unsigned int* scores; //!< Liste des scores
    unsigned int scoresNb; //!< Nombre de scores
}
ScoreList;

/*!
 * \brief Charge les scores enregistrés dans un fichier
          Les scores sont stockés par odre décroissant dans la liste
 * @param sl Pointeur vers la liste de scores
 * @param filename Nom du fichier contenant la liste des scores
 */
void getScoreList( ScoreList* sl );

/*!
 * \brief Trie le tableau des scores par ordre décroissant
 * @param sl Pointeur vers la liste de scores
 */
void sortScores( ScoreList* sl );

#endif
