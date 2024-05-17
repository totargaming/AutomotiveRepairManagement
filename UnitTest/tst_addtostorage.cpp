#include "tst_addtostorage.h"

TestAddToStorage::TestAddToStorage() {
    addtostorage = new addToStorage();
}

TestAddToStorage::~TestAddToStorage() {
    delete addtostorage;
}

void TestAddToStorage::initTestCase() {
    // This function will be called before the first test case is run
    // You can use it to do any setup required for your tests
}

void TestAddToStorage::cleanupTestCase() {
    // This function will be called after the last test case is run
    // You can use it to do any cleanup required
}

void TestAddToStorage::test_validateUserInput() {
    // Test with empty input
    addtostorage->ui->input->setText("");
    QVERIFY(addtostorage->validateUserInput() == false);

    // Test with valid input

}

void TestAddToStorage::test_reset() {
    // Set some values in the input fields
    addtostorage->ui->input->setText("Test Part");
    addtostorage->ui->quantitySelect->setValue(5);

    // Call the reset method
    addtostorage->reset();

    // Check that the input fields have been cleared
    QVERIFY(addtostorage->ui->input->text().isEmpty());
    QVERIFY(addtostorage->ui->quantitySelect->text().isEmpty());
}
