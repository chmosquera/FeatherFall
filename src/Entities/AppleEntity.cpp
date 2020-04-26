//
//  TreeEntity.cpp
//  lab1
//
//  Created by Sydney Baroya on 4/19/20.
//

#include "AppleEntity.h"
#include "../Components/MovementComponent.hpp"

void AppleEntity::draw(Program* prog)
{
	prog->bind();
    MovementComponent movement = getComponent<MovementComponent>();
	//std::cout << "velocity : " << movement.getVelocity().x << ", " << movement.getVelocity().y << ", " << movement.getVelocity().z << std::endl;
    texture->uploadToGPU(prog->getPID(), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->getTextureID());

//	glm::mat4 M = drawable->getModelMatrix();
	glm::mat4 M = glm::translate(glm::mat4(1), movement.getPosition()); // * rotation *
	M = M * glm::scale(glm::mat4(1), scale);
    getComponent<DrawableComponent>().setModelMatrix(M);

    glUniformMatrix4fv(prog->getUniform("M"), 1, GL_FALSE, &getComponent<DrawableComponent>().getModelMatrix()[0][0]);


    this->shape->draw(prog, false);

    prog->unbind();

}
const float gravity = -2.0; //increase in velocity per second
static float x = 0.0f;
void AppleEntity::update(double frametime){
    MovementComponent* mc = &getComponent<MovementComponent>();
	if (mc->getPosition().y < 0.5) {
		return;
	}
	mc->incrementVelocity(glm::vec3(0.0, gravity * frametime, 0.0));
    mc->update(frametime);

    SphereColliderComponent* sc = &getComponent<SphereColliderComponent>();
	sc->center = mc->getPosition();
    //bc->calculateBoxCoordinates(sc->getVelocity(), frametime);
}
