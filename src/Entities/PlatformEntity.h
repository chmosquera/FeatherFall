//
//  PlatformEntity.h
//  lab1
//
//  Created by Sydney Baroya on 4/18/20.
//

#ifndef PlatformEntity_h
#define PlatformEntity_h

#include <string>
#include <glm/gtc/matrix_transform.hpp>
#include "../util/Shape.h"
#include "../Components/DrawableComponent.h"
#include "../Components/MovementComponent.hpp"
#include "../Components/PlaneColliderComponent.hpp"
#include "../OOOGL/Texture.h"
#include "../SystemEnvironment.h"
#include "Entity.h"

class PlatformEntity : public Entity {

public:
	PlatformEntity() : Entity() {}
	PlatformEntity(std::string obj_file_path, std::string tex_file_path) : Entity() {
		this->shape = std::make_shared<Shape>();
		this->shape->loadMesh(obj_file_path);
		this->shape->resize();
		this->shape->init();

		this->texture = new SimpleTexture2D(tex_file_path);
		this->texture->initParams();

		drawable = addComponent<DrawableComponent>();
		movement = addComponent<MovementComponent>();
		plane_collider = addComponent<PlaneColliderComponent>();
	}

	// Components
	DrawableComponent * drawable;
	MovementComponent * movement;
	PlaneColliderComponent * plane_collider;
	
		
	void draw(Program* prog);

	std::shared_ptr<Shape> shape;

	SimpleTexture2D * texture;

    glm::vec3 getScale() { return(scale); }
	void setScale(glm::vec3 s) { scale = s; }
private:
	std::string obj_file_path;
	std::string tex_file_path;

	glm::vec3 position = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
};
#endif /* PlatformEntity_h */
