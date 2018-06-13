#include "messagerecord.h"
#include "photorecord.h"
#include "ui_messagerecord.h"


class MessageRecordPrivate
{
public:
    MessageRecordPrivate(MessageRecord *parent)
        :p(parent)
    {}

    void init()
    {
        p->ui->setupUi(p);

        record = new PhotoRecord;
        p->ui->msg_photo->setWidget(record);
    }

    MessageRecord *p;

    PhotoRecord *record;
};

MessageRecord::MessageRecord(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MessageRecord),
    p_d(new MessageRecordPrivate(this))
{
    p_d->init();
}

MessageRecord::~MessageRecord()
{
    delete ui;
    delete p_d;
}

void MessageRecord::on_all_toggled(bool checked)
{
    Q_UNUSED(checked)
    ui->stacked->setCurrentWidget(ui->msg_all);
}

void MessageRecord::on_photo_toggled(bool checked)
{
    Q_UNUSED(checked)
    ui->stacked->setCurrentWidget(ui->msg_photo);
}

void MessageRecord::on_file_toggled(bool checked)
{
    Q_UNUSED(checked)
    ui->stacked->setCurrentWidget(ui->msg_file);
}
