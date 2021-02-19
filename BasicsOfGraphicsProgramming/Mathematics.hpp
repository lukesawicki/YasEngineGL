#ifndef MATHEMATICS_HPP
#define MATHEMATICS_HPP



template <typename T>
int signum(T a)
{
    if(a > 0)
    {
        return 1;
    }
    else
    {
        if(a < 0)
        {
            return -1;
        }
    }
    return 0;
};

template <typename Type>
class Vector2D
{
    public:
        Type x;
        Type y;
    Vector2D(Type x, Type y)
    {
        this->x = x;
        this->y = y;
    }
};

#include<cmath>


//-----------------------------------------------------------------------------|---------------------------------------|
//                                                                            80                                     120

// About coordinates: Left handed and Right handed:
// From website:
// https://www.scratchapixel.com/lessons/mathematics-physics-for-computer-graphics/geometry/coordinate-systems
//It is also critically important to know which convention is used for the coordinate system when dealing with a
//renderer or any other 3D application. At present, the standard in the industry tends to be the right-hand XYZ
//coordinate system where x points to the right, y is up and z is outward (coming out of the screen).
//Programs and 3D APIs such as Maya and OpenGL use a right-hand coordinate system, while DirectX, pbrt and PRMan
//use a left-hand coordinate system. Note that both Maya and PRMan use a coordinate system in which the up vector
//is called the y-axis and the forward vector is called the z-axis. Essentially, this means that the z-coordinate
//of 3 for a point in one system is -3 in the other. For this reason, we potentially need to reverse the sign of
//an object's z-coordinates when the geometry is exported to the renderer. The choice of coordinate system handedness
//also plays a critical role when it comes to rotation and the cross product of two vectors. We will talk about this
//more in the next few chapters. It's actually easy enough (but painful) to go from one coordinate system to another.
//All that is needed is to scale the point coordinates and the camera-to-world matrix by (1, 1, -1).


//https://www.scratchapixel.com/lessons/3d-basic-rendering/perspective-and-orthographic-projection-matrix
//Remember that they are essentially two conventions when it comes to NDC space. Coordinates are either considered to be defined in the range [-1, 1]. This is the case of most real-time graphics APIs such as OpenGL or Direct3D. Or they can also be defined in the range [0, 1]. The RenderMan specifications define them that way. You are entirely free to choose the convention you prefer. We will stick to the convention used by graphics API because this is essentially within this context that you will see these matrices being used.

// In OpenGL matrices are defined using column major order but it is strange that in perspective matrix it uses row major


struct Vector3GLF {
    float vc0;
    float vc1;
    float vc2;
    Vector3GLF(float vc0, float vc1, float vc2)
    {
        this->vc0 = vc0;
        this->vc1 = vc1;
        this->vc2 = vc2;
    }
} typedef Vector3F, Vec3GLF;


struct Vector4GLF {
    float vc0;
    float vc1;
    float vc2;
    float vc3;

    Vector4GLF()
    {
        this->vc0=0.0F;
        this->vc1=0.0F;
        this->vc2=0.0F;
        this->vc3=1.0F;
    }

    Vector4GLF(float vc0, float vc1, float vc2, float vc3)
    {
        this->vc0 = vc0;
        this->vc1 = vc1;
        this->vc2 = vc2;
        this->vc3 = vc3;
    }

    Vector4GLF(const Vector3GLF& vector3glf)
    {
        this->vc0 = vector3glf.vc0;
        this->vc1 = vector3glf.vc1;
        this->vc2 = vector3glf.vc2;
        this->vc3 = 1;
    }

} typedef Vector4F, Vec4GLF;

struct Matrix4GLF {
    float me00=1.0F, me01=0.0F, me02=0.0F, me03=0.0F;
    float me10=0.0F, me11=1.0F, me12=0.0F, me13=0.0F;
    float me20=0.0F, me21=0.0F, me22=1.0F, me23=0.0F;
    float me30=0.0F, me31=0.0F, me32=0.0F, me33=1.0F;

} typedef Mat4GLF;

static void normalizeVector(Vector3GLF& vector);
static float getVectorMagnitude(const Vector3GLF& vector);

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

