#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define GRID_WIDTH 9
#define CELL_WIDTH 50  // pixels

//#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QColumnView>
#include <QDebug>
#include <QFrame>
#include <QResizeEvent>
#include <QThread>
#include <algorithm>
#include <cmath>
#include <QApplication>


namespace Ui {
    class MainWindow;
}

class SudokuGrid: public QTableWidget {
    Q_OBJECT

public:
    using QTableWidget::QTableWidget;  // inherit the constructor

    void resizeEvent(QResizeEvent* event);
};

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QVBoxLayout* vbox;
    QHBoxLayout* sudoku_grid_container;
    SudokuGrid* sudoku_grid;
    //void resizeEvent(QResizeEvent *event);

private:
    //Ui::MainWindow *ui;
};

void sudokuEditItem(QTableWidgetItem* item);

#endif // MAINWINDOW_H
