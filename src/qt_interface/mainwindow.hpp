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
#include <qcombobox.h>
#include <qdatetimeedit.h>
#include <qspinbox.h>
#include "../task/Task.hpp"
#include "../task_manager/LinkList.hpp"
#include "../task_manager/TaskList.hpp"
#include "../list_group/ListGroup.hpp"
#include "../utils/Utils.hpp"
// #include "TaskModel.hpp"

using namespace std;

#define MAX_LISTS 100

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {

        LeftGroup.initialize_example_tasks();

        setupMenuBar();
        
        // 设置主要区域
        QWidget *centralWidget = new QWidget(this);
        this->setCentralWidget(centralWidget);

        // 设置分割窗口
        QSplitter *splitter = new QSplitter(Qt::Horizontal, centralWidget);
        setupLeftPanel(splitter);
        setupMiddlePanel(splitter);
        setupRightPanel(splitter);


        QList<int> sizes;
        sizes << 2 * 100 << 8 * 100 << 3 * 100;  // 2:8:3 比例
        splitter->setSizes(sizes);

        QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
        mainLayout->addWidget(splitter);

        this->setWindowTitle("任务管理系统");

        this->showMaximized();

        connect(leftGroupWidget, &QListWidget::itemClicked, this, &MainWindow::onListClicked);
        

    };

    ~MainWindow() {}

public slots:
    void onAddListClicked(QListWidget *ListWidget);

    void onDeleteListClicked(QListWidget *ListWidget);

    void onAddTaskClicked(QTableWidget *taskTable,QListWidget *ListWidget);

    void onDeleteTaskClicked(QTableWidget *taskTable, QListWidget *ListWidget);

    void addTaskToTable(Task Task, QTableWidget *taskTable);

    void updateTaskDisplay(QTableWidget *taskTable, QListWidget *ListWidget);

    void onListClicked(QListWidgetItem *item);

    void onHeaderClicked(int column);

    void updateTaskDetails(Task t);

    void onTaskSelected();

    void onTaskChanged();

    void onSearchClicked();

    void onChangeNameClicked(QListWidget *ListWidget);

    void refreshReminderTable();

    void changeTaskStatus();

private:

    // ------------内部指针----------//

    // TaskModel *taskModel;
    ListGroup LeftGroup;
    QListWidget *leftGroupWidget;
    QTableWidget *taskTableWidget;

    QWidget *detailsTool;
    QWidget *reminderTab;
    QTableWidget *reminderTable;

    QMap<int, bool> columnSortOrder; // 用于记录每一列的排序顺序

    // 搜索框
    QLineEdit *searchEdit;

    // 搜索结果
    vector<int> searchResult; 

    // 是否是搜索状态
    bool isSearching;

    // 详情页标签
    QLineEdit *nameEdit, *descriptionEdit;
    QDateEdit *deadlineEdit;
    QSpinBox *prioritySpinBox;
    QComboBox *statusComboBox;
    QLabel *createTimeLabel;

    // ------------大体UI-------------//

    void setupMenuBar();

    void setupLeftPanel(QSplitter *splitter);

    void setupMiddlePanel(QSplitter *splitter);

    void setupRightPanel(QSplitter *splitter);

    QToolBox* createToolbox(); 

    QTabWidget* createTabWidget();

    // ----------菜单区域------------//

    void exportToTxtSingle();

    void exportToCsvSingle();

    void exportToTxtAll();

    void exportToCsvAll();

    void importFromTxt();

    void importFromCsv();

    // ----------左侧区域------------//
    
    void setUpLeftListGroup(QListWidget *parent);

    QString getDeadlineInput();


    // -----------中间区域-----------//

    void setupTaskTable(QTableWidget *taskTable);

    void searchTask(QString keyword, QTableWidget *taskTable);

    void setTaskTableColor(bool status, int row);

    // -----------右侧区域-----------//

    void setupDetailsTool(QWidget *parent);
    
    void setupReminderTab(QWidget *parent);

    void sortReminderTable();
};


#endif // MAIN_WINDOW_HPP
