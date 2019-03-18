#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "forward.h"
#include <QVector>
#include <QTimer>
#include <ctime>
#include <QDebug>

namespace Ui {class MainWindow;}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    QTimer timer;
    Camera cam;
    cv::VideoCapture capture = cv::VideoCapture(0);
    cv::CascadeClassifier cascade;
    int sync;

private slots:

    void main_routing()
    {
        double scale = 4;
        cv::Mat original, gray, smallGray;
        capture >> original;

        cvtColor(original, gray, cv::COLOR_BGR2GRAY);

        cv::resize(gray, smallGray, cv::Size(), 1 / scale, 1 / scale, cv::INTER_LINEAR );
        cv::equalizeHist(smallGray, smallGray);

        std::vector< cv::Rect_<int> > faces;
        cascade.detectMultiScale(smallGray, faces,
           1.1,                       // increase search scale by 10% each pass
           3,                         // drop groups of fewer than three detections
           cv::CASCADE_DO_CANNY_PRUNING | cv::CASCADE_FIND_BIGGEST_OBJECT,  // skip regions unlikely to contain a face
           cv::Size(0,0));              // use XML default for smallest search scale


        if(faces.size())
        {
            cv::Rect face = faces[0];
            cv::Point pt1 (face.x + face.width, face.y + face.height);
            cv::Point pt2 (face.x, face.y);
            pt1 *= scale;
            pt2 *= scale;
            cv::rectangle(original, pt1, pt2, cv::Scalar(0,255,0,0),1,8,0);
            vector3d pos = Algorithms::getDistFromFrame(640.0, 60.0 * 3.14159 / 180, pt1.x - 320, pt1.y - 160, pt2.x - 320, pt2.y  - 160, 150.0);

            pos.y -= 110;

            if(!ui->use->isChecked())
            {
                pos.x = 0;
                pos.y = 0;
                pos.z = 500;
            }
            QString str = "Head position: x=" + QString::number(pos.x, 'g',5)
                    + " y=" + QString::number(pos.y, 'g', 5) +
                    + " z=" + QString::number(pos.z, 'g', 5);
            ui->l_headpos->setText(str);

            ui->glport->pos = pos;
        }

        ui->glport->updateGL();



        QImage img((uchar*)original.data, original.cols, original.rows, original.step, QImage::Format_RGB888);
        ui->cvport->setImage(img);
    }
};

#endif // MAINWINDOW_H
