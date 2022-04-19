#include <cstdlib>
#include <iostream>
#include <GL/glut.h>

GLint WINDOW_WIDTH  = 500,
      WINDOW_HEIGHT = 500;

void init();
void draw();

float r,g,b,mousex,mousey;
bool check = true;

void mouse_test(GLint button, GLint action, GLint x, GLint y);


//=================================================================================================

int main(int argc, char* argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

  GLint screen_width  = glutGet(GLUT_SCREEN_WIDTH),
        screen_height = glutGet(GLUT_SCREEN_HEIGHT);

  glutInitWindowPosition((screen_width - WINDOW_WIDTH) / 2, (screen_height - WINDOW_WIDTH) / 2);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_WIDTH);
  glutCreateWindow("Tarefa 1 - Questao 2");

  init();

  glutDisplayFunc(draw);

  glutMouseFunc(mouse_test);

  glutMainLoop();


  return EXIT_SUCCESS;
}

void init()
{
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
}

void draw()
{
	glClearColor(1,1,1,0);
	glColor3f(r,g,b);
	glPointSize(50);

	if(check){
		glBegin(GL_POINTS);
			glVertex2i(mousex,mousey);
		glEnd();
	}

	glFlush();
}

void mouse_test(GLint button, GLint action, GLint x, GLint y)
{
  if(button==GLUT_LEFT_BUTTON && action==GLUT_DOWN){
	  check = true;
	  mousex = x;
	  mousey = 480-y;

	  r = 0;
	  g = 0;
	  b = 0;
  }
  else if(button==GLUT_RIGHT_BUTTON && action==GLUT_DOWN){
	  glClearColor(1,1,1,0);
	  glClear(GL_COLOR_BUFFER_BIT);
	  check = false;
  }
  glutPostRedisplay();
  draw();
}
