#ifndef POLYGON_H
#define POLYGON_H
#include <math.h>
#include <vector>
#include "mathvector.h"


class Polygon
{
private:
	std::vector<int> vertexVector;
	float rotation;
	float position;

public:

	~Polygon();

	Polygon(int points[], int indices);

	int numVertices();

};


#endif