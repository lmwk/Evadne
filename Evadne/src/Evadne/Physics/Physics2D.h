#pragma once

#include "Evadne/ECS/Components.h"

#include "BulletDynamics/Dynamics/btRigidBody.h"

namespace Evadne {

    namespace Utils {

        inline btCollisionObject::CollisionFlags GetCollisionFlag(int id) 
        {
            if(id == 0)
                return btCollisionObject::CollisionFlags::CF_DYNAMIC_OBJECT;
            if(id == 1)
                return btCollisionObject::CollisionFlags::CF_STATIC_OBJECT;
            if(id == 2)
                return btCollisionObject::CollisionFlags::CF_KINEMATIC_OBJECT;

            EV_CORE_ASSERT(false, "Unknown body type");
            return btCollisionObject::CollisionFlags::CF_STATIC_OBJECT;
        }

        inline btCollisionObject::CollisionFlags Rigidbody2DToBullet2DBody(Rigidbody2DComponent::BodyType bodyType)
        {
            switch (bodyType)
            {
            case Rigidbody2DComponent::BodyType::Static: return btCollisionObject::CollisionFlags::CF_STATIC_OBJECT;
            case Rigidbody2DComponent::BodyType::Dynamic: return btCollisionObject::CollisionFlags::CF_DYNAMIC_OBJECT;
            case Rigidbody2DComponent::BodyType::Kinematic: return btCollisionObject::CollisionFlags::CF_KINEMATIC_OBJECT;
            }

            EV_CORE_ASSERT(false, "Unknown body type");
            return btCollisionObject::CollisionFlags::CF_STATIC_OBJECT;
        }

        inline Rigidbody2DComponent::BodyType Rigidbody2DFromBullet2DBody(btCollisionObject::CollisionFlags bodyType)
        {
            switch (bodyType)
            {
            case btCollisionObject::CollisionFlags::CF_STATIC_OBJECT: return Rigidbody2DComponent::BodyType::Static;
            case btCollisionObject::CollisionFlags::CF_DYNAMIC_OBJECT: return Rigidbody2DComponent::BodyType::Dynamic;
            case btCollisionObject::CollisionFlags::CF_KINEMATIC_OBJECT: return Rigidbody2DComponent::BodyType::Kinematic;
            }

            EV_CORE_ASSERT(false, "Unknown body type");
            return Rigidbody2DComponent::BodyType::Static;
        }

    }

}