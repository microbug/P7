#include "mainwindow.hpp"

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

    this->sudoku_grid->setRowCount(GRID_WIDTH);    // add the right number of cells to the grid
    this->sudoku_grid->setColumnCount(GRID_WIDTH);

    this->sudoku_grid->horizontalHeader()->setVisible(false);  // hide table header
    // remove cell minimum size restriction (this will be limited by minimum window size)
    this->sudoku_grid->horizontalHeader()->setMinimumSectionSize(0);
    this->sudoku_grid->verticalHeader()->setVisible(false);
    this->sudoku_grid->verticalHeader()->setMinimumSectionSize(0);

    this->sudoku_grid->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->sudoku_grid->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // the hbox container allows us to use stretch items
    //   to keep the sudoku puzzle centered in the window
    this->sudoku_grid_container = new QHBoxLayout();
    this->sudoku_grid_container->addStretch();
    this->sudoku_grid_container->addWidget(this->sudoku_grid);
    this->sudoku_grid_container->addStretch();
    this->vbox->addLayout(this->sudoku_grid_container);
    this->setLayout(vbox);
}


MainWindow::~MainWindow() {
    delete sudoku_grid;
    delete sudoku_grid_container;
    delete vbox;
}

void SudokuTable::resizeEvent(QResizeEvent *event) {
    // adapted from https://forum.qt.io/topic/78828/3
    event->accept();
    static bool ignore_event = false;  // static => the value carrys over between function calls
    qDebug() << "resize, x=" << event->size().width() << ", y=" << event->size().height();

    if (!ignore_event) {
        int table_width;  // width / height of the whole sudoku puzzle
        if (event->size().width() > event->size().height()) {  // resize to the smaller of the two dimensions
            table_width = event->size().height();
        } else {
            table_width = event->size().width();
        }

        QWidget::resize(table_width, table_width);
        ignore_event = true;  // the above triggers another event, which should be ignored
        this->verticalHeader()->setDefaultSectionSize(table_width / GRID_WIDTH);
        ignore_event = true;
        this->horizontalHeader()->setDefaultSectionSize(table_width / GRID_WIDTH);
        ignore_event = true;
    } else {
        ignore_event = false;
    }

}

