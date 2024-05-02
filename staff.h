#ifndef STAFF_H
#define STAFF_H

// Include the necessary header files
#include "entitylist.h"
#include "addtostaff.h"
#include "removefromstaff.h"

// Declare the Staff class, which inherits from EntityList
class Staff : public EntityList
{
    Q_OBJECT // Use the Q_OBJECT macro to enable signals and slots

public:
    // Declare the constructor, with a default parameter for parent
    Staff(QWidget *parent = nullptr);

    // Declare the overridden add function
    void add() override;

    // Declare the overridden remove function
    void remove() override;

    // Declare the overridden showInfo function, which takes a QModelIndex as a parameter
    void showInfo(const QModelIndex &index) override;

    // Declare the overridden loadList function
    void loadList() override;

    // Declare the overridden idSort function
    void idSort() override;

    // Declare the overridden nameSort function
    void nameSort() override;

    // Declare the destructor
    ~Staff();

private:
    // Declare a pointer to an AddToStaff object
    AddToStaff* addToStaff_ptr;

    // Declare a pointer to a RemoveFromStaff object
    RemoveFromStaff* removeFromStaff_ptr;
};

#endif // STAFF_H