//
//  CollisionSystem.cpp
//  lab1
//
//  Created by Sydney Baroya on 4/19/20.
//

#include "CollisionSystem.hpp"
#include "Components/BoundingBoxComponent.hpp"
#include "Components/MovementComponent.hpp"
#include "Components/SphereColliderComponent.hpp"
#include "Components/PlaneColliderComponent.hpp"
#include "Components/ColliderComponent.h"
#include "Entities/AppleEntity.h"
#include "Entities/TreeEntity.h"


void CollisionSystem::process(std::vector<Entity*> entities)
{
	
	for (std::size_t i = 0; i < entities.size(); ++i)
	{
		Entity* entity_i = entities[i];
		ColliderComponent* collider_i = &entity_i->getComponent<SphereColliderComponent>();
	}
	/*
    BoundingBoxComponent bound_box_i, bound_box_j;
    for(std::size_t i=0; i<entities.size(); ++i)
    {
        Entity* entity_i = entities[i];
        bound_box_i = entity_i->getComponent<BoundingBoxComponent>();

        for(std::size_t j=i+1; j<entities.size(); ++j)
        {
            Entity* entity_j = entities[j];
            bound_box_j = entity_j->getComponent<BoundingBoxComponent>();
            
            bool has_collided = bound_box_i.isIntersecting(bound_box_j);
            
            if(has_collided)
            {
                if(AppleEntity* ae_i = dynamic_cast<AppleEntity*>(entity_i))
                {
                    if(AppleEntity* ae_j = dynamic_cast<AppleEntity*>(entity_j))
                    {
                        //both apples stop moving or change to opposite directions
                        ae_i->getComponent<MovementComponent>().updateVelocity(glm::vec3(-1));
                        ae_j->getComponent<MovementComponent>().updateVelocity(glm::vec3(-1));
                    }
                    else if (CameraEntity* ce_j = dynamic_cast<CameraEntity*>(entity_j))
                    {
                        if(!ae_i->is_collected){
                            //apple is collected: stops moving, changes color, etc.
                            ae_i->getComponent<MovementComponent>().updateVelocity(glm::vec3(0));
                            number_collected++;
                            ae_i->is_collected=true;
                        }
                    }
                    else if (TreeEntity* te_j = dynamic_cast<TreeEntity*>(entity_j))
                    {
                        //apple changes directions
                        ae_i->getComponent<MovementComponent>().updateVelocity(glm::vec3(-1));
                    }
                }
                else if(CameraEntity* ce_i = dynamic_cast<CameraEntity*>(entity_i))
                {
                    if(AppleEntity* ae_j = dynamic_cast<AppleEntity*>(entity_j))
                    {
                        if(!ae_j->is_collected){
                           //apple is collected: stops moving, changes color, etc.
                            ae_j->getComponent<MovementComponent>().updateVelocity(glm::vec3(0));
                                number_collected++;
                            ae_j->is_collected=true;

                        }
                    }
                    else if (TreeEntity* te_j = dynamic_cast<TreeEntity*>(entity_j))
                    {
                        //player cannot move in that direction anymore
                        ce_i->getComponent<MovementComponent>().updateVelocity(glm::vec3(0));
                    }
                }
                else if(TreeEntity* te_i = dynamic_cast<TreeEntity*>(entity_i))
                {
                    if(AppleEntity* ae_j = dynamic_cast<AppleEntity*>(entity_j))
                    {
                       //apple changes directions
                        ae_j->getComponent<MovementComponent>().updateVelocity(glm::vec3(-1));
                    }
                    else if(CameraEntity* ce_j = dynamic_cast<CameraEntity*>(entity_j))
                    {
                       //player cannot move in that direction anymore
                        ce_j->getComponent<MovementComponent>().updateVelocity(glm::vec3(0));

                    }
                }
            }
        }
		*/
    
}



