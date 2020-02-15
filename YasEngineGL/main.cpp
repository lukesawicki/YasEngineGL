//#include <Windows.h>
//#include <GL/GL.h>
//
//#pragma comment (lib, "opengl32.lib")
//
//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
//
//int WinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in_opt LPSTR lpCmdLine, __in int nShowCmd )
//{
//	MSG msg          = {0};
//	WNDCLASS wc      = {0}; 
//	wc.lpfnWndProc   = WndProc;
//	wc.hInstance     = hInstance;
//	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
//	wc.lpszClassName = "SAMPLE";
//	wc.style = CS_OWNDC;
//	if( !RegisterClass(&wc) )
//		return 1;
//	CreateWindowEx(NULL,"SAMPLE", "YASENGINE", WS_OVERLAPPEDWINDOW|WS_VISIBLE,0,0,640,480,0,0,hInstance,0);
//
//	while( GetMessage( &msg, NULL, 0, 0 ) > 0 )
//		DispatchMessage( &msg );
//
//	return 0;
//}
//
//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	switch(message)
//	{
//	case WM_CREATE:
//		{
//		PIXELFORMATDESCRIPTOR pfd =
//		{
//			sizeof(PIXELFORMATDESCRIPTOR),
//			1,
//			PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
//			PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
//			32,                   // Colordepth of the framebuffer.
//			0, 0, 0, 0, 0, 0,
//			0,
//			0,
//			0,
//			0, 0, 0, 0,
//			24,                   // Number of bits for the depthbuffer
//			8,                    // Number of bits for the stencilbuffer
//			0,                    // Number of Aux buffers in the framebuffer.
//			PFD_MAIN_PLANE,
//			0,
//			0, 0, 0
//		};
//
//		HDC ourWindowHandleToDeviceContext = GetDC(hWnd);
//
//		int  letWindowsChooseThisPixelFormat;
//		letWindowsChooseThisPixelFormat = ChoosePixelFormat(ourWindowHandleToDeviceContext, &pfd); 
//		SetPixelFormat(ourWindowHandleToDeviceContext,letWindowsChooseThisPixelFormat, &pfd);
//
//		HGLRC ourOpenGLRenderingContext = wglCreateContext(ourWindowHandleToDeviceContext);
//		wglMakeCurrent (ourWindowHandleToDeviceContext, ourOpenGLRenderingContext);
//
//		MessageBoxA(0,(char*)glGetString(GL_VERSION), "OPENGL VERSION",0);
//
//		wglDeleteContext(ourOpenGLRenderingContext);
//		PostQuitMessage(0);
//		}
//		break;
//	default:
//		return DefWindowProc(hWnd, message, wParam, lParam);
//	}
//	return 0;
//
//}


#include"main.hpp"

//-----------------------------------------------------------------------------|---------------------------------------|
//    

// Main function off windows application. Return int. 0 - there were not errors. !=0 there were errors.
// hInstance handle to this application. hPrevInstance - not using (deprecated)
// lpCmdLine pointer to char table- string with witch applications are call.
// nShowCmd - variable which tell how to show window.
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	YasEngineGL yasEngineGl = YasEngineGL(hInstance);
	yasEngineGl.run();
	system("PAUSE");
	return 0;
}



//#include<Windows.h>
//#include<GL/GL.h>
//
//#pragma comment (lib, "opengl32.lib")
//
//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
//
//int WinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in_opt LPSTR lpCmdLine, __in int nShowCmd )
//{
//	MSG msg          = {0};
//	WNDCLASS wc      = {0}; 
//	wc.lpfnWndProc   = WndProc;
//	wc.hInstance     = hInstance;
//	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
//	wc.lpszClassName = L"oglversionchecksample";
//	wc.style = CS_OWNDC;
//	if( !RegisterClass(&wc) )
//		return 1;
//	CreateWindowW(wc.lpszClassName,L"openglversioncheck",WS_OVERLAPPEDWINDOW|WS_VISIBLE,0,0,640,480,0,0,hInstance,0);
//
//	while( GetMessage( &msg, NULL, 0, 0 ) > 0 )
//		DispatchMessage( &msg );
//
//	return 0;
//}
//
//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	switch(message)
//	{
//	case WM_CREATE:
//		{
//		PIXELFORMATDESCRIPTOR pfd =
//		{
//			sizeof(PIXELFORMATDESCRIPTOR),
//			1,
//			PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
//			PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
//			32,                   // Colordepth of the framebuffer.
//			0, 0, 0, 0, 0, 0,
//			0,
//			0,
//			0,
//			0, 0, 0, 0,
//			24,                   // Number of bits for the depthbuffer
//			8,                    // Number of bits for the stencilbuffer
//			0,                    // Number of Aux buffers in the framebuffer.
//			PFD_MAIN_PLANE,
//			0,
//			0, 0, 0
//		};
//
//		HDC ourWindowHandleToDeviceContext = GetDC(hWnd);
//
//		int  letWindowsChooseThisPixelFormat;
//		letWindowsChooseThisPixelFormat = ChoosePixelFormat(ourWindowHandleToDeviceContext, &pfd); 
//		SetPixelFormat(ourWindowHandleToDeviceContext,letWindowsChooseThisPixelFormat, &pfd);
//
//		HGLRC ourOpenGLRenderingContext = wglCreateContext(ourWindowHandleToDeviceContext);
//		wglMakeCurrent (ourWindowHandleToDeviceContext, ourOpenGLRenderingContext);
//
//		MessageBoxA(0,(char*)glGetString(GL_VERSION), "OPENGL VERSION",0);
//
//		wglDeleteContext(ourOpenGLRenderingContext);
//		PostQuitMessage(0);
//		}
//		break;
//	default:
//		return DefWindowProc(hWnd, message, wParam, lParam);
//	}
//	return 0;
//
//}

//
//
//
//
//
////#include<GL\glew.h>
////#include<GLFW\glfw3.h>
////#include<iostream>
////
////using namespace std;
////
////void init(GLFWwindow* window)
////{
////}
////
////void display(GLFWwindow* window, double currentTime)
////{
////    glClearColor(1.0, 0.0, 0.0, 1.0);
////    glClear(GL_COLOR_BUFFER_BIT);
////}
////
////int main () //int argc, char *argv[])
////{
////    if(!glfwInit())
////    {
////        exit(EXIT_FAILURE);
////    }
////    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
////    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
////
////    GLFWwindow* window = glfwCreateWindow(600, 600, "YasEngineGL", NULL, NULL);
////    glfwMakeContextCurrent(window);
////    if(glewInit()!=GLEW_OK)
////    {
////        exit(EXIT_FAILURE);
////    }
////    glfwSwapInterval(1);
////
////    init(window);
////
////    while(!glfwWindowShouldClose(window))
////    {
////        display(window, glfwGetTime());
////        glfwSwapBuffers(window);
////        glfwPollEvents();
////    }
////
////    glfwDestroyWindow(window);
////    glfwTerminate();
////    exit(EXIT_SUCCESS);
////
////    return 0;
////}
//
///*
//#ifndef MAIN_HPP
//#define MAIN_HPP
//#include"stdafx.hpp"
//#include"YasEngine.hpp"
//
////-----------------------------------------------------------------------------|---------------------------------------|
////                                                                            80                                     120
//
//;
//
////                                                                            80                                     120
////-----------------------------------------------------------------------------|---------------------------------------|
//
//#endif
//*/
