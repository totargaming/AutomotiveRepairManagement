#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "entitylist.h" // Include the header file for the EntityList class
#include "removefromcustomer.h" // Include the header file for the RemoveFromCustomer class

// Define the Customer class, which inherits from EntityList
class Customer : public EntityList
{
    Q_OBJECT // This macro is necessary for any object that uses signals or slots
public:
    // Constructor, takes a QWidget pointer as an argument with a default value of nullptr
    Customer(QWidget *parent = nullptr);

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
    // Destructor
    ~Customer();
private:
    // Pointer to a RemoveFromCustomer object
    RemoveFromCustomer* removeFromCustomer_ptr;
};

#endif // CUSTOMER_H