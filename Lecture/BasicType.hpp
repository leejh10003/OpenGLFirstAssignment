#pragma once
#include <vector>
using namespace std;
class Matrix;
class Vertex3D;
class Vector3D;
class Face;
class Tetrahderon;
class Matrix;
class MatrixSizeDifferent;





/*
 This Class is exception hadler for Matrix multiplication which has different dimension size in which desired to be equal
 */
class MatrixSizeDifferent : exception
{
protected:
	int former;
	int latter;
public:
	MatrixSizeDifferent(int former, int latter) : former(former), latter(latter) {};
	tuple<int, int> errorSize() const;
	void printError(string kind) const;
};





/*
 This class is Mathmatical matrix for matrix product
 */
class Matrix
{
protected:
	vector<vector<float>> matrix;
	void sizeCheck(const Matrix& latter) const;
public:
	Matrix() {};
	Matrix(vector<vector<float>> matrix) : matrix(matrix) {};
	Matrix operator*(const Matrix& latter) const;
	const vector<float>& operator[](int i) const;
	int size() const;
};





/*
	This class is vertex class which will corresponds to points in 3-dimension space
*/
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
	operator const Matrix() const;
	float distanceTo(const Vertex3D& to) const;
	Vertex3D getNearOneBetween(const Vertex3D& former, const Vertex3D& latter) const;
	float angleBetween(const Vertex3D& former, const Vertex3D& latter) const;
	string getAngleInformation(const Vertex3D& former, const Vertex3D& latter) const;
	float getX() const;
	float getY() const;
	float getZ() const;
	void setX(float input);
	void setY(float input);
	void setZ(float input);
};





/*
	This class is vector class that will corresponds displacement, Direction etc. in 3-dimension space
*/
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
	operator const Matrix() const;
	Vector3D normalize() const;
	float length() const;
	float getX() const;
	float getY() const;
	float getZ() const;
};





Vector3D crossProduct(const Vector3D &former, const Vector3D &latter);





/*
	This class stands for face determined by three point
*/
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




/*
	This class stands for tetrahedron mesh.
*/
class Tetrahedron
{
protected:
	Vertex3D vertices[4];
	Face faces[4];
	Vector3D edges[6];
	Matrix originToTail(const Vertex3D & tail) const;
	Matrix xzPlaneToAxis(const Vector3D & axis) const;
	Matrix zAxisToXZPlane(const Vector3D & axis) const;
	Matrix rotateInZAxis(const float radian) const;
	Matrix xzPlaneToZAxis(const Vector3D& axis) const;
	Matrix axisToXZPlane(const Vector3D& axis) const;
	Matrix tailToOrigin(const Vertex3D& tail) const;
	Matrix getRotationMatrix(const Vertex3D head, const Vertex3D tail, const float radian) const;
	Matrix getRotationOnAxisMatrix(unsigned char input, const float radian);
	void generateFaces();
public:
	void renderIt();
	Tetrahedron();
	Tetrahedron(Vertex3D(&inputVertices)[4], const Vertex3D& arbitraryOuterOne);
	void printAngles() const;
	void printRelationshipWith(const Vertex3D& with);
	void rotation(int input, const float radian);
	void rotationOnAxis(unsigned char input, const float radian);
};