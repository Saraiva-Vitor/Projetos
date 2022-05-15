#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <GL/glext.h>
#include <math.h>
#include <time.h>
#include "stb_image.h"

const int width = 1280;
const int height = 720;

const int FishAmount = 4;
bool win = true;

GLfloat angle, fAspect, rotX;
GLfloat rotY;
GLdouble obsX, obsY, obsZ;

int random(int i, int f)
{
	int random = i + rand() % f;
	if(random >= f) return f-10;
	else return random;
}

GLint pengx = 100;
GLint pengy = 4;
GLint pengz = 100;
bool withFish = false;
GLint pengwalking = 0;
GLint walkingAnimationAngle = 0;

GLint fishsx[] = {random(0,150),random(0,150),random(0,150),random(0,150)};
GLint fishsz[] = {random(0,150),random(0,150),random(0,150),random(0,150)};
GLint fishsy[] = {-4,-4,-4,-4};
GLint FishAmountAux = 4;
bool fishCollision[FishAmount-1] = {false};

GLint holesxAUX[] = {0,0,0};
GLint holeszAUX[] = {0,0,0};

int cont = 610;
double seconds = 0;
int score = 0;

GLuint texID[9];

char* textureFileNames[9] = {"textures/penguin_texture.png",
							 "textures/fish_texture.png",
							 "textures/snow_texture.jpg",
							 "skybox/back.jpg",
							 "skybox/bottom.jpg",
							 "skybox/front.jpg",
							 "skybox/right.jpg",
							 "skybox/left.jpg",
							 "skybox/top.jpg"
};

void Skybox(){
	GLint width = 500;
	GLint height = 500;
	GLint length = 500;
	glBindTexture( GL_TEXTURE_2D, texID[8]);
	glBegin(GL_QUADS);
	//glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f( width, height, -length); // Top Right Of The Quad (Top)
	glTexCoord2d(1.0f, 1.0f); glVertex3f(-width, height, -length); // Top Left Of The Quad (Top)
	glTexCoord2d(0.0, 1.0f); glVertex3f(-width, height, length); // Bottom Left Of The Quad (Top)
	glTexCoord2d(0.0, 0.0f); glVertex3f( width, height, length); // Bottom Right Of The Quad (Top)
	glTexCoord2d(1.0f, 0.0f); glVertex3f( width, height, -length);
	glEnd();

	glBindTexture( GL_TEXTURE_2D, texID[5]);
	glBegin(GL_QUADS);
	//glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2d(0.0f, 0.0f); glVertex3f( width, height, length); // Top Right Of The Quad (Front)
	glTexCoord2d(1.0f, 0.0f); glVertex3f(-width, height, length); // Top Left Of The Quad (Front)
	glTexCoord2d(1.0f, 1.0f); glVertex3f(-width, -height, length); // Bottom Left Of The Quad (Front)
	glTexCoord2d(0.0f, 1.0f); glVertex3f( width, -height, length); // Bottom Right Of The Quad (Front)
	glTexCoord2d(0.0f, 0.0f); glVertex3f( width, height, length);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texID[3]);
	glBegin(GL_QUADS);
	//glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f( width, -height, -length); // Bottom Left Of The Quad (Back)
	glTexCoord2d(1.0f, 1.0f); glVertex3f(-width, -height, -length); // Bottom Right Of The Quad (Back)
	glTexCoord2d(1.0f, 0.0f); glVertex3f(-width, height, -length); // Top Right Of The Quad (Back)
	glTexCoord2d(0.0f, 0.0f); glVertex3f( width, height, -length); // Top Left Of The Quad (Back)
	glTexCoord2d(0.0f, 1.0f); glVertex3f( width, -height, -length);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texID[6]);
	glBegin(GL_QUADS);
	//glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(-width, height, -length); // Top Right Of The Quad (Left)
	glTexCoord2d(1.0f, 1.0f); glVertex3f(-width, -height, -length); // Top Left Of The Quad (Left)
	glTexCoord2d(0.0f, 1.0f); glVertex3f(-width, -height, length); // Bottom Left Of The Quad (Left)
	glTexCoord2d(0.0f, 0.0f); glVertex3f(-width, height, length); // Bottom Right Of The Quad (Left)
	glTexCoord2d(1.0f, 0.0f); glVertex3f(-width, height, -length);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texID[7]);
	glBegin(GL_QUADS);
	//glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2d(0.0f, 0.0f); glVertex3f( width, height, -length); // Top Right Of The Quad (Right)
	glTexCoord2d(1.0f, 0.0f); glVertex3f( width, height, length); // Top Left Of The Quad (Right)
	glTexCoord2d(1.0f, 1.0f); glVertex3f( width, -height, length); // Bottom Left Of The Quad (Right)
	glTexCoord2d(0.0f, 1.0f); glVertex3f( width, -height, -length); // Bottom Right Of The Quad (Right)
	glTexCoord2d(0.0f, 0.0f); glVertex3f( width, height, -length);
	glEnd();
}

