#ifndef TESTREMOVEFROMCAR_H
#define TESTREMOVEFROMCAR_H

#include <QtTest>
#include "../removefromcar.h"
#include "../ui_removefromcar.h"
#include "../SQLheader.h"
class TestRemoveFromCar : public QObject
{
    Q_OBJECT

public:
    TestRemoveFromCar();
    ~TestRemoveFromCar();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_validateUserInput();
    void test_loadBox();

private:
    RemoveFromCar *removeFromCar;
};

#endif // TESTREMOVEFROMCAR_H
