//
//  AppleEntity.h
//  lab1
//
//  Created by Sydney Baroya on 4/18/20.
//

#ifndef AppleEntity_h
#define AppleEntity_h

#include <string>
#include <glm/gtc/matrix_transform.hpp>
#include "../util/Shape.h"
#include "../Components/DrawableComponent.h"
#include "../Components/MovementComponent.hpp"
#include "../OOOGL/Texture.h"
#include "../SystemEnvironment.h"
#include "Entity.h"

class AppleEntity : public Entity {
    
public:
    AppleEntity() : Entity() {
	
	}
    AppleEntity(std::string obj_file_path, std::string tex_file_path) : Entity() {
        this->shape = std::make_shared<Shape>();
        this->shape->loadMesh(obj_file_path);
        this->shape->resize();
        this->shape->init();

		this->texture = new SimpleTexture2D(tex_file_path);
		this->texture->initParams();

		// Apples will for sure have a drawable component, so lets instantiate it here instead of in the application
		this->addComponent<DrawableComponent>();
		this->addComponent<MovementComponent>();
    }

	// Components
//	DrawableComponent * drawable;
//	MovementComponent * movement;

	// Call this before drawing, before the render loop
	//void init(Program* prog);
	void draw(Program* prog) override;
    void update(double frametime) override;

	std::shared_ptr<Shape> shape;

	SimpleTexture2D * texture;

	void setScale(glm::vec3 s) {scale = s; }
    glm::vec3 getScale() { return(scale); }
    bool is_collected = false;

private:    
    std::string obj_file_path;
	std::string tex_file_path;
    
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
};


#endif /* AppleEntity_h */