bool CheckCollision(float rect1x, float rect1y, float rect1z, float rect1Width, float rect1Height, float rect1Depth, float rect2x, float rect2y, float rect2z, float rect2Width, float rect2Height, float rect2Depth){
	if (rect1x < rect2x + rect2Width &&
	   rect1x + rect1Width > rect2x &&
	   rect1y < rect2y + rect2Height &&
	   rect1y + rect1Height > rect2y &&
	   rect1z < rect2z + rect2Depth &&
	   	   rect1z + rect1Depth > rect2z) {
	    // collision detected!
		return true;
	}else return false;
}

void drawText(void *font, char *string){
	{
		// Exibe caractere a caractere
		while(*string)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*string++);
	}

}

void timer(int value){
	seconds += 1.0/60.0;
	cont -= 10;
	score++;
	glutPostRedisplay();
	glutTimerFunc(1000,timer,0);
}

void DefineIluminacao (void)
{
GLfloat luzAmbiente[4]={0.4,0.4,0.4,1.0};
GLfloat luzDifusa[4]={0.6,0.6,0.6,1.0}; // "cor"
GLfloat luzEspecular[4]={0.8, 0.8, 0.8, 1.0};// "brilho"
GLfloat posicaoLuz[4]={0.0, 50.0, 0.0, 1.0};
GLfloat especularidade[4]={1.0,1.0,1.0,1.0};
GLint especMaterial = 60;
glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
glMateriali(GL_FRONT,GL_SHININESS,especMaterial);
glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);
glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );
}

void drawHole(GLfloat radius,GLfloat height){
    GLfloat x              = 0.0;
    GLfloat y              = 0.0;
    GLfloat angle          = 0.0;
    GLfloat angle_stepsize = 1.0;

    /** Draw the tube */
    glColor3f(0.7,0.7,0.7);
    glBegin(GL_QUAD_STRIP);
    angle = 0.0;
        while( angle < 2*M_PI ) {
            x = radius * cos(angle);
            y = radius * sin(angle);
            glVertex3f(x, y , height);
            glVertex3f(x, y , 0.0);
            angle = angle + angle_stepsize;
        }
        glVertex3f(radius, 0.0, height);
        glVertex3f(radius, 0.0, 0.0);
    glEnd();
    /** Draw the circle on top of cylinder */
    glColor3f(0.0,0.0,1.0);
    glBegin(GL_POLYGON);
    angle = 0.0;
        while( angle < 2*M_PI ) {
            x = radius * cos(angle);
            y = radius * sin(angle);
            glVertex3f(x, y , height);
            angle = angle + angle_stepsize;
        }
        glVertex3f(radius, 0.0, height);
    glEnd();
}

void drawFish(){
	//Corpo
	glBindTexture( GL_TEXTURE_2D, texID[1] );
	glPushMatrix();
		glRotatef(90,0,0,1);
		glScalef(0.5,0.8,0.3);
		glTranslatef(2,2,2);
		glColor3f(0.0,0.7,0.7);
		glutSolidSphere(1.0, 16, 8);
	glPopMatrix();

	glBindTexture( GL_TEXTURE_2D, texID[1] );
	//Cauda
	glPushMatrix();
		glRotatef(-90,0,1,0);
		glScalef(0.5,1,1);
		glTranslatef(1.2,1,0.5);
		glColor3f(0.0,0.7,1.0);
		glutSolidCone(0.3,0.6,16,8);
	glPopMatrix();
}

