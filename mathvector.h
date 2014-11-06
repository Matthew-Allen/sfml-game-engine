#ifndef MATHVECTOR_H
#define MATHVECTOR_H
#include <math.h>



class MathVector
{
private: 
	int vectorArray[2];
public:

	~MathVector();

	MathVector()
	{
		vectorArray[0] = 0;
		vectorArray[1] = 0;
	}

	MathVector(int value1, int value2);

	int getX();

	int getY();

	void addVectors(MathVector &inputVector);

	void subtractVectors(MathVector &inputVector);

	void addX(int x);

	void addY(int y);

	void subtractX(int x);

	void subtractY(int y);

	double magnitude();

	double angle(MathVector &vector);

	double dotProduct(MathVector &vector);

	double crossProduct(MathVector &vector)
	{
		return (vectorArray[0] * vector.getY()) - (vectorArray[1] * vector.getX());
	}

	MathVector crossProduct(double inScalar, int type=0)
	{
		if(type == 0)
		{
			return MathVector(inScalar*vectorArray[1],-inScalar*vectorArray[0]);
		} else
		{
			return MathVector(-inScalar*vectorArray[1],inScalar*vectorArray[0]);
		}
	}

	void toUnit();

	MathVector perpendicular();

};

#endif