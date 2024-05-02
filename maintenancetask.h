// This is the header guard. It prevents the header file from being included more than once in the same file.
#ifndef MAINTENANCETASK_H
#define MAINTENANCETASK_H

// Include the necessary header file.
#include "tasklist.h" // This is a custom header file for the TaskList class.

// Declare the MaintenanceTask class, which inherits from the TaskList class.
class MaintenanceTask: public TaskList
{

public:
    // Declare the constructor for the MaintenanceTask class. It takes a QWidget pointer as a parameter, with a default value of nullptr.
    MaintenanceTask(QWidget* parent = nullptr);
    
    // Declare a function to load the task list. This function is overridden from the TaskList class.
    void loadList() override {

    }
    
    // Declare a function to get the type of the task. This function is overridden from the TaskList class.
    QString taskType() override;
    
    // Declare a function to remove a task. This function is overridden from the TaskList class.
    void remove() override;
    
    // Declare a function to change the status of a task to delivery. It takes a QModelIndex as a parameter.
    void changeToDelivery(const QModelIndex &index);
    
    // Declare the destructor for the MaintenanceTask class.
    ~MaintenanceTask();

};

// This is the end of the header guard.
#endif // MAINTENANCETASK_H