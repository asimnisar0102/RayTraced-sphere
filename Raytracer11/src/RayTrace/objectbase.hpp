#ifndef OBJECTBASE_H
#define OBJECTBASE_H

#include "qbLinAlg/qbVector.h"
#include "ray.hpp"

namespace RT
{
    class ObjectBase
    {
        public:
            //constructor default
            ObjectBase();

            //destructor
            virtual ~ObjectBase(); //verify why virtual

            //function to test for intersections
            virtual bool TestIntersections(const Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor);

            //test whether two floats are close to equal (plus minus something)
            bool CloseEnough(const double f1, const double f2);

        //public member variables

        public:
            //base colour of obj
            qbVector<double> m_baseColor {3};
    };
}

#endif