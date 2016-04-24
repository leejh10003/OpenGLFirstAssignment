#include "BasicType.hpp"
#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
Tetrahedron::Tetrahedron(){}
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
		{ 0.0f, c / d ,  b / d, 0.0f },
		{ 0.0f,-b / d , c / d , 0.0f },
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
		return Matrix({ { d / l , 0.0f,  a / l, 0.0f },
		{ 0.0f, 1.0f, 0.0f, 0.0f },
		{ -a / l , 0.0f, d / l , 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f } });
}
Matrix Tetrahedron::rotateInZAxis(const float radian) const
{
	float csin = cos(radian);
	float sine = sin(radian);
	return Matrix({ { csin,-sine, 0.0f, 0.0f },
	{ sine, csin, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f, 1.0f } });
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
		return Matrix({ { d / l , 0.0f, -a / l, 0.0f },
		{ 0.0f, 1.0f, 0.0f, 0.0f },
		{ a / l , 0.0f, d / l , 0.0f },
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
		{ 0.0f, c / d , -b / d, 0.0f },
		{ 0.0f, b / d , c / d , 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f } });
}
Matrix Tetrahedron::tailToOrigin(const Vertex3D & tail) const
{
	return Matrix({ { 1.0f, 0.0f, 0.0f, -tail.getX() },
	{ 0.0f, 1.0f, 0.0f, -tail.getY() },
	{ 0.0f, 0.0f, 1.0f, -tail.getZ() },
	{ 0.0f, 0.0f, 0.0f, 1.0f } });
}
/*
	Generate the rotation matrix in arbitrary axis. Each function in return state get the matrix in each transforming steps.
*/
Matrix Tetrahedron::getRotationMatrix(const Vertex3D head, const Vertex3D tail, const float radian) const
{
	Vector3D axis = head - tail;
	return 
		originToTail(tail) *
		xzPlaneToAxis(axis) *
		zAxisToXZPlane(axis) *
		rotateInZAxis(radian) *
		xzPlaneToZAxis(axis) *
		axisToXZPlane(axis) *
		tailToOrigin(tail)
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
		{ -sine, 0.0f, csin, 0.0f },
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
		copiedHead = vertices[1];
		break;
	case 2:
		copiedTail = vertices[0];
		copiedHead = vertices[2];
		break;
	case 3:
		copiedTail = vertices[0];
		copiedHead = vertices[3];
		break;
	case 4:
		copiedTail = vertices[1];
		copiedHead = vertices[2];
		break;
	case 5:
		copiedTail = vertices[1];
		copiedHead = vertices[3];
		break;
	case 6:
		copiedTail = vertices[2];
		copiedHead = vertices[3];
		break;
	default:
		return;
	}
	Matrix toProduce = getRotationMatrix(copiedHead, copiedTail, radian);
	for (int i = 0; i < 4; i++) {
		Matrix temp = toProduce * (Matrix)vertices[i];
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
void Tetrahedron::printRelationshipWith(const Vertex3D& with) 
{
	for (int i = 0; i < 4; i++) {
		cout << "Face[" << i << "] and Vertex(" << with.getX() << ", " << with.getY() << ", " << with.getZ() << ") are ";
		if (faces[i].relationsBetweenVertex(with) > 0)
			cout << "Positive relationship." << endl;
		else if (faces[i].relationsBetweenVertex(with) < 0)
			cout << "Negative relationship." << endl;
		else
			cout << "Overlapping relationship." << endl;
	}
}