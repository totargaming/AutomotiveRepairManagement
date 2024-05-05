#include <QtTest>
#include <QApplication> // Include QApplication
#include "tst_addtocar.h"
#include "tst_removefromcar.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv); // Create QApplication

    int status = 0;

    TestAddToCar addTest;
    status |= QTest::qExec(&addTest, argc, argv);

    // RemoveFromCar removeTest;
    // status |= QTest::qExec(&removeTest, argc, argv);

    return status;
}
