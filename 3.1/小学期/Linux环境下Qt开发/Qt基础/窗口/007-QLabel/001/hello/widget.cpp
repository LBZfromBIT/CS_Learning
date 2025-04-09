#include "widget.h"
#include "ui_widget.h"
#include <QDesktopServices>
#include <QUrl>
#include <QMovie>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //1、可以显示普通文本字符串
    ui->label_hello->setText("hello world");
    QString str("hello");
    ui->label_hello_002->setText(str);
    //2、可以显示HTML格式的字符串
    //其中setOpenExternalLinks()函数是用来设置用户点击链接之后是否自动打开链接，
    //如果参数指定为true则会自动打开，如果设置为false，想要打开链接只能通过捕捉linkActivated()信号，
    //在自定义的槽函数中使用QDesktopServices::openUrl()打开链接，该函数参数默认值为false
    ui->label_html_001->setText("<h1><a href=\"https://www.baidu.com\">百度一下</a></h1>");
    ui->label_html_001->setOpenExternalLinks(true);
    //3、可以显示HTML格式的字符串
    //其中setOpenExternalLinks()函数是用来设置用户点击链接之后是否自动打开链接，
    //如果参数指定为true则会自动打开，如果设置为false，想要打开链接只能通过捕捉linkActivated()信号，
    //在自定义的槽函数中使用QDesktopServices::openUrl()打开链接，该函数参数默认值为false
    ui->label_html_002->setText("<h1><a href=\"https://www.baidu.com\">百度一下</a></h1>");
    ui->label_html_002->setOpenExternalLinks(false);
    connect(ui->label_html_002, &QLabel::linkActivated, this, &Widget::slotOpenUrl);
    //4、显示图片
    QPixmap pixmap;
    pixmap.load(":/new/prefix1/images/butterfly.jpg");
    ui->label_jpg->setPixmap(pixmap);
    //5、显示动画
    QMovie *movie = new QMovie(":/new/prefix1/images/movie.gif");
    ui->label_gif->setMovie(movie);
    movie->start();
}

Widget::~Widget()
{
    delete ui;
}

//槽函数
void Widget::slotOpenUrl(const QString &link)
{
    qDebug() << "into it";
    QDesktopServices::openUrl(QUrl(link));
}

