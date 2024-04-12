#include "staff.h"
#include "ui_entitylist.h"
Staff::Staff(QWidget *parent): EntityList(parent) {
    qDebug() << "Staff: Initializing Staff";
    loadList();
    addToStaff_ptr = new AddToStaff();
    connect(addToStaff_ptr, &AddToStaff::staffAdded, this, &Staff::loadList);

}
void Staff::add() {
    qDebug() << "Staff: add() called";
    addToStaff_ptr->setWindowTitle("Staff: Hire");
    addToStaff_ptr->show();
}

void Staff::remove() {

}

void Staff::showInfo(const QModelIndex &index) {
    qDebug() << "Staff: Entering showInfo";

    int row = index.row();
    QString staffId = ui->tableView->model()->data(ui->tableView->model()->index(row, 0)).toString();

    QSqlDatabase database = QSqlDatabase::database("DB");
    if (!database.isOpen()) {
        qDebug() << "Staff: Database is not open!";
        return;
    }

    QSqlQuery query(database);
    query.prepare("SELECT * FROM Staff WHERE StaffID = :staffId");
    query.bindValue(":staffId", staffId);
    if (!query.exec()) {
        qDebug() << "Staff: Failed to execute query" << query.lastError();
        return;
    }

    if (query.next()) {
        QString name = query.value("Name").toString();
        QString phone = query.value("Phone").toString();
        int wage = query.value("Wage").toInt();
        QString assigned = (query.value("Assigned").toInt() == 1) ? "Yes" : "No";
        QString maintenanceId = query.value("MaintenanceID").isNull() ? "Not assigned" : query.value("MaintenanceID").toString();

        ui->txtInfo->setText("Staff ID: " + staffId + "\nName: " + name + "\nPhone: " + phone + "\nWage: " + QString::number(wage) + "\nAssigned: " + assigned + "\nMaintenance ID: " + maintenanceId);
    }

    qDebug() << "Staff: Exiting showInfo";
}

void Staff::loadList() {
    qDebug() << "Staff: Entering loadList";
    QSqlDatabase database = QSqlDatabase::database("DB");
    if (!database.isOpen()) {
        qDebug() << "Staff: Database is not open!";
        return;
    }
    model = new QSqlQueryModel();
    model->setQuery("SELECT StaffID, Name FROM Staff", database);
    ui->tableView->setModel(model);
    qDebug() << "Staff: Exiting loadList";
}

void Staff::idSort() {
    qDebug() << "Staff: Entering idSort";
    QSqlDatabase database = QSqlDatabase::database("DB");
    model = new QSqlQueryModel();
    model->setQuery("SELECT StaffID, Name FROM Staff ORDER BY StaffID", database);
    ui->tableView->setModel(model);
    qDebug() << "Staff: Exiting idSort";
}

void Staff::nameSort() {
    qDebug() << "Staff: Entering nameSort";
    QSqlDatabase database = QSqlDatabase::database("DB");
    model = new QSqlQueryModel();
    model->setQuery("SELECT StaffID, Name FROM Staff ORDER BY Name", database);
    ui->tableView->setModel(model);
    qDebug() << "Staff: Exiting nameSort";
}

Staff::~Staff() {
    qDebug() << "Car: Destructor called";
    delete addToStaff_ptr;
}
