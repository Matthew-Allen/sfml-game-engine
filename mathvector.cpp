#include <math.h>
#include "mathvector.h"

/*


Class which defines a 2D vector and relevant operations which may be performed on one. Should make doing vector math easier.


*/

MathVector::~MathVector(){};

MathVector::MathVector(int value1, int value2)
{
	vectorArray[0] = value1;
	vectorArray[1] = value2;
}

int MathVector::getX()
{
	return vectorArray[0]; 
}
int MathVector::getY()
{
	return vectorArray[1];
}

void MathVector::addVectors(MathVector &inputVector)
{
	vectorArray[0] += inputVector.getX();
	vectorArray[1] += inputVector.getY();
}

void MathVector::subtractVectors(MathVector &inputVector)
{
	vectorArray[0] -= inputVector.getX();
	vectorArray[1] -= inputVector.getY();
}

void MathVector::addX(int x)
{
	vectorArray[0] += x;
}

void MathVector::addY(int y)
{
	vectorArray[1] += y;
}

void MathVector::subtractX(int x)
{
	vectorArray[0] -= x;
}

void MathVector::subtractY(int y)
{
	vectorArray[1] -= y;
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

/*
double MathVector::crossProduct(MathVector &vector)
{
	return (vectorArray[0] * vector.getY()) - (vectorArray[1] * vector.getX());
}

MathVector MathVector::crossProduct(double inScalar, int type)
{
	if(type == 0)
		{
			return MathVector(inScalar*vectorArray[1],-inScalar*vectorArray[0]);
		} else
		{
			return MathVector(-inScalar*vectorArray[1],inScalar*vectorArray[0]);
		}
}
*/
void MathVector::toUnit()
{
	//Converts THIS VECTOR to unit form. original magnitude will be lost, and this operation cannot be undone
	int magnitude = this->magnitude();
	vectorArray[0] /= magnitude;
	vectorArray[1] /= magnitude;
}

MathVector MathVector::perpendicular()
{
	return MathVector(-vectorArray[1],vectorArray[0]);
}