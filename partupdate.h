// Include guard to prevent multiple inclusions of the same header file.
#ifndef PARTUPDATE_H
#define PARTUPDATE_H

// Include necessary Qt classes.
#include <QDialog>
#include "SQLheader.h" // Include the SQL header file.
#include "validation.h" // Include the validation header file.
#include <QMessageBox> // Include the QMessageBox class for displaying messages.

// Declare the Ui namespace and forward declare the PartUpdate class.
namespace Ui {
class PartUpdate;
}

// Declare the PartUpdate class, which inherits from QDialog and Validation.
class PartUpdate : public QDialog, public Validation
{
    Q_OBJECT // Use the Q_OBJECT macro to enable signals and slots.

public:
    // Declare the constructor and destructor.
    explicit PartUpdate(QWidget *parent = nullptr);
    ~PartUpdate();

    // Declare public member functions.
    bool validateUserInput();
    void loadBox();
    void showEvent(QShowEvent *event);

signals:
    // Declare a signal that is emitted when a part is updated.
    void partUpdated();

private slots:
    // Declare slots for handling button clicks and text changes.
    void on_deleteBtn_clicked();
    void on_updateBtn_clicked();
    void on_removeList_currentTextChanged(const QString &text);

    void on_cancelBtn_clicked();

private:
    // Declare private member variables.
    Ui::PartUpdate *ui; // Pointer to the UI.
    QSqlDatabase database; // The database.

};

// End of include guard.
#endif // PARTUPDATE_H
