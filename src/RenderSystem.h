#pragma once

#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H


#include <GLFW/glfw3.h>
//#include "Scene.h"
#include "Program.h"
#include "Entities/Entity.h"
#include "Components/DrawableComponent.h"
#include "Entities/CameraEntity.h"

class RenderSystem {
public:
    static RenderSystem& getInstance() {
        static RenderSystem _instance_;
        return(_instance_);
    }

    void init(GLFWwindow* window);
    void process(std::vector<Entity*> entities, CameraEntity* camera);
//    virtual void processEntity(const MVPSet& MVP, Entity* entity, Program* shader = nullptr);
private:
    GLFWwindow* _mWindow = nullptr;
    int w_width;
    int w_height;
};

#endif
