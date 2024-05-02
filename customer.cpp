#include "customer.h"
#include "ui_entitylist.h"

// Constructor
Customer::Customer(QWidget* parent): EntityList(parent) {
    qDebug() << "Customer: Initializing Customer";
    // Hide the add button
    ui->addBtn->setVisible(false);
    // Load the list of customers
    loadList();
    // Create a new RemoveFromCustomer object
    removeFromCustomer_ptr = new RemoveFromCustomer();
    // Connect the customerRemoved signal from removeFromCustomer_ptr to the loadList slot
    connect(removeFromCustomer_ptr, &RemoveFromCustomer::customerRemoved, this, &Customer::loadList);
}

// Add function (currently empty)
void Customer::add() {

}

// Remove function
void Customer::remove() {
    qDebug() << "Car: remove() called";
    // Set the window title of removeFromCustomer_ptr
    removeFromCustomer_ptr->setWindowTitle("Car: Remove");
    // Show the removeFromCustomer_ptr window
    removeFromCustomer_ptr->show();
    ui->txtInfo->clear();
}

// Show information about a customer
void Customer::showInfo(const QModelIndex &index) {
    qDebug() << "Customer: Entering showInfo";

    // Get the row number from the index
    int row = index.row();
    // Get the UserId from the model
    QString UserId = ui->tableView->model()->data(ui->tableView->model()->index(row, 0)).toString();

    // Get the database
    QSqlDatabase database = QSqlDatabase::database("DB");
    // Check if the database is open
    if (!database.isOpen()) {
        qDebug() << "Car: Database is not open!";
        return;
    }

    // Prepare a query to select all from Customer where UserId matches
    QSqlQuery query(database);
    query.prepare("SELECT * FROM Customer WHERE UserID = :UserId");
    query.bindValue(":UserId", UserId);
    // Execute the query
    if (!query.exec()) {
        qDebug() << "Car: Failed to execute query(1)" << query.lastError();
        return;
    }

    // If the query returns a result
    if (query.next()) {
        // Get the name, phone number, and vehicle ID from the query result
        QString name = query.value("Name").toString();
        QString phoneNumber = query.value("Phone").toString();
        QString vehicleId = query.value("VehicleID").toString();

        // Prepare a query to select the model and brand from Vehicle where VehicleId matches
        QSqlQuery userQuery(database);
        userQuery.prepare("SELECT Model, Brand FROM Vehicle WHERE VehicleID = :VehicleId");
        userQuery.bindValue(":VehicleId", vehicleId);
        // Execute the query
        if (!userQuery.exec()) {
            qDebug() << "Car: Failed to execute user query(2)" << userQuery.lastError();
            return;
        }

        QString model;
        QString brand;

        // If the query returns a result
        if (userQuery.next()) {
            // Get the model and brand from the query result
            model = userQuery.value("Model").toString();
            brand = userQuery.value("Brand").toString();
        }

        // Set the text in the info text box
        ui->txtInfo->setText("Name: " + name + "\nPhone: " + phoneNumber + "\nVehicle ID: " + vehicleId + "\nModel: " + model + "\nBrand: " + brand);
    }

    qDebug() << "Customer: Exiting showInfo";
}

// Load the list of customers
void Customer::loadList() {
    qDebug() << "Customer: Entering loadList";
    // Get the database
    QSqlDatabase database = QSqlDatabase::database("DB");
    // Check if the database is open
    if (!database.isOpen()) {
        qDebug() << "Customer: Database is not open!";
        return;
    }
    // Create a new QSqlQueryModel
    model = new QSqlQueryModel();
    // Set the query to select UserId and Name from Customer
    model->setQuery("SELECT UserID, Name FROM Customer", database);
    // Set the model for the table view
    ui->tableView->setModel(model);
    qDebug() << "Customer: Exiting loadList";
}

// Sort by ID
void Customer::idSort() {
    qDebug() << "Customer: Entering idSort";
    // Get the database
    QSqlDatabase database = QSqlDatabase::database("DB");
    // Create a new QSqlQueryModel
    model = new QSqlQueryModel();
    // Set the query to select UserId and Name from Customer, ordered by UserId
    model->setQuery("SELECT UserID, Name FROM Customer ORDER BY UserID", database);
    qDebug() << "Customer: Row count: " << model->rowCount();
    // Set the model for the table view
    ui->tableView->setModel(model);
    qDebug() << "Customer: Exiting idSort";
}

// Sort by name
void Customer::nameSort() {
    qDebug() << "Customer: Entering nameSort";
    // Get the database
    QSqlDatabase database = QSqlDatabase::database("DB");
    // Create a new QSqlQueryModel
    model = new QSqlQueryModel();
    // Set the query to select UserId and Name from Customer, ordered by Name
    model->setQuery("SELECT UserID, Name FROM Customer ORDER BY Name", database);
    qDebug() << "Customer: Row count: " << model->rowCount();
    // Set the model for the table view
    ui->tableView->setModel(model);
    qDebug() << "Customer: Exiting nameSort";
}

// Destructor
Customer::~Customer() {
    qDebug() << "Customer: Destructor called";
    // Delete removeFromCustomer_ptr
    delete removeFromCustomer_ptr;
}
