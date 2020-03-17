#ifndef YASENGINEGL_HPP
#define YASENGINEGL_HPP
#include<cstring>
#include<string>
#include<iostream>
#include<fstream>
#include<Windows.h>
#include<gl/gl.h>
#include<glext.h>
#include<wglext.h>
#include"TimePicker.hpp"

//-----------------------------------------------------------------------------|---------------------------------------|
//                                                                            80                                     120

class YasEngineGL
{
    public:
        YasEngineGL(HINSTANCE hInstance);

        void render();
        void swapBuffers();
        void prepareWindow(int nCmdShow);
        void run(int nCmdShow);
        void destroy();
        GLuint createShaderProgram();
        void initShaders();
        void clear();
        std::string loadShaderCode(std::string fileName);

    private:
        //WinAPI

        static LRESULT CALLBACK windowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
        ATOM registerWindowClass(HINSTANCE hInstance);
        
        HINSTANCE applicationHandle;
        HWND windowHandle;
        LPTSTR windowClassName;
        DWORD style;
        HDC	deviceContext;
        HGLRC renderingContext;

        
        //OpenGL
        void extractFunctionsPointers();
        void printShaderLog(GLuint shader);
        void printProgramLog(int prog);
        bool checkOpenGLError();
        
        // GLuint - shorthand for “unsigned int”, provided by OpenGL.
        GLuint shaderProgram;
        GLuint vertexArrayObjectIds[1];

        static std::string engineName;
        static std::string applicationName;
        static std::string shadersPath;

        int windowXposition;
        int windowYposition;
        int windowWidth;
        int windowHeight;

		bool windowed;

        // OpenGL and extension function pointers:

        // For working with shaders
        PFNGLCREATESHADERPROC glCreateShader;
        PFNGLCREATEPROGRAMPROC glCreateProgram;
        PFNGLSHADERSOURCEPROC glShaderSource;
        PFNGLCOMPILESHADERPROC glCompileShader;
        PFNGLATTACHSHADERPROC glAttachShader;
        PFNGLLINKPROGRAMPROC glLinkProgram;
        PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
        PFNGLBINDVERTEXARRAYPROC glBindVertexArray;

        // For error checking and logging
        PFNGLGETSHADERIVPROC glGetShaderiv;
        PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
        PFNGLGETPROGRAMIVPROC glGetProgramiv;
        PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;

        // For rendering
        PFNGLUSEPROGRAMPROC glUseProgram;
};

#endif

//                                                                            80                                     120
//-----------------------------------------------------------------------------|---------------------------------------|
