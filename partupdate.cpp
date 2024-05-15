// Include the necessary header files.
#include "partupdate.h"
#include "ui_partupdate.h"

// Define the constructor for the PartUpdate class.
PartUpdate::PartUpdate(QWidget *parent)
    : QDialog(parent) // Initialize the base class.
    , ui(new Ui::PartUpdate) // Initialize the UI.
{
    ui->setupUi(this); // Set up the UI.
    database = QSqlDatabase::database("DB"); // Get the database.
    if (!database.isValid() || !database.isOpen()) { // Check if the database is valid and open.
        qDebug() << "RemoveFromCar: Failed to initialize database";
        return;
    }
    qDebug() << "RemoveFromCar: Successfully initialized database";
    loadBox(); // Load the combo box.
}

// Define the destructor for the PartUpdate class.
PartUpdate::~PartUpdate()
{
    delete ui; // Delete the UI.
}

// Define a function to validate the user input.
bool PartUpdate::validateUserInput() {
    QString selectedItem = ui->removeList->currentText(); // Get the current text of the combo box.
    if (selectedItem.isEmpty()) { // Check if the text is empty.
        QMessageBox::warning(this, "Warning", "Please select an item"); // Show a warning message.
        return false;
    }
    return true; // Return true if the text is not empty.
}

// Define a function to load the combo box.
void PartUpdate::loadBox() {
    ui->removeList->clear(); // Clear the combo box.
    QSqlQuery query(database); // Create a query.
    query.prepare("SELECT name FROM Storage"); // Prepare the query.
    query.exec(); // Execute the query.
    while(query.next()){ // Loop through the results.
        ui->removeList->addItem(query.value(0).toString()); // Add each result to the combo box.
        qDebug() << "PartUpdate: Filling removeList" << query.value(0).toString();
    }
    qDebug() << "PartUpdate: Last query" << query.lastQuery();
    qDebug() << "PartUpdate: Last error" << query.lastError().text();
}

// Define a function to handle the show event.
void PartUpdate::showEvent(QShowEvent *event)
{
    QDialog::showEvent(event); // Call the base class implementation.
    loadBox(); // Refresh the combo box.
    qDebug() << "Dialog shown";

}

// Define a slot for the click event of the delete button.
void PartUpdate::on_deleteBtn_clicked()
{
    if (!validateUserInput()) { // Validate the user input.
        return;
    }
    QString selectedItem = ui->removeList->currentText(); // Get the current text of the combo box.

    QSqlQuery query(database); // Create a query.
    query.prepare("DELETE FROM Storage WHERE name = :name"); // Prepare the query.
    query.bindValue(":name", selectedItem); // Bind the value.
    if (query.exec()) { // Execute the query.
        qDebug() << "PartUpdate: Item deleted successfully";
        QMessageBox::information(this, "Success", "Item deleted successfully"); // Show a success message.
    } else {
        qDebug() << "PartUpdate: Failed to delete item" << query.lastError().text();
        QMessageBox::critical(this, "Error", "Failed to delete item: " + query.lastError().text()); // Show an error message.
    }
    loadBox(); // Refresh the combo box.
    emit partUpdated(); // Emit the partUpdated signal.
}

// Define a slot for the click event of the update button.
void PartUpdate::on_updateBtn_clicked()
{
    if (!validateUserInput()) { // Validate the user input.
        return;
    }
    QString selectedItem = ui->removeList->currentText(); // Get the current text of the combo box.

    int newQuantity = ui->quantitySelect->value(); // Get the value of the quantity select.
    QSqlQuery query(database); // Create a query.
    query.prepare("UPDATE Storage SET quantity = :quantity WHERE name = :name"); // Prepare the query.
    query.bindValue(":name", selectedItem); // Bind the value.
    query.bindValue(":quantity", newQuantity); // Bind the value.
    if (query.exec()) { // Execute the query.
        qDebug() << "PartUpdate: Item updated successfully";
        QMessageBox::information(this, "Success", "Item updated successfully"); // Show a success message.
    } else {
        qDebug() << "PartUpdate: Failed to update item" << query.lastError().text();
        QMessageBox::critical(this, "Error", "Failed to update item: " + query.lastError().text()); // Show an error message.
    }
    loadBox(); // Refresh the combo box.
    emit partUpdated(); // Emit the partUpdated signal.
}

// Define a slot for the currentTextChanged event of the combo box.
void PartUpdate::on_removeList_currentTextChanged(const QString &text)
{
    QSqlQuery query(database); // Create a query.
    query.prepare("SELECT quantity FROM Storage WHERE name = :name"); // Prepare the query.
    query.bindValue(":name", text); // Bind the value.
    query.exec(); // Execute the query.
    if (query.next()) { // Check if there are any results.
        int quantity = query.value(0).toInt(); // Get the quantity.
        ui->quantityReport->setText("Last updated quantity: " + QString::number(quantity)); // Set the text of the quantity report.
    }
}
