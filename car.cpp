#include "car.h"
#include "ui_entitylist.h"
Car::Car(QWidget* parent): EntityList(parent){
    loadList();
}
void Car::add() {

}
void Car::remove() {

}

void Car::loadList() {
    qDebug() << "Entering loadList";
    QSqlDatabase database = QSqlDatabase::database("DB");
    if (!database.isOpen()) {
        qDebug() << "Database is not open!";
        return;
    }
    model = new QSqlQueryModel();
    model->setQuery("SELECT VehicleID, Model FROM Vehicle", database);
    ui->tableView->setModel(model);
    qDebug() << "Exiting loadList";
}

void Car::idSort() {
    qDebug() << "Entering idSort";
    QSqlDatabase database = QSqlDatabase::database("DB");
    model = new QSqlQueryModel();
    model->setQuery("SELECT VehicleID, Model FROM Vehicle ORDER BY VehicleID", database);
    ui->tableView->setModel(model);
    qDebug() << "Exiting idSort";
}

void Car::nameSort() {
    qDebug() << "Entering nameSort";
    QSqlDatabase database = QSqlDatabase::database("DB");
    model = new QSqlQueryModel();
    model->setQuery("SELECT VehicleID, Model FROM Vehicle ORDER BY Model", database);
    ui->tableView->setModel(model);
    qDebug() << "Exiting nameSort";
}

void Car::showInfo(const QModelIndex &index) {
    qDebug() << "Entering showInfo";


    int row = index.row();
    QString vehicleId = ui->tableView->model()->data(ui->tableView->model()->index(row, 0)).toString();

    QSqlDatabase database = QSqlDatabase::database("DB");
    if (!database.isOpen()) {
        qDebug() << "Database is not open!";
        return;
    }

    QSqlQuery query(database);
    query.prepare("SELECT * FROM Vehicle WHERE VehicleID = :vehicleId");
    query.bindValue(":vehicleId", vehicleId);
    if (!query.exec()) {
        qDebug() << "Failed to execute query: " << query.lastError();
        return;
    }

    if (query.next()) {
        QString model = query.value("Model").toString();
        QString brand = query.value("Brand").toString();
        QString dateAssigned = query.value("DateAssigned").toString();
        QString assigned = query.value("Assigned").toString();
        QString description = query.value("Description").toString();
        QString userId = query.value("UserID").toString();

        ui->txtInfo->setText("Vehicle ID: " + vehicleId + "\nModel: " + model + "\nBrand: " + brand + "\nDate Assigned: " + dateAssigned + "\nAssigned: " + assigned + "\nDescription: " + description + "\nUser ID: " + userId);
    }

    qDebug() << "Exiting showInfo";
}
Car::~Car() {

}
