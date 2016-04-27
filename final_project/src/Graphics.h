#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <GL/gl.h>
#include "MathsComponents.h"


/*!
 * Contient les informations concernant une texture
 */
typedef struct textureinformation
{
    GLuint id; //!< ID openGL de la texture
    Vector2i size; //!< Taille de la texture
}
TextureInformations;


#endif
