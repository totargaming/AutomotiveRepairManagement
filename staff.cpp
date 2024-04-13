#include "staff.h"
#include "ui_entitylist.h"
Staff::Staff(QWidget *parent): EntityList(parent) {
    qDebug() << "Staff: Initializing Staff";
    loadList();
    addToStaff_ptr = new AddToStaff();
    removeFromStaff_ptr = new RemoveFromStaff();
    connect(addToStaff_ptr, &AddToStaff::staffAdded, this, &Staff::loadList);
    connect(removeFromStaff_ptr, &RemoveFromStaff::staffRemoved, this, &Staff::loadList);

}
void Staff::add() {
    qDebug() << "Staff: add() called";
    addToStaff_ptr->setWindowTitle("Staff: Hire");
    addToStaff_ptr->show();
}

void Staff::remove() {
    qDebug() << "Staff: remove() called";
    removeFromStaff_ptr->setWindowTitle("Staff: Fire");
    removeFromStaff_ptr->show();
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
        QString vehicleId = query.value("VehicleID").isNull() ? "Not assigned" : query.value("VehicleID").toString();

        // Fetch the model from the Vehicle table
        QString model;
        if (vehicleId != "Not assigned") {
            QSqlQuery vehicleQuery(database);
            vehicleQuery.prepare("SELECT Model FROM Vehicle WHERE VehicleID = :vehicleId");
            vehicleQuery.bindValue(":vehicleId", vehicleId);
            if (!vehicleQuery.exec()) {
                qDebug() << "Staff: Failed to execute vehicle query" << vehicleQuery.lastError();
                return;
            }

            if (vehicleQuery.next()) {
                model = vehicleQuery.value("Model").toString();
            }
        } else {
            model = "Not assigned";
        }

        ui->txtInfo->setText("Staff ID: " + staffId + "\nName: " + name + "\nPhone: " + phone + "\nWage: " + QString::number(wage) + "\nAssigned: " + assigned + "\nVehicle Model: " + model);
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
    delete removeFromStaff_ptr;

}
