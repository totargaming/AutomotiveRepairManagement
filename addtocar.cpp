#include "addtocar.h"
#include "ui_addtocar.h"
#include <QDebug> // Include for qDebug
#include <QRegularExpression>
// Constructor for AddToCar class
AddToCar::AddToCar(QWidget *parent)
    : QDialog(parent), ui(new Ui::AddToCar)
{
    ui->setupUi(this);                       // Set up the user interface for this dialog
    database = QSqlDatabase::database("DB"); // Connect to the database named "DB"
    qDebug() << "AddToCar constructor called";
}

// Destructor for AddToCar class
AddToCar::~AddToCar()
{
    delete ui; // Delete the user interface when the dialog is destroyed
    qDebug() << "AddToCar destructor called";
}

// Function to validate user input
bool AddToCar::validateUserInput()
{
    // Get user input from UI
    QString model = ui->txtModel->text();
    QString brand = ui->txtBrand->text();
    QString customerName = ui->txtCustomerName->text();
    QString phone = ui->txtPhone->text();
    QString description = ui->txtDescription->toPlainText();

    // Validate user input
    if (model.isEmpty() || brand.isEmpty() || customerName.isEmpty())
    {
        QMessageBox::warning(this, "Input Error", "Model, Brand, and Customer Name should not be empty.");
        return false;
    }

    if (!phone.startsWith('0') || phone.length() != 10)
    {
        QMessageBox::warning(this, "Input Error", "Phone should start with 0 and have a length of 10.");
        return false;
    }

    for (QChar c : phone)
    {
        if (!c.isDigit())
        {
            QMessageBox::warning(this, "Input Error", "Phone should contain only numeric characters.");
            return false;
        }
    }

    if (description.isEmpty())
    {
        QMessageBox::warning(this, "Input Error", "Description should not be empty.");
        return false;
    }

    QRegularExpression rx("^[a-zA-Z0-9 ]*$");  // Regex for alphanumeric characters
    if (!rx.match(model).hasMatch() || !rx.match(brand).hasMatch())
    {
        QMessageBox::warning(this, "Input Error", "Model and Brand should contain only alphanumeric characters.");
        return false;
    }
    QRegularExpression rxName("^[a-zA-Z ]*$");  // Regex for alphabetic characters and spaces
    if (!rxName.match(customerName).hasMatch())
    {
        QMessageBox::warning(this, "Input Error", "Customer Name should contain only alphabetic characters and spaces.");
        return false;
    }
    qDebug() << "User input validated";
    return true;
}

// Function to reset all input fields
void AddToCar::reset()
{
    ui->txtModel->clear();
    ui->txtBrand->clear();
    ui->txtDescription->clear();
    ui->txtCustomerName->clear();
    ui->txtPhone->clear();
    qDebug() << "Input fields reset";
}

// Function to handle the click event of the add button
void AddToCar::on_addBtn_clicked()
{
    // Validate user input before proceeding
    if (!validateUserInput())
    {
        return;
    }

    // Get user input from UI
    QString model = ui->txtModel->text();
    QString brand = ui->txtBrand->text();
    QString description = ui->txtDescription->toPlainText().simplified();
    QString customerName = ui->txtCustomerName->text();
    QString phone = ui->txtPhone->text();

    QSqlQuery query(database);

    // Insert into Vehicle table
    query.prepare("INSERT INTO Vehicle (Model, Brand, Description) VALUES (:Model, :Brand, :Description)");
    query.bindValue(":Model", model);
    query.bindValue(":Brand", brand);
    query.bindValue(":Description", description);

    if (!query.exec())
    {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
        return;
    }

    int vehicleID = query.lastInsertId().toInt();

    // Insert into Customer table
    query.prepare("INSERT INTO Customer (Name, Phone, VehicleID) VALUES (:Name, :Phone, :VehicleID)");
    query.bindValue(":Name", customerName);
    query.bindValue(":Phone", phone);
    query.bindValue(":VehicleID", vehicleID);

    if (!query.exec())
    {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
        return;
    }

    int userID = query.lastInsertId().toInt();

    // Update the UserID in the Vehicle table
    query.prepare("UPDATE Vehicle SET UserID = :UserID WHERE VehicleID = :VehicleID");
    query.bindValue(":UserID", userID);
    query.bindValue(":VehicleID", vehicleID);

    if (!query.exec())
    {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
        return;
    }

    qDebug() << "Car added successfully";
    emit carAdded();

    QMessageBox::information(this, "Success", "Vehicle and Customer information added successfully.");
    reset();
    close();
}

void AddToCar::on_cancelBtn_clicked()
{
    close();
}

