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
    QString name = ui->nameEdit->toPlainText();
    QString size = ui->sizeEdit->toPlainText();

    ui->textBrowser->setPlainText(matrix_chain_multiplication(name, size));
}

QString MainWindow::matrix_chain_multiplication(QString& name, QString& size) {
    QString res;
    int n = name.size(), INF = 0x3f3f3f3f;
    vector<int> r, c;
    vector<vector<int>> dp(n, vector<int>(n));
    vector<vector<int>> memo(n, vector<int>(n, -1));

    QStringList list = size.split(',');
    for (QString& s: list) {
        QStringList nums = s.split('*');
        r.push_back(nums[0].toInt());
        c.push_back(nums[1].toInt());
    }

    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++)
            dp[i][j] = INF;

    for (int i = 0; i < n; i++)
         dp[i][i] = 0;

    for (int length = 2; length <= n; length++) {
        for (int i = 0; i + length - 1 < n; i++) {
            int j = i + length - 1;
            for (int k = 0; k < j; k++) {
                int cost = dp[i][k] + dp[k+1][j] + r[i] * c[k] * c[j];
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                    memo[i][j] = k;
                }
            }
        }
    }

    res += "(" + find_ans(0, n - 1, name, memo) + ")";
    res += QString("\n所需乘法次數：%1次\n").arg(dp[0][n-1]);
    return res;
}

QString MainWindow::find_ans(int l, int r, QString& s, vector<vector<int>>& memo) {
    if (l == r)
        return s.mid(l, 1);

    int m = memo[l][r];
    QString L = find_ans(l, m, s, memo);
    QString R = find_ans(m + 1, r, s, memo);
    if (L.size() > 1) L = "(" + L + ")";
    if (R.size() > 1) R = "(" + R + ")";
    return L + R;
}
