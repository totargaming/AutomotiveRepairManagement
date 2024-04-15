#include "maintenancetask.h"
#include "ui_entitylist.h"
MaintenanceTask::MaintenanceTask(QWidget* parent) : TaskList(parent) {
    ui->removeBtn->setText("To Delivery!");
    TaskList::loadList();
}
QString MaintenanceTask::taskType() {
    return "Maintenance";
}
void MaintenanceTask::remove() {
    // Get the selected index
    QModelIndex index = ui->tableView->currentIndex();
    if (!index.isValid()) {
        qDebug() << "No row selected!";
        return;
    }

    int row = index.row();
    QString modelName = ui->tableView->model()->data(ui->tableView->model()->index(row, 0)).toString();

    QSqlDatabase database = QSqlDatabase::database("DB");
    if (!database.isOpen()) {
        qDebug() << "Database is not open!";
        return;
    }

    QSqlQuery query(database);
    query.prepare("UPDATE Vehicle SET Finished = 1 WHERE Model = :modelName");
    query.bindValue(":modelName", modelName);
    if (!query.exec()) {
        qDebug() << "Failed to execute query" << query.lastError();
        return;
    }
    QMessageBox::information(this, "Success", "Task has been successfully moved to delivery state");

    qDebug() << "Model: " << modelName << " marked as finished.";
    TaskList::loadList();
}



MaintenanceTask::~MaintenanceTask() {
}
