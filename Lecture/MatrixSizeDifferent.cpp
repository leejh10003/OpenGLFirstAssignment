#include "BasicType.hpp"
#include <iostream>
#include <tuple>
#include <string>
tuple<int, int> MatrixSizeDifferent::errorSize() const
{
	return tuple<int, int>(former, latter);
}
void MatrixSizeDifferent::printError(string kind) const
{
	cerr << "Wrong dimension size (n," << former << "), (" << latter << ", n) between" << kind << endl;
}