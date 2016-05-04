#ifndef FILEMANIPULATION_H
#define FILEMANIPULATION_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


/*!
 * \brief Retourne le nombre de caractères stockés dans un fichier
 * @param file Pointeur vers le fichier ouvert
 * @return Nombre de caractères dans le fichier
 */
unsigned long filesize( FILE* file );

/*!
 * \brief Retourne le fichier dans un tableau de caractères
 * @param file Pointeur vers le fichier ouvert
 * @param len (out) Pointeur vers le nombre de caractères dans le fichier
 * @return Tableau de caractères
 */
char* fileToString( FILE* file, unsigned long* len );

/*!
 * \brief Ecrit la chaîne de caractère dans le fichier file
 * @param file Pointeur vers le fichier ouvert
 * @param str Chaîne de caractères à écrire
 */
void writeStringToFile( FILE* file, const char* str );

/*!
 * \brief Ajoute un int à la fin d'une chaîne de caractères et la retourne
 * @param str Pointeur vers la chaîne de caractère
 * @param len Taille de la chaîne de caractères (in/out)
 * @param i Integer à ajouter à la chaîne
 * @return Chaîne de caractère avec l'ajout
 */
char* appendIntToString( char* str, unsigned long* len, unsigned int i );


#endif
