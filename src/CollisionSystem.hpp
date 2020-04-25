//
//  CollisionSystem.hpp
//  lab1
//
//  Created by Sydney Baroya on 4/19/20.
//

#ifndef CollisionSystem_hpp
#define CollisionSystem_hpp

#include <vector>
#include "Entities/Entity.h"
#include "Entities/CameraEntity.h"

class CollisionSystem {
public:
    static CollisionSystem& getInstance() {
        static CollisionSystem _instance_;
        return(_instance_);
    }
    
    void process(std::vector<Entity*> entities);
    void checkObjectCollisions(std::vector<Entity*> entities);
    
    template<typename Base, typename T>
    inline bool instanceof(const T*) {
        return std::is_base_of<Base, T>::value;
    }
    
    int getNumberCollected() { return(number_collected); }
    
private:
    int number_collected = 0;
};

#endif /* CollisionSystem_hpp */
