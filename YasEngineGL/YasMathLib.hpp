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
    Vector3GLF(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }
} typedef Vector3F, Vec3F;

struct Vector4GLF {
    GLfloat x;
    GLfloat y;
    GLfloat z;
    GLfloat w;
} typedef Vector4F, Vec4F;

struct Matrix4GLF {
    // Naming: me - matrix entry
    GLfloat me00=1.0F, me01=0.0F, me02=0.0F, me03=0.0F;
    GLfloat me10=0.0F, me11=1.0F, me12=0.0F, me13=0.0F;
    GLfloat me20=0.0F, me21=0.0F, me22=1.0F, me23=0.0F;
    GLfloat me30=0.0F, me31=0.0F, me32=0.0F, me33=1.0F;

} typedef Mat4GLF;

static void transpose(Matrix4GLF &mat);
static void normalizeVector(Vector3GLF& vector);
static GLfloat getVectorMagnitude(const Vector3GLF& vector);

static Matrix4GLF multiply(const Matrix4GLF& a,const Matrix4GLF& b)
{
    Matrix4GLF mat = {
        a.me00*b.me00 + a.me01*b.me10 + a.me02*b.me20 + a.me03*b.me30, /*|*/ a.me00*b.me01 + a.me01*b.me11 + a.me02*b.me21 + a.me03*b.me31, /*|*/ a.me00*b.me02 + a.me01*b.me12 + a.me02*b.me22 + a.me03*b.me32, /*|*/ a.me00*b.me03 + a.me01*b.me13 + a.me02*b.me23 + a.me03*b.me33,
        a.me10*b.me00 + a.me11*b.me10 + a.me12*b.me20 + a.me13*b.me30, /*|*/ a.me10*b.me01 + a.me11*b.me11 + a.me12*b.me21 + a.me13*b.me31, /*|*/ a.me10*b.me02 + a.me11*b.me12 + a.me12*b.me22 + a.me13*b.me32, /*|*/ a.me10*b.me03 + a.me11*b.me13 + a.me12*b.me23 + a.me13*b.me33,
        a.me20*b.me00 + a.me21*b.me10 + a.me22*b.me20 + a.me23*b.me30, /*|*/ a.me20*b.me01 + a.me21*b.me11 + a.me22*b.me21 + a.me23*b.me31, /*|*/ a.me20*b.me02 + a.me21*b.me12 + a.me22*b.me22 + a.me23*b.me32, /*|*/ a.me20*b.me03 + a.me21*b.me13 + a.me22*b.me23 + a.me23*b.me33,
        a.me30*b.me00 + a.me31*b.me10 + a.me32*b.me20 + a.me33*b.me30, /*|*/ a.me30*b.me01 + a.me31*b.me11 + a.me32*b.me21 + a.me33*b.me31, /*|*/ a.me30*b.me02 + a.me31*b.me12 + a.me32*b.me22 + a.me33*b.me32, /*|*/ a.me30*b.me03 + a.me31*b.me13 + a.me32*b.me23 + a.me33*b.me33
    };
    return mat;
}

// IN GLM IT IS (GLM_DEPTH_CLIP_SPACE == GLM_DEPTH_ZERO_ONE) == false
static Matrix4GLF buildPerspectiveMatrixGLF(const float& fieldOfViewY, const float& aspectRatio, const float& zNearPlane, const float& zFarPlane, bool isTransposed = false)
{
    Matrix4GLF mat = {
        static_cast<GLfloat>(1.0F / ((tan(fieldOfViewY/2.0F)) * aspectRatio)), 0.0F,                                                    0.0F,                                                                                0.0F,  //0
        0.0F,                                                                  static_cast<GLfloat>(1.0F / (tan(fieldOfViewY/2.0F))),   0.0F,                                                                                0.0F,  //1
        0.0F,                                                                  0.0F,                                                    static_cast<GLfloat>( - (zFarPlane + zNearPlane)/( zFarPlane - zNearPlane) ),        -1.0F, //2
        0.0F,                                                                  0.0F,                                                    static_cast<GLfloat>(- (2 * zFarPlane * zNearPlane) / (zFarPlane - zNearPlane) ),    0.0F   //3
    };
    
    if(isTransposed)
    {
        transpose(mat);
    }

    return mat;
}

static Matrix4GLF buildTranslationMatrixRowMajorGLFloat(const GLfloat& x, const GLfloat& y, const GLfloat&  z)
{
    Matrix4GLF mat = {
        mat.me00 = 1.0F, mat.me01 = 0.0F, mat.me02 = 0.0F, mat.me03 = 0.0F,
        mat.me10 = 0.0F, mat.me11 = 1.0F, mat.me12 = 0.0F, mat.me13 = 0.0F,
        mat.me20 = 0.0F, mat.me21 = 0.0F, mat.me22 = 1.0F, mat.me23 = 0.0F,
        mat.me30 = x,    mat.me31 = y,    mat.me32 = z,    mat.me33 = 1.0F
    };

    return mat;
}

