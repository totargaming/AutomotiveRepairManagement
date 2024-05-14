QT += testlib core gui widgets sql
# QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_addtocar.cpp \
    maintest.cpp \
    tst_addtomaintenance.cpp \
    tst_addtostaff.cpp \
    tst_removefromcar.cpp\
    ../addtocar.cpp\
    ../validation.cpp\
    ../addtostaff.cpp\
    ../removefromcar.cpp\
    ../addtomaintenance.cpp\

HEADERS += \
    tst_addtocar.h \
    tst_addtomaintenance.h \
    tst_addtostaff.h \
    tst_removefromcar.h\
    ../addtocar.h\
    ../validation\
    ../addtostaff.h\
    ../removefromcar.h\
    ../SQLheader.h\
    ../addtomaintenance.h\

