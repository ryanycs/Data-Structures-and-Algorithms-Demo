#include "mainwindow.h"
#include "./ui_mainwindow.h"
#define N 30

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    W = 500;
    H = 50;
    R = 30;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter paint(this);
    paint.setBrush(Qt::white);
    paint.setFont(QFont("Consolas",10));

    if (draw) {
        drawTree(paint, tree.root, this->size().width()/ 2, 20, W);
    }
}

void MainWindow::on_okButton_clicked()
{
    QString nodes = ui->nodeEdit->toPlainText();
    QString freqs = ui->freqEdit->toPlainText();

    obst(nodes, freqs);

    draw = true;
    update();

    vector<QChar> order;
    QString text;
    order = tree.preorder();
    for (int i = 0; i < order.size(); i++) {
        text += QString(order[i]) + (i == order.size() - 1 ? "" : ",");
    }
    ui->PreorderBrowser->setPlainText(text);
    text.clear();

    order = tree.inorder();
    for (int i = 0; i < order.size(); i++) {
        text += QString(order[i]) + (i == order.size() - 1 ? "" : ",");
    }
    ui->InorderBrowser->setPlainText(text);
    text.clear();

//    order = tree.posorder();
//    for (int i = 0; i < order.size(); i++) {
//        text += QString(order[i]) + (i == order.size() - 1 ? "" : ",");
//    }
//    ui->PosorderBrowser->setPlainText(text);
//    text.clear();
}

void MainWindow::obst(QString nodes, QString freqs) {
    int n = nodes.size(), INF = 0x3f3f3f3f;
    int freq[N], prefix_sum[N] = {};
    int dp[N][N];
    vector<vector<int>> memo(N, vector<int>(N));

    QStringList list = freqs.split(' ');
    for (int i = 0; i < n; i++) {
        freq[i] = list[i].toInt();
        prefix_sum[i+1] = prefix_sum[i] + freq[i];
    }

    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++)
            dp[i][j] = INF;

    for (int i = 0; i < n; i++) {
        dp[i][i] = freq[i];
        memo[i][i] = i;
    }

    for (int length = 2; length <= n; length++) {
        for (int i = 0; i + length - 1 < n; i++) {
            int j = i + length - 1;
            for (int k = i; k <= j; k++) {
                int cost = (k > i ? dp[i][k-1] : 0) +
                           (k < j ? dp[k+1][j] : 0) +
                           prefix_sum[j+1] - prefix_sum[i];
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                    memo[i][j] = k;
                }
            }
        }
    }

    tree.root = find_ans(0, n-1, nodes, memo);
}

TreeNode<QChar>* MainWindow::find_ans(int l, int r, QString& s, vector<vector<int>>& memo) {
    if (l > r)
        return NULL;

    int m = memo[l][r];
    TreeNode<QChar> *node;
    node = new TreeNode(s[m]);
    node->left = find_ans(l, m - 1, s, memo);
    node->right = find_ans(m + 1, r, s, memo);
    return node;
}

void MainWindow::drawTree(QPainter& paint, TreeNode<QChar>* node, int x, int y, int w) {
    if (node == NULL)
        return;

    int curWidth = w / 2;

    paint.drawEllipse(x, y, R, R);

    paint.drawText(QRect(QPoint(x, y),QSize(QSize(R,R))), QString(node->val), QTextOption(Qt::AlignCenter));

    if (node->left != NULL)
        paint.drawLine(x + R / 2, y + R, x - curWidth + R / 2, y + H);
    if (node->right != NULL)
       paint.drawLine(x + R / 2, y + R, x + curWidth + R / 2, y + H);

    drawTree(paint, node->left, x - curWidth, y + H, curWidth);
    drawTree(paint, node->right, x + curWidth, y + H, curWidth);
}
