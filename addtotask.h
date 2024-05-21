#ifndef ADDTOTASK_H  // Preprocessor directive to prevent multiple inclusions of
                     // this header file
#define ADDTOTASK_H  // Defines ADDTOTASK_H symbol to indicate that this header
                     // file has been included

// Include necessary header files
#include <QDate>  // Includes QDate class from Qt framework to handle date values
#include <QDialog>  // Includes QDialog class from Qt framework to create dialog windows
#include <QMessageBox>  // Includes QMessageBox class from Qt framework to create message boxes

#include "SQLheader.h"  // Includes custom header file for SQL related operations
#include "validation.h"  // Includes custom header file for validation related operations

// Forward declaration of the Ui::AddToTask class
namespace Ui {
class AddToTask;  // Forward declaration of AddToTask class inside Ui namespace
}

// AddToTask class declaration
class AddToTask
    : public QDialog,
      Validation  // Class declaration, inheriting from QDialog and Validation
{
  Q_OBJECT  // This macro must appear in the private section of a class
            // definition that declares its own signals and slots or that uses
            // other services provided by Qt's meta-object system.

      public : explicit AddToTask(
                   QWidget *parent =
                       nullptr);  // Constructor declaration, takes a QWidget
                                  // pointer as an argument, default is nullptr
  bool
  validateUserInput();  // Function to validate user input, returns a boolean
  void loadBox();       // Function to load the combo boxes, returns void
  void showEvent(
      QShowEvent *event);  // Function to handle the show event, takes a pointer
                           // to a QShowEvent as an argument, returns void
  ~AddToTask();            // Destructor declaration
  friend class TestAddToTask;  // Declares TestAddToTask as a friend class,
                               // allowing it to access private and protected
                               // members of AddToTask

 signals:
  void taskAdded();  // Signal declaration, emitted when a task is added

 private slots:
  void on_modelBox_currentTextChanged(
      const QString &text);  // Slot declaration, connected to the
                             // currentTextChanged signal of the model combo box

  void on_addBtn_clicked();  // Slot declaration, connected to the click event
                             // of the add button

  void on_cancelBtn_clicked();  // Slot declaration, connected to the click
                                // event of the cancel button

 private:
  Ui::AddToTask *ui;  // Pointer to the user interface, of type Ui::AddToTask
  QSqlDatabase database;  // Database object, of type QSqlDatabase
};

#endif  // ADDTOTASK_H  // End of preprocessor conditional directive