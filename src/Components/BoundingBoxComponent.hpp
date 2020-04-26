//
//  BoundingBoxComponent.hpp
//  lab1
//
//  Created by Sydney Baroya on 4/19/20.
//

#ifndef BoundingBoxComponent_hpp
#define BoundingBoxComponent_hpp
#include "Component.h"
#include "ColliderComponent.h"
#include "../util/Shape.h"

class BoundingBoxComponent : public ColliderComponent {
public:
    BoundingBoxComponent() : ColliderComponent() {
        
        
    }
    void init(Shape shape, glm::vec3 start_pos, glm::vec3 scale);
    void calculateBoxCoordinates(glm::vec3 velocity, double framerate);
    void calculateBoxCoordinates(glm::vec3 position);
    bool isIntersecting(ColliderComponent obj);
    glm::vec3 getBox() { return(boxScale); }
    
    float dist;
    glm::vec3 center_position;
    float minX, minY, minZ, maxX, maxY, maxZ;
    //std::vector<glm::vec3> pos;

private:
    glm::vec3 boxScale;
};



#endif /* BoundingBoxComponent_hpp */
