#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <random>
#include <iomanip>
#include <time.h>
#include <string>
#include <unistd.h>

using namespace std;

const double PI = 3.141592654;
const int FishAmount = 4;
bool win = false;

int randomXFishPosition()
{
	srand((unsigned) time(0));
	int randomx = 300 + rand() % 700;
	if(randomx >= 700) return 600;
	else return randomx;
}

int randomYFishPosition()
{
	srand((unsigned) time(0));
	int randomy = 10 + rand() % 100;
	if(randomy <= 0) return 140;
	else return randomy;
}

int randomXPetrelInicioAttack()
{
	srand((unsigned) time(0));
	return 300 + rand() % 700;
}

int randomXPetrelFimAttack()
{
	srand((unsigned) time(0));
	return 0 + rand() % 300;
}

int randomYPetrelPosition()
{
	srand((unsigned) time(0));
	return 50 + rand() % 350;
}


bool pengright = true;
int pengx = 200;
int pengy = 180;
int pengz = 0;
bool withFish = false;

bool petleft = true;
int petx = 640;
int pety = 450;
int petz = 0;

int fishx[] = {randomXFishPosition(),randomXFishPosition(),randomXFishPosition(),randomXFishPosition()};
int fishy[] = {20,60,100,140};
int fishz = 0;
int FishAmountAux = 4;
bool fishCollision[FishAmount-1] = {false};

int cont = 610;
double seconds = 0;
int score = 0;

bool water = false;
bool rightFish[FishAmount-1] = {true};

void drawElipse(double focox, double focoy) {
	int d;
	glBegin(GL_POLYGON);
	for (d = 0; d < 32; d++) {
		double angle = 2*PI/32 * d;
		glVertex2d(focox*cos(angle), focoy*sin(angle));
	}
	glEnd();
	glutPostRedisplay();
}

void FishMovement(int i){
	if(fishx[i]<700 && rightFish[i]==true){
		rightFish[i] = true;
		fishx[i]=fishx[i]+2;
	}
	if(fishx[i]>=700) rightFish[i]=false;
	if(fishx[i]>320 && rightFish[i]==false){
		rightFish[i] = false;
		fishx[i]=fishx[i]-2;
	}
	if(fishx[i]<=320) rightFish[i] = true;
	glutPostRedisplay();
}

void PetrelMovement(){
	float L0, L1, L2;
	float inicioattackX, fimattackX, fimattackY,meioattackX;
	float inicioattackY = 450;
	float meioattackY = 180;

	if(petleft == true){
		srand(time(NULL));
		inicioattackX = randomXPetrelInicioAttack();
		fimattackX = randomXPetrelFimAttack();
		fimattackY = randomYPetrelPosition();
		meioattackX = (inicioattackX+fimattackX)/2;

		L0 = ((petx-meioattackX)*(petx-fimattackX))/((inicioattackX-meioattackX)*(inicioattackX-fimattackX));
		L1 = ((petx-inicioattackX)*(petx-fimattackX))/((meioattackX-inicioattackX)*(meioattackX-fimattackX));
		L2 = ((petx-inicioattackX)*(petx-meioattackX))/((fimattackX-inicioattackX)*(fimattackX-meioattackX));

		pety = L0*inicioattackY + L1*meioattackY + L2*fimattackY;
		if(pety>500) pety = 500;
		//pety = 0.525*pow(petx,2) - 3.825*petx + 7.55;
	}
	if(petleft == false){
		pety = 500;
	}

	if(petx<700 && petleft==false){
		petleft = false;
		petx=petx+3;
	}
	if(petx>=700) petleft = true;
	if(petx>0 && petleft==true){
		petleft = true;
		petx=petx-3;
	}
	if(petx<=0) petleft = false;
	glutPostRedisplay();
}

bool CheckCollision(float rect1x, float rect1y, float rect1Width, float rect1Height, float rect2x, float rect2y, float rect2Width, float rect2Height){
	if (rect1x < rect2x + rect2Width &&
	   rect1x + rect1Width > rect2x &&
	   rect1y < rect2y + rect2Height &&
	   rect1y + rect1Height > rect2y) {
	    // collision detected!
		return true;
	}else return false;
}

