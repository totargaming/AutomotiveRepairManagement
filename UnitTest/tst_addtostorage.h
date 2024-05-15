#ifndef TESTADDTOSTORAGE_H
#define TESTADDTOSTORAGE_H

#include <QtTest>
#include "../addtostorage.h"
#include "../ui_addtostorage.h"
class TestAddToStorage : public QObject
{
    Q_OBJECT
public:
    TestAddToStorage();
    ~TestAddToStorage();
private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_validateUserInput();
    void test_reset();
private:
    addToStorage* addtostorage;
};

#endif // TESTADDTOSTORAGE_H
