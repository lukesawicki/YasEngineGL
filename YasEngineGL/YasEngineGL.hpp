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

LRESULT CALLBACK windowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

class YasEngineGL
{
    public:
        YasEngineGL(HINSTANCE hInstance);
        ATOM registerWindowClass(HINSTANCE hInstance);
        
        DWORD style;

        struct Config {
		    int width;
		    int	height;
		    int posX;
		    int posY;
		    bool windowed;
	    } config;

        void adjustSize();
	    void center();
        void render();
        void swapBuffers();
        void prepareWindow(int nCmdShow);
        void run(int nCmdShow);
        void destroy();
    
    private:
        static const char* engineName;
        static const char* applicationName;

        // Windows API
        int windowXposition                 = 10;//TODO take system width
        int windowYposition                 = 10;//TODO teke system height
        int windowWidth                     = 640;
        int windowHeight                    = 360;

        //WNDCLASSEX windowClassEx;
        HWND windowHandle;
        HINSTANCE applicationHandle;
        LPTSTR windowClassName; // Name
        HDC	deviceContext;
        HGLRC renderingContext;			// Rendering Context
};

#endif

//                                                                            80                                     120
//-----------------------------------------------------------------------------|---------------------------------------|
