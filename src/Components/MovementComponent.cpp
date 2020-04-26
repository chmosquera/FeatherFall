//
//  MovementComponent.cpp
//  lab1
//
//  Created by Sydney Baroya on 4/19/20.
//

#include "MovementComponent.hpp"
#include <iostream>


void MovementComponent::update(double frametime){

//	std::cout << "velocity : " << velocity.x << ", " << velocity.y << ", " << velocity.z << std::endl;
    this->x += frametime * this->velocity.x;
    this->y += frametime * this->velocity.y;
    this->z += frametime * this->velocity.z;
}

void MovementComponent::setPosition(glm::vec3 pos){ x = pos.x; y = pos.y; z = pos.z; }

glm::vec3 MovementComponent::getPosition() { return(glm::vec3(x, y, z)); }

void MovementComponent::updateVelocity(glm::vec3 scalar){
    this->velocity.x *= scalar.x;
    this->velocity.y *= scalar.y;
    this->velocity.z *= scalar.z;
}

void MovementComponent::incrementVelocity(glm::vec3 val) {
	this->velocity.x += val.x;
	this->velocity.y += val.y;
	this->velocity.z += val.z;
}

void MovementComponent::setVelocity(glm::vec3 v) {
	velocity = v;
}
glm::vec3 MovementComponent::getVelocity() { return(velocity); }
