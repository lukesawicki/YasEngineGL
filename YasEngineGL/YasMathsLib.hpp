#ifndef YASMATHSLIB_HPP
#define YASMATHSLIB_HPP

#include<cmath>

//-----------------------------------------------------------------------------|---------------------------------------|
//                                                                            80                                     120

//namespace YasMathsLib {
struct Vector4F {
    float x;
    float y;
    float z;
    float w;
} typedef Vector4F, Vec4F;

struct Vector3F {
    float x;
    float y;
    float z;
} typedef Vector3F, Vec3F;

    struct Matrix4F {
        float x1, y1, z1, w1;
        float x2, y2, z2, w2;
        float x3, y3, z3, w3;
        float x4, y4, z4, w4;
    } typedef Mat4;

static Matrix4F buildTranslationMatrix(float x, float y, float z)
{
    Matrix4F mat;
      
    mat.x1 = 1.0F; mat.y1 = 0.0F; mat.z1 = 0.0F; mat.w1 = 0.0F;
    mat.x2 = 0.0F; mat.y2 = 1.0F; mat.z2 = 0.0F; mat.w2 = 0.0F;
    mat.x3 = 0.0F; mat.y3 = 0.0F; mat.z3 = 1.0F; mat.w3 = 0.0F;
    mat.x4 = x;    mat.y4 = y;    mat.z4 = z;    mat.w4 = 1.0F;
    
    return mat;
}


//Rotate X
static Matrix4F buildPitchMatrix(float rad) // Rotate around X axis
{
    Matrix4F mat;

    mat.x1 = 1.0F; mat.y1 = 0.0F;     mat.z1 = 0.0F;      mat.w1 = 0.0F;
    mat.x2 = 0.0F; mat.y2 = cos(rad); mat.z2 = -sin(rad); mat.w2 = 0.0F;
    mat.x3 = 0.0F; mat.y3 = sin(rad); mat.z3 = cos(rad);  mat.w3 = 0.0F;
    mat.x4 = 0.0F; mat.y4 = 0.0F;     mat.z4 = 0.0F;      mat.w4 = 1.0F;
        
    return mat;
}

//Rotate Y
static Matrix4F buildYawMatrix(float rad) // Rotate around Y axis
{
    Matrix4F mat;

    mat.x1 = cos(rad);  mat.y1 = 0.0F; mat.z1 = sin(rad); mat.w1 = 0.0F;
    mat.x2 = 0.0F;      mat.y2 = 1.0F; mat.z2 = 0.0F;     mat.w2 = 0.0F;
    mat.x3 = -sin(rad); mat.y3 = 0.0F; mat.z3 = cos(rad); mat.w3 = 0.0F;
    mat.x4 = 0.0F;      mat.y4 = 0.0F; mat.z4 = 0.0F;     mat.w4 = 1.0F;
        
    return mat;
}

//Rotate Z
static Matrix4F buildRollMatrix(float rad) // Rotate around Z axis
{
    Matrix4F mat;

    mat.x1 = cos(rad); mat.y1 = -sin(rad); mat.z1 = 0.0F; mat.w1 = 0.0F;
    mat.x2 = sin(rad); mat.y2 = cos(rad);  mat.z2 = 0.0F; mat.w2 = 0.0F;
    mat.x3 = 0.0F;     mat.y3 = 0.0F;      mat.z3 = 1.0F; mat.w3 = 0.0F;
    mat.x4 = 0.0F;     mat.y4 = 0.0F;      mat.z4 = 0.0F; mat.w4 = 1.0F;

    return mat;
}

static Matrix4F buildScaleMatrix(float x, float y, float z)
{
    Matrix4F mat;

    mat.x1 = x;    mat.y1 = 0.0F; mat.z1 = 0.0F; mat.w1 = 0.0F;
    mat.x2 = 0.0F; mat.y2 = y;    mat.z2 = 0.0F; mat.w2 = 0.0F;
    mat.x3 = 0.0F; mat.y3 = 0.0F; mat.z3 = z;    mat.w3 = 0.0F;
    mat.x4 = 0.0F; mat.y4 = 0.0F; mat.z4 = 0.0F; mat.w4 = 1.0F;

    return mat;
}

//}

#endif YASMATHSLIB_HPP

//                                                                            80                                     120
//-----------------------------------------------------------------------------|---------------------------------------|
