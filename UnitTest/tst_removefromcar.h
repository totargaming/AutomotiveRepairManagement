#ifndef TESTREMOVEFROMCAR_H
#define TESTREMOVEFROMCAR_H

#include <QtTest>

// add necessary includes here

class TestRemoveFromCar : public QObject
{
    Q_OBJECT

public:
    TestRemoveFromCar();
    ~TestRemoveFromCar();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

};
#endif // TSTREMOVEFROMCAR_H
