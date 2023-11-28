#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once
#include <QMainWindow>
#include <QPainter>
#include <vector>
using std::vector;
using std::swap;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);
    void draw_tree(QPainter& paint, vector<int>& arr, int root, int x, int y, int w);
    template <class T> void heapify(vector<T>& arr, int root, int size);
    template <class T> void build_heap(vector<T>& arr, int size);
    template <class T> void heap_sort(vector<T>& arr, int size);

    bool draw_heap = false, draw_step = false;
    int radis, width, height;
    int step_idx = 0;
    vector<int> arr;
    vector<vector<int>> step;

private slots:
    void on_pushButton_clicked();

    void on_showButton_clicked();

    void on_resultButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
