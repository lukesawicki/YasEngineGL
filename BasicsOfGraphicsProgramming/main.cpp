#include<cstdlib>
#include<iostream>
#include<vector>
#include<cmath>
#include<SDL.h>
#include"Mathematics.hpp"
#include"TimePicker.hpp"

#include "geometry.h"

//[comment]
// List of vertices making up the object
//[/comment]
const Vect3f verts[146] = {
    {        0,    39.034,         0}, {  0.76212,    36.843,         0},
    {        3,    36.604,         0}, {        1,    35.604,         0},
    {   2.0162,    33.382,         0}, {        0,    34.541,         0},
    {  -2.0162,    33.382,         0}, {       -1,    35.604,         0},
    {       -3,    36.604,         0}, { -0.76212,    36.843,         0},
    {-0.040181,     34.31,         0}, {   3.2778,    30.464,         0},
    {-0.040181,    30.464,         0}, {-0.028749,    30.464,         0},
    {   3.2778,    30.464,         0}, {   1.2722,    29.197,         0},
    {   1.2722,    29.197,         0}, {-0.028703,    29.197,         0},
    {   1.2722,    29.197,         0}, {   5.2778,    25.398,         0},
    { -0.02865,    25.398,         0}, {   1.2722,    29.197,         0},
    {   5.2778,    25.398,         0}, {   3.3322,    24.099,         0},
    {-0.028683,    24.099,         0}, {   7.1957,    20.299,         0},
    { -0.02861,    20.299,         0}, {   5.2778,    19.065,         0},
    {-0.028663,    18.984,         0}, {   9.2778,    15.265,         0},
    {-0.028571,    15.185,         0}, {   9.2778,    15.265,         0},
    {   7.3772,    13.999,         0}, {-0.028625,    13.901,         0},
    {   9.2778,    15.265,         0}, {   12.278,    8.9323,         0},
    {-0.028771,    8.9742,         0}, {   12.278,    8.9323,         0},
    {   10.278,    7.6657,         0}, {-0.028592,    7.6552,         0},
    {   15.278,    2.5994,         0}, {-0.028775,    2.6077,         0},
    {   15.278,    2.5994,         0}, {   13.278,    1.3329,         0},
    {-0.028727,    1.2617,         0}, {   18.278,   -3.7334,         0},
    {   18.278,   -3.7334,         0}, {   2.2722,   -1.2003,         0},
    {-0.028727,   -1.3098,         0}, {   4.2722,        -5,         0},
    {   4.2722,        -5,         0}, {-0.028727,        -5,         0},
    {  -3.3582,    30.464,         0}, {  -3.3582,    30.464,         0},
    {  -1.3526,    29.197,         0}, {  -1.3526,    29.197,         0},
    {  -1.3526,    29.197,         0}, {  -5.3582,    25.398,         0},
    {  -1.3526,    29.197,         0}, {  -5.3582,    25.398,         0},
    {  -3.4126,    24.099,         0}, {   -7.276,    20.299,         0},
    {  -5.3582,    19.065,         0}, {  -9.3582,    15.265,         0},
    {  -9.3582,    15.265,         0}, {  -7.4575,    13.999,         0},
    {  -9.3582,    15.265,         0}, {  -12.358,    8.9323,         0},
    {  -12.358,    8.9323,         0}, {  -10.358,    7.6657,         0},
    {  -15.358,    2.5994,         0}, {  -15.358,    2.5994,         0},
    {  -13.358,    1.3329,         0}, {  -18.358,   -3.7334,         0},
    {  -18.358,   -3.7334,         0}, {  -2.3526,   -1.2003,         0},
    {  -4.3526,        -5,         0}, {  -4.3526,        -5,         0},
    {        0,     34.31,  0.040181}, {        0,    30.464,   -3.2778},
    {        0,    30.464,  0.040181}, {        0,    30.464,  0.028749},
    {        0,    30.464,   -3.2778}, {        0,    29.197,   -1.2722},
    {        0,    29.197,   -1.2722}, {        0,    29.197,  0.028703},
    {        0,    29.197,   -1.2722}, {        0,    25.398,   -5.2778},
    {        0,    25.398,   0.02865}, {        0,    29.197,   -1.2722},
    {        0,    25.398,   -5.2778}, {        0,    24.099,   -3.3322},
    {        0,    24.099,  0.028683}, {        0,    20.299,   -7.1957},
    {        0,    20.299,   0.02861}, {        0,    19.065,   -5.2778},
    {        0,    18.984,  0.028663}, {        0,    15.265,   -9.2778},
    {        0,    15.185,  0.028571}, {        0,    15.265,   -9.2778},
    {        0,    13.999,   -7.3772}, {        0,    13.901,  0.028625},
    {        0,    15.265,   -9.2778}, {        0,    8.9323,   -12.278},
    {        0,    8.9742,  0.028771}, {        0,    8.9323,   -12.278},
    {        0,    7.6657,   -10.278}, {        0,    7.6552,  0.028592},
    {        0,    2.5994,   -15.278}, {        0,    2.6077,  0.028775},
    {        0,    2.5994,   -15.278}, {        0,    1.3329,   -13.278},
    {        0,    1.2617,  0.028727}, {        0,   -3.7334,   -18.278},
    {        0,   -3.7334,   -18.278}, {        0,   -1.2003,   -2.2722},
    {        0,   -1.3098,  0.028727}, {        0,        -5,   -4.2722},
    {        0,        -5,   -4.2722}, {        0,        -5,  0.028727},
    {        0,    30.464,    3.3582}, {        0,    30.464,    3.3582},
    {        0,    29.197,    1.3526}, {        0,    29.197,    1.3526},
    {        0,    29.197,    1.3526}, {        0,    25.398,    5.3582},
    {        0,    29.197,    1.3526}, {        0,    25.398,    5.3582},
    {        0,    24.099,    3.4126}, {        0,    20.299,     7.276},
    {        0,    19.065,    5.3582}, {        0,    15.265,    9.3582},
    {        0,    15.265,    9.3582}, {        0,    13.999,    7.4575},
    {        0,    15.265,    9.3582}, {        0,    8.9323,    12.358},
    {        0,    8.9323,    12.358}, {        0,    7.6657,    10.358},
    {        0,    2.5994,    15.358}, {        0,    2.5994,    15.358},
    {        0,    1.3329,    13.358}, {        0,   -3.7334,    18.358},
    {        0,   -3.7334,    18.358}, {        0,   -1.2003,    2.3526},
    {        0,        -5,    4.3526}, {        0,        -5,    4.3526}
};

