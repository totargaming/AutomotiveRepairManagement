#ifndef STORAGE_H
#define STORAGE_H

// Include necessary header files
#include <QDialog>
#include "SQLheader.h"
#include "addtostorage.h"
#include "partupdate.h"

// Declare the Ui namespace and forward declare the Storage class
namespace Ui {
class Storage;
}

// Declare the Storage class, which inherits from QDialog
class Storage : public QDialog
{
    Q_OBJECT // Use the Q_OBJECT macro to enable signals and slots

public:
    // Declare the constructor, with a default parameter for parent
    explicit Storage(QWidget *parent = nullptr);

    // Declare the loadAll function
    void loadAll();
    void showEvent(QShowEvent *event); // Method to handle the show event

    // Declare the destructor
    ~Storage();

private slots:
    // Declare the slot for the search button click event
    void on_searchBtn_clicked();

    // Declare the slot for the refresh button click event
    void on_refreshBtn_clicked();

    // Declare the slot for the add button click event
    void on_addBtn_clicked();

    // Declare the slot for the update button click event
    void on_updateBtn_clicked();

private:
    // Declare a pointer to the UI for the Storage
    Ui::Storage *ui;

    // Declare a pointer to a QSqlQueryModel
    QSqlQueryModel* model;

    // Declare a pointer to an addToStorage object
    addToStorage* addToStorage_ptr;

    // Declare a pointer to a PartUpdate object
    PartUpdate* partUpdate_ptr;
};

#endif // STORAGE_H
