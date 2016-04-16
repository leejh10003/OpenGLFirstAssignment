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
public:
	Face(const Vertex3D(&input)[3]);
	Face();
	void renderIt();
private:
	Vertex3D vertices[3];
	Vertex3D centerOfGravity;
	Vector3D normal;
	void getCenterOfGravity();
	void getNormalVector();
};
class Tetrahedron
{
public:
	void renderIt();
	Tetrahedron(Vertex3D(&inputVertices)[4])
	{
		for (int i = 0; i < 4; i++) {
			vertices[i].setX(inputVertices[i].getX());
			vertices[i].setY(inputVertices[i].getY());
			vertices[i].setZ(inputVertices[i].getZ());
		}
		faces[0] = Face({ vertices[0], vertices[1], vertices[2] });
		faces[1] = Face({ vertices[0], vertices[2], vertices[3] });
		faces[2] = Face({ vertices[0], vertices[3], vertices[1] });
		faces[3] = Face({ vertices[1], vertices[3], vertices[2] });
	}
private:
	Vertex3D vertices[4];
	Face faces[4];
};