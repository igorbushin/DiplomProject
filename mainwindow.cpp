#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    sync = 0;
    ui->setupUi(this);
    connect(&timer, SIGNAL(timeout()), this, SLOT(main_routing()));
    const char* cascade_name_alt2 = "haarcascade_frontalface_alt2.xml";
    cascade.load(cascade_name_alt2);
    timer.start(100);
}

MainWindow::~MainWindow()
{
    delete ui;
}

