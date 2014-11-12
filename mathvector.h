#ifndef MATHVECTOR_H
#define MATHVECTOR_H
#include <math.h>
#include <SFML/Graphics.hpp>



class MathVector
{
private: 
	double vectorArray[2];
public:

	~MathVector();

	MathVector()
	{
		vectorArray[0] = 0;
		vectorArray[1] = 0;
	}

	MathVector(double value1, double value2);

	MathVector(sf::Vector2f);

	double getX();

	double getY();

	MathVector addVectors(MathVector inputVector);

	MathVector subtractVectors(MathVector inputVector);

	MathVector addX(double x);

	MathVector addY(double y);

	MathVector subtractX(double x);

	MathVector subtractY(double y);

	double magnitude();

	double angle(MathVector &vector);

	double dotProduct(MathVector &vector);

	double wedgeProduct(MathVector &vector);

	double crossProduct(MathVector vector);
/*	{
		if(type == 0)
		{
			return MathVector(inScalar*vectorArray[1],-inScalar*vectorArray[0]);
		} else
		{
			return MathVector(-inScalar*vectorArray[1],inScalar*vectorArray[0]);
		}
	}
*/
	MathVector toUnit();

	MathVector negate();

	MathVector multiply(double scalar);

	MathVector perpendicular();

	sf::Vector2f toSFMLVector();

};

#endif