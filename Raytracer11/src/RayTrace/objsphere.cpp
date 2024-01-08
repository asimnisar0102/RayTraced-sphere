#include "objsphere.hpp"
#include <cmath>

//default constructor
RT::ObjSphere::ObjSphere()
{

}

//destructor
RT::ObjSphere::~ObjSphere()
{

}

//test for intersections
bool RT:: ObjSphere::TestIntersections(const RT::Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor)
{
    //compute values a b c
    qbVector<double> vhat = castRay.m_lab;
    vhat.Normalize();

    // a = (|direction cast ray|)^2 = unit vector = 1

    //compute b
    double b = 2.0*qbVector<double>::dot(castRay.m_point1, vhat);

    //compute c
    double c = qbVector<double>::dot(castRay.m_point1, castRay.m_point1) - 1.0;

    //test intersection
    double intTest = (b*b) - 4.0 * c;

    if (intTest > 0.0)
    {
        double numSQRT = sqrtf(intTest); //sqrt of numerator for quadratic eqn
        double t1 = (-b +numSQRT) / 2.0;
        double t2 = (-b -numSQRT) / 2.0;

        //if t1 or t2 -ve, ignore bc behind camera

        if((t1<0.0) || (t2 < 0.0))
        {
             return false;
        }
        else
        {
            //determine which poi closest to camera
            if (t1<t2)
            {
                intPoint = castRay.m_point1 + (vhat * t1);
            }
            else
            {
                intPoint = castRay.m_point1 + (vhat*t2);
            }
        }

        return true;
    }
    else
    {
        return false;
    }
}
