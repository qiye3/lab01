#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QApplication>
#include <QMainWindow>
#include <QSplitter>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QScrollArea>
#include <QFrame>
#include <QLabel>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QTableWidget>
#include <QTabWidget>
#include <QToolBox>
#include <QHeaderView>
#include "../task/Task.hpp"
#include "../task_manager/LinkList.hpp"

#define MAX_LISTS 100

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {

        setupMenuBar();
        
        // 设置主要区域
        QWidget *centralWidget = new QWidget(this);
        this->setCentralWidget(centralWidget);

        // 设置分割窗口
        QSplitter *splitter = new QSplitter(Qt::Horizontal, centralWidget);
        setupLeftPanel(splitter);
        setupMiddlePanel(splitter);
        setupRightPanel(splitter);

        listList = findChild<QListWidget *>("listList");  
        taskTable = findChild<QTableWidget *>("taskTable");

        QList<int> sizes;
        sizes << 2 * 100 << 8 * 100 << 3 * 100;  // 2:8:3 比例
        splitter->setSizes(sizes);

        QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
        mainLayout->addWidget(splitter);

        this->setWindowTitle("任务管理系统");

        this->showMaximized();

    }

    ~MainWindow() {}

public slots:
    void onAddListClicked();

    void onDeleteListClicked();

    void onAddTaskClicked();

    void onDeleteTaskClicked();

    void addTaskToTable(Task &Task);

    void updateTaskDisplay();


private:
    struct List {
        QString name;
        QListWidget *list;
        LinkList linklist;
    }Lists[MAX_LISTS];

    QListWidget *listList;
    QListWidgetItem *currentListItem;
    List *currentList;
    QTableWidget *taskTable;

    // ------------大体UI-------------//

    void setupMenuBar();

    void setupLeftPanel(QSplitter *splitter);

    void setupMiddlePanel(QSplitter *splitter);

    void setupRightPanel(QSplitter *splitter);

    QToolBox* createToolbox(); 

    QTabWidget* createTabWidget();

    List* getCurrentList();

    // ---------左侧区域------------//

    void setupListList(QListWidget *listList);

    // ---------中间区域------------//

    void setupTaskTable(QTableWidget *taskTable);
    
    void initExampleTasks();
    
};

#endif