static Matrix4GLF buildTranslationMatrixRowMajorGLFloat(const Vector3GLF& vector)
{
    Matrix4GLF mat = {
        mat.me00 = 1.0F, mat.me01 = 0.0F, mat.me02 = 0.0F, mat.me03 = 0.0F,
        mat.me10 = 0.0F, mat.me11 = 1.0F, mat.me12 = 0.0F, mat.me13 = 0.0F,
        mat.me20 = 0.0F, mat.me21 = 0.0F, mat.me22 = 1.0F, mat.me23 = 0.0F,
        mat.me30 = vector.x,    mat.me31 = vector.y,    mat.me32 = vector.z,    mat.me33 = 1.0F
    };

    return mat;
}

static Matrix4GLF buildTranslationMatrixColumnMajorGLFloat(const GLfloat& x, const GLfloat& y, const GLfloat&  z)
{
    Matrix4GLF mat = {
        mat.me00 = 1.0F, mat.me01 = 0.0F, mat.me02 = 0.0F, mat.me03 = x,
        mat.me10 = 0.0F, mat.me11 = 1.0F, mat.me12 = 0.0F, mat.me13 = y,
        mat.me20 = 0.0F, mat.me21 = 0.0F, mat.me22 = 1.0F, mat.me23 = z,
        mat.me30 = 0.0F, mat.me31 = 0.0F, mat.me32 = 0.0,  mat.me33 = 1.0F
    };
    
    return mat;
}

static Matrix4GLF buildTranslationMatrixColumnMajorGLFloat(const Vector3GLF& vector)
{
    Matrix4GLF mat = {
        mat.me00 = 1.0F, mat.me01 = 0.0F, mat.me02 = 0.0F, mat.me03 = vector.x,
        mat.me10 = 0.0F, mat.me11 = 1.0F, mat.me12 = 0.0F, mat.me13 = vector.y,
        mat.me20 = 0.0F, mat.me21 = 0.0F, mat.me22 = 1.0F, mat.me23 = vector.z,
        mat.me30 = 0.0F, mat.me31 = 0.0F, mat.me32 = 0.0,  mat.me33 = 1.0F
    };
    
    return mat;
}

GLfloat getVectorMagnitude(const Vector3GLF& vector)
{
    return sqrt(pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2));
}

void normalizeVector(Vector3GLF& vector)
{
    GLfloat vectorMagnitude = getVectorMagnitude(vector);
    vector.x = vector.x / vectorMagnitude;
    vector.y = vector.y / vectorMagnitude;
    vector.z = vector.z / vectorMagnitude;
}

 // Rotate around X axis
static Matrix4GLF buildPitchMatrix(const float& rad)
{
    Matrix4GLF mat = {
        mat.me00 = 1.0F, mat.me01 = 0.0F,     mat.me02 = 0.0F,      mat.me03 = 0.0F,
        mat.me10 = 0.0F, mat.me11 = cos(rad), mat.me12 = -sin(rad), mat.me13 = 0.0F,
        mat.me20 = 0.0F, mat.me21 = sin(rad), mat.me22 = cos(rad),  mat.me23 = 0.0F,
        mat.me30 = 0.0F, mat.me31 = 0.0F,     mat.me32 = 0.0F,      mat.me33 = 1.0F,
    };
    return mat;
}

// Rotate around Y axis
static Matrix4GLF buildYawMatrix(const float& rad)
{
    Matrix4GLF mat = {
        mat.me00 = cos(rad),  mat.me01 = 0.0F, mat.me02 = sin(rad), mat.me03 = 0.0F,
        mat.me10 = 0.0F,      mat.me11 = 1.0F, mat.me12 = 0.0F,     mat.me13 = 0.0F,
        mat.me20 = -sin(rad), mat.me21 = 0.0F, mat.me22 = cos(rad), mat.me23 = 0.0F,
        mat.me30 = 0.0F,      mat.me31 = 0.0F, mat.me32 = 0.0F,     mat.me33 = 1.0F,
    };
    return mat;
}

// Rotate around Z axis
static Matrix4GLF buildRollMatrix(const float& rad)
{
    Matrix4GLF mat = {
        mat.me00 = cos(rad), mat.me01 = -sin(rad), mat.me02 = 0.0F, mat.me03 = 0.0F,
        mat.me10 = sin(rad), mat.me11 = cos(rad),  mat.me12 = 0.0F, mat.me13 = 0.0F,
        mat.me20 = 0.0F,     mat.me21 = 0.0F,      mat.me22 = 1.0F, mat.me23 = 0.0F,
        mat.me30 = 0.0F,     mat.me31 = 0.0F,      mat.me32 = 0.0F, mat.me33 = 1.0F,
    };
    return mat;
}

