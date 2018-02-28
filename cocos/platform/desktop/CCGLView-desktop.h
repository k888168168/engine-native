/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#pragma once

#include "glfw3/glfw3.h"
#include "glfw3/glfw3native.h"

#include "platform/CCPlatformMacros.h"
#include "platform/CCApplication.h"

#ifndef GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WIN32
#endif

#ifndef GLFW_EXPOSE_NATIVE_WGL
#define GLFW_EXPOSE_NATIVE_WGL
#endif

NS_CC_BEGIN

class CC_DLL GLView final
{
public:
    GLView(Application *application, const std::string& name, int x, int y, int width, int height,
           Application::PixelFormat pixelformat, Application::DepthFormat depthFormat, int multiSampleCount);
    ~GLView();

    bool windowShouldClose() const;
    void pollEvents();
    void swapBuffers();
    float getScaleFactor() const;
    
private:  
    bool initGlew();

    // GLFW callbacks
    void onGLFWError(int errorID, const char* errorDesc);
    void onGLFWMouseCallBack(GLFWwindow* window, int button, int action, int modify);
    void onGLFWMouseMoveCallBack(GLFWwindow* window, double x, double y);
    void onGLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void onGLFWCharCallback(GLFWwindow* window, unsigned int character);
    void onGLFWWindowIconifyCallback(GLFWwindow* window, int iconified);

    bool _captured = false;
 
    GLFWwindow* _mainWindow = nullptr;
    GLFWmonitor* _monitor = nullptr;

    std::string _glfwError;
    
    Application *_application = nullptr;

    float _mouseX = 0;
    float _mouseY = 0;

    friend class GLFWEventHandler;
};


class CC_DLL GLFWEventHandler final
{
public:
    static void onGLFWError(int errorID, const char* errorDesc)
    {
        _view->onGLFWError(errorID, errorDesc);
    }

    static void onGLFWMouseCallBack(GLFWwindow* window, int button, int action, int modify)
    {
        _view->onGLFWMouseCallBack(window, button, action, modify);
    }

    static void onGLFWMouseMoveCallBack(GLFWwindow* window, double x, double y)
    {
        _view->onGLFWMouseMoveCallBack(window, x, y);
    }

    static void onGLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        _view->onGLFWKeyCallback(window, key, scancode, action, mods);
    }

    static void onGLFWCharCallback(GLFWwindow* window, unsigned int character)
    {
        _view->onGLFWCharCallback(window, character);
    }

    static void setGLView(GLView* view)
    {
        _view = view;
    }

    static void onGLFWWindowIconifyCallback(GLFWwindow* window, int iconified)
    {
        _view->onGLFWWindowIconifyCallback(window, iconified);
    }

private:
    static GLView* _view;
};

NS_CC_END   // end of namespace   cocos2d