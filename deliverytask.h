#ifndef DELIVERYTASK_H
#define DELIVERYTASK_H
#include "tasklist.h"
class DeliveryTask: public TaskList
{
public:
    DeliveryTask(QWidget* parent = nullptr);
    QString taskType() override;
    void remove() override;
    void add() override;

};

#endif // DELIVERYTASK_H
