#include "evpch.h"
#include "ScriptEngine.h"

#include "ScriptGlue.h"

#include "mono/jit/jit.h"
#include "mono/metadata/assembly.h"
#include "mono/metadata/object.h"

namespace Evadne {

    

    namespace Utils {

        static char* ReadBytes(const std::filesystem::path& filepath, uint32_t* outSize)
        {
            std::ifstream stream(filepath, std::ios::binary | std::ios::ate);

            if (!stream)
            {
                // Failed to open the file
                return nullptr;
            }

            std::streampos end = stream.tellg();
            stream.seekg(0, std::ios::beg);
            uint32_t size = end - stream.tellg();

            if (size == 0)
            {
                // File is empty
                return nullptr;
            }

            char* buffer = new char[size];
            stream.read((char*)buffer, size);
            stream.close();

            *outSize = size;
            return buffer;
        }

        MonoAssembly* LoadMonoAssembly(const std::filesystem::path& assemblyPath)
        {
            uint32_t fileSize = 0;
            char* fileData = ReadBytes(assemblyPath, &fileSize);

            MonoImageOpenStatus status;
            MonoImage* image = mono_image_open_from_data_full(fileData, fileSize, 1, &status, 0);

            if (status != MONO_IMAGE_OK)
            {
                const char* errorMessage = mono_image_strerror(status);

                return nullptr;
            }

            std::string pathString = assemblyPath.string();
            MonoAssembly* assembly = mono_assembly_load_from_full(image, pathString.c_str(), &status, 0);
            mono_image_close(image);

            delete[] fileData;

            return assembly;
        }

        void PrintAssemblyTypes(MonoAssembly* assembly)
        {
            MonoImage* image = mono_assembly_get_image(assembly);
            const MonoTableInfo* typeDefinitionsTable = mono_image_get_table_info(image, MONO_TABLE_TYPEDEF);
            int32_t numTypes = mono_table_info_get_rows(typeDefinitionsTable);

            for (int32_t i = 0; i < numTypes; i++)
            {
                uint32_t cols[MONO_TYPEDEF_SIZE];
                mono_metadata_decode_row(typeDefinitionsTable, i, cols, MONO_TYPEDEF_SIZE);

                const char* nameSpace = mono_metadata_string_heap(image, cols[MONO_TYPEDEF_NAMESPACE]);
                const char* name = mono_metadata_string_heap(image, cols[MONO_TYPEDEF_NAME]);

                EV_CORE_TRACE("{}.{}", nameSpace, name);
            }

        }
    }
    
    struct ScriptEngineData
    {
        MonoDomain* RootDomain = nullptr;
        MonoDomain* AppDomain = nullptr;

        MonoAssembly* CoreAssembly = nullptr;
        MonoImage* CoreAssemblyImage = nullptr;

        MonoAssembly* AppAssembly = nullptr;
        MonoImage* AppAssemblyImage = nullptr;

        ScriptClass EntityClass;

        std::unordered_map<std::string, Ref<ScriptClass>> EntityClasses;
        std::unordered_map<UUID, Ref<ScriptInstance>> EntityInstances;

        Scene* SceneContext = nullptr;
    };

    static ScriptEngineData* sc_Data = nullptr;