void drawFish(){
	glColor3f(0.0f,0.0f,0.0f);
	glBegin(GL_POLYGON);
		glVertex2f(-47,0);
		glVertex2f(-22,-18);
		glVertex2f(7,-34);
		glVertex2f(46,-34);
		glVertex2f(87,-6);
		glVertex2f(87,6);
		glVertex2f(49,40);
		glVertex2f(10,40);
		glVertex2f(-21,19);
		glVertex2f(-47,0);
	glEnd();
	glPushMatrix();
		glTranslatef(40, 0, 0);
		glBegin(GL_TRIANGLES);
			glVertex2f(-50,0);
			glVertex2f(-100,30);
			glVertex2f(-100,-30);
		glEnd();
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.3f,0.5f,0.7f);
	glTranslatef(25, 4, 0);
	drawElipse(45,25);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(35, 0, 0);
		glBegin(GL_TRIANGLES);
			glVertex2f(-60,0);
			glVertex2f(-80,10);
			glVertex2f(-80,-10);
		glEnd();
	glPopMatrix();
}

void drawPetrel(){
	glPushMatrix();
	glRotatef(45,0,0,1);
	glColor3f(1.0f,0.8f,0.0f);
	glBegin(GL_POLYGON);
		glVertex2f(-72,72);
		glVertex2f(-99,83);
		glVertex2f(-74,82);
		glVertex2f(-72,72);
	glEnd();
	glColor3f(0.9f,0.9f,0.9f);
	glBegin(GL_POLYGON);
		glVertex2f(-74,82);
		glVertex2f(-72,72);
		glVertex2f(-38,10);
		glVertex2f(-28,38);
		glVertex2f(-32,63);
		glVertex2f(-48,83);
		glVertex2f(-74,82);
	glEnd();
	glColor3f(0.8f,0.8f,0.8f);
	glBegin(GL_POLYGON);
		glVertex2f(-38,10);
		glVertex2f(-26,-9);
		glVertex2f(-4,-24);
		glVertex2f(27,-42);
		glVertex2f(50,-51);
		glVertex2f(44,-34);
		glVertex2f(26,-14);
		glVertex2f(23,1);
		glVertex2f(-2,25);
		glVertex2f(-28,38);
		glVertex2f(-38,10);
	glEnd();
	glColor3f(0.2f,0.2f,0.2f);
	glBegin(GL_POLYGON);
		glVertex2f(-8,17);
		glVertex2f(8,40);
		glVertex2f(88,96);
		glVertex2f(73,63);
		glVertex2f(-8,17);
	glEnd();
	glColor3f(0.7f,0.7f,0.7f);
	glBegin(GL_POLYGON);
		glVertex2f(-8,17);
		glVertex2f(19,-3);
		glVertex2f(73,63);
		glVertex2f(-8,17);
	glEnd();
	glColor3f(0.2f,0.2f,0.2f);
	glBegin(GL_POLYGON);
		glVertex2f(27,-42);
		glVertex2f(50,-51);
		glVertex2f(44,-34);
		glVertex2f(70,-64);
		glVertex2f(70,-73);
		glVertex2f(27,-42);
	glEnd();
	glPopMatrix();
	glPushMatrix();
		glRotatef(45,0,0,1);
		glTranslatef(-50, 75, 0);
		glColor3f(1,1,1);
		drawElipse(4,4);
	glPopMatrix();
	glPushMatrix();
		glRotatef(45,0,0,1);
		glTranslatef(-50, 75, 0);
		glColor3f(0,0,0);
		drawElipse(2,2);
	glPopMatrix();
}

void drawPenguin() {
	glColor3f(0.0f,0.0f,0.0f);
	drawElipse(20,40);

	glPushMatrix();
		glTranslatef(5, -5, 0);
		glColor3f(1.0f,1.0f,1.0f);
		drawElipse(10,30);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(5, 50, 0);
		glColor3f(0.0f,0.0f,0.0f);
		drawElipse(15,15);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(10, 50, 0);
		glColor3f(1.0f,1.0f,1.0f);
		drawElipse(3,3);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(20, 40, 0);
		glColor3f(1.0f,0.8f,0.0f);
		glBegin(GL_TRIANGLES);
			glVertex2f(-10,0);
			glVertex2f(10,0);
			glVertex2f(0,10);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(10, -40, 0);
		glRotatef(120, 0, 0, 1);
		glColor3f(1.0f,0.7f,0.0f);
		glBegin(GL_TRIANGLES);
			glVertex2f(-10,0);
			glVertex2f(10,0);
			glVertex2f(0,10);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-5, -40, 0);
		glRotatef(120, 0, 0, 1);
		glColor3f(1.0f,0.7f,0.0f);
		glBegin(GL_TRIANGLES);
			glVertex2f(-10,0);
			glVertex2f(10,0);
			glVertex2f(0,10);
		glEnd();
	glPopMatrix();
	if(withFish == true){
		glPushMatrix();
		glTranslatef(10,35,0);
		glScalef(0.2,0.2,1);
		drawFish();
		glPopMatrix();
	}
}

