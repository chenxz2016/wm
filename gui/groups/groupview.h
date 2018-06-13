#ifndef GROUPVIEW_H
#define GROUPVIEW_H

#include <QTreeWidget>

class GroupView : public QTreeWidget
{
    Q_OBJECT
public:
    GroupView(QWidget *parent = 0);

    void update();
private slots:
    void groupsViewItemExpland(QTreeWidgetItem*);
    void groupsViewItemClicked(QModelIndex);
private:
    QModelIndex m_index;
};

#endif // GROUPVIEW_H
