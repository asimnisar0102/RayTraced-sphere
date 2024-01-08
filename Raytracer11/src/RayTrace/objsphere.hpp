#ifndef OBJSPHERE_H
#define OBJSPHERE_H

#include "objectbase.hpp"

namespace RT
{
    class ObjSphere : public ObjectBase
    {
        public:
            //default constructor, defines unit sphere at origin
            ObjSphere();

            //override destructor
            virtual ~ObjSphere() override;

            //override function to test for intersections
            virtual bool TestIntersections(const RT::Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor);

        private:
            

    };
}


#endif