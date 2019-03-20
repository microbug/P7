#include "mainwindow.hpp"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    this->vbox = new QVBoxLayout(this);
    this->sudoku_grid = new SudokuGrid;

    this->sudoku_grid->setFrameStyle(QFrame::Plain | QFrame::Box);

    this->sudoku_grid->setRowCount(GRID_WIDTH);  // add the right number of cells to the grid
    this->sudoku_grid->setColumnCount(GRID_WIDTH);

    this->sudoku_grid->horizontalHeader()->setVisible(false);  // hide horizontal table header
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

    QPushButton *testButton = new QPushButton("Test");
    vbox->addWidget(testButton);

    // `this` is the MainWindow object (declared in main.cpp)
    // MainWindow::setLayout(vbox) fills the window with the layout `vbox`,
    // which contains the sudoku grid and the push button

    this->setLayout(vbox);

    // Test filling the grid.
    // Note that the grid is still updated even though this comes after setLayout --
    // this is different to when we used a QPainter to make the grid.
    for (int i = 0; i < pow(GRID_WIDTH, 2); i++) {
        QTableWidgetItem* item = new QTableWidgetItem;
        item->setText("5");
        item->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        this->sudoku_grid->setItem(i % GRID_WIDTH, i / GRID_WIDTH, item);
    }

    // make SudokuGrid::editItem() run every time an item is changed
    connect(this->sudoku_grid, &SudokuGrid::itemChanged, this->sudoku_grid, &SudokuGrid::editItem);
}


void SudokuGrid::editItem(QTableWidgetItem* item) {
    qDebug() << item->text();  // print whatever the user wrote to debug console

    static bool ignore_events = false;  // static => the value carrys over between function calls
    if (!ignore_events) {
        item->setText("2");  // every time the user changes an item, set it to 2
        ignore_events = true;  // stop this function from running again (setText edits the item so it will call this function again)
    } else {
        ignore_events = false;
    }
}


void SudokuGrid::resizeEvent(QResizeEvent *event) {
    // adapted from https://forum.qt.io/topic/78828/3
    event->accept();
    static bool ignore_events = false;
    qDebug() << "resize, x=" << event->size().width() << ", y=" << event->size().height();

    if (!ignore_events) {
        ignore_events = true;

        // table_width is the width of the whole sudoku grid
        int table_width = std::min(event->size().width(), event->size().height());

        // The next three lines call this->resizeEvent() after running. This will be ignored
        // because ignore_events==true.
        QWidget::resize(table_width, table_width);  //  update overall width
        this->verticalHeader()->setDefaultSectionSize(table_width / GRID_WIDTH);  // update column width
        this->horizontalHeader()->setDefaultSectionSize(table_width / GRID_WIDTH);  // update row width

        QThread::msleep(10);  // wait a short time for the events from the resize code above to run
        ignore_events = false;  // allow new resize events
    }
}


MainWindow::~MainWindow() {
    delete sudoku_grid;
    delete sudoku_grid_container;
    delete vbox;
}
