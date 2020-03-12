#include"YasEngineGL.hpp"

//-----------------------------------------------------------------------------|---------------------------------------|
//                                                                            80                                     120

std::string YasEngineGL::engineName = "YasEngine";
std::string YasEngineGL::applicationName = "YasEngine Demo Application";

LRESULT CALLBACK YasEngineGL::windowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
    windowWidth = 600; // 640;
	windowHeight = 600; // 360;
	
    windowXposition = 0;
	windowYposition = 0;

	windowed = true;
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

    //std::string YasEngineGL::engineName = "YasEngine";
    
    std::string consoleTitle = engineName + " logging window";

	SetConsoleTitle(consoleTitle.c_str());
    std::cout.clear();

    applicationHandle = hInstance;
}

GLuint YasEngineGL::createShaderProgram()
{
        PFNGLCREATESHADERPROC glCreateShader = (PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader");

        PFNGLCREATEPROGRAMPROC glCreateProgram = (PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram");

        PFNGLSHADERSOURCEPROC glShaderSource = (PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource");

        PFNGLCOMPILESHADERPROC glCompileShader = (PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");

        PFNGLATTACHSHADERPROC glAttachShader = (PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader");

        PFNGLLINKPROGRAMPROC glLinkProgram = (PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram");

    const char *vertexShaderSource =
		"#version 430    \n"
		"void main(void) \n"
		"{ gl_Position = vec4(0.0, 0.0, 0.0, 1.0); }";

	const char *fragmentShaderSource =
		"#version 430    \n"
		"out vec4 color; \n"
		"void main(void) \n"
		"{\n" 
            "if (gl_FragCoord.x < 300)\n"
            "{\n"
            "color = vec4(1.0, 0.0, 0.0, 1.0); \n"
            "}\n"
            "else\n"
            "{\n"
                "color = vec4(0.0, 0.0, 1.0, 1.0); \n"
            "}\n"
        "}\n";

///////////////////////////
//  	"#version 430    \n"
//    "out vec4 color; \n"
//    "void main(void) \n"
//    "{" 
//        "color = vec4(0.0, 0.0, 1.0, 1.0); "
//    "}";
///////////////////////////

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

    GLuint vertexAndFragmentShaderProgram = glCreateProgram();
		
	glAttachShader(vertexAndFragmentShaderProgram, vertexShader);
	glAttachShader(vertexAndFragmentShaderProgram, fragmentShader);
	glLinkProgram(vertexAndFragmentShaderProgram);

	return vertexAndFragmentShaderProgram;
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
    windowClassEx.lpszClassName                 = applicationName.c_str();

    // Handle to icon whitch will be show on windows bar.
    windowClassEx.hIconSm                       = LoadIcon(0, IDI_APPLICATION);

    // Function whtch create, set values and register window class in the system.
    return RegisterClassEx(&windowClassEx);
}

void YasEngineGL::prepareWindow(int nCmdShow)
{
    windowClassName = MAKEINTATOM(registerWindowClass(applicationHandle));

    // handle if window didn't created

    HWND fakeWindow = CreateWindow(
                    windowClassName, "Fake Window",
                    WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
                    0, 0,
                    1, 1,
                    NULL, NULL,
                    applicationHandle, NULL);
   
    HDC fakeDeviceContext = GetDC(fakeWindow);

    PIXELFORMATDESCRIPTOR fakePixelFormatDescriptor;

    ZeroMemory(&fakePixelFormatDescriptor, sizeof(fakePixelFormatDescriptor));
    fakePixelFormatDescriptor.nSize = sizeof(fakePixelFormatDescriptor);
    fakePixelFormatDescriptor.nVersion = 1;
    fakePixelFormatDescriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    fakePixelFormatDescriptor.iPixelType = PFD_TYPE_RGBA;
    fakePixelFormatDescriptor.cColorBits = 32;
    fakePixelFormatDescriptor.cAlphaBits = 8;
    fakePixelFormatDescriptor.cDepthBits = 24;
 
    int fakePixelFormatId = ChoosePixelFormat(fakeDeviceContext, &fakePixelFormatDescriptor);
    if(fakePixelFormatId == 0)
    {
        std::cout << "Choosing pixel format failed." << std::endl;
        exit(1);
    }

    if(SetPixelFormat(fakeDeviceContext, fakePixelFormatId, &fakePixelFormatDescriptor) == false)
    {
        std::cout << "Setting pixel format failed." << std::endl;
        exit(1);
    }

    HGLRC fakeRenderingContext = wglCreateContext(fakeDeviceContext);
 
    if (fakeRenderingContext == 0) {
        std::cout << "wglCreateContext() failed." << std::endl;
        exit(1);
    }
 
    if (wglMakeCurrent(fakeDeviceContext, fakeRenderingContext) == false) {
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

    windowHandle = CreateWindow(windowClassName, applicationName.c_str(), style, windowXposition, windowYposition,
                                windowWidth, windowHeight, NULL, NULL, applicationHandle, NULL);

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

	int pixelFormatID;
    UINT formatsNumber;
	const bool status = wglChoosePixelFormatARB(deviceContext, pixelAttribs, NULL, 1, &pixelFormatID, &formatsNumber);

	if (status == false || formatsNumber == 0) {
		std::cout << "wglChoosePixelFormatARB() failed." << std::endl;
		exit(1);
	}

	PIXELFORMATDESCRIPTOR pixelFormatDescriptor;
	DescribePixelFormat(deviceContext, pixelFormatID, sizeof(pixelFormatDescriptor), &pixelFormatDescriptor);
	SetPixelFormat(deviceContext, pixelFormatID, &pixelFormatDescriptor);

	const int major_min = 4, minor_min = 3; // minor_min changed from 0 to 3
	const int contextAttribs[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, major_min,
		WGL_CONTEXT_MINOR_VERSION_ARB, minor_min,
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
    	//WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_DEBUG_BIT_ARB,
		0
	};

	renderingContext = wglCreateContextAttribsARB(deviceContext, 0, contextAttribs);
	if (renderingContext == NULL) {
		std::cout << "wglCreateContextAttribsARB() failed." << std::endl;
		exit(1);
	}

	// Delete temporary context and window

	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(fakeRenderingContext);
	ReleaseDC(fakeWindow, fakeDeviceContext);
	DestroyWindow(fakeWindow);
	if (!wglMakeCurrent(deviceContext, renderingContext)) {
		std::cout << "wglMakeCurrent() failed." << std::endl;
		exit(1);
	}

	SetWindowText(windowHandle, reinterpret_cast<LPCSTR>(glGetString(GL_VERSION)));
	ShowWindow(windowHandle, nCmdShow);

    // Brings thread that created this window into the foreground and activates the window.
	SetForegroundWindow(windowHandle);

    // Set focus to specified window.
	SetFocus(windowHandle);

}

void YasEngineGL::printShaderLog(GLuint shader)
{
    //EXAMPLE | PFNGLGENVERTEXARRAYSPROC glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)wglGetProcAddress("glGenVertexArrays"); |
    int len = 0;
	int chWrittn = 0;
	char *log;
    //typedef void (APIENTRYP PFNGLGETSHADERIVPROC) (GLuint shader, GLenum pname, GLint *params);
    PFNGLGETSHADERIVPROC glGetShaderiv = (PFNGLGETSHADERIVPROC)wglGetProcAddress("glGetShaderiv");
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
	if (len > 0) {
		log = (char *)malloc(len);
        PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)wglGetProcAddress("glGetShaderInfoLog");
        //typedef void (APIENTRYP PFNGLGETSHADERINFOLOGPROC) (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
		glGetShaderInfoLog(shader, len, &chWrittn, log);
		std::cout << "Shader Info Log: " << log << std::endl;
		free(log);
	}
}

void YasEngineGL::printProgramLog(int prog)
{
    int len = 0;
	int chWrittn = 0;
	char *log;
    //typedef void (APIENTRYP PFNGLGETPROGRAMIVPROC) (GLuint program, GLenum pname, GLint *params);
    PFNGLGETPROGRAMIVPROC glGetProgramiv = (PFNGLGETPROGRAMIVPROC)wglGetProcAddress("glGetProgramiv");
	glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
	if (len > 0) {
		log = (char *)malloc(len);
        //typedef void (APIENTRYP PFNGLGETPROGRAMINFOLOGPROC) (GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
        PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)wglGetProcAddress("glGetProgramInfoLog");
		glGetProgramInfoLog(prog, len, &chWrittn, log);
		std::cout << "Program Info Log: " << log << std::endl;
		free(log);
	}
}

bool YasEngineGL::checkOpenGLError()
{
    bool foundError = false;
	int glErr = glGetError();
	while (glErr != GL_NO_ERROR) {
		std::cout << "glError: " << glErr << std::endl;
		foundError = true;
		glErr = glGetError();
	}
	return foundError;
}

void YasEngineGL::initShaders() {
    shaderProgram = createShaderProgram();

    //typedef void (APIENTRYP PFNGLGENVERTEXARRAYSPROC) (GLsizei n, GLuint *arrays);
    PFNGLGENVERTEXARRAYSPROC glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)wglGetProcAddress("glGenVertexArrays");
    
    //typedef void (APIENTRYP PFNGLBINDVERTEXARRAYPROC) (GLuint array); 
    PFNGLBINDVERTEXARRAYPROC glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)wglGetProcAddress("glBindVertexArray");

    glGenVertexArrays(1, vertexArrayObjectIds);
	glBindVertexArray(vertexArrayObjectIds[0]);
}

void YasEngineGL::clear()
{    
    glClearColor(1.0F, 0.0F, 0.0F, 1.0F);
	glClear(GL_COLOR_BUFFER_BIT);
}

void YasEngineGL::render()
{
    PFNGLUSEPROGRAMPROC glUseProgram = (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram");

    glUseProgram(shaderProgram);
	glPointSize(80.0f);
	glDrawArrays(GL_POINTS, 0, 1);
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
    initShaders();

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
            //clear();
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
    destroy();
}

//                                                                            80                                     120
//-----------------------------------------------------------------------------|---------------------------------------|
