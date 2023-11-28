#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>

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

private:
    Ui::MainWindow *ui;
public:
    bool draw;
    int width;
    int x, y;
    int n;
    void draw_Sierpinski_triangle(QPainter& paint, QPoint a, QPoint b, QPoint c, int k);
    void draw_Sierpinski_carpet(QPainter& paint, QRect rect, int k);
    void draw_Koch_curve(QPainter& paint, QPoint a, QPoint b, int k);
    void draw_Koch_snowflake(QPainter& paint, QPoint a, QPoint b, QPoint c);
private slots:
    void on_OKButton_clicked();
};
#endif // MAINWINDOW_H
