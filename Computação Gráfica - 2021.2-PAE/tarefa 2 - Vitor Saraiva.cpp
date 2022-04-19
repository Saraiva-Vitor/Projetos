#include <GL/glut.h>
#include <math.h>

void init();
void display();

GLint wsize_x = 800;
GLint wsize_y = 800;

void init() {
  // define a cor de background da janela
  glClearColor(0.2, 0.8, 1.0, 1.0);

  // define o sistema de visualização - tipo de projeção
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-5, 5, -5, 5, -5, 5);

}

void catavento(float x, float y)
{
	glColor3f(0.4, 0.4, 0.4);
	glBegin(GL_POLYGON);
		glVertex2f(x, y);
		glVertex2f(x-0.5, y-0.2);
		glVertex2f(x-1, y-1);
		glVertex2f(x, y);
		glVertex2f(x+0.2, y-0.5);
		glVertex2f(x+1, y-1);
		glVertex2f(x, y);
		glVertex2f(x+0.2, y+0.5);
		glVertex2f(x, y+1.5);
		glVertex2f(x, y);
	glEnd();
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
		glVertex2f(x-0.05, y-3);
	  	glVertex2f(x+0.05, y-3);
	  	glVertex2f(x+0.05, y);
	  	glVertex2f(x-0.05, y);
	  	glVertex2f(x-0.05, y-3);
	glEnd();
	glColor3f(0.8, 0.8, 0.8);
	float i = 0.0f;
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y); // Center
		   	for(i = 0.0f; i <= 360; i++)
		   		glVertex2f(0.07*cos(M_PI * i / 180.0) + x, 0.07*sin(M_PI * i / 180.0) + y);
	glEnd();
}

void sol(float x, float y)
{
	float i = 0.0f;
	float r = 0.7;
	glColor3f(1.0, 1.0, 0.0);
	        glBegin(GL_TRIANGLE_FAN);
	        	glVertex2f(x, y); // Center
	        	for(i = 0.0f; i <= 360; i++)
	                glVertex2f(r*cos(M_PI * i / 180.0) + x, r*sin(M_PI * i / 180.0) + y);
	        glEnd();
	        glBegin(GL_LINES);
	        	glVertex3f(x+r,y,0);
	        	glVertex3f(x+r+0.5,y,0);
	        glEnd();
	        glBegin(GL_LINES);
	        	glVertex3f(x-r,y,0);
	        	glVertex3f(x-r-0.5,y,0);
	        glEnd();
	        glBegin(GL_LINES);
	        	glVertex3f(x,y+r,0);
	        	glVertex3f(x,y+r+0.5,0);
	        glEnd();
	        glBegin(GL_LINES);
	        	glVertex3f(x,y-r,0);
	        	glVertex3f(x,y-r-0.5,0);
	       	glEnd();
	        glBegin(GL_LINES);
	        	glVertex3f(x,y,0);
	        	glVertex3f(x+r+0.25,y+r+0.25,0);
	        glEnd();
	        glBegin(GL_LINES);
	        	glVertex3f(x,y,0);
	        	glVertex3f(x+r+0.25,y-r-0.25,0);
	        glEnd();
	        glBegin(GL_LINES);
	        	glVertex3f(x,y,0);
	        	glVertex3f(x-r-0.25,y-r-0.25,0);
	        glEnd();
	        glBegin(GL_LINES);
	        	glVertex3f(x,y,0);
	        	glVertex3f(x-r-0.25,y+r+0.25,0);
	        glEnd();
}

