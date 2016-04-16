#pragma once
#include <Windows.h>
#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
class Vertex3D;
class Vector3D;
class Face;
class Tetrahderon;
class Vertex3D {
private:
	float x;
	float y;
	float z;
public:
	Vertex3D();
	Vertex3D(float xInput, float yInput, float zInput);
	Vertex3D(const Vertex3D &input);
	Vector3D operator-(const Vertex3D& latter) const;
	Vertex3D operator-(const Vector3D& latter) const;
	Vertex3D operator+(const Vector3D& latter) const;
	Vertex3D& operator-=(const Vector3D& latter);
	Vertex3D& operator+=(const Vector3D& latter);
	float getX() const;
	float getY() const;
	float getZ() const;
	void setX(float input);
	void setY(float input);
	void setZ(float input);
};
class Vector3D {
private:
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
public:
	Vector3D() :x(0.0f), y(0.0f), z(0.0f) {}
	Vector3D(float x, float y, float z) :x(x), y(y), z(z) {}
	Vector3D operator+(const Vector3D &latter) const;
	Vertex3D operator+(const Vertex3D &latter) const;
	Vector3D operator-(const Vector3D &latter) const;
	float operator*(const Vector3D &latter) const;
	float getX() const;
	float getY() const;
	float getZ() const;
};
Vector3D crossProduct(const Vector3D &former, const Vector3D &latter);
class Face {
	Face(const Vertex3D(&input)[3])
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
	Tetrahedron(Vertex3D(&inputVertices)[4])
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