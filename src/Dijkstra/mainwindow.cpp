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
    paint.setFont(QFont("Consolas",12));

    /* A C 10,A E 30,A F 100,B C 5,C D 50,D F 10,E F 60,E D 20 */
    if (draw) {
        int x = 10, y = 10;
        for (int i = 0; i < result.size(); i++) {
            if (i == 0)
                paint.drawText(QRect(QPoint(x, y), QSize(100,height)), QString("Initial"), QTextOption(Qt::AlignCenter));
            else
                paint.drawText(QRect(QPoint(x, y), QSize(100,height)), QString("Including %1").arg(seq[i]), QTextOption(Qt::AlignCenter));

            y += height;

            for (int j = 0; j <= result[0].size(); j++) {
                paint.drawRect(x + width * j, y, width, height);
                if (j >= 1)
                    paint.drawText(QRect(QPoint(x + width * j, y), QSize(width,height)), QString("%1").arg(vertex[j-1]), QTextOption(Qt::AlignCenter));
            }

            y += height;

            for (int j = 0; j <= result[0].size(); j++) {
                paint.drawRect(x + width * j, y, width, height);
                if (j == 0)
                    paint.drawText(QRect(QPoint(x + width * j, y), QSize(width,height)), QString("%1").arg(QChar(start + 'A')), QTextOption(Qt::AlignCenter));
                else
                    paint.drawText(QRect(QPoint(x + width * j, y), QSize(width,height)), QString("%1").arg(result[i][j-1]), QTextOption(Qt::AlignCenter));
            }
            y += height;
        }
    }
}

void MainWindow::on_okButton_clicked()
{
    QString s = ui->textEdit->toPlainText();
    QString s2 = ui->textEdit_2->toPlainText();

    if (s.size() == 0 || s2.size() == 0)
        return;

    seq.clear();
    vertex.clear();
    result.clear();

    start = s2[0].toLatin1() - 'A';

    QStringList list = s.split(',');
    vector<vector<pair<int, int>>> adj(26, vector<pair<int, int>>());
    set<int> vertices;

    for (auto &e: list) {
        QStringList list2 = e.split(' ');
        char a = list2[0][0].toLatin1(), b = list2[1][0].toLatin1();
        int w = list2[2].toInt();
        adj[a-'A'].push_back({b - 'A', w});
        adj[b-'A'].push_back({a - 'A', w});
        vertices.insert(a - 'A');
        vertices.insert(b - 'A');
    }

    for (auto v: vertices)
        vertex.push_back(v + 'A');

    dijkstra(adj, vertices, start);
    draw = true;
    update();
//    ui->textBrowser->setText(res);
}

void MainWindow::dijkstra(vector<vector<pair<int, int>>>& adj, set<int>& vertices, int start) {
    vector<int> distance(26, 9999);
    vector<bool> visit(26);
    priority_queue<pair<int, int>> pq; // {distance, vertex_b}

    distance[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int a = pq.top().second; pq.pop();

        if (visit[a]) continue;
        visit[a] = true;

        for (auto e: adj[a]) {
            int b = e.first, weight = e.second;

            if (distance[a] + weight < distance[b]) {
                distance[b] = distance[a] + weight;
                pq.push({-distance[b], b});
            }
        }

        seq.push_back(a + 'A');
        vector<int> tmp;
        for (int i: vertices)
            tmp.push_back(distance[i]);
        result.push_back(tmp);
    }
}
