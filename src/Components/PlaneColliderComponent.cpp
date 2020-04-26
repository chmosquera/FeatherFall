#include "PlaneColliderComponent.hpp"
#include "SphereColliderComponent.hpp"
#include <sstream>
#include <ctgmath>
#include <iostream>

void PlaneColliderComponent::init(glm::vec3 a, glm::vec3 b, glm::vec3 c)
{
	n = normalize(cross(b - a, c - a));
	d = dot(n, a);
}

bool PlaneColliderComponent::isIntersecting(ColliderComponent o)
{

	SphereColliderComponent* obj = dynamic_cast<SphereColliderComponent*>(&o);
	if (obj) {
		return false;
	}
	return false;

}
