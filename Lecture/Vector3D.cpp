#include "BasicType.hpp"

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
Vector3D::operator const Matrix() const
{
	vector<vector<float>> produced(4, vector<float>());
	produced[0][0] = x;
	produced[1][0] = y;
	produced[2][0] = z;
	produced[3][0] = 1;
	return produced;
}
Vector3D Vector3D::normalize() const
{
	float length = this->length();
	return Vector3D(x / length, y / length, z / length);
}
float Vector3D::length() const { return sqrt(pow(x, 2.0f) + pow(y, 2.0f) + pow(z, 2.0f)); }
float Vector3D::getX() const { return x; }
float Vector3D::getY() const { return y; }
float Vector3D::getZ() const { return z; }
