#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
class Vertex3D;
class Vector3D;
class Face;
class Tetrahderon;
class Vertex3D
{
protected:
	float x;
	float y;
	float z;
public:
	Vertex3D();
	Vertex3D(float xInput, float yInput, float zInput);
	Vertex3D(const Vertex3D &input);
	Vertex3D operator+(const Vector3D& latter) const;
	Vertex3D operator-(const Vector3D& latter) const;
	Vector3D operator-(const Vertex3D& latter) const;
	Vertex3D& operator+=(const Vector3D& latter);
	Vertex3D& operator-=(const Vector3D& latter);
	operator const Vector3D() const;
	float distanceTo(const Vertex3D& to) const;
	Vertex3D getNearOneBetween(const Vertex3D& former, const Vertex3D& latter) const;
	float angleBetween(const Vertex3D& former, const Vertex3D& latter) const;
	std::string getAngleInformation(const Vertex3D& former, const Vertex3D& latter) const;
	float getX() const;
	float getY() const;
	float getZ() const;
	void setX(float input);
	void setY(float input);
	void setZ(float input);
};
class Vector3D
{
protected:
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
	Vector3D operator*(const float &latter) const;
	Vector3D normalize() const;
	float length() const;
	float getX() const;
	float getY() const;
	float getZ() const;
};
Vector3D crossProduct(const Vector3D &former, const Vector3D &latter);
class Face
{
protected:
	Vertex3D vertices[3];
	Vertex3D centerOfGravity;
	Vertex3D endOfNormalVector;
	Vertex3D opposed;
	Vector3D normal;
	Vector3D normalizedNormal;
	Vector3D directionCorrectedNormal;
	float faceColor[4];
	float d;
public:
	Face(const Vertex3D(&input)[3], const float(&givenFaceColor)[4], const Vertex3D& opposed);
	Face();
	void renderIt();
	float relationsBetweenVertex(const Vertex3D& with);
	void printRelationshipBetweenEdge() const;
protected:
	void getCenterOfGravity();
	void getNormalVector();
	void getNormalVectorNormalized();
	Vector3D determineDirection();
	void getEndOfNormalVector();
	void getD();
};
class Tetrahedron
{
protected:
	Vertex3D vertices[4];
	Face faces[4];
	Vector3D edges[6];
public:
	void renderIt();
	Tetrahedron(Vertex3D(&inputVertices)[4], const Vertex3D& arbitraryOuterOne);
	void Tetrahedron::printAngles() const;
};