#include "widget.h"
#include "ui_widget.h"
#include "dialog.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_next_clicked()
{
    Dialog* dialog = new Dialog(this);
    dialog->show();
    //dialog->exec();

}
