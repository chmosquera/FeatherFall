//
//  DrawableComponent.h
//  lab1
//
//  Created by Sydney Baroya on 4/18/20.
//

#ifndef DrawableComponent_h
#define DrawableComponent_h

#include "../Components/Component.h"
#include <glm/gtc/matrix_transform.hpp>

struct MVPSet{
    glm::mat4 M;
    glm::mat4 V;
    glm::mat4 P;
};

class DrawableComponent : public Component {
public:
    DrawableComponent() : Component(){}
//    void draw(Program* program) override;
    MVPSet* getMVP() { return(&MVP);}
    void setMVP(MVPSet matrices) { MVP = matrices; }
	
	// VP is dependent on camera, so i think a drawable only cares about model, lmk?
	glm::mat4 getModelMatrix() { return modelMatrix; }
	void setModelMatrix(glm::mat4 m) { modelMatrix = m; }
	void setModelMatrix(glm::vec3 pos, glm::vec3 scale, glm::vec3 rot) {
		glm::mat4 M = glm::translate(glm::mat4(1), pos)
						* glm::rotate(glm::mat4(1), rot.x, glm::vec3(1, 0, 0))
						* glm::rotate(glm::mat4(1), rot.y, glm::vec3(0, 1, 0))
						* glm::rotate(glm::mat4(1), rot.z, glm::vec3(1, 0, 1))
						* glm::scale(glm::mat4(1), scale);

		modelMatrix = M;
	}

private:
    MVPSet MVP;

	glm::mat4 modelMatrix = glm::mat4(1);
};


#endif /* DrawableComponent_h */
