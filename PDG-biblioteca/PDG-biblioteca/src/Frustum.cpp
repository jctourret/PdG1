#include "Frustum.h"

Frustum::Frustum(Camera* cam, float aspect, float fovY, float zNear, float zFar)
{
	const float halfVSide = zFar * tanf(fovY * .5f);
	const float halfHSide = halfVSide * aspect;
	const glm::vec3 frontMultFar = zFar * cam->getFront();
	system("CLS");
	std::cout << "Near Face ";
	nearFace = Plane( cam->getPosition() + zNear * cam->getFront(), cam->getFront());
	std::cout << "Far Face ";
	farFace = Plane(cam->getPosition() + frontMultFar, -cam->getFront());
	std::cout << "Right Face ";
	rightFace = Plane( cam->getPosition(),
				glm::cross(frontMultFar - cam->getSide() *halfHSide, cam->getUp()));
	std::cout << "Left Face ";
	leftFace = Plane(cam->getPosition(),
				glm::cross(cam->getUp(), frontMultFar + cam->getSide() * halfHSide));
	std::cout << "Top Face ";
	topFace = Plane(cam->getPosition(),
				glm::cross(cam->getSide(),frontMultFar - cam->getUp() * halfVSide));
	std::cout << "Bottom Face ";
	bottomFace = Plane(cam->getPosition(),
				glm::cross(frontMultFar + cam->getUp() * halfVSide, cam->getSide()));
}


bool Frustum::pointInFrustum(glm::vec3 point)
{
	std::cout << "Near Face ";
	bool nearF = nearFace.getSignedDistanceToPlane(point)>0;
	std::cout << "Far Face ";
	bool farF = farFace.getSignedDistanceToPlane(point) > 0;
	std::cout << "Top Face ";
	bool topF = topFace.getSignedDistanceToPlane(point) > 0;
	std::cout << "Bottom Face ";
	bool bottomF = bottomFace.getSignedDistanceToPlane(point) > 0;
	std::cout << "Right Face ";
	bool rightF = rightFace.getSignedDistanceToPlane(point) > 0;
	std::cout << "Left Face ";
	bool leftF = leftFace.getSignedDistanceToPlane(point) > 0;
	return( nearF && farF && topF && bottomF && rightF && leftF);
}

Frustum::~Frustum()
{

}