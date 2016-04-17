#include <cmath>
#include <iostream>
#include "BasicType.hpp"
Vertex3D::Vertex3D() : x(0.0f), y(0.0f), z(0.0f) {}
Vertex3D::Vertex3D(float xInput, float yInput, float zInput) :x(xInput), y(yInput), z(zInput) {}
Vertex3D::Vertex3D(const Vertex3D &input)
{
	x = input.getX();
	y = input.getY();
	z = input.getZ();
}

Vector3D Vertex3D::operator-(const Vertex3D& latter) const
{
	return Vector3D(x - latter.getX(),
		y - latter.getY(),
		z - latter.getZ());
}
Vertex3D Vertex3D::operator-(const Vector3D& latter) const
{
	return Vertex3D(x - latter.getX(),
		y - latter.getY(),
		z - latter.getZ());
}
Vertex3D Vertex3D::operator+(const Vector3D& latter) const
{

	return Vertex3D(x + latter.getX(),
		y + latter.getY(),
		z + latter.getZ());
}
Vertex3D& Vertex3D::operator-=(const Vector3D& latter)
{
	x -= latter.getX();
	y -= latter.getY();
	z -= latter.getZ();
	return (*this);
}
Vertex3D& Vertex3D::operator+=(const Vector3D& latter)
{
	this->x += latter.getX();
	this->y += latter.getY();
	this->z += latter.getZ();
	return (*this);
}
float Vertex3D::getX() const { return x; }
float Vertex3D::getY() const { return y; }
float Vertex3D::getZ() const { return z; }
void Vertex3D::setX(float input) { x = input; }
void Vertex3D::setY(float input) { y = input; }
void Vertex3D::setZ(float input) { z = input; }

Vector3D Vector3D::operator+(const Vector3D &latter) const
{
	return Vector3D(x + latter.getX(),
		y + latter.getY(),
		z + latter.getZ());
}
Vertex3D Vector3D::operator+(const Vertex3D &latter) const
{
	return Vertex3D(x + latter.getX(),
		y + latter.getY(),
		z + latter.getZ());
}
Vector3D Vector3D::operator-(const Vector3D &latter) const
{
	return Vector3D(x - latter.getX(),
		y - latter.getY(),
		z - latter.getZ());
}
float Vector3D::operator*(const Vector3D &latter) const { return x*latter.getX() + y*latter.getY() + z*latter.getZ(); }
Vector3D Vector3D::operator*(const float &latter) const { return Vector3D(x*latter, y*latter, z*latter); }
float Vector3D::getX() const { return x; }
float Vector3D::getY() const { return y; }
float Vector3D::getZ() const { return z; }
Vector3D crossProduct(const Vector3D &former, const Vector3D &latter)
{
	return Vector3D(former.getY()*latter.getZ() - former.getZ()*latter.getY(),
					former.getZ()*latter.getX() - former.getX()*latter.getZ(),
					former.getX()*latter.getY() - former.getY()*latter.getX());
}
Face::Face(const Vertex3D(&input)[3], const float(&givenFaceColor)[4])
{
	for (int i = 0; i < 3; i++) { vertices[i] = input[i]; }
	for (int i = 0; i < 4; i++) { faceColor[i] = givenFaceColor[i]; }
	getCenterOfGravity();
	getNormalVector();
	getNormalVectorNormalized();
	getEndOfNormalVector();
}
Face::Face()
{
	for (int i = 0; i < 3; i++) { vertices[i] = Vertex3D(0.0f, 0.0f, 0.0f); }
}
void Face::getCenterOfGravity()
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
void Face::getNormalVector()
{
	Vector3D former = vertices[1] - vertices[0];
	Vector3D latter = vertices[2] - vertices[0];
	normal = crossProduct(former, latter);
}
void Face::getNormalVectorNormalized()
{
	float x = normal.getX();
	float y = normal.getY();
	float z = normal.getZ();
	float size = sqrt(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0));
	normalizedNormal = Vector3D(x/size, y/size, z/size);
}
void Face::getEndOfNormalVector()
{
	endOfNormalVector = centerOfGravity + normalizedNormal * 2.0;
}
void Face::renderIt()
{
	glBegin(GL_TRIANGLES);
	glColor4f(faceColor[0], faceColor[1], faceColor[2], faceColor[3]);
	for (int i = 0; i < 3; i++)
		glVertex3f(vertices[i].getX(),vertices[i].getY(), vertices[i].getZ());
	glEnd();
	glLineWidth(5.0f);
	glBegin(GL_LINES);
	glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
	glVertex3f(centerOfGravity.getX(), centerOfGravity.getY(), centerOfGravity.getZ());
	glVertex3f(endOfNormalVector.getX(), endOfNormalVector.getY(), endOfNormalVector.getZ());
	glEnd();
}
Tetrahedron::Tetrahedron(Vertex3D(&inputVertices)[4])
{
	for (int i = 0; i < 4; i++) {
		vertices[i].setX(inputVertices[i].getX());
		vertices[i].setY(inputVertices[i].getY());
		vertices[i].setZ(inputVertices[i].getZ());
	}
	faces[0] = Face({ vertices[0], vertices[1], vertices[2] }, { 1.0f, 0.0f, 0.0f, 1.0f });
	faces[1] = Face({ vertices[0], vertices[2], vertices[3] }, { 0.0f, 1.0f, 0.0f, 1.0f });
	faces[2] = Face({ vertices[0], vertices[3], vertices[1] }, { 0.0f, 0.0f, 1.0f, 1.0f });
	faces[3] = Face({ vertices[1], vertices[3], vertices[2] }, { 1.0f, 1.0f, 0.0f, 1.0f });
}
void Tetrahedron::renderIt()
{
	for (int i = 0; i < 4; i++)
		faces[i].renderIt();
}