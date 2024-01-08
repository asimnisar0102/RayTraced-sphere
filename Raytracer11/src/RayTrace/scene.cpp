#include "scene.hpp"

//constructor

RT::Scene::Scene()
{
    //config camera
    m_camera.SetPosition(qbVector<double>{std::vector<double> {0.0,-10.0,0.0}});
    m_camera.SetLookAt(qbVector<double>{std::vector<double> {0.0,0.0,0.0}});
    m_camera.SetUp(qbVector<double>{std::vector<double> {0.0,0.0,1.0}});
    m_camera.setHorzSize(0.25);
    m_camera.SetAspect(16.0/9.0);
    m_camera.UpdateCameraGeometry();

}

//performing rendering

bool RT::Scene::Render(image &outputImage)
{
    //get dim of output img

    int xSize = outputImage.GetXSize();
    int ySize = outputImage.GetYSize();

    //loop each pixel in img
    RT::Ray cameraRay;
    qbVector<double> intPoint (3);
    qbVector<double> localNormal (3);
    qbVector<double> localColor (3);
    double xFact = 1.0 / static_cast<double>(xSize / 2.0);
    double yFact = 1.0 / static_cast<double>(ySize / 2.0);
    double minDist = 1e6;
    double maxDist = 0.0;

    for(int x=0; x<xSize; ++x)
    {
        for(int y=0; y<ySize; ++y)
        {
            //normalize coords
            double normX = (static_cast<double>(x) * xFact) - 1.0;
            double normY = (static_cast<double>(y) * yFact) - 1.0;

            //gen ray for pixel
            m_camera.GenerateRay(normX, normY, cameraRay);

            //test if intersection is valid
            bool validInt = m_testSphere.TestIntersections(cameraRay, intPoint, localNormal, localColor);

            //if int valid, change pixel colour 
            if(validInt)
            {
                //compute distance b/w cam and poi
                double dist = (intPoint - cameraRay.m_point1).norm();
                if (dist > maxDist)
                {
                    maxDist = dist;
                }
                if(dist < minDist)
                {
                    minDist = dist;
                }

                outputImage.SetPixel(x,y,255.0-((dist-9.0)/0.94605)*255.0,0.0,0.0);

                //closest value to cam is 9 units, minimum dist  will be 0
            }
            else
            {
                outputImage.SetPixel(x,y,0.0,0.0,0.0);
            }
        }
    }

    std::cout << "Minimum distance = " <<minDist << std::endl;
    std::cout << "Maximum distance = " << maxDist << std::endl;
  
    return true;
}