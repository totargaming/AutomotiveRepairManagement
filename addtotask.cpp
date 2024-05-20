#include "addtotask.h"
#include "ui_addtotask.h"

// Constructor
AddToTask::AddToTask(QWidget *parent)
    : QDialog(parent) // Initialize QDialog with parent widget
    , ui(new Ui::AddToTask) // Initialize UI
{
    ui->setupUi(this); // Set up UI for this dialog
    database = QSqlDatabase::database("DB"); // Get the database instance
    if (!database.isValid() || !database.isOpen()) { // Check if the database is valid and open
        qDebug() << "AddToTask: Failed to initialize database"; // Log error message
        return;
    }
    qDebug() << "AddToTask: Successfully initialized database"; // Log success message
    loadBox(); // Load the combo boxes
}

// Destructor
AddToTask::~AddToTask()
{
    delete ui; // Delete the UI
}

// Method to load the combo boxes
void AddToTask::loadBox() {
    ui->modelBox->clear(); // Clear the model combo box
    ui->staffBox->clear(); // Clear the staff combo box

    // Load models
    QSqlQuery modelQuery(database); // Create a query
    modelQuery.prepare("SELECT Model FROM Vehicle WHERE Scheduled = 1 AND Assigned = 0 AND Finished = 0 AND StaffID IS NULL"); // Prepare the query
    if (!modelQuery.exec()) { // Execute the query
        qDebug() << "AddToTask: Failed to execute model query" << modelQuery.lastError().text(); // Log error message
        return;
    }
    while(modelQuery.next()){ // While there are more records
        ui->modelBox->addItem(modelQuery.value(0).toString()); // Add the model to the combo box
    }

    // Load staff
    QSqlQuery staffQuery(database); // Create a query
    staffQuery.prepare("SELECT Name FROM Staff WHERE Assigned = 0 AND VehicleID IS NULL"); // Prepare the query
    if (!staffQuery.exec()) { // Execute the query
        qDebug() << "AddToTask: Failed to execute staff query" << staffQuery.lastError().text(); // Log error message
        return;
    }
    while(staffQuery.next()){ // While there are more records
        ui->staffBox->addItem(staffQuery.value(0).toString()); // Add the staff name to the combo box
    }
}

// Method to handle the show event
void AddToTask::showEvent(QShowEvent *event)
{
    QDialog::showEvent(event); // Call base class implementation
    loadBox(); // Refresh the combo box
}

// Method to validate user input
bool AddToTask::validateUserInput() {
    if (ui->modelBox->currentText().isEmpty() || ui->staffBox->currentText().isEmpty()) { // Check if the model and staff are selected
        QMessageBox::warning(this, "Warning", "Please select a model and a staff member"); // Show warning message
        return false;
    }
    return true;
}

// Slot to handle the currentTextChanged signal of the model combo box
void AddToTask::on_modelBox_currentTextChanged(const QString &text)
{
    QSqlQuery query(database); // Create a query
    query.prepare("SELECT StartDate, Deadline FROM Vehicle WHERE Model = :Model"); // Prepare the query
    query.bindValue(":Model", text); // Bind the model value
    if (!query.exec()) { // Execute the query
        qDebug() << "AddToTask: Failed to execute query" << query.lastError().text(); // Log error message
        return;
    }

    QString startDate, deadline;
    if (query.next()) { // If there is a record
        startDate = query.value(0).toString(); // Get the start date
        deadline = query.value(1).toString(); // Get the deadline
    }

    // Set the labels
    ui->startDateLabel->setText("Start date: " + QDate::fromString(startDate, "yyyy-MM-dd").toString("dd/MM/yyyy"));
    ui->deadlineLabel->setText("Deadline: " + QDate::fromString(deadline, "yyyy-MM-dd").toString("dd/MM/yyyy"));
}

// Slot to handle the clicked signal of the add button
void AddToTask::on_addBtn_clicked()
{
    if (!validateUserInput()) { // Validate user input
        return;
    }

    QString modelName = ui->modelBox->currentText(); // Get the selected model
    QString staffName = ui->staffBox->currentText(); // Get the selected staff

    // Update Vehicle
    QSqlQuery vehicleQuery(database); // Create a query
    vehicleQuery.prepare("UPDATE Vehicle SET Assigned = 1, StaffID = (SELECT StaffID FROM Staff WHERE Name = :StaffName) WHERE Model = :ModelName"); // Prepare the query
    vehicleQuery.bindValue(":StaffName", staffName); // Bind the staff name
    vehicleQuery.bindValue(":ModelName", modelName); // Bind the model name
    if (!vehicleQuery.exec()) { // Execute the query
        qDebug() << "AddToTask: Failed to update Vehicle" << vehicleQuery.lastError().text(); // Log error message
        return;
    }

    // Update Staff
    QSqlQuery staffQuery(database); // Create a query
    staffQuery.prepare("UPDATE Staff SET Assigned = 1, VehicleID = (SELECT VehicleID FROM Vehicle WHERE Model = :ModelName) WHERE Name = :StaffName"); // Prepare the query
    staffQuery.bindValue(":ModelName", modelName); // Bind the model name
    staffQuery.bindValue(":StaffName", staffName); // Bind the staff name
    if (!staffQuery.exec()) { // Execute the query
        qDebug() << "AddToTask: Failed to update Staff" << staffQuery.lastError().text(); // Log error message
        return;
    }

    QMessageBox::information(this, "Success", "Task has been successfully added"); // Show success message
    emit taskAdded(); // Emit the taskAdded signal

    loadBox(); // Refresh the combo boxes
    close();
}

void AddToTask::on_cancelBtn_clicked()
{
    close();
}

