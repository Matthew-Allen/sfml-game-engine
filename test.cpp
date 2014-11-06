#include <iostream>
#include "mathvector.h"

int main()
{
	MathVector testVector = MathVector(5,5);

	std::cout << testVector.getX() << std::endl;
}