#include "maintenancetask.h"
#include "ui_entitylist.h"

MaintenanceTask::MaintenanceTask(QWidget* parent) : TaskList(parent) {
    ui->removeBtn->setText("To Delivery!");
    loadList();
    addToTask_ptr = new AddToTask();
    connect(addToTask_ptr, &AddToTask::taskAdded, this, &MaintenanceTask::loadList);
}
QString MaintenanceTask::taskType() {
    return "Maintenance";
}
void MaintenanceTask::remove() {

}
void MaintenanceTask::add() {
    addToTask_ptr->setWindowTitle("Maintenance Task: Assign");
    addToTask_ptr->show();
}
MaintenanceTask::~MaintenanceTask() {
    delete addToTask_ptr;
}
