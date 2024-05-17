#include "storage.h"
#include "ui_storage.h"
#include <QRegularExpression>


// Constructor for the Storage class
Storage::Storage(QWidget *parent)
    : QDialog(parent) // Initialize the QDialog with the parent widget
    , ui(new Ui::Storage) // Initialize the UI for the Storage
{
    qDebug() << "Entering Storage constructor";
    ui->setupUi(this); // Set up the UI for this widget
    loadAll(); // Load all data
    addToStorage_ptr = new addToStorage(); // Initialize addToStorage_ptr
    partUpdate_ptr = new PartUpdate(); // Initialize partUpdate_ptr
    // Connect the partAdded signal from addToStorage to the loadAll slot in this class
    connect(addToStorage_ptr, &addToStorage::partAdded, this, &Storage::loadAll);
    // Connect the partUpdated signal from PartUpdate to the loadAll slot in this class
    connect(partUpdate_ptr, &PartUpdate::partUpdated, this, &Storage::loadAll);
    qDebug() << "Exiting Storage constructor";
}

// Destructor for the Storage class
Storage::~Storage()
{
    qDebug() << "Entering Storage destructor";
    delete ui; // Delete the UI
    delete addToStorage_ptr; // Delete the addToStorage_ptr
    delete partUpdate_ptr; // Delete the partUpdate_ptr
    qDebug() << "Exiting Storage destructor";
}
void Storage::showEvent(QShowEvent *event) {
    QWidget::showEvent(event); // Call base class implementation
    loadAll(); // Refresh the combo box
    qDebug() << "Storage Widget shown";
}
// Function to load all data
void Storage::loadAll() {
    qDebug() << "Storage: Entering loadAll";
    QSqlDatabase database = QSqlDatabase::database("DB"); // Get the database
    if (!database.isOpen()) { // If the database is not open
        qDebug() << "Storage: Database is not open!";
        return; // Return from the function
    }
    model = new QSqlQueryModel(); // Create a new QSqlQueryModel
    model->setQuery("SELECT Name, Quantity FROM Storage", database); // Set the query for the model

    ui->tableView->setModel(model); // Set the model for the tableView
    qDebug() << "Storage: Exiting loadAll";
}

// Function to handle the click event of the search button

void Storage::on_searchBtn_clicked()
{
    qDebug() << "Storage: Entering on_searchBtn_clicked";
    QString partName = ui->input->text(); // Get the text from the input
    qDebug() << "Part: " << partName;
    QSqlDatabase database = QSqlDatabase::database("DB"); // Get the database

    model = new QSqlQueryModel(); // Create a new QSqlQueryModel

    // Validate input to accept only letters
    QRegularExpression regex("^[a-zA-Z]*$");
    if (!regex.match(partName).hasMatch()) {
        qDebug() << "Storage: Invalid input. Only letters are allowed.";
        return;
    }

    if(partName.isEmpty()) { // If the partName is empty
        loadAll(); // Load all data
    }
    else {
        QString queryString = "SELECT * FROM Storage WHERE name LIKE '%" + partName + "%'";
        model->setQuery(queryString, database); // Set the query for the model
        if (model->lastError().isValid()) { // If the query execution fails
            qDebug() << "Storage: Failed to execute query" << model->lastError();
            return; // Return from the function
        }
        ui->tableView->setModel(model); // Set the model for the tableView
    }
    qDebug() << "Storage: Exiting on_searchBtn_clicked";
}

// Function to handle the click event of the refresh button
void Storage::on_refreshBtn_clicked()
{
    qDebug() << "Storage: Entering on_refreshBtn_clicked";
    loadAll(); // Load all data
    qDebug() << "Storage: Exiting on_refreshBtn_clicked";
}

// Function to handle the click event of the add button
void Storage::on_addBtn_clicked()
{
    qDebug() << "Storage: Entering on_addBtn_clicked";
    addToStorage_ptr->setWindowTitle("Storage: Import"); // Set the window title for addToStorage_ptr
    addToStorage_ptr->show(); // Show the addToStorage_ptr
    qDebug() << "Storage: Exiting on_addBtn_clicked";
}

// Function to handle the click event of the update button
void Storage::on_updateBtn_clicked()
{
    qDebug() << "Storage: Entering on_updateBtn_clicked";
    partUpdate_ptr->setWindowTitle("Storage: Update"); // Set the window title for partUpdate_ptr
    partUpdate_ptr->show(); // Show the partUpdate_ptr
    qDebug() << "Storage: Exiting on_updateBtn_clicked";
}