    void ScriptEngine::Init()
    {
        sc_Data = new ScriptEngineData();

        InitMono();
        LoadAssembly("Resources/Scripts/Evadne-ScriptCore.dll");

        LoadAppAssembly("SandboxProject/Assets/Scripts/Binaries/Sandbox.dll");
        LoadAssemblyClasses();

        ScriptGlue::RegisterComponents();
        ScriptGlue::RegisterFunctions();

        // Retrieve and instantiate class (with constructor)
        sc_Data->EntityClass = ScriptClass("Evadne", "Entity", true);
#if 0
        MonoObject* instance = sc_Data->EntityClass.Instantiate();

        // Call method
        MonoMethod* printMessageFunc = sc_Data->EntityClass.GetMethod("PrintMessage", 0);
        sc_Data->EntityClass.InvokeMethod(instance, printMessageFunc);

        // Call method with param
        MonoMethod* printIntFunc = sc_Data->EntityClass.GetMethod("PrintInt", 1);

        int value = 5;
        void* param = &value;

        sc_Data->EntityClass.InvokeMethod(instance, printIntFunc, &param);

        MonoMethod* printIntsFunc = sc_Data->EntityClass.GetMethod("PrintInts", 2);
        int value2 = 508;
        void* params[2] =
        {
            &value,
            &value2
        };
        sc_Data->EntityClass.InvokeMethod(instance, printIntsFunc, params);

        MonoString* monoString = mono_string_new(sc_Data->AppDomain, "Hello World from C++!");
        MonoMethod* printCustomMessageFunc = sc_Data->EntityClass.GetMethod("PrintCustomMessage", 1);
        void* stringParam = monoString;
        sc_Data->EntityClass.InvokeMethod(instance, printCustomMessageFunc, &stringParam);

        EV_CORE_ASSERT(false);
#endif
    }

    void ScriptEngine::Shutdown()
    {
        ShutdownMono();
        delete sc_Data;
    }

    void ScriptEngine::LoadAssembly(const std::filesystem::path& filepath)
    {
        sc_Data->AppDomain = mono_domain_create_appdomain("EvadneScriptRuntime", nullptr);
        mono_domain_set(sc_Data->AppDomain, true);

        
        sc_Data->CoreAssembly = Utils::LoadMonoAssembly(filepath);
        sc_Data->CoreAssemblyImage = mono_assembly_get_image(sc_Data->CoreAssembly);
    }

    void ScriptEngine::LoadAppAssembly(const std::filesystem::path& filepath)
    {
        sc_Data->AppAssembly = Utils::LoadMonoAssembly(filepath);
        auto assemb = sc_Data->AppAssembly;
        sc_Data->AppAssemblyImage = mono_assembly_get_image(sc_Data->AppAssembly);
        auto assembi = sc_Data->AppAssemblyImage;

    }

    void ScriptEngine::OnRuntimeStart(Scene* scene)
    {
        sc_Data->SceneContext = scene;
    }

    void ScriptEngine::OnRuntimeStop()
    {
        sc_Data->SceneContext = nullptr;

        sc_Data->EntityInstances.clear();
    }

    bool ScriptEngine::EntityClassExists(const std::string& fullClassName)
    {
        return sc_Data->EntityClasses.find(fullClassName) != sc_Data->EntityClasses.end();
    }

    void ScriptEngine::OnCreateEntity(Entity entity)
    {
        const auto& sc = entity.GetComponent<ScriptComponent>();
        if(ScriptEngine::EntityClassExists(sc.ClassName)) 
        {
            Ref<ScriptInstance> instance = CreateRef<ScriptInstance>(sc_Data->EntityClasses[sc.ClassName], entity);
            sc_Data->EntityInstances[entity.GetUUID()] = instance;
            instance->InvokeOnCreate();
        }
    }

    void ScriptEngine::OnUpdateEntity(Entity entity, Timestep ts)
    {
        UUID entityUUID = entity.GetUUID();
        EV_CORE_ASSERT(sc_Data->EntityInstances.find(entityUUID) != sc_Data->EntityInstances.end());

        Ref<ScriptInstance> instance = sc_Data->EntityInstances[entityUUID];
        instance->InvokeOnUpdate((float)ts);
    }

    Scene* ScriptEngine::GetSceneContext()
    {
        return sc_Data->SceneContext;
    }

    std::unordered_map<std::string, Ref<ScriptClass>> ScriptEngine::GetEntityClasses()
    {
        return sc_Data->EntityClasses;
    }

    MonoImage* ScriptEngine::GetCoreAssemblyImage()
    {
        return sc_Data->CoreAssemblyImage;
    }

    void ScriptEngine::InitMono()
    {
        mono_set_assemblies_path("mono/lib");

        MonoDomain* rootDomain = mono_jit_init("EvadneJITRuntime");
        EV_CORE_ASSERT(rootDomain);

        sc_Data->RootDomain = rootDomain;

    }

