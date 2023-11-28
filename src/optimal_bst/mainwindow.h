#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include "BST.h"
using namespace std;

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
    void drawTree(QPainter& paint, TreeNode<QChar>* node, int x, int y, int w);
    void obst(QString nodes, QString freqs);
    TreeNode<QChar>* find_ans(int l, int r, QString& s, vector<vector<int>>& memo);

private slots:
    void on_okButton_clicked();

private:
    Ui::MainWindow *ui;

    BST<QChar> tree;
    int R, H, W;
    bool draw;
};
#endif // MAINWINDOW_H
