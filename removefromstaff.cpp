#include "removefromstaff.h"
#include "ui_removefromstaff.h"

RemoveFromStaff::RemoveFromStaff(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RemoveFromStaff)
{
    ui->setupUi(this);
    database = QSqlDatabase::database("DB");
    if (!database.isValid() || !database.isOpen()) {
        qDebug() << "RemoveFromStaff: Failed to initialize database";
        return;
    }
    qDebug() << "RemoveFromStaff: Successfully initialized database";
    loadBox();
}

RemoveFromStaff::~RemoveFromStaff()
{
    delete ui;
}
bool RemoveFromStaff::validateUserInput() {
    QString selectedItem = ui->removeList->currentText();
    if (selectedItem.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please select an item");
        return false;
    }
    return true;
}
void RemoveFromStaff::loadBox() {
    ui->removeList->clear();
    QSqlQuery query(database);
    query.prepare("SELECT Name FROM Staff");
    if (!query.exec()) {
        qDebug() << "RemoveFromStaff: Failed to execute query" << query.lastError().text();
        return;
    }
    while(query.next()){
        ui->removeList->addItem(query.value(0).toString());
        qDebug() << "RemoveFromStaff: Filling removeList" << query.value(0).toString();
    }
    qDebug() << "RemoveFromStaff: Last query" << query.lastQuery();
    qDebug() << "RemoveFromStaff: Last error" << query.lastError().text();
}
void RemoveFromStaff::showEvent(QShowEvent *event) {
    QDialog::showEvent(event); // Call base class implementation
    loadBox(); // Refresh the combo box
}

void RemoveFromStaff::on_removeList_currentTextChanged(const QString &text)
{
    QSqlQuery query(database);
    query.prepare("SELECT StaffID, Phone, Wage, Assigned FROM Staff WHERE Name = :Name");
    query.bindValue(":Name", text);
    if (!query.exec()) {
        qDebug() << "RemoveFromStaff: Failed to execute query" << query.lastError().text();
        return;
    }

    QString staffId, phone, wage,assigned;

    if (query.next()) {
        staffId = query.value(0).toString();
        phone = query.value(1).toString();
        wage = query.value(2).toString();
        assigned = query.value(3).toInt() == 1 ? "Yes" : "No";
    }

    ui->idReport->setText("ID: " + staffId);
    ui->phoneReport->setText("Phone: " + phone);
    ui->wageReport->setText("Wage: " + wage);
    ui->assignedReport->setText("Working: " + assigned);
}

void RemoveFromStaff::on_removeBtn_clicked()
{
    if (!validateUserInput()) {
        return;
    }
    QString selectedItem = ui->removeList->currentText();

    QSqlQuery query(database);
    query.prepare("SELECT StaffID FROM Staff WHERE Name = :Name");
    query.bindValue(":Name", selectedItem);
    if (!query.exec()) {
        qDebug() << "RemoveFromStaff: Failed to execute query" << query.lastError().text();
        return;
    }

    QString staffId;
    if (query.next()) {
        staffId = query.value(0).toString();
    }

    query.prepare("DELETE FROM Staff WHERE Name = :Name");
    query.bindValue(":Name", selectedItem);
    if (query.exec()) {
        qDebug() << "RemoveFromStaff: Staff member deleted successfully";
    } else {
        qDebug() << "RemoveFromStaff: Failed to delete staff member" << query.lastError().text();
        return;
    }

    loadBox(); // Refresh the combo box
    emit staffRemoved();

}
