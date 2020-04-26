#include "InputSystem.h"

std::map<InputSystem::input_t, std::function<void()>> InputSystem::inputCallback;

void InputSystem::MapKeybind() {
	inputCallback[UP_ARROW_PRESS] = std::bind([]() {
		Application::getInstance().camera->movement->setVelocity(glm::vec3(0, 0, -1));
		std::cout << "up" << std::endl;
	});
	inputCallback[RIGHT_ARROW_PRESS] = std::bind([]() {
		Application::getInstance().camera->movement->setVelocity(glm::vec3(1, 0, 0));
		
	});
	inputCallback[DOWN_ARROW_PRESS] = std::bind([]() {
		Application::getInstance().camera->movement->setVelocity(glm::vec3(0, 0, 1));
		
	});
	inputCallback[LEFT_ARROW_PRESS] = std::bind([]() {
		Application::getInstance().camera->movement->setVelocity(glm::vec3(-1, 0, 0));
		
	});

	//
	//inputCallback[UP_ARROW_REPEAT] = std::bind( [] () {
	//	Application::getInstance().camera->smoothTranslate(glm::vec3(0, 0, 1));
	//	std::cout << "repeat" << std::endl;
	//});
	//inputCallback[RIGHT_ARROW_REPEAT] = std::bind(&default_action);
	//inputCallback[DOWN_ARROW_REPEAT] = std::bind(&default_action);
	//inputCallback[LEFT_ARROW_REPEAT] = std::bind(&default_action);


	void (*stop_camera_movement)() = []() {
		Application::getInstance().camera->movement->setVelocity(glm::vec3(0, 0, 0));
	};
	inputCallback[UP_ARROW_RELEASE] = std::bind(stop_camera_movement);
	inputCallback[RIGHT_ARROW_RELEASE] = std::bind(stop_camera_movement);
	inputCallback[DOWN_ARROW_RELEASE] = std::bind(stop_camera_movement);
	inputCallback[LEFT_ARROW_RELEASE] = std::bind(stop_camera_movement);
}

	void InputSystem::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		input_t input = { key, action };
		if (inputCallback[input]) (inputCallback[input])();		
		
	}

	void InputSystem::cursorPositionCallBack(GLFWwindow* window, double xpos, double ypos) {
		
		Application::getInstance().camera->ProcessMouseMovement(xpos, ypos);
	}

	void InputSystem::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{

	}

