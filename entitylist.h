#ifndef ENTITYLIST_H  // Preprocessor directive to prevent multiple inclusions
                      // of this header file
#define ENTITYLIST_H  // Defines ENTITYLIST_H symbol to indicate that this
                      // header file has been included

// Include necessary header files
#include <SQLheader.h>  // Includes custom SQLheader file

#include <QTableWidget>  // Includes QTableWidget class from Qt Widgets module
#include <QWidget>       // Includes QWidget class from Qt Widgets module

namespace Ui {
class EntityList;  // Forward declaration of the EntityList class in the Ui
                   // namespace
}

// Define the EntityList class, which inherits from QWidget
class EntityList : public QWidget {
  Q_OBJECT  // This macro must appear in the private section of a class
            // definition that declares its own signals and slots or that uses
            // other services provided by Qt's meta-object system.

      public : explicit EntityList(
                   QWidget *parent =
                       nullptr);  // Constructor declaration, takes a QWidget
                                  // pointer as an argument, default is nullptr

  // Pure virtual functions to be implemented by derived classes
  virtual void add() = 0;
  virtual void remove() = 0;
  virtual void showInfo(const QModelIndex &index) = 0;
  virtual void loadList() = 0;
  virtual void idSort() = 0;
  virtual void nameSort() = 0;

  virtual ~EntityList();  // Destructor declaration

 private slots:
  // Slots for button clicked signals
  void on_addBtn_clicked();
  void on_removeBtn_clicked();
  void on_idSortBtn_clicked();
  void on_nameSortBtn_clicked();

  // Slot for the table view clicked signal
  void on_tableView_clicked(const QModelIndex &index);

 protected:
  Ui::EntityList *ui;     // Pointer to the UI for the EntityList
  QSqlQueryModel *model;  // Pointer to the SQL query model
};

#endif  // ENTITYLIST_H  // End of preprocessor conditional directive