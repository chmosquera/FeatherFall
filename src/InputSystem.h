//
//  TreeEntity.h
//  lab1
//
//  Created by Chanelle Mosquera on 4/26/20.
//

#pragma once

#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H

#include "GLFW/glfw3.h"
#include <map>
#include "Application.h"
#include <iostream>
#include <functional>

class InputSystem {
public:

	typedef struct input_t {
		int key;
		int action;

		bool operator==(const input_t &o) const {
			return this->key == o.key && this->action == o.action;
		}
		bool operator<(const input_t &o) const {
			return this->key < o.key || (this->key == o.key && this->action < o.action);
		}
		bool operator>(const input_t &o) const {
			return this->key > o.key || (this->key == o.key && this->action > o.action);
		}
		bool operator<=(const input_t &o) const {
			return this->key <= o.key || (this->key == o.key && this->action <= o.action);
		}
		bool operator>=(const input_t &o) const {
			return this->key >= o.key || (this->key == o.key && this->action >= o.action);
		}

	} input;

	static InputSystem& getInstance() {
		static InputSystem _instance_;
		return(_instance_);
	}

	void init() {
		MapKeybind();
	}

	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void cursorPositionCallBack(GLFWwindow* window, double xpos, double ypos);
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);


private:

	static std::map<input_t, std::function<void()>> inputCallback;
	//static std::map<input_t, int> inputCallback;
	                                                   
	input_t UP_ARROW_PRESS = { GLFW_KEY_UP, GLFW_PRESS };
	input_t RIGHT_ARROW_PRESS = { GLFW_KEY_RIGHT, GLFW_PRESS };
	input_t DOWN_ARROW_PRESS = { GLFW_KEY_DOWN, GLFW_PRESS };
	input_t LEFT_ARROW_PRESS = { GLFW_KEY_LEFT, GLFW_PRESS };

	input_t UP_ARROW_REPEAT = { GLFW_KEY_UP, GLFW_REPEAT };
	input_t RIGHT_ARROW_REPEAT = { GLFW_KEY_RIGHT, GLFW_REPEAT };
	input_t DOWN_ARROW_REPEAT = { GLFW_KEY_DOWN, GLFW_REPEAT };
	input_t LEFT_ARROW_REPEAT = { GLFW_KEY_LEFT, GLFW_REPEAT };

	input_t UP_ARROW_RELEASE = { GLFW_KEY_UP, GLFW_RELEASE };
	input_t RIGHT_ARROW_RELEASE = { GLFW_KEY_RIGHT, GLFW_RELEASE };
	input_t DOWN_ARROW_RELEASE = { GLFW_KEY_DOWN, GLFW_RELEASE };
	input_t LEFT_ARROW_RELEASE = { GLFW_KEY_LEFT, GLFW_RELEASE };

	input_t MOUSE_BTN_DOWN = { GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS };

	static void default_action() {
		std::cout << "This is a blank action--------------" << std::endl;
		return;	
	}

	void MapKeybind();

};
#endif // !INPUT_SYSTEM_H
