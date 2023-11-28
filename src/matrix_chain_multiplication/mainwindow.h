#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
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
    QString matrix_chain_multiplication(QString& name, QString& size);
    QString find_ans(int l, int r, QString& s, vector<vector<int>>& memo);

private slots:
    void on_okButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
