#ifndef TESTREMOVEFROMSTAFF_H
#define TESTREMOVEFROMSTAFF_H

#include <QtTest>
#include "../removefromstaff.h"
#include "../ui_removefromstaff.h"
#include "../SQLheader.h"
class TestRemoveFromStaff : public QObject
{
    Q_OBJECT
public:
    TestRemoveFromStaff();
    ~TestRemoveFromStaff();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_validateUserInput();
    void test_loadBox();
private:
    RemoveFromStaff* removefromstaff;
};

#endif // TESTREMOVEFROMSTAFF_H
