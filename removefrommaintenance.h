// Ensure the header file is included only once by the preprocessor
#ifndef REMOVEFROMMAINTENANCE_H
#define REMOVEFROMMAINTENANCE_H

// Include necessary Qt libraries
#include <QDialog> // Provides functionality to create dialog windows
#include "SQLheader.h" // Include the SQL header file (assumed to contain SQL related definitions)
#include "validation.h" // Include the validation header file (assumed to contain validation related definitions)
#include <QMessageBox> // Provides functionality to create message box
#include <QDate> // Provides functionality to work with dates

// Declare a namespace for the User Interface (UI)
namespace Ui {
    class RemoveFromMaintenance; // Forward declaration of the RemoveFromMaintenance class
}

// Define the RemoveFromMaintenance class, which inherits from QDialog and Validation
class RemoveFromMaintenance : public QDialog, Validation
{
    Q_OBJECT // Macro that enables Qt's meta-object system

public:
    // Declare constructor
    explicit RemoveFromMaintenance(QWidget *parent = nullptr);

    // Declare function to validate user input
    bool validateUserInput();

    // Declare function to load data into combo box
    void loadBox();

    // Declare function to handle show event
    void showEvent(QShowEvent *event);

    // Declare destructor
    ~RemoveFromMaintenance();

signals:
    // Declare signal that is emitted when maintenance is removed
    void maintenanceRemoved();

private slots:
    // Declare slot to handle click event of remove button
    void on_removeBtn_clicked();

    // Declare slot to handle change in selected item in combo box
    void on_removeList_currentTextChanged(const QString &text);

private:
    // Declare pointer to UI object
    Ui::RemoveFromMaintenance *ui;

    // Declare object for database connection
    QSqlDatabase database;
};

// End of the preprocessor conditional
#endif // REMOVEFROMMAINTENANCE_H