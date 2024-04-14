#include "removefrommaintenance.h"
#include "ui_removefrommaintenance.h"

RemoveFromMaintenance::RemoveFromMaintenance(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RemoveFromMaintenance)
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

RemoveFromMaintenance::~RemoveFromMaintenance()
{
    delete ui;
}

bool RemoveFromMaintenance::validateUserInput() {
    QString selectedItem = ui->removeList->currentText();
    if (selectedItem.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please select an item");
        return false;
    }
    return true;
}
void RemoveFromMaintenance::showEvent(QShowEvent *event)
{
    QDialog::showEvent(event); // Call base class implementation
    loadBox(); // Refresh the combo box
}
void RemoveFromMaintenance::loadBox() {
    ui->removeList->clear();
    QSqlQuery query(database);
    query.prepare("SELECT Model FROM Vehicle WHERE Scheduled = 1");
    if (!query.exec()) {
        qDebug() << "RemoveFromMaintenance: Failed to execute query" << query.lastError().text();
        return;
    }
    while(query.next()){
        ui->removeList->addItem(query.value(0).toString());
        qDebug() << "RemoveFromMaintenance: Filling removeList" << query.value(0).toString();
    }
    qDebug() << "RemoveFromMaintenance: Last query" << query.lastQuery();
    qDebug() << "RemoveFromMaintenance: Last error" << query.lastError().text();
}

void RemoveFromMaintenance::on_removeList_currentTextChanged(const QString &text)
{
    QSqlQuery query(database);
    query.prepare("SELECT StaffID, StartDate, Deadline FROM Vehicle WHERE Model = :Model");
    query.bindValue(":Model", text);
    if (!query.exec()) {
        qDebug() << "RemoveFromMaintenance: Failed to execute query" << query.lastError().text();
        return;
    }

    QString staffId, startDate, deadline;
    if (query.next()) {
        staffId = query.value(0).toString();
        startDate = query.value(1).toString();
        deadline = query.value(2).toString();
    }

    query.prepare("SELECT Name FROM Staff WHERE StaffID = :staffId");
    query.bindValue(":staffId", staffId);
    if (!query.exec()) {
        qDebug() << "RemoveFromMaintenance: Failed to execute query" << query.lastError().text();
        return;
    }

    QString staffName = "Not Assigned";
    if (query.next()) {
        staffName = query.value(0).toString();
        if(staffName.isEmpty()) {
            staffName = "Not Assigned";
        }
    }

    ui->staffNameReport->setText("Staff: " + staffName);
    ui->startDateReport->setText("Start date: " + QDate::fromString(startDate, "yyyy-MM-dd").toString("dd/MM/yyyy"));
    ui->deadlineReport->setText("Deadline: " + QDate::fromString(deadline, "yyyy-MM-dd").toString("dd/MM/yyyy"));
}
void RemoveFromMaintenance::on_removeBtn_clicked()
{
    if (!validateUserInput()) {
        return;
    }

    QString selectedItem = ui->removeList->currentText();

    QSqlQuery query(database);
    query.prepare("SELECT StaffID FROM Vehicle WHERE Model = :Model");
    query.bindValue(":Model", selectedItem);
    if (!query.exec()) {
        qDebug() << "RemoveFromMaintenance: Failed to execute query" << query.lastError().text();
        return;
    }

    QString staffId;
    if (query.next()) {
        staffId = query.value(0).toString();
    }

    query.prepare("UPDATE Vehicle SET Scheduled = 0, Assigned = 0, Finished = 0, StartDate = NULL, Deadline = NULL, StaffID = NULL WHERE Model = :Model");
    query.bindValue(":Model", selectedItem);
    if (query.exec()) {
        qDebug() << "RemoveFromMaintenance: Vehicle updated successfully";
    } else {
        qDebug() << "RemoveFromMaintenance: Failed to update vehicle" << query.lastError().text();
        return;
    }

    query.prepare("UPDATE Staff SET VehicleID = NULL, Assigned = 0 WHERE StaffID = :staffId");
    query.bindValue(":staffId", staffId);
    if (query.exec()) {
        qDebug() << "RemoveFromMaintenance: Staff updated successfully";
        QMessageBox::information(this, "Success", "Item updated successfully");
    } else {
        qDebug() << "RemoveFromMaintenance: Failed to update staff" << query.lastError().text();
        QMessageBox::critical(this, "Error", "Failed to update item: " + query.lastError().text());
    }

    loadBox(); // Refresh the combo box
    emit maintenanceRemoved();
}
