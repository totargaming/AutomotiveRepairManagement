#include "deliverytask.h" // Include the header file for the DeliveryTask class
#include "ui_entitylist.h" // Include the header file for the UI of the entity list

// Constructor for the DeliveryTask class, which inherits from TaskList
DeliveryTask::DeliveryTask(QWidget *parent) : TaskList(parent)
{
    ui->addBtn->setVisible(false); // Hide the add button
    ui->removeBtn->setText("Car Delivered!"); // Change the text of the remove button
    ui->label->setText("DELIVERY TASK");

    TaskList::loadList(); // Load the list from the TaskList class
}

// Function to return the type of task
QString DeliveryTask::taskType()
{
    return "Delivery"; // Return "Delivery" as the type of task
}

// Function to remove a task
void DeliveryTask::remove()
{
    qDebug() << "TaskList: Entering remove"; // Debug message indicating the start of the remove function

    // Get the current index from the table view
    QModelIndex index = ui->tableView->currentIndex();
    if (!index.isValid()) // If the index is not valid
    {
        qDebug() << "TaskList: Invalid index"; // Debug message indicating an invalid index
        return; // Return from the function
    }

    // Get the row number from the index
    int row = index.row();
    // Get the model name from the table view
    QString modelName = ui->tableView->model()->data(ui->tableView->model()->index(row, 0)).toString();

    // Get the database with the name "DB"
    QSqlDatabase database = QSqlDatabase::database("DB");
    if (!database.isOpen()) // If the database is not open
    {
        qDebug() << "Delivery: Database is not open!"; // Debug message indicating that the database is not open
        return; // Return from the function
    }

    // Create a query for the database
    QSqlQuery query(database);
    // Prepare the query to select the UserID and StaffID from the Vehicle table where the Model is the model name
    query.prepare("SELECT UserID, StaffID FROM Vehicle WHERE Model = :modelName");
    query.bindValue(":modelName", modelName); // Bind the model name to the query
    if (!query.exec()) // If the query fails to execute
    {
        qDebug() << "Delivery: Failed to execute query(1)" << query.lastError(); // Debug message indicating a failed query execution
        return; // Return from the function
    }

    if (query.next()) // If there is a next record in the query result
    {
        // Get the UserID and StaffID from the query result
        QString userId = query.value("UserID").toString();
        QString staffId = query.value("StaffID").toString();

        // Delete customer info
        QSqlQuery deleteCustomerQuery(database); // Create a query for the database
        // Prepare the query to delete from the Customer table where the UserID is the user ID
        deleteCustomerQuery.prepare("DELETE FROM Customer WHERE UserID = :userId");
        deleteCustomerQuery.bindValue(":userId", userId); // Bind the user ID to the query
        if (!deleteCustomerQuery.exec()) // If the query fails to execute
        {
            qDebug() << "Delivery: Failed to execute delete customer query" << deleteCustomerQuery.lastError(); // Debug message indicating a failed query execution
            return; // Return from the function
        }

        // Update staff info
        QSqlQuery updateStaffQuery(database); // Create a query for the database
        // Prepare the query to update the Staff table to set Assigned to 0 and VehicleID to NULL where the StaffID is the staff ID
        updateStaffQuery.prepare("UPDATE Staff SET Assigned = 0, VehicleID = NULL WHERE StaffID = :staffId");
        updateStaffQuery.bindValue(":staffId", staffId); // Bind the staff ID to the query
        if (!updateStaffQuery.exec()) // If the query fails to execute
        {
            qDebug() << "Delivery: Failed to execute update staff query" << updateStaffQuery.lastError(); // Debug message indicating a failed query execution
            return; // Return from the function
        }

        // Delete vehicle info
        QSqlQuery deleteVehicleQuery(database); // Create a query for the database
        // Prepare the query to delete from the Vehicle table where the Model is the model name
        deleteVehicleQuery.prepare("DELETE FROM Vehicle WHERE Model = :modelName");
        deleteVehicleQuery.bindValue(":modelName", modelName); // Bind the model name to the query
        if (!deleteVehicleQuery.exec()) // If the query fails to execute
        {
            qDebug() << "Delivery: Failed to execute delete vehicle query" << deleteVehicleQuery.lastError(); // Debug message indicating a failed query execution
            return; // Return from the function
        }
        ui->txtInfo->clear();
    }
    // Show a message box indicating a successful delivery
    QMessageBox::information(this, "Success", "Car has been successfully Delivered");
    TaskList::loadList(); // Load the list from the TaskList class
    ui->txtInfo->clear(); // Clear the text info
    qDebug() << "Delivery: Exiting remove"; // Debug message indicating the end of the remove function
}
void DeliveryTask::showEvent(QShowEvent *event) {
    QWidget::showEvent(event); // Call base class implementation
    ui->txtInfo->clear();

    loadList(); // Refresh the combo box
    qDebug() << "DeliveryTask Widget shown";
}
// Destructor for the DeliveryTask class
DeliveryTask::~DeliveryTask()
{
}
