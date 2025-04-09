#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QMouseEvent>

#if 0
‌QMouseEvent对象的globalPos()方法:
1.‌QMouseEvent对象的globalPos()方法用于获取鼠标事件发生时的全局坐标位置。‌
2.在Qt框架中，QMouseEvent对象包含了与鼠标事件相关的信息，其中globalPos()方法返回的是鼠标事件发生时的全局坐标位置。
这对于处理鼠标移动、点击等事件非常有用，尤其是当你需要在全局坐标系中定位鼠标的位置时。
全局坐标是以屏幕左上角为原点的坐标系，而局部坐标则是以控件左上角为原点的坐标系。
通过globalPos()方法，你可以获取到鼠标在屏幕上的绝对位置，这对于实现一些需要精确控制鼠标位置的功能非常有帮助。
3.例如，在处理鼠标移动事件时，你可以使用globalPos()方法来获取鼠标的当前位置，
并根据这个位置来更新界面上的某些元素的位置或者执行其他与位置相关的操作。
这种方法在需要跟踪鼠标移动轨迹、实现屏幕范围内的拖拽操作等场景中特别有用。
4.此外，通过结合使用localPos()方法（如果需要的话），你可以轻松地在局部坐标系和全局坐标系之间进行转换，
从而实现更加灵活的用户界面交互设计‌
#endif

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //去窗口表框
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());

    //把窗口背景设置为透明
    setAttribute(Qt::WA_TranslucentBackground);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawPixmap(0, 0, QPixmap("../Image/sunny.png"));
}

void Widget::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::RightButton)
    {
        //如果是右键
        close();
    }
    else if(e->button() == Qt::LeftButton)
    {
        //求坐标差值
        //当前点击坐标-窗口左上角坐标
        p = e->globalPos() - this->frameGeometry().topLeft();
    }
}

void Widget::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons() & Qt::LeftButton)
    {
       move(e->globalPos() - p);
    }
}
