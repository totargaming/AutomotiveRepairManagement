#ifndef TESTREMOVEFROMMAINTENANCE_H
#define TESTREMOVEFROMMAINTENANCE_H


#include <QtTest>
#include "../removefrommaintenance.h"
#include "../ui_removefrommaintenance.h"
#include "../SQLheader.h"

class TestRemoveFromMaintenance : public QObject
{
    Q_OBJECT
public:
    TestRemoveFromMaintenance();
    ~TestRemoveFromMaintenance();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_validateUserInput();
    void test_loadBox();
private:
    RemoveFromMaintenance* removefrommaintenance;
};

#endif // TESTREMOVEFROMMAINTENANCE_H