void drawPenguin(){
	glMatrixMode(GL_MODELVIEW);

	    //Cabeca
		//glBindTexture( GL_TEXTURE_2D, texID[0] );
	    glPushMatrix();
	    glColor3f(0.1,0.1,0.1);
	    glutSolidSphere(0.8, 16, 8);
	    glPopMatrix();

	    //Olhos
	    glPushMatrix();
	    	glTranslatef(-0.3,0.4,0.5);
	    	glColor3f(1.0,1.0,1.0);
	    	glutSolidSphere(0.15, 16, 8);
	    glPopMatrix();
	    glPushMatrix();
	    	glTranslatef(-0.35,0.4,0.6);
	    	glColor3f(0.0,0.0,0.0);
	    	glutSolidSphere(0.08, 16, 8);
	    glPopMatrix();
	    glPushMatrix();
	    	glTranslatef(0.3,0.4,0.5);
	    	glColor3f(1.0,1.0,1.0);
	    	glutSolidSphere(0.15, 16, 8);
	    glPopMatrix();
	    glPushMatrix();
	    	glTranslatef(0.35,0.4,0.6);
	    	glColor3f(0.0,0.0,0.0);
	    	glutSolidSphere(0.08, 16, 8);
	    glPopMatrix();

	    //Bico
	    glTranslatef(0,-0.1,0.6);
	    glPushMatrix();
	    glColor3f(1.0,0.6,0.0);
	    	glutSolidCone(0.3,0.6,16,8);
	    glPopMatrix();

	    //Corpo
	    //glBindTexture( GL_TEXTURE_2D, texID[0] );
	    glPushMatrix();
	    	glTranslatef(0,-2,-1);
	    	glColor3f(0.1,0.1,0.1);
	    	glScalef(1,2,1);
	    	glutSolidSphere(1.0, 16, 8);
	    glPopMatrix();
	   	glPushMatrix();
	   		glTranslatef(0,-2,-0.5);
	   		glColor3f(1.0,1.0,1.0);
	   		glScalef(0.7,1.7,0.7);
	   		glutSolidSphere(1.0, 16, 8);
	   	glPopMatrix();

	   	//Patas
	   	glPushMatrix();
	   		glTranslatef(0.4,-3.8,-0.3);
	   		glRotatef(-90,1,0,0);
	   		glColor3f(1.0,0.6,0.0);
	   		glutSolidCone(0.3,0.5,16,8);
	   	glPopMatrix();
	   	glPushMatrix();
	   		glTranslatef(-0.4,-3.8,-0.3);
	   		glRotatef(-90,1,0,0);
	   		glColor3f(1.0,0.6,0.0);
	   		glutSolidCone(0.3,0.5,16,8);
	   	glPopMatrix();

	   	//Nadadeiras
	   	glPushMatrix();
   			glRotatef(walkingAnimationAngle,1,0,0);
	   		glTranslatef(-1,-2,-1);
	   		glColor3f(0.1,0.1,0.1);
	   		glScalef(0.2,1,0.5);
	   		glutSolidSphere(1.0, 16, 8);
	    glPopMatrix();
	    glPushMatrix();
	    	glRotatef(-walkingAnimationAngle,1,0,0);
	    	glTranslatef(1,-2,-1);
	    	glColor3f(0.1,0.1,0.1);
	    	glScalef(0.2,1,0.5);
	    	glutSolidSphere(1.0, 16, 8);
	    glPopMatrix();

		if(withFish == true){
			glPushMatrix();
			glTranslatef(1.5,-1,0);
			drawFish();
			glPopMatrix();
		}
}


