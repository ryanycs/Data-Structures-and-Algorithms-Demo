#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    draw = false;
    width = 500;
    height = 50;
    radis = 30;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter paint(this);
    paint.setBrush(Qt::white);
    paint.setFont(QFont("times",10));
    if (draw) {
        drawTree(paint, tree.root, this->size().width()/ 2, 20, width);
    }
}

void MainWindow::on_InsertButton_clicked()
{
    QStringList list = ui->textEdit->toPlainText().split(" ");
    ui->textEdit->setPlainText("");
    for (QString& s: list) {
        int insertNode = s.toInt();
        tree.insert(insertNode);
    }
}

void MainWindow::on_DrawButton_clicked()
{
    draw = true;
    update();
}

void MainWindow::drawTree(QPainter& paint, TreeNode<int>* node, int x, int y, int w) {
    if (node == NULL)
        return;

    int curWidth = w / 2;

    if (node->color == RED) {
        paint.setPen(Qt::red);
        paint.setBrush(Qt::red);
    }
    paint.drawEllipse(x, y, radis, radis);
    paint.setBrush(Qt::white);
    paint.setPen(Qt::black);

    if (node->color == RED) paint.setPen(Qt::white);
    paint.drawText(QRect(QPoint(x, y),QSize(QSize(radis,radis))), QString::number(node->val), QTextOption(Qt::AlignCenter));
    paint.setPen(Qt::black);

    // draw red edge
    if (node->color == RED) {
        paint.setPen(Qt::red);
        if (node == node->parent->left) {
            paint.drawLine(x + radis / 2, y, x + w + radis / 2, y - height + radis);
        }
        else if (node == node->parent->right) {
            paint.drawLine(x + radis / 2, y, x - w + radis / 2, y - height + radis);
        }
        paint.setPen(Qt::black);
    }

    if (node->left != NULL)
        paint.drawLine(x + radis / 2, y + radis, x - curWidth + radis / 2, y + height);
    if (node->right != NULL)
       paint.drawLine(x + radis / 2, y + radis, x + curWidth + radis / 2, y + height);

    drawTree(paint, node->left, x - curWidth, y + height, curWidth);
    drawTree(paint, node->right, x + curWidth, y + height, curWidth);
}