const uint32_t numTris = 128;

//[comment]
// Triangle index array. A triangle has 3 vertices. Each successive group of 3
// integers in this array represent the positions of the vertices in the vertex
// array making up one triangle of that object. For example, the first 3 integers
// from this array, 8/7/9 represent the positions of the vertices making up the
// the first triangle. You can access these vertices with the following code:
//
//     verts[8]; /* first vertex  */
//
//     verts[7]; /* second vertex */
//
//     verts[9]; /* third vertex  */
//
// 6/5/5 are the positions of the vertices in the vertex array making up the second
// triangle, and so on.
// To find the indices of the n-th triangle, use the following code:
//
//     tris[n * 3];     /* index of the first vertex in the verts array */
//
//     tris[n * 3 + 1]; /* index of the second vertexin the verts array */
//
//     tris[n * 3 + 2]; /* index of the third vertex in the verts array */
//[/comment]
const uint32_t tris[numTris * 3] = {
      8,   7,   9,   6,   5,   7,   4,   3,   5,   2,   1,   3,   0,   9,   1,
      5,   3,   7,   7,   3,   9,   9,   3,   1,  10,  12,  11,  13,  15,  14,
     15,  13,  16,  13,  17,  16,  18,  20,  19,  17,  20,  21,  20,  23,  22,
     20,  24,  23,  23,  26,  25,  24,  26,  23,  26,  27,  25,  26,  28,  27,
     27,  30,  29,  28,  30,  27,  30,  32,  31,  30,  33,  32,  27,  30,  34,
     32,  36,  35,  33,  36,  32,  36,  38,  37,  36,  39,  38,  38,  41,  40,
     39,  41,  38,  41,  43,  42,  41,  44,  43,  44,  45,  43,  44,  47,  46,
     44,  48,  47,  48,  49,  47,  48,  51,  50,  10,  52,  12,  13,  53,  54,
     55,  17,  54,  13,  54,  17,  56,  57,  20,  17,  58,  20,  20,  59,  60,
     20,  60,  24,  60,  61,  26,  24,  60,  26,  26,  61,  62,  26,  62,  28,
     62,  63,  30,  28,  62,  30,  30,  64,  65,  30,  65,  33,  62,  66,  30,
     65,  67,  36,  33,  65,  36,  36,  68,  69,  36,  69,  39,  69,  70,  41,
     39,  69,  41,  41,  71,  72,  41,  72,  44,  44,  72,  73,  44,  74,  75,
     44,  75,  48,  48,  75,  76,  48,  77,  51,  78,  80,  79,  81,  83,  82,
     83,  81,  84,  81,  85,  84,  86,  88,  87,  85,  88,  89,  88,  91,  90,
     88,  92,  91,  91,  94,  93,  92,  94,  91,  94,  95,  93,  94,  96,  95,
     95,  98,  97,  96,  98,  95,  98, 100,  99,  98, 101, 100,  95,  98, 102,
    100, 104, 103, 101, 104, 100, 104, 106, 105, 104, 107, 106, 106, 109, 108,
    107, 109, 106, 109, 111, 110, 109, 112, 111, 112, 113, 111, 112, 115, 114,
    112, 116, 115, 116, 117, 115, 116, 119, 118,  78, 120,  80,  81, 121, 122,
    123,  85, 122,  81, 122,  85, 124, 125,  88,  85, 126,  88,  88, 127, 128,
     88, 128,  92, 128, 129,  94,  92, 128,  94,  94, 129, 130,  94, 130,  96,
    130, 131,  98,  96, 130,  98,  98, 132, 133,  98, 133, 101, 130, 134,  98,
    133, 135, 104, 101, 133, 104, 104, 136, 137, 104, 137, 107, 137, 138, 109,
    107, 137, 109, 109, 139, 140, 109, 140, 112, 112, 140, 141, 112, 142, 143,
    112, 143, 116, 116, 143, 144, 116, 145, 119
};

