#ifndef CAMERA_H
#define CAMERA_H

#include "forward.h"

class Camera
{

public:
    Camera()
    {
        h_angle = 60;
        h_resolution = 640;
        w_resolution = 320;
    }

private:
    double h_angle;
    double h_resolution;
    double w_resolution;
};

#endif // CAMERA_H
