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

    /* A B 15,A C 31,B C 10 */
    /* (A,B,8) (A,C,9) (A,D,6) (B,C,7) (B,E,9) (B,F,4) (C,D,6) (C,E,2) (C,F,3) (D,F,2) (E,G,3) (F,G,3) */
    if (draw) {
        int x = 10, y = 10;
        draw = false;

        if (step == 0)
            paint.drawText(QRect(QPoint(x, y), QSize(100,height)), QString("Initial"), QTextOption(Qt::AlignCenter));
        else
            paint.drawText(QRect(QPoint(x, y), QSize(100,height)), QString("Including %1").arg(QChar(vertex[step-1] + 'A')), QTextOption(Qt::AlignCenter));

        y += height;

        for (int i = 0; i <= vertex.size(); i++) {
            for (int j = 0; j <= vertex.size(); j++) {
                int a = vertex[i-1], b = vertex[j-1];

                paint.drawRect(x + width * j, y, width, height);
                if (i == 0 && j != 0)
                    paint.drawText(QRect(QPoint(x + width * j, y), QSize(width,height)), QString("%1").arg(QChar(b + 'A')), QTextOption(Qt::AlignCenter));
                else if (i != 0 && j == 0)
                    paint.drawText(QRect(QPoint(x + width * j, y), QSize(width,height)), QString("%1").arg(QChar(a + 'A')), QTextOption(Qt::AlignCenter));
                else if (i != 0 && j != 0)
                    paint.drawText(QRect(QPoint(x + width * j, y), QSize(width,height)), QString("%1").arg(result[step][a][b]), QTextOption(Qt::AlignCenter));
            }
            y += height;
        }

        if (step < result.size() - 1)
            step = step + 1;
        else
            step = 0;
    }
}

void MainWindow::on_okButton_clicked()
{
    QString s = ui->textEdit->toPlainText();

    if (s.size() == 0)
        return;

    vertex.clear();
    result.clear();
    step = 0;

    QStringList list = s.split(' ');
    vector<vector<int>> adj(26, vector<int>(26, 1000));
    set<int> vertices;

    for (int i = 0; i < 26; i++)
        adj[i][i] = 0;

    for (auto& e: list) {
        int a = e[1].toLatin1() - 'A';
        int b = e[3].toLatin1() - 'A';
        int w = e.mid(5, e.size() - 6).toInt();

        adj[a][b] = w;
        adj[b][a] = w;
        vertices.insert(a);
        vertices.insert(b);
    }

    for (auto v: vertices)
        vertex.push_back(v);

    folyd_warshell(adj, vertices);
}

void MainWindow::on_showButton_clicked()
{
    draw = true;
    update();
}

void MainWindow::folyd_warshell(vector<vector<int>>& dp, set<int>& vertices) {
    int n = dp.size();

    result.push_back(dp);

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dp[i][k] == 1000 || dp[k][j] == 1000) continue;
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
            }
        }
        if (vertices.find(k) != vertices.end())
            result.push_back(dp);
    }
}