//[comment]
// Compute the 2D pixel coordinates of a point defined in world space. This function
// requires the point original world coordinates of course, the world-to-camera
// matrix (which you can get from computing the inverse of the camera-to-world matrix,
// the matrix transforming the camera), the canvas dimension and the image width and
// height in pixels.
//
// Note that we don't check in this version of the function if the point is visible
// or not. If the absolute value of of any of the screen coordinates are greater
// that their respective maximum value (the canvas width for the x-coordinate,
// and the canvas height for the y-coordinate) then the point is not visible.
// When a SVG file is displayed to the screen, the application displaying the content
// of the file clips points and lines which are not visible. Thus we can store lines or point
// in the file whether they are visible or not. The final clipping will be done when the
// image is displayed to the screen.
//[/comment]
void computePixelCoordinates(
    const Vect3f pWorld,
    Vect2i& pRaster,
    const Matr44f& worldToCamera,
    const float& canvasWidth,
    const float& canvasHeight,
    const uint32_t& imageWidth,
    const uint32_t& imageHeight
)
{
    Vect3f pCamera;
    worldToCamera.multVecMatrix(pWorld, pCamera);
    Vect2f pScreen;
    pScreen.x = pCamera.x / -pCamera.z;
    pScreen.y = pCamera.y / -pCamera.z;
    Vect2f pNDC;
    pNDC.x = (pScreen.x + canvasWidth * 0.5) / canvasWidth;
    pNDC.y = (pScreen.y + canvasHeight * 0.5) / canvasHeight;
    pRaster.x = (int)(pNDC.x * imageWidth);
    pRaster.y = (int)((1 - pNDC.y) * imageHeight);
}

void drawGentleLine(Vector2D<int>* point0, Vector2D<int>* point1, SDL_Renderer* renderer);
void drawSteepLine(Vector2D<int>* point0, Vector2D<int>* point1, SDL_Renderer* renderer);
void drawLine(Vector2D<int>* point0, Vector2D<int>* point1, SDL_Renderer* renderer);
void prepareMatrices();
void render(float dt, SDL_Renderer *renderer);
void processPoints(float* points, int numberOfPoints,const Matrix4GLF& matrix);


