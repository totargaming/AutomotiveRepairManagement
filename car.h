#ifndef CAR_H  // Preprocessor directive to prevent multiple inclusions of this
               // header file
#define CAR_H  // Defines CAR_H symbol to indicate that this header file has
               // been included

// Include necessary header files
#include "QDate"  // Includes QDate class from Qt framework to handle date values
#include "addtocar.h"    // Includes custom header file for the AddToCar class
#include "entitylist.h"  // Includes custom header file for the EntityList class
#include "removefromcar.h"  // Includes custom header file for the RemoveFromCar class

// Define the Car class, which inherits from EntityList
class Car : public EntityList {
  Q_OBJECT  // This macro must appear in the private section of a class
            // definition that declares its own signals and slots or that uses
            // other services provided by Qt's meta-object system.

      public : Car(QWidget *parent =
                       nullptr);  // Constructor declaration, takes a QWidget
                                  // pointer as an argument, default is nullptr
  void add() override;            // Overrides the add function from EntityList
  void remove() override;  // Overrides the remove function from EntityList
  void showInfo(const QModelIndex &index)
      override;  // Overrides the showInfo function from EntityList, takes a
                 // const reference to a QModelIndex as an argument

  void loadList() override;  // Overrides the loadList function from EntityList
  void idSort() override;    // Overrides the idSort function from EntityList
  void nameSort() override;  // Overrides the nameSort function from EntityList
  void showEvent(
      QShowEvent *event);  // Function to handle the show event, takes a pointer
                           // to a QShowEvent as an argument

  ~Car();  // Destructor declaration

 private:
  AddToCar *addToCar_ptr;            // Pointer to an AddToCar object
  RemoveFromCar *removeFromCar_ptr;  // Pointer to a RemoveFromCar object
};

#endif  // CAR_H  // End of preprocessor conditional directive