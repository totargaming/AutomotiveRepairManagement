#include "addtocar.h"
#include "ui_addtocar.h"

AddToCar::AddToCar(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddToCar)
{
    ui->setupUi(this);
    database = QSqlDatabase::database("DB");
}

AddToCar::~AddToCar()
{
    delete ui;
}



bool AddToCar::validateUserInput() {
    QString model = ui->txtModel->text();
    QString brand = ui->txtBrand->text();
    QString customerName = ui->txtCustomerName->text();
    QString phone = ui->txtPhone->text();

    // Check if Model, Brand, and Customer Name are not empty
    if (model.isEmpty() || brand.isEmpty() || customerName.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Model, Brand, and Customer Name should not be empty.");
        return false;
    }

    // Check if Phone starts with 0 and has a length of 10
    if (!phone.startsWith('0') || phone.length() != 10) {
        QMessageBox::warning(this, "Input Error", "Phone should start with 0 and have a length of 10.");
        return false;
    }

    // Check if Phone contains only numeric characters
    for (QChar c : phone) {
        if (!c.isDigit()) {
            QMessageBox::warning(this, "Input Error", "Phone should contain only numeric characters.");
            return false;
        }
    }

    return true;
}

void AddToCar::reset() {
    ui->txtModel->clear();
    ui->txtBrand->clear();
    ui->txtDescription->clear();
    ui->txtCustomerName->clear();
    ui->txtPhone->clear();
}
void AddToCar::on_addBtn_clicked() {
    if (!validateUserInput()) {
        return;
    }

    QString model = ui->txtModel->text();
    QString brand = ui->txtBrand->text();
    QString description = ui->txtDescription->toPlainText().simplified();
    QString customerName = ui->txtCustomerName->text();
    QString phone = ui->txtPhone->text();

    QSqlQuery query(database);

    // Insert into Vehicle table
    query.prepare("INSERT INTO Vehicle (Model, Brand, Description) VALUES (:Model, :Brand, :Description)");
    query.bindValue(":Model", model);
    query.bindValue(":Brand", brand);
    query.bindValue(":Description", description);

    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
        return;
    }

    // Get the VehicleID of the last inserted Vehicle
    int vehicleID = query.lastInsertId().toInt();

    // Insert into Customer table
    query.prepare("INSERT INTO Customer (Name, Phone, VehicleID) VALUES (:Name, :Phone, :VehicleID)");
    query.bindValue(":Name", customerName);
    query.bindValue(":Phone", phone);
    query.bindValue(":VehicleID", vehicleID);

    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
        return;
    }

    // Get the UserID of the last inserted Customer
    int userID = query.lastInsertId().toInt();

    // Update the UserID in the Vehicle table
    query.prepare("UPDATE Vehicle SET UserID = :UserID WHERE VehicleID = :VehicleID");
    query.bindValue(":UserID", userID);
    query.bindValue(":VehicleID", vehicleID);

    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
        return;
    }
    emit carAdded();

    QMessageBox::information(this, "Success", "Vehicle and Customer information added successfully.");
    reset();
}
