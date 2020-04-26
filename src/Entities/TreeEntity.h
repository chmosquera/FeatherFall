//
//  TreeEntity.h
//  lab1
//
//  Created by Sydney Baroya on 4/18/20.
//

#ifndef TreeEntity_h
#define TreeEntity_h

#include <string>
#include <glm/gtc/matrix_transform.hpp>
#include "../Components/DrawableComponent.h"
#include "../Components/MovementComponent.hpp"
#include "../OOOGL/Texture.h"
#include "../SystemEnvironment.h"
#include "Entity.h"

class TreeEntity : public Entity {

public:
	TreeEntity() : Entity() {}
	TreeEntity(std::string obj1_file_path, std::string obj2_file_path, std::string tex1_file_path, std::string tex2_file_path) : Entity() {
		this->shape_1 = std::make_shared<Shape>();
		this->shape_1->loadMesh(obj1_file_path);
		this->shape_1->resize();
		this->shape_1->init();
		this->shape_2 = std::make_shared<Shape>();
		this->shape_2->loadMesh(obj2_file_path);
		this->shape_2->resize();
		this->shape_2->init();

		this->texture_1 = new SimpleTexture2D(tex1_file_path);
		this->texture_1->initParams();
		this->texture_2 = new SimpleTexture2D(tex2_file_path);
		this->texture_2->initParams();

		addComponent<DrawableComponent>();
	}

	// Call this before drawing, before the render loop
	//void init(Program* prog);
	void draw(Program* prog) override;

	std::shared_ptr<Shape> shape_1;
	std::shared_ptr<Shape> shape_2;

	SimpleTexture2D * texture_1;
	SimpleTexture2D * texture_2;

	void setScale(glm::vec3 s) { scale = s; }
    glm::vec3 getScale() { return(scale); }

private:
	std::string obj_file_path;
	std::string tex_file_path;
};


#endif /* TreeEntity_h */
