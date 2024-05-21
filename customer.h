#ifndef CUSTOMER_H  // Preprocessor directive to prevent multiple inclusions of
                    // this header file
#define CUSTOMER_H  // Defines CUSTOMER_H symbol to indicate that this header
                    // file has been included

// Include necessary header files
#include "entitylist.h"  // Includes custom header file for the EntityList class
#include "removefromcustomer.h"  // Includes custom header file for the RemoveFromCustomer class

// Define the Customer class, which inherits from EntityList
class Customer : public EntityList {
  Q_OBJECT  // This macro must appear in the private section of a class
            // definition that declares its own signals and slots or that uses
            // other services provided by Qt's meta-object system.

      public
      : Customer(QWidget *parent =
                     nullptr);  // Constructor declaration, takes a QWidget
                                // pointer as an argument, default is nullptr
  void add() override;          // Overrides the add function from EntityList
  void remove() override;       // Overrides the remove function from EntityList
  void showInfo(const QModelIndex &index)
      override;  // Overrides the showInfo function from EntityList, takes a
                 // const reference to a QModelIndex as an argument

  void loadList() override;  // Overrides the loadList function from EntityList
  void idSort() override;    // Overrides the idSort function from EntityList
  void nameSort() override;  // Overrides the nameSort function from EntityList
  void showEvent(
      QShowEvent *event);  // Function to handle the show event, takes a pointer
                           // to a QShowEvent as an argument

  ~Customer();  // Destructor declaration

 private:
  RemoveFromCustomer
      *removeFromCustomer_ptr;  // Pointer to a RemoveFromCustomer object
};

#endif  // CUSTOMER_H  // End of preprocessor conditional directive