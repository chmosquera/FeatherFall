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

		addComponent<DrawableComponent>();
		addComponent<MovementComponent>();
	}
		
	void draw(Program* prog);

	std::shared_ptr<Shape> shape;

	SimpleTexture2D * texture;
private:
	std::string obj_file_path;
	std::string tex_file_path;
};
#endif /* PlatformEntity_h */
