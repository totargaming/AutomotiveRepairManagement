#include "removefromcar.h"
#include "ui_removefromcar.h"

RemoveFromCar::RemoveFromCar(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RemoveFromCar)
{
    ui->setupUi(this);
    database = QSqlDatabase::database("DB");
    if (!database.isValid() || !database.isOpen()) {
        qDebug() << "RemoveFromCar: Failed to initialize database";
        return;
    }
    qDebug() << "RemoveFromCar: Successfully initialized database";
    loadBox();
}

RemoveFromCar::~RemoveFromCar()
{
    delete ui;
}

void RemoveFromCar::loadBox() {
    ui->removeList->clear();
    QSqlQuery query(database);
    query.prepare("SELECT Model FROM Vehicle");
    if (!query.exec()) {
        qDebug() << "RemoveFromCar: Failed to execute query" << query.lastError().text();
        return;
    }
    while(query.next()){
        ui->removeList->addItem(query.value(0).toString());
        qDebug() << "RemoveFromCar: Filling removeList" << query.value(0).toString();
    }
    qDebug() << "RemoveFromCar: Last query" << query.lastQuery();
    qDebug() << "RemoveFromCar: Last error" << query.lastError().text();
}

void RemoveFromCar::showEvent(QShowEvent *event)
{
    QDialog::showEvent(event); // Call base class implementation
    loadBox(); // Refresh the combo box
}
bool RemoveFromCar::validateUserInput() {
    QString selectedItem = ui->removeList->currentText();
    if (selectedItem.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please select an item");
        return false;
    }
    return true;
}


void RemoveFromCar::on_removeList_currentTextChanged(const QString &text)
{
    QSqlQuery query(database);
    query.prepare("SELECT VehicleID, UserID FROM Vehicle WHERE Model = :Model");
    query.bindValue(":Model", text);
    if (!query.exec()) {
        qDebug() << "RemoveFromCar: Failed to execute query" << query.lastError().text();
        return;
    }

    QString vehicleId, userId;
    if (query.next()) {
        vehicleId = query.value(0).toString();
        userId = query.value(1).toString();
    }

    ui->idReport->setText("ID: " + vehicleId);

    query.prepare("SELECT Name FROM Customer WHERE UserID = :userId");
    query.bindValue(":userId", userId);
    if (!query.exec()) {
        qDebug() << "RemoveFromCar: Failed to execute query" << query.lastError().text();
        return;
    }

    QString customerName;
    if (query.next()) {
        customerName = query.value(0).toString();
    }

    ui->customerNameReport->setText("Customer Name: " + customerName);
}


void RemoveFromCar::on_removeBtn_clicked()
{
    if (!validateUserInput()) {
        return;
    }
    QString selectedItem = ui->removeList->currentText();

    QSqlQuery query(database);
    query.prepare("SELECT UserID FROM Vehicle WHERE Model = :Model");
    query.bindValue(":Model", selectedItem);
    if (!query.exec()) {
        qDebug() << "RemoveFromCar: Failed to execute query" << query.lastError().text();
        return;
    }

    QString userId;
    if (query.next()) {
        userId = query.value(0).toString();
    }

    query.prepare("DELETE FROM Vehicle WHERE Model = :Model");
    query.bindValue(":Model", selectedItem);
    if (query.exec()) {
        qDebug() << "RemoveFromCar: Vehicle deleted successfully";
    } else {
        qDebug() << "RemoveFromCar: Failed to delete vehicle" << query.lastError().text();
        return;
    }

    query.prepare("DELETE FROM Customer WHERE UserID = :userId");
    query.bindValue(":userId", userId);
    if (query.exec()) {
        qDebug() << "RemoveFromCar: Customer deleted successfully";
        QMessageBox::information(this, "Success", "Item deleted successfully");
    } else {
        qDebug() << "RemoveFromCar: Failed to delete customer" << query.lastError().text();
        QMessageBox::critical(this, "Error", "Failed to delete item: " + query.lastError().text());
    }

    loadBox(); // Refresh the combo box
    emit carRemoved();
}

