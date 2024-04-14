QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addtocar.cpp \
    addtomaintenance.cpp \
    addtostaff.cpp \
    addtostorage.cpp \
    addtotask.cpp \
    car.cpp \
    customer.cpp \
    deliverytask.cpp \
    entitylist.cpp \
    main.cpp \
    maintenance.cpp \
    maintenancetask.cpp \
    mainwindow.cpp \
    partupdate.cpp \
    removefromcar.cpp \
    removefromcustomer.cpp \
    removefrommaintenance.cpp \
    removefromstaff.cpp \
    staff.cpp \
    storage.cpp \
    tasklist.cpp \
    validation.cpp

HEADERS += \
    SQLheader.h \
    addtocar.h \
    addtomaintenance.h \
    addtostaff.h \
    addtostorage.h \
    addtotask.h \
    car.h \
    customer.h \
    deliverytask.h \
    entitylist.h \
    maintenance.h \
    maintenancetask.h \
    mainwindow.h \
    partupdate.h \
    removefromcar.h \
    removefromcustomer.h \
    removefrommaintenance.h \
    removefromstaff.h \
    staff.h \
    storage.h \
    tasklist.h \
    validation.h

FORMS += \
    addtocar.ui \
    addtomaintenance.ui \
    addtostaff.ui \
    addtostorage.ui \
    addtotask.ui \
    entitylist.ui \
    maintenance.ui \
    mainwindow.ui \
    partupdate.ui \
    removefromcar.ui \
    removefromcustomer.ui \
    removefrommaintenance.ui \
    removefromstaff.ui \
    storage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
