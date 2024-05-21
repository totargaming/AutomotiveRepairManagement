#ifndef TASKLIST_H  // Preprocessor directive to prevent multiple inclusions of
                    // this header file
#define TASKLIST_H  // Defines TASKLIST_H symbol to indicate that this header
                    // file has been included

// Include necessary header files
#include <QDate>  // Includes QDate class from Qt Core module for date handling

#include "addtotask.h"   // Includes custom header file for the AddToTask class
#include "entitylist.h"  // Includes custom header file for the EntityList class

// Define the TaskList class, which inherits from EntityList
class TaskList : public EntityList {
  Q_OBJECT  // This macro must appear in the private section of a class
            // definition that declares its own signals and slots or that uses
            // other services provided by Qt's meta-object system.

      public : explicit TaskList(
                   QWidget *parent =
                       nullptr);  // Constructor declaration, takes a QWidget
                                  // pointer as an argument, default is nullptr
  void showInfo(const QModelIndex &index)
      override;                // Overridden function to show task info
  void add() override;         // Overridden function to add task
  void loadList() override;    // Overridden function to load task list
  void idSort() override;      // Overridden function to sort tasks by id
  void nameSort() override;    // Overridden function to sort tasks by name
  virtual QString taskType();  // Function to get the task type
  void idSort(
      QString taskType);  // Function to sort tasks by id based on task type
  void nameSort(
      QString taskType);  // Function to sort tasks by name based on task type
  void loadList(QString taskType);  // Function to load tasks based on task type
  virtual ~TaskList();              // Destructor declaration

 protected:
  AddToTask *addToTask_ptr;  // Pointer to the AddToTask object
};

#endif  // TASKLIST_H  // End of preprocessor conditional directive