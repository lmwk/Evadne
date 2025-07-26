#include "evpch.h"
#include "ScriptGlue.h"
#include "ScriptEngine.h"

#include "Evadne/Core/UUID.h"
#include "Evadne/Input/KeyCodes.h"
#include "Evadne/Input/Input.h"

#include "Evadne/Scene/Scene.h"
#include "Evadne/ECS/Entity.h"

#include "Evadne/Physics/Physics2D.h"

#include "mono/metadata/object.h"
#include "mono/metadata/reflection.h"

#include "BulletDynamics/Dynamics/btRigidBody.h"

namespace Evadne {

	static std::unordered_map<MonoType*, std::function<bool(Entity)>> s_EntityHasComponentFuncs;

#define EV_ADD_INTERNAL_CALL(Name) mono_add_internal_call("Evadne.InternalCalls::"#Name, Name)

    static void NativeLog(MonoString* string, int parameter) 
    {
        char* cStr = mono_string_to_utf8(string);
        std::string str(cStr);
        mono_free(cStr);
        std::cout << str << ", " << parameter << std::endl;
    }

	static void NativeLog_Vector(glm::vec3* parameter, glm::vec3* outResult)
	{
		EV_CORE_WARN("Value: {0}", glm::to_string(*parameter));
		*outResult = glm::normalize(*parameter);
	}

	static float NativeLog_VectorDot(glm::vec3* parameter)
	{
		EV_CORE_WARN("Value: {0}", glm::to_string(*parameter));
		return glm::dot(*parameter, *parameter);
	}

	static MonoObject* GetScriptInstance(UUID entityID) 
	{
		return ScriptEngine::GetManagedInstance(entityID);
	}

	

	static bool Entity_HasComponent(UUID entityID, MonoReflectionType* componentType)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		EV_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		EV_CORE_ASSERT(entity);

