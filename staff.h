#ifndef STAFF_H  // Preprocessor directive to prevent multiple inclusions of
                 // this header file
#define STAFF_H  // Defines STAFF_H symbol to indicate that this header file has
                 // been included

// Include necessary header files
#include "addtostaff.h"  // Includes custom header file for the AddToStaff class
#include "entitylist.h"  // Includes custom header file for the EntityList class
#include "removefromstaff.h"  // Includes custom header file for the RemoveFromStaff class

// Define the Staff class, which inherits from EntityList
class Staff : public EntityList {
  Q_OBJECT  // This macro must appear in the private section of a class
            // definition that declares its own signals and slots or that uses
            // other services provided by Qt's meta-object system.

      public : explicit Staff(
                   QWidget *parent =
                       nullptr);  // Constructor declaration, takes a QWidget
                                  // pointer as an argument, default is nullptr
  void add() override;            // Overridden function to add staff
  void remove() override;         // Overridden function to remove staff
  void showInfo(const QModelIndex &index)
      override;              // Overridden function to show staff info
  void loadList() override;  // Overridden function to load staff list
  void idSort() override;    // Overridden function to sort staff by id
  void nameSort() override;  // Overridden function to sort staff by name
  void showEvent(QShowEvent *event);  // Overridden function from QWidget to
                                      // handle show events
  ~Staff();                           // Destructor declaration

 private:
  AddToStaff *addToStaff_ptr;  // Pointer to the AddToStaff object
  RemoveFromStaff
      *removeFromStaff_ptr;  // Pointer to the RemoveFromStaff object
};

#endif  // STAFF_H  // End of preprocessor conditional directive