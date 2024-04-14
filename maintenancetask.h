#ifndef MAINTENANCETASK_H
#define MAINTENANCETASK_H
#include "tasklist.h"
class MaintenanceTask: public TaskList
{
public:
    MaintenanceTask(QWidget* parent = nullptr);
    QString taskType() override;
    void remove() override;
    void add() override;
};

#endif // MAINTENANCETASK_H

