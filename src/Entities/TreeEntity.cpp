//
//  TreeEntity.cpp
//  OOOGLtarget
//
//  Created by Sydney Baroya on 4/21/20.
//

#include "TreeEntity.h"

void TreeEntity::draw(Program* prog)
{
	prog->bind();

	// for transparency TODO
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

	// root model
    glm::mat4 M = glm::translate(glm::mat4(1), getComponent<MovementComponent>().getPosition()); // * rotation *
	getComponent<DrawableComponent>().setModelMatrix(M);

    // draw the base
	texture_1->uploadToGPU(prog->getPID(), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_1->getTextureID());

	glm::mat4 M_base = getComponent<DrawableComponent>().getModelMatrix();

    glUniformMatrix4fv(prog->getUniform("M"), 1, GL_FALSE, &M_base[0][0]);
    this->shape_1->draw(prog, false);
    

    // draw the top
    texture_2->uploadToGPU(prog->getPID(), 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_2->getTextureID());

    glm::mat4 M_top = getComponent<DrawableComponent>().getModelMatrix() * glm::translate(glm::mat4(1), glm::vec3(0, 1.5, 0)) * glm::scale(glm::mat4(1), glm::vec3(1.5));

    glUniformMatrix4fv(prog->getUniform("M"), 1, GL_FALSE, &M_top[0][0]);
    this->shape_2->draw(prog, false);

	glDisable(GL_BLEND);
	prog->unbind();
}
