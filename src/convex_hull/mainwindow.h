#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QString>
#include <bits/stdc++.h>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct Point {
    int x, y;
};

int cross(Point& a, Point& b, Point& c);
int distance2(Point& a, Point& b);
bool cmp(Point& a, Point& b);
vector<Point> graham_scan(vector<Point> p);

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);
    vector<Point> points;
    vector<Point> convex_hull;
    int unit = 10;
    bool draw = false;

private slots:
    void on_okButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
