//
//  CameraEntity.cpp
//  lab1
//
//  Created by Sydney Baroya on 4/19/20.
//

#include "CameraEntity.h"
#include "../Components/BoundingBoxComponent.hpp"
#include "../Components/MovementComponent.hpp"

glm::mat4 CameraEntity::getView() const
{

	glm::mat4 R = glm::rotate(glm::mat4(1), 0.1f, glm::vec3(1, 0, 0));
	//glm::vec4 dir = glm::vec4(0, 0, -5, 1);
	//dir = dir * R;
	//glm::vec3 pos = glm::vec3(dir.x, dir.y, dir.z);


	//glm::mat4 T = M * glm::translate(glm::mat4(1), movement->getPosition());
	//glm::mat4 V = R * T;

	//return V;

		// You should know the camera move reversely relative to the user input.

	// That's the point of Graphics Camera

	glm::quat reverseOrient = glm::conjugate(orientation);
	glm::mat4 rot = glm::mat4_cast(reverseOrient);
	glm::mat4 translation = glm::translate(glm::mat4(1.0), -movement->getPosition());

	return rot * translation;

}
glm::vec3 CameraEntity::getViewDir() const
{
    return glm::vec3(0,0,0);
}

void CameraEntity::setProjectionMatrix(Program * prog) {
	prog->bind();
	glUniformMatrix4fv(prog->getUniform("P"), 1, GL_FALSE, &getPerspective()[0][0]);
	prog->unbind();
}
void CameraEntity::setViewMatrix(Program * prog) {
	prog->bind();
	glUniformMatrix4fv(prog->getUniform("V"), 1, GL_FALSE, &getView()[0][0]);
	prog->unbind();
}

static glm::vec3 speed = glm::vec3(0);
static float step = 0.1f;
void CameraEntity::smoothTranslate(glm::vec3 maxSpeed) {
	if (speed.x < maxSpeed.x) speed.x += step;
	if (speed.y < maxSpeed.y) speed.y += step;
	if (speed.z < maxSpeed.z) speed.z += step;

	if (speed.x > maxSpeed.x) speed.x -= step;
	if (speed.y > maxSpeed.y) speed.y -= step;
	if (speed.z > maxSpeed.z) speed.z -= step;

	//getComponent<MovementComponent>().incrementVelocity(speed);
}


//static float w = 0;
void CameraEntity::update(double frametime){
    getComponent<BoundingBoxComponent>().calculateBoxCoordinates(movement->getPosition());
	movement->update(frametime);

	//x += 0.1f;	
	//movement->setVelocity(glm::vec3(0,0,x));
	glm::vec3 vel = movement->getVelocity();
	M = M * glm::translate(glm::mat4(1), movement->getVelocity()); // *glm::rotate(glm::mat4(1), w, glm::vec3(1, 0, 0));

}

glm::mat4 CameraEntity::getViewMatrix()
{
	// You should know the camera move reversely relative to the user input.

	// That's the point of Graphics Camera

	glm::quat reverseOrient = glm::conjugate(orientation);
	glm::mat4 rot = glm::mat4_cast(reverseOrient);
	glm::mat4 translation = glm::translate(glm::mat4(1.0), -movement->getPosition());

	return rot * translation;
}

void CameraEntity::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{

	CursorPos newpos = { xoffset, yoffset };
	float dX = (xoffset - old_cursor_pos.x) * mouse_sensativity;
	float dY = (yoffset - old_cursor_pos.y) * mouse_sensativity * 0.1;

	pitch += dX;
	yaw -= dY; // inverse

	// continue changing look direction if mouse is along edge of acreen
	if (xoffset > (screensize.x / 4) && xoffset < (screensize.x / 4 * 3)) old_cursor_pos.x = xoffset;
	if (yoffset > (screensize.y / 4) && xoffset < (screensize.y / 4 * 3)) old_cursor_pos.y = yoffset;

	//old_cursor_pos = glm::vec2(xoffset, yoffset);
	//float pitch_change = xoffset * mouse_sensativity;
	//float yaw_change = yoffset * mouse_sensativity;


	updateCameraVectors();
}

void CameraEntity::updateCameraVectors()
{
	// Yaw
	glm::quat aroundY = glm::angleAxis(glm::radians(-pitch), glm::vec3(0, 1, 0));

	// Pitch
	glm::quat aroundX = glm::angleAxis(glm::radians(yaw), glm::vec3(1, 0, 0));

	orientation = aroundY * aroundX;
}