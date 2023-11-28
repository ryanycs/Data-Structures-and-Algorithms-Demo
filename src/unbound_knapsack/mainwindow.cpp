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
}

void MainWindow::on_okButton_clicked()
{
    QString s = ui->weight->toPlainText();
    ui->weight->setPlainText("");

    int weight = s.toInt();
    ui->textBrowser->setPlainText(knapsack(weight));
}

QString MainWindow::knapsack(int weight) {
    QString res;
    int n = 4;
    int w[] = {3, 10, 25, 27};
    int v[] = {2, 11, 27, 30};
    map<char, int> cnt;
    vector<int> dp(weight + 1);
    vector<pair<int, int>> memo(weight + 1, {0, -1});

    for (int i = 0; i < n; i++) {
        for (int j = w[i]; j <= weight; j++) {
            if (dp[j-w[i]] + v[i] > dp[j]) {
                dp[j] = dp[j-w[i]] + v[i];
                memo[j] = {j-w[i], i};
            }
        }
    }

    int i = weight;
    while (i) {
        if (memo[i].second != -1)
            cnt[memo[i].second + 'A']++;
        i = memo[i].first;
    }

    res += QString("今天可販售的最高金額 %1 元\n").arg(dp[weight]);
    res += "農作物：\n";
    for (auto item: cnt) {
        res += QString("%1，數量 %2 。\n").arg(item.first).arg(item.second);
    }
    return res;
}
