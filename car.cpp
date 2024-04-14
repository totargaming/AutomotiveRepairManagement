#include "car.h"
#include "ui_entitylist.h"

Car::Car(QWidget* parent): EntityList(parent){
    qDebug() << "Car: Initializing Car";
    ui->nameSortBtn->setText("Load by Model");
    loadList();
    addToCar_ptr = new AddToCar();
    removeFromCar_ptr = new RemoveFromCar();
    connect(addToCar_ptr, &AddToCar::carAdded, this, &Car::loadList);
    connect(removeFromCar_ptr, &RemoveFromCar::carRemoved, this, &Car::loadList);
}


void Car::add() {
    qDebug() << "Car: add() called";
    addToCar_ptr->setWindowTitle("Car: Register");
    addToCar_ptr->show();
}

void Car::remove() {
    qDebug() << "Car: remove() called";
    removeFromCar_ptr->setWindowTitle("Car: Remove");
    removeFromCar_ptr->show();
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
        qDebug() << "Car: Failed to execute query(1)" << query.lastError();
        return;
    }

    if (query.next()) {
        QString model = query.value("Model").toString();
        QString brand = query.value("Brand").toString();

        QString assigned = (query.value("Assigned").toInt() == 1) ? "Yes" : "No";
        QString scheduled = (query.value("Scheduled").toInt() == 1) ? "Yes" : "No";

        QString finished = (query.value("Finished").toInt() == 1) ? "Yes" : "No";


        QString description = query.value("Description").toString();
        QString userId = query.value("UserID").toString();
        QString startDate = query.value("StartDate").toString();
        if (startDate.isEmpty()) {
            startDate = "Not scheduled";
        } else {
            // Convert to QDate and format it
            startDate = QDate::fromString(startDate, "yyyy-MM-dd").toString("dd/MM/yyyy");
        }

        QString deadline = query.value("Deadline").toString();
        if (deadline.isEmpty()) {
            deadline = "Not scheduled";
        } else {
            // Convert to QDate and format it
            deadline = QDate::fromString(deadline, "yyyy-MM-dd").toString("dd/MM/yyyy");
        }
        QSqlQuery userQuery(database);
        userQuery.prepare("SELECT Name FROM Customer WHERE UserID = :userId");
        userQuery.bindValue(":userId", userId);
        if (!userQuery.exec()) {
            qDebug() << "Car: Failed to execute user query(2)" << userQuery.lastError();
            return;
        }

        QString customerName;

        if (userQuery.next()) {
            customerName = userQuery.value("Name").toString();
        }

        ui->txtInfo->setText("Vehicle ID: " + vehicleId + "\nModel: " + model + "\nBrand: " + brand + "\nDescription: " + description + "\nCustomer: " + customerName + "\nScheduled: " + scheduled+  "\nAssigned: " + assigned + "\nFinished: " + finished + "\nStart Date: " + startDate + "\nDeadline: " + deadline);
    }

    qDebug() << "Car: Exiting showInfo";
}

Car::~Car() {
    qDebug() << "Car: Destructor called";
    delete addToCar_ptr;
    delete removeFromCar_ptr;
}
