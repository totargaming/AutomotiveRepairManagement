#ifndef TESTADDTOMAINTENANCE_H
#define TESTADDTOMAINTENANCE_H
#include <QtTest>
#include "../addtomaintenance.h"
#include "../ui_addtomaintenance.h"
class TestAddToMaintenance : public QObject
{
    Q_OBJECT
public:
    TestAddToMaintenance();
    ~TestAddToMaintenance();
private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_validateUserInput();
    void test_loadBox();
private:
    AddToMaintenance* addtomaintenance;
};

#endif // TESTADDTOMAINTENANCE_H
