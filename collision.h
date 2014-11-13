#include "mathvector.h"
#include "mathvector.h"
#include <limits>

struct minkowskiDifference_t
{
	bool colliding;
	MathVector collisionNormal;
	double collisionDepth;
};

minkowskiDifference_t buildMinkowskiDifference(std::vector<MathVector> a, std::vector<MathVector> b);