static Matrix4GLF buildAllRotationMatrix(const float& p, const float& y, const float& r, bool isTransposed = false)
{
    Matrix4GLF mat = {
        mat.me00 = cos(r)*cos(y),                        mat.me01 = sin(r)*cos(y),                             mat.me02 = sin(y),         mat.me03 = 0.0F,
        mat.me10 = sin(r)*cos(p) + cos(r)*sin(y)*sin(p), mat.me11 = cos(r)*cos(p) -(sin(r)*sin(y)*sin(p)),     mat.me12 = -sin(p)*cos(y), mat.me13 = 0.0F,
        mat.me20 = sin(r)*sin(p) - cos(r)*sin(y)*cos(p), mat.me21 = cos(r)*sin(p) + sin(r)*sin(y)*cos(p),      mat.me22 = cos(y)*cos(p),  mat.me23 = 0.0F,
        mat.me30 = 0.0F,                                 mat.me31 = 0.0F,                                      mat.me32 = 0.0F,           mat.me33 = 1.0F,
    };

    //if(isTransposed)
    //{
    //    transpose(mat);
    //}

    return mat;
}

static Matrix4GLF rotationAroundArbitraryAxies(Vector3GLF axisVector, const float& angle, bool isTransposed = false)
{
    float c = cos(angle);
    float s = sin(angle);
    
    normalizeVector(axisVector);

        Matrix4GLF mat = {
    mat.me00 = c+((1.0F - c)*axisVector.x)* axisVector.x,             mat.me01 = ((1.0F-c)*axisVector.x)*axisVector.y + s*axisVector.z, mat.me02 = ((1.0F-c)*axisVector.x)*axisVector.z - s*axisVector.y, mat.me03 = 0.0F,
    mat.me10 = ((1.0F-c)*axisVector.y)*axisVector.x - s*axisVector.z, mat.me11 = c+((1.0F - c)*axisVector.y)*axisVector.y,              mat.me12 = ((1.0F-c)*axisVector.y)*axisVector.z + s*axisVector.x, mat.me13 = 0.0F,
    mat.me20 = ((1.0F-c)*axisVector.z)*axisVector.x + s*axisVector.y,   mat.me21 = ((1.0F-c)*axisVector.z)*axisVector.y - s*axisVector.x,   mat.me22 = c+((1.0F - c)*axisVector.z)*axisVector.z,                           mat.me23 = 0.0F,
    mat.me30 = 0.0F,                                                            mat.me31 = 0.0F,                                                            mat.me32 = 0.0F,                                                            mat.me33 = 1.0F,
    };

    //if(isTransposed)
    //{
    //    transpose(mat);
    //}

    return mat;
}

//Scale
static Matrix4GLF buildScaleMatrix(const float& x, const float& y, const float& z)
{
    Matrix4GLF mat = {
        mat.me00 = x,    mat.me01 = 0.0F, mat.me01 = 0.0F, mat.me01 = 0.0F,
        mat.me10 = 0.0F, mat.me11 = y,    mat.me11 = 0.0F, mat.me11 = 0.0F,
        mat.me20 = 0.0F, mat.me21 = 0.0F, mat.me21 = z,    mat.me21 = 0.0F,
        mat.me30 = 0.0F, mat.me31 = 0.0F, mat.me31 = 0.0F, mat.me31 = 1.0F,
    };
    return mat;
}

//Transpose
static void transpose(Matrix4GLF &mat)
{
    Matrix4GLF matCopy;

    matCopy.me00=mat.me00; matCopy.me10=mat.me10; matCopy.me20=mat.me20; matCopy.me30=mat.me30;
    matCopy.me10=mat.me01; matCopy.me11=mat.me11; matCopy.me21=mat.me21; matCopy.me31=mat.me31;
    matCopy.me20=mat.me02; matCopy.me12=mat.me12; matCopy.me22=mat.me22; matCopy.me32=mat.me32;
    matCopy.me30=mat.me03; matCopy.me13=mat.me13; matCopy.me23=mat.me23; matCopy.me33=mat.me33;

    mat.me00=matCopy.me00; mat.me01=matCopy.me10; mat.me02=matCopy.me20; mat.me03=matCopy.me30;
    mat.me10=matCopy.me01; mat.me11=matCopy.me11; mat.me12=matCopy.me21; mat.me13=matCopy.me31;
    mat.me20=matCopy.me02; mat.me21=matCopy.me12; mat.me22=matCopy.me22; mat.me23=matCopy.me32;
    mat.me30=matCopy.me03; mat.me31=matCopy.me13; mat.me32=matCopy.me23; mat.me33=matCopy.me33;
}

#endif YASMATHLIB_HPP

// Right handed

// Row major

// Column major

//----------------------------------------------------------------------------------------------------------------------

// Left handed

// Row major

// Column major


//                                                                            80                                     120
//-----------------------------------------------------------------------------|---------------------------------------|
