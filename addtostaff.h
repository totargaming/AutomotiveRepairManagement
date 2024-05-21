#ifndef ADDTOSTAFF_H  // Preprocessor directive to prevent multiple inclusions
                      // of this header file
#define ADDTOSTAFF_H  // Defines ADDTOSTAFF_H symbol to indicate that this
                      // header file has been included

// Include necessary header files
#include <QDialog>  // Includes QDialog class from Qt framework to create dialog windows
#include <QMessageBox>  // Includes QMessageBox class from Qt framework to create message boxes

#include "SQLheader.h"  // Includes custom header file for SQL related operations
#include "validation.h"  // Includes custom header file for validation related operations

// Declare the Ui namespace and the AddToStaff class
namespace Ui {
class AddToStaff;  // Forward declaration of AddToStaff class inside Ui
                   // namespace
}

// Declare the AddToStaff class, which inherits from QDialog and Validation
class AddToStaff : public QDialog,
                   public Validation  // Class declaration, inheriting from
                                      // QDialog and Validation
{
  Q_OBJECT  // This macro must appear in the private section of a class
            // definition that declares its own signals and slots or that uses
            // other services provided by Qt's meta-object system.

      public :
      // Declare the constructor and destructor
      explicit AddToStaff(
          QWidget *parent =
              nullptr);  // Constructor declaration, takes a QWidget pointer as
                         // an argument, default is nullptr
  ~AddToStaff();         // Destructor declaration

  // Declare public methods
  bool validateUserInput()
      override;  // Function to validate user input, returns a boolean,
                 // overrides the method from Validation
  void reset();  // Function to reset the input fields, returns void
  friend class TestAddToStaff;  // Declares TestAddToStaff as a friend class,
                                // allowing it to access private and protected
                                // members of AddToStaff

 signals:
  void
  staffAdded();  // Signal declaration, emitted when a staff member is added

 private slots:
  void on_addBtn_clicked();  // Slot declaration, connected to the click event
                             // of the add button

  void on_cancelBtn_clicked();  // Slot declaration, connected to the click
                                // event of the cancel button

 private:
  Ui::AddToStaff *ui;  // Pointer to the user interface, of type Ui::AddToStaff
  QSqlDatabase database;  // Database object, of type QSqlDatabase
};

#endif  // ADDTOSTAFF_H  // End of preprocessor conditional directive