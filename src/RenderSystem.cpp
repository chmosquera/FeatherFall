#include "RenderSystem.h"
#include "util/ShaderLibrary.hpp"

void RenderSystem::init(GLFWwindow* window)
{
    _mWindow = window;
    glfwGetFramebufferSize(_mWindow, &w_width, &w_height);
        
    glViewport(0, 0, w_width, w_height);
    
    
    glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.01176f, 0.6706f, 1.0f, 1.0f);

   
}

void RenderSystem::process(std::vector<Entity*> entities, CameraEntity* camera){
    // Clear framebuffer.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ShaderLibrary& shlib = ShaderLibrary::getInstance();
	    
    for(Entity* entity : entities)
    {
		if (!(entity->getProgName().empty())) {
			Program* prog = shlib.getPtr(entity->getProgName());

			// send V & P matrices to GPU for this program
			camera->setProjectionMatrix(prog);
			camera->setViewMatrix(prog);

			entity->draw(prog);
		}
    }
}
