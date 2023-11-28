#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include "RBT.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);

private slots:
    void on_InsertButton_clicked();

    void on_DrawButton_clicked();

private:
    Ui::MainWindow *ui;
    int width;
    int height;
    int radis;
    bool draw;
    RBT<int> tree;
    void drawTree(QPainter& paint, TreeNode<int>* node, int x, int y, int w);
};
#endif // MAINWINDOW_H