		MonoType* managedType = mono_reflection_type_get_type(componentType);
		EV_CORE_ASSERT(s_EntityHasComponentFuncs.find(managedType) != s_EntityHasComponentFuncs.end());
		return s_EntityHasComponentFuncs.at(managedType)(entity);
	}

	static uint64_t Entity_FindEntityByName(MonoString* name) 
	{
		char* nameCStr = mono_string_to_utf8(name);

		Scene* scene = ScriptEngine::GetSceneContext();
		EV_CORE_ASSERT(scene);
		Entity entity = scene->FindEntityByName(nameCStr);
		mono_free(nameCStr);

		if (!entity)
			return 0;

		return entity.GetUUID();
	}



	static void TransformComponent_GetTranslation(UUID entityID, glm::vec3* outTranslation)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		EV_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		EV_CORE_ASSERT(entity);

		*outTranslation = entity.GetComponent<TransformComponent>().Translation;
	}

	static void TransformComponent_SetTranslation(UUID entityID, glm::vec3* translation)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		EV_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		EV_CORE_ASSERT(entity);

		entity.GetComponent<TransformComponent>().Translation = *translation;
	}

	static void Rigidbody2DComponent_ApplyLinearImpulse(UUID entityID, glm::vec2* impulse, glm::vec2* point)
	{
		
		Scene* scene = ScriptEngine::GetSceneContext();
		EV_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		EV_CORE_ASSERT(entity);

		auto& rb2d = entity.GetComponent<Rigidbody2DComponent>();
		btRigidBody* body = (btRigidBody*)rb2d.RuntimeBody;
		body->applyForce(btVector3(impulse->x, impulse->y, 0), btVector3(point->x, point->y, 0));
		body->activate(true);
	}

	static void Rigidbody2DComponent_ApplyLinearImpulseToCenter(UUID entityID, glm::vec2* impulse)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		EV_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		EV_CORE_ASSERT(entity);

		auto& rb2d = entity.GetComponent<Rigidbody2DComponent>();
		btRigidBody* body = (btRigidBody*)rb2d.RuntimeBody;
		body->applyCentralForce(btVector3(impulse->x, impulse->y, 0));
		body->activate(true);
	}

	static void Rigidbody2DComponent_GetLinearVelocity(UUID entityID, glm::vec2* outLinearVelocity)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		EV_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		EV_CORE_ASSERT(entity);

		auto& rb2d = entity.GetComponent<Rigidbody2DComponent>();
		btRigidBody* body = (btRigidBody*)rb2d.RuntimeBody;
		const btVector3& linearVelocity = body->getLinearVelocity();
		*outLinearVelocity = glm::vec2(linearVelocity.x(), linearVelocity.y());
	}

	static Rigidbody2DComponent::BodyType Rigidbody2DComponent_GetType(UUID entityID) 
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		EV_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		EV_CORE_ASSERT(entity);

		auto& rb2d = entity.GetComponent<Rigidbody2DComponent>();
		btRigidBody* body = (btRigidBody*)rb2d.RuntimeBody;
		return Utils::Rigidbody2DFromBullet2DBody(Utils::GetCollisionFlag(body->getCollisionFlags()));
	}

	static void Rigidbody2DComponent_SetType(UUID entityID, Rigidbody2DComponent::BodyType bodyType)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		EV_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		EV_CORE_ASSERT(entity);

		auto& rb2d = entity.GetComponent<Rigidbody2DComponent>();
		btRigidBody* body = (btRigidBody*)rb2d.RuntimeBody;
		body->setCollisionFlags(Utils::Rigidbody2DToBullet2DBody(bodyType));
	}

	static bool Input_IsKeyDown(KeyCode keycode)
	{
		return Input::IsKeyPressed(keycode);
	}

	template<typename... Component>
	static void RegisterComponent()
	{
		([]()
			{
				std::string_view typeName = typeid(Component).name();
				size_t pos = typeName.find_last_of(':');
				std::string_view structName = typeName.substr(pos + 1);
				std::string managedTypename = fmt::format("Evadne.{}", structName);

				MonoType* managedType = mono_reflection_type_from_name(managedTypename.data(), ScriptEngine::GetCoreAssemblyImage());
				if (!managedType)
				{
					EV_CORE_ERROR("Could not find component type {}", managedTypename);
					return;
				}
				s_EntityHasComponentFuncs[managedType] = [](Entity entity) { return entity.HasComponent<Component>(); };
			}(), ...);
	}

	template<typename... Component>
	static void RegisterComponent(ComponentGroup<Component...>)
	{
		RegisterComponent<Component...>();
	}

	void ScriptGlue::RegisterComponents() 
	{
		s_EntityHasComponentFuncs.clear();
		RegisterComponent(AllComponents{});
	}

	void ScriptGlue::RegisterFunctions()
	{
		EV_ADD_INTERNAL_CALL(NativeLog);
		EV_ADD_INTERNAL_CALL(NativeLog_Vector);
		EV_ADD_INTERNAL_CALL(NativeLog_VectorDot);

		EV_ADD_INTERNAL_CALL(GetScriptInstance);
		EV_ADD_INTERNAL_CALL(Entity_HasComponent);
		EV_ADD_INTERNAL_CALL(Entity_FindEntityByName);
		EV_ADD_INTERNAL_CALL(TransformComponent_GetTranslation);
		EV_ADD_INTERNAL_CALL(TransformComponent_SetTranslation);

		EV_ADD_INTERNAL_CALL(Rigidbody2DComponent_ApplyLinearImpulse);
		EV_ADD_INTERNAL_CALL(Rigidbody2DComponent_ApplyLinearImpulseToCenter);
		EV_ADD_INTERNAL_CALL(Rigidbody2DComponent_GetLinearVelocity);
		EV_ADD_INTERNAL_CALL(Rigidbody2DComponent_GetType);
		EV_ADD_INTERNAL_CALL(Rigidbody2DComponent_SetType);

		EV_ADD_INTERNAL_CALL(Input_IsKeyDown);
	}

}