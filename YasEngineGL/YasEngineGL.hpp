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
#include"YasMathsLib.hpp"

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
        void render(float deltaTime, float &x);
        void swapBuffers();

        void initShaders();
        std::string loadShaderCode(std::string fileName);
        GLuint createShaderProgram();
        float stepFactor = 0.1F;

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

        GLuint offsetLoc;

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

        //int width;
        //int height;
        float aspect;

        Matrix4GLF perspectiveMatrix;
        //glm::mat4 perspectiveMatrix;
        //glm::mat4 viewMatrix;
        Matrix4GLF viewMatrix;
        //glm::mat4 modelMatrix;
        Matrix4GLF modelMatrix;
        //glm::mat4 modelViewMatrix;
        Matrix4GLF modelViewMatrix;

        Matrix4GLF modelTranslationMatrix;
        Matrix4GLF modelRotationMatrix;

        const float SPEED = 1.75;

        GLuint renderingProgram;

        GLuint vertexArrayObject[NUMBER_OF_VERTEX_ARRAY_OBJECTS];
        GLuint vertexBufferObject[NUMBER_OF_VERTEX_BUFFER_OBJECTS];

        GLuint modelViewLocation;
        GLuint projectionLocation;

        void setupVertices();

        // CUBE EXAMPLE DATA END

        // Gameplay
        float pointSizeChangingFactor = 1;
};

#endif

//                                                                            80                                     120
//-----------------------------------------------------------------------------|---------------------------------------|
