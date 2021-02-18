#include<cstdlib>
#include<iostream>
#include<vector>
#include<cmath>
#include<SDL.h>
#include"Mathematics.hpp"
#include"TimePicker.hpp"

void drawGentleLine(Vector2D<int>* point0, Vector2D<int>* point1, SDL_Renderer* renderer);
void drawSteepLine(Vector2D<int>* point0, Vector2D<int>* point1, SDL_Renderer* renderer);
void drawLine(Vector2D<int>* point0, Vector2D<int>* point1, SDL_Renderer* renderer);
void preparePerspectiveAndViewMatrix();
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

        float cameraX;
        float cameraY;
        float cameraZ;

        float cubeLocationX;
        float cubeLocationY;
        float cubeLocationZ;

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
    //SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    Vector2D<int>* point0 = new Vector2D<int>(60, 60);
    Vector2D<int>* point1 = new Vector2D<int>(200, 80); 

    Vector2D<int>* point2 = new Vector2D<int>(60, 80);
    Vector2D<int>* point3 = new Vector2D<int>(200, 60); 

    Vector2D<int>* point4 = new Vector2D<int>(60, 60);
    Vector2D<int>* point5 = new Vector2D<int>(200, 60); 

    Vector2D<int>* point6 = new Vector2D<int>(60, 60);
    Vector2D<int>* point7 = new Vector2D<int>(60, 200); 

    drawLine(point0, point1, renderer);
    drawLine(point2, point3, renderer);
    drawLine(point4, point5, renderer);
    drawLine(point6, point7, renderer);

    //

    
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

    preparePerspectiveAndViewMatrix();
    int circleSpeedFactor = 1000;
    int circleSpeed = 2 * circleSpeedFactor;
    int circleCenterX = 50;
    int circleCenterY = 300;
    int circleX = 0;
    int circleY = 0;
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

    for(int i=0; i< 360;i++) {
        circleX = circleCenterX + 50*cos(i);
        circleY = circleCenterY + 50*sin(i);
        SDL_RenderDrawPoint(renderer, circleX, circleY);
    }

    aspect = static_cast<float>(windowWidth / windowHeight);
    perspectiveMatrix = buildPerspectiveMatrixGLF(1.0472F, aspect, 0.1F, 1000.0F);
    Vector3GLF cameraVector(-cameraX, -cameraY, -cameraZ);
    viewMatrix = buildTranslationMatrixRowMajorGLFloat(cameraVector);

    movingStepX = movingStepX + movingStepFactorX*deltaTime;
    rotationStep = rotationStep + (-1.75F*deltaTime*rotationSpeedFactor);
    Vector3GLF justX = {1.0F, 0.0F, 0.0F};
    rotationModelMatrix = rotationAroundArbitraryAxies(justX, rotationStep);
    modelMatrix = multiply(rotationModelMatrix, modelTranslationMatrix);
    modelViewMatrix = multiply(modelMatrix, viewMatrix);


    //from shader:
    //gl_Position = proj_matrix * mv_matrix * vec4(position,1.0);
    /////////////////////////////////////////////////////////////////////
    matrixInShaderInOpenGL = multiply(perspectiveMatrix, modelViewMatrix);
    processPoints(vertexPositionsCube, 8, matrixInShaderInOpenGL);

    for(int i=0; i<=8; i++)
    {
        printf("%f x: ",vertexPositionsCube[i*3]);
        printf("%f y: ",vertexPositionsCube[i*3+1]);
        printf("%f z: ",vertexPositionsCube[i*3+2]);
    }


     SDL_RenderDrawPoint(renderer, vertexPositionsCube[0], vertexPositionsCube[1]);
     SDL_RenderDrawPoint(renderer, vertexPositionsCube[3], vertexPositionsCube[4]);
     SDL_RenderDrawPoint(renderer, vertexPositionsCube[6], vertexPositionsCube[7]);
     SDL_RenderDrawPoint(renderer, vertexPositionsCube[9], vertexPositionsCube[10]);

     SDL_RenderDrawPoint(renderer, vertexPositionsCube[12], vertexPositionsCube[13]);
     SDL_RenderDrawPoint(renderer, vertexPositionsCube[15], vertexPositionsCube[16]);
     SDL_RenderDrawPoint(renderer, vertexPositionsCube[18], vertexPositionsCube[19]);
     SDL_RenderDrawPoint(renderer, vertexPositionsCube[21], vertexPositionsCube[22]);


    //drawPoints(vertexPositionsCube, renderer, );

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
        temporaryVector.vc0 = points[i*3+1];
        temporaryVector.vc0 = points[i*3+2];
        newPoints.push_back(matrixMultiplyedByVector(matrix, temporaryVector));
    }

    int i=0;

    for(const Vector4GLF& point: newPoints)
    {
        points[i++] = point.vc0 + (windowWidth/2.0F);
        points[i++] = (windowHeight/2.0F) - point.vc1;
        points[i++] = point.vc2;
    }

    //return new Vector2D<float>(x + (windowWidth/2.0F), (windowHeight/2.0F) - y );

    //gl_Position = proj_matrix * mv_matrix * vec4(position,1.0);
    //static Vector4GLF matrixMultiplyedByVector(Matrix4GLF mat, Vector4GLF vector4glf)

}

void preparePerspectiveAndViewMatrix()
{
	
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