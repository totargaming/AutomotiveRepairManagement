#include "car.h"
#include "ui_entitylist.h"

Car::Car(QWidget* parent): EntityList(parent){
    qDebug() << "Car: Initializing Car";
    loadList();
}

void Car::add() {
    qDebug() << "Car: add() called";
}

void Car::remove() {
    qDebug() << "Car: remove() called";
}

void Car::loadList() {
    qDebug() << "Car: Entering loadList";
    QSqlDatabase database = QSqlDatabase::database("DB");
    if (!database.isOpen()) {
        qDebug() << "Car: Database is not open!";
        return;
    }
    model = new QSqlQueryModel();
    model->setQuery("SELECT VehicleID, Model FROM Vehicle", database);
    ui->tableView->setModel(model);
    qDebug() << "Car: Exiting loadList";
}

void Car::idSort() {
    qDebug() << "Car: Entering idSort";
    QSqlDatabase database = QSqlDatabase::database("DB");
    model = new QSqlQueryModel();
    model->setQuery("SELECT VehicleID, Model FROM Vehicle ORDER BY VehicleID", database);
    ui->tableView->setModel(model);
    qDebug() << "Car: Exiting idSort";
}

void Car::nameSort() {
    qDebug() << "Car: Entering nameSort";
    QSqlDatabase database = QSqlDatabase::database("DB");
    model = new QSqlQueryModel();
    model->setQuery("SELECT VehicleID, Model FROM Vehicle ORDER BY Model", database);
    ui->tableView->setModel(model);
    qDebug() << "Car: Exiting nameSort";
}

void Car::showInfo(const QModelIndex &index) {
    qDebug() << "Car: Entering showInfo";

    int row = index.row();
    QString vehicleId = ui->tableView->model()->data(ui->tableView->model()->index(row, 0)).toString();

    QSqlDatabase database = QSqlDatabase::database("DB");
    if (!database.isOpen()) {
        qDebug() << "Car: Database is not open!";
        return;
    }

    QSqlQuery query(database);
    query.prepare("SELECT * FROM Vehicle WHERE VehicleID = :vehicleId");
    query.bindValue(":vehicleId", vehicleId);
    if (!query.exec()) {
        qDebug() << "Car: Failed to execute query" << query.lastError();
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

    qDebug() << "Car: Exiting showInfo";
}

Car::~Car() {
    qDebug() << "Car: Destructor called";
}