void drawBabyPenguin(){
	glMatrixMode(GL_MODELVIEW);

	    //Cabeca
		//glBindTexture( GL_TEXTURE_2D, texID[0] );
	    glPushMatrix();
	    glColor3f(0.5,0.5,0.5);
	    glutSolidSphere(0.8, 16, 8);
	    glPopMatrix();

	    //Olhos
	    glPushMatrix();
	    	glTranslatef(-0.3,0.4,0.5);
	    	glColor3f(1.0,1.0,1.0);
	    	glutSolidSphere(0.15, 16, 8);
	    glPopMatrix();
	    glPushMatrix();
	    	glTranslatef(-0.35,0.4,0.6);
	    	glColor3f(0.0,0.0,0.0);
	    	glutSolidSphere(0.08, 16, 8);
	    glPopMatrix();
	    glPushMatrix();
	    	glTranslatef(0.3,0.4,0.5);
	    	glColor3f(1.0,1.0,1.0);
	    	glutSolidSphere(0.15, 16, 8);
	    glPopMatrix();
	    glPushMatrix();
	    	glTranslatef(0.35,0.4,0.6);
	    	glColor3f(0.0,0.0,0.0);
	    	glutSolidSphere(0.08, 16, 8);
	    glPopMatrix();

	    //Bico
	    glTranslatef(0,-0.1,0.6);
	    glPushMatrix();
	    glColor3f(1.0,0.6,0.0);
	    	glutSolidCone(0.3,0.6,16,8);
	    glPopMatrix();

	    //Corpo
	    //glBindTexture( GL_TEXTURE_2D, texID[0] );
	    glPushMatrix();
	    	glTranslatef(0,-2,-1);
	    	glColor3f(0.5,0.5,0.5);
	    	glScalef(1,2,1);
	    	glutSolidSphere(1.0, 16, 8);
	    glPopMatrix();
	   	glPushMatrix();
	   		glTranslatef(0,-2,-0.5);
	   		glColor3f(1.0,1.0,1.0);
	   		glScalef(0.7,1.7,0.7);
	   		glutSolidSphere(1.0, 16, 8);
	   	glPopMatrix();

	   	//Patas
	   	glPushMatrix();
	   		glTranslatef(0.4,-3.8,-0.3);
	   		glRotatef(-90,1,0,0);
	   		glColor3f(1.0,0.6,0.0);
	   		glutSolidCone(0.3,0.5,16,8);
	   	glPopMatrix();
	   	glPushMatrix();
	   		glTranslatef(-0.4,-3.8,-0.3);
	   		glRotatef(-90,1,0,0);
	   		glColor3f(1.0,0.6,0.0);
	   		glutSolidCone(0.3,0.5,16,8);
	   	glPopMatrix();

	   	//Nadadeiras
	   	glPushMatrix();
	   		glTranslatef(-1,-2,-1);
	   		glColor3f(0.5,0.5,0.5);
	   		glScalef(0.2,1,0.5);
	   		glutSolidSphere(1.0, 16, 8);
	    glPopMatrix();
	    glPushMatrix();
	    	glTranslatef(1,-2,-1);
	    	glColor3f(0.5,0.5,0.5);
	    	glScalef(0.2,1,0.5);
	    	glutSolidSphere(1.0, 16, 8);
	    glPopMatrix();
}

void drawTerrain(){
	glBindTexture( GL_TEXTURE_2D, texID[2]);
	glColor3f(1,1,1);
	glBegin(GL_QUADS);
		glVertex3f(200,-4,200);
		glVertex3f(0,-4,200);
		glVertex3f(0,-4,0);
		glVertex3f(200,-4,0);
	glEnd();
}

