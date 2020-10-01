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

static void transpose(Matrix4GLF &mat);
static void normalizeVector(Vector3GLF& vector);
static GLfloat getVectorMagnitude(const Vector3GLF& vector);

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

//static Matrix4GLF multiplyT(const Matrix4GLF& a,const Matrix4GLF& b)
//{
//    Matrix4GLF mat = {
//        a.me11*b.me11 + a.me12*b.me21 + a.me13*b.me31 + a.me14*b.me41, /*|*/ a.me11*b.me12 + a.me12*b.me22 + a.me13*b.me32 + a.me14*b.me42, /*|*/ a.me11*b.me13 + a.me12*b.me23 + a.me13*b.me33 + a.me14*b.me43, /*|*/ a.me11*b.me14 + a.me12*b.me24 + a.me13*b.me34 + a.me14*b.me44,
//        a.me21*b.me11 + a.me22*b.me21 + a.me23*b.me31 + a.me24*b.me41, /*|*/ a.me21*b.me12 + a.me22*b.me22 + a.me23*b.me32 + a.me24*b.me42, /*|*/ a.me21*b.me13 + a.me22*b.me23 + a.me23*b.me33 + a.me24*b.me43, /*|*/ a.me21*b.me14 + a.me22*b.me24 + a.me23*b.me34 + a.me24*b.me44,
//        a.me31*b.me11 + a.me32*b.me21 + a.me33*b.me31 + a.me34*b.me41, /*|*/ a.me31*b.me12 + a.me32*b.me22 + a.me33*b.me32 + a.me34*b.me42, /*|*/ a.me31*b.me13 + a.me32*b.me23 + a.me33*b.me33 + a.me34*b.me43, /*|*/ a.me31*b.me14 + a.me32*b.me24 + a.me33*b.me34 + a.me34*b.me44,
//        a.me41*b.me11 + a.me42*b.me21 + a.me43*b.me31 + a.me44*b.me41, /*|*/ a.me41*b.me12 + a.me42*b.me22 + a.me43*b.me32 + a.me44*b.me42, /*|*/ a.me41*b.me13 + a.me42*b.me23 + a.me43*b.me33 + a.me44*b.me43, /*|*/ a.me41*b.me14 + a.me42*b.me24 + a.me43*b.me34 + a.me44*b.me44
//    };
//
//    transponse(mat);
//
//    return mat;
//}

// IN GLM IT IS (GLM_DEPTH_CLIP_SPACE == GLM_DEPTH_ZERO_ONE) == false
static Matrix4GLF buildPerspectiveMatrixGLF(const float& fieldOfViewY, const float& aspectRatio, const float& zNearPlane, const float& zFarPlane)
{
    Matrix4GLF mat = {
        //0000000000000000000000000000000000000000000000000000000000000000000  111111111111111111111111111111111111111111111111111111   22222222222222222222222222222222222222222222222222222222222222222222222222222222     333333333333333333333
        static_cast<GLfloat>(1.0F / ((tan(fieldOfViewY/2.0F)) * aspectRatio)), 0.0F,                                                    0.0F,                                                                                0.0F,  //0
        0.0F,                                                                  static_cast<GLfloat>(1.0F / (tan(fieldOfViewY/2.0F))),   0.0F,                                                                                0.0F,  //1
        0.0F,                                                                  0.0F,                                                    static_cast<GLfloat>( - (zFarPlane + zNearPlane)/( zFarPlane - zNearPlane) ),        -1.0F, //2
        0.0F,                                                                  0.0F,                                                    static_cast<GLfloat>(- (2 * zFarPlane * zNearPlane) / (zFarPlane - zNearPlane) ),    0.0F   //3
    };

    return mat;
}


// IN GLM IT IS (GLM_DEPTH_CLIP_SPACE == GLM_DEPTH_ZERO_ONE) == FALSE
//static Matrix4GLF buildPerspectiveMatrixGLF(const float& fieldOfViewY, const float& aspectRatio, const float& zNearPlane, const float& zFarPlane)
//{
//    Matrix4GLF mat = {
//        static_cast<GLfloat>(1.0F / ((tan(fieldOfViewY/2.0F)) * aspectRatio)), 0.0F,                                               0.0F,                                                                                0.0F,
//        0.0F,                                                                  static_cast<GLfloat>(1.0F / (tan(fieldOfViewY/2.0F))), 0.0F,                                                                                0.0F,
//        0.0F,                                                                  0.0F,                                               static_cast<GLfloat>(-((zFarPlane + zNearPlane)/(zFarPlane - zNearPlane )) ),        -1.0F,
//        0.0F,                                                                  0.0F,                                               static_cast<GLfloat>(-(( 2.0F * zFarPlane * zNearPlane) / zFarPlane - zNearPlane )), 0.0F
//    };
//
//    return mat;
//}