float vertexPositionsCube[24] = {-1,  1, -1, //0
                                  1,  1, -1, //1
                                  1,  1, -1, //2
                                  1, -1, -1, //3
                                 -1,  1,  1, //4
                                  1,  1,  1, //5
                                 -1, -1,  1, //6
                                  1, -1,  1 //7
                                };


       // CUBE EXAMPLE START

        float cameraX = 0.0F;
        float cameraY = 0.0F;
        float cameraZ = 8.0F;

        float cubeLocationX = 0.0f;
        float cubeLocationY = -2.0f;
        float cubeLocationZ = 0.0f;

        Vector3GLF cubePosition(cubeLocationX, cubeLocationY, cubeLocationZ);

        float aspect;

        // Transformations data
        float movingStepX = 0.0F;
        float movingStepY = 0.0F;
        float movingStepZ = 0.0F;
        float movingStepFactorX = 0.35F;
        float movingStepFactorY = 0.52F;
        float movingStepFactorZ = 0.7F;

        float rotationStep = 0.0F;
        float rotationSpeedFactor = 0.95F;

        Matrix4GLF allRotationsMatrix;

        Matrix4GLF perspectiveMatrix;

        Matrix4GLF viewMatrix;

        Matrix4GLF modelMatrix;

        Matrix4GLF modelViewMatrix;

        Matrix4GLF modelTranslationMatrix;
        Matrix4GLF rotationModelMatrix;

        Matrix4GLF matrixInShaderInOpenGL;

        int windowWidth = 600;
        int windowHeight = 600;

        int helperCounter = 0;

        int pixelCounter = 0;
