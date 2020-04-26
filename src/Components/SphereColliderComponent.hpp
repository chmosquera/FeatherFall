#ifndef SphereColliderComponent_hpp
#define SphereColliderComponent_hpp

#include "Component.h"
#include "ColliderComponent.h"
#include "../util/Shape.h"

class SphereColliderComponent : public ColliderComponent {
public:
	SphereColliderComponent() : ColliderComponent() {


	}
	void init(Shape shape, glm::vec3 center, float radius);
	bool isIntersecting(ColliderComponent obj);
	glm::vec3 center;
	float radius;
	bool dead;

private:
	glm::vec3 boxScale;
};



#endif