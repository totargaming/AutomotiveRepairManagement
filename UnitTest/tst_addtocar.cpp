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
    // Test with invalid input
    addtocar->ui->txtModel->setText("");
    addtocar->ui->txtBrand->setText("Brand");
    addtocar->ui->txtCustomerName->setText("Customer");
    addtocar->ui->txtPhone->setText("0123456789");
    QVERIFY(!addtocar->validateUserInput());

    // Test with valid input
    addtocar->ui->txtModel->setText("Model");
    addtocar->ui->txtBrand->setText("Brand");
    addtocar->ui->txtCustomerName->setText("Customer");
    addtocar->ui->txtPhone->setText("0123456789");
    QVERIFY(addtocar->validateUserInput());
}

void TestAddToCar::test_reset()
{
    addtocar->ui->txtModel->setText("Model");
    addtocar->ui->txtBrand->setText("Brand");
    addtocar->ui->txtCustomerName->setText("Customer");
    addtocar->ui->txtPhone->setText("0123456789");

    addtocar->reset();

    QCOMPARE(addtocar->ui->txtModel->text(), QString(""));
    QCOMPARE(addtocar->ui->txtBrand->text(), QString(""));
    QCOMPARE(addtocar->ui->txtCustomerName->text(), QString(""));
    QCOMPARE(addtocar->ui->txtPhone->text(), QString(""));
}

// QTEST_MAIN(TestAddToCar)
// #include "tst_addtocar.moc"
