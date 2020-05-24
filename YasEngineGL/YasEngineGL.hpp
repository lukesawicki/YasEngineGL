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



        ///////////////////////////
        //typedef void (APIENTRYP PFNGLUNIFORMMATRIX4FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
        //GLEW_FUN_EXPORT PFNGLUNIFORMMATRIX4FVPROC __glewUniformMatrix4fv;

        //glUniformMatrix4fv
        //typedef void (APIENTRYP PFNGLUNIFORMMATRIX4FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
        ///////////////////////////



        //glUniformMatrix4fv(modelViewLocation, 1, GL_FALSE, glm::value_ptr(modelViewMatrix));
    
    
        // GLM FUNCTION
        //glUniformMatrix4fv(modelViewLocation, 1, GL_FALSE, &modelViewMatrix);




        // Gameplay
        float pointSizeChangingFactor = 1;
};

#endif

//                                                                            80                                     120
//-----------------------------------------------------------------------------|---------------------------------------|
