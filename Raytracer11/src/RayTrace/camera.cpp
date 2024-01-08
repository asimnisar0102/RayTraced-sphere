#include "camera.hpp"
#include "ray.hpp"
#include <math.h>

RT::Camera::Camera()
{
    //default constructor
    m_cameraPosition = qbVector<double> {std::vector<double> {0.0, -10.0,0.0}};
    m_cameraLookAt = qbVector<double> {std::vector<double> {0.0, 0.0,0.0}};
    m_cameraUp = qbVector<double> {std::vector<double> {0.0, 0.0,1.0}};
    m_cameraLength = 1.0;
    m_cameraHorzSize = 1.0;
    m_cameraAspectRatio = 1.0;
    
}

void RT::Camera::SetPosition(const qbVector<double> &newPosition)
{
    m_cameraPosition = newPosition;
}

void RT::Camera::SetLookAt(const qbVector<double> &newLookAt)
{
    m_cameraLookAt = newLookAt;
}

void RT::Camera::SetUp(const qbVector<double> &upVector)
{
    m_cameraUp = upVector;
}

void RT::Camera::SetLength(double newLength)
{
    m_cameraLength = newLength;
}

void RT::Camera::setHorzSize(double newHorzSize)
{
    m_cameraHorzSize = newHorzSize;
}

void RT::Camera::SetAspect(double newAspect)
{
    m_cameraAspectRatio = newAspect;
}

//return pos of camera

qbVector<double> RT::Camera::GetPosition()
{
    return m_cameraPosition;
}

//return LookAt of camera

qbVector<double> RT::Camera::GetLookAt()
{
    return m_cameraLookAt;
}

//return up vector

qbVector<double> RT::Camera::GetUp()
{
    return m_cameraUp;
}

//return length of cam

double RT::Camera::GetLength()
{
    return m_cameraLength;
}

//return horizontal size

double RT::Camera::GetHorzSize()
{
    return m_cameraHorzSize;
}

//return aspect ration of cam

double RT::Camera::GetAspect()
{
    return m_cameraAspectRatio;
}


//return u vector

qbVector<double> RT::Camera::GetU()
{
    return m_projectionScreenU;
}

qbVector<double> RT::Camera::GetV()
{
    return m_projectionScreenV;
}

//return projection screen cent

qbVector<double> RT::Camera::GetScreenCentre()
{
    return m_projectionScreenCentre;
}

//FUNCION FOR CAMERA GEOMETRY

void RT::Camera::UpdateCameraGeometry()
{
    //compute vector from camera pos to lookat pos
    m_alignmentVector = m_cameraLookAt - m_cameraPosition;
    m_alignmentVector.Normalize();

    //compute u and v vectors
    m_projectionScreenU = qbVector<double>::cross(m_alignmentVector, m_cameraUp);
    m_projectionScreenU.Normalize();
    m_projectionScreenV = qbVector<double>::cross(m_projectionScreenU, m_alignmentVector);
    m_projectionScreenV.Normalize();

    //compute pos of centre point of screen

    m_projectionScreenCentre = m_cameraPosition + (m_cameraLength * m_alignmentVector);

    //modify u/v vectors to match aspect ratio

    m_projectionScreenU = m_projectionScreenU * m_cameraHorzSize;
    m_projectionScreenV = m_projectionScreenV * (m_cameraHorzSize / m_cameraAspectRatio);
}

bool RT::Camera::GenerateRay(float proScreenX, float proScreenY, RT::Ray &cameraRay)
{
    //compute location of screen point in coords (u-v to xyz coords)
    qbVector<double> screenWorldPart1 = m_projectionScreenCentre + (m_projectionScreenU * proScreenX);
    qbVector<double> screenWorldCoordinate = screenWorldPart1 + (m_projectionScreenV * proScreenY);

    //compute ray using this point and camera position
    cameraRay.m_point1 = m_cameraPosition;
    cameraRay.m_point2 = screenWorldCoordinate;
    cameraRay.m_lab = screenWorldCoordinate - m_cameraPosition;
    
    return true;
}