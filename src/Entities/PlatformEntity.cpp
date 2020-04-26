//
//  PlatformEntity.cpp
//  OOOGLtarget
//
//  Created by Sydney Baroya on 4/21/20.
//

#include "PlatformEntity.h"
#include "../Components/DrawableComponent.h"
#include "Entity.h"

void PlatformEntity::draw(Program* apple_prog)
{
	DrawableComponent * drawable = &getComponent<DrawableComponent>();
	MovementComponent * movement = &getComponent<MovementComponent>();

	apple_prog->bind();
	
	// Get updated position
	if (movement != nullptr) position = movement->getPosition();

    texture->uploadToGPU(apple_prog->getPID(), 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture->getTextureID());
       
    glUniformMatrix4fv(apple_prog->getUniform("M"), 1, GL_FALSE, &drawable->getModelMatrix()[0][0]);
    this->shape->draw(apple_prog, false);


    apple_prog->unbind();

}

