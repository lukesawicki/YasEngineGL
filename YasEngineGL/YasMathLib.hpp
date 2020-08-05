#ifndef YASMATHLIB_HPP
#define YASMATHLIB_HPP

#include<cmath>

//-----------------------------------------------------------------------------|---------------------------------------|
//                                                                            80                                     120

// In OpenGL matrices are defined using column major order but it is strange that in perspective matrix it uses row major

struct Vector3GLF {
    GLfloat x;
    GLfloat y;
    GLfloat z;
} typedef Vector3F, Vec3F;

struct Vector4GLF {
    GLfloat x;
    GLfloat y;
    GLfloat z;
    GLfloat w;
} typedef Vector4F, Vec4F;

struct Matrix4GLF {
    // Naming: me - matrix entry
    GLfloat me11=1.0F, me12=0.0F, me13=0.0F, me14=0.0F;
    GLfloat me21=0.0F, me22=1.0F, me23=0.0F, me24=0.0F;
    GLfloat me31=0.0F, me32=0.0F, me33=1.0F, me34=0.0F;
    GLfloat me41=0.0F, me42=0.0F, me43=0.0F, me44=1.0F;

} typedef Mat4GLF;

static Matrix4GLF multiply(const Matrix4GLF& a,const Matrix4GLF& b)
{
    Matrix4GLF mat = {
        a.me11*b.me11 + a.me12*b.me21 + a.me13*b.me31 + a.me14*b.me41, /*|*/ a.me11*b.me12 + a.me12*b.me22 + a.me13*b.me32 + a.me14*b.me42, /*|*/ a.me11*b.me13 + a.me12*b.me23 + a.me13*b.me33 + a.me14*b.me43, /*|*/ a.me11*b.me14 + a.me12*b.me24 + a.me13*b.me34 + a.me14*b.me44,
        a.me21*b.me11 + a.me22*b.me21 + a.me23*b.me31 + a.me24*b.me41, /*|*/ a.me21*b.me12 + a.me22*b.me22 + a.me23*b.me32 + a.me24*b.me42, /*|*/ a.me21*b.me13 + a.me22*b.me23 + a.me23*b.me33 + a.me24*b.me43, /*|*/ a.me21*b.me14 + a.me22*b.me24 + a.me23*b.me34 + a.me24*b.me44,
        a.me31*b.me11 + a.me32*b.me21 + a.me33*b.me31 + a.me34*b.me41, /*|*/ a.me31*b.me12 + a.me32*b.me22 + a.me33*b.me32 + a.me34*b.me42, /*|*/ a.me31*b.me13 + a.me32*b.me23 + a.me33*b.me33 + a.me34*b.me43, /*|*/ a.me31*b.me14 + a.me32*b.me24 + a.me33*b.me34 + a.me34*b.me44,
        a.me41*b.me11 + a.me42*b.me21 + a.me43*b.me31 + a.me44*b.me41, /*|*/ a.me41*b.me12 + a.me42*b.me22 + a.me43*b.me32 + a.me44*b.me42, /*|*/ a.me41*b.me13 + a.me42*b.me23 + a.me43*b.me33 + a.me44*b.me43, /*|*/ a.me41*b.me14 + a.me42*b.me24 + a.me43*b.me34 + a.me44*b.me44
    };
    return mat;
}

static Matrix4GLF buildPerspectiveMatrixGLF(const float& fieldOfViewY, const float& aspectRatio, const float& zNearPlane, const float& zFarPlane)
{
    Matrix4GLF mat = {
        static_cast<GLfloat>(1 / ((tan(fieldOfViewY/2.0F)) * aspectRatio)), 0,                                               0,                                                                                0,
        0,                                                                  static_cast<GLfloat>(1 / (tan(fieldOfViewY/2))), 0,                                                                                0,
        0,                                                                  0,                                               static_cast<GLfloat>( (zNearPlane + zFarPlane)/(zNearPlane - zFarPlane) ),        -1.0F,
        0,                                                                  0,                                               static_cast<GLfloat>(-(( 2 * zFarPlane * zNearPlane) / zFarPlane - zNearPlane )), 0
    };

    return mat;
}

static Matrix4GLF buildTranslationMatrixGLF(const GLfloat& x, const GLfloat& y, const GLfloat&  z)
{
    Matrix4GLF mat = {
        mat.me11 = 1.0F, mat.me12 = 0.0F, mat.me13 = 0.0F, mat.me14 = 0.0F,
        mat.me21 = 0.0F, mat.me22 = 1.0F, mat.me23 = 0.0F, mat.me24 = 0.0F,
        mat.me31 = 0.0F, mat.me32 = 0.0F, mat.me33 = 1.0F, mat.me34 = 0.0F,
        mat.me41 = x,    mat.me42 = y,    mat.me43 = z,    mat.me44 = 1.0F
    };
    return mat;
}

 // Rotate around X axis
