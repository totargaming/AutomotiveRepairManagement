#ifndef ENTITYLIST_H
#define ENTITYLIST_H

#include <QWidget>

namespace Ui {
class EntityList;
}

class EntityList : public QWidget
{
    Q_OBJECT

public:
    explicit EntityList(QWidget *parent = nullptr);
    ~EntityList();

private:
    Ui::EntityList *ui;
};

#endif // ENTITYLIST_H
