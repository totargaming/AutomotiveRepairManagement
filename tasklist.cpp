#include "tasklist.h"
#include "ui_entitylist.h"
TaskList::TaskList(QWidget* parent): EntityList(parent) {
    qDebug() << "TaskList: Initializing TaskList";
}
// void TaskList::add() {

// }

// void TaskList::remove() {
//     qDebug() << "TaskList: Entering remove";

//     QModelIndex index = ui->tableView->currentIndex();
//     if (!index.isValid()) {
//         qDebug() << "TaskList: Invalid index";
//         return;
//     }

//     int row = index.row();
//     QString modelName = ui->tableView->model()->data(ui->tableView->model()->index(row, 0)).toString();

//     QSqlDatabase database = QSqlDatabase::database("DB");
//     if (!database.isOpen()) {
//         qDebug() << "TaskList: Database is not open!";
//         return;
//     }

//     QSqlQuery query(database);
//     query.prepare("SELECT UserID, StaffID FROM Vehicle WHERE Model = :modelName");
//     query.bindValue(":modelName", modelName);
//     if (!query.exec()) {
//         qDebug() << "TaskList: Failed to execute query(1)" << query.lastError();
//         return;
//     }

//     if (query.next()) {
//         QString userId = query.value("UserID").toString();
//         QString staffId = query.value("StaffID").toString();

//         // Delete customer info
//         QSqlQuery deleteCustomerQuery(database);
//         deleteCustomerQuery.prepare("DELETE FROM Customer WHERE UserID = :userId");
//         deleteCustomerQuery.bindValue(":userId", userId);
//         if (!deleteCustomerQuery.exec()) {
//             qDebug() << "TaskList: Failed to execute delete customer query" << deleteCustomerQuery.lastError();
//             return;
//         }

//         // Update staff info
//         QSqlQuery updateStaffQuery(database);
//         updateStaffQuery.prepare("UPDATE Staff SET Assigned = 0, VehicleID = NULL WHERE StaffID = :staffId");
//         updateStaffQuery.bindValue(":staffId", staffId);
//         if (!updateStaffQuery.exec()) {
//             qDebug() << "TaskList: Failed to execute update staff query" << updateStaffQuery.lastError();
//             return;
//         }

//         // Delete vehicle info
//         QSqlQuery deleteVehicleQuery(database);
//         deleteVehicleQuery.prepare("DELETE FROM Vehicle WHERE Model = :modelName");
//         deleteVehicleQuery.bindValue(":modelName", modelName);
//         if (!deleteVehicleQuery.exec()) {
//             qDebug() << "TaskList: Failed to execute delete vehicle query" << deleteVehicleQuery.lastError();
//             return;
//         }
//     }

//     qDebug() << "TaskList: Exiting remove";
// }

void TaskList::showInfo(const QModelIndex &index) {
    qDebug() << "TaskList: Entering showInfo";

    int row = index.row();
    QString modelName = ui->tableView->model()->data(ui->tableView->model()->index(row, 0)).toString();

    QSqlDatabase database = QSqlDatabase::database("DB");
    if (!database.isOpen()) {
        qDebug() << "TaskList: Database is not open!";
        return;
    }

    QSqlQuery query(database);
    query.prepare("SELECT * FROM Vehicle WHERE Model = :modelName");
    query.bindValue(":modelName", modelName);
    if (!query.exec()) {
        qDebug() << "TaskList: Failed to execute query(1)" << query.lastError();
        return;
    }

    if (query.next()) {
        QString startDate = query.value("StartDate").toString();
        QString deadline = query.value("Deadline").toString();
        QString finished = (query.value("Finished").toInt() == 1) ? "Yes" : "No";
        QString userId = query.value("UserID").toString();

        // Calculate days remaining
        QDate deadlineDate = QDate::fromString(deadline, "yyyy-MM-dd");
        int daysRemaining = QDate::currentDate().daysTo(deadlineDate);

        QSqlQuery userQuery(database);
        userQuery.prepare("SELECT Name, Phone FROM Customer WHERE UserID = :userId");
        userQuery.bindValue(":userId", userId);
        if (!userQuery.exec()) {
            qDebug() << "TaskList: Failed to execute user query(2)" << userQuery.lastError();
            return;
        }

        QString customerName;
        QString customerPhone;

        if (userQuery.next()) {
            customerName = userQuery.value("Name").toString();
            customerPhone = userQuery.value("Phone").toString();
        }

        ui->txtInfo->setText("Start Date: " + startDate + "\nDeadline: " + deadline + "\nDays remaining: " + QString::number(daysRemaining) + "\nFinished: " + finished + "\nCustomer name: " + customerName + "\nCustomer's phone number: " + customerPhone);
    }

    qDebug() << "TaskList: Exiting showInfo";
}

