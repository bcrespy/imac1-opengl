#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/*
Projection
 Model view : où on fait les transform --> matrice
 glmatrixmode : quel est la pile de matrice active
*/


/* Nombre de bits par pixel de la fenÃªtre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

const int NB_MAX_POINTS = 4;



void reshape(unsigned int windowWidth, unsigned int windowHeight) {
    glViewport(0, 0, windowWidth, windowHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-8., 8., -8.*(float)windowHeight/(float)windowWidth, 8.*(float)windowHeight/(float)windowWidth);
}



void setVideoMode(unsigned int windowWidth, unsigned int windowHeight) {
    if(NULL == SDL_SetVideoMode(windowWidth, windowHeight, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE)) {
        fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
        exit(EXIT_FAILURE);
    }
}

void dessinCarre() {
    glBegin(GL_POLYGON);
    glVertex2f( -0.5, 0.5);
    glVertex2f( 0.5 , 0.5);
    glVertex2f( 0.5 , -0.5);
    glVertex2f( -0.5 , -0.5);

    glEnd();
}

void dessinRepere() {
    glBegin(GL_LINES);
    glColor3f(1,0,0);
    glVertex2f(0, 0);
    glVertex2f(1, 0);
    glColor3f(0,1,0);
    glVertex2f(0, 0);
    glVertex2f(0, 1);
    glEnd();
}

void dessinCercle(int angle) {
    glBegin(GL_POLYGON);
    float i = 0;
    for (; i<angle; i++) {
        glVertex2f(cos(i)/2, sin(i)/2);
    }
    glEnd();
}


int main(int argc, char** argv) {

    /* Dimensions de la fenÃªtre */
    unsigned int windowWidth  = 800;
    unsigned int windowHeight = 600;


    /* Initialisation de la SDL */
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
        return EXIT_FAILURE;
    }

    /* Ouverture d'une fenÃªtre et crÃ©ation d'un contexte OpenGL */
    setVideoMode(windowWidth, windowHeight);
    reshape(windowWidth, windowHeight);

    /* Titre de la fenÃªtre */
    SDL_WM_SetCaption("OpenGL powa :D", NULL);


    /* Boucle d'affichage */
    int loop = 1;
    float xMove = 0, yMove = 0;

    float distance = 0 ;

    int rotateLPressed = 0, rotateRPressed = 0, movePressed = 0;


    glPointSize(1);
    int pressButton = 0;
    float angle=0;


    while(loop) {
        /* RÃ©cupÃ©ration du temps au dÃ©but de la boucle */
        Uint32 startTime = SDL_GetTicks();
        glClear(GL_COLOR_BUFFER_BIT);

        /* Placer ici le code de dessin */
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        dessinRepere();

        if( movePressed )
        {
            xMove += 0.1 * cos(angle * M_PI / 180);
            yMove += 0.1 * sin(angle * M_PI / 180);
        }

        if( rotateLPressed )
            angle+= 2;

        if( rotateRPressed )
            angle-= 2;

        glPushMatrix();


        glTranslatef(xMove, yMove, 0);
        glRotatef(angle, 0, 0, 1);
        //glTranslatef(-cos(angle)*yDistance, -sin(angle)*yDistance, 0);


        //glTranslatef(cos(angle)*yDistance, sin(angle)*yDistance, 0);

        dessinCarre();
        glPopMatrix();


        /* Echange du front et du back buffer : mise Ã  jour de la fenÃªtre */
        SDL_GL_SwapBuffers();

        /* Boucle traitant les evenements */
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            /* L'utilisateur ferme la fenÃªtre : */
            if(e.type == SDL_QUIT) {
                loop = 0;
                break;
            }

            /* Quelques exemples de traitement d'evenements : */
            switch(e.type) {
                    /* Clic souris */
                case SDL_MOUSEBUTTONUP:
                    pressButton=0;
                    break;

                case SDL_MOUSEBUTTONDOWN:

                    break;

                    /* move the mouse */
                case SDL_MOUSEMOTION:
                    if(pressButton==1) {
                    }
                    break;

                    /* Touche clavier */
                case SDL_KEYDOWN:

                    if(e.key.keysym.sym == SDLK_UP)
                        movePressed = 1;

                    if(e.key.keysym.sym == SDLK_LEFT)
                        rotateLPressed = 1;

                    if(e.key.keysym.sym == SDLK_RIGHT)
                        rotateRPressed = 1;

                    if(e.key.keysym.sym == SDLK_q)
                        loop = 0;
                    break;

                case SDL_KEYUP:

                    if(e.key.keysym.sym == SDLK_UP)
                        movePressed = 0;

                    if(e.key.keysym.sym == SDLK_LEFT)
                        rotateLPressed = 0;

                    if(e.key.keysym.sym == SDLK_RIGHT)
                        rotateRPressed = 0;

                    break;

                    /* resize window */
                case SDL_VIDEORESIZE:
                    windowWidth  = e.resize.w;
                    windowHeight = e.resize.h;
                    setVideoMode(windowWidth, windowHeight);
                    reshape(windowWidth, windowHeight);
                    break;


                default:
                    break;
            }
        }

        /* Calcul du temps écoulé */
        Uint32 elapsedTime = SDL_GetTicks() - startTime;

        /* Si trop peu de temps s'est écoulé, on met en pause le programme */
        if(elapsedTime < FRAMERATE_MILLISECONDS) {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
    }

    /* Liberation des ressources associées Ã  la SDL */
    SDL_Quit();

    return EXIT_SUCCESS;
}
