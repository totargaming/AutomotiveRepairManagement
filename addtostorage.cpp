#include "addtostorage.h"
#include "ui_addtostorage.h"

// Constructor
addToStorage::addToStorage(QWidget *parent)
    : QDialog(parent) // Initialize QDialog with parent widget
    , ui(new Ui::addToStorage) // Initialize UI
{
    ui->setupUi(this); // Set up the user interface for this dialog
    database = QSqlDatabase::database("DB"); // Get the database instance named "DB"
    qDebug() << "Database initialized successfully";
}

// Destructor
addToStorage::~addToStorage()
{
    delete ui; // Delete the UI
    qDebug() << "UI deleted successfully";
}

// Function to handle the add button click event
void addToStorage::on_addBtn_clicked()
{
    // Validate the user input
    if (validateUserInput()) {
        // Get the part name and quantity from the UI
        QString partName = ui->input->text();
        int quantity = ui->quantitySelect->value();

        // Log the part name and quantity
        qDebug() << "partName: " << partName << "Quantity: " << quantity;

        // Prepare a query to insert the part name and quantity into the database
        QSqlQuery query(database);
        query.prepare("insert into Storage (name, quantity) values(:name, :quantity)");
        query.bindValue(":name", partName);
        query.bindValue(":quantity", quantity);
        query.exec();
        query.finish();
        query.clear();

        // Emit the partAdded signal
        emit partAdded();

        // Log the last error text from the query
        qDebug() << "No error: " << query.lastError().text();

        // Show a success message
        QMessageBox::information(this, "Success", "Added successfully!");

        // Reset the input fields
        reset();
        close();
    }
}

// Function to reset the input fields
void addToStorage::reset() {
    ui->input->clear(); // Clear the input field
    ui->quantitySelect->clear(); // Clear the quantity select field
    qDebug() << "Input fields reset";
}

// Function to validate user input
bool addToStorage::validateUserInput() {
    // Get the part name and quantity from the UI
    QString partName = ui->input->text();
    int quantity = ui->quantitySelect->value();

    // Check if the part name is empty
    if(partName.isEmpty()) {
        QMessageBox::critical(this, "Validation Error!", "Part's name is left blank!");
        qDebug() << "Part name is empty";
        return false;
    }

    // Check if the quantity is valid
    if(quantity <= 0) {
        QMessageBox::critical(this, "Validation Error!", "Quantity should be a positive integer!");
        qDebug() << "Invalid quantity";
        return false;
    }

    // Check if the part name contains only alphabetic characters and spaces
    for (QChar c : partName) {
        if (!c.isLetter() && !c.isSpace()) {
            QMessageBox::critical(this, "Validation Error!", "Part name should contain only alphabetic characters and spaces!");
            qDebug() << "Part name contains non-alphabetic characters";
            return false;
        }
    }

    // Prepare a query to select the name from the Storage table
    QSqlQuery query(database);
    query.prepare("SELECT name FROM Storage");
    query.exec();

    // Check if the part name already exists in the database
    while (query.next()) {
        QString existedName = query.value(0).toString();
        if (partName == existedName) {
            QMessageBox::critical(this,"Validation Error!", "Name already exist!");
            query.finish();
            query.clear();
            qDebug() << "Existed Error: " << query.lastError().text();
            return false;
        }
    }

    query.finish();
    query.clear();
    qDebug() << "No Error: " << query.lastError().text();

    return true;
}

void addToStorage::on_cancelBtn_clicked()
{
    close();
}

