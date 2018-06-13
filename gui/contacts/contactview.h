#ifndef CONTACTVIEW_H
#define CONTACTVIEW_H

#include <QTreeWidget>

class ContactView : public QTreeWidget
{
    Q_OBJECT
public:
    ContactView(QWidget*parent= 0);
    ~ContactView();

    void update();
private slots:
    void contactViewItemExpland(QTreeWidgetItem*);
    void contactViewItemClicked(QModelIndex);
private:
    QModelIndex m_index;
};

#endif // CONTACTVIEW_H
