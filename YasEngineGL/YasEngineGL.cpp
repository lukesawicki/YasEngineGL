#include"YasEngineGL.hpp"

//-----------------------------------------------------------------------------|---------------------------------------|
//                                                                            80                                     120

const char* YasEngineGL::engineName = "YasEngine";
const char* YasEngineGL::applicationName = "YasEngine Demo Application";

LRESULT CALLBACK windowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
		switch (message) {
		case WM_KEYDOWN:
			if (wParam == VK_ESCAPE) {
				PostQuitMessage(0);
			}
			break;
		case WM_CLOSE:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

YasEngineGL::YasEngineGL(HINSTANCE hInstance)
{
    config.width = 1024;
	config.height = 720;
	config.posX = CW_USEDEFAULT;
	config.posY = 0;
	config.windowed = true;
	style = WS_CAPTION | WS_SYSMENU | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
        // Allocates a new console for the calling process.
	AllocConsole();
    // Attaches the calling process to the console of the specified process.
	AttachConsole(GetCurrentProcessId());
    // Stream object
	FILE* file;
    // fropen_s open existing file with another name
	freopen_s(&file, "CON", "w", stdout);
	freopen_s(&file, "CON", "w", stderr);
	SetConsoleTitle("YasEngine logging");
    std::cout.clear();

    applicationHandle = hInstance;
}

///////////////////////////////////////////////////////////
// Adjust window's size for non-client area elements
// like border and title bar

void YasEngineGL::adjustSize() {

	RECT rect = { 0, 0, config.width, config.height };
	AdjustWindowRect(&rect, style, false);
	config.width = rect.right - rect.left;
	config.height = rect.bottom - rect.top;
}

///////////////////////////////////////////////////////////

void YasEngineGL::center() {

	RECT primaryDisplaySize;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &primaryDisplaySize, 0);	// system taskbar and application desktop toolbars not included
	config.posX = (primaryDisplaySize.right - config.width) / 2;
	config.posY = (primaryDisplaySize.bottom - config.height) / 2;
}

ATOM YasEngineGL::registerWindowClass(HINSTANCE hInstance)
{
    WNDCLASSEX windowClassEx;
    ZeroMemory(&windowClassEx, sizeof(windowClassEx));
    std::cout << "Preaparing windowClassEx for window" << std::endl;
    // Size of windowClassEx object
    windowClassEx.cbSize                        = sizeof(WNDCLASSEX);

    // Window style. Look and behavior
    windowClassEx.style                         = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;

    // Pointer to window procedure
    windowClassEx.lpfnWndProc                   = windowProcedure;

    // Size of extra memory for the application
    windowClassEx.cbClsExtra                    = 0;

    // Size of extra memory for window created using this window class
    windowClassEx.cbWndExtra                    = 0;

    // handle to application
    windowClassEx.hInstance                     = applicationHandle;

    // Appliction icon in the alt + tab dialog
    windowClassEx.hIcon                         = LoadIcon(0, IDI_APPLICATION);

    // Handle to cursor displayed when cursor is over the window
    windowClassEx.hCursor                       = LoadCursor(0, IDC_CROSS);

    // Handle to brush for redrawing window
    windowClassEx.hbrBackground                 = (HBRUSH)GetStockObject(WHITE_BRUSH);

    // Handle to menu which will be attached to this window
    windowClassEx.lpszMenuName                  = 0;

    // Name of window
    windowClassEx.lpszClassName                 = "YASEngineGLwindowClass";

    // Handle to icon whitch will be show on windows bar.
    windowClassEx.hIconSm                       = LoadIcon(0, IDI_APPLICATION);

    // Function whtch create, set values and register window class in the system.
    return RegisterClassEx(&windowClassEx);
}

