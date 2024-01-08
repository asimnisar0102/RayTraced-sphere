#include "objectbase.hpp"
#include <math.h>

#define EPSILON 1e-21f

//default constructor

RT::ObjectBase::ObjectBase()
{

}

//destructor
RT::ObjectBase::~ObjectBase()
{

}

//test intersections
bool RT::ObjectBase::TestIntersections(const Ray & castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor)
{
    return false;
}

//test if two floats are close
bool RT::ObjectBase::CloseEnough(const double f1, const double f2)
{
    return fabs(f1-f2) < EPSILON;
}