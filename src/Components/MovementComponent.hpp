//
//  MovementComponent.hpp
//  lab1
//
//  Created by Sydney Baroya on 4/19/20.
//

#ifndef MovementComponent_hpp
#define MovementComponent_hpp

#include "Component.h"


class MovementComponent : public Component {
public:
    MovementComponent() : Component() {
        this->x = 0;
        this->y = 0;
        this->z = 0;
        
        this->velocity = glm::vec3(0,0,0);
    }
//    void init() override;
    void update(double frametime) override;
    
    void updateVelocity(glm::vec3 scalar);
	void incrementVelocity(glm::vec3 val);
    void setVelocity(glm::vec3 velocity);
    glm::vec3 getVelocity();
    
    void setPosition(glm::vec3 pos);
    glm::vec3 getPosition();

private:
    float x;
    float y;
    float z;
    
    glm::vec3 velocity;

};
#endif /* MovementComponent_hpp */
