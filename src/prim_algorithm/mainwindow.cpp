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
        bool done[26][26] = {};
        for (int a = 0; a < 26; a++) {
            for (auto edge: adj[a]) {
                int b = edge.first, w = edge.second;
                if (done[b][a]) continue;
                done[a][b] = true;

                char A = a + 'A', B = b + 'A';
                paint.drawLine(coord[A], coord[B]);
                int x = coord[A].x() + (coord[B].x() - coord[A].x()) * 0.25;
                int y = coord[A].y() + (coord[B].y() - coord[A].y()) * 0.25;
                paint.drawText(QPoint(x, y), QString::number(w));
            }
        }
        for (auto node: coord) {
            paint.drawEllipse(node.second, R, R);
            int x = node.second.x(), y = node.second.y();
            paint.drawText(QRect(QPoint(x - R, y - R), QSize(QSize(2 * R,2 * R))), QString(node.first), QTextOption(Qt::AlignCenter));
        }
    }

    if (showstep) {
        for (int i = 0; i < step; i++) {
            int a = res[i].first, b = res[i].second;
            char A = a + 'A', B = b + 'A';
            paint.setPen(QPen(Qt::red, 2));
            paint.drawLine(coord[A], coord[B]);
            paint.setPen(QPen(Qt::black, 2));

            paint.drawEllipse(coord[A], R, R);
            paint.drawText(QRect(QPoint(coord[A].x() - R, coord[A].y() - R), QSize(QSize(2 * R,2 * R))), QString(QChar(A)), QTextOption(Qt::AlignCenter));
            paint.drawEllipse(coord[B], R, R);
            paint.drawText(QRect(QPoint(coord[B].x() - R, coord[B].y() - R), QSize(QSize(2 * R,2 * R))), QString(QChar(B)), QTextOption(Qt::AlignCenter));
        }
    }
}

void MainWindow::on_okButton_clicked()
{
    QString nodes = ui->nodeEdit->toPlainText();
    QString edges = ui->edgeEdit->toPlainText();
    if (nodes.size() == 0 || edges.size() == 0)
        return;

    adj.clear();
    coord.clear();
    res.clear();

    /* prim's algorithm */
    prim(edges);

    /* set coordinate of node */
    sort(nodes.begin(), nodes.end());
    double sita = 2 * M_PI / nodes.size();
    for (int i = 0; i < nodes.size(); i++) {
        int x = 200 * qCos(i * sita);
        int y = 200 * qSin(i * sita);
        coord[(char)nodes[i].unicode()] = {this->size().width() / 2 + x, 250 + y};
    }

    /* draw graph */
    draw = true;
    showstep = false;
    step = 0;
    update();
}

void MainWindow::on_stepButton_clicked()
{
    if (step == res.size()) {
        showstep = false;
        step = 0;
    }
    else {
        showstep = true;
        step++;
    }
    update();
}

void MainWindow::prim(QString& edges) {
    adj = vector<vector<pair<int, int>>>(26, vector<pair<int, int>>());
    int dis[26], parent[26], INF = 0x3f3f3f3f;
    bool done[26];

    /* init */
    for (int i = 0; i < 26; i++) dis[i] = INF;
    memset(parent, -1, sizeof(parent));
    memset(done, 0, sizeof(done));

    QStringList list = edges.split(' ');
    for (QString edge: list) {
        int from = edge[1].unicode() - 'A';
        int to = edge[3].unicode() - 'A';
        int w = edge.mid(5, edge.size() - 6).toInt();

        adj[from].push_back({to, w});
        adj[to].push_back({from, w});
    }

    priority_queue<pair<int, int>> pq;
    dis[0] = 0;
    pq.push({0, 0});

    while (!pq.empty()) {
        int a = pq.top().second; pq.pop();

        if (done[a]) continue;
        done[a] = true;

        if (parent[a] != -1)
            res.push_back({a, parent[a]}); // result

        for (auto edge: adj[a]) {
            int b = edge.first, w = edge.second;
            if (!done[b] && w <= dis[b]) {
                dis[b] = w;
                parent[b] = a;
                pq.push({-w, b});
            }
        }
    }
}
