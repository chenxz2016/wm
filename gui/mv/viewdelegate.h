#ifndef VIEWDELEGATE_H
#define VIEWDELEGATE_H

#include <QStyledItemDelegate>

#define GROUP_ROOT_HEIGHT                   35
#define GROUP_ITEM_HEIGHT                   50

#define CONTACT_ROOT_HEIGHT                 40
#define CONTACT_ITEM_HEIGHT                 50

enum ViewItemRole
{
    GroupRole=1,
    ContactRole,
    GroupRootRole,
    GroupItemRole,
    ContactRootRole,
    ContactItemRole
};

enum VRole
{
    ViewRole = Qt::UserRole + 1,
    ViewDataRole
};

class ViewDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    ViewDelegate(QWidget *parent = 0);
    ~ViewDelegate();

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const Q_DECL_OVERRIDE;
    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const Q_DECL_OVERRIDE;
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const Q_DECL_OVERRIDE;
private:
    QWidget *m_parent;
};

#endif // VIEWDELEGATE_H
