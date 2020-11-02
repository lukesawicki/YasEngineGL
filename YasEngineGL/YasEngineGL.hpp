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
#include"YasMathLib.hpp"

//-----------------------------------------------------------------------------|---------------------------------------|
//                                                                            80                                     120

class YasEngineGL
{
    public:
        YasEngineGL(HINSTANCE hInstance);
        void prepareWindow(int nCmdShow);
        void run(int nCmdShow);
        void destroy();

        void clear();
        void render(double deltaTime);
        void swapBuffers();

        void initShaders();
        std::string loadShaderCode(std::string fileName);
        GLuint createShaderProgram();
 
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
        PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
        PFNGLPROGRAMUNIFORM1FEXTPROC glProgramUniform1f;

        // NEW ONES
        ////////////////
        PFNGLGENBUFFERSPROC glGenBuffers;
        PFNGLBINDBUFFERPROC glBindBuffer;
        PFNGLBUFFERDATAPROC glBufferData;
        PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
        PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
        PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
        ////////////////
        // END NEW ONES

        // CUBE EXAMPLE START

        static const int NUMBER_OF_VERTEX_ARRAY_OBJECTS = 1;
        static const int NUMBER_OF_VERTEX_BUFFER_OBJECTS = 2;

        float cameraX;
        float cameraY;
        float cameraZ;

        float cubeLocationX;
        float cubeLocationY;
        float cubeLocationZ;

        float aspect;

        float rotationStep = 0.0F;
        float rotationStepAroundX = 0.0F;
        float rotationStepAroundY = 0.0F;
        float rotationStepAroundZ = 0.0F;

        float rotationSpeedFactor = 0.95F;

        float xStep = 0.0F;
        float yStep = 0.0F;
        float zStep = 0.0F;

        Matrix4GLF allRotationsMatrix;

        Matrix4GLF perspectiveMatrix;

        Matrix4GLF viewMatrix;

        Matrix4GLF modelMatrix;

        Matrix4GLF modelViewMatrix;

        Matrix4GLF modelTranslationMatrix;
        Matrix4GLF rotationModelMatrix;

        GLuint renderingProgram;

        GLuint vertexArrayObject[NUMBER_OF_VERTEX_ARRAY_OBJECTS];
        GLuint vertexBufferObject[NUMBER_OF_VERTEX_BUFFER_OBJECTS];

        GLuint modelViewLocation;
        GLuint projectionLocation;

        void setupVertices();
};

#endif

//                                                                            80                                     120
//-----------------------------------------------------------------------------|---------------------------------------|
