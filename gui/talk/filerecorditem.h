#ifndef FILERECORDITEM_H
#define FILERECORDITEM_H

#include <QFileInfo>
#include <QWidget>

namespace Ui {
class FileRecordItem;
}

class FileRecordItem : public QWidget
{
    Q_OBJECT

public:
    explicit FileRecordItem(QWidget *parent = 0);
    FileRecordItem(const QString &path);
    ~FileRecordItem();

    enum FileType
    {
        FILE,
        TEXT,
        DOC,
        PPT,
        XSL,
        PDF,
        VIDEO,
        AUDIO,
        FOLDER,
        PICTURE
    };

    void append(const QString &file);

    void setFileInfo(const QFileInfo &info);


    FileType type()const;
    void setType(FileType type);

    QString date()const;
    void setDate(const QString &date);
    void setDate(const QDateTime &date);

    QString sender()const;
    void setSender(const QString &sender);

    bool isExist()const;
private:
    Ui::FileRecordItem *ui;
};

#endif // FILERECORDITEM_H
