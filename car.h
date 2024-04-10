#ifndef CAR_H
#define CAR_H
#include "entitylist.h"
#include "addtocar.h"
#include "removefromcar.h"
class Car : public EntityList
{
public:
     Car(QWidget *parent = nullptr);
    void add();
    void remove();
    void showInfo(const QModelIndex &index);
    void loadList();
    void idSort();
    void nameSort();
     ~Car();
private:
     AddToCar* addToCar_ptr;
    RemoveFromCar* removeFromCar_ptr;
};

#endif // CAR_H