//OpenGL Right Handed Coordination System and thata are
// In OpenGL default matrices order are column-major(column vectors);
// from OpenGL 4.x you can change that and this matrix below is ****row-major****
// IN GLM IT IS (GLM_DEPTH_CLIP_SPACE == GLM_DEPTH_ZERO_ONE) == false
//ROW MAJOR
static Matrix4GLF buildPerspectiveMatrixGLF(const float& fieldOfViewY, const float& aspectRatio, const float& zNearPlane, const float& zFarPlane)
{
    Matrix4GLF mat = {
        static_cast<float>(1.0F / ((tan(fieldOfViewY/2.0F)) * aspectRatio)), 0.0F,                                                    0.0F,                                                                                0.0F,  //0
        0.0F,                                                                  static_cast<float>(1.0F / (tan(fieldOfViewY/2.0F))),   0.0F,                                                                                0.0F,  //1
        0.0F,                                                                  0.0F,                                                    static_cast<float>( - (zFarPlane + zNearPlane)/( zFarPlane - zNearPlane) ),        -1.0F, //2
        0.0F,                                                                  0.0F,                                                    static_cast<float>(- (2 * zFarPlane * zNearPlane) / (zFarPlane - zNearPlane) ),    0.0F   //3
    };
    return mat;
}

//ROW MAJOR
static Matrix4GLF buildTranslationMatrixRowMajorGLFloat(const Vector3GLF& vector)
{
    Matrix4GLF mat = {
        mat.me00 = 1.0F, mat.me01 = 0.0F, mat.me02 = 0.0F, mat.me03 = 0.0F,
        mat.me10 = 0.0F, mat.me11 = 1.0F, mat.me12 = 0.0F, mat.me13 = 0.0F,
        mat.me20 = 0.0F, mat.me21 = 0.0F, mat.me22 = 1.0F, mat.me23 = 0.0F,
        mat.me30 = vector.vc0,    mat.me31 = vector.vc1,    mat.me32 = vector.vc2,    mat.me33 = 1.0F
    };

    return mat;
}

float getVectorMagnitude(const Vector3GLF& vector)
{
    return sqrt(pow(vector.vc0, 2) + pow(vector.vc1, 2) + pow(vector.vc2, 2));
}

void normalizeVector(Vector3GLF& vector)
{
    float vectorMagnitude = getVectorMagnitude(vector);
    vector.vc0 = vector.vc0 / vectorMagnitude;
    vector.vc1 = vector.vc1 / vectorMagnitude;
    vector.vc2 = vector.vc2 / vectorMagnitude;
}


static Matrix4GLF buildAllRotationMatrix(const float& p, const float& vc1, const float& r)
{
    Matrix4GLF mat = {
        mat.me00 = cos(r)*cos(vc1),                        mat.me01 = sin(r)*cos(vc1),                             mat.me02 = sin(vc1),         mat.me03 = 0.0F,
        mat.me10 = sin(r)*cos(p) + cos(r)*sin(vc1)*sin(p), mat.me11 = cos(r)*cos(p) -(sin(r)*sin(vc1)*sin(p)),     mat.me12 = -sin(p)*cos(vc1), mat.me13 = 0.0F,
        mat.me20 = sin(r)*sin(p) - cos(r)*sin(vc1)*cos(p), mat.me21 = cos(r)*sin(p) + sin(r)*sin(vc1)*cos(p),      mat.me22 = cos(vc1)*cos(p),  mat.me23 = 0.0F,
        mat.me30 = 0.0F,                                 mat.me31 = 0.0F,                                      mat.me32 = 0.0F,           mat.me33 = 1.0F,
    };

    return mat;
}

