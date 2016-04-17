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
float Vector3D::getX() const { return x; }
float Vector3D::getY() const { return y; }
float Vector3D::getZ() const { return z; }
Vector3D crossProduct(const Vector3D &former, const Vector3D &latter)
{
	return Vector3D(former.getY()*latter.getZ() - former.getZ()*latter.getY(),
					former.getZ()*latter.getX() - former.getX()*latter.getZ(),
					former.getX()*latter.getY() - former.getY()*latter.getX());
}
Face::Face(const Vertex3D(&input)[3])
{
	for (int i = 0; i < 3; i++) { vertices[i] = input[i]; }
	getCenterOfGravity();
	getNormalVector();
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
void Face::renderIt()
{
	for (int i = 0; i < 3; i++)
		glVertex3f(vertices[i].getX(),vertices[i].getY(), vertices[i].getZ());
}
void Tetrahedron::renderIt()
{
	glBegin(GL_TRIANGLES);
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	faces[0].renderIt();
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
	faces[1].renderIt();
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
	faces[2].renderIt();
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
	faces[3].renderIt();
	glEnd();
}
