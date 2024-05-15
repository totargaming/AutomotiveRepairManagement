#ifndef TESTADDTOTASK_H
#define TESTADDTOTASK_H

#include <QtTest>
#include "../addtotask.h"
#include "../ui_addtotask.h"
class TestAddToTask : public QObject
{
    Q_OBJECT
public:
    TestAddToTask();
    ~TestAddToTask();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_validateUserInput();
    void test_loadBox();
private:
    AddToTask* addtotask;

};

#endif // TESTADDTOTASK_H
