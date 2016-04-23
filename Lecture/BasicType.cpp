#include <cmath>
#include <iostream>
#include <string>
#include <tuple>
#include "BasicType.hpp"
using namespace std;
tuple<int, int> MatrixSizeDifferent::errorSize() const
{
	return tuple<int, int>(former, latter);
}
void MatrixSizeDifferent::printError(string kind) const
{
	cerr << "Wrong dimension size (n," << former << "), (" << latter << ", n) between"<< kind << endl;
}
 const vector<float>& Matrix::operator[](int i) const
{
	return matrix[i];
}
void Matrix::sizeCheck(const Matrix& latter) const
{
	try {
		if (this->matrix[0].size() != latter.size())
			throw MatrixSizeDifferent(matrix[0].size(),latter.size());
	}
	catch (MatrixSizeDifferent e)
	{
		e.printError("Matrix and Matrix");
		exit(-1);
	}
}
int Matrix::size() const
{
	return matrix.size();
}
Matrix Matrix::operator*(const Matrix& latter) const
{
	sizeCheck(latter);
	int coDim = latter.size();
	int formerDim = matrix.size();
	int latterDim = latter[0].size();
	vector<vector<float>> producted(formerDim, vector<float>(latterDim, 0.0f));
	for (int i = 0; i < formerDim; i++)
		for (int j = 0; j < latterDim; j++)
			for (int k = 0; k < coDim; k++)
				producted[i][j] += matrix[i][k] * latter[k][j];
	return producted;
}
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
	return sqrt(pow(distance.getX(),2.0) + pow(distance.getY(), 2.0) + pow(distance.getZ(), 2.0));
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
	return Vector3D( x/length, y/length, z/length);
}
float Vector3D::length() const{	return sqrt(pow(x,2.0f) + pow(y, 2.0f) + pow(z, 2.0f)); }
float Vector3D::getX() const { return x; }
float Vector3D::getY() const { return y; }
float Vector3D::getZ() const { return z; }
Vector3D crossProduct(const Vector3D &former, const Vector3D &latter)
{
	return Vector3D(former.getY()*latter.getZ() - former.getZ()*latter.getY(),
					former.getZ()*latter.getX() - former.getX()*latter.getZ(),
					former.getX()*latter.getY() - former.getY()*latter.getX());
}
Face::Face(const Vertex3D(&input)[3], const float(&givenFaceColor)[4], const Vertex3D& opposed): opposed(opposed)
{
	for (int i = 0; i < 3; i++) { vertices[i] = input[i]; }
	for (int i = 0; i < 4; i++) { faceColor[i] = givenFaceColor[i]; }
	getCenterOfGravity();
	getNormalVector();
	getNormalVectorNormalized();
	determineDirection();
	getD();
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
	normalizedNormal = normal.normalize();
}
Vector3D Face::determineDirection()
{
	directionCorrectedNormal = opposed.getNearOneBetween(centerOfGravity + normalizedNormal, centerOfGravity - normalizedNormal) - centerOfGravity;
	return directionCorrectedNormal;
}
void Face::getEndOfNormalVector()
{
	endOfNormalVector = centerOfGravity + directionCorrectedNormal * 2.0f;
}
void Face::getD()
{
	d = -((Vector3D)centerOfGravity * normalizedNormal);
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
void Face::printRelationshipBetweenEdge() const
{
	cout << "Angle0: " << vertices[0].getAngleInformation(vertices[1], vertices[2]) << endl;
	cout << "Angle1: " << vertices[1].getAngleInformation(vertices[0], vertices[2]) << endl;
	cout << "Angle2: " << vertices[2].getAngleInformation(vertices[0], vertices[1]) << endl;
}
float Face::relationsBetweenVertex(const Vertex3D& with)
{
	return directionCorrectedNormal * with + d;
}
Tetrahedron::Tetrahedron(Vertex3D(&inputVertices)[4], const Vertex3D& arbitraryOuterOne)
{
	for (int i = 0; i < 4; i++) {
		vertices[i].setX(inputVertices[i].getX());
		vertices[i].setY(inputVertices[i].getY());
		vertices[i].setZ(inputVertices[i].getZ());
	}
	generateFaces();
	cout << ((faces[0].relationsBetweenVertex(arbitraryOuterOne) > 0) ? "Positive" : "Negative") << endl;
	cout << ((faces[1].relationsBetweenVertex(arbitraryOuterOne) > 0) ? "Positive" : "Negative") << endl;
	cout << ((faces[2].relationsBetweenVertex(arbitraryOuterOne) > 0) ? "Positive" : "Negative") << endl;
	cout << ((faces[3].relationsBetweenVertex(arbitraryOuterOne) > 0) ? "Positive" : "Negative") << endl;
	printAngles();
}
Matrix Tetrahedron::originToTail(const Vertex3D & tail) const
{
	return Matrix({ { 1.0f, 0.0f, 0.0f, tail.getX() },
					{ 0.0f, 1.0f, 0.0f, tail.getY() },
					{ 0.0f, 0.0f, 1.0f, tail.getZ() },
					{ 0.0f, 0.0f, 0.0f, 1.0f } });
}
Matrix Tetrahedron::xzPlaneToAxis(const Vector3D & axis) const
{
	float b = axis.getY();
	float c = axis.getZ();
	float d = sqrt(pow(b, 2.0f) + pow(c, 2.0f));
	if (d == 0.0f)
		return Matrix({ { 1.0f, 0.0f, 0.0f, 0.0f },
						{ 0.0f, 1.0f, 0.0f, 0.0f },
						{ 0.0f, 0.0f, 1.0f, 0.0f },
						{ 0.0f, 0.0f, 0.0f, 1.0f } });
	else
		return Matrix({ { 1.0f, 0.0f, 0.0f, 0.0f },
						{ 0.0f, c/d ,  b/d, 0.0f },
						{ 0.0f,-b/d , c/d , 0.0f },
						{ 0.0f, 0.0f, 0.0f, 1.0f } });
}
Matrix Tetrahedron::zAxisToXZPlane(const Vector3D & axis) const
{
	float a = axis.getX();
	float b = axis.getY();
	float c = axis.getZ();
	float d = sqrt(pow(b, 2.0) + pow(c, 2.0));
	float l = sqrt(pow(a, 2.0) + pow(b, 2.0) + pow(c, 2.0));
	if (l == 0.0f)
		return Matrix({ { 1.0f, 0.0f, 0.0f, 0.0f },
						{ 0.0f, 1.0f, 0.0f, 0.0f },
						{ 0.0f, 0.0f, 1.0f, 0.0f },
						{ 0.0f, 0.0f, 0.0f, 1.0f } });
	else
		return Matrix({ { d/l , 0.0f,  a/l, 0.0f },
						{ 0.0f, 1.0f, 0.0f, 0.0f },
						{-a/l , 0.0f, d/l , 0.0f },
						{ 0.0f, 0.0f, 0.0f, 1.0f } });
}
Matrix Tetrahedron::rotateInZAxis(const float radian) const
{
	float csin = cos(radian);
	float sine = sin(radian);
	return Matrix({ {csin,-sine, 0.0f, 0.0f},
					{sine, csin, 0.0f, 0.0f},
					{0.0f, 0.0f, 1.0f, 0.0f},
					{0.0f, 0.0f, 0.0f, 1.0f} });
}
Matrix Tetrahedron::xzPlaneToZAxis(const Vector3D & axis) const
{
	float a = axis.getX();
	float b = axis.getY();
	float c = axis.getZ();
	float d = sqrt(pow(b, 2.0f) + pow(c, 2.0f));
	float l = sqrt(pow(a, 2.0f) + pow(b, 2.0f) + pow(c, 2.0f));
	if (l == 0.0f)
		return Matrix({ { 1.0f, 0.0f, 0.0f, 0.0f },
						{ 0.0f, 1.0f, 0.0f, 0.0f },
						{ 0.0f, 0.0f, 1.0f, 0.0f },
						{ 0.0f, 0.0f, 0.0f, 1.0f } });
	else
		return Matrix({ { d/l , 0.0f, -a/l, 0.0f },
						{ 0.0f, 1.0f, 0.0f, 0.0f },
						{ a/l , 0.0f, d/l , 0.0f },
						{ 0.0f, 0.0f, 0.0f, 1.0f } });
}
Matrix Tetrahedron::axisToXZPlane(const Vector3D & axis) const
{
	float b = axis.getY();
	float c = axis.getZ();
	float d = sqrt(pow(b, 2.0f) + pow(c, 2.0f));
	if (d == 0.0f)
		return Matrix({ { 1.0f, 0.0f, 0.0f, 0.0f },
						{ 0.0f, 1.0f, 0.0f, 0.0f },
						{ 0.0f, 0.0f, 1.0f, 0.0f },
						{ 0.0f, 0.0f, 0.0f, 1.0f } });
	else
		return Matrix({ { 1.0f, 0.0f, 0.0f, 0.0f },
						{ 0.0f, c/d , -b/d, 0.0f },
						{ 0.0f, b/d , c/d , 0.0f },
						{ 0.0f, 0.0f, 0.0f, 1.0f } });
}
Matrix Tetrahedron::tailToOrigin(const Vertex3D & tail) const
{
	return Matrix({ {1.0f, 0.0f, 0.0f, -tail.getX()},
					{0.0f, 1.0f, 0.0f, -tail.getY()},
					{0.0f, 0.0f, 1.0f, -tail.getZ()},
					{0.0f, 0.0f, 0.0f, 1.0f		   } });
}
Matrix Tetrahedron::getRotationMatrix(const Vertex3D & head, const Vertex3D & tail, const float radian) const
{
	Vector3D axis = head - tail;
	return tailToOrigin(tail) *
		   axisToXZPlane(axis) *
		   xzPlaneToZAxis(axis) *
		   rotateInZAxis(radian) *
		   zAxisToXZPlane(axis) *
		   xzPlaneToAxis(axis) *
		   originToTail(tail)
		;
}
Matrix Tetrahedron::getRotationOnAxisMatrix(unsigned char input, const float radian)
{
	float csin = cos(radian);
	float sine = sin(radian);
	switch (input)
	{
	case 'x':
		return Matrix({ { csin,-sine, 0.0f, 0.0f },
						{ sine, csin, 0.0f, 0.0f },
						{ 0.0f, 0.0f, 1.0f, 0.0f },
						{ 0.0f, 0.0f, 0.0f, 1.0f } });
	case 'y':
		return Matrix({ { 1.0f, 0.0f, 0.0f, 0.0f },
						{ 0.0f, csin,-sine, 0.0f },
						{ 0.0f, sine, csin, 0.0f },
						{ 0.0f, 0.0f, 0.0f, 1.0f } });
	case 'z':
		return Matrix({ { csin, 0.0f, sine, 0.0f },
						{ 0.0f, 1.0f, 0.0f, 0.0f },
						{-sine, 0.0f, csin, 0.0f },
						{ 0.0f, 0.0f, 0.0f, 1.0f } });
	}
}
void Tetrahedron::generateFaces()
{
	faces[0] = Face({ vertices[0], vertices[1], vertices[2] }, { 1.0f, 0.0f, 0.0f, 1.0f }, vertices[3]);
	faces[1] = Face({ vertices[0], vertices[2], vertices[3] }, { 0.0f, 1.0f, 0.0f, 1.0f }, vertices[1]);
	faces[2] = Face({ vertices[0], vertices[3], vertices[1] }, { 0.0f, 0.0f, 1.0f, 1.0f }, vertices[2]);
	faces[3] = Face({ vertices[1], vertices[3], vertices[2] }, { 1.0f, 1.0f, 0.0f, 1.0f }, vertices[0]);
}
void Tetrahedron::renderIt()
{
	for (int i = 0; i < 4; i++)
		faces[i].renderIt();
}
void Tetrahedron::printAngles() const
{
	for (int i = 0; i < 4; ++i) {
		cout << "Face" << i << ":" << endl;
		faces[i].printRelationshipBetweenEdge();
	}
}

void Tetrahedron::rotation(int input, const float radian)
{
	Vertex3D copiedTail;
	Vertex3D copiedHead;
	switch (input)
	{
	case 1:
		copiedTail = vertices[0];
		copiedTail = vertices[1];
		break;
	case 2:
		copiedTail = vertices[0];
		copiedTail = vertices[2];
		break;
	case 3:
		copiedTail = vertices[0];
		copiedTail = vertices[3];
		break;
	case 4:
		copiedTail = vertices[1];
		copiedTail = vertices[2];
		break;
	case 5:
		copiedTail = vertices[1];
		copiedTail = vertices[3];
		break;
	case 6:
		copiedTail = vertices[2];
		copiedTail = vertices[3];
		break;
	default:
		return;
	}
	for (int i = 0; i < 4; i++) {
		Matrix temp = getRotationMatrix(copiedHead, copiedTail, radian) * (Matrix)vertices[i];
		vertices[i].setX(temp[0][0]);
		vertices[i].setY(temp[1][0]);
		vertices[i].setZ(temp[2][0]);
	}
	generateFaces();
}

void Tetrahedron::rotationOnAxis(unsigned char input, const float radian)
{
	for (int i = 0; i < 4; i++) {
		Matrix temp = getRotationOnAxisMatrix(input, radian) * (Matrix)vertices[i];
		vertices[i].setX(temp[0][0]);
		vertices[i].setY(temp[1][0]);
		vertices[i].setZ(temp[2][0]);
	}
	generateFaces();
}
