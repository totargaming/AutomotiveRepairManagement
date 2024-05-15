#include "tst_removefromstaff.h"

TestRemoveFromStaff::TestRemoveFromStaff() {
    removefromstaff = new RemoveFromStaff();
}
TestRemoveFromStaff::~TestRemoveFromStaff() {
    delete removefromstaff;
}
void TestRemoveFromStaff::initTestCase(){

}
void TestRemoveFromStaff::cleanupTestCase(){

}
void TestRemoveFromStaff::test_validateUserInput()
{
    // Test case: Check if validateUserInput function returns false when no item is selected
    removefromstaff->ui->removeList->clear();
    QCOMPARE(removefromstaff->validateUserInput(), false);

    // Test case: Check if validateUserInput function returns true when an item is selected
    removefromstaff->ui->removeList->addItem("Test Item"); // Add an item to the combo box
    removefromstaff->ui->removeList->setCurrentText("Test Item"); // Set the current text to the added item
    QCOMPARE(removefromstaff->validateUserInput(), true);
}

void TestRemoveFromStaff::test_loadBox()
{
    // Test case: Check if loadBox function loads items into the combo box
    // This test case involves database operations
    // You might need to set up a mock database or use a real database with known data for this test

    // 1. Set up the database and insert some known data
    QSqlDatabase database = QSqlDatabase::database("DB"); // Get the database.

    QSqlQuery query(database);
    query.exec("INSERT INTO Staff (Name, Assigned) VALUES ('Test Staff', 1)");

    // 2. Call removefromstaff->loadBox()
    removefromstaff->loadBox();

    // 3. Check if the combo box contains the data you inserted into the database
    bool containsInsertedData = false;
    for(int i = 0; i < removefromstaff->ui->removeList->count(); i++)
    {
        if(removefromstaff->ui->removeList->itemText(i) == "Test Staff")
        {
            containsInsertedData = true;
            break;
        }
    }
    QCOMPARE(containsInsertedData, true);

    // 4. Clean up the database
    query.exec("DELETE FROM Staff WHERE Name = 'Test Staff'");
}
