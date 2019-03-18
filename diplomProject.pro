#-------------------------------------------------
#
# Project created by QtCreator 2013-06-05T14:58:49
#
#-------------------------------------------------

QT       += core gui opengl widgets

TARGET = diplom_project
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += \
    mainwindow.h \
    cvport.h \
    forward.h \
    camera.h \
    algorithms.h \
    glport.h

FORMS    += mainwindow.ui

INCLUDEPATH += $$(GLUT)/include
INCLUDEPATH += $$(OPENCV)/include

LIBS += -L$$(OPENCV)/lib
LIBS += -lopencv_core400
LIBS += -lopencv_imgproc400
LIBS += -lopencv_objdetect400
LIBS += -lopencv_videoio400

LIBS += -lopengl32
LIBS += -lglu32
LIBS += -L$$(GLUT)/lib
LIBS += -lglut32

cascades.path = $${OUT_PWD}
cascades.files += haarcascade_frontalface/haarcascade_frontalface_alt2.xml
INSTALLS += cascades
