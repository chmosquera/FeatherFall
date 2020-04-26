//
//  BoundingBoxComponent.cpp
//  lab1
//
//  Created by Sydney Baroya on 4/19/20.
//

#include "BoundingBoxComponent.hpp"
#include <sstream>
#include <ctgmath>
#include <iostream>

void BoundingBoxComponent::init(Shape shape, glm::vec3 start_pos, glm::vec3 scale)
{
    minX = minY = minZ = 1.1754E+38F;
    maxX = maxY = maxZ = -1.1754E+38F;
    std::vector<float> *posBuf = shape.getPosBuf();

    for (int i = 0; i < shape.getObjCount(); i++)
    for (size_t v = 0; v < posBuf[i].size() / 3; v++)
    {
        float x_val =posBuf[i][3 * v + 0];
        float y_val =posBuf[i][3 * v + 1];
        float z_val =posBuf[i][3 * v + 2];


        if (x_val < minX) minX = x_val;
        if (x_val > maxX) maxX = x_val;

        if (y_val < minY) minY = y_val;
        if (y_val > maxY) maxY = y_val;

        if (z_val < minZ) minZ = z_val;
        if (z_val > maxZ) maxZ = z_val;
    }
    
    glm::vec3 halfBoxDimensions = glm::vec3(((maxX-minX)*scale.x)-(maxX-minX), ((maxY-minY)*scale.y)-(maxY-minY), ((maxZ-minZ)*scale.z)-(maxZ-minZ));
//    halfBoxDimensions = glm::vec3(scale.x/2, scale.y/2, scale.z/2);
    if(scale.x>1.0f){
        minX += (start_pos.x - (halfBoxDimensions.x/2))*7;// *5;
        maxX += (start_pos.x + (halfBoxDimensions.x/2))*7;// *5;
        minY += (start_pos.y - (halfBoxDimensions.y/2))*7;//*5;
        maxY += (start_pos.y + (halfBoxDimensions.y/2))*7;// *5;
        minZ += (start_pos.z - (halfBoxDimensions.z/2))*7;//*5;
        maxZ += (start_pos.z + (halfBoxDimensions.z/2))*7;//*5;
    }
    else{
        minX += (start_pos.x - (halfBoxDimensions.x/2));
        maxX += (start_pos.x + (halfBoxDimensions.x/2));
        minY += (start_pos.y - (halfBoxDimensions.y/2));
        maxY += (start_pos.y + (halfBoxDimensions.y/2));
        minZ += (start_pos.z - (halfBoxDimensions.z/2));
        maxZ += (start_pos.z + (halfBoxDimensions.z/2));
    }
    
//    center_position = glm::vec3((maxX+minX)/2,(maxY+minY)/2,(maxZ+minZ)/2);
}

void BoundingBoxComponent::calculateBoxCoordinates(glm::vec3 velocity, double framerate)
{
    minX += framerate*velocity.x;//*0.5;
    maxX += framerate*velocity.x;//*0.5;
    minY += framerate*velocity.y;//*0.5;
    maxY += framerate*velocity.y;//*0.5;
    minZ += framerate*velocity.z;//*0.5;
    maxZ += framerate*velocity.z;//*0.5;

//    boxScale = glm::vec3(maxX-minX, maxY-minY, maxZ-minZ);
//
//    center_position = glm::vec3((maxX+minX)/2,(maxY+minY)/2,(maxZ+minZ)/2);
//    std::cout << "new_CENTER: " << center_position.x << ", " << center_position.y << ", " << center_position.z << std::endl;


}
void BoundingBoxComponent::calculateBoxCoordinates(glm::vec3 position)
{
    minX = position.x-1;
    maxX = position.x+1;
    minY = position.y - 5;
    maxY = position.y + 5;
    minZ = position.z-1;
    maxZ = position.z+1;

}

bool BoundingBoxComponent::isIntersecting(ColliderComponent o)
{
	
	BoundingBoxComponent* obj = dynamic_cast<BoundingBoxComponent*>(&o);
	if (obj) {
		return minX <= obj->maxX && maxX >= obj->minX &&
			minY <= obj->maxY && maxY >= obj->minY &&
			minZ <= obj->maxZ && maxZ >= obj->minZ;
	}
	return false;
	
}

