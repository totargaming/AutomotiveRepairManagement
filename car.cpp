#include "car.h"
#include "ui_entitylist.h"

// Constructor
Car::Car(QWidget* parent): EntityList(parent){
    qDebug() << "Car: Initializing Car";
    ui->nameSortBtn->setText("Sort by Model"); // Set the text of the nameSortBtn to "Load by Model"
    loadList(); // Load the list of cars
    addToCar_ptr = new AddToCar(); // Initialize the addToCar_ptr
    removeFromCar_ptr = new RemoveFromCar(); // Initialize the removeFromCar_ptr
    // Connect the carAdded signal from addToCar_ptr to the loadList slot in this class
    connect(addToCar_ptr, &AddToCar::carAdded, this, &Car::loadList);
    // Connect the carRemoved signal from removeFromCar_ptr to the loadList slot in this class
    connect(removeFromCar_ptr, &RemoveFromCar::carRemoved, this, &Car::loadList);
}

// Method to add a car
void Car::add() {
    qDebug() << "Car: add() called";
    addToCar_ptr->setWindowTitle("Car Information: Register"); // Set the window title of addToCar_ptr to "Car: Register"
    addToCar_ptr->show(); // Show the addToCar_ptr window
}

// Method to remove a car
void Car::remove() {
    qDebug() << "Car: remove() called";
    removeFromCar_ptr->setWindowTitle("Car Information: Remove"); // Set the window title of removeFromCar_ptr to "Car: Remove"
    removeFromCar_ptr->show(); // Show the removeFromCar_ptr window
    ui->txtInfo->clear();
}

// Method to load the list of cars
void Car::loadList() {
    qDebug() << "Car: Entering loadList";
    QSqlDatabase database = QSqlDatabase::database("DB"); // Get the database
    if (!database.isOpen()) { // If the database is not open
        qDebug() << "Car: Database is not open!";
        return; // Return
    }
    model = new QSqlQueryModel(); // Initialize the model
    model->setQuery("SELECT VehicleID, Model FROM Vehicle", database); // Set the query of the model
    ui->tableView->setModel(model); // Set the model of the tableView
    qDebug() << "Car: Exiting loadList";
}

// Method to sort the list of cars by ID
void Car::idSort() {
    qDebug() << "Car: Entering idSort";
    QSqlDatabase database = QSqlDatabase::database("DB"); // Get the database
    model = new QSqlQueryModel(); // Initialize the model
    model->setQuery("SELECT VehicleID, Model FROM Vehicle ORDER BY VehicleID", database); // Set the query of the model
    ui->tableView->setModel(model); // Set the model of the tableView
    qDebug() << "Car: Exiting idSort";
}

// Method to sort the list of cars by name
void Car::nameSort() {
    qDebug() << "Car: Entering nameSort";
    QSqlDatabase database = QSqlDatabase::database("DB"); // Get the database
    model = new QSqlQueryModel(); // Initialize the model
    model->setQuery("SELECT VehicleID, Model FROM Vehicle ORDER BY Model", database); // Set the query of the model
    ui->tableView->setModel(model); // Set the model of the tableView
    qDebug() << "Car: Exiting nameSort";
}

// Method to show the information of a car
void Car::showInfo(const QModelIndex &index) {
    qDebug() << "Car: Entering showInfo";

    int row = index.row(); // Get the row of the index
    QString vehicleId = ui->tableView->model()->data(ui->tableView->model()->index(row, 0)).toString(); // Get the vehicle ID

    QSqlDatabase database = QSqlDatabase::database("DB"); // Get the database
    if (!database.isOpen()) { // If the database is not open
        qDebug() << "Car: Database is not open!";
        return; // Return
    }

    QSqlQuery query(database); // Initialize the query
    query.prepare("SELECT * FROM Vehicle WHERE VehicleID = :vehicleId"); // Prepare the query
    query.bindValue(":vehicleId", vehicleId); // Bind the value of vehicleId to the query
    if (!query.exec()) { // If the query execution fails
        qDebug() << "Car: Failed to execute query(1)" << query.lastError();
        return; // Return
    }

    if (query.next()) { // If the query has a next result
        // Get the values from the query result
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
        QSqlQuery userQuery(database); // Initialize the userQuery
        userQuery.prepare("SELECT Name FROM Customer WHERE UserID = :userId"); // Prepare the userQuery
        userQuery.bindValue(":userId", userId); // Bind the value of userId to the userQuery
        if (!userQuery.exec()) { // If the userQuery execution fails
            qDebug() << "Car: Failed to execute user query(2)" << userQuery.lastError();
            return; // Return
        }

        QString customerName;

        if (userQuery.next()) { // If the userQuery has a next result
            customerName = userQuery.value("Name").toString(); // Get the customer name
        }

        // Set the text of txtInfo
        ui->txtInfo->setText("Vehicle ID: " + vehicleId + "\nModel: " + model + "\nBrand: " + brand + "\nDescription: " + description + "\nCustomer: " + customerName + "\nScheduled: " + scheduled+  "\nAssigned: " + assigned + "\nFinished: " + finished + "\nStart Date: " + startDate + "\nDeadline: " + deadline);
    }

    qDebug() << "Car: Exiting showInfo";
}
void Car::showEvent(QShowEvent *event) {
    QWidget::showEvent(event); // Call base class implementation
    loadList(); // Refresh the combo box
    qDebug() << "Car Widget shown";
}
// Destructor
Car::~Car() {
    qDebug() << "Car: Destructor called";
    delete addToCar_ptr; // Delete addToCar_ptr
    delete removeFromCar_ptr; // Delete removeFromCar_ptr
}
