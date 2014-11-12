#include "polygon.h"

Polygon::Polygon(int points[], int indices)
{
	for(int i = 0; i < indices; i++)
	{
		vertexVector.push_back(points[i]);
	}
}

int Polygon::numVertices()
{
	return vertexVector.size();
}