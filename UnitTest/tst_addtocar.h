#ifndef TESTADDTOCAR_H
#define TESTADDTOCAR_H

#include <QtTest>
#include "../addtocar.h"
#include "../ui_addtocar.h"
class TestAddToCar : public QObject
{
    Q_OBJECT

public:
    TestAddToCar();
    ~TestAddToCar();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_validateUserInput();
    void test_reset();

private:
    AddToCar* addtocar;
};

#endif // TESTADDTOCAR_H