// ???????? MAJOR
static Matrix4GLF rotationAroundArbitraryAxies(Vector3GLF axisVector, const float& angle)
{
    float c = cos(angle);
    float s = sin(angle);
    
    normalizeVector(axisVector);

    //Matrix4GLF mat =
    //{
    //    mat.me00 = c+((1.0F - c)*axisVector.vc0)* axisVector.vc0,               mat.me01 = ((1.0F-c)*axisVector.vc0)*axisVector.vc1 + s*axisVector.vc2, mat.me02 = ((1.0F-c)*axisVector.vc0)*axisVector.vc2 - s*axisVector.vc1, mat.me03 = 0.0F,
    //    mat.me10 = ((1.0F-c)*axisVector.vc1)*axisVector.vc0 - s*axisVector.vc2, mat.me11 = c+((1.0F - c)*axisVector.vc1)*axisVector.vc1,                mat.me12 = ((1.0F-c)*axisVector.vc1)*axisVector.vc2 + s*axisVector.vc0, mat.me13 = 0.0F,
    //    mat.me20 = ((1.0F-c)*axisVector.vc2)*axisVector.vc0 + s*axisVector.vc1, mat.me21 = ((1.0F-c)*axisVector.vc2)*axisVector.vc1 - s*axisVector.vc0, mat.me22 = c+((1.0F - c)*axisVector.vc2)*axisVector.vc2,                mat.me23 = 0.0F,
    //    mat.me30 = 0.0F,                                                        mat.me31 = 0.0F,                                                        mat.me32 = 0.0F,                                                        mat.me33 = 1.0F,
    //};

    Matrix4GLF mat =
    {
        mat.me00 = c+((1.0F - c)*axisVector.vc0)* axisVector.vc0,               mat.me01 = ((1.0F-c)*axisVector.vc0)*axisVector.vc1 - s*axisVector.vc2, mat.me02 = ((1.0F-c)*axisVector.vc0)*axisVector.vc2 + s*axisVector.vc1, mat.me03 = 0.0F,
        mat.me10 = ((1.0F-c)*axisVector.vc1)*axisVector.vc0 + s*axisVector.vc2, mat.me11 = c+((1.0F - c)*axisVector.vc1)*axisVector.vc1,                mat.me12 = ((1.0F-c)*axisVector.vc1)*axisVector.vc2 - s*axisVector.vc0, mat.me13 = 0.0F,
        mat.me20 = ((1.0F-c)*axisVector.vc2)*axisVector.vc0 - s*axisVector.vc1, mat.me21 = ((1.0F-c)*axisVector.vc2)*axisVector.vc1 + s*axisVector.vc0, mat.me22 = c+((1.0F - c)*axisVector.vc2)*axisVector.vc2,                mat.me23 = 0.0F,
        mat.me30 = 0.0F,                                                        mat.me31 = 0.0F,                                                        mat.me32 = 0.0F,                                                        mat.me33 = 1.0F,
    };

    return mat;
}

static Vector4GLF vectorMultiplyedByMatrix(Vector4GLF vector4glf, Matrix4GLF mat)
{
    return Vector4GLF
    (
        vector4glf.vc0 * mat.me00 + vector4glf.vc1 * mat.me10 + vector4glf.vc2 * mat.me20 + vector4glf.vc3 * mat.me30,
        vector4glf.vc0 * mat.me01 + vector4glf.vc1 * mat.me11 + vector4glf.vc2 * mat.me21 + vector4glf.vc3 * mat.me31,
        vector4glf.vc0 * mat.me02 + vector4glf.vc1 * mat.me12 + vector4glf.vc2 * mat.me22 + vector4glf.vc3 * mat.me32,
        vector4glf.vc0 * mat.me03 + vector4glf.vc1 * mat.me13 + vector4glf.vc2 * mat.me23 + vector4glf.vc3 * mat.me33
    );
}

static Vector4GLF matrixMultiplyedByVector(Matrix4GLF mat, Vector4GLF vector4glf)
{
    return Vector4GLF
    (
        mat.me00 * vector4glf.vc0 + mat.me01 * vector4glf.vc1 + mat.me02 * vector4glf.vc2 + mat.me03 * vector4glf.vc3,
        mat.me10 * vector4glf.vc0 + mat.me11 * vector4glf.vc1 + mat.me12 * vector4glf.vc2 + mat.me13 * vector4glf.vc3,
        mat.me20 * vector4glf.vc0 + mat.me21 * vector4glf.vc1 + mat.me22 * vector4glf.vc2 + mat.me23 * vector4glf.vc3,
        mat.me30 * vector4glf.vc0 + mat.me31 * vector4glf.vc1 + mat.me32 * vector4glf.vc2 + mat.me33 * vector4glf.vc3
    );

}

Vector2D<float>* toWindowCoordinates(float x, float y, int windowWidth, int windowHeight) {
    return new Vector2D<float>(x + (windowWidth/2.0F), (windowHeight/2.0F) - y );
}

#endif
