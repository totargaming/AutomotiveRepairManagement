#ifndef CAR_H
#define CAR_H
#include "entitylist.h" // Include the header file for the EntityList class
#include "addtocar.h" // Include the header file for the AddToCar class
#include "removefromcar.h" // Include the header file for the RemoveFromCar class
#include "QDate" // Include the QDate class for handling dates

// Define the Car class, which inherits from EntityList
class Car : public EntityList
{
    Q_OBJECT // This macro is necessary for any object that uses signals or slots
public:
    // Constructor, takes a QWidget pointer as an argument with a default value of nullptr
    Car(QWidget *parent = nullptr);
    // Override the add function from EntityList
    void add() override;
    // Override the remove function from EntityList
    void remove() override;
    // Override the showInfo function from EntityList
    void showInfo(const QModelIndex &index) override;

    // Override the loadList function from EntityList
    void loadList() override;
    // Override the idSort function from EntityList
    void idSort() override;
    // Override the nameSort function from EntityList
    void nameSort() override;
    void showEvent(QShowEvent *event); // Method to handle the show event

    // Destructor
    ~Car();
private:
    // Pointer to an AddToCar object
    AddToCar* addToCar_ptr;
    // Pointer to a RemoveFromCar object
    RemoveFromCar* removeFromCar_ptr;
};

#endif // CAR_H
