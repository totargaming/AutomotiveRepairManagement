#ifndef MAINTENANCETASK_H
#define MAINTENANCETASK_H
#include "tasklist.h"

class MaintenanceTask: public TaskList
{
public:
    MaintenanceTask(QWidget* parent = nullptr);
    void loadList() override {

    }
    QString taskType() override;
    void remove() override;
    void changeToDelivery(const QModelIndex &index);
    ~MaintenanceTask();


};

#endif // MAINTENANCETASK_H