    void ScriptEngine::ShutdownMono()
    {
        sc_Data->AppDomain = nullptr;

        sc_Data->RootDomain = nullptr;
    }

    void ScriptEngine::LoadAssemblyClasses()
    {
        sc_Data->EntityClasses.clear();

        const MonoTableInfo* typeDefinitionsTable = mono_image_get_table_info(sc_Data->AppAssemblyImage, MONO_TABLE_TYPEDEF);
        int32_t numTypes = mono_table_info_get_rows(typeDefinitionsTable);
        MonoClass* entityClass = mono_class_from_name(sc_Data->CoreAssemblyImage, "Evadne", "Entity");

        for (int32_t i = 0; i < numTypes; i++)
        {
            uint32_t cols[MONO_TYPEDEF_SIZE];
            mono_metadata_decode_row(typeDefinitionsTable, i, cols, MONO_TYPEDEF_SIZE);

            const char* nameSpace = mono_metadata_string_heap(sc_Data->AppAssemblyImage, cols[MONO_TYPEDEF_NAMESPACE]);
            const char* name = mono_metadata_string_heap(sc_Data->AppAssemblyImage, cols[MONO_TYPEDEF_NAME]);
            std::string fullName;
            if (strlen(nameSpace) != 0)
                fullName = fmt::format("{}.{}", nameSpace, name);
            else
                fullName = name;

            MonoClass* monoClass = mono_class_from_name(sc_Data->AppAssemblyImage, nameSpace, name);

            if (monoClass == entityClass)
                continue;

            bool isEntity = mono_class_is_subclass_of(monoClass, entityClass, false);
            if (isEntity)
                sc_Data->EntityClasses[fullName] = CreateRef<ScriptClass>(nameSpace, name);
        }
    }

    MonoObject* ScriptEngine::InstantiateClass(MonoClass* monoClass)
    {
        MonoObject* instance = mono_object_new(sc_Data->AppDomain, monoClass);
        mono_runtime_object_init(instance);
        return instance;
    }

    

    

    ScriptClass::ScriptClass(const std::string& classNamespace, const std::string& className, bool isCore)
        : m_ClassNamespace(classNamespace), m_ClassName(className)
    {
        m_MonoClass = mono_class_from_name(isCore ? sc_Data->CoreAssemblyImage : sc_Data->AppAssemblyImage, classNamespace.c_str(), className.c_str());
    }

    MonoObject* ScriptClass::Instantiate()
    {
        return ScriptEngine::InstantiateClass(m_MonoClass);
    }

    MonoMethod* ScriptClass::GetMethod(const std::string& name, int parameterCount)
    {
        return mono_class_get_method_from_name(m_MonoClass, name.c_str(), parameterCount);
    }

    MonoObject* ScriptClass::InvokeMethod(MonoObject* instance, MonoMethod* method, void** params)
    {
        return mono_runtime_invoke(method, instance, params, nullptr);
    }

    ScriptInstance::ScriptInstance(Ref<ScriptClass> scriptClass, Entity entity)
        : m_ScriptClass(scriptClass)
    {
        m_Instance = scriptClass->Instantiate();

        m_Constructor = sc_Data->EntityClass.GetMethod(".ctor", 1);
        m_OnCreateMethod = scriptClass->GetMethod("OnCreate", 0);
        m_OnUpdateMethod = scriptClass->GetMethod("OnUpdate", 1);

        {
            UUID entityID = entity.GetUUID();
            void* param = &entityID;
            m_ScriptClass->InvokeMethod(m_Instance, m_Constructor, &param);
        }
    }

    void ScriptInstance::InvokeOnCreate()
    {
        if (m_OnCreateMethod)
            m_ScriptClass->InvokeMethod(m_Instance, m_OnCreateMethod);
    }

    void ScriptInstance::InvokeOnUpdate(float ts)
    {
        if (m_OnUpdateMethod)
        {
            void* param = &ts;
            m_ScriptClass->InvokeMethod(m_Instance, m_OnUpdateMethod, &param);
        }
    }

}