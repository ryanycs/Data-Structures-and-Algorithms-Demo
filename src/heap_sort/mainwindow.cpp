#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    paint.setPen(Qt::black);

    if (draw_heap) {
        draw_tree(paint, arr, 0, this->size().width()/ 2, 20, width);
        draw_heap = false;
    }
    if (draw_step) {
        draw_step = false;
        draw_tree(paint, step[step_idx], 0, this->size().width()/ 2, 20, width);

//        if (step_idx < step.size() - 1)
//            step_idx++;
    }
}

void MainWindow::on_pushButton_clicked()
{
    QString s = ui->textEdit->toPlainText();
    QStringList buffer = s.split(',');
    arr.clear();
    step.clear();
    step_idx = 0;

    for (auto& str: buffer) {
        arr.push_back(str.toInt());
    }

    heap_sort(arr, arr.size());

    draw_step = true;
    update();

    QString res;
    for (auto& num: arr) {
        res.push_back(QString::number(num));
        res.push_back(",");
    }
    res.removeLast();

    ui->textBrowser->setPlainText(res);
//    ui->textEdit->setPlainText("");
//    ui->textEdit->setPlainText(res);
}

void MainWindow::on_showButton_clicked()
{
    draw_step = true;
    update();
    if (step_idx < step.size() - 1)
        step_idx++;
}

void MainWindow::on_resultButton_clicked()
{
    draw_heap = true;
    update();
}


void MainWindow::draw_tree(QPainter& paint, vector<int>& arr, int root, int x, int y, int w) {
    if (root >= arr.size())
        return;

    int curWidth = w / 2;

    paint.drawEllipse(x, y, radis, radis);

    paint.drawText(QRect(QPoint(x, y),QSize(QSize(radis,radis))), QString::number(arr[root]), QTextOption(Qt::AlignCenter));

    if (root * 2 + 1 < arr.size())
        paint.drawLine(x + radis / 2, y + radis, x - curWidth + radis / 2, y + height);
    if (root * 2 + 2 < arr.size())
       paint.drawLine(x + radis / 2, y + radis, x + curWidth + radis / 2, y + height);

    draw_tree(paint, arr, root * 2 + 1, x - curWidth, y + height, curWidth);
    draw_tree(paint, arr, root * 2 + 2, x + curWidth, y + height, curWidth);
}

template <class T>
void MainWindow::heapify(vector<T>& arr, int root, int size) {
    int left = root << 1;
    int right = root << 1 | 1;
    int mx_idx = root;

    if (left <= size && arr[left] > arr[mx_idx])
        mx_idx = left;
    if (right <= size && arr[right] > arr[mx_idx])
        mx_idx = right;

    if (mx_idx != root) {
        swap(arr[root], arr[mx_idx]);
        step.push_back(vector<T>(arr.begin() + 1, arr.end()));
        heapify(arr, mx_idx, size);
    }
}

template <class T>
void MainWindow::build_heap(vector<T>& arr, int size) {
    for (int i = size / 2; i >= 1; i--)
        heapify(arr, i, size);
}

template <class T>
void MainWindow::heap_sort(vector<T>& arr, int size) {
    arr.insert(arr.begin(), 0);
    step.push_back(vector<T>(arr.begin() + 1, arr.end()));
    build_heap(arr, size);
    for (int last = size; last >= 2; last--) {
        swap(arr[1], arr[last]);
        step.push_back(vector<T>(arr.begin() + 1, arr.end()));
        heapify(arr, 1, last - 1);
    }
    arr.erase(arr.begin());
}
