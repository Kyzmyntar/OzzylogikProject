#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeView>

class TreeModel;
class IconDelegate;
class SqlLiteStorage;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QTreeView *treeView;
    TreeModel *model;
    IconDelegate *delegate;
    SqlLiteStorage *storage;
};
#endif
