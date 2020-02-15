#include"YasEngineGL.hpp"

//-----------------------------------------------------------------------------|---------------------------------------|
//                                                                            80                                     120

LRESULT CALLBACK windowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
        case WM_CREATE:
        
        {
            PIXELFORMATDESCRIPTOR pfd =
            {
                sizeof(PIXELFORMATDESCRIPTOR),
                1,
                PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
                PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
                32,                   // Colordepth of the framebuffer.
                0, 0, 0, 0, 0, 0,
                0,
                0,
                0,
                0, 0, 0, 0,
                24,                   // Number of bits for the depthbuffer
                8,                    // Number of bits for the stencilbuffer
                0,                    // Number of Aux buffers in the framebuffer.
                PFD_MAIN_PLANE,
                0,
                0, 0, 0
            };

        
            HDC ourWindowHandleToDeviceContext = GetDC(hWnd);

            int  letWindowsChooseThisPixelFormat;
            letWindowsChooseThisPixelFormat = ChoosePixelFormat(ourWindowHandleToDeviceContext, &pfd); 
            SetPixelFormat(ourWindowHandleToDeviceContext,letWindowsChooseThisPixelFormat, &pfd);

            HGLRC ourOpenGLRenderingContext = wglCreateContext(ourWindowHandleToDeviceContext);
            wglMakeCurrent (ourWindowHandleToDeviceContext, ourOpenGLRenderingContext);

            //std::cout << glGetString(GL_VERSION) << std::endl;

            //MessageBoxA(0,(char*)glGetString(GL_VERSION), "OPENGL VERSION",0);

            wglDeleteContext(ourOpenGLRenderingContext);
            //PostQuitMessage(0);
        }
        break;

		case WM_DISPLAYCHANGE:
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			return(0);
            break;
        case WM_KEYDOWN:
        {
            // TODO
        }
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

const char* YasEngineGL::engineName = "YasEngine";
const char* YasEngineGL::applicationName = "YasEngine Demo Application";

YasEngineGL::YasEngineGL(HINSTANCE hInstance)
{
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

void YasEngineGL::prepareWindow()
{
    std::cout << "Preaparing window..." << std::endl;
    // Size of windowClassEx object
    windowClassEx.cbSize                        = sizeof(WNDCLASSEX);

    // Window style. Look and behavior
    windowClassEx.style                         = CS_VREDRAW | CS_HREDRAW;

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
    windowClassEx.lpszClassName                 = "YASEngineGL window class";

    // Handle to icon whitch will be show on windows bar.
    windowClassEx.hIconSm                       = LoadIcon(0, IDI_APPLICATION);

    // Function whtch create, set values and register window class in the system.
    RegisterClassEx(&windowClassEx);

    // Function tho create window with specyfied properties.
    windowHandle = CreateWindowEx(NULL, "YASEngineGL window class", "YASEngineGL", WS_OVERLAPPEDWINDOW|WS_VISIBLE, windowXposition,
                                  windowYposition, windowWidth, windowHeight, NULL, NULL, applicationHandle, NULL);
    
    // Set window's show state
	ShowWindow(windowHandle, SW_NORMAL);

    // Brings thread that created this window into the foreground and activates the window.
	SetForegroundWindow(windowHandle);

    // Set focus to specified window.
	SetFocus(windowHandle);
}

void YasEngineGL::run()
{
    prepareWindow();

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
