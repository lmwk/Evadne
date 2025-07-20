#include "evpch.h"
#include "ScriptGlue.h"

#include "mono/metadata/object.h"

namespace Evadne {

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

	void ScriptGlue::RegisterFunctions()
	{
		EV_ADD_INTERNAL_CALL(NativeLog);
		EV_ADD_INTERNAL_CALL(NativeLog_Vector);
		EV_ADD_INTERNAL_CALL(NativeLog_VectorDot);
	}

}