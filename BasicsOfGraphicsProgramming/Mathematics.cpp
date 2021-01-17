struct FloatVector
{
    float x;
    float y;

    FloatVector(float x, float y)
    {
        this->x = x;
        this->y = y;
    }

    FloatVector(const FloatVector& vector) 
    {
        this->x = vector.x;
        this->y = vector.y;
    }

} FloatVector;

struct IntegerVector
{
    int x;
    int y;

    IntegerVector(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    IntegerVector(const IntegerVector& vector)
    {
        this->x = vector.x;
        this->y = vector.y;
    }
} IntegerVector;
