#ifndef ADDTOMAINTENANCE_H  // Preprocessor directive to prevent multiple
                            // inclusions of this header file
#define ADDTOMAINTENANCE_H  // Defines ADDTOMAINTENANCE_H symbol to indicate
                            // that this header file has been included

// Include necessary header files
#include <QDateEdit>  // Includes QDateEdit class from Qt framework to create date editor widgets
#include <QDialog>  // Includes QDialog class from Qt framework to create dialog windows
#include <QMessageBox>  // Includes QMessageBox class from Qt framework to create message boxes

#include "SQLheader.h"  // Includes custom header file for SQL related operations
#include "validation.h"  // Includes custom header file for validation related operations

// Declare the Ui namespace and the AddToMaintenance class
namespace Ui {
class AddToMaintenance;  // Forward declaration of AddToMaintenance class inside
                         // Ui namespace
}

// Declare the AddToMaintenance class, which inherits from QDialog and
// Validation
class AddToMaintenance
    : public QDialog,
      Validation  // Class declaration, inheriting from QDialog and Validation
{
  Q_OBJECT  // This macro must appear in the private section of a class
            // definition that declares its own signals and slots or that uses
            // other services provided by Qt's meta-object system.

      public :
      // Declare the constructor and destructor
      explicit AddToMaintenance(
          QWidget *parent =
              nullptr);  // Constructor declaration, takes a QWidget pointer as
                         // an argument, default is nullptr
  ~AddToMaintenance();   // Destructor declaration

  // Declare public methods
  bool
  validateUserInput();  // Function to validate user input, returns a boolean
  void loadBox();       // Function to load the combo box, returns void
  void showEvent(
      QShowEvent *event);  // Function to handle the show event, returns void
  friend class TestAddToMaintenance;  // Declares TestAddToMaintenance as a
                                      // friend class, allowing it to access
                                      // private and protected members of
                                      // AddToMaintenance

 signals:
  void assigned();  // Signal declaration, emitted when a vehicle is assigned

 private slots:
  void on_addBtn_clicked();  // Slot declaration, connected to the click event
                             // of the add button

  void on_cancelBtn_clicked();  // Slot declaration, connected to the click
                                // event of the cancel button

 private:
  Ui::AddToMaintenance
      *ui;  // Pointer to the user interface, of type Ui::AddToMaintenance
  QSqlDatabase database;  // Database object, of type QSqlDatabase
};

#endif  // ADDTOMAINTENANCE_H  // End of preprocessor conditional directive