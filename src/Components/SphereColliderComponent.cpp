#include "SphereColliderComponent.hpp"
#include "PlaneColliderComponent.hpp"
#include <sstream>
#include <ctgmath>
#include <cmath>
#include <iostream>

void SphereColliderComponent::init(Shape shape, glm::vec3 pos, float rad)
{
	center = pos;
	radius = rad;
	dead = false;
}

bool SphereColliderComponent::isIntersecting(ColliderComponent obj)
{
	
	SphereColliderComponent* sphere = dynamic_cast<SphereColliderComponent*>(&obj);
	if (sphere) {
		return glm::length(center - sphere->center) < (radius + sphere->radius);
	}
	PlaneColliderComponent* plane = dynamic_cast<PlaneColliderComponent*>(&obj);
	if (plane) {
		float distance = dot(center, plane->n) - plane->d;
		return fabs(distance) <= radius;
	}
	return false;
	
}


