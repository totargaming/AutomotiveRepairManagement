// Include the necessary header files.
#include "maintenancetask.h"
#include "ui_entitylist.h"

// Define the constructor for the MaintenanceTask class. It inherits from the TaskList class.
MaintenanceTask::MaintenanceTask(QWidget* parent) : TaskList(parent) {
    // Change the text of the remove button to "To Delivery!".
    ui->removeBtn->setText("To Delivery!");
    ui->label->setText("MAINTENANCE INFO");

    // Load the task list.
    TaskList::loadList();
}

// Define a function that returns the type of the task. In this case, it's "Maintenance".
QString MaintenanceTask::taskType() {
    return "Maintenance";
}
void MaintenanceTask::showEvent(QShowEvent *event) {
    QWidget::showEvent(event); // Call base class implementation
    ui->txtInfo->clear();

    loadList(); // Refresh the combo box
    qDebug() << "MaintenanceTask Widget shown";
}
// Define a function to remove a task.
void MaintenanceTask::remove() {
    // Get the currently selected index in the table view.
    QModelIndex index = ui->tableView->currentIndex();
    // If no row is selected, output a debug message and return.
    if (!index.isValid()) {
        qDebug() << "No row selected!";
        return;
    }

    // Get the row number of the selected index.
    int row = index.row();
    // Get the model name from the first column (0) of the selected row.
    QString modelName = ui->tableView->model()->data(ui->tableView->model()->index(row, 0)).toString();

    // Get the database connection.
    QSqlDatabase database = QSqlDatabase::database("DB");
    // If the database is not open, output a debug message and return.
    if (!database.isOpen()) {
        qDebug() << "Database is not open!";
        return;
    }

    // Prepare a query to update the Finished field of the Vehicle table for the selected model.
    QSqlQuery query(database);
    query.prepare("UPDATE Vehicle SET Finished = 1 WHERE Model = :modelName");
    query.bindValue(":modelName", modelName);
    // If the query fails to execute, output a debug message and return.
    if (!query.exec()) {
        qDebug() << "Failed to execute query" << query.lastError();
        return;
    }
    // Display a message box to inform the user that the task has been successfully moved to the delivery state.
    QMessageBox::information(this, "Success", "Task has been successfully moved to delivery state");

    // Output a debug message indicating that the model has been marked as finished.
    qDebug() << "Model: " << modelName << " marked as finished.";
    emit forwardedToDelivery();
    // Reload the task list.

    TaskList::loadList();
    ui->txtInfo->clear();
}

// Define the destructor for the MaintenanceTask class.
MaintenanceTask::~MaintenanceTask() {
}
