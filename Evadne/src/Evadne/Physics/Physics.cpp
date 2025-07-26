#include "evpch.h"
#include "Physics.h"
#include "Physics2D.h"

namespace Evadne {
    Physics* Physics::instance = nullptr;

    Physics::Physics(const glm::vec3& gravity, bool is3d)
    {
        if (instance) {
            EV_WARN("Only one instance of Physics can exist");
        }
        instance = this;
        PhysicsInit(is3d);
    }

    Physics::~Physics()
    {
        DeletePhysics();
    }

    void Physics::PhysicsInit(bool is3d)
    {
        
        collisionConfiguration = new btDefaultCollisionConfiguration();
        dispatcher = new btCollisionDispatcher(collisionConfiguration);
        if(!is3d) 
        {
            m_simplexSolver = new btVoronoiSimplexSolver();
            m_pdSolver = new btMinkowskiPenetrationDepthSolver();

            m_convexAlgo2d = new btConvex2dConvex2dAlgorithm::CreateFunc(m_simplexSolver, m_pdSolver);
            m_box2dbox2dAlgo = new btBox2dBox2dCollisionAlgorithm::CreateFunc();

            dispatcher->registerCollisionCreateFunc(CONVEX_2D_SHAPE_PROXYTYPE, CONVEX_2D_SHAPE_PROXYTYPE, m_convexAlgo2d);
            dispatcher->registerCollisionCreateFunc(BOX_2D_SHAPE_PROXYTYPE, CONVEX_2D_SHAPE_PROXYTYPE, m_convexAlgo2d);
            dispatcher->registerCollisionCreateFunc(CONVEX_2D_SHAPE_PROXYTYPE, BOX_2D_SHAPE_PROXYTYPE, m_convexAlgo2d);
            dispatcher->registerCollisionCreateFunc(BOX_2D_SHAPE_PROXYTYPE, BOX_2D_SHAPE_PROXYTYPE, m_box2dbox2dAlgo);
        }
        broadphase = new btDbvtBroadphase();
        solver = new btSequentialImpulseConstraintSolver;
        dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
        dynamicsWorld->setGravity(btVector3(gravity.x, gravity.y, gravity.z));
    }

    void Physics::DeletePhysics()
    {
        delete dynamicsWorld;
        delete solver;
        delete m_convexAlgo2d;
        delete m_pdSolver;
        delete m_simplexSolver;
        delete m_box2dbox2dAlgo;
        delete dispatcher;
        delete collisionConfiguration;
        delete broadphase;
        instance = nullptr;
    }

    void Physics::SetGlobalGravity(const glm::vec3 gravity)
    {
        this->gravity = gravity;
    }

    void Physics::UpdatePhysics(Timestep ts)
    {
        dynamicsWorld->stepSimulation(ts, 10);

    }

    void Physics::AddRigidBody(Entity ent)
    {
        auto& transform = ent.GetComponent<TransformComponent>();
        auto& rb2d = ent.GetComponent<Rigidbody2DComponent>();

        btTransform groundTransform;
        auto& translation = transform.Translation;
        groundTransform.setIdentity();
        groundTransform.setOrigin(btVector3(translation.x, translation.y, translation.z));
        btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
        btRigidBody* rBody;

        if (ent.HasComponent<BoxCollider2DComponent>())
        {
            auto& bc2d = ent.GetComponent<BoxCollider2DComponent>();

            btCollisionShape* boxShape = new btBox2dShape(btVector3(bc2d.Size.x * transform.Scale.x, bc2d.Size.y * transform.Scale.y, 0));

            if(rb2d.Type == Rigidbody2DComponent::BodyType::Dynamic)
                boxShape->calculateLocalInertia(rb2d.Mass, btVector3(0, 0, 0));

            rBody = new btRigidBody(rb2d.Mass, myMotionState, boxShape);
            rBody->setFriction(bc2d.Friction);
            rBody->setRestitution(bc2d.Restitution);
            rBody->setCollisionFlags(Evadne::Utils::Rigidbody2DToBullet2DBody(rb2d.Type));
            rb2d.RuntimeBody = rBody;
            dynamicsWorld->addRigidBody(rBody);
        }
        else if (ent.HasComponent<CircleCollider2DComponent>()) 
        {
            auto& bc2d = ent.GetComponent<CircleCollider2DComponent>();

            btCollisionShape* sphereShape = new btSphereShape(transform.Scale.x * bc2d.Radius);

            if (rb2d.Type == Rigidbody2DComponent::BodyType::Dynamic)
                sphereShape->calculateLocalInertia(rb2d.Mass, btVector3(0, 0, 0));

            rBody = new btRigidBody(rb2d.Mass, myMotionState, sphereShape);
            rBody->setFriction(bc2d.Friction);
            rBody->setRestitution(bc2d.Restitution);
            rBody->setCollisionFlags(Evadne::Utils::Rigidbody2DToBullet2DBody(rb2d.Type));
            rb2d.RuntimeBody = rBody;
            dynamicsWorld->addRigidBody(rBody);
        }
        else
        {
            btCollisionShape* boxShape = new btBox2dShape(btVector3(0, 0, 0));

            if (rb2d.Type == Rigidbody2DComponent::BodyType::Dynamic)
                boxShape->calculateLocalInertia(rb2d.Mass, btVector3(0, 0, 0));
            
            rBody = new btRigidBody(rb2d.Mass, myMotionState, boxShape);
            rBody->setCollisionFlags(Evadne::Utils::Rigidbody2DToBullet2DBody(rb2d.Type));
            rb2d.RuntimeBody = rBody;
            dynamicsWorld->addRigidBody(rBody);
        }
    }

}