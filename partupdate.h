#ifndef PARTUPDATE_H  // Preprocessor directive to prevent multiple inclusions
                      // of this header file
#define PARTUPDATE_H  // Defines PARTUPDATE_H symbol to indicate that this
                      // header file has been included

// Include necessary header files
#include <QDialog>      // Includes QDialog class from Qt Widgets module
#include <QMessageBox>  // Includes QMessageBox class for displaying messages

#include "SQLheader.h"   // Includes custom SQLheader file
#include "validation.h"  // Includes custom header file for the Validation class

namespace Ui {
class PartUpdate;  // Forward declaration of the PartUpdate class in the Ui
                   // namespace
}

// Define the PartUpdate class, which inherits from QDialog and Validation
class PartUpdate : public QDialog, public Validation {
  Q_OBJECT  // This macro must appear in the private section of a class
            // definition that declares its own signals and slots or that uses
            // other services provided by Qt's meta-object system.

      public : explicit PartUpdate(
                   QWidget *parent =
                       nullptr);  // Constructor declaration, takes a QWidget
                                  // pointer as an argument, default is nullptr
  ~PartUpdate();                  // Destructor declaration

  // Public member functions
  bool validateUserInput();
  void loadBox();
  void showEvent(QShowEvent *event);

 signals:
  void partUpdated();  // Signal that is emitted when a part is updated

 private slots:
  // Slots for various button clicked signals and text changes
  void on_deleteBtn_clicked();
  void on_updateBtn_clicked();
  void on_removeList_currentTextChanged(const QString &text);
  void on_cancelBtn_clicked();

 private:
  Ui::PartUpdate *ui;     // Pointer to the UI for the PartUpdate class
  QSqlDatabase database;  // QSqlDatabase object for the database connection
};

#endif  // PARTUPDATE_H  // End of preprocessor conditional directive