void DentroDoDesenha(){
	glPushMatrix();
	//Draw Fish
	if(FishAmountAux == 4){
	for(int i=0; i<FishAmount; i++){
		glPushMatrix();
		glTranslatef(fishsx[i],fishsy[i],fishsz[i]);
		drawFish();
		glPopMatrix();
	}
	}
	glPopMatrix();

	drawTerrain();

	GLint holesx[] = {random(0,150),random(0,150),random(0,150),random(0,150),random(0,150),random(0,150)};
	GLint holesz[] = {random(0,150),random(0,150),random(0,150),random(0,150),random(0,150),random(0,150)};
	for(int cont=0;cont<6;cont++){
		holesxAUX[cont] = holesx[cont];
		holeszAUX[cont] = holesz[cont];
		glPushMatrix();
			glTranslatef(holesx[cont],-6,holesz[cont]);
			glRotatef(-90,1,0,0);
			drawHole(5,3);
		glPopMatrix();
	}

	glPushMatrix();
		glTranslatef(pengx,pengy,pengz);
		glScalef(2,2,2);
		glRotatef(rotY,0,1,0);
		drawPenguin();
	glPopMatrix();

	/*/Penguin Collision Box
		glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_QUADS);
			glVertex3f(pengx-3,pengy-7,pengz+3);
			glVertex3f(pengx+3,pengy-7,pengz+3);
			glVertex3f(pengx+3,pengy+3,pengz+3);
			glVertex3f(pengx-3,pengy+3,pengz+3);
			glVertex3f(pengx-3,pengy-7,pengz+3);
		glEnd();
		glBegin(GL_QUADS);
			glVertex3f(pengx-3,pengy-7,pengz-3);
			glVertex3f(pengx+3,pengy-7,pengz-3);
			glVertex3f(pengx+3,pengy+3,pengz-3);
			glVertex3f(pengx-3,pengy+3,pengz-3);
			glVertex3f(pengx-3,pengy-7,pengz-3);
		glEnd();
		glBegin(GL_QUADS);
			glVertex3f(pengx+3,pengy-7,pengz-3);
			glVertex3f(pengx+3,pengy-7,pengz+3);
			glVertex3f(pengx+3,pengy+3,pengz+3);
			glVertex3f(pengx+3,pengy+3,pengz-3);
			glVertex3f(pengx+3,pengy-7,pengz-3);
		glEnd();
		glBegin(GL_QUADS);
			glVertex3f(pengx-3,pengy-7,pengz-3);
			glVertex3f(pengx-3,pengy-7,pengz+3);
			glVertex3f(pengx-3,pengy+3,pengz+3);
			glVertex3f(pengx-3,pengy+3,pengz-3);
			glVertex3f(pengx-3,pengy-7,pengz-3);
		glEnd();*/

	/*/Baby Penguin Collision Box
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
		glVertex3f(90-1.5,0-3.5,90+1.5);
		glVertex3f(90+1.5,0-3.5,90+1.5);
		glVertex3f(90+1.5,0+1.5,90+3);
		glVertex3f(90-1.5,0+1.5,90+1.5);
		glVertex3f(90-1.5,0-3.5,90+1.5);
	glEnd();
	glBegin(GL_QUADS);
		glVertex3f(90-1.5,0-3.5,90-1.5);
		glVertex3f(90+1.5,0-3.5,90-1.5);
		glVertex3f(90+1.5,0+1.5,90-1.5);
		glVertex3f(90-1.5,0+1.5,90-1.5);
		glVertex3f(90-1.5,0-3.5,90-1.5);
	glEnd();
	glBegin(GL_QUADS);
		glVertex3f(90+1.5,0-3.5,90-1.5);
		glVertex3f(90+1.5,0-3.5,90+1.5);
		glVertex3f(90+1.5,0+1.5,90+1.5);
		glVertex3f(90+1.5,0+1.5,90-1.5);
		glVertex3f(90+1.5,0-3.5,90-1.5);
	glEnd();
	glBegin(GL_QUADS);
		glVertex3f(90-1.5,0-3.5,90-1.5);
		glVertex3f(90-1.5,0-3.5,90+1.5);
		glVertex3f(90-1.5,0+1.5,90+1.5);
		glVertex3f(90-1.5,0+1.5,90-1.5);
		glVertex3f(90-1.5,0-3.5,90-1.5);
	glEnd();*/

	/*/Fish Collision Box
	glColor3f(1.0f, 0.0f, 0.0f);
	for(int i=0; i<FishAmount; i++){
		glBegin(GL_QUADS);
			glVertex3f(fishsx[i]-3,fishsy[i]-1,fishsz[i]-1);
			glVertex3f(fishsx[i]-3,fishsy[i]-1,fishsz[i]+1);
			glVertex3f(fishsx[i]-3,fishsy[i]+1,fishsz[i]+1);
			glVertex3f(fishsx[i]-3,fishsy[i]+1,fishsz[i]-1);
			glVertex3f(fishsx[i]-3,fishsy[i]-1,fishsz[i]-1);
		glEnd();
		glBegin(GL_QUADS);
			glVertex3f(fishsx[i]+0,fishsy[i]-1,fishsz[i]-1);
			glVertex3f(fishsx[i]+0,fishsy[i]-1,fishsz[i]+1);
			glVertex3f(fishsx[i]+0,fishsy[i]+1,fishsz[i]+1);
			glVertex3f(fishsx[i]+0,fishsy[i]+1,fishsz[i]-1);
			glVertex3f(fishsx[i]+0,fishsy[i]-1,fishsz[i]-1);
		glEnd();
		glBegin(GL_QUADS);
			glVertex3f(fishsx[i]-3,fishsy[i]-1,fishsz[i]-1);
			glVertex3f(fishsx[i]+0,fishsy[i]-1,fishsz[i]-1);
			glVertex3f(fishsx[i]+0,fishsy[i]+1,fishsz[i]-1);
			glVertex3f(fishsx[i]-3,fishsy[i]+1,fishsz[i]-1);
			glVertex3f(fishsx[i]-3,fishsy[i]-1,fishsz[i]-1);
		glEnd();
		glBegin(GL_QUADS);
			glVertex3f(fishsx[i]-3,fishsy[i]-1,fishsz[i]+1);
			glVertex3f(fishsx[i]+0,fishsy[i]-1,fishsz[i]+1);
			glVertex3f(fishsx[i]+0,fishsy[i]+1,fishsz[i]+1);
			glVertex3f(fishsx[i]-3,fishsy[i]+1,fishsz[i]+1);
			glVertex3f(fishsx[i]-3,fishsy[i]-1,fishsz[i]+1);
		glEnd();
	}*/

	/*/Holes Collision Box
	glColor3f(1.0f, 0.0f, 0.0f);
	for(int i=0; i<3; i++){
		glBegin(GL_QUADS);
			glVertex3f(holesx[i]-5,-4-2,holesz[i]-5);
			glVertex3f(holesx[i]-5,-4-2,holesz[i]+5);
			glVertex3f(holesx[i]-5,-4+2,holesz[i]+5);
			glVertex3f(holesx[i]-5,-4+2,holesz[i]-5);
			glVertex3f(holesx[i]-5,-4-2,holesz[i]-5);
		glEnd();
		glBegin(GL_QUADS);
			glVertex3f(holesx[i]+5,-4-2,holesz[i]-5);
			glVertex3f(holesx[i]+5,-4-2,holesz[i]+5);
			glVertex3f(holesx[i]+5,-4+2,holesz[i]+5);
			glVertex3f(holesx[i]+5,-4+2,holesz[i]-5);
			glVertex3f(holesx[i]+5,-4-2,holesz[i]-5);
		glEnd();
		glBegin(GL_QUADS);
			glVertex3f(holesx[i]-5,-4-2,holesz[i]-5);
			glVertex3f(holesx[i]+5,-4-2,holesz[i]-5);
			glVertex3f(holesx[i]+5,-4+2,holesz[i]-5);
			glVertex3f(holesx[i]-5,-4+2,holesz[i]-5);
			glVertex3f(holesx[i]-5,-4-2,holesz[i]-5);
		glEnd();
		glBegin(GL_QUADS);
			glVertex3f(holesx[i]-5,-4-2,holesz[i]+5);
			glVertex3f(holesx[i]+5,-4-2,holesz[i]+5);
			glVertex3f(holesx[i]+5,-4+2,holesz[i]+5);
			glVertex3f(holesx[i]-5,-4+2,holesz[i]+5);
			glVertex3f(holesx[i]-5,-4-2,holesz[i]+5);
		glEnd();
	}*/

	//Baby Penguin
	glPushMatrix();
		glTranslatef(90,0,90);
		glScalef(1,1,1);
		drawBabyPenguin();
	glPopMatrix();

}

