#include "staff.h"
#include "ui_entitylist.h"

// Constructor for Staff class
Staff::Staff(QWidget *parent): EntityList(parent) {
    qDebug() << "Staff: Initializing Staff";
    loadList(); // Load the list of staff
    ui->label->setText("STAFF INFO");
    addToStaff_ptr = new AddToStaff(); // Create a new instance of AddToStaff
    removeFromStaff_ptr = new RemoveFromStaff(); // Create a new instance of RemoveFromStaff
    // Connect the staffAdded signal from addToStaff_ptr to the loadList slot in this class
    connect(addToStaff_ptr, &AddToStaff::staffAdded, this, &Staff::loadList);
    // Connect the staffRemoved signal from removeFromStaff_ptr to the loadList slot in this class
    connect(removeFromStaff_ptr, &RemoveFromStaff::staffRemoved, this, &Staff::loadList);
}

void Staff::showEvent(QShowEvent *event) {
    QWidget::showEvent(event); // Call base class implementation
    loadList(); // Refresh the combo box
    qDebug() << "Staff Widget shown";
}
// Function to add a staff member
void Staff::add() {
    qDebug() << "Staff: add() called";
    addToStaff_ptr->setWindowTitle("Staff: Recruit"); // Set the window title
    addToStaff_ptr->show(); // Show the window
}

// Function to remove a staff member
void Staff::remove() {
    qDebug() << "Staff: remove() called";
    removeFromStaff_ptr->setWindowTitle("Staff Information: Layoff"); // Set the window title
    removeFromStaff_ptr->show(); // Show the window
    ui->txtInfo->clear(); // Clear the info text
}

// Function to show information about a staff member
void Staff::showInfo(const QModelIndex &index) {
    qDebug() << "Staff: Entering showInfo";

    int row = index.row(); // Get the row number from the index
    // Get the staff ID from the model
    QString staffId = ui->tableView->model()->data(ui->tableView->model()->index(row, 0)).toString();

    // Get the database connection
    QSqlDatabase database = QSqlDatabase::database("DB");
    if (!database.isOpen()) { // Check if the database is open
        qDebug() << "Staff: Database is not open!";
        return;
    }

    // Prepare a query to select the staff member with the given ID
    QSqlQuery query(database);
    query.prepare("SELECT * FROM Staff WHERE StaffID = :staffId");
    query.bindValue(":staffId", staffId);
    if (!query.exec()) { // Execute the query
        qDebug() << "Staff: Failed to execute query" << query.lastError();
        return;
    }

    // If the query returned a result
    if (query.next()) {
        // Get the staff member's details from the query result
        QString name = query.value("Name").toString();
        QString phone = query.value("Phone").toString();
        int wage = query.value("Wage").toInt();
        QString assigned = (query.value("Assigned").toInt() == 1) ? "Yes" : "No";
        QString vehicleId = query.value("VehicleID").isNull() ? "Not assigned" : query.value("VehicleID").toString();

        // Fetch the model from the Vehicle table
        QString model;
        if (vehicleId != "Not assigned") {
            // Prepare a query to select the vehicle with the given ID
            QSqlQuery vehicleQuery(database);
            vehicleQuery.prepare("SELECT Model FROM Vehicle WHERE VehicleID = :vehicleId");
            vehicleQuery.bindValue(":vehicleId", vehicleId);
            if (!vehicleQuery.exec()) { // Execute the query
                qDebug() << "Staff: Failed to execute vehicle query" << vehicleQuery.lastError();
                return;
            }

            // If the query returned a result
            if (vehicleQuery.next()) {
                model = vehicleQuery.value("Model").toString(); // Get the vehicle model from the query result
            }
        } else {
            model = "Not assigned";
        }

        // Set the info text to the staff member's details
        ui->txtInfo->setText("Staff ID: " + staffId + "\nName: " + name + "\nPhone: " + phone + "\nWage: " + QString::number(wage) + "\nAssigned: " + assigned + "\nVehicle Model: " + model);
    }

    qDebug() << "Staff: Exiting showInfo";
}

// Function to load the list of staff members
void Staff::loadList() {
    qDebug() << "Staff: Entering loadList";
    QSqlDatabase database = QSqlDatabase::database("DB"); // Get the database connection
    if (!database.isOpen()) { // Check if the database is open
        qDebug() << "Staff: Database is not open!";
        return;
    }
    model = new QSqlQueryModel(); // Create a new query model
    model->setQuery("SELECT StaffID, Name FROM Staff", database); // Set the query for the model
    ui->tableView->setModel(model); // Set the model for the table view
    qDebug() << "Staff: Exiting loadList";
}

// Function to sort the list of staff members by ID
void Staff::idSort() {
    qDebug() << "Staff: Entering idSort";
    QSqlDatabase database = QSqlDatabase::database("DB"); // Get the database connection
    model = new QSqlQueryModel(); // Create a new query model
    model->setQuery("SELECT StaffID, Name FROM Staff ORDER BY StaffID", database); // Set the query for the model
    ui->tableView->setModel(model); // Set the model for the table view
    qDebug() << "Staff: Exiting idSort";
}

// Function to sort the list of staff members by name
void Staff::nameSort() {
    qDebug() << "Staff: Entering nameSort";
    QSqlDatabase database = QSqlDatabase::database("DB"); // Get the database connection
    model = new QSqlQueryModel(); // Create a new query model
    model->setQuery("SELECT StaffID, Name FROM Staff ORDER BY Name", database); // Set the query for the model
    ui->tableView->setModel(model); // Set the model for the table view
    qDebug() << "Staff: Exiting nameSort";
}

// Destructor for Staff class
Staff::~Staff() {
    qDebug() << "Car: Destructor called";
    delete addToStaff_ptr; // Delete the AddToStaff instance
    delete removeFromStaff_ptr; // Delete the RemoveFromStaff instance
}
