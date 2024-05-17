#include "addtomaintenance.h"
#include "ui_addtomaintenance.h"

// Constructor
AddToMaintenance::AddToMaintenance(QWidget *parent)
    : QDialog(parent) // Initialize QDialog with parent widget
    , ui(new Ui::AddToMaintenance) // Initialize UI
{
    ui->setupUi(this); // Set up the user interface for this dialog
    database = QSqlDatabase::database("DB"); // Get the database instance named "DB"
    
    // Check if the database is valid and open
    if (!database.isValid() || !database.isOpen()) {
        qDebug() << "Database is not valid or open";
        return;
    }
    qDebug() << "Database initialized successfully";
    
    loadBox(); // Load the combo box with data
}

// Destructor
AddToMaintenance::~AddToMaintenance()
{
    delete ui; // Delete the UI
}

// Function to validate user input
bool AddToMaintenance::validateUserInput() {
    qDebug() << "Validating user input";

    // Check if the model box is empty
    if(ui->modelBox->currentText().isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Model box is empty");
        qDebug() << "Model box is empty";
        return false;
    }

    // Get the start and deadline dates
    QDate startDate = ui->startDateEdit->date();
    QDate deadlineDate = ui->deadlineDateEdit->date();

    // Check if the start date is in the past
    if(startDate < QDate::currentDate()) {
        QMessageBox::warning(this, "Validation Error", "Start date cannot be in the past");
        qDebug() << "Start date is in the past";
        return false;
    }

    // Check if the deadline date is before or the same as the start date
    if(deadlineDate <= startDate) {
        QMessageBox::warning(this, "Validation Error", "Deadline date should be after start date");
        qDebug() << "Deadline date is not after start date";
        return false;
    }

    qDebug() << "User input validated successfully";
    return true;
}

// Function to load the combo box with data
void AddToMaintenance::loadBox() {
    ui->modelBox->clear(); // Clear the combo box
    qDebug() << "Loading combo box";
    
    QSqlQuery query(database); // Create a query
    query.prepare("SELECT Model FROM Vehicle WHERE Scheduled = 0"); // Prepare the query

    // Execute the query
    if(query.exec()) {
        // Loop through the results
        while(query.next()) {
            ui->modelBox->addItem(query.value(0).toString()); // Add each result to the combo box
            qDebug() << "Added item to combo box: " << query.value(0).toString();
        }
    } else {
        QMessageBox::warning(this, "Database Error", "Failed to load models");
        qDebug() << "Failed to load models from database";
    }

    // Set the start and deadline dates to the current date
    ui->startDateEdit->setDate(QDate::currentDate());
    ui->deadlineDateEdit->setDate(QDate::currentDate());

    qDebug() << "Set start and deadline dates to current date";
}

// Function to handle the add button click event
void AddToMaintenance::on_addBtn_clicked() {
    qDebug() << "Add button clicked";
    
    // Validate the user input
    if(!validateUserInput()) {
        return;
    }

    QSqlQuery query(database); // Create a query
    // Prepare the query
    query.prepare("UPDATE Vehicle SET Scheduled = 1, StartDate = :startDate, Deadline = :deadline WHERE Model = :model");
    // Bind the values to the query
    query.bindValue(":startDate", ui->startDateEdit->date().toString("yyyy-MM-dd"));
    query.bindValue(":deadline", ui->deadlineDateEdit->date().toString("yyyy-MM-dd"));
    query.bindValue(":model", ui->modelBox->currentText());

    // Execute the query
    if(!query.exec()) {
        QMessageBox::warning(this, "Database Error", "Failed to update vehicle");
        qDebug() << "Failed to update vehicle in database";
        return;
    }
    
    QMessageBox::information(this, "Success", "Maintenance information added successfully.");
    loadBox(); // Refresh the combo box
    emit assigned(); // Emit the assigned signal
    close();
}

// Function to handle the show event
void AddToMaintenance::showEvent(QShowEvent *event) {
    QDialog::showEvent(event); // Call base class implementation
    loadBox(); // Refresh the combo box
    qDebug() << "Dialog shown";
}
