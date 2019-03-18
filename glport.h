#ifndef GLPORT_H
#define GLPORT_H

#include "forward.h"
#include <QGLWidget>
#include <GL/glu.h>
#include <glut.h>

class GLPort : public QGLWidget
{
    Q_OBJECT
public:
    GLPort(QWidget *parent) : QGLWidget(parent)
    {
        hor_resolution_global = 1366;
        ver_resolution_global = 768;
        width_mm = 340;
        height_mm = 195;
    }

    void initializeGL()
    {
        glClearColor(0.2, 0.2, 0.2, 1);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHTING);
        glEnable(GL_COLOR_MATERIAL );
    }

    void paintGL()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        GLdouble aspect = ver_resolution / hor_resolution;

        double k1 = ver_resolution / ver_resolution_global;
        double k2 = hor_resolution / hor_resolution_global;

        pos.x = -pos.x;
        pos.y = -pos.y;

        double left = (k2 * -width_mm / 2 - pos.x)/pos.z;
        double right = (k2 * width_mm / 2 - pos.x)/pos.z;
        double top = (k1 * -height_mm / 2 - pos.y)/pos.z;
        double bottom = (k1 * height_mm / 2 - pos.y)/pos.z;
        double _near = pos.z/pos.z;

        glFrustum(left, right, top, bottom, _near, 100000.0);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        gluLookAt(pos.x, pos.y, pos.z, pos.x, pos.y, 0, 0, 1, 0);

        glColor3f(1, 0.6, 0);
        glTranslatef(0, 0, 0);
        glutSolidTeapot(50);
    }

    void resizeGL(int w, int h)
    {
        glViewport(0, 0, w, h);
        ver_resolution = h;
        hor_resolution = w;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }

signals:

public:
    vector3d pos;

private:
    double hor_resolution_global;
    double ver_resolution_global;
    double ver_resolution;
    double hor_resolution;
    double width_mm;
    double height_mm;

};

#endif // GLPORT_H
