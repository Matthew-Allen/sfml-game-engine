#include "collision.h"
#include "mathvector.h"
#include <limits>

#define TOLERANCE 0.00001

struct Edge_t
{
	double distance;
	MathVector normal;
	int index;
};

MathVector getFurthestPoint(MathVector direction, std::vector<MathVector> polygon)
	{
		double greatestDotProduct = -std::numeric_limits<double>::max();
		double currentDotProduct;
		MathVector currentVertex;
		MathVector bestVertex;
		for(int i = 0; i < polygon.size(); i++)
		{
			currentVertex = polygon[i];
			currentDotProduct = currentVertex.dotProduct(direction);
			if(currentDotProduct > greatestDotProduct)
			{
				greatestDotProduct = currentDotProduct;
				bestVertex = currentVertex;
			}
		}

		return bestVertex;

	}

MathVector getSupportVertex(std::vector<MathVector> a, std::vector<MathVector> b, MathVector direction)
{
	MathVector point0 = getFurthestPoint(direction,a);
	MathVector point1 = getFurthestPoint(direction.negate(),b);
	return point0.subtractVectors(point1);
}

MathVector tripleProduct(MathVector a, MathVector b, MathVector c)
{
	MathVector U = b.multiply(c.dotProduct(a));
	MathVector V = a.multiply(c.dotProduct(b));

	return U.subtractVectors(V);
}

bool containsOrigin(std::vector<MathVector> &simplex, MathVector &direction)
{
	MathVector a = simplex.back();
	MathVector b, c, ab, ac, abPerp, acPerp;
	MathVector ao = a.negate();

	if(simplex.size() == 3)
	{
		b = simplex[0];
		c = simplex[1];

		ab = b.subtractVectors(a);
		ac = c.subtractVectors(a);

		abPerp = tripleProduct(ac, ab, ab);
		acPerp = tripleProduct(ab, ac, ac);

		if(abPerp.dotProduct(ao) > 0)
		{
			simplex.erase(simplex.begin() + 1);
			direction = abPerp;
		} else if (acPerp.dotProduct(ao) > 0)
		{
			simplex.erase(simplex.begin());
			direction = acPerp;
		} else
		{
			return true;
		}
	} else
	{
		b = simplex[0];
		ab = b.subtractVectors(a);
		abPerp = tripleProduct(ab, ao, ab);

		if(abPerp.getX() == 0 || abPerp.getY() == 0)
		{
			direction = ab.perpendicular();
		} else
		{
			direction = abPerp;
		}
	}
	return false;
}

Edge_t findClosestEdge(std::vector<MathVector> simplex)
{
	Edge_t closest;
	closest.distance = std::numeric_limits<double>::max();
	closest.index = 0;
	double d;
	MathVector a, b, e, oa, n;

	for(int i = 0; i < simplex.size(); i++)
	{
		a = simplex[i];
		b = simplex[(i+1)%simplex.size()];

		e = b.subtractVectors(a);
		oa = a;

		n = tripleProduct(e, oa , e);

		n = n.toUnit();
//		std::cout << "normal triple product: " << n.getX() << ", " << n.getY() << std::endl;

		d = n.dotProduct(a);

		if(d < closest.distance)
		{
			closest.distance = d;
			closest.normal = n;
			closest.index = (i+1)%simplex.size();
		}

	}
	return closest;
}

minkowskiDifference_t buildMinkowskiDifference(std::vector<MathVector> a, std::vector<MathVector> b)
{
	MathVector direction = MathVector(1,1);
	std::vector<MathVector> simplex;
	simplex.push_back(getSupportVertex(a, b, direction));
	minkowskiDifference_t difference;

	direction = direction.negate();

	while(true)
	{
		simplex.push_back(getSupportVertex(a, b, direction));
		if(simplex.back().dotProduct(direction) <= 0)
		{
			difference.colliding = false;
			difference.collisionNormal = MathVector(0,0);
			difference.collisionDepth = 0;
			return difference;
		} else if(containsOrigin(simplex, direction) && simplex.size() == 3)
		{
			while(true)
			{
				//Perform EPA to get collision normal and penetration distance
				Edge_t e = findClosestEdge(simplex);

				MathVector p = getSupportVertex(a, b, direction);
				double d = p.dotProduct(e.normal);
//				std::cout << d - e.distance << std::endl;
//				std::cout << "Simplex size: " << simplex.size() << std::endl;
				if(d - e.distance < TOLERANCE)
				{
					difference.collisionNormal = e.normal;
					difference.collisionDepth = d;
					difference.colliding = true;
					return difference;
				} else
				{
//					std::cout << "Closest edge not found in this iteration, adding point to simplex and continuing." << std::endl;
					simplex.insert((simplex.begin()+e.index),p);
				}
			}
		}
	}
}