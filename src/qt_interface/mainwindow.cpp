#include "mainwindow.hpp"
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QDateTime>

// ------------大体UI-------------//

// 设置菜单栏
void MainWindow::setupMenuBar() {
    QMenuBar *menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    // 创建菜单
    QMenu *fileMenu = new QMenu("文件", this);
    QMenu *editMenu = new QMenu("编辑", this);
    QMenu *viewMenu = new QMenu("视图", this);
    QMenu *toolsMenu = new QMenu("工具", this);
    QMenu *helpMenu = new QMenu("帮助", this);

    // 添加菜单到菜单栏
    menuBar->addMenu(fileMenu);
    menuBar->addMenu(editMenu);
    menuBar->addMenu(viewMenu);
    menuBar->addMenu(toolsMenu);
    menuBar->addMenu(helpMenu);

    // 添加一些动作（Action）到菜单中
    QAction *newFileAction = new QAction("新建", this);
    QAction *openFileAction = new QAction("打开", this);
    QAction *exitAction = new QAction("退出", this);
    fileMenu->addAction(newFileAction);
    fileMenu->addAction(openFileAction);
    fileMenu->addSeparator();  // 添加分隔符
    fileMenu->addAction(exitAction);

    // 退出动作绑定关闭事件
    connect(exitAction, &QAction::triggered, this, &QMainWindow::close);
}

// 设置左侧区域
void MainWindow::setupLeftPanel(QSplitter *splitter) {
    QWidget *leftPanel = new QWidget;
    QVBoxLayout *leftLayout = new QVBoxLayout(leftPanel);
    
    QListWidget *listList = new QListWidget;
    connect(listList, &QListWidget::itemSelectionChanged, this, &MainWindow::updateTaskDisplay);


    // 添加分割线
    QFrame *line1 = new QFrame;
    line1->setFrameShape(QFrame::HLine);
    line1->setFrameShadow(QFrame::Sunken);

    // 左侧按钮栏
    QHBoxLayout *leftButtonLayout = new QHBoxLayout;
    
    QPushButton *newListButton = new QPushButton("+");
    connect(newListButton, &QPushButton::clicked, this, &MainWindow::onAddListClicked);

    QPushButton *deleteListButton = new QPushButton("x");
    connect(deleteListButton, &QPushButton::clicked, this, &MainWindow::onDeleteListClicked);
    
    QPushButton *toolboxButton = new QPushButton("...");
        
    // 设置按钮为正方形
    newListButton->setFixedSize(30, 30);
    deleteListButton->setFixedSize(30, 30);
    toolboxButton->setFixedSize(30, 30);

    leftButtonLayout->addWidget(newListButton);
    leftButtonLayout->addWidget(deleteListButton);
    leftButtonLayout->addStretch();  // 空白部分
    leftButtonLayout->addWidget(toolboxButton);

    // 将分割线和按钮栏添加到布局
    leftLayout->addWidget(line1);  // 分割线在按钮栏上方
    leftLayout->addLayout(leftButtonLayout);
    leftLayout->addWidget(listList);

    splitter->addWidget(leftPanel);

    setupListList(listList);
}

// 设置中间区域
void MainWindow::setupMiddlePanel(QSplitter *splitter) {
    // 中间任务显示
    QWidget *middlePanel = new QWidget;
    QVBoxLayout *middleLayout = new QVBoxLayout(middlePanel);
    QScrollArea *taskScrollArea = new QScrollArea;
    QTableWidget *taskTable = new QTableWidget;
    taskScrollArea->setWidget(taskTable);
    taskScrollArea->setWidgetResizable(true);

    // 分割线 - 直接放在布局上方
    QFrame *line2 = new QFrame;
    line2->setFrameShape(QFrame::HLine);
    line2->setFrameShadow(QFrame::Sunken);

    // 中间按钮栏
    QHBoxLayout *middleButtonLayout = new QHBoxLayout;
    
    QPushButton *addTaskButton = new QPushButton("添加任务");
    connect(addTaskButton, &QPushButton::clicked, this, &MainWindow::onAddTaskClicked);

    QPushButton *deleteTaskButton = new QPushButton("删除任务");
    connect(deleteTaskButton, &QPushButton::clicked, this, &MainWindow::onDeleteTaskClicked);

    
    addTaskButton->setFixedSize(30, 30);
    deleteTaskButton->setFixedSize(30, 30);

    middleButtonLayout->addWidget(addTaskButton);
    middleButtonLayout->addWidget(deleteTaskButton);
    middleButtonLayout->addStretch();  // 空白部分

    // 将分割线和按钮栏添加到布局
    middleLayout->addWidget(line2);  // 分割线在按钮栏上方
    middleLayout->addLayout(middleButtonLayout);
    middleLayout->addWidget(taskScrollArea);

    splitter->addWidget(middlePanel);

    setupTaskTable(taskTable);
}