//-----------------------------------------------------------------------------|---------------------------------------|
//                                                                            80                                     120
int main(int argc, char * argv[])
{
    SDL_Renderer *renderer;
    SDL_Window* window;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(windowWidth, windowHeight, 0, &window, &renderer);

    if(!window)
    {
        std::cerr << "Error failed to create window!\n";
        return 1;
    }
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    
    SDL_Event event;
    bool running = true;


    double time;
    double newTime;
    double deltaTime;
    double fps;
    double fpsTime;
    unsigned int frames;
    MSG message;

    TimePicker timePicker = TimePicker();
    time = timePicker.getSeconds();

    fpsTime = 0.0F;
    frames = 0;
    message.message = WM_NULL;

    prepareMatrices();
    int circleSpeedFactor = 1000;
    int circleSpeed = 2 * circleSpeedFactor;
    int circleCenterX = 50;
    int circleCenterY = 300;
    int circleX = 0;
    int circleY = 0;
    Vector3GLF cameraVector(-cameraX, -cameraY, -cameraZ);

    processPoints(vertexPositionsCube, 8, matrixInShaderInOpenGL);
    //

    Matr44f cameraToWorld(0.871214, 0, -0.490904, 0, -0.192902, 0.919559, -0.342346, 0, 0.451415, 0.392953, 0.801132, 0, 14.777467, 29.361945, 27.993464, 1);
    Matr44f worldToCamera = cameraToWorld.inverse();
    //std::cerr << worldToCamera << std::endl;
    float canvasWidth = 2, canvasHeight = 2;
    uint32_t imageWidth = 512, imageHeight = 512;
    //[comment]
    // Loop over all the triangles making up the object, get the 3 vertices
    // making the current triangle, convert the 3 vertices wolrd coordinates
    // to 2D pixel coordinates using the computePixelCoordinates function.
    // Then finally store the result as 3 lines connecting the projected
    // vertices of the current triangle to each other.
    //[/comment]

    for (uint32_t i = 0; i < numTris; ++i) {
        const Vect3f& v0World = verts[tris[i * 3]];
        const Vect3f& v1World = verts[tris[i * 3 + 1]];
        const Vect3f& v2World = verts[tris[i * 3 + 2]];
        Vect2i v0Raster, v1Raster, v2Raster;
        computePixelCoordinates(v0World, v0Raster, worldToCamera, canvasWidth, canvasHeight, imageWidth, imageHeight);
        computePixelCoordinates(v1World, v1Raster, worldToCamera, canvasWidth, canvasHeight, imageWidth, imageHeight);
        computePixelCoordinates(v2World, v2Raster, worldToCamera, canvasWidth, canvasHeight, imageWidth, imageHeight);
        //std::cerr << v0Raster << ", " << v1Raster << ", " << v2Raster << std::endl;
        SDL_RenderDrawPoint(renderer, circleX, circleY);

        SDL_RenderDrawPoint(renderer, v0Raster.x, v0Raster.y); SDL_RenderDrawPoint(renderer, v1Raster.x, v1Raster.y);
        SDL_RenderDrawPoint(renderer, v1Raster.x, v1Raster.y); SDL_RenderDrawPoint(renderer, v2Raster.x, v2Raster.y);
        SDL_RenderDrawPoint(renderer, v2Raster.x, v2Raster.y); SDL_RenderDrawPoint(renderer, v0Raster.x, v0Raster.y);
    }

    
    Vector2D<int>* beginPoint = new Vector2D<int>();
    Vector2D<int>* endPoint = new Vector2D<int>();

    while(running)
    {
    
        while(SDL_PollEvent(&event))
        {
            running = event.type != SDL_QUIT;
        }
        

        newTime = timePicker.getSeconds();  
        deltaTime = newTime - time;
        time = newTime;
        //printf("%f",deltaTime);
        //render(deltaTime, renderer);
    
    

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    int randomX = rand() % 600;
    int randomY = rand() & 600;
    pixelCounter++;
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    circleCenterX = circleCenterX + deltaTime * circleSpeed;

    //for(int i=0; i< 360;i++) {
    //    circleX = circleCenterX + 50*cos(i);
    //    circleY = circleCenterY + 50*sin(i);
    //    SDL_RenderDrawPoint(renderer, circleX, circleY);
    //}

    // here were methods which are in function prepareMatrices();

    //processPoints(vertexPositionsCube, 8, matrixInShaderInOpenGL);

    //std::cout << "X " << vertexPositionsCube[0] * windowWidth << "Y " << vertexPositionsCube[1]  * (1-windowHeight) << std::endl;
    //std::cout << "X " << vertexPositionsCube[3] * windowWidth << "Y " << vertexPositionsCube[4]  * (1-windowHeight) << std::endl;
    //std::cout << "X " << vertexPositionsCube[6] * windowWidth << "Y " << vertexPositionsCube[7]  * (1-windowHeight) << std::endl;
    //std::cout << "X " << vertexPositionsCube[9] * windowWidth << "Y " << vertexPositionsCube[10] * (1-windowHeight) << std::endl;
    //                                                                                             
    //std::cout << "X " << vertexPositionsCube[12]* windowWidth << "Y " << vertexPositionsCube[13] * (1-windowHeight) << std::endl;
    //std::cout << "X " << vertexPositionsCube[15]* windowWidth << "Y " << vertexPositionsCube[16] * (1-windowHeight) << std::endl;
    //std::cout << "X " << vertexPositionsCube[18]* windowWidth << "Y " << vertexPositionsCube[19] * (1-windowHeight) << std::endl;
    //std::cout << "X " << vertexPositionsCube[21]* windowWidth << "Y " << vertexPositionsCube[22] * (1-windowHeight) << std::endl;


    
    //std::cout << "X " << vertexPositionsCube[0]  << " Y " << vertexPositionsCube[1]   << std::endl;
    //std::cout << "X " << vertexPositionsCube[3]  << " Y " << vertexPositionsCube[4]   << std::endl;
    //std::cout << "X " << vertexPositionsCube[6]  << " Y " << vertexPositionsCube[7]   << std::endl;
    //std::cout << "X " << vertexPositionsCube[9]  << " Y " << vertexPositionsCube[10]  << std::endl;
    //                                                                                 
    //std::cout << "X " << vertexPositionsCube[12] << " Y " << vertexPositionsCube[13]  << std::endl;
    //std::cout << "X " << vertexPositionsCube[15] << " Y " << vertexPositionsCube[16]  << std::endl;
    //std::cout << "X " << vertexPositionsCube[18] << " Y " << vertexPositionsCube[19]  << std::endl;
    //std::cout << "X " << vertexPositionsCube[21] << " Y " << vertexPositionsCube[22]  << std::endl;

    // SDL_RenderDrawPoint(renderer, vertexPositionsCube[0] , vertexPositionsCube[1] );
    // SDL_RenderDrawPoint(renderer, vertexPositionsCube[3] , vertexPositionsCube[4] );
    // SDL_RenderDrawPoint(renderer, vertexPositionsCube[6] , vertexPositionsCube[7] );
    // SDL_RenderDrawPoint(renderer, vertexPositionsCube[9] , vertexPositionsCube[10]);
    //                                                          
    // SDL_RenderDrawPoint(renderer, vertexPositionsCube[12], vertexPositionsCube[13]);
    // SDL_RenderDrawPoint(renderer, vertexPositionsCube[15], vertexPositionsCube[16]);
    // SDL_RenderDrawPoint(renderer, vertexPositionsCube[18], vertexPositionsCube[19]);
    // SDL_RenderDrawPoint(renderer, vertexPositionsCube[21], vertexPositionsCube[22]);


    //drawPoints(vertexPositionsCube, renderer, );

    for (uint32_t i = 0; i < numTris; ++i) {
        const Vect3f& v0World = verts[tris[i * 3]];
        const Vect3f& v1World = verts[tris[i * 3 + 1]];
        const Vect3f& v2World = verts[tris[i * 3 + 2]];
        Vect2i v0Raster, v1Raster, v2Raster;
        computePixelCoordinates(v0World, v0Raster, worldToCamera, canvasWidth, canvasHeight, imageWidth, imageHeight);
        computePixelCoordinates(v1World, v1Raster, worldToCamera, canvasWidth, canvasHeight, imageWidth, imageHeight);
        computePixelCoordinates(v2World, v2Raster, worldToCamera, canvasWidth, canvasHeight, imageWidth, imageHeight);
        //std::cerr << v0Raster << ", " << v1Raster << ", " << v2Raster << std::endl;
        SDL_RenderDrawPoint(renderer, circleX, circleY);

        beginPoint->x = v0Raster.x;
        beginPoint->y = v0Raster.y;
        endPoint->x = v1Raster.x;
        endPoint->y = v1Raster.y;
        drawLine(beginPoint, endPoint, renderer);
        SDL_RenderDrawPoint(renderer, v0Raster.x, v0Raster.y); SDL_RenderDrawPoint(renderer, v1Raster.x, v1Raster.y);


        beginPoint->x = v1Raster.x;
        beginPoint->y = v1Raster.y;
        endPoint->x = v2Raster.x;
        endPoint->y = v2Raster.y;
        drawLine(beginPoint, endPoint, renderer);
        SDL_RenderDrawPoint(renderer, v1Raster.x, v1Raster.y); SDL_RenderDrawPoint(renderer, v2Raster.x, v2Raster.y);

        beginPoint->x = v2Raster.x;
        beginPoint->y = v2Raster.y;
        endPoint->x = v0Raster.x;
        endPoint->y = v0Raster.y;
        drawLine(beginPoint, endPoint, renderer);
        SDL_RenderDrawPoint(renderer, v2Raster.x, v2Raster.y); SDL_RenderDrawPoint(renderer, v0Raster.x, v0Raster.y);

        /*void drawLine(Vector2D<int>* point0, Vector2D<int>* point1, SDL_Renderer* renderer)*/
    }

    SDL_RenderPresent(renderer);


        ++frames;
        fpsTime = fpsTime + deltaTime;
        if(fpsTime >= 1.0F)
        {
            fps = frames / fpsTime;
            frames = 0;
            fpsTime = 0.0F;
        }
    }



    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);


    SDL_Quit();
    return 0;
}
//                                                                            80                                     120
//-----------------------------------------------------------------------------|---------------------------------------|


