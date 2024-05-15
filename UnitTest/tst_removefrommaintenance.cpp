#include "tst_removefrommaintenance.h"

TestRemoveFromMaintenance::TestRemoveFromMaintenance() {
    removefrommaintenance = new RemoveFromMaintenance();
}
TestRemoveFromMaintenance::~TestRemoveFromMaintenance() {
    delete removefrommaintenance;
}

void TestRemoveFromMaintenance::initTestCase() {

}
void TestRemoveFromMaintenance::cleanupTestCase() {

}
void TestRemoveFromMaintenance::test_validateUserInput()
{
    // Test case: Check if validateUserInput function returns false when no item is selected
    removefrommaintenance->ui->removeList->clear();
    QCOMPARE(removefrommaintenance->validateUserInput(), false);

    // Test case: Check if validateUserInput function returns true when an item is selected
    removefrommaintenance->ui->removeList->addItem("Test Item"); // Add an item to the combo box
    removefrommaintenance->ui->removeList->setCurrentText("Test Item"); // Set the current text to the added item
    QCOMPARE(removefrommaintenance->validateUserInput(), true);
}

void TestRemoveFromMaintenance::test_loadBox()
{
    // Test case: Check if loadBox function loads items into the combo box
    // This test case involves database operations
    // You might need to set up a mock database or use a real database with known data for this test

    // 1. Set up the database and insert some known data
    QSqlDatabase database = QSqlDatabase::database("DB"); // Get the database.

    QSqlQuery query(database);
    query.exec("INSERT INTO Vehicle (Model, Scheduled) VALUES ('Test Model', 1)");

    // 2. Call removefrommaintenance->loadBox()
    removefrommaintenance->loadBox();

    // 3. Check if the combo box contains the data you inserted into the database
    bool containsInsertedData = false;
    for(int i = 0; i < removefrommaintenance->ui->removeList->count(); i++)
    {
        if(removefrommaintenance->ui->removeList->itemText(i) == "Test Model")
        {
            containsInsertedData = true;
            break;
        }
    }
    QCOMPARE(containsInsertedData, true);

    // 4. Clean up the database
    query.exec("DELETE FROM Vehicle WHERE Model = 'Test Model'");
}
