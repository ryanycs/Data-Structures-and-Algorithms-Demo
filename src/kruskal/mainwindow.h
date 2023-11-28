#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
using std::vector;
using std::map;
using std::sort;

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
    int Find(int a);
    void Union(int a, int b);
    void kruskal(vector<vector<int>>& edge);

    vector<int> parent = vector<int>(26);
    vector<vector<int>> edges;
    vector<vector<int>> step;
    map<char, QPoint> coord;
    bool draw = false, draw_step = false;
    int step_num = 0;
    int radis = 20;

private slots:
    void on_okButton_clicked();

    void on_showButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
