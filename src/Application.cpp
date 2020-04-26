#include "Application.h"
#include <glad/glad.h>
#include <iostream>
#include "../src/util/ShaderLibrary.hpp"
#include "Entities/AppleEntity.h"
#include "Entities/TreeEntity.h"
#include "Entities/PlatformEntity.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Components/MovementComponent.hpp"
#include "Components/BoundingBoxComponent.hpp"
#include "CollisionSystem.hpp"
#include "util/Time.h"
#include "InputSystem.h"

static void error_callback(int error, const char* description) { std::cerr << "glfw error: " << description << std::endl; };
static void resize_callback(GLFWwindow* window, int in_width, int in_height) { };

void Application::init(int argc, char** argv)
{
	config.startup_state = StartupState(argc, argv);
	initGLFW();
	initGL();
	initShaders();
	initScene();
	InputSystem::getInstance().init();
}

void Application::run()
{
    Time time;
    RenderSystem& render_system = RenderSystem::getInstance();
    CollisionSystem& collision_system = CollisionSystem::getInstance();

    render_system.init(_window);
//    std::vector<Entity*> new_entities(entities);
//    new_entities.push_back(&camera);
    //double frame = 0;
    //std::vector<Entity*> new_entities(entities);
    //new_entities.emplace_back(camera);
    //
    //int total_apples = 0;
    //int total_collected = 0;
	// Loop until the user closes the window.
	while (!glfwWindowShouldClose(_window))
	{
        double frametime = time.getElapsedTime();

		// TODO put this in another class
		int state = glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_LEFT);
		if (state == GLFW_PRESS) {
			camera->unlockOrientation();
			std::cout << "locked" << std::endl;
		}
		else {
			camera->lockOrientation();
			std::cout << "unlocked" << std::endl;
		}

        //if(frame>=2.0){

            
        //AppleEntity* apple = new AppleEntity(resourceDir + "apple.obj", resourceDir + "Apple_BaseColor.png");
        //apple->setProgName("apple_prog");
        //apple->setScale(glm::vec3(0.25f));
        //MovementComponent* mc_a = &apple->getComponent<MovementComponent>();
        //mc_a->setPosition(glm::vec3(rand()%8-4, -0.5,rand()%8-4));
        //int v = rand()%2 - 1;
        //if(v==0)
        //    v=-1;
        //mc_a->setVelocity(glm::vec3(rand()%2-1,0,v));
        //apple->addComponent<BoundingBoxComponent>();
        //apple->getComponent<BoundingBoxComponent>().init(*apple->shape, mc_a->getPosition(), apple->getScale());
        //new_entities.emplace_back(apple);

        //    frame = 0.0;
        //    total_apples++;
        //    
        //    std::cout<<"APPLES COLLECTED: "<<total_collected<<std::endl;
        //    std::cout<<"APPLES LEFT: "<<total_apples-total_collected<<std::endl;

        //    
        //}
        //frame+=frametime;
        for(Entity* e : entities)
            e->update(frametime);
        collision_system.process(entities);
        //total_collected = collision_system.getNumberCollected();
		render_system.process(entities, camera);

		// Swap front and back buffers.
		glfwSwapBuffers(_window);
		// Poll for and process events.
		glfwPollEvents();
	}
}


void Application::cleanup()
{
	glfwHideWindow(_window);
	glfwDestroyWindow(_window);
	glfwTerminate();
}

bool Application::shouldExit() const
{
	return false;
}

void Application::initGL()
{
	// Initialize GLAD
	if (!gladLoadGL())
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		exit(1);
	}
	glGetError();
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}

void Application::initGLFW()
{
	InputSystem * inputSystem = &InputSystem::getInstance();
	glfwSetErrorCallback(error_callback);

	// Initialize glfw library
	if (!glfwInit())
	{
		std::cerr << "GLFW initialization failed!" << std::endl;
		exit(0);
	}

	//request the highest possible version of OGL - important for mac
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	// Create a windowed mode window and its OpenGL context.
	_window = glfwCreateWindow(config.w_width, config.w_height, "lab1", nullptr, nullptr);
	if (!_window)
	{
		glfwTerminate();
		exit(0);
	}

	glfwMakeContextCurrent(_window);

	// Set vsync
	glfwSwapInterval(1);

	glfwSetKeyCallback(_window, inputSystem->keyCallback);
	glfwSetMouseButtonCallback(_window, inputSystem->mouseButtonCallback);
	glfwSetCursorPosCallback(_window, inputSystem->cursorPositionCallBack);
	glfwSetFramebufferSizeCallback(_window, resize_callback);

}

void Application::initShaders()
{
	ShaderLibrary::getInstance().loadFromShaderCollection(srcDir + "shaders.txt");
}

