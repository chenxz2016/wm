#ifndef WMWIDGETDATA_H
#define WMWIDGETDATA_H

class QWidget;

class WMWidgetData
{
public:
    WMWidgetData(QWidget *parent = 0);

    virtual void drawWindowEdge();


    QWidget *m_parent;
};

#endif // WMWIDGETDATA_H
