QT += testlib core gui widgets sql
# QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_addtocar.cpp \
    maintest.cpp \
    tst_addtomaintenance.cpp \
    tst_addtostaff.cpp \
    tst_addtostorage.cpp \
    tst_addtotask.cpp \
    tst_removefromcar.cpp\
    ../addtocar.cpp\
    ../validation.cpp\
    ../addtostaff.cpp\
    ../removefromcar.cpp\
    ../addtomaintenance.cpp\
    ../addtostorage.cpp\
    ../addtotask.cpp\
    ../removefromcustomer.cpp\
    tst_removefromcustomer.cpp\
    ../removefrommaintenance.cpp\
    tst_removefrommaintenance.cpp\
    ../removefromstaff.cpp\
    tst_removefromstaff.cpp

HEADERS += \
    tst_addtocar.h \
    tst_addtomaintenance.h \
    tst_addtostaff.h \
    tst_addtostorage.h \
    tst_addtotask.h \
    tst_removefromcar.h\
    ../addtocar.h\
    ../validation\
    ../addtostaff.h\
    ../removefromcar.h\
    ../SQLheader.h\
    ../addtomaintenance.h\
    ../addtostorage.h\
    ../addtotask.h\
    ../removefromcustomer.h\
    tst_removefromcustomer.h \
    tst_removefrommaintenance.h\
    ../removefrommaintenance.h\
    ../removefromstaff.h\
    tst_removefromstaff.h