void Application::initScene()
{
	camera = new CameraEntity();
	BoundingBoxComponent * bb = camera->addComponent<BoundingBoxComponent>();
	bb->minX = -1.0f;
	bb->maxX = 1.0f;
	bb->minY = -1.5f;
	bb->maxY = 1.5f;
	bb->minZ = -1.0f;
	bb->maxZ = 1.0f;
	

	camera->position = glm::vec3(0, 5, 0);
	entities.emplace_back(camera);
	camera->setProgName("platform_prog");

    glm::ivec2 screensize = getCurrScreenSize();
	camera->setAspect(screensize.x / screensize.y);
	camera->setScreensize(screensize);
	entities.emplace_back(camera);

	// -- platform --
	PlatformEntity* platform = new PlatformEntity(resourceDir + "platform.obj", resourceDir + "Zelt_Baumstamm_Boden_diffuse.png");
    platform->setProgName("platform_prog");
    MovementComponent* mc_p = &platform->getComponent<MovementComponent>();
	platform->position = glm::vec3(0.0f, -1, -5);
	platform->scale = glm::vec3(10, 1, 10);
    platform->addComponent<BoundingBoxComponent>();
    platform->getComponent<BoundingBoxComponent>().init(*platform->shape, platform->position, platform->scale);
	

	TreeEntity* tree = new TreeEntity(resourceDir + "tree_base.obj", resourceDir + "tree_top.obj", resourceDir + "Zelt_Baumstamm_Boden_diffuse.png", resourceDir + "leaf_tex.png");
	tree->setProgName("tree_prog");
	tree->position = glm::vec3(0, 0, -5);
	tree->addComponent<BoundingBoxComponent>();
	tree->getComponent<BoundingBoxComponent>().init(*tree->shape_1, tree->position, tree->scale);
	entities.emplace_back(tree);

	camera->setTargetObject(tree);
    
	 // --- tree -----
     /*for(int i=-2; i<3; i++)
     {
         TreeEntity* tree = new TreeEntity(resourceDir + "tree_base.obj", resourceDir + "tree_top.obj", resourceDir + "Zelt_Baumstamm_Boden_diffuse.png", resourceDir + "leaf_tex.png");
         tree->setProgName("tree_prog");
         MovementComponent* mc_t = &tree->getComponent<MovementComponent>();
         mc_t->setPosition(glm::vec3(i, 0 , -13));
         tree->addComponent<BoundingBoxComponent>();
         tree->getComponent<BoundingBoxComponent>().init(*tree->shape_1, mc_t->getPosition(), tree->getScale());
         entities.emplace_back(tree);
     }
     for(int i=-3; i>-9; i--)
     {
         TreeEntity* tree = new TreeEntity(resourceDir + "tree_base.obj", resourceDir + "tree_top.obj", resourceDir + "Zelt_Baumstamm_Boden_diffuse.png", resourceDir + "leaf_tex.png");
         tree->setProgName("tree_prog");
         MovementComponent* mc_t = &tree->getComponent<MovementComponent>();
         mc_t->setPosition(glm::vec3(i, 0 , -16-i));
         tree->addComponent<BoundingBoxComponent>();
         tree->getComponent<BoundingBoxComponent>().init(*tree->shape_1, mc_t->getPosition(), tree->getScale());
         entities.emplace_back(tree);
     }
     for(int i=-8; i<-2; i++)
     {
         TreeEntity* tree = new TreeEntity(resourceDir + "tree_base.obj", resourceDir + "tree_top.obj", resourceDir + "Zelt_Baumstamm_Boden_diffuse.png", resourceDir + "leaf_tex.png");
         tree->setProgName("tree_prog");
         MovementComponent* mc_t = &tree->getComponent<MovementComponent>();
         mc_t->setPosition(glm::vec3(-8, 0 , i));
         tree->addComponent<BoundingBoxComponent>();
         tree->getComponent<BoundingBoxComponent>().init(*tree->shape_1, mc_t->getPosition(), tree->getScale());
         entities.emplace_back(tree);
     }
     for(int i=-7; i<-2; i++)
     {
         TreeEntity* tree = new TreeEntity(resourceDir + "tree_base.obj", resourceDir + "tree_top.obj", resourceDir + "Zelt_Baumstamm_Boden_diffuse.png", resourceDir + "leaf_tex.png");
         tree->setProgName("tree_prog");
         MovementComponent* mc_t = &tree->getComponent<MovementComponent>();
         mc_t->setPosition(glm::vec3(i, 0 , i+7));
         tree->addComponent<BoundingBoxComponent>();
         tree->getComponent<BoundingBoxComponent>().init(*tree->shape_1, mc_t->getPosition(), tree->getScale());
         entities.emplace_back(tree);
     }

     for(int i=-2; i<3; i++)
        {
            TreeEntity* tree = new TreeEntity(resourceDir + "tree_base.obj", resourceDir + "tree_top.obj", resourceDir + "Zelt_Baumstamm_Boden_diffuse.png", resourceDir + "leaf_tex.png");
            tree->setProgName("tree_prog");
            MovementComponent* mc_t = &tree->getComponent<MovementComponent>();
            mc_t->setPosition(glm::vec3(i, 0 , 4));
            tree->addComponent<BoundingBoxComponent>();
            tree->getComponent<BoundingBoxComponent>().init(*tree->shape_1, mc_t->getPosition(), tree->getScale());
            entities.emplace_back(tree);
        }
        for(int i=8; i>2; i--)
        {
            TreeEntity* tree = new TreeEntity(resourceDir + "tree_base.obj", resourceDir + "tree_top.obj", resourceDir + "Zelt_Baumstamm_Boden_diffuse.png", resourceDir + "leaf_tex.png");
            tree->setProgName("tree_prog");
            MovementComponent* mc_t = &tree->getComponent<MovementComponent>();
            mc_t->setPosition(glm::vec3(i, 0 , -i+7));
            tree->addComponent<BoundingBoxComponent>();
            tree->getComponent<BoundingBoxComponent>().init(*tree->shape_1, mc_t->getPosition(), tree->getScale());
            entities.emplace_back(tree);
        }
        for(int i=-8; i<-2; i++)
        {
            TreeEntity* tree = new TreeEntity(resourceDir + "tree_base.obj", resourceDir + "tree_top.obj", resourceDir + "Zelt_Baumstamm_Boden_diffuse.png", resourceDir + "leaf_tex.png");
            tree->setProgName("tree_prog");
            MovementComponent* mc_t = &tree->getComponent<MovementComponent>();
            mc_t->setPosition(glm::vec3(8, 0 , i));
            tree->addComponent<BoundingBoxComponent>();
            tree->getComponent<BoundingBoxComponent>().init(*tree->shape_1, mc_t->getPosition(), tree->getScale());
            entities.emplace_back(tree);
        }
        for(int i=2; i<8; i++)
        {
            TreeEntity* tree = new TreeEntity(resourceDir + "tree_base.obj", resourceDir + "tree_top.obj", resourceDir + "Zelt_Baumstamm_Boden_diffuse.png", resourceDir + "leaf_tex.png");
            tree->setProgName("tree_prog");
            MovementComponent* mc_t = &tree->getComponent<MovementComponent>();
            mc_t->setPosition(glm::vec3(i, 0 , i-15));
            tree->addComponent<BoundingBoxComponent>();
            tree->getComponent<BoundingBoxComponent>().init(*tree->shape_1, mc_t->getPosition(), tree->getScale());
            entities.emplace_back(tree);
        }*/
	
    for(Entity* e : entities){
        Program * prog = ShaderLibrary::getInstance().getPtr(e->getProgName());
        prog->addUniform("P");
        prog->addUniform("V");
        prog->addUniform("M");
        prog->addAttribute("vertPos");
        prog->addAttribute("vertTex");
    }
     Program * prog = ShaderLibrary::getInstance().getPtr("apple_prog");
     prog->addUniform("P");
     prog->addUniform("V");
     prog->addUniform("M");
     prog->addAttribute("vertPos");
     prog->addAttribute("vertTex");
}

