#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <set>
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
    void folyd_warshell(vector<vector<int>>& dp, set<int>& vertices);

    bool draw = false;
    int step = 0;
    int width = 50, height = 25;
    vector<int> vertex;
    vector<vector<vector<int>>> result;

private slots:
    void on_okButton_clicked();

    void on_showButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