// 设置右侧区域
void MainWindow::setupRightPanel(QSplitter *splitter) {
    QWidget *rightPanel = new QWidget;
    QVBoxLayout *rightLayout = new QVBoxLayout(rightPanel);

    QToolBox *toolbox = createToolbox();
    rightLayout->addWidget(toolbox);

    QTabWidget *tabWidget = createTabWidget();
    rightLayout->addWidget(tabWidget);

    splitter->addWidget(rightPanel);
}

// 添加工具箱布局
QToolBox* MainWindow::createToolbox()
{
    // 创建 QToolBox 对象
    QToolBox *toolbox = new QToolBox;

    // 创建第一个页面 - 任务详情/提醒
    QWidget *detailsTool = new QWidget;
    QVBoxLayout *detailsLayout = new QVBoxLayout(detailsTool);
    QLabel *detailsLabel = new QLabel("任务详情/提醒内容");
    detailsLayout->addWidget(detailsLabel);
    toolbox->addItem(detailsTool, "任务详情/提醒");

    // 创建第二个页面 - 任务提醒
    QWidget *remindersTool = new QWidget;
    QVBoxLayout *remindersLayout = new QVBoxLayout(remindersTool);
    QLabel *remindersLabel = new QLabel("任务提醒内容");
    remindersLayout->addWidget(remindersLabel);
    toolbox->addItem(remindersTool, "任务提醒");

    // 你可以继续添加更多的页面

    return toolbox;
}

// 添加标签页布局
QTabWidget* MainWindow::createTabWidget(){
    // 创建 QTabWidget 对象
    QTabWidget *tabWidget = new QTabWidget;

    // 创建第一个标签页 - 扩展工具
    QWidget *extensionsTab = new QWidget;
    QVBoxLayout *extensionsLayout = new QVBoxLayout(extensionsTab);
    QLabel *extensionsLabel = new QLabel("扩展工具内容");
    extensionsLayout->addWidget(extensionsLabel);
    tabWidget->addTab(extensionsTab, "扩展工具");

    // 创建第二个标签页 - 更多工具
    QWidget *moreToolsTab = new QWidget;
    QVBoxLayout *moreToolsLayout = new QVBoxLayout(moreToolsTab);
    QLabel *moreToolsLabel = new QLabel("更多工具内容");
    moreToolsLayout->addWidget(moreToolsLabel);
    tabWidget->addTab(moreToolsTab, "更多工具");

    // 你可以继续添加更多的标签页

    return tabWidget;
}


// ------------左侧区域-------------//

// 初始化左侧任务列表
void MainWindow::setupListList(QListWidget *listList){
    listList->addItem("默认列表");
    listList->addItem("工作");
    listList->addItem("学习");
    listList->addItem("生活");
    listList->addItem("其他");
}

// 添加列表按钮
void MainWindow::onAddListClicked(){
    QListWidget *listList = findChild<QListWidget *>("listList");

    // 添加新列表的名称
    QString newListName = "新列表";
    listList->addItem(newListName);

    // 找到空闲的 Lists 结构体索引
    for (int i = 0; i < MAX_LISTS; ++i) {
        if (Lists[i].name.isEmpty()) {
            // 存储列表名和对应的 LinkList
            Lists[i].name = newListName;
            Lists[i].list = listList;  // 关联到当前的 QListWidget
            Lists[i].linklist = LinkList(); // 初始化新的 LinkList
            break;
        }
    }
}

// 删除列表按钮
void MainWindow::onDeleteListClicked(){
    QListWidget *listList = findChild<QListWidget *>("listList");
    QListWidgetItem *item = listList->currentItem();
    
    if (item) {
        QString listName = item->text();

        // 查找对应的 LinkList 并清理
        for (int i = 0; i < MAX_LISTS; ++i) {
            if (Lists[i].name == listName) {
                // 清除这个 List 的信息
                Lists[i].name.clear();
                Lists[i].list = nullptr;  // 可以选择不再关联
                Lists[i].linklist.~LinkList();  // 释放 LinkList
                break;
            }
        }

        // 删除 QListWidgetItem
        delete item;
    }
}

// 获取当前选中的列表
MainWindow::List* MainWindow::getCurrentList(){
    int currentIndex = listList->currentRow();

    if (currentIndex >= 0 && currentIndex < MAX_LISTS) {
        return &Lists[currentIndex];
    }
    return nullptr;

}


// ------------中间区域-------------//

