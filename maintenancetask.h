#ifndef MAINTENANCETASK_H
#define MAINTENANCETASK_H
#include "tasklist.h"
#include "addtotask.h"
class MaintenanceTask: public TaskList
{
public:
    MaintenanceTask(QWidget* parent = nullptr);
    void loadList() override {

    }
    QString taskType() override;
    void remove() override;
    void add() override;
    ~MaintenanceTask();
private:
    AddToTask* addToTask_ptr;

};

#endif // MAINTENANCETASK_H

