#include "tst_addtomaintenance.h"


TestAddToMaintenance::TestAddToMaintenance() {
    addtomaintenance = new AddToMaintenance();

}

TestAddToMaintenance::~TestAddToMaintenance() {
    delete addtomaintenance;
}
// Initialize the test case
void TestAddToMaintenance::initTestCase() {
}

// Cleanup the test case
void TestAddToMaintenance::cleanupTestCase() {
}

// Test the validateUserInput method
void TestAddToMaintenance::test_validateUserInput() {
    // Set up the state of the addToMaintenance object
    addtomaintenance->ui->modelBox->setCurrentText("Test Model");
    addtomaintenance->ui->startDateEdit->setDate(QDate::currentDate().addDays(1));
    addtomaintenance->ui->deadlineDateEdit->setDate(QDate::currentDate().addDays(2));

    // Call the validateUserInput method and check the result
    QVERIFY(addtomaintenance->validateUserInput() == true);

    // Test with empty model box
    addtomaintenance->ui->modelBox->clear();
    QVERIFY(addtomaintenance->validateUserInput() == false);

    // Test with start date in the past
    addtomaintenance->ui->modelBox->setCurrentText("Test Model");
    addtomaintenance->ui->startDateEdit->setDate(QDate::currentDate().addDays(-1));
    QVERIFY(addtomaintenance->validateUserInput() == false);

    // Test with deadline date before start date
    addtomaintenance->ui->startDateEdit->setDate(QDate::currentDate().addDays(2));
    addtomaintenance->ui->deadlineDateEdit->setDate(QDate::currentDate().addDays(1));
    QVERIFY(addtomaintenance->validateUserInput() == false);
}

// Test the loadBox method
void TestAddToMaintenance::test_loadBox() {
    // Call the loadBox method
    addtomaintenance->loadBox();

    // Check the state of the combo box
    // This assumes that you have a method to get the number of items in the combo box
    QVERIFY(addtomaintenance->ui->modelBox->count() > 0);

    // Check the state of the date edits
    QVERIFY(addtomaintenance->ui->startDateEdit->date() == QDate::currentDate());
    QVERIFY(addtomaintenance->ui->deadlineDateEdit->date() == QDate::currentDate());
}
