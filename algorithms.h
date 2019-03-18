#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "forward.h"

struct vector3d
{
    vector3d()
    {
        x = y = z = 0;
    }

    vector3d(double _x, double _y, double _z)
    {
        x = _x; y = _y; z = _z;
    }

    double x, y, z;
};

class Algorithms
{
public:
    static vector3d getDistFromFrame(double h_res,
                                   double h_angle,
                                   double xPix1, double yPix1,
                                   double xPix2, double yPix2,
                                   double size_mm)
    {
        double zPix = h_res / 2.0 / tan(h_angle / 2.0);

        double z = zPix * size_mm / fabs(xPix1 - xPix2);
        double x = (xPix1 + xPix2) / 2.0 * z / zPix;
        double y = (yPix1 + yPix2) / 2.0 * z / zPix;
        return vector3d(x, y, z);
    }
};

#endif // ALGORITHMS_H
