#ifndef YASGRAPHICSLIBRARY_HPP
#define YASGRAPHICSLIBRARY_HPP
#include<cmath>
#include<iostream>
#include<windows.h>
#include<gl/gl.h>
//#include <GLFW/glfw3.h>
#include"Vector2D.hpp"
#include"Vector3D.hpp"
#include"Vector4D.hpp"


namespace YasGL
{
    const uint8_t NUMBER_OF_COLORS = 4;
    const uint8_t RGB_FORMAT = 3;
    const uint8_t RGBA_FORMAT = 4;

    const uint8_t RED_POSITION = 0;
    const uint8_t GREEN_POSITION = 1;
    const uint8_t BLUE_POSITION = 2;
    const uint8_t ALPHA_POSITION = 3;

	const Vector4D<uint8_t> RED(255, 0, 0, 0);
	const Vector4D<uint8_t> GREEN(0, 255, 0, 0);
	const Vector4D<uint8_t> BLUE(0, 0, 255, 0);
	const Vector4D<uint8_t> BLACK(0, 0, 0, 0);

    

    void clearColor(uint8_t* pixels, Vector4D<uint8_t>* drawingColor, Vector2D<int>* windowDimensions);

    void cartesianPositionToWindow(Vector2D<int>* point, Vector2D<int>* windowDimensions);
    void windowPositionToCartesian(Vector2D<int>* point, Vector2D<int>* windowDimensions);
    
    uint8_t* createPixelsTable(Vector2D<int>* windowDimensions, Vector4D<uint8_t>* defaultColor);

    void drawPoint(Vector2D<int>* point, uint8_t* pixels, Vector4D<uint8_t>* drawingColor, Vector2D<int>* windowDimensions);
    void drawPoint(int x, int y, uint8_t* pixels, Vector4D<uint8_t>* drawingColor, Vector2D<int>* windowDimensions);

    void drawLine(Vector2D<int>* point0, Vector2D<int>* point1, uint8_t* pixels, Vector4D<uint8_t>* drawingColor, Vector2D<int>* windowDimensions);

    void lukeDrawLineOctan0V1(Vector2D<int>* point0, Vector2D<int>* point1, uint8_t* pixels, Vector4D<uint8_t>* drawingColor, Vector2D<int>* windowDimensions);
    void lukeDrawLineOctan0V2(Vector2D<int>* point0, Vector2D<int>* point1, uint8_t* pixels, Vector4D<uint8_t>* drawingColor, Vector2D<int>* windowDimensions);

    void helsinkiDraw(Vector2D<int>* point0, Vector2D<int>* point1, uint8_t* pixels, Vector3D<uint8_t>* drawingColor, Vector2D<int>* windowDimensions);

    void drawCartesianAxies(Vector2D<int>* windowDimensions, uint8_t* pixels);
    int xyPixelToArrayPosition(Vector2D<int>* point, int windowWidth);
    int xyPixelToArrayPosition(int x, int y, int windowWidth);
    void drawCircle(Vector2D<int>* position, int& radius, uint8_t* pixels, Vector4D<uint8_t>* drawingColor, Vector2D<int>* windowDimensions); //Vector2D<int>* windowDimensions
}

#endif