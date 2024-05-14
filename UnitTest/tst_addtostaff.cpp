#include "tst_addtostaff.h"

TestAddToStaff::TestAddToStaff() {
    addtostaff = new AddToStaff();
}
TestAddToStaff::~TestAddToStaff() {
    delete addtostaff;
}
void TestAddToStaff::initTestCase() {

}

void TestAddToStaff::cleanupTestCase() {

}

void TestAddToStaff::test_validateUserInput() {
    // Test case: Check if validateUserInput function returns false when any of the fields are empty
    addtostaff->ui->txtName->setText("");
    addtostaff->ui->txtPhone->setText("");
    addtostaff->ui->txtWage->setText("");
    QCOMPARE(addtostaff->validateUserInput(), false);

    // Test case: Check if validateUserInput function returns false when phone number is not valid
    addtostaff->ui->txtName->setText("Test Name");
    addtostaff->ui->txtPhone->setText("1234567890"); // Phone number does not start with 0
    addtostaff->ui->txtWage->setText("1000");
    QCOMPARE(addtostaff->validateUserInput(), false);

    // Test case: Check if validateUserInput function returns true when all fields are valid
    addtostaff->ui->txtName->setText("Test Name");
    addtostaff->ui->txtPhone->setText("0123456789"); // Phone number starts with 0 and has a length of 10
    addtostaff->ui->txtWage->setText("1000");
    QCOMPARE(addtostaff->validateUserInput(), true);
}

void TestAddToStaff::test_reset() {
    // Set some text in the input fields
    addtostaff->ui->txtName->setText("Test Name");
    addtostaff->ui->txtPhone->setText("0123456789");
    addtostaff->ui->txtWage->setText("1000");

    // Call the reset method
    addtostaff->reset();

    // Check if all the fields are empty after calling the reset method
    QCOMPARE(addtostaff->ui->txtName->text(), QString(""));
    QCOMPARE(addtostaff->ui->txtPhone->text(), QString(""));
    QCOMPARE(addtostaff->ui->txtWage->text(), QString(""));
}
