#include "deliverytask.h"
#include "ui_entitylist.h"

DeliveryTask::DeliveryTask(QWidget* parent) : TaskList(parent) {
    ui->addBtn->setVisible(false);
    ui->removeBtn->setText("Car Delivered!");
    loadList();
}
QString DeliveryTask::taskType() {
    return "Delivery";
}
void DeliveryTask::remove() {

}
