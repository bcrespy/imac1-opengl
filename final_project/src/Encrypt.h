#ifndef ENCRYPT_H
#define ENCRYPT_H


#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>


// Clé de chiffrement pour l'encryptage basique
static const char* key = "Qôåîü,vvzÉii)C)3øfCLù|fI>=£NçW.3:mÿô;ø^?[*àIÉ=G]DôT>ØØ;{=YbtKûRXÆPfhÇ~UZ12û.=Ilm?|JLxV`3D@OBS9bNR1ì";


/*!
 * \brief Encryptage basique d'une chaine de caractère str d'une taille len avec la clé de chiffrement définie
 *        Encryptage basique d'une addition de la clé sur la chaîne de caractère
 * @param str Chaîne de caractère à encrypter
 * @param len Taille de la chaîne de caractère
 * @return Chaîne cryptée
 */
char* encryptString( const char* str, unsigned int len );


/*!
 * \brief Décryptage de la fonction encryptString suivant la même clé de chiffrement
 * @param str Chaîne à décrypter
 * @param len Taille de la chaîne à décrypter
 * @return Chaîne décryptée
 */
char* decryptString( const char* str, unsigned int len );


#endif
