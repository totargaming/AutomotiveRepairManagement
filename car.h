#ifndef CAR_H
#define CAR_H
#include "entitylist.h"
#include "addtocar.h"
#include "removefromcar.h"
#include "QDate"
class Car : public EntityList
{
    Q_OBJECT
public:
     Car(QWidget *parent = nullptr);
    void add() override;
    void remove() override;
    void showInfo(const QModelIndex &index) override;

    void loadList() override;
    void idSort() override;
    void nameSort() override;
     ~Car();
private:
    AddToCar* addToCar_ptr;
    RemoveFromCar* removeFromCar_ptr;
};

#endif // CAR_H