static Matrix4GLF buildPitchMatrix(const float& rad)
{
    Matrix4GLF mat = {
        mat.me11 = 1.0F, mat.me12 = 0.0F,     mat.me13 = 0.0F,      mat.me14 = 0.0F,
        mat.me21 = 0.0F, mat.me22 = cos(rad), mat.me23 = -sin(rad), mat.me24 = 0.0F,
        mat.me31 = 0.0F, mat.me32 = sin(rad), mat.me33 = cos(rad),  mat.me34 = 0.0F,
        mat.me41 = 0.0F, mat.me42 = 0.0F,     mat.me43 = 0.0F,      mat.me44 = 1.0F,
    };
    return mat;
}

// Rotate around Y axis
static Matrix4GLF buildYawMatrix(const float& rad)
{
    Matrix4GLF mat = {
        mat.me11 = cos(rad),  mat.me12 = 0.0F, mat.me13 = sin(rad), mat.me14 = 0.0F,
        mat.me21 = 0.0F,      mat.me22 = 1.0F, mat.me23 = 0.0F,     mat.me24 = 0.0F,
        mat.me31 = -sin(rad), mat.me32 = 0.0F, mat.me33 = cos(rad), mat.me34 = 0.0F,
        mat.me41 = 0.0F,      mat.me42 = 0.0F, mat.me43 = 0.0F,     mat.me44 = 1.0F,
    };
    return mat;
}

// Rotate around Z axis
static Matrix4GLF buildRollMatrix(const float& rad)
{
    Matrix4GLF mat = {
        mat.me11 = cos(rad), mat.me12 = -sin(rad), mat.me13 = 0.0F, mat.me14 = 0.0F,
        mat.me21 = sin(rad), mat.me22 = cos(rad),  mat.me23 = 0.0F, mat.me24 = 0.0F,
        mat.me31 = 0.0F,     mat.me32 = 0.0F,      mat.me33 = 1.0F, mat.me34 = 0.0F,
        mat.me41 = 0.0F,     mat.me42 = 0.0F,      mat.me43 = 0.0F, mat.me44 = 1.0F,
    };
    return mat;
}

//Scale
static Matrix4GLF buildScaleMatrix(const float& x, const float& y, const float& z)
{
    Matrix4GLF mat = {
        mat.me11 = x,    mat.me12 = 0.0F, mat.me12 = 0.0F, mat.me12 = 0.0F,
        mat.me21 = 0.0F, mat.me22 = y,    mat.me22 = 0.0F, mat.me22 = 0.0F,
        mat.me31 = 0.0F, mat.me32 = 0.0F, mat.me32 = z,    mat.me32 = 0.0F,
        mat.me41 = 0.0F, mat.me42 = 0.0F, mat.me42 = 0.0F, mat.me42 = 1.0F,
    };
    return mat;
}

//Transpose
static void transponse(Matrix4GLF &mat)
{
    Matrix4GLF matCopy;

    matCopy.me11=mat.me11; matCopy.me21=mat.me21; matCopy.me31=mat.me31; matCopy.me41=mat.me41;
    matCopy.me21=mat.me12; matCopy.me22=mat.me22; matCopy.me32=mat.me32; matCopy.me42=mat.me42;
    matCopy.me31=mat.me13; matCopy.me23=mat.me23; matCopy.me33=mat.me33; matCopy.me43=mat.me43;
    matCopy.me41=mat.me14; matCopy.me24=mat.me24; matCopy.me34=mat.me34; matCopy.me44=mat.me44;

    mat.me11=matCopy.me11; mat.me12=matCopy.me21; mat.me13=matCopy.me31; mat.me14=matCopy.me41;
    mat.me21=matCopy.me12; mat.me22=matCopy.me22; mat.me23=matCopy.me32; mat.me24=matCopy.me42;
    mat.me31=matCopy.me13; mat.me32=matCopy.me23; mat.me33=matCopy.me33; mat.me34=matCopy.me43;
    mat.me41=matCopy.me14; mat.me42=matCopy.me24; mat.me43=matCopy.me34; mat.me44=matCopy.me44;
}

#endif YASMATHLIB_HPP

//                                                                            80                                     120
//-----------------------------------------------------------------------------|---------------------------------------|
