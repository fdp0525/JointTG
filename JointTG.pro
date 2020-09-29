DESTDIR += ./bin
OBJECTS_DIR += ./tmp

QMAKE_CXXFLAGS += -std=gnu++11
QMAKE_CXXFLAGS+= -fopenmp
QMAKE_LFLAGS +=  -fopenmp

INCLUDEPATH += ./Open3D
SOURCES += \
    main.cpp

HEADERS += \
    Open3D.h \
    jointtgconfig.h

INCLUDEPATH += /usr/include/eigen3 /usr/local/include
INCLUDEPATH += /usr/local/include/opencv
LIBS +=  -lopencv_calib3d -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_highgui -lopencv_imgproc -lopencv_ml -lopencv_objdetect -lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_video -lopencv_videostab
LIBS += -lGL -lGLEW -lglfw -lz
LIBS += -lboost_system -lboost_filesystem
LIBS += -lflann

LIBS += -L$$PWD/lib -lJointTexGeo
