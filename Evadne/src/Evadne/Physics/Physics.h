#pragma once

#include "BulletCollision/CollisionDispatch/btCollisionObject.h"

#include "BulletCollision/BroadphaseCollision/btDbvtBroadphase.h"
#include <BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h>

#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <BulletSoftBody/btSoftRigidDynamicsWorld.h>

#include <BulletSoftBody/btSoftBodyRigidBodyCollisionConfiguration.h>

#include "BulletCollision/CollisionDispatch/btBox2dBox2dCollisionAlgorithm.h"
#include "BulletCollision/CollisionDispatch/btConvex2dConvex2dAlgorithm.h"

#include "BulletCollision/CollisionShapes/btBox2dShape.h"
#include "BulletCollision/CollisionShapes/btConvex2dShape.h"
#include "BulletCollision/CollisionShapes/btSphereShape.h"

#include "BulletCollision/NarrowPhaseCollision/btMinkowskiPenetrationDepthSolver.h"

#include "Evadne/ECS/Components.h"
#include "Evadne/ECS/Entity.h"

#include "BulletDynamics/Dynamics/btRigidBody.h"
#include "BulletDynamics/Dynamics/btDynamicsWorld.h"
#include "LinearMath/btDefaultMotionState.h"

namespace Evadne {


    class Physics 
    {
    public:
        Physics(const glm::vec3& gravity = glm::vec3(0, -9.81, 0), bool is3d = false);
        ~Physics();
        static Physics* instance;
        btCollisionObject::CollisionFlags Rigidbody2DToBullet2DBody(Rigidbody2DComponent::BodyType bodyType);
        void PhysicsInit(bool is3d);
        void DeletePhysics();
        void SetGlobalGravity(const glm::vec3 gravity);
        void UpdatePhysics(Timestep ts);
        void AddRigidBody(Entity ent);
    public:
        btDiscreteDynamicsWorld* dynamicsWorld;
        btBroadphaseInterface* broadphase;
        btDefaultCollisionConfiguration* collisionConfiguration;
        btCollisionDispatcher* dispatcher;
        btSequentialImpulseConstraintSolver* solver;
        glm::vec3 gravity = glm::vec3(0, -9.81, 0);
        static inline const glm::vec3 DefaultGravity = glm::vec3(0, -9.81, 0);
    private:

        btConvex2dConvex2dAlgorithm::CreateFunc* m_convexAlgo2d;
        btVoronoiSimplexSolver* m_simplexSolver;
        btMinkowskiPenetrationDepthSolver* m_pdSolver;
        btBox2dBox2dCollisionAlgorithm::CreateFunc* m_box2dbox2dAlgo;
    };

}