void Collisions(){
	//Collision Penguin x Hole
	for(int i=0; i<3; i++){
		if(CheckCollision(pengx, pengy, pengz,6,10,6,holesxAUX[i],-6,holeszAUX[i],7,100,7) == true && win == false){
			exit(1);
		}
	}
	//Collision Penguin x Baby Penguin
	if((CheckCollision(pengx, pengy, pengz,6,10,6, 90,0,90, 3,5,3) == true)  && withFish == true){
		withFish = false;
		cont+=600;
	}

	//Collision Penguin x Fish
	for(int i=0; i<FishAmount; i++){
		if(CheckCollision(pengx, pengy, pengz,6,10,6,fishsx[i],fishsy[i],fishsz[i],3,10,2) == true  && withFish == false){
			fishCollision[i]=true;
			withFish = true;
			if(fishCollision[i]==true){
				fishsx[i] = random(0,150);
				fishsz[i] = random(0,150);
			}
		}
	}
}

void HUD(){
	if(score >= 300){
		glPushMatrix();
		glRasterPos2f(315,250);
		drawText(GLUT_BITMAP_TIMES_ROMAN_24, "VOCE GANHOU!!!");
		glPopMatrix();
		win = true;
	}
	if(cont >=610) cont=610;
	if(cont <=10 && win == false){
		exit(1);
	}

	glRasterPos2f(10,20);
	drawText(GLUT_BITMAP_TIMES_ROMAN_24, "VIDA DO FILHOTE: ");

	if(cont <= 600 && cont >= 500) {
		glRasterPos2f(240,20);
		drawText(GLUT_BITMAP_TIMES_ROMAN_24, "6");
	}
	if(cont <= 500 && cont >= 400) {
		glRasterPos2f(240,20);
		drawText(GLUT_BITMAP_TIMES_ROMAN_24, "5");
	}
	if(cont <=400 && cont >= 300) {
		glRasterPos2f(240,20);
		drawText(GLUT_BITMAP_TIMES_ROMAN_24, "4");
	}
	if(cont <= 300 && cont >= 200) {
		glRasterPos2f(240,20);
		drawText(GLUT_BITMAP_TIMES_ROMAN_24, "3");
	}
	if(cont <= 200 && cont >= 100) {
		glRasterPos2f(240,20);
		drawText(GLUT_BITMAP_TIMES_ROMAN_24, "2");
	}
	if(cont <= 100 && cont >= 0) {
		glRasterPos2f(240,20);
		drawText(GLUT_BITMAP_TIMES_ROMAN_24, "1");
	}
}