void carro(float x, float y)
{
	float i = 0.0f;
	glColor3f(0.0, 0.0, 0.0);
	float drodas=0.5;
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x-drodas, y); // Center
	   	for(i = 0.0f; i <= 360; i++)
	   		glVertex2f(0.3*cos(M_PI * i / 180.0) + x-drodas, 0.3*sin(M_PI * i / 180.0) + y);
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
			glVertex2f(x+drodas, y); // Center
		   	for(i = 0.0f; i <= 360; i++)
		   		glVertex2f(0.3*cos(M_PI * i / 180.0) + x+drodas, 0.3*sin(M_PI * i / 180.0) + y);
	glEnd();
	glColor3f(0.85, 0.85, 0.85);
	glBegin(GL_TRIANGLE_FAN);
			glVertex2f(x+drodas, y); // Center
		   	for(i = 0.0f; i <= 360; i++)
		   		glVertex2f(0.2*cos(M_PI * i / 180.0) + x + drodas, 0.2*sin(M_PI * i / 180.0) + y);
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
			glVertex2f(x-drodas, y); // Center
		   	for(i = 0.0f; i <= 360; i++)
		   		glVertex2f(0.2*cos(M_PI * i / 180.0) + x-drodas, 0.2*sin(M_PI * i / 180.0) + y);
	glEnd();
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_TRIANGLE_FAN);
			glVertex2f(x+drodas, y); // Center
		   	for(i = 0.0f; i <= 360; i++)
		   		glVertex2f(0.05*cos(M_PI * i / 180.0) + x+drodas, 0.05*sin(M_PI * i / 180.0) + y);
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
			glVertex2f(x-drodas, y); // Center
		   	for(i = 0.0f; i <= 360; i++)
		   		glVertex2f(0.05*cos(M_PI * i / 180.0) + x-drodas, 0.05*sin(M_PI * i / 180.0) + y);
	glEnd();
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
		glVertex2f(x, y+0.1);
		glVertex2f(x+1, y+0.1);
		glVertex2f(x+1, y+0.7);
		glVertex2f(x-0.6, y+0.7);
		glVertex2f(x-0.6, y+1.2);
		glVertex2f(x+0.4, y+1.2);
		glVertex2f(x+0.4, y+0.7);
		glVertex2f(x-1, y+0.7);
		glVertex2f(x-1, y+0.1);
		glVertex2f(x, y+0.1);
	glEnd();
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  //Grama
  glColor3f(0.2, 0.7, 0.3);
  glBegin(GL_QUADS);
  	  glVertex2f(-5, -5);
  	  glVertex2f(-5, -4);
  	  glVertex2f(5, -4);
  	  glVertex2f(5, -5);
  glEnd();
  //Asfalto
  glColor3f(0.35, 0.35, 0.35);
  glBegin(GL_QUADS);
  	  glVertex2f(-5, -4);
  	  glVertex2f(-5, -2);
  	  glVertex2f(5, -2);
  	  glVertex2f(5, -4);
  glEnd();
  //Faixa
  glColor3f(1.0, 1.0, 1.0);
  glBegin(GL_QUADS);
  	  glVertex2f(-4.5, -2.9);
  	  glVertex2f(-3.5, -2.9);
  	  glVertex2f(-3.5, -3.0);
  	  glVertex2f(-4.5, -3.0);
  	  glVertex2f(-3.0, -2.9);
  	  glVertex2f(-2.0, -2.9);
  	  glVertex2f(-2.0, -3.0);
  	  glVertex2f(-3.0, -3.0);
  	  glVertex2f(-1.5, -2.9);
  	  glVertex2f(-0.5, -2.9);
  	  glVertex2f(-0.5, -3.0);
  	  glVertex2f(-1.5, -3.0);
  	  glVertex2f(1.5, -2.9);
  	  glVertex2f(0.5, -2.9);
  	  glVertex2f(0.5, -3.0);
  	  glVertex2f(1.5, -3.0);
  	  glVertex2f(4.5, -2.9);
  	  glVertex2f(3.5, -2.9);
  	  glVertex2f(3.5, -3.0);
  	  glVertex2f(4.5, -3.0);
  	  glVertex2f(3.0, -2.9);
  	  glVertex2f(2.0, -2.9);
  	  glVertex2f(2.0, -3.0);
  	  glVertex2f(3.0, -3.0);
  glEnd();
  //Montanhas
  glColor3f(0.2, 0.5, 0.3);
  glBegin(GL_POLYGON);
  	  glVertex2f(-5, -2);
  	  glVertex2f(-5, -1);
  	  glVertex2f(-3, 1);
  	  glVertex2f(-2, 0.5);
  	  glVertex2f(0, 2);
  	  glVertex2f(2, -1);
  	  glVertex2f(4, 1);
   	  glVertex2f(5, -1);
   	  glVertex2f(5, -2);
   	  glVertex2f(-5, -2);
  glEnd();
  catavento(-4,2.5);
  catavento(-2,3);
  catavento(0,1.5);
  carro(0,-3.5);
  sol(3.5,3.5);

  glutSwapBuffers();
}

int main(int argc, char** argv) {

  //Inicializa a biblioteca GLUT e negocia uma seção com o gerenciador de janelas.
  //É possível passar argumentos para a função glutInit provenientes da linha de execução, tais como informações sobre a geometria da tela
  glutInit(&argc, argv);

  //Informa à biblioteca GLUT o modo do display a ser utilizado quando a janela gráfica for criada.
  // O flag GLUT_SINGLE força o uso de uma janela com buffer simples, significando que todos os desenhos serão feitos diretamente nesta janela.
  // O flag GLUT_RGB determina que o modelo de cor utilizado será o modelo RGB.
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

  //Define o tamanho inicial da janela, 256x256 pixels, e a posição inicial do seu canto superior esquerdo na tela, (x, y)=(100, 100).
  glutInitWindowSize(wsize_x, wsize_y);
  glutInitWindowPosition(200, 200);

  // Cria uma janela e define seu título
  glutCreateWindow("Tarefa 2");

  //Nesta função é definido o estado inicial do OpenGL. Ajustes podem ser feitos para o usuário nessa função.
  init();

  // Define display() como a função de desenho (display callback) para a janela corrente.
  // Quando GLUT determina que esta janela deve ser redesenhada, a função de desenho é chamada.
  glutDisplayFunc(display);

  //Inicia o loop de processamento de desenhos com GLUT.
  // Esta rotina deve ser chamada pelo menos uma vez em um programa que utilize a biblioteca GLUT.
  glutMainLoop();

  return 0;

}