void drawBabyPenguin(){
	glPushMatrix();
	glScaled(0.6,0.6,1);
	glColor3f(0.3f,0.3f,0.3f);
	drawElipse(20,40);
	glPushMatrix();
		glTranslatef(5, -5, 0);
		glColor3f(1.0f,1.0f,1.0f);
		drawElipse(10,30);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(5, 50, 0);
		glColor3f(0.3f,0.3f,0.3f);
		drawElipse(15,15);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(10, 50, 0);
		glColor3f(1.0f,1.0f,1.0f);
		drawElipse(3,3);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(20, 40, 0);
		glColor3f(1.0f,0.8f,0.0f);
		glBegin(GL_TRIANGLES);
			glVertex2f(-10,0);
			glVertex2f(10,0);
			glVertex2f(0,10);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(10, -40, 0);
		glRotatef(120, 0, 0, 1);
		glColor3f(1.0f,0.7f,0.0f);
		glBegin(GL_TRIANGLES);
			glVertex2f(-10,0);
			glVertex2f(10,0);
			glVertex2f(0,10);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-5, -40, 0);
		glRotatef(120, 0, 0, 1);
		glColor3f(1.0f,0.7f,0.0f);
		glBegin(GL_TRIANGLES);
			glVertex2f(-10,0);
			glVertex2f(10,0);
			glVertex2f(0,10);
		glEnd();
	glPopMatrix();
	glPopMatrix();
}

void drawText(void *font, char *string){
	{
		// Exibe caractere a caractere
		while(*string)
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15,*string++);
	}

}

void timer(int value){
	seconds += 1.0/60.0;
	cont -= 10;
	score++;
		//if (seconds == 1) exit(1);
	glutPostRedisplay();
	glutTimerFunc(1000,timer,0);
}

void contador(int cont){
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);
		glVertex2i(10,480);
		glVertex2i(cont,480);
		glVertex2i(cont,460);
		glVertex2i(10,460);
	glEnd();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	//Draw Snow
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
		glVertex2f(0,0);
		glVertex2f(300,0);
		glVertex2f(300,150);
		glVertex2f(0,150);
	glEnd();

	//Draw Water
	glColor3f(0.5f, 0.5f, 1.0f);
	glBegin(GL_POLYGON);
		glVertex2f(300,0);
		glVertex2f(700,0);
		glVertex2f(700,150);
		glVertex2f(300,150);
	glEnd();

	/*/Penguin Collision Box
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
		glVertex2f(pengx-30,pengy-30);
		glVertex2f(pengx+30,pengy-30);
		glVertex2f(pengx+30,pengy+30);
		glVertex2f(pengx-30,pengy+30);
		glVertex2f(pengx-30,pengy-30);
	glEnd();*/

	//Draw Penguin
	glPushMatrix();
	glTranslated(pengx,pengy,pengz);
	if(pengright==false) glRotatef(180,0,1,0);
	if(water==true){
		if(pengy>150) pengy = 140;
		glRotatef(-90,0,0,1);
	}
	drawPenguin();
	glPopMatrix();

	/*/Baby Penguin Collision Box
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
		glVertex2f(00,120);
		glVertex2f(40,120);
		glVertex2f(40,200);
		glVertex2f(00,200);
		glVertex2f(00,120);
	glEnd();*/

	//Draw Baby Penguin
	glPushMatrix();
	glTranslated(20,160,0);
	drawBabyPenguin();
	glPopMatrix();

	/*/Petrel Collision Box
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
		glVertex2f(petx-40,pety-20);
		glVertex2f(petx+40,pety-20);
		glVertex2f(petx+40,pety+30);
		glVertex2f(petx-40,pety+30);
		glVertex2f(petx-40,pety-20);
	glEnd();*/

	//Draw Petrel
	glPushMatrix();
	glTranslated(petx,pety,petz);
	glScaled(0.6,0.6,1);
	if(petleft==false){
		glRotatef(180,0,1,0);
	}
	drawPetrel();
	glPopMatrix();

	//Collision Penguin x Petrel
	if(CheckCollision(pengx,pengy,50,50,petx,pety,70,40) == true  && win == false) exit(1);

	//Collision Penguin x Fish
	for(int i=0; i<FishAmount; i++){
		if(CheckCollision(pengx,pengy,60,60,fishx[i],fishy[i],20,20) == true  && withFish == false){
			fishCollision[i]=true;
			withFish = true;
			if(fishCollision[i]==true){
				fishx[i] = randomXFishPosition();
				fishy[i] = randomYFishPosition();
			}
		}
	}
	//Collision Penguin x Baby Penguin
	if(CheckCollision(pengx,pengy,60,60,20,140,40,80) == true  && withFish == true){
		withFish = false;
		cont+=600;
	}

	if(score >= 300){
		glColor3f(1.0f, 1.0f, 0.0f);
		glBegin(GL_QUADS);
			glVertex2i(300,200);
			glVertex2i(400,200);
			glVertex2i(400,300);
			glVertex2i(300,300);
		glEnd();

		glColor3f(0.0f, 0.0f, 0.0f);
		glLineWidth(5);
		glBegin(GL_LINE_STRIP);
			glVertex2i(300,200);
			glVertex2i(400,200);
			glVertex2i(400,300);
			glVertex2i(300,300);
			glVertex2i(300,200);
		glEnd();

		glPushMatrix();
		glColor3f(0.0f, 0.0f, 0.0f);
		glRasterPos2f(315,250);
		drawText(GLUT_BITMAP_9_BY_15, "VOCE GANHOU!!!");
		glPopMatrix();
		win = true;
	}
	if(cont >=610) cont=610;
	if(cont <=10 && win == false) exit(1);

	/*/Fish Collision Box
	glColor3f(1.0f, 0.0f, 0.0f);
	for(int i=0; i<FishAmount; i++){
		glBegin(GL_QUADS);
			glVertex2f(fishx[i]-10,fishy[i]-10);
			glVertex2f(fishx[i]+10,fishy[i]-10);
			glVertex2f(fishx[i]+10,fishy[i]+10);
			glVertex2f(fishx[i]-10,fishy[i]+10);
			glVertex2f(fishx[i]-10,fishy[i]-10);
		glEnd();
	}*/

	//Draw Fish
	if(FishAmountAux == 4){
	for(int i=0; i<FishAmount; i++){
		glPushMatrix();
		glTranslated(fishx[i],fishy[i],fishz);
		glScaled(0.2,0.2,1);
		if(rightFish[i]==false) glRotatef(180,0,0,1);
		drawFish();
		glPopMatrix();
	}
	}

	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
		glVertex2i(10,480);
		glVertex2i(610,480);
		glVertex2i(610,460);
		glVertex2i(10,460);
	glEnd();
	contador(cont);
	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(5);
	glBegin(GL_LINE_STRIP);
		glVertex2i(10,480);
		glVertex2i(610,480);
		glVertex2i(610,460);
		glVertex2i(10,460);
		glVertex2i(10,480);
	glEnd();

	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glRasterPos2f(15,470);
	drawText(GLUT_BITMAP_9_BY_15, "VIDA DO FILHOTE");
	glPopMatrix();


	glutSwapBuffers();

}  // end display

