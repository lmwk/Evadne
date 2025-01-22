#include "evpch.h"
#include "Evadne/Platforms/OpenGL/OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Evadne {

    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
        :m_WindowHandle(windowHandle) 
    {
        EV_CORE_ASSERT(windowHandle, "Window handle is null");
    }

    void OpenGLContext::Init() 
    {
        EV_PROFILE_FUNCTION();

        glfwMakeContextCurrent(m_WindowHandle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        EV_CORE_ASSERT(status, "Failed to initialize Glad");

        EV_CORE_INFO("OpenGL Info:");
        EV_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
        EV_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
        EV_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));

        EV_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "Evadne requires at least OpenGL version 4.5");


    }

    void OpenGLContext::SwapBuffers() 
    {
        EV_PROFILE_FUNCTION();

        glfwSwapBuffers(m_WindowHandle);
    }

}