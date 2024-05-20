// Include the necessary header files.
#include "removefromcar.h"
#include "ui_removefromcar.h"

// Define the constructor for the RemoveFromCar class.
RemoveFromCar::RemoveFromCar(QWidget *parent)
    : QDialog(parent) // Initialize the QDialog part of this object.
    , ui(new Ui::RemoveFromCar) // Initialize the UI part of this object.
{
    ui->setupUi(this); // Set up the UI.
    database = QSqlDatabase::database("DB"); // Get the database.
    if (!database.isValid() || !database.isOpen()) { // Check if the database is valid and open.
        qDebug() << "RemoveFromCar: Failed to initialize database"; // Log an error message.
        return; // Return early.
    }
    qDebug() << "RemoveFromCar: Successfully initialized database"; // Log a success message.
    loadBox(); // Load the combo box.
}

// Define the destructor for the RemoveFromCar class.
RemoveFromCar::~RemoveFromCar()
{
    delete ui; // Delete the UI.
}

// Define the loadBox function, which loads the combo box with data from the database.
void RemoveFromCar::loadBox() {
    ui->removeList->clear(); // Clear the combo box.
    QSqlQuery query(database); // Create a new query.
    query.prepare("SELECT Model FROM Vehicle"); // Prepare the query.
    if (!query.exec()) { // Execute the query.
        qDebug() << "RemoveFromCar: Failed to execute query" << query.lastError().text(); // Log an error message.
        return; // Return early.
    }
    while(query.next()){ // While there are more rows in the result set.
        ui->removeList->addItem(query.value(0).toString()); // Add the current row to the combo box.
        qDebug() << "RemoveFromCar: Filling removeList" << query.value(0).toString(); // Log a message.
    }
    qDebug() << "RemoveFromCar: Last query" << query.lastQuery(); // Log the last query.
    qDebug() << "RemoveFromCar: Last error" << query.lastError().text(); // Log the last error.
}

// Define the showEvent function, which is called when the dialog is shown.
void RemoveFromCar::showEvent(QShowEvent *event)
{
    QDialog::showEvent(event); // Call the base class implementation.
    loadBox(); // Refresh the combo box.
    qDebug() << "Dialog shown";

}

// Define the validateUserInput function, which validates the user's input.
bool RemoveFromCar::validateUserInput() {
    QString selectedItem = ui->removeList->currentText(); // Get the selected item.
    if (selectedItem.isEmpty()) { // If the selected item is empty.
        QMessageBox::warning(this, "Warning", "Please select an item"); // Show a warning message.
        return false; // Return false.
    }
    return true; // Return true.
}

// Define the slot for when the current text in the removeList combo box changes.
void RemoveFromCar::on_removeList_currentTextChanged(const QString &text)
{
    QSqlQuery query(database); // Create a new query.
    query.prepare("SELECT VehicleID, UserID FROM Vehicle WHERE Model = :Model"); // Prepare the query.
    query.bindValue(":Model", text); // Bind the value.
    if (!query.exec()) { // Execute the query.
        qDebug() << "RemoveFromCar: Failed to execute query" << query.lastError().text(); // Log an error message.
        return; // Return early.
    }

    QString vehicleId, userId; // Declare the variables.
    if (query.next()) { // If there is a next row.
        vehicleId = query.value(0).toString(); // Get the vehicle ID.
        userId = query.value(1).toString(); // Get the user ID.
    }

    ui->idReport->setText("ID: " + vehicleId); // Set the text.

    query.prepare("SELECT Name FROM Customer WHERE UserID = :userId"); // Prepare the query.
    query.bindValue(":userId", userId); // Bind the value.
    if (!query.exec()) { // Execute the query.
        qDebug() << "RemoveFromCar: Failed to execute query" << query.lastError().text(); // Log an error message.
        return; // Return early.
    }

    QString customerName; // Declare the variable.
    if (query.next()) { // If there is a next row.
        customerName = query.value(0).toString(); // Get the customer name.
    }

    ui->customerNameReport->setText("Customer Name: " + customerName); // Set the text.
}

// Define the slot for when the removeBtn button is clicked.
void RemoveFromCar::on_removeBtn_clicked()
{
    if (!validateUserInput()) { // If the user input is not valid.
        return; // Return early.
    }
    QString selectedItem = ui->removeList->currentText(); // Get the selected item.

    QSqlQuery query(database); // Create a new query.
    query.prepare("SELECT UserID FROM Vehicle WHERE Model = :Model"); // Prepare the query.
    query.bindValue(":Model", selectedItem); // Bind the value.
    if (!query.exec()) { // Execute the query.
        qDebug() << "RemoveFromCar: Failed to execute query" << query.lastError().text(); // Log an error message.
        return; // Return early.
    }

    QString userId; // Declare the variable.
    if (query.next()) { // If there is a next row.
        userId = query.value(0).toString(); // Get the user ID.
    }

    query.prepare("DELETE FROM Vehicle WHERE Model = :Model"); // Prepare the query.
    query.bindValue(":Model", selectedItem); // Bind the value.
    if (query.exec()) { // Execute the query.
        qDebug() << "RemoveFromCar: Vehicle deleted successfully"; // Log a success message.
    } else {
        qDebug() << "RemoveFromCar: Failed to delete vehicle" << query.lastError().text(); // Log an error message.
        return; // Return early.
    }

    query.prepare("DELETE FROM Customer WHERE UserID = :userId"); // Prepare the query.
    query.bindValue(":userId", userId); // Bind the value.
    if (query.exec()) { // Execute the query.
        qDebug() << "RemoveFromCar: Customer deleted successfully"; // Log a success message.
        QMessageBox::information(this, "Success", "Item deleted successfully"); // Show an information message.
    } else {
        qDebug() << "RemoveFromCar: Failed to delete customer" << query.lastError().text(); // Log an error message.
        QMessageBox::critical(this, "Error", "Failed to delete item: " + query.lastError().text()); // Show a critical message.
    }

    loadBox(); // Refresh the combo box.
    emit carRemoved(); // Emit the carRemoved signal.
    close();
}

void RemoveFromCar::on_cancelBtn_clicked()
{
    close();
}

