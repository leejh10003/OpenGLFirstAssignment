#include <cmath>
#include <iostream>
#include <string>
#include <tuple>
#include "BasicType.hpp"
using namespace std;
Vector3D crossProduct(const Vector3D &former, const Vector3D &latter)
{
	return Vector3D(former.getY()*latter.getZ() - former.getZ()*latter.getY(),
					former.getZ()*latter.getX() - former.getX()*latter.getZ(),
					former.getX()*latter.getY() - former.getY()*latter.getX());
}