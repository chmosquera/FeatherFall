#pragma once
#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H
#include <string>
#include "../Program.h"
#include "Component.h"


class ColliderComponent : public Component {

public:
	ColliderComponent() : Component() {}
	virtual void init() {}
	virtual void update(double frametime) {}
	virtual void draw(Program* prog) {}
	virtual bool isIntersecting(ColliderComponent obj) { return false; }


	virtual ~ColliderComponent() {}
};

#endif