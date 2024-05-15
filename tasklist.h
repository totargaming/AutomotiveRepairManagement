#ifndef TASKLIST_H
#define TASKLIST_H

// Include the necessary header files
#include "entitylist.h"
#include "addtotask.h"
#include <QDate>

// Declare the TaskList class, which inherits from EntityList
class TaskList : public EntityList
{
    Q_OBJECT // Use the Q_OBJECT macro to enable signals and slots

public:
    // Constructor for TaskList, with a default parent of nullptr
    TaskList(QWidget *parent = nullptr);

    // Override the showInfo function from EntityList to show information about a task
    void showInfo(const QModelIndex &index) override;

    // Override the add function from EntityList to add a task
    void add() override;

    // Override the loadList function from EntityList to load the task list
    void loadList() override;

    // Override the idSort function from EntityList to sort the task list by ID
    void idSort() override;

    // Override the nameSort function from EntityList to sort the task list by name
    void nameSort() override;

    // Declare a function to get the task type
    virtual QString taskType();

    // Declare a function to sort the task list by ID based on the task type
    void idSort(QString taskType);

    // Declare a function to sort the task list by name based on the task type
    void nameSort(QString taskType);

    // Declare a function to load the task list based on the task type
    void loadList(QString taskType);

    // Destructor for TaskList
    virtual ~TaskList();

protected:
    // Declare a pointer to an AddToTask object
    AddToTask *addToTask_ptr;
};

#endif // TASKLIST_H
