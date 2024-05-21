#ifndef STORAGE_H  // Preprocessor directive to prevent multiple inclusions of
                   // this header file
#define STORAGE_H  // Defines STORAGE_H symbol to indicate that this header file
                   // has been included

// Include necessary header files
#include <QDialog>  // Includes QDialog class from Qt Widgets module for dialog window

#include "SQLheader.h"  // Includes custom SQLheader file
#include "addtostorage.h"  // Includes custom header file for the AddToStorage class
#include "partupdate.h"  // Includes custom header file for the PartUpdate class

namespace Ui {
class Storage;  // Forward declaration of the Storage class in the Ui namespace
}

// Define the Storage class, which inherits from QDialog
class Storage : public QDialog {
  Q_OBJECT  // This macro must appear in the private section of a class
            // definition that declares its own signals and slots or that uses
            // other services provided by Qt's meta-object system.

      public : explicit Storage(
                   QWidget* parent =
                       nullptr);  // Constructor declaration, takes a QWidget
                                  // pointer as an argument, default is nullptr
  void loadAll();                 // Function to load all storage items
  void showEvent(QShowEvent* event);  // Overridden function from QWidget to
                                      // handle show events
  ~Storage();                         // Destructor declaration

 private slots:
  // Slots for various button clicked signals
  void on_searchBtn_clicked();
  void on_refreshBtn_clicked();
  void on_addBtn_clicked();
  void on_updateBtn_clicked();

 private:
  Ui::Storage* ui;                 // Pointer to the UI for the Storage class
  QSqlQueryModel* model;           // Pointer to the QSqlQueryModel object
  addToStorage* addToStorage_ptr;  // Pointer to the AddToStorage object
  PartUpdate* partUpdate_ptr;      // Pointer to the PartUpdate object
};

#endif  // STORAGE_H  // End of preprocessor conditional directive