#include "evpch.h"
#include "Evadne/Scene/Scene.h"

#include "Evadne/ECS/Components.h"
#include "Evadne/ECS/ScriptableEntity.h"
#include "Evadne/Rendering/2D/Renderer2D.h"

#include <glm/glm.hpp>

#include "Evadne/ECS/Entity.h"

#include "Evadne/Physics/Physics.h"

#include "BulletDynamics/Dynamics/btRigidBody.h"

namespace Evadne {

    Scene::Scene()
    {
    }

    Scene::~Scene()
    {

    }

    Entity Scene::CreateEntity(const std::string& name)
    {
        return CreateEntityWithUUID(UUID(), name);
    }

    Entity Scene::CreateEntityWithUUID(UUID uuid, const std::string& name)
    {
        Entity entity = { m_Registry.create(), this };
        entity.AddComponent<IDComponent>(uuid);
        entity.AddComponent<TransformComponent>();
        auto& tag = entity.AddComponent<TagComponent>();
        tag.Tag = name.empty() ? "Entity" : name;
        return entity;
    }

    void Scene::DestroyEntity(Entity entity)
    {
        m_Registry.destroy(entity);
    }

    void Scene::OnRuntimeStart()
    {
        m_Physics = new Physics();

        auto view = m_Registry.view<Rigidbody2DComponent>();
        for (auto e : view)
        {
            Entity entity = { e, this };
            m_Physics->AddRigidBody(entity);
        }
    }

    void Scene::OnRuntimeStop()
    {
        delete m_Physics;
    }

    void Scene::OnUpdateRuntime(Timestep ts)
    {
        {
            m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc) 
                {
                    if(!nsc.Instance) 
                    {
                        nsc.Instance = nsc.InstantiateScript();
                        nsc.Instance->m_Entity = Entity{ entity, this };
                        nsc.Instance->OnCreate();
                    }
                    nsc.Instance->OnUpdate(ts);


                });
        }

        {
            m_Physics->UpdatePhysics(ts);

            auto view = m_Registry.view<Rigidbody2DComponent>();
            for(auto e : view) 
            {
                Entity entity = { e, this };
                auto& transform = entity.GetComponent<TransformComponent>();
                auto& rb2d = entity.GetComponent<Rigidbody2DComponent>();

                btRigidBody* body = (btRigidBody*)rb2d.RuntimeBody;
                const auto& position = body->getWorldTransform();
                transform.Translation.x = position.getOrigin().x();
                transform.Translation.y = position.getOrigin().y();
                transform.Rotation.z = position.getRotation().z();
            }
        }

        Camera* mainCamera = nullptr;
        glm::mat4 cameraTransform;
        {
            auto view = m_Registry.view<TransformComponent, CameraComponent>();
            for(auto entity : view)
            {
                auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);

                if(camera.Primary) 
                {
                    mainCamera = &camera.Camera;
                    cameraTransform = transform.GetTransform();
                    break;
                }
            }
        }

        if (mainCamera)
        {
            Renderer2D::BeginScene(*mainCamera, cameraTransform);

            auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
            for (auto entity : group)
            {
                auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
                Renderer2D::DrawSprite(transform.GetTransform(), sprite, (int)entity);
            }

            Renderer2D::EndScene();
        }
    }
    void Scene::OnUpdateEditor(Timestep ts, EditorCamera& camera)
    {
        Renderer2D::BeginScene(camera);
        auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
        for (auto entity : group)
        {
            auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
            Renderer2D::DrawSprite(transform.GetTransform(), sprite, (int)entity);
        }
        Renderer2D::EndScene();
    }
    void Scene::OnViewportResize(uint32_t width, uint32_t height)
    {
        m_ViewportHeight = width;
        m_ViewportHeight = height;

        auto view = m_Registry.view<CameraComponent>();
        for(auto entity: view) 
        {
            auto& cameraComponent = view.get<CameraComponent>(entity);
            if (!cameraComponent.FixedAspectRatio)
                cameraComponent.Camera.SetViewportSize(width, height);
        }
    }

    Entity Scene::GerPrimaryCameraEntity()
    {
        auto view = m_Registry.view<CameraComponent>();
        for (auto entity : view) 
        {
            const auto& camera = view.get<CameraComponent>(entity);
            if (camera.Primary)
                return Entity{ entity, this };
        }
        return {};
    }

    template<typename T>
    void Scene::OnComponentAdded(Entity entity, T& component)
    {
        //static_assert(false);
    }
    template<>
    void Scene::OnComponentAdded<IDComponent>(Entity entity, IDComponent& component) 
    {
    }
    template<>
    void Scene::OnComponentAdded<TransformComponent>(Entity entity, TransformComponent& component)
    {
    }
    template<>
    void Scene::OnComponentAdded<CameraComponent>(Entity entity, CameraComponent& component)
    {
        if (m_ViewportWidth > 0 && m_ViewportHeight > 0)
            component.Camera.SetViewportSize(m_ViewportWidth, m_ViewportHeight);
    }
    template<>
    void Scene::OnComponentAdded<SpriteRendererComponent>(Entity entity, SpriteRendererComponent& component)
    {
    }
    template<>
    void Scene::OnComponentAdded<TagComponent>(Entity entity, TagComponent& component)
    {
    }
    template<>
    void Scene::OnComponentAdded<NativeScriptComponent>(Entity entity, NativeScriptComponent& component)
    {
    }

    template<>
    void Scene::OnComponentAdded<Rigidbody2DComponent>(Entity entity, Rigidbody2DComponent& component)
    {
    }

    template<>
    void Scene::OnComponentAdded<BoxCollider2DComponent>(Entity entity, BoxCollider2DComponent& component)
    {
    }
}