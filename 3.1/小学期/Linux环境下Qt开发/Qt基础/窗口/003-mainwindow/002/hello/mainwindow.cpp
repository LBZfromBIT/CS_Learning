#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <QToolBar>
#include <QStatusBar>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //1. 创建菜单栏
    QMenuBar* menuBar = new QMenuBar();
    this->setMenuBar(menuBar);
    //2. 创建菜单
    QMenu* menu1 = new QMenu("文件");
    QMenu* menu2 = new QMenu("编辑");
    QMenu* menu3 = new QMenu("视图");
    menuBar->addMenu(menu1);
    menuBar->addMenu(menu2);
    menuBar->addMenu(menu3);
    QMenu* menu4 = new QMenu("调试(&D)");
    QMenu* menu5 = new QMenu("工具(&T)");
    QMenu* menu6 = new QMenu("帮助(&H)");
    menuBar->addMenu(menu4);
    menuBar->addMenu(menu5);
    menuBar->addMenu(menu6);

    //给菜单添加菜单项
    QAction* action1 = new QAction("新建");
    QAction* action2 = new QAction("打开");
    QAction* action3 = new QAction("保存");
    menu1->addAction(action1);
    menu1->addAction(action2);
    menu1->addAction(action3);
    menu1->addSeparator();
    QAction* action4 = new QAction("退出");
    menu1->addAction(action4);

    connect(action1,&QAction::triggered,this,&MainWindow::handle);

    //创建工具栏
    QToolBar* toolBar = new QToolBar();
    this->addToolBar(toolBar);
    // 添加编辑
    QAction* actiontool1 = new QAction("编辑");
    //actiontool1->setIcon(QIcon(":/edit.png"));
    toolBar->addAction(actiontool1);

    // 添加分隔符
    toolBar->addSeparator();

    // 添加打开按钮
      QAction *actionOpen = new QAction("open");
    actionOpen->setIcon(QIcon(":/new/prefix1/images/open.png"));
    toolBar->addAction(actionOpen);
    connect(actionOpen, &QAction::triggered, this, &MainWindow::openFile);

    // 添加保存按钮
    QAction *actionSave = new QAction("save");
    //actionSave->setIcon(QIcon(":/save.png"));
    toolBar->addAction(actionSave);
    connect(actionSave, &QAction::triggered, this, &MainWindow::saveFile);

    //创建状态栏
    QStatusBar* statusBar = this->statusBar();
    this->setStatusBar(statusBar);
    QLabel* label1 = new QLabel("aaaaaaaaaaa");
    QLabel* label2 = new QLabel("bbbbbbbbbbbbb");
    statusBar->addWidget(label1);//在状态栏左侧添加控件
    statusBar->addPermanentWidget(label2);//在状态栏右侧添加控件
}

void MainWindow::handle()
{
    qDebug() << "1111111111111111";
}

MainWindow::~MainWindow()
{
    delete ui;
}

