#include "removefrommaintenance.h"
#include "ui_removefrommaintenance.h"

// Constructor
RemoveFromMaintenance::RemoveFromMaintenance(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RemoveFromMaintenance)
{
    // Setup UI
    ui->setupUi(this);

    // Get database connection
    database = QSqlDatabase::database("DB");

    // Check if database is valid and open
    if (!database.isValid() || !database.isOpen()) {
        qDebug() << "RemoveFromCar: Failed to initialize database";
        return;
    }

    qDebug() << "RemoveFromCar: Successfully initialized database";

    // Load the combo box with data
    loadBox();
}

// Destructor
RemoveFromMaintenance::~RemoveFromMaintenance()
{
    // Delete UI object
    delete ui;
}

// Function to validate user input
bool RemoveFromMaintenance::validateUserInput() {
    // Get selected item from combo box
    QString selectedItem = ui->removeList->currentText();

    // Check if item is selected
    if (selectedItem.isEmpty()) {
        // Show warning message if no item is selected
        QMessageBox::warning(this, "Warning", "Please select an item");
        return false;
    }

    // Return true if item is selected
    return true;
}

// Function to handle show event
void RemoveFromMaintenance::showEvent(QShowEvent *event)
{
    // Call base class implementation
    QDialog::showEvent(event);

    // Refresh the combo box
    loadBox();
    qDebug() << "Dialog shown";

}

// Function to load data into combo box
void RemoveFromMaintenance::loadBox() {
    // Clear combo box
    ui->removeList->clear();

    // Prepare SQL query
    QSqlQuery query(database);
    query.prepare("SELECT Model FROM Vehicle WHERE Scheduled = 1");

    // Execute SQL query
    if (!query.exec()) {
        qDebug() << "RemoveFromMaintenance: Failed to execute query" << query.lastError().text();
        return;
    }

    // Add items to combo box
    while(query.next()){
        ui->removeList->addItem(query.value(0).toString());
        qDebug() << "RemoveFromMaintenance: Filling removeList" << query.value(0).toString();
    }

    qDebug() << "RemoveFromMaintenance: Last query" << query.lastQuery();
    qDebug() << "RemoveFromMaintenance: Last error" << query.lastError().text();
}

// Function to handle change in selected item in combo box
void RemoveFromMaintenance::on_removeList_currentTextChanged(const QString &text)
{
    // Prepare SQL query
    QSqlQuery query(database);
    query.prepare("SELECT StaffID, StartDate, Deadline FROM Vehicle WHERE Model = :Model");
    query.bindValue(":Model", text);

    // Execute SQL query
    if (!query.exec()) {
        qDebug() << "RemoveFromMaintenance: Failed to execute query" << query.lastError().text();
        return;
    }

    QString staffId, startDate, deadline;
    if (query.next()) {
        // Get staff ID, start date, and deadline
        staffId = query.value(0).toString();
        startDate = query.value(1).toString();
        deadline = query.value(2).toString();
    }

    // Prepare SQL query to get staff name
    query.prepare("SELECT Name FROM Staff WHERE StaffID = :staffId");
    query.bindValue(":staffId", staffId);

    // Execute SQL query
    if (!query.exec()) {
        qDebug() << "RemoveFromMaintenance: Failed to execute query" << query.lastError().text();
        return;
    }

    QString staffName = "Not Assigned";
    if (query.next()) {
        // Get staff name
        staffName = query.value(0).toString();
        if(staffName.isEmpty()) {
            staffName = "Not Assigned";
        }
    }

    // Set staff name, start date, and deadline in UI
    ui->staffNameReport->setText("Staff: " + staffName);
    ui->startDateReport->setText("Start date: " + QDate::fromString(startDate, "yyyy-MM-dd").toString("dd/MM/yyyy"));
    ui->deadlineReport->setText("Deadline: " + QDate::fromString(deadline, "yyyy-MM-dd").toString("dd/MM/yyyy"));
}

// Function to handle click event of remove button
void RemoveFromMaintenance::on_removeBtn_clicked()
{
    // Validate user input
    if (!validateUserInput()) {
        return;
    }

    // Get selected item from combo box
    QString selectedItem = ui->removeList->currentText();

    // Prepare SQL query to get staff ID
    QSqlQuery query(database);
    query.prepare("SELECT StaffID FROM Vehicle WHERE Model = :Model");
    query.bindValue(":Model", selectedItem);

    // Execute SQL query
    if (!query.exec()) {
        qDebug() << "RemoveFromMaintenance: Failed to execute query" << query.lastError().text();
        return;
    }

    QString staffId;
    if (query.next()) {
        // Get staff ID
        staffId = query.value(0).toString();
    }

    // Prepare SQL query to update vehicle
    query.prepare("UPDATE Vehicle SET Scheduled = 0, Assigned = 0, Finished = 0, StartDate = NULL, Deadline = NULL, StaffID = NULL WHERE Model = :Model");
    query.bindValue(":Model", selectedItem);

    // Execute SQL query
    if (query.exec()) {
        qDebug() << "RemoveFromMaintenance: Vehicle updated successfully";
    } else {
        qDebug() << "RemoveFromMaintenance: Failed to update vehicle" << query.lastError().text();
        return;
    }

    // Prepare SQL query to update staff
    query.prepare("UPDATE Staff SET VehicleID = NULL, Assigned = 0 WHERE StaffID = :staffId");
    query.bindValue(":staffId", staffId);

    // Execute SQL query
    if (query.exec()) {
        qDebug() << "RemoveFromMaintenance: Staff updated successfully";
        QMessageBox::information(this, "Success", "Item updated successfully");
    } else {
        qDebug() << "RemoveFromMaintenance: Failed to update staff" << query.lastError().text();
        QMessageBox::critical(this, "Error", "Failed to update item: " + query.lastError().text());
    }

    // Refresh the combo box
    loadBox();

    // Emit signal that maintenance has been removed
    emit maintenanceRemoved();
    close();
}
