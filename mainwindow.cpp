#include "mainwindow.h"
#include "Tree/treemodel.h"
#include "icondelegate.h"
#include "DataStorage/sqllitestorage.h"
#include <QCoreApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    treeView(new QTreeView(this)),
    model(nullptr),
    delegate(new IconDelegate(this)),
    storage(nullptr)
{
    storage = new SqlLiteStorage(QCoreApplication::applicationDirPath() + "/system.db");

    model = new TreeModel(storage);
    treeView->setModel(model);
    treeView->setFrameStyle(QFrame::Box | QFrame::Plain);
    treeView->setAlternatingRowColors(true);
    treeView->setStyleSheet("QTreeView { gridline-color: lightgray; }");
    treeView->setHeaderHidden(true);
    treeView->setItemDelegate(delegate);

    setCentralWidget(treeView);
}

MainWindow::~MainWindow()
{
    delete model;
    delete storage;
}