static Matrix4GLF buildTranslationMatrixGLF(const GLfloat& x, const GLfloat& y, const GLfloat&  z)
{
    //Vector3GLF translationVector = {x, y, z};
    //normalizeVector(translationVector);

    Matrix4GLF mat = {
        mat.me11 = 1.0F, mat.me12 = 0.0F, mat.me13 = 0.0F, mat.me14 = 0.0F,
        mat.me21 = 0.0F, mat.me22 = 1.0F, mat.me23 = 0.0F, mat.me24 = 0.0F,
        mat.me31 = 0.0F, mat.me32 = 0.0F, mat.me33 = 1.0F, mat.me34 = 0.0F,
        //mat.me41 = translationVector.x,    mat.me42 = translationVector.y,    mat.me43 = translationVector.z,    mat.me44 = 1.0F
        mat.me41 = x,    mat.me42 = y,    mat.me43 = z,    mat.me44 = 1.0F
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

static Matrix4GLF buildAllRotationMatrix(const float& p, const float& y, const float& r)
{
    Matrix4GLF mat = {
        mat.me11 = cos(r)*cos(y),                        mat.me12 = sin(r)*cos(y),                             mat.me13 = sin(y),         mat.me14 = 0.0F,
        mat.me21 = sin(r)*cos(p) + cos(r)*sin(y)*sin(p), mat.me22 = cos(r)*cos(p) -(sin(r)*sin(y)*sin(p)),     mat.me23 = -sin(p)*cos(y), mat.me24 = 0.0F,
        mat.me31 = sin(r)*sin(p) - cos(r)*sin(y)*cos(p), mat.me32 = cos(r)*sin(p) + sin(r)*sin(y)*cos(p),      mat.me33 = cos(y)*cos(p),  mat.me34 = 0.0F,
        mat.me41 = 0.0F,                                 mat.me42 = 0.0F,                                      mat.me43 = 0.0F,           mat.me44 = 1.0F,
    };

    return mat;
}

static Matrix4GLF rotationAroundArbitraryAxies(Vector3GLF axisUnitVector, const float& angle)
{
    float c = cos(angle);
    float s = sin(angle);

    //Vector3GLF vectorToNormalize = {axisUnitVector.x, axisUnitVector.y, axisUnitVector.z};
    //normalizeVector(axisUnitVector);
    // lukesawicki !!!!!!!!!!!!!!!!!!!!!!!!!
    //TUTAJ PRACUJE NA ELEMENTACH MACIERZY A W matrix_transform.iml jest mnozenie vektorow ktore sa czescia macierzy przez znormalizowany vector z parametru metody

    //Matrix4GLF mat = {
    //mat.me11 = c+(1.0F - c)*pow(axisUnitVector.x, 2),                           mat.me12 = (1.0F-c)*axisUnitVector.x*axisUnitVector.y - s*axisUnitVector.z, mat.me13 = (1.0F-c)*axisUnitVector.x*axisUnitVector.z + s*axisUnitVector.y, mat.me14 = 0.0F,
    //mat.me21 = (1.0F-c)*axisUnitVector.x*axisUnitVector.y + s*axisUnitVector.z, mat.me22 = c+(1.0F - c)*pow(axisUnitVector.y, 2),                           mat.me23 = (1.0F-c)*axisUnitVector.y*axisUnitVector.z - s*axisUnitVector.x, mat.me24 = 0.0F,
    //mat.me31 = (1.0F-c)*axisUnitVector.x*axisUnitVector.z - s*axisUnitVector.y, mat.me32 = (1.0F-c)*axisUnitVector.y*axisUnitVector.z + s*axisUnitVector.x, mat.me33 = c+(1.0F - c)*pow(axisUnitVector.z, 2),                           mat.me34 = 0.0F,
    //mat.me41 = 0.0F,                                                            mat.me42 = 0.0F,                                                            mat.me43 = 0.0F ,                                                           mat.me44 = 1.0F,
    //};
    
        Matrix4GLF mat = {
    mat.me11 = c+(1.0F - c)*pow(axisUnitVector.x, 2),                           mat.me12 = (1.0F-c)*axisUnitVector.x*axisUnitVector.y + s*axisUnitVector.z, mat.me13 = (1.0F-c)*axisUnitVector.x*axisUnitVector.z - s*axisUnitVector.y, mat.me14 = 0.0F,
    mat.me21 = (1.0F-c)*axisUnitVector.y*axisUnitVector.x - s*axisUnitVector.z, mat.me22 = c+(1.0F - c)*pow(axisUnitVector.y, 2),                           mat.me23 = (1.0F-c)*axisUnitVector.y*axisUnitVector.z + s*axisUnitVector.x, mat.me24 = 0.0F,
    mat.me31 = (1.0F-c)*axisUnitVector.z*axisUnitVector.x + s*axisUnitVector.y, mat.me32 = (1.0F-c)*axisUnitVector.z*axisUnitVector.y - s*axisUnitVector.x, mat.me33 = c+(1.0F - c)*pow(axisUnitVector.z, 2),                           mat.me34 = 0.0F,
    mat.me41 = 0.0F,                                                            mat.me42 = 0.0F,                                                            mat.me43 = 0.0F,                                                            mat.me44 = 1.0F,
    };

    return mat;
}

static Matrix4GLF rotationAroundArbitraryAxiesT(Vector3GLF axisUnitVector, const float& angle)
{
    float c = cos(angle);
    float s = sin(angle);

    //Matrix4GLF mat = {
    //mat.me11 = c+(1.0F - c)*pow(axisUnitVector.x, 2),                           mat.me12 = (1.0F-c)*axisUnitVector.x*axisUnitVector.y - s*axisUnitVector.z, mat.me13 = (1.0F-c)*axisUnitVector.x*axisUnitVector.z + s*axisUnitVector.y, mat.me14 = 0.0F,
    //mat.me21 = (1.0F-c)*axisUnitVector.x*axisUnitVector.y + s*axisUnitVector.z, mat.me22 = c+(1.0F - c)*pow(axisUnitVector.y, 2),                           mat.me23 = (1.0F-c)*axisUnitVector.y*axisUnitVector.z - s*axisUnitVector.x, mat.me24 = 0.0F,
    //mat.me31 = (1.0F-c)*axisUnitVector.x*axisUnitVector.z - s*axisUnitVector.y, mat.me32 = (1.0F-c)*axisUnitVector.y*axisUnitVector.z + s*axisUnitVector.x, mat.me33 = c+(1.0F - c)*pow(axisUnitVector.z, 2),                           mat.me34 = 0.0F,
    //mat.me41 = 0.0F,                                                            mat.me42 = 0.0F,                                                            mat.me43 = 0.0F ,                                                           mat.me44 = 1.0F,
    //};

    Matrix4GLF mat = {
    mat.me11 = c+(1.0F - c)*pow(axisUnitVector.x, 2),                           mat.me12 = (1.0F-c)*axisUnitVector.x*axisUnitVector.y + s*axisUnitVector.z, mat.me13 = (1.0F-c)*axisUnitVector.x*axisUnitVector.z - s*axisUnitVector.y, mat.me14 = 0.0F,
    mat.me21 = (1.0F-c)*axisUnitVector.y*axisUnitVector.x - s*axisUnitVector.z, mat.me22 = c+(1.0F - c)*pow(axisUnitVector.y, 2),                           mat.me23 = (1.0F-c)*axisUnitVector.y*axisUnitVector.z + s*axisUnitVector.x, mat.me24 = 0.0F,
    mat.me31 = (1.0F-c)*axisUnitVector.z*axisUnitVector.x + s*axisUnitVector.y, mat.me32 = (1.0F-c)*axisUnitVector.z*axisUnitVector.y - s*axisUnitVector.x, mat.me33 = c+(1.0F - c)*pow(axisUnitVector.z, 2),                           mat.me34 = 0.0F,
    mat.me41 = 0.0F,                                                            mat.me42 = 0.0F,                                                            mat.me43 = 0.0F,                                                            mat.me44 = 1.0F,
    };

    transpose(mat);
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
static void transpose(Matrix4GLF &mat)
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
