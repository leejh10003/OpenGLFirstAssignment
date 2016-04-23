#include "BasicType.hpp"
#include <string>
#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
float Face::relationsBetweenVertex(const Vertex3D& with)
{
	return directionCorrectedNormal * with + d;
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
		glVertex3f(vertices[i].getX(), vertices[i].getY(), vertices[i].getZ());
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