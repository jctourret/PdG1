#include "Plane.h"


Plane::Plane() {

}

Plane::~Plane() {

}

Plane Plane::GetReversedPlane()
{
	Plane a;
	a.normal = -normal;
	a.distance = distance;
	return a;
}

