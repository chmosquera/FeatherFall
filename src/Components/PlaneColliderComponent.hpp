#ifndef PlaneColliderComponent_hpp
#define PlaneColliderComponent_hpp

#include "Component.h"
#include "ColliderComponent.h"
#include "../util/Shape.h"

class PlaneColliderComponent : public ColliderComponent {
public:
	PlaneColliderComponent() : ColliderComponent() {


	}
	void init(glm::vec3 a, glm::vec3 b, glm::vec3 c);
	bool isIntersecting(ColliderComponent obj);
	glm::vec3 n;
	float d;

private:
	glm::vec3 boxScale;
};
#endif
