#include "BasicType.hpp"
Vertex3D::Vertex3D() : x(0.0f), y(0.0f), z(0.0f) {}
Vertex3D::Vertex3D(float xInput, float yInput, float zInput) : x(xInput), y(yInput), z(zInput) {}
Vertex3D::Vertex3D(const Vertex3D &input)
{
	x = input.getX();
	y = input.getY();
	z = input.getZ();
}

Vertex3D Vertex3D::operator-(const Vector3D& latter) const
{
	return Vertex3D(x - latter.getX(),
		y - latter.getY(),
		z - latter.getZ());
}
Vector3D Vertex3D::operator-(const Vertex3D& latter) const
{
	return Vector3D(x - latter.getX(),
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
Vertex3D::operator const Vector3D() const
{
	return (*this) - Vertex3D(0.0f, 0.0f, 0.0f);
}
Vertex3D::operator const Matrix() const
{
	vector<vector<float>> produced(4, vector<float>(1));
	produced[0][0] = x;
	produced[1][0] = y;
	produced[2][0] = z;
	produced[3][0] = 1;
	return produced;
}
float Vertex3D::distanceTo(const Vertex3D& to) const
{
	Vector3D distance = (*this) - to;
	return sqrt(pow(distance.getX(), 2.0) + pow(distance.getY(), 2.0) + pow(distance.getZ(), 2.0));
}
Vertex3D Vertex3D::getNearOneBetween(const Vertex3D& former, const Vertex3D& latter) const
{
	return this->distanceTo(former) > this->distanceTo(latter) ? former : latter;
}
float Vertex3D::angleBetween(const Vertex3D& former, const Vertex3D& latter) const
{
	return (former - (*this)) * (latter - (*this));
}
string Vertex3D::getAngleInformation(const Vertex3D& former, const Vertex3D& latter) const
{
	if (angleBetween(former, latter) > 0)
		return "Acute";
	else if (angleBetween(former, latter) < 0)
		return "Obtuse";
	else
		return "Rectangle";
}
float Vertex3D::getX() const { return x; }
float Vertex3D::getY() const { return y; }
float Vertex3D::getZ() const { return z; }
void Vertex3D::setX(float input) { x = input; }
void Vertex3D::setY(float input) { y = input; }
void Vertex3D::setZ(float input) { z = input; }