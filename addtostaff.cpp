#include "addtostaff.h"
#include "ui_addtostaff.h"

// Constructor
AddToStaff::AddToStaff(QWidget *parent)
    : QDialog(parent) // Initialize QDialog with parent widget
    , ui(new Ui::AddToStaff) // Initialize UI
{
    ui->setupUi(this); // Set up the user interface for this dialog
    database = QSqlDatabase::database("DB"); // Get the database instance named "DB"
    qDebug() << "Database initialized successfully";
}

// Destructor
AddToStaff::~AddToStaff()
{
    delete ui; // Delete the UI
}

// Function to validate user input
bool AddToStaff::validateUserInput() {
    qDebug() << "Validating user input";

    // Get the name, phone, and wage text from the UI
    QString name = ui->txtName->text();
    QString phone = ui->txtPhone->text();
    QString wageText = ui->txtWage->text();

    // Check if any of the fields are empty
    if (name.isEmpty() || phone.isEmpty() || wageText.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Name, Phone, and Wage Name should not be empty.");
        qDebug() << "Name, Phone, or Wage is empty";
        return false;
    }

    // Check if the phone number starts with 0 and has a length of 10
    if (!phone.startsWith('0') || phone.length() != 10) {
        QMessageBox::warning(this, "Input Error", "Phone should start with 0 and have a length of 10.");
        qDebug() << "Phone number is not valid";
        return false;
    }

    // Check if the phone number contains only numeric characters
    for (QChar c : phone) {
        if (!c.isDigit()) {
            QMessageBox::warning(this, "Input Error", "Phone should contain only numeric characters.");
            qDebug() << "Phone number contains non-numeric characters";
            return false;
        }
    }

    qDebug() << "User input validated successfully";
    return true;
}

// Function to reset the input fields
void AddToStaff::reset() {
    ui->txtName->clear(); // Clear the name field
    ui->txtPhone->clear(); // Clear the phone field
    ui->txtWage->clear(); // Clear the wage field
    qDebug() << "Input fields reset";
}

// Function to handle the add button click event
void AddToStaff::on_addBtn_clicked()
{
    qDebug() << "Add button clicked";

    // Validate the user input
    if (!validateUserInput()) {
        return;
    }

    // Get the name, phone, and wage from the UI
    QString name = ui->txtName->text();
    QString phone = ui->txtPhone->text();
    int wage = ui->txtWage->text().toInt();

    QSqlQuery query(database); // Create a query
    // Prepare the query
    query.prepare("INSERT INTO Staff (Name, Phone, Wage) VALUES (:Name, :Phone, :Wage)");
    // Bind the values to the query
    query.bindValue(":Name", name);
    query.bindValue(":Phone", phone);
    query.bindValue(":Wage", wage);

    // Execute the query
    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
        qDebug() << "Failed to insert staff into database";
        return;
    }

    emit staffAdded(); // Emit the staffAdded signal
    QMessageBox::information(this, "Success", "Staff information added successfully.");
    qDebug() << "Staff information added successfully";

    reset(); // Reset the input fields
}