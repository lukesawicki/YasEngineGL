#ifndef YASENGINEGL_HPP
#define YASENGINEGL_HPP
#include<fstream>
#include<iostream>
#include<Windows.h>
#include <gl/gl.h>
#include <glext.h>
#include <wglext.h>
#include"TimePicker.hpp"

//-----------------------------------------------------------------------------|---------------------------------------|
//                                                                            80                                     120

class YasEngineGL
{
    public:
        YasEngineGL(HINSTANCE hInstance);
        ATOM registerWindowClass(HINSTANCE hInstance);
        static LRESULT CALLBACK windowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
        DWORD style;
        GLuint shaderPoint;

        //#define numVAOs 1

        GLuint renderingProgram;
        GLuint vao[1];

        void render();
        void swapBuffers();
        void prepareWindow(int nCmdShow);
        void run(int nCmdShow);
        void destroy();
        GLuint createShaderForPoint();
        void *GetAnyGLFuncAddress(const char *name);

//typedef GLuint (APIENTRYP PFNGLCREATESHADERPROC) (GLenum type);
//typedef void (APIENTRYP PFNGLCOMPILESHADERPROC) (GLuint shader);
//typedef GLuint (APIENTRYP PFNGLCREATEPROGRAMPROC) (void);
//typedef GLuint (APIENTRYP PFNGLCREATESHADERPROC) (GLenum type);
//typedef void (APIENTRYP PFNGLDELETEPROGRAMPROC) (GLuint program);
//typedef void (APIENTRYP PFNGLDELETESHADERPROC) (GLuint shader);
//typedef void (APIENTRYP PFNGLDETACHSHADERPROC) (GLuint program, GLuint shader);




    private:
        static const char* engineName;
        static const char* applicationName;

        int windowXposition;
        int windowYposition;
        int windowWidth;
        int windowHeight;

		bool windowed;

        HWND windowHandle;
        HINSTANCE applicationHandle;
        LPTSTR windowClassName;
        HDC	deviceContext;
        HGLRC renderingContext;
};

#endif

//                                                                            80                                     120
//-----------------------------------------------------------------------------|---------------------------------------|
