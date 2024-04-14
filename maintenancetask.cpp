#include "maintenancetask.h"
#include "ui_entitylist.h"

MaintenanceTask::MaintenanceTask(QWidget* parent) : TaskList(parent) {
    ui->removeBtn->setText("To Delivery!");
    loadList();
}
QString MaintenanceTask::taskType() {
    return "Maintenance";
}
void MaintenanceTask::remove() {

}
void MaintenanceTask::add() {

}
