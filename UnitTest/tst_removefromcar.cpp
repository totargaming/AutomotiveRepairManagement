#include "tst_removefromcar.h"

TestRemoveFromCar::TestRemoveFromCar()
{
    removeFromCar = new RemoveFromCar();
}

TestRemoveFromCar::~TestRemoveFromCar()
{
    delete removeFromCar;
}

void TestRemoveFromCar::initTestCase()
{
    // Initialization before executing test cases
}

void TestRemoveFromCar::cleanupTestCase()
{
    // Clean-up after all test cases are executed
}

void TestRemoveFromCar::test_validateUserInput()
{
    // Test case: Check if validateUserInput function returns false when no item is selected
    removeFromCar->ui->removeList->clear();
    QCOMPARE(removeFromCar->validateUserInput(), false);

    // Test case: Check if validateUserInput function returns true when an item is selected
    removeFromCar->ui->removeList->addItem("Test Item"); // Add an item to the combo box
    removeFromCar->ui->removeList->setCurrentText("Test Item"); // Set the current text to the added item
    QCOMPARE(removeFromCar->validateUserInput(), true);
}

void TestRemoveFromCar::test_loadBox()
{
    // Test case: Check if loadBox function loads items into the combo box
    // This test case involves database operations
    // You might need to set up a mock database or use a real database with known data for this test

    // 1. Set up the database and insert some known data
    QSqlDatabase database = QSqlDatabase::database("DB"); // Get the database.

    QSqlQuery query(database);
    query.exec("INSERT INTO Vehicle (Model) VALUES ('Test Model')");

    // 2. Call removeFromCar->loadBox()
    removeFromCar->loadBox();

    // 3. Check if the combo box contains the data you inserted into the database
    bool containsInsertedData = false;
    for(int i = 0; i < removeFromCar->ui->removeList->count(); i++)
    {
        if(removeFromCar->ui->removeList->itemText(i) == "Test Model")
        {
            containsInsertedData = true;
            break;
        }
    }
    QCOMPARE(containsInsertedData, true);

    // 4. Clean up the database
    query.exec("DELETE FROM Vehicle WHERE Model = 'Test Model'");
}
