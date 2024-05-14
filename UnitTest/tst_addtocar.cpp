#include "tst_addtocar.h"

TestAddToCar::TestAddToCar()
{
    addtocar = new AddToCar();
}

TestAddToCar::~TestAddToCar()
{
    delete addtocar;
}

void TestAddToCar::initTestCase()
{
    // Initialization before running tests
}

void TestAddToCar::cleanupTestCase()
{
    // Cleanup after running tests
}

void TestAddToCar::test_validateUserInput()
{
    // Test with empty brand
    addtocar->ui->txtModel->setText("Model");
    addtocar->ui->txtBrand->setText("");
    addtocar->ui->txtCustomerName->setText("Customer");
    addtocar->ui->txtPhone->setText("0123456789");
    QVERIFY(!addtocar->validateUserInput());

    // Test with empty customer name
    addtocar->ui->txtModel->setText("Model");
    addtocar->ui->txtBrand->setText("Brand");
    addtocar->ui->txtCustomerName->setText("");
    addtocar->ui->txtPhone->setText("0123456789");
    QVERIFY(!addtocar->validateUserInput());

    // Test with phone number not starting with 0
    addtocar->ui->txtModel->setText("Model");
    addtocar->ui->txtBrand->setText("Brand");
    addtocar->ui->txtCustomerName->setText("Customer");
    addtocar->ui->txtPhone->setText("1234567890");
    QVERIFY(!addtocar->validateUserInput());

    // Test with phone number less than 10 digits
    addtocar->ui->txtModel->setText("Model");
    addtocar->ui->txtBrand->setText("Brand");
    addtocar->ui->txtCustomerName->setText("Customer");
    addtocar->ui->txtPhone->setText("012345678");
    QVERIFY(!addtocar->validateUserInput());

    // Test with phone number containing non-numeric characters
    addtocar->ui->txtModel->setText("Model");
    addtocar->ui->txtBrand->setText("Brand");
    addtocar->ui->txtCustomerName->setText("Customer");
    addtocar->ui->txtPhone->setText("012345678a");
    QVERIFY(!addtocar->validateUserInput());
}

void TestAddToCar::test_reset()
{
    addtocar->ui->txtModel->setText("Model");
    addtocar->ui->txtBrand->setText("Brand");
    addtocar->ui->txtDescription->setText("Description");
    addtocar->ui->txtCustomerName->setText("Customer");
    addtocar->ui->txtPhone->setText("0123456789");

    addtocar->reset();

    QCOMPARE(addtocar->ui->txtModel->text(), QString(""));
    QCOMPARE(addtocar->ui->txtBrand->text(), QString(""));
    QCOMPARE(addtocar->ui->txtDescription->toPlainText(), QString(""));
    QCOMPARE(addtocar->ui->txtCustomerName->text(), QString(""));
    QCOMPARE(addtocar->ui->txtPhone->text(), QString(""));
}

// QTEST_MAIN(TestAddToCar)
// #include "tst_addtocar.moc"
