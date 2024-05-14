#ifndef TESTADDTOSTAFF_H
#define TESTADDTOSTAFF_H

#include <QtTest>
#include "../addtostaff.h"
#include "../ui_addtostaff.h"
class TestAddToStaff : public QObject
{
    Q_OBJECT
public:
    TestAddToStaff();
    ~TestAddToStaff();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_validateUserInput();
    void test_reset();
private:
    AddToStaff* addtostaff;
};

#endif // TESTADDTOSTAFF_H
