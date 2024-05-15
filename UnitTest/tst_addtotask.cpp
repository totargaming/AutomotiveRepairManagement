#include "tst_addtotask.h"

TestAddToTask::TestAddToTask() {
    addtotask = new AddToTask();
}

TestAddToTask::~TestAddToTask() {
    delete addtotask;
}

void TestAddToTask::initTestCase() {
    addtotask = new AddToTask();
}

void TestAddToTask::cleanupTestCase() {
    delete addtotask;
}

void TestAddToTask::test_validateUserInput() {
    // Test with empty input
    addtotask->ui->modelBox->clear();
    addtotask->ui->staffBox->clear();
    QVERIFY(addtotask->validateUserInput() == false);

    // Test with valid input
    addtotask->ui->modelBox->addItem("Test Model");
    addtotask->ui->modelBox->setCurrentText("Test Model");
    addtotask->ui->staffBox->addItem("Test Staff");
    addtotask->ui->staffBox->setCurrentText("Test Staff");
    QVERIFY(addtotask->validateUserInput() == true);
}

void TestAddToTask::test_loadBox() {
    // Assuming that the database is correctly set up and contains the necessary data,
    // the combo boxes should not be empty after calling loadBox.
    addtotask->loadBox();
    QVERIFY(!addtotask->ui->modelBox->currentText().isEmpty());
    QVERIFY(!addtotask->ui->staffBox->currentText().isEmpty());
}