void Desenha(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	DefineIluminacao();
	glPushMatrix();
		glViewport(0, height/2, width/2, height/2);
		gluLookAt(0, 0, 0, 0, 0, -1, 0, 1, 0);
		gluLookAt(0, 0, 0, pengx, pengy, -pengz, 0, 1, 0);
		DentroDoDesenha();
		Collisions();
		Skybox();
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0.0, width/2, height/2, 0.0, -1.0, 10.0);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glDisable(GL_CULL_FACE);

		glClear(GL_DEPTH_BUFFER_BIT);

		//Draw Score and Life Bar
		HUD();

		// Making sure we can render 3d again
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glViewport(width/2, height/2, width/2, height/2);
		gluLookAt(0, 1, 0, 0, 0, -1, 0, 1, 0);
		gluLookAt(0, 1, 0, pengx, pengy, -pengz, 0, 1, 0);
		DentroDoDesenha();
		Collisions();
		Skybox();
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0.0, width/2, height/2, 0.0, -1.0, 10.0);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glDisable(GL_CULL_FACE);

		glClear(GL_DEPTH_BUFFER_BIT);

		//Draw Score and Life Bar
		HUD();

		// Making sure we can render 3d again
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glViewport(width/2, 0, width/2, height/2);
		gluLookAt(50, 0, 100, 0, 0, -2, 0, 1, 0);
		gluLookAt(50, 0, 100, pengx, pengy, -2*pengz, 0, 1, 0);
		DentroDoDesenha();
		Collisions();
		Skybox();
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0.0,  width/2, height/2, 0.0, -1.0, 10.0);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glDisable(GL_CULL_FACE);

		glClear(GL_DEPTH_BUFFER_BIT);

		//Draw Score and Life Bar
		HUD();

		// Making sure we can render 3d again
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glViewport(0, 0, width/2, height/2);
		gluLookAt(0.3, 0.2, 1, 0.2, 0, -1, 0, 1, 0);
		gluLookAt(0.3, 0.2, 1, 0.2*pengx, pengy, -pengz, 0, 1, 0);
		DentroDoDesenha();
		Collisions();
		Skybox();
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0.0,  width/2, height/2, 0.0, -1.0, 10.0);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glDisable(GL_CULL_FACE);

		glClear(GL_DEPTH_BUFFER_BIT);

		//Draw Score and Life Bar
		HUD();

		// Making sure we can render 3d again
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
	glPopMatrix();

	glutSwapBuffers();
}

void tick(int){
	srand((unsigned) time(0));
	glutTimerFunc(1000/30,tick,0);
	pengwalking+=1;
	glutPostRedisplay();
}

void Inicializa(void)
{
	srand((unsigned) time(0));
	glClearColor(0.5f, 0.7f, 0.8f, 1.0f);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_SCISSOR_TEST);
	glEnable(GL_TEXTURE_2D);
    float white[4] = { 1, 1, 1, 1 };  // A white material, suitable for texturing.
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);
	glShadeModel(GL_SMOOTH);
	angle=50;
	rotX = 30;
	rotY = 0;
	obsZ = 180;
}

