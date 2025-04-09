/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QLabel *label_hello;
    QLabel *label_hello_002;
    QLabel *label_html_001;
    QLabel *label_html_002;
    QLabel *label_jpg;
    QLabel *label_gif;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(800, 600);
        label_hello = new QLabel(Widget);
        label_hello->setObjectName(QString::fromUtf8("label_hello"));
        label_hello->setGeometry(QRect(46, 20, 111, 20));
        label_hello_002 = new QLabel(Widget);
        label_hello_002->setObjectName(QString::fromUtf8("label_hello_002"));
        label_hello_002->setGeometry(QRect(50, 70, 67, 17));
        label_html_001 = new QLabel(Widget);
        label_html_001->setObjectName(QString::fromUtf8("label_html_001"));
        label_html_001->setGeometry(QRect(50, 110, 351, 51));
        label_html_002 = new QLabel(Widget);
        label_html_002->setObjectName(QString::fromUtf8("label_html_002"));
        label_html_002->setGeometry(QRect(50, 190, 391, 61));
        label_jpg = new QLabel(Widget);
        label_jpg->setObjectName(QString::fromUtf8("label_jpg"));
        label_jpg->setGeometry(QRect(50, 280, 351, 161));
        label_gif = new QLabel(Widget);
        label_gif->setObjectName(QString::fromUtf8("label_gif"));
        label_gif->setGeometry(QRect(60, 490, 311, 81));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", nullptr));
        label_hello->setText(QApplication::translate("Widget", "TextLabel", nullptr));
        label_hello_002->setText(QApplication::translate("Widget", "TextLabel", nullptr));
        label_html_001->setText(QApplication::translate("Widget", "TextLabel", nullptr));
        label_html_002->setText(QApplication::translate("Widget", "TextLabel", nullptr));
        label_jpg->setText(QApplication::translate("Widget", "TextLabel", nullptr));
        label_gif->setText(QApplication::translate("Widget", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
