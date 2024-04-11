QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addtocar.cpp \
    addtostorage.cpp \
    car.cpp \
    customer.cpp \
    entitylist.cpp \
    main.cpp \
    mainwindow.cpp \
    partupdate.cpp \
    removefromcar.cpp \
    removefromcustomer.cpp \
    storage.cpp \
    validation.cpp

HEADERS += \
    SQLheader.h \
    addtocar.h \
    addtostorage.h \
    car.h \
    customer.h \
    entitylist.h \
    mainwindow.h \
    partupdate.h \
    removefromcar.h \
    removefromcustomer.h \
    storage.h \
    validation.h

FORMS += \
    addtocar.ui \
    addtostorage.ui \
    entitylist.ui \
    mainwindow.ui \
    partupdate.ui \
    removefromcar.ui \
    removefromcustomer.ui \
    storage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
