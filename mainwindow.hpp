#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define GRID_WIDTH 9

#include <algorithm>
#include <cmath>

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QColumnView>
#include <QDebug>
#include <QResizeEvent>
#include <QThread>
#include <QApplication>
#include <QPushButton>


namespace Ui {
    class MainWindow;
}

class SudokuGrid: public QTableWidget {  // a view class (SudokuPuzzle is a model class)
    Q_OBJECT

    public:
        using QTableWidget::QTableWidget;  // inherit the QTableWidget constructor

    public slots:
        void editItem(QTableWidgetItem* item);

    private slots:
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
};

#endif // MAINWINDOW_H
