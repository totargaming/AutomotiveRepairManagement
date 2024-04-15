#include "addtotask.h"
#include "ui_addtotask.h"

AddToTask::AddToTask(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddToTask)
{
    ui->setupUi(this);
    database = QSqlDatabase::database("DB");
    if (!database.isValid() || !database.isOpen()) {
        qDebug() << "AddToTask: Failed to initialize database";
        return;
    }
    qDebug() << "AddToTask: Successfully initialized database";
    loadBox();
}

AddToTask::~AddToTask()
{
    delete ui;
}

void AddToTask::loadBox() {
    ui->modelBox->clear();
    ui->staffBox->clear();
    // Load models
    QSqlQuery modelQuery(database);
    modelQuery.prepare("SELECT Model FROM Vehicle WHERE Scheduled = 1 AND Assigned = 0 AND Finished = 0 AND StaffID IS NULL");
    if (!modelQuery.exec()) {
        qDebug() << "AddToTask: Failed to execute model query" << modelQuery.lastError().text();
        return;
    }
    while(modelQuery.next()){
        ui->modelBox->addItem(modelQuery.value(0).toString());
    }

    // Load staff
    QSqlQuery staffQuery(database);
    staffQuery.prepare("SELECT Name FROM Staff WHERE Assigned = 0 AND VehicleID IS NULL");
    if (!staffQuery.exec()) {
        qDebug() << "AddToTask: Failed to execute staff query" << staffQuery.lastError().text();
        return;
    }
    while(staffQuery.next()){
        ui->staffBox->addItem(staffQuery.value(0).toString());
    }
}

void AddToTask::showEvent(QShowEvent *event)
{
    QDialog::showEvent(event); // Call base class implementation
    loadBox(); // Refresh the combo box
}

bool AddToTask::validateUserInput() {
    if (ui->modelBox->currentText().isEmpty() || ui->staffBox->currentText().isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please select a model and a staff member");
        return false;
    }
    return true;
}

void AddToTask::on_modelBox_currentTextChanged(const QString &text)
{
    QSqlQuery query(database);
    query.prepare("SELECT StartDate, Deadline FROM Vehicle WHERE Model = :Model");
    query.bindValue(":Model", text);
    if (!query.exec()) {
        qDebug() << "AddToTask: Failed to execute query" << query.lastError().text();
        return;
    }

    QString startDate, deadline;
    if (query.next()) {
        startDate = query.value(0).toString();
        deadline = query.value(1).toString();
    }

    ui->startDateLabel->setText("Start date: " + QDate::fromString(startDate, "yyyy-MM-dd").toString("dd/MM/yyyy"));
    ui->deadlineLabel->setText("Deadline: " + QDate::fromString(deadline, "yyyy-MM-dd").toString("dd/MM/yyyy"));
}

void AddToTask::on_addBtn_clicked()
{
    if (!validateUserInput()) {
        return;
    }

    QString modelName = ui->modelBox->currentText();
    QString staffName = ui->staffBox->currentText();

    // Update Vehicle
    QSqlQuery vehicleQuery(database);
    vehicleQuery.prepare("UPDATE Vehicle SET Assigned = 1, StaffID = (SELECT StaffID FROM Staff WHERE Name = :StaffName) WHERE Model = :ModelName");
    vehicleQuery.bindValue(":StaffName", staffName);
    vehicleQuery.bindValue(":ModelName", modelName);
    if (!vehicleQuery.exec()) {
        qDebug() << "AddToTask: Failed to update Vehicle" << vehicleQuery.lastError().text();
        return;
    }

    // Update Staff
    QSqlQuery staffQuery(database);
    staffQuery.prepare("UPDATE Staff SET Assigned = 1, VehicleID = (SELECT VehicleID FROM Vehicle WHERE Model = :ModelName) WHERE Name = :StaffName");
    staffQuery.bindValue(":ModelName", modelName);
    staffQuery.bindValue(":StaffName", staffName);
    if (!staffQuery.exec()) {
        qDebug() << "AddToTask: Failed to update Staff" << staffQuery.lastError().text();
        return;
    }

    QMessageBox::information(this, "Success", "Task has been successfully added");
    emit taskAdded();

    loadBox();

}