void TaskList::loadList(){
    qDebug() << taskType();
    loadList(taskType());
}
QString TaskList::taskType() {

}
void TaskList::loadList(QString taskType) {
    qDebug() << "TaskList: Entering loadList";
    QSqlDatabase database = QSqlDatabase::database("DB");
    if (!database.isOpen()) {
        qDebug() << "TaskList: Database is not open!";
        return;
    }
    model = new QSqlQueryModel();

    QString queryString = "SELECT Vehicle.Model, Staff.Name "
                          "FROM Vehicle "
                          "INNER JOIN Staff ON Vehicle.StaffID = Staff.StaffID ";

    if (taskType == "Maintenance") {
        queryString += "WHERE Vehicle.Assigned = 1 AND Vehicle.Finished = 0";
    } else {
        queryString += "WHERE Vehicle.Assigned = 1 AND Vehicle.Finished = 1";
    }

    model->setQuery(queryString, database);
    ui->tableView->setModel(model);
    qDebug() << "TaskList: Exiting loadList";
}

void TaskList::idSort(){
    qDebug() << taskType();

    idSort(taskType());
}

void TaskList::nameSort(){
    qDebug() << taskType();

    nameSort(taskType());
}
void TaskList::idSort(QString taskType) {
    qDebug() << "TaskList: Entering idSort";
    QSqlDatabase database = QSqlDatabase::database("DB");
    model = new QSqlQueryModel();

    QString queryString = "SELECT Vehicle.Model, Staff.Name "
                          "FROM Vehicle "
                          "INNER JOIN Staff ON Vehicle.StaffID = Staff.StaffID ";

    if (taskType == "Maintenance") {
        queryString += "WHERE Vehicle.Assigned = 1 AND Vehicle.Finished = 0 ORDER BY Vehicle.VehicleID";
    } else {
        queryString += "WHERE Vehicle.Assigned = 1 AND Vehicle.Finished = 1 ORDER BY Vehicle.VehicleID";
    }

    model->setQuery(queryString, database);
    ui->tableView->setModel(model);
    qDebug() << "TaskList: Exiting idSort";
}

void TaskList::nameSort(QString taskType) {
    qDebug() << "TaskList: Entering nameSort";
    QSqlDatabase database = QSqlDatabase::database("DB");
    model = new QSqlQueryModel();

    QString queryString = "SELECT Vehicle.Model, Staff.Name "
                          "FROM Vehicle "
                          "INNER JOIN Staff ON Vehicle.StaffID = Staff.StaffID ";

    if (taskType == "Maintenance") {
        queryString += "WHERE Vehicle.Assigned = 1 AND Vehicle.Finished = 0 ORDER BY Vehicle.Model";
    } else {
        queryString += "WHERE Vehicle.Assigned = 1 AND Vehicle.Finished = 1 ORDER BY Vehicle.Model";
    }

    model->setQuery(queryString, database);
    ui->tableView->setModel(model);
    qDebug() << "TaskList: Exiting nameSort";
}

TaskList::~TaskList(){

}
