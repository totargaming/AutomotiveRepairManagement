#ifndef TESTREMOVEFROMCUSTOMER_H
#define TESTREMOVEFROMCUSTOMER_H

#include <QtTest>
#include "../removefromcustomer.h"
#include "../ui_removefromcustomer.h"
#include "../SQLheader.h"

class TestRemoveFromCustomer : public QObject
{
    Q_OBJECT
public:
    TestRemoveFromCustomer();
    ~TestRemoveFromCustomer();

private slots:

    void initTestCase();
    void cleanupTestCase();
    void test_validateUserInput();
    void test_loadBox();

private:
    RemoveFromCustomer *removefromcustomer;
};

#endif // TESTREMOVEFROMCUSTOMER_H
