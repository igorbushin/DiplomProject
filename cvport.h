#ifndef CVPORT_H
#define CVPORT_H

#include <QLabel>
#include "forward.h"

class CVPort : public QLabel
{
    Q_OBJECT
public:
    CVPort(QWidget *parent) : QLabel(parent)
    {
    }
    void setImage(QImage & img)
    {
        this->setPixmap(QPixmap::fromImage(img));
    }

signals:

public slots:

};



#endif // CVPORT_H
