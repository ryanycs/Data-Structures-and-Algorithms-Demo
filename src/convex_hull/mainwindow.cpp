#include "mainwindow.h"
#include "./ui_mainwindow.h"
Point p0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter paint(this);
    paint.setBrush(Qt::white);
    paint.setPen(QPen(Qt::black, 2));

    if (draw == true) {
        for (int i = 1; i < convex_hull.size(); i++) {
            paint.drawLine(convex_hull[i].x, convex_hull[i].y, convex_hull[i-1].x, convex_hull[i-1].y);
        }

        for (auto point: points) {
            paint.drawEllipse(QPoint(point.x, point.y), 5, 5);
        }
    }
}

void MainWindow::on_okButton_clicked()
{
    QString s = ui->pointEdit->toPlainText();
    QStringList list = s.split('\n');
    points.clear();
    convex_hull.clear();

    for (auto& point: list) {
        QStringList p = point.split(' ');
        points.push_back({p[0].toInt(), p[1].toInt()});
    }

    convex_hull = graham_scan(points);

    for (int i = 0; i < convex_hull.size(); i++) {
        convex_hull[i].x = convex_hull[i].x * unit + 50;
        convex_hull[i].y = convex_hull[i].y * unit + 50;
    }
    for (int i = 0; i < points.size(); i++) {
        points[i].x = points[i].x * unit + 50;
        points[i].y = points[i].y * unit + 50;
    }

    draw = true;
    update();
}

/* ab x ac */
int cross(Point& a, Point& b, Point& c) {
    return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

/* distance(a, b)^2 */
int distance2(Point& a, Point& b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

bool cmp(Point& a, Point& b) {
    int cross_ab = cross(p0, a, b);
    int distance_a = distance2(p0, a);
    int distance_b = distance2(p0, b);

    return cross_ab > 0 || (cross_ab == 0 && distance_a < distance_b);
}

vector<Point> graham_scan(vector<Point> p) {
    int n = p.size();

    /* find the buttom left point */
    int min_idx = 0;
    for (int i = 1; i < n; i++) {
        if (p[i].y < p[min_idx].y ||
                p[i].y == p[min_idx].y && p[i].x < p[min_idx].x)
            min_idx = i;
    }
    swap(p[0], p[min_idx]);
    p0 = p[0];

    /* sort by angle */
    sort(p.begin() + 1, p.end(), cmp);

    /* remove the point if the points has the same angle but leave the farthest one */
    int m = 1;
    for (int i = 1; i < n; i++) {
        while (i < n-1 && cross(p0, p[i], p[i+1]) == 0)
            i++;

        p[m] = p[i];
        m++;
    }

    /* start to add the point and check */
    vector<Point> stk;

    for (int i = 0; i < m; i++) {
        while (stk.size() >= 2 &&
                cross(*(stk.end() - 2), *(stk.end() - 1), p[i]) < 0)
            stk.pop_back();
        stk.push_back(p[i]);
    }
    stk.push_back(p[0]);

    return stk;
}