// 初始化表格布局
void MainWindow::setupTaskTable(QTableWidget *taskTable){
    taskTable->setColumnCount(6);

    taskTable->setHorizontalHeaderLabels(QStringList() << "任务名称" << "任务描述" << "优先级" << "状态" << "截止日期" << "创建日期");

    // 设置列宽
    taskTable->setColumnWidth(0, 100);  // 名称列
    taskTable->setColumnWidth(1, 200);  // 描述列
    taskTable->setColumnWidth(2, 50);   // 优先级列
    taskTable->setColumnWidth(3, 80);   // 状态列
    taskTable->setColumnWidth(4, 120);  // 截止日期列
    taskTable->setColumnWidth(5, 120);  // 创建时间列

    taskTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    taskTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    taskTable->setSelectionMode(QAbstractItemView::SingleSelection);

    taskTable->setShowGrid(true);
    taskTable->verticalHeader()->setVisible(false);
    taskTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    taskTable->horizontalHeader()->setStretchLastSection(true);
}

// 随列表选择更新表格显示
void MainWindow::updateTaskDisplay(){

    currentListItem = listList->currentItem();

    currentList = getCurrentList();

    // 清空表格
    taskTable->setRowCount(0);

    if (!currentListItem) {
        return; // 如果没有选中任何列表，直接返回
    }

    for(int i = 1; i <= currentList->linklist.Length(); i++){
        Task task = currentList->linklist.get_task(i);
        addTaskToTable(task);
    }
}

// 添加任务按钮 
void MainWindow::onAddTaskClicked() {
    currentListItem = listList->currentItem();
    
    if (!currentListItem) {
        QMessageBox::warning(this, "警告", "请先选择一个列表!");
        return;
    }

    // 从用户那里获取任务详情（可以用对话框或输入窗口）
    Task newTask;
    newTask.change_task("任务名称", "任务描述", 1, "2024-10-01");

    // 获取当前选中的列表名
    QString listName = currentListItem->text();
    
}

// 向表格中添加任务
void MainWindow::addTaskToTable(Task &task){

    currentList->linklist.append(task);
            
    // 将任务添加到表格中
    int newRow = taskTable->rowCount();

    taskTable->insertRow(newRow);
    
    taskTable->setItem(newRow, 0, new QTableWidgetItem(QString::fromStdString(task.get_name()))); 
    
    taskTable->setItem(newRow, 1, new QTableWidgetItem(QString::fromStdString(task.get_description()))); 
    
    taskTable->setItem(newRow, 2, new QTableWidgetItem(QString::number(task.get_priority()))); 
    
    taskTable->setItem(newRow, 3, new QTableWidgetItem(task.get_status() ? "已完成" : "未完成"));
    
    taskTable->setItem(newRow, 4, new QTableWidgetItem(QString::fromStdString(task.get_deadline())));
    
    taskTable->setItem(newRow, 5, new QTableWidgetItem(QString::fromStdString(task.get_create_time())));    

}


// 删除任务按钮
void MainWindow::onDeleteTaskClicked(){

    // 获取左侧的 QListWidget
    QListWidget *listList = findChild<QListWidget *>("listList");
    
    // 获取当前选中的列表项
    QListWidgetItem *currentListItem = listList->currentItem();

    // 获取中间的 QTableWidget
    QTableWidget *taskTable = findChild<QTableWidget *>("taskTable");

    int currentRow = taskTable->currentRow();
    if (currentRow >= 0 && currentListItem) {
        // 获取当前选中的列表名
        QString listName = currentListItem->text();
        
        // 从表格中获取任务名称
        QString taskName = taskTable->item(currentRow, 0)->text();

        // 查找对应的 LinkList
        for (int i = 0; i < MAX_LISTS; ++i) {
            if (Lists[i].name == listName) {
                // 从 LinkList 中删除任务
                Lists[i].linklist.remove_by_name(taskName.toStdString()); 

                // 从表格中删除任务
                taskTable->removeRow(currentRow);
                break; // 找到并删除后退出循环
            }
        }
    }
}


// 初始化示例任务
void MainWindow::initExampleTasks(){
// 示例任务数据
    struct ExampleTask {
        QString name;
        QString description;
        int priority;
        QString status;
        QString deadline;
        QString createTime;
    };

    QList<ExampleTask> exampleTasks = {
        {"任务1", "描述1", 1, "未完成", "2024-10-05", "2024-09-30"},
        {"任务2", "描述2", 2, "完成", "2024-10-10", "2024-09-29"},
        {"任务3", "描述3", 3, "未完成", "2024-10-15", "2024-09-28"},
        {"任务4", "描述4", 1, "未完成", "2024-10-20", "2024-09-27"},
        {"任务5", "描述5", 2, "未完成", "2024-10-25", "2024-09-26"}
    };

    // 遍历示例任务，添加到 LinkList 和表格
    for (const ExampleTask &task : exampleTasks) {
        // 创建 Task 对象
        Task newTask;
        
        newTask.change_task(task.name.toStdString(), task.description.toStdString(), task.priority, task.deadline.toStdString());

        // 将任务添加到表格
        addTaskToTable(newTask);
    }
}