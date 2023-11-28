#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    width = 500;
    x = this->size().width() / 2, y = 50;
    draw = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter paint(this);

    if (draw) {
        //    draw_Sierpinski_triangle(paint, QPoint(x, y),
        //                QPoint(x - width / 2, y + (double)(sqrt(3) / 2) * width),
        //                QPoint(x + width / 2, y + (double)(sqrt(3) / 2) * width), 0);

        //    draw_Sierpinski_carpet(paint, QRect(x, y, width, width), 0);
        //    draw_Koch_curve(paint, QPoint(x, y), QPoint(x + width, y), 0);
        paint.eraseRect(QRect(0, 0, this->size().width(), this->size().height()));
        draw_Koch_snowflake(paint, QPoint(x, y),
                            QPoint(x - width / 2, y + (double)(sqrt(3) / 2) * width),
                            QPoint(x + width / 2, y + (double)(sqrt(3) / 2) * width));
        //    QPoint point[3] = {{50, 0}, {0, 50}, {100, 50}};
        //    paint.drawPolygon(point, 3);
    }
}

void MainWindow::draw_Sierpinski_triangle(QPainter& paint, QPoint a, QPoint b, QPoint c, int k) {
    if (k == n)
        return;

    QPoint tri[3] = {a, b, c};
    paint.setBrush(Qt::black);
    paint.drawPolygon(tri, 3);
    paint.setBrush(Qt::white);

    QPoint p = {(a.x() + b.x()) / 2, (a.y() + b.y()) / 2};
    QPoint q = {(a.x() + c.x()) / 2, (a.y() + c.y()) / 2};
    QPoint r = {(b.x() + c.x()) / 2, (b.y() + c.y()) / 2};
    QPoint tri2[3] = {p, q, r};
//    paint.setBrush(Qt::black);
    paint.drawPolygon(tri2, 3);
//    paint.setBrush(Qt::white);

    draw_Sierpinski_triangle(paint, a, p, q, k + 1);
    draw_Sierpinski_triangle(paint, p, b, r, k + 1);
    draw_Sierpinski_triangle(paint, q, r, c, k + 1);
}

void MainWindow::draw_Sierpinski_carpet(QPainter& paint, QRect rect, int k){
    if (k == n)
        return;
    int w = rect.width() / 3;

    QPoint a = {rect.topLeft().x() + w, rect.topLeft().y() + w};
    QPoint b = {rect.topRight().x() - w, rect.topRight().y() + w};
    QPoint c = {rect.bottomLeft().x() + w, rect.bottomLeft().y() - w};
    QPoint d = {rect.bottomRight().x() - w, rect.bottomRight().y() - w};

    paint.setBrush(Qt::black);
    paint.drawRect(QRect(a, d));
    paint.setBrush(Qt::white);
    draw_Sierpinski_carpet(paint, QRect(rect.topLeft().x(), rect.topLeft().y(), w, w), k + 1);
    draw_Sierpinski_carpet(paint, QRect(rect.topLeft().x() + w, rect.topLeft().y(), w, w), k + 1);
    draw_Sierpinski_carpet(paint, QRect(rect.topRight().x() - w, rect.topLeft().y(), w, w), k + 1);

    draw_Sierpinski_carpet(paint, QRect(rect.topLeft().x(), rect.topLeft().y() + w, w, w), k + 1);
    draw_Sierpinski_carpet(paint, QRect(rect.topRight().x() - w, rect.topLeft().y() + w, w, w), k + 1);

    draw_Sierpinski_carpet(paint, QRect(rect.topLeft().x(), rect.bottomLeft().y() - w, w, w), k + 1);
    draw_Sierpinski_carpet(paint, QRect(rect.topLeft().x() + w, rect.bottomLeft().y() - w, w, w), k + 1);
    draw_Sierpinski_carpet(paint, QRect(rect.topRight().x() - w, rect.bottomLeft().y() - w, w, w), k + 1);
}

void MainWindow::draw_Koch_snowflake(QPainter& paint, QPoint a, QPoint b, QPoint c) {
    draw_Koch_curve(paint, a, b, 0);
    draw_Koch_curve(paint, b, c, 0);
    draw_Koch_curve(paint, c, a, 0);
}

void MainWindow::draw_Koch_curve(QPainter& paint, QPoint a, QPoint b, int k){
    if (k == n) {
        paint.drawLine(a, b);
        return;
    }

    int dx = (b.x() - a.x()) / 3;
    int dy = (b.y() - a.y()) / 3;

    QPoint p = {
        a.x() + dx,
        a.y() + dy
    };
    QPoint q = {
        a.x() + 2 * dx,
        a.y() + 2 *dy
    };
    QPoint r = {
        (int)((a.x() + b.x()) * 0.5 + sqrt(3) * (a.y() - b.y()) / 6),
        (int)((a.y() + b.y()) * 0.5 + sqrt(3) * (b.x() - a.x()) / 6)
    };

    draw_Koch_curve(paint, a, p, k + 1);
    draw_Koch_curve(paint, p, r, k + 1);
    draw_Koch_curve(paint, r, q, k + 1);
    draw_Koch_curve(paint, q, b, k + 1);
}

void MainWindow::on_OKButton_clicked()
{
    n = ui->textEdit->toPlainText().toInt();
    draw = true;
    update();
}

