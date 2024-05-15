#include "tst_removefromcustomer.h"

TestRemoveFromCustomer::TestRemoveFromCustomer() {
    removefromcustomer = new RemoveFromCustomer();
}

TestRemoveFromCustomer::~TestRemoveFromCustomer() {
    delete removefromcustomer;
}

void TestRemoveFromCustomer::initTestCase() {
}

void TestRemoveFromCustomer::cleanupTestCase() {
}

void TestRemoveFromCustomer::test_validateUserInput() {
    // Test with empty input
    removefromcustomer->ui->removeList->clear();
    QVERIFY(removefromcustomer->validateUserInput() == false);

    // Test with valid input
    removefromcustomer->ui->removeList->addItem("Test Customer");

    removefromcustomer->ui->removeList->setCurrentText("Test Customer");
    QVERIFY(removefromcustomer->validateUserInput() == true);
}

void TestRemoveFromCustomer::test_loadBox()
{
    // Test case: Check if loadBox function loads items into the combo box
    // This test case involves database operations
    // You might need to set up a mock database or use a real database with known data for this test

    // 1. Set up the database and insert some known data
    QSqlDatabase database = QSqlDatabase::database("DB"); // Get the database.

    QSqlQuery query(database);
    query.exec("INSERT INTO Customer (Name) VALUES ('Test Customer')");

    // 2. Call removefromcustomer->loadBox()
    removefromcustomer->loadBox();

    // 3. Check if the combo box contains the data you inserted into the database
    bool containsInsertedData = false;
    for(int i = 0; i < removefromcustomer->ui->removeList->count(); i++)
    {
        if(removefromcustomer->ui->removeList->itemText(i) == "Test Customer")
        {
            containsInsertedData = true;
            break;
        }
    }
    QCOMPARE(containsInsertedData, true);

    // 4. Clean up the database
    query.exec("DELETE FROM Customer WHERE Name = 'Test Customer'");
}
