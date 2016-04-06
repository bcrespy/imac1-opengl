#include "Renderer.h"



void dessinCarre()
{
    glBegin( GL_POLYGON );
    glVertex2f( -0.5, 0.5);
    glVertex2f( 0.5 , 0.5);
    glVertex2f( 0.5 , -0.5);
    glVertex2f( -0.5 , -0.5);
    glEnd();
}


void dessinRepere()
{
    glBegin( GL_LINES );
    glColor3f( 1, 0, 0 );
    glVertex2f( 0, 0 );
    glVertex2f( 1, 0 );
    glColor3f( 0, 1, 0 );
    glVertex2f( 0, 0 );
    glVertex2f( 0, 1 );
    glEnd();
}


void updateRender( GameObjects* objects )
{
    glClear(GL_COLOR_BUFFER_BIT);

    /* Placer ici le code de dessin */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef( -objects->player.position.x*2.f, -objects->player.position.y*2.f, 0 );
    dessinRepere();

    glPushMatrix();
    glTranslatef( objects->player.position.x, objects->player.position.y, 0 );
    glTranslatef( objects->player.position.x, objects->player.position.y, 0 );
    glRotatef( objects->player.angle, 0, 0, 1 );
    dessinCarre();
    glPopMatrix();

    /* Echange du front et du back buffer : mise Ã  jour de la fenÃªtre */
    SDL_GL_SwapBuffers();
}
