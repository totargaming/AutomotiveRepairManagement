#ifndef MAINTENANCE_H  // Preprocessor directive to prevent multiple inclusions
                       // of this header file
#define MAINTENANCE_H  // Defines MAINTENANCE_H symbol to indicate that this
                       // header file has been included

// Include necessary header files
#include <QCalendarWidget>  // Includes QCalendarWidget class from Qt Widgets module
#include <QWidget>          // Includes QWidget class from Qt Widgets module

#include "SQLheader.h"  // Includes custom SQLheader file
#include "addtomaintenance.h"  // Includes custom header file for the AddToMaintenance class
#include "removefrommaintenance.h"  // Includes custom header file for the RemoveFromMaintenance class

namespace Ui {
class Maintenance;  // Forward declaration of the Maintenance class in the Ui
                    // namespace
}

// Define the Maintenance class, which inherits from QWidget
class Maintenance : public QWidget {
  Q_OBJECT  // This macro must appear in the private section of a class
            // definition that declares its own signals and slots or that uses
            // other services provided by Qt's meta-object system.

      public : explicit Maintenance(
                   QWidget *parent =
                       nullptr);  // Constructor declaration, takes a QWidget
                                  // pointer as an argument, default is nullptr
  void loadAll();                 // Function to load all maintenance data
  void showEvent(QShowEvent *event);  // Function to handle the show event
  void markCalendar();                // Function to mark the calendar
  ~Maintenance();                     // Destructor declaration

 private slots:
  // Slots for various button clicked and selection changed signals
  void on_calendarWidget_selectionChanged();
  void on_addBtn_clicked();
  void on_removeBtn_clicked();
  void on_startDateTable_clicked(const QModelIndex &index);
  void on_deadlineTable_clicked(const QModelIndex &index);
  void on_homeBtn_clicked();

 private:
  Ui::Maintenance *ui;        // Pointer to the UI for the Maintenance class
  QCalendarWidget *calendar;  // Pointer to a QCalendarWidget
  AddToMaintenance
      *addToMaintenance_ptr;  // Pointer to an instance of AddToMaintenance
  RemoveFromMaintenance *removeFromMaintenance_ptr;  // Pointer to an instance
                                                     // of RemoveFromMaintenance
};

#endif  // MAINTENANCE_H  // End of preprocessor conditional directive