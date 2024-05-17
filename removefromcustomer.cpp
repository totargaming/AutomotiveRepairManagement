#include "removefromcustomer.h"
#include "ui_removefromcustomer.h"

RemoveFromCustomer::RemoveFromCustomer(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RemoveFromCustomer)
{
    ui->setupUi(this);
    database = QSqlDatabase::database("DB");
    if (!database.isValid() || !database.isOpen()) {
        qDebug() << "RemoveFromCustomer: Failed to initialize database";
        return;
    }
    qDebug() << "RemoveFromCustomer: Successfully initialized database";
    loadBox();
}

RemoveFromCustomer::~RemoveFromCustomer()
{
    delete ui;
}

bool RemoveFromCustomer::validateUserInput() {
    QString selectedItem = ui->removeList->currentText();
    if (selectedItem.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please select an item");
        return false;
    }
    return true;
}
void RemoveFromCustomer::loadBox() {
    ui->removeList->clear();
    QSqlQuery query(database);
    query.prepare("SELECT Name FROM Customer");
    if (!query.exec()) {
        qDebug() << "RemoveFromCustomer: Failed to execute query" << query.lastError().text();
        return;
    }
    while(query.next()){
        ui->removeList->addItem(query.value(0).toString());
        qDebug() << "RemoveFromCustomer: Filling removeList" << query.value(0).toString();
    }
    qDebug() << "RemoveFromCustomer: Last query" << query.lastQuery();
    qDebug() << "RemoveFromCustomer: Last error" << query.lastError().text();
}
void RemoveFromCustomer:: showEvent(QShowEvent *event) {
    QDialog::showEvent(event); // Call base class implementation
    loadBox(); // Refresh the combo box
    qDebug() << "Dialog shown";

}

void RemoveFromCustomer::on_removeList_currentTextChanged(const QString &text)
{
    QSqlQuery query(database);
    query.prepare("SELECT UserID, Phone, VehicleID FROM Customer WHERE Name = :Name");
    query.bindValue(":Name", text);
    if (!query.exec()) {
        qDebug() << "RemoveFromCustomer: Failed to execute query" << query.lastError().text();
        return;
    }

    QString userId, phone, vehicleId;
    if (query.next()) {
        userId = query.value(0).toString();
        phone = query.value(1).toString();
        vehicleId = query.value(2).toString();
    }

    ui->idReport->setText("ID: " + userId);
    ui->phoneReport->setText("Phone Number: " + phone);
    query.prepare("SELECT Model FROM Vehicle WHERE VehicleID = :VehicleId");
    query.bindValue(":VehicleId", vehicleId);
    if (!query.exec()) {
        qDebug() << "RemoveFromCustomer: Failed to execute query" << query.lastError().text();
        return;
    }

    QString model;
    if (query.next()) {
        model = query.value(0).toString();
    }

    ui->carModelReport->setText("Car Model: " + model);
}


void RemoveFromCustomer::on_removeBtn_clicked()
{
    if (!validateUserInput()) {
        return;
    }
    QString selectedItem = ui->removeList->currentText();

    QSqlQuery query(database);
    query.prepare("SELECT VehicleID FROM Customer WHERE Name = :name");
    query.bindValue(":name", selectedItem);
    if (!query.exec()) {
        qDebug() << "RemoveFromCustomer: Failed to execute query" << query.lastError().text();
        return;
    }

    QString vehicleId;
    if (query.next()) {
        vehicleId = query.value(0).toString();
    }

    query.prepare("SELECT StaffID FROM Vehicle WHERE VehicleID = :VehicleId");
    query.bindValue(":VehicleId", vehicleId);
    if (!query.exec()) {
        qDebug() << "RemoveFromCustomer: Failed to execute query" << query.lastError().text();
        return;
    }

    QString staffId;
    if (query.next()) {
        staffId = query.value(0).toString();
    }

    query.prepare("UPDATE Staff SET Assigned = 0, VehicleID = NULL WHERE StaffID = :StaffId");
    query.bindValue(":StaffId", staffId);
    if (!query.exec()) {
        qDebug() << "RemoveFromCustomer: Failed to update staff" << query.lastError().text();
        return;
    }

    query.prepare("DELETE FROM Customer WHERE Name = :name");
    query.bindValue(":name", selectedItem);
    if (query.exec()) {
        qDebug() << "RemoveFromCustomer: Customer deleted successfully";
    } else {
        qDebug() << "RemoveFromCustomer: Failed to delete customer" << query.lastError().text();
        return;
    }

    query.prepare("DELETE FROM Vehicle WHERE VehicleID = :VehicleId");
    query.bindValue(":VehicleId", vehicleId);
    if (query.exec()) {
        qDebug() << "RemoveFromCustomer: Vehicle deleted successfully";
        QMessageBox::information(this, "Success", "Item deleted successfully");
    } else {
        qDebug() << "RemoveFromCustomer: Failed to delete vehicle" << query.lastError().text();
        QMessageBox::critical(this, "Error", "Failed to delete item: " + query.lastError().text());
    }

    loadBox(); // Refresh the combo box
    emit customerRemoved();
    close();
}

