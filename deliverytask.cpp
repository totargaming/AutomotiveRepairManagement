#include "deliverytask.h"
#include "ui_entitylist.h"

DeliveryTask::DeliveryTask(QWidget *parent) : TaskList(parent)
{
    ui->addBtn->setVisible(false);
    ui->removeBtn->setText("Car Delivered!");
    TaskList::loadList();
}
QString DeliveryTask::taskType()
{
    return "Delivery";
}
void DeliveryTask::remove()
{
    qDebug() << "TaskList: Entering remove";

    QModelIndex index = ui->tableView->currentIndex();
    if (!index.isValid())
    {
        qDebug() << "TaskList: Invalid index";
        return;
    }

    int row = index.row();
    QString modelName = ui->tableView->model()->data(ui->tableView->model()->index(row, 0)).toString();

    QSqlDatabase database = QSqlDatabase::database("DB");
    if (!database.isOpen())
    {
        qDebug() << "Delivery: Database is not open!";
        return;
    }

    QSqlQuery query(database);
    query.prepare("SELECT UserID, StaffID FROM Vehicle WHERE Model = :modelName");
    query.bindValue(":modelName", modelName);
    if (!query.exec())
    {
        qDebug() << "Delivery: Failed to execute query(1)" << query.lastError();
        return;
    }

    if (query.next())
    {
        QString userId = query.value("UserID").toString();
        QString staffId = query.value("StaffID").toString();

        // Delete customer info
        QSqlQuery deleteCustomerQuery(database);
        deleteCustomerQuery.prepare("DELETE FROM Customer WHERE UserID = :userId");
        deleteCustomerQuery.bindValue(":userId", userId);
        if (!deleteCustomerQuery.exec())
        {
            qDebug() << "Delivery: Failed to execute delete customer query" << deleteCustomerQuery.lastError();
            return;
        }

        // Update staff info
        QSqlQuery updateStaffQuery(database);
        updateStaffQuery.prepare("UPDATE Staff SET Assigned = 0, VehicleID = NULL WHERE StaffID = :staffId");
        updateStaffQuery.bindValue(":staffId", staffId);
        if (!updateStaffQuery.exec())
        {
            qDebug() << "Delivery: Failed to execute update staff query" << updateStaffQuery.lastError();
            return;
        }

        // Delete vehicle info
        QSqlQuery deleteVehicleQuery(database);
        deleteVehicleQuery.prepare("DELETE FROM Vehicle WHERE Model = :modelName");
        deleteVehicleQuery.bindValue(":modelName", modelName);
        if (!deleteVehicleQuery.exec())
        {
            qDebug() << "Delivery: Failed to execute delete vehicle query" << deleteVehicleQuery.lastError();
            return;
        }
    }
    QMessageBox::information(this, "Success", "Car has been successfully Delivered");
    TaskList::loadList();
    ui->txtInfo->clear();
    qDebug() << "Delivery: Exiting remove";
}
DeliveryTask::~DeliveryTask()
{
}