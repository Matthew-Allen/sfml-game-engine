#include <math.h>
#include "mathvector.h"

/*


Class which defines a 2D vector and relevant operations which may be performed on one. Should make doing vector math easier.


*/

MathVector::~MathVector(){};

MathVector::MathVector(double value1, double value2)
{
	vectorArray[0] = value1;
	vectorArray[1] = value2;
}


//Vector can be constructed using SFML Vector2f objects, can also be transformed back into Vector2f objects
MathVector::MathVector(sf::Vector2f sfmlVector)
{
	vectorArray[0] = sfmlVector.x;
	vectorArray[1] = sfmlVector.y;
}

double MathVector::getX()
{
	return vectorArray[0]; 
}
double MathVector::getY()
{
	return vectorArray[1];
}

MathVector MathVector::addVectors(MathVector inputVector)
{
	return MathVector(vectorArray[0] + inputVector.getX(),vectorArray[1] + inputVector.getY());
}

MathVector MathVector::subtractVectors(MathVector inputVector)
{
	return MathVector(vectorArray[0] - inputVector.getX(),vectorArray[1] - inputVector.getY());
}

MathVector MathVector::addX(double x)
{
	return MathVector(vectorArray[0] + x,vectorArray[1]);
}

MathVector MathVector::addY(double y)
{
	return MathVector(vectorArray[0], vectorArray[1] + y);
}

MathVector MathVector::subtractX(double x)
{
	return MathVector(vectorArray[0] - x, vectorArray[1]);
}

MathVector MathVector::subtractY(double y)
{
	return MathVector(vectorArray[0], vectorArray[1] - y);
}

double MathVector::magnitude()
{
	double squaredX = pow(vectorArray[0], 2);
	double squaredY = pow(vectorArray[1], 2);
	return(sqrt(squaredX + squaredY));
}

double MathVector::angle(MathVector &vector)
{
	return acos(this->dotProduct(vector));
}

double MathVector::dotProduct(MathVector &vector)
{
	return (vectorArray[0] * vector.getX()) + (vectorArray[1] * vector.getY());
}


double MathVector::wedgeProduct(MathVector &vector)
{
	return (vectorArray[0] * vector.getY()) - (vectorArray[1] * vector.getX());
}

double MathVector::crossProduct(MathVector vector)
{
	return (vectorArray[0]*vector.getY()) - (vectorArray[0]*vector.getX());
}

MathVector MathVector::toUnit()
{
	double magnitude = this->magnitude();
	return MathVector(vectorArray[0] / magnitude, vectorArray[1] / magnitude);
}

MathVector MathVector::perpendicular()
{
	return MathVector(-vectorArray[1],vectorArray[0]);
}

sf::Vector2f MathVector::toSFMLVector()
{
	return sf::Vector2f(vectorArray[0], vectorArray[1]);
}

MathVector MathVector::negate()
{
	return MathVector(-vectorArray[0], -vectorArray[1]);
}

MathVector MathVector::multiply(double scalar)
{
	return MathVector(vectorArray[0] * scalar, vectorArray[1] * scalar);
}