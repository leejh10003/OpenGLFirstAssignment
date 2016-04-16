#include <Windows.h>
#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
using namespace std;
class Vertex3D{
public:
	Vertex3D() : x(0.0f), y(0.0f), z(0.0f) {}
	Vertex3D(float xInput, float yInput, float zInput):x(xInput), y(yInput), z(zInput) {}
	Vertex3D(const Vertex3D &input)
	{
		x = input.getX();
		y = input.getY();
		z = input.getZ();
	}
	Vector3D operator-(const Vertex3D& latter) const 
	{
		return Vector3D(x - latter.getX(),
						y - latter.getY(),
						z - latter.getZ());
	}
	Vertex3D operator-(const Vector3D& latter) const
	{
		return Vertex3D(x - latter.getX(),
						y - latter.getY(),
						z - latter.getZ());
	}
	Vertex3D operator+(const Vector3D& latter) const
	{

		return Vertex3D(x + latter.getX(),
						y + latter.getY(),
						z + latter.getZ());
	}
	Vertex3D& operator-=(const Vector3D& latter)
	{
		x -= latter.getX();
		y -= latter.getY();
		z -= latter.getZ();
		return (*this);
	}
	Vertex3D& operator+=(const Vector3D& latter)
	{
		x += latter.getX();
		y += latter.getY();
		z += latter.getZ();
		return (*this);
	}
	float getX() const { return x; }
	float getY() const { return y; }
	float getZ() const { return z; }
	void setX(float input) { x = input; }
	void setY(float input) { y = input; }
	void setZ(float input) { z = input; }
private:
	float x;
	float y;
	float z;
};
class Vector3D {
public:
	Vector3D():x(0.0f), y(0.0f), z(0.0f) {}
	Vector3D(float x, float y, float z) :x(x), y(y), z(z) {}
	Vector3D operator+(const Vector3D &latter) const
	{
		return Vector3D(x + latter.getX(),
						y + latter.getY(),
						z + latter.getZ());
	}
	Vertex3D operator+(const Vertex3D &latter) const
	{
		return Vertex3D(x + latter.getX(),
						y + latter.getY(),
						z + latter.getZ());
	}
	Vector3D operator-(const Vector3D &latter) const 
	{
		return Vector3D(x - latter.getX(),
						y - latter.getY(),
						z - latter.getZ());
	}
	float operator*(const Vector3D &latter) const { return x*latter.getX() + y*latter.getY() + z*latter.getZ(); }
	float getX() const { return x; }
	float getY() const { return y; }
	float getZ() const { return z; }
private:
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
};
Vector3D crossProduct(const Vector3D &former, const Vector3D &latter)
{
	return Vector3D(former.getY()*latter.getZ() - former.getZ()*latter.getY(),
					former.getZ()*latter.getX() - former.getX()*latter.getZ(),
					former.getX()*latter.getY() - former.getY()*latter.getX());
}

class Face {
	Face(const Vertex3D (&input)[3])
	{
		for (int i = 0; i < 3; i++) { vertices[i] = input[i]; }
		getCenterOfGravity();
		getNormalVector();
	}
private:
	Vertex3D vertices[3];
	Vertex3D centerOfGravity;
	Vector3D normal;
	void getCenterOfGravity()
	{
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
		for (int i = 0; i < 3; i++) {
			x += vertices[i].getX();
			y += vertices[i].getY();
			z += vertices[i].getZ();
		}
		centerOfGravity = Vertex3D(x / 3.0f, y / 3.0f, z / 3.0f);
	}
	void getNormalVector()
	{
		Vector3D former = vertices[1] - vertices[0];
		Vector3D latter = vertices[2] - vertices[0];
		normal = crossProduct(former, latter);
	}
};
class Tetrahedron
{
public:
	void renderIt()
	{
		glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
			glVertex3f(vertices[0].getX(), vertices[0].getY(), vertices[0].getZ());
			glVertex3f(vertices[1].getX(), vertices[1].getY(), vertices[1].getZ());
			glVertex3f(vertices[2].getX(), vertices[2].getY(), vertices[2].getZ());
		glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
			glVertex3f(vertices[1].getX(), vertices[1].getY(), vertices[1].getZ());
			glVertex3f(vertices[2].getX(), vertices[2].getY(), vertices[2].getZ());
			glVertex3f(vertices[3].getX(), vertices[3].getY(), vertices[3].getZ());
		glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
			glVertex3f(vertices[0].getX(), vertices[0].getY(), vertices[0].getZ());
			glVertex3f(vertices[2].getX(), vertices[2].getY(), vertices[2].getZ());
			glVertex3f(vertices[3].getX(), vertices[3].getY(), vertices[3].getZ());
		glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
			glVertex3f(vertices[0].getX(), vertices[0].getY(), vertices[0].getZ());
			glVertex3f(vertices[1].getX(), vertices[1].getY(), vertices[1].getZ());
			glVertex3f(vertices[3].getX(), vertices[3].getY(), vertices[3].getZ());
	}
	Tetrahedron(Vertex3D (&inputVertices)[4])
	{
		for (int i = 0; i < 4; i++) {
			vertices[i].setX(inputVertices[i].getX());
			vertices[i].setY(inputVertices[i].getY());
			vertices[i].setZ(inputVertices[i].getZ());
		}
	}
private:
	Vertex3D vertices[4];
	Face faces[4];
};

void Render(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();	
	gluLookAt(0.0f, 0.0f, 20.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	Vertex3D vertices[4] = { Vertex3D(5.0f,-5.0f,0.0f),
							 Vertex3D(0.0f,5.0f,0.0f),
							 Vertex3D(0.0f,-5.0f,-5.0f),
							 Vertex3D(-5.0f,-5.0f,0.0f) };
	Tetrahedron exampleTetrahdron(vertices);

	// 여기에 코드를 작성하십시오.
	glBegin(GL_TRIANGLES);
	exampleTetrahdron.renderIt();
	glEnd();

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
	HWND hWnd = ::FindWindow("ConsoleWindowClass" ,NULL );
	::MoveWindow(hWnd , 420 , 0 , 500 , 500, TRUE );

	//Window 제목은 학번과 학생 이름으로 작성하십시오.
	glutCreateWindow("2014210078_이준혁");

	glEnable(GL_DEPTH_TEST | GL_BLEND);
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

