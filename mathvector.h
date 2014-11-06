#ifndef MATHVECTOR_H
#define MATHVECTOR_H
#include <math.h>



class MathVector
{
private: 
	int vectorArray[2];
public:

	~MathVector();

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

	double wedgeProduct(MathVector &vector);

	void toUnit();

	MathVector perpendicular();

};

#endif