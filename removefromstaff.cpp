#include "removefromstaff.h"
#include "ui_removefromstaff.h"

// Constructor
RemoveFromStaff::RemoveFromStaff(QWidget *parent)
    : QDialog(parent) // Initialize QDialog with parent widget
    , ui(new Ui::RemoveFromStaff) // Initialize UI
{
    ui->setupUi(this); // Setup UI for this dialog
    database = QSqlDatabase::database("DB"); // Get the database instance
    if (!database.isValid() || !database.isOpen()) { // Check if database is valid and open
        qDebug() << "RemoveFromStaff: Failed to initialize database";
        return;
    }
    qDebug() << "RemoveFromStaff: Successfully initialized database";
    loadBox(); // Load items into the combo box
}

// Destructor
RemoveFromStaff::~RemoveFromStaff()
{
    delete ui; // Delete the UI
}

// Function to validate user input
bool RemoveFromStaff::validateUserInput() {
    QString selectedItem = ui->removeList->currentText(); // Get the selected item
    if (selectedItem.isEmpty()) { // Check if an item is selected
        QMessageBox::warning(this, "Warning", "Please select an item"); // Show warning if no item is selected
        return false;
    }
    return true;
}

// Function to load items into the combo box
void RemoveFromStaff::loadBox() {
    ui->removeList->clear(); // Clear the combo box
    QSqlQuery query(database); // Create a query
    query.prepare("SELECT Name FROM Staff"); // Prepare the query
    if (!query.exec()) { // Execute the query
        qDebug() << "RemoveFromStaff: Failed to execute query" << query.lastError().text();
        return;
    }
    while(query.next()){ // Loop through the result set
        ui->removeList->addItem(query.value(0).toString()); // Add each item to the combo box
        qDebug() << "RemoveFromStaff: Filling removeList" << query.value(0).toString();
    }
    qDebug() << "RemoveFromStaff: Last query" << query.lastQuery();
    qDebug() << "RemoveFromStaff: Last error" << query.lastError().text();
}

// Function to handle show event
void RemoveFromStaff::showEvent(QShowEvent *event) {
    QDialog::showEvent(event); // Call base class implementation
    loadBox(); // Refresh the combo box
    qDebug() << "Dialog shown";

}

// Slot to handle change in selected item in combo box
void RemoveFromStaff::on_removeList_currentTextChanged(const QString &text)
{
    QSqlQuery query(database); // Create a query
    query.prepare("SELECT StaffID, Phone, Wage, Assigned FROM Staff WHERE Name = :Name"); // Prepare the query
    query.bindValue(":Name", text); // Bind the value
    if (!query.exec()) { // Execute the query
        qDebug() << "RemoveFromStaff: Failed to execute query" << query.lastError().text();
        return;
    }

    QString staffId, phone, wage,assigned;

    if (query.next()) { // If there is a result
        staffId = query.value(0).toString();
        phone = query.value(1).toString();
        wage = query.value(2).toString();
        assigned = query.value(3).toInt() == 1 ? "Yes" : "No";
    }

    // Set the text of the labels
    ui->idReport->setText("ID: " + staffId);
    ui->phoneReport->setText("Phone: " + phone);
    ui->wageReport->setText("Wage: " + wage);
    ui->assignedReport->setText("Working: " + assigned);
}

// Slot to handle click event of remove button
void RemoveFromStaff::on_removeBtn_clicked()
{
    if (!validateUserInput()) { // Validate user input
        return;
    }
    QString selectedItem = ui->removeList->currentText(); // Get the selected item

    QSqlQuery query(database); // Create a query
    query.prepare("SELECT StaffID FROM Staff WHERE Name = :Name"); // Prepare the query
    query.bindValue(":Name", selectedItem); // Bind the value
    if (!query.exec()) { // Execute the query
        qDebug() << "RemoveFromStaff: Failed to execute query" << query.lastError().text();
        return;
    }

    QString staffId;
    if (query.next()) { // If there is a result
        staffId = query.value(0).toString();
    }

    // Update the Vehicle table
    query.prepare("UPDATE Vehicle SET StaffID = NULL, Assigned = 0 WHERE StaffID = :StaffID");
    query.bindValue(":StaffID", staffId);
    if (!query.exec()) {
        qDebug() << "RemoveFromStaff: Failed to update Vehicle table" << query.lastError().text();
        return;
    }

    query.prepare("DELETE FROM Staff WHERE Name = :Name"); // Prepare the delete query
    query.bindValue(":Name", selectedItem); // Bind the value
    if (query.exec()) { // Execute the query
        qDebug() << "RemoveFromStaff: Staff member deleted successfully";
    } else {
        qDebug() << "RemoveFromStaff: Failed to delete staff member" << query.lastError().text();
        return;
    }

    loadBox(); // Refresh the combo box
    emit staffRemoved(); // Emit the signal
    close();
}
