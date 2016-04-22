#include <Windows.h>
#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "BasicType.hpp"
using namespace std;

void Render(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();	
	gluLookAt(0.0f, 0.0f, 20.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	Vertex3D vertices[4] = { Vertex3D(5.0f,-5.0f,0.0f),
							 Vertex3D(0.0f,5.0f,0.0f),
							 Vertex3D(0.0f,0.0f,5.0f),
							 Vertex3D(-5.0f,-5.0f,0.0f)};
	Tetrahedron exampleTetrahdron(vertices, Vertex3D(10.0f, 10.0f, 10.0f));
	
	exampleTetrahdron.renderIt();

	glutSwapBuffers();
}

void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, w/h, 1.0f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void Mouse(int mouse_event, int state, int x, int y)
{
	switch(mouse_event)
	{
		case GLUT_LEFT_BUTTON:
		
			break;
		case GLUT_MIDDLE_BUTTON:
		
			break;
		case GLUT_RIGHT_BUTTON:
		
			break;
		default:
			break;		
	}
	glutPostRedisplay();
}


void Motion(int x, int y)
{
	
	glutPostRedisplay();
}


void Keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'q':
		case VK_ESCAPE:
			exit(0);
		break;
	}
	glutPostRedisplay();
}

void SpecialKey(int key, int x, int y)
{
	switch(key) 
	{
		case GLUT_KEY_F1:
			printf("Hellow World \n");
			break;
	}
	glutPostRedisplay();
}

void Idle(void)
{
	
	glutPostRedisplay();
}
int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	
	glutInitWindowSize(400,400);
	glutInitWindowPosition(0, 0);

	//Console Window 위치 변경
	HWND hWnd = ::FindWindow((LPCWSTR)"ConsoleWindowClass" ,NULL );
	::MoveWindow(hWnd , 420 , 0 , 500 , 500, TRUE );

	//Window 제목은 학번과 학생 이름으로 작성하십시오.
	glutCreateWindow("2014210078_이준혁");

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

	glDepthFunc(GL_LEQUAL);
	glutDisplayFunc(Render);
	glutReshapeFunc(Reshape);

	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKey);
	glutIdleFunc(Idle);
	glutMainLoop();

	return 0;
}

