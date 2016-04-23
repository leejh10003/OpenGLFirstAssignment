#include "BasicType.hpp"

const vector<float>& Matrix::operator[](int i) const
{
	return matrix[i];
}
void Matrix::sizeCheck(const Matrix& latter) const
{
	try {
		if (this->matrix[0].size() != latter.size())
			throw MatrixSizeDifferent(matrix[0].size(), latter.size());
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