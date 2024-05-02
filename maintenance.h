// This is the header guard. It prevents the header file from being included more than once in the same file.
#ifndef MAINTENANCE_H
#define MAINTENANCE_H

// Include the necessary libraries and header files.
#include <QWidget> // Provides all the functionality to create a widget in Qt.
#include "SQLheader.h" // This is a custom header file that likely contains SQL-related functions or definitions.
#include <QCalendarWidget> // Provides a monthly based calendar widget allowing the user to select a date.
#include "addtomaintenance.h" // This is a custom header file for the AddToMaintenance class.
#include "removefrommaintenance.h" // This is a custom header file for the RemoveFromMaintenance class.

// Declare the Ui namespace and forward declare the Maintenance class within it.
namespace Ui {
class Maintenance;
}

// Declare the Maintenance class, which inherits from QWidget.
class Maintenance : public QWidget
{
    // The Q_OBJECT macro must appear in the private section of a class definition that declares its own signals and slots or that uses other services provided by Qt's meta-object system.
    Q_OBJECT

public:
    // Declare the constructor for the Maintenance class. It takes a QWidget pointer as a parameter, with a default value of nullptr.
    explicit Maintenance(QWidget *parent = nullptr);
    
    // Declare a function to load all maintenance data.
    void loadAll();
    
    // Declare the destructor for the Maintenance class.
    ~Maintenance();

private slots:
    // Declare a slot that will be called when the selection in the calendar widget changes.
    void on_calendarWidget_selectionChanged();

    // Declare a slot that will be called when the add button is clicked.
    void on_addBtn_clicked();

    // Declare a slot that will be called when the remove button is clicked.
    void on_removeBtn_clicked();

    // Declare a slot that will be called when a cell in the start date table is clicked.
    void on_startDateTable_clicked(const QModelIndex &index);

    // Declare a slot that will be called when a cell in the deadline table is clicked.
    void on_deadlineTable_clicked(const QModelIndex &index);

private:
    // Declare a pointer to the user interface for the Maintenance class.
    Ui::Maintenance *ui;
    
    // Declare a pointer to a QCalendarWidget.
    QCalendarWidget *calendar;
    
    // Declare pointers to instances of AddToMaintenance and RemoveFromMaintenance.
    AddToMaintenance* addToMaintenance_ptr;
    RemoveFromMaintenance* removeFromMaintenance_ptr;
};

// This is the end of the header guard.
#endif // MAINTENANCE_H