#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "MathsComponents.h"
#include "GeometryComponents.h"



/* Nombre de bits par pixel de la fenÃªtre */
static const unsigned int BIT_PER_PIXEL = 32;

#define GL_CLAMP_TO_EDGE 0x812F

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

const int NB_MAX_POINTS = 4;

// Vitesse en unité par seconde
static const float INITIAL_SPEED = 5.;
static const float MAX_SPEED = 12.;


void reshape( Vector2i window )
{
    glViewport( 0, 0, window.x, window.y );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D( -1., 1., -1.*(float)window.y/(float)window.x, 1.*(float)window.y/(float)window.x );
}


void setVideoMode( Vector2i window )
{
    if( NULL == SDL_SetVideoMode(window.x, window.y, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE) )
    {
        fprintf( stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n" );
        exit( EXIT_FAILURE );
    }
}


void drawLine( Vector2f pt1, Vector2f pt2 )
{
    glLineWidth( 2.5 );
    glBegin( GL_LINES );
    glColor3f( 1.0, 0.0, 0.0 );
    glVertex2f( pt1.x, pt1.y );
    glVertex2f( pt2.x, pt2.y );
    glEnd();
}


void drawPoint( Vector2f pt )
{
    glPointSize( 4.0 );
    glBegin( GL_POINTS );
    glColor3f( 0.0, 0.0, 1.0 );
    glVertex2f( pt.x, pt.y );
    glEnd();
}


void drawSelectedPoint( Vector2f pt )
{
    glPointSize( 6.0 );
    glBegin( GL_POINTS );
    glColor3f( 0.0, 1.0, 0.0 );
    glVertex2f( pt.x, pt.y );
    glEnd();
}


GLuint loadTexture( const char filename[], Vector2i *textureSize, int alpha )
{
    SDL_Surface* surface = IMG_Load( filename );
    if( surface == NULL )
        printf( "Error: \"%s\"\n", SDL_GetError() );

    GLint type = (alpha) ? GL_RGBA : GL_RGB;

    GLuint textureID;
    textureSize->x = surface->w;
    textureSize->y = surface->h;

    glGenTextures( 1, &textureID );
    glBindTexture( GL_TEXTURE_2D, textureID );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glTexImage2D( GL_TEXTURE_2D, 0, type, surface->w, surface->h, 0, type, GL_UNSIGNED_BYTE, surface->pixels );

    printf( "Texture %s [%d;%d] loaded\n", filename, surface->w, surface->h );

    SDL_FreeSurface( surface );
    return textureID;
}


void renderRect( Vector2f rectSize, unsigned int centered )
{
    glBegin( GL_POLYGON );
    glColor3f( 1.0, 1.0, 1.0 );

    if( centered )
    {
        glTexCoord2f( 0.0, 0.0 );
        glVertex2f( -rectSize.x, rectSize.y );
        glTexCoord2f( 1.0, 0.0 );
        glVertex2f( rectSize.x, rectSize.y );
        glTexCoord2f( 1.0, 1.0 );
        glVertex2f( rectSize.x, -rectSize.y );
        glTexCoord2f( 0.0, 1.0 );
        glVertex2f( -rectSize.x, -rectSize.y );
    }
    else
    {
        glTexCoord2f( 0.0, 0.0 );
        glVertex2f( 0, rectSize.y*2 );
        glTexCoord2f( 1.0, 0.0 );
        glVertex2f( rectSize.x*2, rectSize.y*2 );
        glTexCoord2f( 1.0, 1.0 );
        glVertex2f( rectSize.x*2, 0 );
        glTexCoord2f( 0.0, 1.0 );
        glVertex2f( 0, 0 );
    }

    glEnd();
}


Vector2f gameCooriToGLCoor( Vector2i vec, Vector2i windowSize )
{
    Vector2f vecGL;
    vecGL.x = ( ((float)vec.x) / windowSize.x );
    vecGL.y = ( ((float)vec.y) / windowSize.x );
    return vecGL;
}


void save( char* filename, Vector2i* pointsList, int nbPoints )
{
    FILE *f = fopen( filename, "w" );
    if( f == NULL )
    {
        printf("Error opening file!\n");
        exit(1);
    }

    int i = 0;
    for( ; i < nbPoints; i++ )
    {
        fprintf(f, "%i %i\n", pointsList[i].x, pointsList[i].y);
    }

    fclose(f);

    printf( "Collider %s successfully saved.\n", filename );
}


enum tool
{
    ADD_POINT, MOVE_POINT
};
typedef enum tool Tool;


unsigned int getClosestPoint( Vector2i* ptList, unsigned int nbPoints, Vector2i coor )
{
    unsigned int ptIndex = 0;
    float lowestDistance = 999999;
    int i = 0;
    for( ; i < nbPoints; i++ )
    {
        float distance = sqrt( (coor.x-ptList[i].x)*(coor.x-ptList[i].x) + (coor.y-ptList[i].y)*(coor.y-ptList[i].y) );
        if( distance < lowestDistance )
        {
            lowestDistance = distance;
            ptIndex = i;
        }
    }
    return ptIndex;
}


int main( int argc, char** argv )
{
    // Redirection du flux de sortie pour qu'il s'affiche dans la console
    freopen( "CON", "w", stdout );

    if( argc != 3 )
    {
        printf( "You need at least 2 arguments to run the collider creator.\n" );
        return EXIT_FAILURE;
    }

    printf( "\n---------------\nControls\n---------------\n");
    printf( "p : select tool Add_Point (default)\n" );
    printf( "o : select tool Move_Point\n" );
    printf( "s : save the collider file\n" );
    printf( "---------------\n\n" );

    Tool currentTool = ADD_POINT;
    printf( "Current tool : Add_Point\n" );

    /* Dimensions de la fenÃªtre */
    Vector2i windowSize;
    windowSize.x = 1280;
    windowSize.y = 720;

    Vector2i pointsList[50];
    unsigned int nbPoints = 0;
    unsigned int selectedPoint = -1;

    char* filename = argv[1];
    char* colliderFilename = argv[2];


    /* Initialisation de la SDL */
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
        return EXIT_FAILURE;
    }

    /* Ouverture d'une fenÃªtre et crÃ©ation d'un contexte OpenGL */
    setVideoMode( windowSize );
    reshape( windowSize );

    Vector2i textureSize;
    GLuint textureID = loadTexture( filename, &textureSize, 1 );

    float heightRatio = windowSize.y / textureSize.y;

    Vector2i newTextSize;
    newTextSize.x = textureSize.x*heightRatio;
    newTextSize.y = textureSize.y*heightRatio;

    Vector2f textureSizeGL;
    textureSizeGL = gameCooriToGLCoor( newTextSize, windowSize );

    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    /* Titre de la fenÃªtre */
    SDL_WM_SetCaption("Collider creator", NULL);


    /* Boucle d'affichage */
    int loop = 1;
    float xMove = 0, yMove = 0;

    float distance = 0 ;

    int rotateLPressed = 0, rotateRPressed = 0, movePressed = 0, acceleratePressed = 0;
    Uint32 startTime;


    glPointSize(1);
    int pressButton = 0;
    float angle = 0;

    int y2;
    int x2;


    while( loop )
    {
        /* RÃ©cupÃ©ration du temps au dÃ©but de la boucle */
        startTime = SDL_GetTicks();

        /* Boucle traitant les evenements */
        SDL_Event e;
        while(SDL_PollEvent(&e))
        {
            /* L'utilisateur ferme la fenÃªtre : */
            if( e.type == SDL_QUIT ) {
                loop = 0;
                break;
            }

            /* Quelques exemples de traitement d'evenements : */
            switch(e.type)
            {
                    /* Clic souris */
                case SDL_MOUSEBUTTONUP:
                    pressButton = 0;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    pressButton = 1;
                    if( currentTool == ADD_POINT )
                    {
                        pointsList[nbPoints].x = (e.motion.x - windowSize.x/2) / heightRatio;
                        pointsList[nbPoints].y = -(e.motion.y - windowSize.y/2) / heightRatio;
                        nbPoints++;
                        selectedPoint = nbPoints-1;
                    }
                    else if( currentTool == MOVE_POINT )
                    {
                        Vector2i pos;
                        pos.x = (e.motion.x - windowSize.x/2) / heightRatio;
                        pos.y = -(e.motion.y - windowSize.y/2) / heightRatio;
                        selectedPoint = getClosestPoint( pointsList, nbPoints, pos );
                    }
                    break;

                    /* move the mouse */
                    case SDL_MOUSEMOTION:
                        if( pressButton && currentTool == MOVE_POINT )
                        {
                            pointsList[selectedPoint].x = (e.motion.x - windowSize.x/2) / heightRatio;
                            pointsList[selectedPoint].y = -(e.motion.y - windowSize.y/2) / heightRatio;
                        }
                        break;

                    /* Touche clavier */
                case SDL_KEYDOWN:

                    switch( e.key.keysym.sym )
                    {
                        case SDLK_s :
                            save( colliderFilename, pointsList, nbPoints );
                            loop = 0;
                        break;

                        case SDLK_p :
                            if( currentTool != ADD_POINT )
                            {
                                currentTool = ADD_POINT;
                                printf( "CurrentTool : Add_Point\n" );
                            }
                        break;

                        case SDLK_o :
                            if( currentTool != MOVE_POINT )
                            {
                                currentTool = MOVE_POINT;
                                printf( "CurrentTool : Move_Point\n" );
                            }
                        break;

                        case SDLK_UP :

                        break;
                    }

                    break;

                case SDL_KEYUP:
                    break;

                default:
                    break;
            }
        }

        glClear(GL_COLOR_BUFFER_BIT);

        /* Placer ici le code de dessin */
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glEnable( GL_TEXTURE_2D );
        glBindTexture( GL_TEXTURE_2D, textureID );
        renderRect( textureSizeGL, 1 );
        glDisable( GL_TEXTURE_2D );

        int i = 0;
        for( ; i < nbPoints; i++ )
        {
            int lastIndex = (i==nbPoints-1) ? 0 : i+1;

            Vector2i sized1;
            sized1.x = pointsList[i].x * heightRatio * 2;
            sized1.y = pointsList[i].y * heightRatio * 2;

            Vector2i sized2;
            sized2.x = pointsList[lastIndex].x * heightRatio * 2;
            sized2.y = pointsList[lastIndex].y * heightRatio * 2;

            Vector2f pt1 = gameCooriToGLCoor( sized1, windowSize );
            Vector2f pt2 = gameCooriToGLCoor( sized2, windowSize );

            drawLine( pt1, pt2 );
            drawPoint( pt1 );

            if( i == selectedPoint )
                drawSelectedPoint( pt1 );
        }

        /* Echange du front et du back buffer : mise Ã  jour de la fenÃªtre */
        SDL_GL_SwapBuffers();

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