void drawGentleLine(Vector2D<int>* point0, Vector2D<int>* point1, SDL_Renderer* renderer)
{
    int deltaX = point1->x - point0->x;
    int deltaY = point1->y - point0->y;

    int yIteration = 1;

    if(deltaY <0)
    {
        yIteration = -1;
        deltaY = -deltaY;
    }

    int difference = (2 * deltaY) - deltaX;

    int y = point0->y;

    for (int i = point0->x; i <= point1->x; i++)
    {
        SDL_RenderDrawPoint(renderer, i, y);
        if(difference >0)
        {
            y = y + yIteration;
            difference = difference + (2*(deltaY - deltaX));
        }
        else
        {
            difference = difference + 2*deltaY;
        }
    }
}


void drawSteepLine(Vector2D<int>* point0, Vector2D<int>* point1, SDL_Renderer* renderer)
{
    int deltaX = point1->x - point0->x;
    int deltaY = point1->y - point0->y;

    int xIteration = 1;

    if(deltaX <0)
    {
        xIteration = -1;
        deltaX = -deltaX;
    }

    int difference = (2 * deltaX) - deltaY;

    int x = point0->x;

    for (int i = point0->y; i <= point1->y; i++)
    {
        SDL_RenderDrawPoint(renderer, x, i);
        if(difference >0)
        {
            x = x + xIteration;
            difference = difference + (2*(deltaX - deltaY));
        }
        else
        {
            difference = difference + 2*deltaX;
        }
    }
}

