#include <Windows.h>
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#define PI 3.14159265
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "BasicType.hpp"
using namespace std;

static Vertex3D vertices[4];
static Tetrahedron exampleTetrahdron;
void Render(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();	
	gluLookAt(0.0f, 0.0f, 20.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	glLineWidth(1.0f);
	glColor4f(1.0f, 1.0f,1.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(10.0f, 0.0f, 0.0f);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 10.0f, 0.0f);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 10.0f);
	glEnd();
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
		case 'q': break;
		case '1':
			exampleTetrahdron.rotation(1, PI / 180); break;
		case '2':
			exampleTetrahdron.rotation(2, PI / 180); break;
		case '3':
			exampleTetrahdron.rotation(3, PI / 180); break;
		case '4':
			exampleTetrahdron.rotation(4, PI / 180); break;
		case '5':
			exampleTetrahdron.rotation(5, PI / 180); break;
		case '6':
			exampleTetrahdron.rotation(6, PI / 180); break;
		case 'x':
			exampleTetrahdron.rotationOnAxis('x', PI / 180); break;
		case 'y':
			exampleTetrahdron.rotationOnAxis('y', PI / 180); break;
		case 'z':
			exampleTetrahdron.rotationOnAxis('z', PI / 180); break;
		case 'p':
			exampleTetrahdron.printRelationshipWith(Vertex3D(20.0f, 0.0f, 0.0f)); break;
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
//read object in text file format and generate tetrahedron mesh
void readInputText(void)
{
	ifstream verticesData("input.txt", ios::in);
	string inputString(istreambuf_iterator<char>(verticesData), (istreambuf_iterator<char>()));
	float arr[12];
	int i = 0;
	while (true)
	{
		size_t index = inputString.find(",");
		if (index == string::npos)
			break;
		float readed = atof(inputString.substr(0, index).c_str());
		arr[i] = readed;
		inputString = inputString.substr(index + 1, inputString.length());
		i++;
	}
	vertices[0] = Vertex3D(arr[0], arr[1], arr[2]);
	vertices[1] = Vertex3D(arr[3], arr[4], arr[5]);
	vertices[2] = Vertex3D(arr[6], arr[7], arr[8]);
	vertices[3] = Vertex3D(arr[9], arr[10], arr[11]);
	exampleTetrahdron = Tetrahedron(vertices, Vertex3D(10.0f, 10.0f, 10.0f));
}
int main(int argc, char ** argv)
{
	readInputText();
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

