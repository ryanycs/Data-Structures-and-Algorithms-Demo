#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <set>
#include <queue>
using namespace std;

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
    void dijkstra(vector<vector<pair<int, int>>>& adj, set<int>& vertices, int start);

    bool draw = false;
    int width = 50, height = 25;
    int start;
    vector<char> seq, vertex;
    vector<vector<int>> result;

private slots:
    void on_okButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
