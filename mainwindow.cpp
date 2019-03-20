#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    this->vbox = new QVBoxLayout(this);
    this->sudoku_grid = new SudokuTable;

    QString style("QTableView\
        {\
            color: #000;\
            border: 1px solid #000;\
            background: #FFF;\
            gridline-color: #000;\
            padding: 0px;margin:0px; \
        }\
        QTableView::item\
        {\
            background: #FFF;\
        }");
    this->sudoku_grid->setStyleSheet(style);
    this->sudoku_grid->setFrameStyle(QFrame::Plain | QFrame::Box);

    this->sudoku_grid->setRowCount(GRID_WIDTH);
    this->sudoku_grid->setColumnCount(GRID_WIDTH);


    this->sudoku_grid->horizontalHeader()->setVisible(false);  // hide table header
    this->sudoku_grid->horizontalHeader()->setMinimumSectionSize(0);  // set minimum
    //this->sudoku_grid->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    this->sudoku_grid->verticalHeader()->setVisible(false);
    this->sudoku_grid->verticalHeader()->setMinimumSectionSize(0);
    //this->sudoku_grid->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    this->sudoku_grid->resizeColumnsToContents();

    // adapted from https://stackoverflow.com/a/37615363
    this->sudoku_grid->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->sudoku_grid->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //this->sudoku_grid->setFixedSize(this->sudoku_grid->horizontalHeader()->length() + 2,
    //                                this->sudoku_grid->verticalHeader()->length() + 2);


    // the hbox container makes sure the grid is centred horizontally
    this->sudoku_grid_container = new QHBoxLayout();
    this->sudoku_grid_container->addWidget(this->sudoku_grid);
    this->vbox->addLayout(this->sudoku_grid_container);
    this->setLayout(vbox);
}


MainWindow::~MainWindow() {
    //delete ui;
}

void SudokuTable::resizeEvent(QResizeEvent *event)
{
    event->accept();

    int table_width;
    if (event->size().width() > event->size().height()) {  // resize to the smaller of the two dimensions
        table_width = event->size().height();
    } else {
        table_width = event->size().width();
    }

    QWidget::resize(table_width, table_width);
    this->verticalHeader()->setDefaultSectionSize(table_width / GRID_WIDTH);
    this->horizontalHeader()->setDefaultSectionSize(table_width / GRID_WIDTH);

}