void drawLine(Vector2D<int>* point0, Vector2D<int>* point1, SDL_Renderer* renderer)
{
    if(abs(point1->y - point0->y) < abs(point1->x - point0->x))
    {
        if(point0->x > point1->x)
        {
            drawGentleLine(point1, point0, renderer);
        }
        else
        {
            drawGentleLine(point0, point1, renderer);
        }
    }
    else
    {
        if(point0->y > point1->y)
        {
            drawSteepLine(point1, point0, renderer);
        }
        else
        {
            drawSteepLine(point0, point1, renderer);
        }
    }
}

void drawPoints(float* points, Matrix4GLF matrix, SDL_Renderer* renderer)
{
    //float vertexPositionsCube[24]
    for(int i=0; i<8; i++)
    {
        SDL_RenderDrawPoint(renderer, points[i*3], points[(i*3)+1]);
    }
}

void processPoints(float* points, int numberOfPoints,const Matrix4GLF& matrix)
{
    //float* processedPoints = new float[numberOfPoints*3];
    std::vector<Vector4GLF> newPoints;

    Vector4GLF temporaryVector;
    for(int i=0; i<numberOfPoints; i++)
    {
        temporaryVector.vc0 = points[i*3];
        temporaryVector.vc1 = points[i*3+1];
        temporaryVector.vc2 = points[i*3+2];
        newPoints.push_back(matrixMultiplyedByVector(matrix, temporaryVector));
    }

    for(int i=0; i<numberOfPoints; i++)
    {
        points[i*3]     = newPoints.at(i).vc0;
        points[i*3+1]   = newPoints.at(i).vc1;
        points[i*3+2]   = newPoints.at(i).vc2;
    }

    int i=0;

    //for(const Vector4GLF& point: newPoints)
    //{
    //    points[i++] = point.vc0 + (windowWidth/2.0F);
    //    points[i++] = (windowHeight/2.0F) - point.vc1;
    //    points[i++] = point.vc2;
    //}

    //return new Vector2D<float>(x + (windowWidth/2.0F), (windowHeight/2.0F) - y );

    //gl_Position = proj_matrix * mv_matrix * vec4(position,1.0);
    //static Vector4GLF matrixMultiplyedByVector(Matrix4GLF mat, Vector4GLF vector4glf)

}

void prepareMatrices()
{
    Vector3GLF cameraVector(-cameraX, -cameraY, -cameraZ);

    aspect = static_cast<float>(windowWidth / windowHeight);

    perspectiveMatrix = buildPerspectiveMatrixGLF(1.0472F, aspect, 0.1F, 1000.0F);
   
    viewMatrix = buildTranslationMatrixRowMajorGLFloat(cameraVector);

    modelMatrix = buildTranslationMatrixRowMajorGLFloat(cubePosition); 


    // ??modelViewMatrix = multiply(modelMatrix, viewMatrix);
    modelViewMatrix = multiply(viewMatrix, modelMatrix);

    //from shader:
    //gl_Position = proj_matrix * mv_matrix * vec4(position,1.0);

        //    int windowWidth = 600;
        //int windowHeight = 600;

    matrixInShaderInOpenGL = multiply(perspectiveMatrix, modelViewMatrix);
}

void render(float dt, SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    int randomX = rand() % 600;
    int randomY = rand() & 600;
    pixelCounter++;
    if(pixelCounter < 1000)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderDrawPoint(renderer, randomX, randomY);
    }
    ////////////////////////////////////////////////////////////////////
    //from shader:
    //gl_Position = proj_matrix * mv_matrix * vec4(position,1.0);
    /////////////////////////////////////////////////////////////////////
    SDL_RenderPresent(renderer);
}