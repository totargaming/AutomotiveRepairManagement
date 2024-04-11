#include "customer.h"
#include "ui_entitylist.h"
Customer::Customer(QWidget* parent): EntityList(parent) {
    qDebug() << "Customer: Initializing Customer";
    ui->addBtn->setVisible(false);
    loadList();
    removeFromCustomer_ptr = new RemoveFromCustomer();
    connect(removeFromCustomer_ptr, &RemoveFromCustomer::customerRemoved, this, &Customer::loadList);


}

void Customer::add() {

}
void Customer::remove() {
    qDebug() << "Car: remove() called";
    removeFromCustomer_ptr->setWindowTitle("Car: Remove");
    removeFromCustomer_ptr->show();
}
void Customer::showInfo(const QModelIndex &index) {
    qDebug() << "Customer: Entering showInfo";

    int row = index.row();
    QString UserId = ui->tableView->model()->data(ui->tableView->model()->index(row, 0)).toString();

    QSqlDatabase database = QSqlDatabase::database("DB");
    if (!database.isOpen()) {
        qDebug() << "Car: Database is not open!";
        return;
    }

    QSqlQuery query(database);
    query.prepare("SELECT * FROM Customer WHERE UserID = :UserId");
    query.bindValue(":UserId", UserId);
    if (!query.exec()) {
        qDebug() << "Car: Failed to execute query(1)" << query.lastError();
        return;
    }

    if (query.next()) {
        QString name = query.value("Name").toString();
        QString phoneNumber = query.value("Phone").toString();
        QString vehicleId = query.value("VehicleID").toString();

        QSqlQuery userQuery(database);
        userQuery.prepare("SELECT Model, Brand FROM Vehicle WHERE VehicleID = :VehicleId");
        userQuery.bindValue(":VehicleId", vehicleId);
        if (!userQuery.exec()) {
            qDebug() << "Car: Failed to execute user query(2)" << userQuery.lastError();
            return;
        }

        QString model;
        QString brand;

        if (userQuery.next()) {
            model = userQuery.value("Model").toString();
            brand = userQuery.value("Brand").toString();
        }

        ui->txtInfo->setText("Name: " + name + "\nPhone: " + phoneNumber + "\nVehicle ID: " + vehicleId + "\nModel: " + model + "\nBrand: " + brand);
    }

    qDebug() << "Customer: Exiting showInfo";
}
void Customer::loadList() {
    qDebug() << "Customer: Entering loadList";
    QSqlDatabase database = QSqlDatabase::database("DB");
    if (!database.isOpen()) {
        qDebug() << "Customer: Database is not open!";
        return;
    }
    model = new QSqlQueryModel();
    model->setQuery("SELECT UserID, Name FROM Customer", database);
    ui->tableView->setModel(model);
    qDebug() << "Customer: Exiting loadList";
}
void Customer::idSort() {
    qDebug() << "Customer: Entering idSort";
    QSqlDatabase database = QSqlDatabase::database("DB");
    model = new QSqlQueryModel();
    model->setQuery("SELECT UserID, Name FROM Customer ORDER BY UserID", database);
    qDebug() << "Customer: Row count: " << model->rowCount();
    ui->tableView->setModel(model);
    qDebug() << "Customer: Exiting idSort";
}
void Customer::nameSort() {
    qDebug() << "Customer: Entering nameSort";
    QSqlDatabase database = QSqlDatabase::database("DB");
    model = new QSqlQueryModel();
    model->setQuery("SELECT UserID, Name FROM Customer ORDER BY Name", database);
    qDebug() << "Customer: Row count: " << model->rowCount();
    ui->tableView->setModel(model);
    qDebug() << "Customer: Exiting nameSort";
}
Customer::~Customer() {
    qDebug() << "Customer: Destructor called";
    delete removeFromCustomer_ptr;

}
