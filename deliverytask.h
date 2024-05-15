#ifndef DELIVERYTASK_H
#define DELIVERYTASK_H
#include "tasklist.h" // Include the header file for the TaskList class

// Define the DeliveryTask class, which inherits from TaskList
class DeliveryTask : public TaskList
{
    Q_OBJECT
public:
    // Constructor, takes a QWidget pointer as an argument with a default value of nullptr
    DeliveryTask(QWidget *parent = nullptr);

    // Override the taskType function from TaskList
    QString taskType() override;

    // Override the remove function from TaskList
    void remove() override;

    // Override the add function from TaskList, but provide no implementation
    void add() override {}
    void showEvent(QShowEvent *event); // Method to handle the show event

    // Destructor
    ~DeliveryTask();
};

#endif // DELIVERYTASK_H
