#include "mainwindow.h"
#include "./ui_mainwindow.h"

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
    paint.setFont(QFont("Consolas",15));

    if (draw) {
        for (auto edge: edges) {
            int w = edge[0], a = edge[1], b = edge[2];

            char A = a + 'A', B = b + 'A';
            paint.drawLine(coord[A], coord[B]);
            int x = coord[A].x() + (coord[B].x() - coord[A].x()) * 0.25;
            int y = coord[A].y() + (coord[B].y() - coord[A].y()) * 0.25;
            paint.drawText(QPoint(x, y), QString::number(w));
        }

        for (auto node: coord) {
            paint.drawEllipse(node.second, radis, radis);
            int x = node.second.x(), y = node.second.y();
            paint.drawText(QRect(QPoint(x - radis, y - radis), QSize(QSize(2 * radis, 2 * radis))), QString(node.first), QTextOption(Qt::AlignCenter));
        }
    }

    if (draw_step) {
        draw_step = false;
        for (int i = 0; i < step_num; i++) {
            int a = step[i][0], b = step[i][1];
            char A = a + 'A', B = b + 'A';
            paint.setPen(QPen(Qt::red, 2));
            paint.drawLine(coord[A], coord[B]);
            paint.setPen(QPen(Qt::black, 2));

            paint.drawEllipse(coord[A], radis, radis);
            paint.drawText(QRect(QPoint(coord[A].x() - radis, coord[A].y() - radis), QSize(QSize(2 * radis,2 * radis))), QString(QChar(A)), QTextOption(Qt::AlignCenter));
            paint.drawEllipse(coord[B], radis, radis);
            paint.drawText(QRect(QPoint(coord[B].x() - radis, coord[B].y() - radis), QSize(QSize(2 * radis,2 * radis))), QString(QChar(B)), QTextOption(Qt::AlignCenter));
        }

        if (step_num < step.size())
            step_num++;
        else
            step_num = 0;

    }
}

void MainWindow::on_okButton_clicked()
{
//    vector<vector<int>> edges;
    QString s = ui->textEdit->toPlainText();
    QString nodes = ui->nodeEdit->toPlainText();
    if (s.size() == 0 || nodes.size() == 0)
        return;

    sort(nodes.begin(), nodes.end());
    double sita = 2 * M_PI / nodes.size();
    for (int i = 0; i < nodes.size(); i++) {
        int x = 200 * qCos(i * sita);
        int y = 200 * qSin(i * sita);
        coord[nodes[i].toLatin1()] = {this->size().width() / 2 + x, 250 + y};
    }

    QStringList list = s.split(' ');
    for (auto e: list) {
        int a = e[1].toLatin1() - 'A';
        int b = e[3].toLatin1() - 'A';
        int w = e.mid(5, e.size() - 6).toInt();

        edges.push_back({w, a, b});
    }

    /* (B,A,1) (B,C,2) (C,D,3) (D,B,6) (D,E,6) */
    /* (A,B,9) (A,C,3) (C,D,6) (B,F,1) (C,F,2) (F,G,4) (F,E,5) (E,G,1) (D,E,1) */
    kruskal(edges);

    draw = true;
    update();
}

void MainWindow::on_showButton_clicked()
{
    draw_step = true;
    update();
}

int MainWindow::Find(int a) {
    if (parent[a] == a)
        return a;
    return parent[a] = Find(parent[a]);
}

void MainWindow::Union(int a, int b) {
    int root_a = Find(a);
    int root_b = Find(b);
    if (root_a != root_b) {
        parent[root_a] = root_b;
    }
}

void MainWindow::kruskal(vector<vector<int>>& edges) {
    for (int i = 0; i < 26; i++)
        parent[i] = i;

    int cost = 0;
    sort(edges.begin(), edges.end());
    for (vector<int> e: edges) {
        int w = e[0], a = e[1], b = e[2];
        if (Find(a) != Find(b)) {
            cost += w;
            Union(a, b);
            step.push_back({a, b});
//            printf("%d - %d, w = %d\n", a, b, w);
        }
    }
}
