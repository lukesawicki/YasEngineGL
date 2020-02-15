#ifndef YASENGINEGL_HPP
#define YASENGINEGL_HPP
#include<Windows.h>
#include <GL/GL.h>
#include<fstream>
#include<iostream>
#include"TimePicker.hpp"

//-----------------------------------------------------------------------------|---------------------------------------|
//                                                                            80                                     120

LRESULT CALLBACK windowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

class YasEngineGL
{
    public:
        YasEngineGL(HINSTANCE hInstance);
        void prepareWindow();
        void run();
    
    private:
        static const char* engineName;
        static const char* applicationName;

        // Windows API
        int windowXposition                 = 10;//TODO take system width
        int windowYposition                 = 10;//TODO teke system height
        int windowWidth                     = 1280;
        int windowHeight                    = 720;
        WNDCLASSEX windowClassEx;
        HWND windowHandle;
        HINSTANCE applicationHandle;

};

#endif

//                                                                            80                                     120
//-----------------------------------------------------------------------------|---------------------------------------|
