#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <QToolBar>
#include <QStatusBar>
#include <QLabel>
#include <QTextEdit>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setText("hello");
    ui->textEdit->setText("hello");
    ui->plainTextEdit->setPlainText("hello");
#if 0
    //这段代码是错的
    QAction* openAction = new QAction(QIcon(":/new/prefix1/images/open"),tr("&Open..."), this);
    openAction->setShortcuts(QKeySequence::Open);
    openAction->setStatusTip(tr("Open an existing file"));

    QAction* saveAction = new QAction(QIcon(":/new/prefix1/images/save"), tr("&Save..."), this);
    saveAction->setShortcuts(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save a new file"));

    QMenu *file = menuBar()->addMenu(tr("&File"));
    file->addAction(openAction);
    file->addAction(saveAction);

    QToolBar *toolBar = addToolBar(tr("&File"));
    toolBar->addAction(openAction);
    toolBar->addAction(saveAction);

    QTextEdit* textEdit = new QTextEdit(this);
    setCentralWidget(textEdit);

    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveFile);
#endif

    ///////////////////////////////
    //1. 创建菜单栏
    QMenuBar* menuBar = new QMenuBar();
    this->setMenuBar(menuBar);
    //2. 创建菜单
    QMenu* menu1 = new QMenu("File");
    menuBar->addMenu(menu1);

    //3. 给菜单添加菜单项
    QAction* action2 = new QAction("打开");
    QAction* action3 = new QAction("保存");
    menu1->addAction(action2);
    menu1->addAction(action3);
    connect(action2,&QAction::triggered,this,&MainWindow::openFile);
    connect(action3,&QAction::triggered,this,&MainWindow::saveFile);

    //创建工具栏
    QToolBar* toolBar = new QToolBar();
    this->addToolBar(toolBar);

    // 添加打开按钮
    QAction *actionOpen = new QAction("open");
    actionOpen->setIcon(QIcon(":/new/prefix1/images/open.png"));
    toolBar->addAction(actionOpen);
    connect(actionOpen, &QAction::triggered, this, &MainWindow::openFile);

    // 添加保存按钮
    QAction *actionSave = new QAction("save");
    actionSave->setIcon(QIcon(":/new/prefix1/images/save.png"));
    toolBar->addAction(actionSave);
    connect(actionSave, &QAction::triggered, this, &MainWindow::saveFile);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//打开文件
void MainWindow::openFile()
{
    QString path = QFileDialog::getOpenFileName(this,
               tr("Open File"), ".", tr("Text Files(*.txt)"));
    if(!path.isEmpty())
    {
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::warning(this, tr("Read File"),
                         tr("Cannot open file:\n%1").arg(path));
            return;
        }
        qDebug() << "path = " << path;
        QTextStream in(&file);
        //QString line= in.readAll();
        //qDebug() << "line = " << line;
        ui->textEdit->setText(in.readAll());
        //ui->textEdit->setText(line);

        file.close();
    }
    else
    {
        QMessageBox::warning(this, tr("Path"),
                             tr("You did not select any file."));
     }
}



//保存文件
void MainWindow::saveFile()
{
    QString path = QFileDialog::getSaveFileName(this,
               tr("Open File"), ".", tr("Text Files(*.txt)"));
    if(!path.isEmpty())
    {
        QFile file(path);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QMessageBox::warning(this, tr("Write File"),
                         tr("Cannot open file:\n%1").arg(path));
            return;
        }
        QTextStream out(&file);
        out << ui->textEdit->toPlainText();
        file.close();
    }
    else
    {
        QMessageBox::warning(this, tr("Path"),
                             tr("You did not select any file."));
    }
}

