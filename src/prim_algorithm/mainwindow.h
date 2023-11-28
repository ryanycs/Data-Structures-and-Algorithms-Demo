#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QtMath>
#include <queue>
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
    void prim(QString& edges);

private slots:
    void on_okButton_clicked();

    void on_stepButton_clicked();

private:
    Ui::MainWindow *ui;

    map<char, QPoint> coord;
    vector<vector<pair<int, int>>> adj;
    vector<pair<int, int>> res;
    bool draw = false, showstep = false;
    int R = 20, step = 0;
    int mx, my;
};
#endif // MAINWINDOW_H
