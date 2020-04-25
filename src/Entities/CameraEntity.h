#pragma once
#ifndef CAMERA_ENTITY_H
#define CAMERA_ENTITY_H

#include "Entity.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include "../Components/MovementComponent.hpp"

class CameraEntity : public Entity {
public:

	struct CursorPos {
		double x_pos;
		double y_pos;
	};

	CameraEntity() : Entity(), fov(45.0f), near_plane(.01f), far_plane(100.0f) {
		init();
	}
	CameraEntity(float fov, const glm::vec3& loc) : Entity(), fov(fov), near_plane(.01f), far_plane(100.0f){
		init();
	}
	CameraEntity(float fov, const glm::vec3& loc, float near_plane, float far_plane) : Entity(), fov(fov), near_plane(near_plane), far_plane(far_plane) {
		init();
	}

	// Setup camera properties
	void init() {
		movement = addComponent<MovementComponent>();
	}

	// Components
	MovementComponent * movement;

	void update(double frametime) override;
	glm::mat4 getPerspective() const {
		return(glm::perspective(glm::radians(fov), aspect, near_plane, far_plane));
	}

	void updateRotation(glm::vec3 rot) { rotation += rot; }

	virtual glm::mat4 getOrthographic() const {
		return(glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, near_plane, far_plane));
	}

	glm::mat4 getOrthographic(float left, float right, float bottom, float top, float near_plane, float far_plane) {
		return(glm::ortho(left, right, bottom, top, near_plane, far_plane));
	}

	virtual glm::mat4 getView() const;
	virtual glm::vec3 getViewDir() const;
	
	void setProjectionMatrix(Program * prog);
	void setViewMatrix(Program * prog);

	virtual void setNearPlane(float near_plane) { this->near_plane = near_plane; }
	virtual void setFarPlane(float far_plane) { this->far_plane = far_plane; }
	void setAspect(float aspect) { this->aspect = aspect;  }

	void smoothTranslate(glm::vec3 v);

	glm::mat4 getViewMatrix();	
	void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
//	void ProcessMouseScroll(float yoffset);

	void setScreensize(glm::ivec2 s) { screensize = s; }

	// Model matrix is needed to move this entity
	glm::mat4 M = glm::mat4(1);

	glm::quat orientation = glm::quat(0, 0, 0, -1);	
	float pitch = 0;
	float yaw = 0;

	float movement_speed = 10.0f;
	float mouse_sensativity = 0.01f;
	float zoom = 45.0f;

	glm::vec2 old_cursor_pos = glm::vec2(0);

private:
	glm::vec3 rotation = glm::vec3(0);
	float fov;
	float near_plane;
	float far_plane;
	float aspect;
	glm::ivec2 screensize;

	void updateCameraVectors();
};

#endif