void YasEngineGL::prepareWindow(int nCmdShow)
{
    windowClassName = MAKEINTATOM(registerWindowClass(applicationHandle));

    HWND fakeWindow = CreateWindow(
                    windowClassName, "Fake Window",
                    WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
                    0, 0,
                    1, 1,
                    NULL, NULL,
                    applicationHandle, NULL);
   
    HDC fakeDC = GetDC(fakeWindow);

    PIXELFORMATDESCRIPTOR fakePFD;

    ZeroMemory(&fakePFD, sizeof(fakePFD));
    fakePFD.nSize = sizeof(fakePFD);
    fakePFD.nVersion = 1;
    fakePFD.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    fakePFD.iPixelType = PFD_TYPE_RGBA;
    fakePFD.cColorBits = 32;
    fakePFD.cAlphaBits = 8;
    fakePFD.cDepthBits = 24;
 
    int fakePFDID = ChoosePixelFormat(fakeDC, &fakePFD);
    if(fakePFDID == 0)
    {
        std::cout << "Choosing pixel format failed." << std::endl;
        exit(1);
    }

    if(SetPixelFormat(fakeDC, fakePFDID, &fakePFD) == false)
    {
        std::cout << "Setting pixel format failed." << std::endl;
        exit(1);
    }

    HGLRC fakeRC = wglCreateContext(fakeDC);    // Rendering Contex
 
    if (fakeRC == 0) {
        std::cout << "wglCreateContext() failed." << std::endl;
        exit(1);
    }
 
    if (wglMakeCurrent(fakeDC, fakeRC) == false) {
        std::cout << "wglMakeCurrent() failed." << std::endl;
        exit(1);
    }

    PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = nullptr;
    wglChoosePixelFormatARB = reinterpret_cast<PFNWGLCHOOSEPIXELFORMATARBPROC>(wglGetProcAddress("wglChoosePixelFormatARB"));
    if (wglChoosePixelFormatARB == nullptr) {
        std::cout << "wglGetProcAddress() failed." << std::endl;
        exit(1);
    }
 
    PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = nullptr;
    wglCreateContextAttribsARB = reinterpret_cast<PFNWGLCREATECONTEXTATTRIBSARBPROC>(wglGetProcAddress("wglCreateContextAttribsARB"));
    if (wglCreateContextAttribsARB == nullptr) {
        std::cout << "wglGetProcAddress() failed." << std::endl;
        exit(1);
    }
//-----------------------------------------------------------------------------|---------------------------------------|

    // Function tho create window with specyfied properties.
//windowHandle = CreateWindowEx(NULL, "YASEngineGL window class", "YASEngineGL", WS_OVERLAPPEDWINDOW|WS_VISIBLE, windowXposition,
                                  //windowYposition, windowWidth, windowHeight, NULL, NULL, applicationHandle, NULL);

	//WND = CreateWindow(
	//	windowClass, "OpenGL Window",	// class name, window name
	//	style,							// styles
	//	config.posX, config.posY,		// posx, posy. If x is set to CW_USEDEFAULT y is ignored
	//	config.width, config.height,	// width, height
	//	NULL, NULL,						// parent window, menu
	//	hInstance, NULL);				// instance, param
    
    windowHandle = CreateWindow(windowClassName, "YasEngineGL", style, config.posX, config.posY, config.width, config.height, NULL, NULL, applicationHandle, NULL);

    deviceContext = GetDC(windowHandle);

	const int pixelAttribs[] = {
		WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
		WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
		WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
		WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
		WGL_COLOR_BITS_ARB, 32,
		WGL_ALPHA_BITS_ARB, 8,
		WGL_DEPTH_BITS_ARB, 24,
		WGL_STENCIL_BITS_ARB, 8,
		WGL_SAMPLE_BUFFERS_ARB, GL_TRUE,
		WGL_SAMPLES_ARB, 4,
		0
	};

	int pixelFormatID; UINT numFormats;
	const bool status = wglChoosePixelFormatARB(deviceContext, pixelAttribs, NULL, 1, &pixelFormatID, &numFormats);

	if (status == false || numFormats == 0) {
		std::cout << "wglChoosePixelFormatARB() failed." << std::endl;
		exit(1);
	}

	PIXELFORMATDESCRIPTOR pixelFormatDescriptor;
	DescribePixelFormat(deviceContext, pixelFormatID, sizeof(pixelFormatDescriptor), &pixelFormatDescriptor);
	SetPixelFormat(deviceContext, pixelFormatID, &pixelFormatDescriptor);

	const int major_min = 4, minor_min = 0;
	const int contextAttribs[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, major_min,
		WGL_CONTEXT_MINOR_VERSION_ARB, minor_min,
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
//		WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_DEBUG_BIT_ARB,
		0
	};

	renderingContext = wglCreateContextAttribsARB(deviceContext, 0, contextAttribs);
	if (renderingContext == NULL) {
		std::cout << "wglCreateContextAttribsARB() failed." << std::endl;
		exit(1);
	}

	// delete temporary context and window

	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(fakeRC);
	ReleaseDC(fakeWindow, fakeDC);
	DestroyWindow(fakeWindow);
	if (!wglMakeCurrent(deviceContext, renderingContext)) {
		std::cout << "wglMakeCurrent() failed." << std::endl;
		exit(1);
	}

	// init opengl loader here (extra safe version)

	SetWindowText(windowHandle, reinterpret_cast<LPCSTR>(glGetString(GL_VERSION)));
	ShowWindow(windowHandle, nCmdShow);

 //   // Set window's show state
	//ShowWindow(windowHandle, SW_NORMAL);

 //   // Brings thread that created this window into the foreground and activates the window.
	//SetForegroundWindow(windowHandle);

 //   // Set focus to specified window.
	//SetFocus(windowHandle);
}

void YasEngineGL::render()
{
	glClearColor(0.129f, 0.586f, 0.949f, 1.0f);	// rgb(33,150,243)
	glClear(GL_COLOR_BUFFER_BIT);
}

void YasEngineGL::swapBuffers()
{

	SwapBuffers(deviceContext);
}

void YasEngineGL::destroy() {

	wglMakeCurrent(NULL, NULL);
	if (renderingContext) {
		wglDeleteContext(renderingContext);
	}
	if (deviceContext) {
		ReleaseDC(windowHandle, deviceContext);
	}
	if (windowHandle) {
		DestroyWindow(windowHandle);
	}
}

void YasEngineGL::run(int nCmdShow)
{

    prepareWindow(nCmdShow);

    std::cout << "Windows and OpenGL context Prepared... starting rendering" << std::endl;

    float time;
    float newTime;
    float deltaTime;
    float fps;
    float fpsTime;
    unsigned int frames;
    MSG message;

    TimePicker timePicker = TimePicker();
    time = timePicker.getSeconds();
    fpsTime = 0.0F;
    frames = 0;
    message.message = WM_NULL;

    while(message.message != WM_QUIT)
    {
        if(PeekMessage(&message, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
        else
        {
            newTime = timePicker.getSeconds();
            deltaTime = newTime - time;
            time = newTime;
            // TODO drawFrame(deltaTime);   
            render();
		    swapBuffers();
            frames++;
            fpsTime = fpsTime + deltaTime;
            if(fpsTime >= 1.0F)
            {
                fps = frames / fpsTime;
                frames = 0;
                fpsTime = 0.0F;
            }
        }
    }

}

//                                                                            80                                     120
//-----------------------------------------------------------------------------|---------------------------------------|