void PosicionaObservador(void)
{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		DefineIluminacao();
		glTranslatef(-100,50,-obsZ);
		glRotatef(rotX,1,0,0);
}

void EspecificaParametrosVisualizacao(void)
{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		gluPerspective(angle,fAspect,0.5,500);
		//gluLookAt(0,0,0.5,pengx,pengy,pengz,0.0f,1.0f,0.0f);

		PosicionaObservador();
}

void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
		if ( h == 0 ) h = 1;
		glViewport(0,0, w, h);
		fAspect = (GLfloat)w/(GLfloat)h;
		EspecificaParametrosVisualizacao();
}

void GerenciaMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN) {
			// Zoom-in
			if (angle >= 10)
				angle -= 15;
		}
	if (button == GLUT_RIGHT_BUTTON)
		if (state == GLUT_DOWN) {
			// Zoom-out
			if (angle <= 130)
				angle += 15;
		}
	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}

void TeclasEspeciais (int tecla, int x, int y)
{
	switch (tecla)
	{
		case GLUT_KEY_LEFT:
			rotY-=10;
			if(rotY<0){
				rotY = -(rotY/360) + 360;
			}
			break;
		case GLUT_KEY_RIGHT:
			rotY+=10;
			if(rotY>360){
				rotY = fmod(rotY,360);
			}
			break;
		case GLUT_KEY_UP:
			if(rotY>0 && rotY<90){
				pengx++;
				pengz++;
			}else if(rotY==0 || rotY==360){
				pengz++;
			}else if(rotY>90 && rotY<180){
				pengx++;
				pengz--;
			}else if(rotY==90){
				pengx++;
			}else if(rotY>180 && rotY<270){
				pengx--;
				pengz--;
			}else if(rotY==180){
				pengz--;
			}else if(rotY>270 && rotY<360){
				pengx--;
				pengz++;
			}else if(rotY==270){
				pengx--;
			}

			if(pengx>=200) pengx = 200;
			if(pengz>=200) pengz = 200;
			if(pengx<=0) pengx = 0;
			if(pengz<=0) pengz = 0;

			walkingAnimationAngle = 20*pow(-1,pengwalking);

			break;
		case GLUT_KEY_DOWN:
			if(rotY>0 && rotY<90){
				pengx--;
				pengz--;
			}else if(rotY==0 || rotY==360){
				pengz--;
			}else if(rotY>90 && rotY<180){
				pengx--;
				pengz++;
			}else if(rotY==90){
				pengx--;
			}else if(rotY>180 && rotY<270){
				pengx++;
				pengz++;
			}else if(rotY==180){
				pengz++;
			}else if(rotY>270 && rotY<360){
				pengx++;
				pengz--;
			}else if(rotY==270){
				pengx++;
			}

			if(pengx>=200) pengx = 200;
			if(pengz>=200) pengz = 200;
			if(pengx<=0) pengx = 0;
			if(pengz<=0) pengz = 0;

			walkingAnimationAngle = -20*pow(-1,pengwalking);

			break;
		case GLUT_KEY_HOME:
			obsZ+=15;
			break;
		case GLUT_KEY_END:
			obsZ-=15;
			break;
	}
	PosicionaObservador();
	glutPostRedisplay();
}

void loadTextures() {
	int width, height, nrChannels;
	unsigned char *data;

	glGenTextures(8, texID);

	for(int i = 0; i < 9;i++)
	{
	glBindTexture(GL_TEXTURE_2D, texID[i]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load(textureFileNames[i], &width, &height, &nrChannels, 0);

	if (data)
	{
	    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE );
	}
	else
	{
		 printf("Failed to load texture\n");
	}
	stbi_image_free(data);
	}
}

int main()
{
	int argc = 0;
	char *argv[] = { (char *)"gl", 0 };
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(5,5);
	glutInitWindowSize(width,height);
	glutCreateWindow("Trabalho 2 - Gabriel Calheias e Vitor Saraiva");
	glutDisplayFunc(Desenha);
	glutTimerFunc(0,tick,0);
	glutTimerFunc(1000,timer,0);
	glutSpecialFunc(TeclasEspeciais);
    glutReshapeFunc(AlteraTamanhoJanela);
	glutMouseFunc(GerenciaMouse);
	Inicializa();
	loadTextures();
	glutMainLoop();
}