void tick(int){
	srand((unsigned) time(0));
	glutTimerFunc(1000/30,tick,0);
	PetrelMovement();
	for(int i = 0; i < FishAmount; i++){
		FishMovement(i);
	}
	glutPostRedisplay();
}

void init() {
	glClearColor(0.5f, 0.8f, 1.0f,1);
		// The next three lines set up the coordinates system.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 700, 0, 500, 0, 100);
	glMatrixMode(GL_MODELVIEW);
	srand((unsigned) time(0));
}


void TeclasEspeciais (int tecla, int x, int y)
{
	switch (tecla)
	{
		case GLUT_KEY_LEFT:
			pengright = false;
			if(pengx>=00){
				pengx = pengx-05;
				if(pengx>=300){
					water = true;
				}
				else{
					water = false;
					pengy = 180;
				}
			}
			else pengx = 0;
			break;
		case GLUT_KEY_RIGHT:
			pengright = true;
			if(pengx<=700){
				pengx = pengx+5;
				if(pengx>=300){
					water = true;
				}
				else {
					water = false;
					pengy = 180;
				}
			}
			else pengx = 700;
			break;
		case GLUT_KEY_UP:
			if(water==true){
				if(pengy>150) pengy = 140;
				else pengy = pengy+5;
			}
			break;
		case GLUT_KEY_DOWN:
			if(water==true){
				if(pengy<0) pengy = 0;
				else pengy = pengy-5;
			}
			break;
		case GLUT_KEY_HOME:
			FishAmountAux = FishAmountAux - 1;
			break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(1280,720);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Trabalho 1 - Vitor Saraiva");

    init();

    glutDisplayFunc(display);

    glutTimerFunc(0,tick,0);
    glutTimerFunc(1000,timer,0);

    glutSpecialFunc(TeclasEspeciais);

    glutMainLoop();
    return 0;
}
