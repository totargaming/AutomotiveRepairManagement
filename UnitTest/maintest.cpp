#include <QtTest>
#include <QApplication> // Include QApplication
#include "tst_addtocar.h"
#include "tst_removefromcar.h"
#include "tst_addtostaff.h" // Include the AddToStaff test header file
#include "tst_addtomaintenance.h"
#include "tst_addtostorage.h"
#include "tst_addtotask.h"
#include "tst_removefromcustomer.h"
#include "tst_removefrommaintenance.h"
#include "../SQLheader.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv); // Create QApplication

    int status = 0;
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE", "DB");
    // Set the database name (i.e., the path to the database file).
    database.setDatabaseName("E:\\Workspace\\AutomotiveRepairManagement\\database.db");
    // Try to open the database.
    if(!database.open()){
        // If the database fails to open, output a debug message and return from the constructor.
        qDebug() << "Maintest: Error: Unable to open database..";
    }
    else{
        // If the database opens successfully, output a debug message.
        qDebug() << "Maintest: Database open successfully..";
    }
    TestAddToCar addCarTest;
    status |= QTest::qExec(&addCarTest, argc, argv);

    TestRemoveFromCar removeCarTest;
    status |= QTest::qExec(&removeCarTest, argc, argv);

    TestAddToStaff addStaffTest; // Create an instance of TestAddToStaff
    status |= QTest::qExec(&addStaffTest, argc, argv); // Run the AddToStaff test

    TestAddToMaintenance addMaintenanceTest;
    status |= QTest::qExec(&addMaintenanceTest, argc, argv);

    TestAddToStorage addStorageTest;
    status |= QTest::qExec(&addStorageTest, argc, argv);

    TestAddToTask addTaskTest;
    status |= QTest::qExec(&addTaskTest, argc, argv);

    TestRemoveFromCustomer removeCustomerTest;
    status |= QTest::qExec(&removeCustomerTest, argc, argv);

    TestRemoveFromMaintenance removeMaintenanceTest;
    status |= QTest::qExec(&removeMaintenanceTest, argc, argv);

    return status;
}