bool Application::isFullscreen()
{
	return glfwGetWindowMonitor(_window) != nullptr;
}
void Application::setFullScreen(bool fullscreen)
{
	if (fullscreen_mode == fullscreen)
		return;

	if (fullscreen)
	{
		// backup windwo position and window size
		glfwGetWindowPos(_window, &_wndPos[0], &_wndPos[1]);
		glfwGetWindowSize(_window, &_wndSize[0], &_wndSize[1]);

		// get reolution of monitor
		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

		// swithc to full screen
		glfwSetWindowMonitor(_window, _monitor, 0, 0, mode->width, mode->height, 0);
		fullscreen_mode = true;
	}
	else
	{
		// restore last window size and position
		glfwSetWindowMonitor(_window, nullptr, _wndPos[0], _wndPos[1], _wndSize[0], _wndSize[1], 0);
		fullscreen_mode = false;
	}


}

glm::ivec2 Application::getCurrScreenSize()
{
	int width, height;
	glfwGetFramebufferSize(_window, &width, &height);

	return glm::ivec2(width, height);
}

StartupState::StartupState(int argc, char** argv)
{
	if (argc > 1) {
		parseArgs(argc, argv);
	}
}

void StartupState::parseArgs(int argc, char** argv)
{
	std::vector<std::string> args((&argv[1]), &(argv[argc]));
	std::vector<std::string>::iterator carg = args.begin();
	while (carg != args.end()) {
		if (carg->at(0) == '-') {
			carg = parseOption(carg, args);
		}
		else {
			carg = parseInput(carg, args);
		}
	}
}

std::vector<std::string>::iterator StartupState::parseOption(std::vector<std::string>::iterator carg, const std::vector<std::string>& args)
{
	if (*carg == "-dev" || *carg == "--developer")
		this->developer_mode = true;
	return std::next(carg);
}

std::vector<std::string>::iterator StartupState::parseInput(std::vector<std::string>::iterator carg, const std::vector<std::string>& args)
{
	input_paths.push_back(*carg);
	return std::next(carg);
}
