#include "evpch.h"
#include "Evadne/Platforms/OpenGL/OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <gl/GL.h>

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

#ifdef EV_ENABLE_ASSERTS
        int versionMajor;
        int versionMinor;
        glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
        glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

        EV_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Evadne requires at least OpenGL version 4.5!");
#endif


    }

    void OpenGLContext::SwapBuffers() 
    {
        EV_PROFILE_FUNCTION();

        glfwSwapBuffers(m_WindowHandle);
    }

}