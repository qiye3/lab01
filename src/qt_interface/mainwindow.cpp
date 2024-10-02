#include "mainwindow.hpp"
#include <QVBoxLayout>
#include <QDateEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QDateTime>
#include <QInputDialog>

// -----------工具函数------------//




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



// ------------左侧区域-------------//

// 设置左侧区域
void MainWindow::setupLeftPanel(QSplitter *splitter) {
    QWidget *leftPanel = new QWidget;
    QVBoxLayout *leftLayout = new QVBoxLayout(leftPanel);
    
    leftGroupWidget = new QListWidget;
    leftGroupWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    setUpLeftListGroup(leftGroupWidget);

    // 添加分割线
    QFrame *line1 = new QFrame;
    line1->setFrameShape(QFrame::HLine);
    line1->setFrameShadow(QFrame::Sunken);

    // 左侧按钮栏
    QHBoxLayout *leftButtonLayout = new QHBoxLayout;
    
    QPushButton *newListButton = new QPushButton("+");
    connect(newListButton, &QPushButton::clicked, this, [=](){onAddListClicked(leftGroupWidget);});

    QPushButton *deleteListButton = new QPushButton("x");
    connect(deleteListButton, &QPushButton::clicked, this, [=](){onDeleteListClicked(leftGroupWidget);});
    
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
    leftLayout->addWidget(leftGroupWidget);

    splitter->addWidget(leftPanel);

}

// 初始化左侧任务列表
void MainWindow::setUpLeftListGroup(QListWidget *leftListGroup){
    int i = 0;
    while(i < LeftGroup.Length()){
        leftListGroup->addItem(QString::fromStdString(LeftGroup.get_i_name(i)));
        i++;
    }
}

// 添加列表按钮
void MainWindow::onAddListClicked(QListWidget *ListWidget){
    // 弹出对话框
    bool ok;
    QString text = QInputDialog::getText(this, tr("新建列表"),
                                         tr("列表名称:"), QLineEdit::Normal,
                                         tr("新列表"), &ok);

                                        
    if (ok && !text.isEmpty()) {
        LeftGroup.append_list(ListGroup::SEQLIST, text.toStdString());
        ListWidget->addItem(text);
    }
}

// 删除列表按钮
void MainWindow::onDeleteListClicked(QListWidget *ListWidget){
    int currentIndex = ListWidget->currentRow();
    if (currentIndex >= 0) {
        LeftGroup.remove_list(currentIndex);
        ListWidget->takeItem(currentIndex);
    }
}

// ------------中间区域-------------//

// 设置中间区域
void MainWindow::setupMiddlePanel(QSplitter *splitter) {
    // 中间任务显示
    QWidget *middlePanel = new QWidget;
    QVBoxLayout *middleLayout = new QVBoxLayout(middlePanel);
    QScrollArea *taskScrollArea = new QScrollArea;


    taskTableWidget = new QTableWidget;
    taskScrollArea->setWidget(taskTableWidget);
    taskScrollArea->setWidgetResizable(true);
    taskTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    setupTaskTable(taskTableWidget);

    // 分割线 - 直接放在布局上方
    QFrame *line2 = new QFrame;
    line2->setFrameShape(QFrame::HLine);
    line2->setFrameShadow(QFrame::Sunken);

    // 中间按钮栏
    QHBoxLayout *middleButtonLayout = new QHBoxLayout;
    
    QPushButton *addTaskButton = new QPushButton("添加任务");
    connect(addTaskButton, &QPushButton::clicked, this, [=](){onAddTaskClicked(taskTableWidget, leftGroupWidget);});

    QPushButton *deleteTaskButton = new QPushButton("删除任务");
    connect(deleteTaskButton, &QPushButton::clicked, this, [=](){onDeleteTaskClicked(taskTableWidget, leftGroupWidget);});

    
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
}


// 初始化表格布局
void MainWindow::setupTaskTable(QTableWidget *taskTable){
    taskTable->setColumnCount(6);

    QStringList headers = QStringList() << "任务名称" << "任务描述" << "优先级" << "状态" << "截止日期" << "创建日期";

    taskTable->setHorizontalHeaderLabels(headers);

    // 设置列宽
    taskTable->setColumnWidth(0, 100);  // 名称列
    taskTable->setColumnWidth(1, 200);  // 描述列
    taskTable->setColumnWidth(2, 50);   // 优先级列
    taskTable->setColumnWidth(3, 80);   // 状态列
    taskTable->setColumnWidth(4, 120);  // 截止日期列
    taskTable->setColumnWidth(5, 120);  // 创建时间列

    taskTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    taskTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    taskTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    taskTable->setShowGrid(true);
    taskTable->verticalHeader()->setVisible(false);
    taskTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    taskTable->horizontalHeader()->setStretchLastSection(true);

    // 自定义表头布局
    QHeaderView *header = taskTable->horizontalHeader();
    header->setSectionsClickable(true);  // 使表头项可以点击

    // 初始化所有列的排序状态为升序
    for (int i = 0; i < taskTable->columnCount(); ++i) {
        columnSortOrder[i] = true;
    }

    connect(header, &QHeaderView::sectionClicked, this, &MainWindow::onHeaderClicked);

}


// 随列表选择更新表格显示
void MainWindow::updateTaskDisplay(QTableWidget *taskTable, QListWidget *ListWidget){
    int current_Index = ListWidget->currentRow();
    if(current_Index < 0) return;

    TaskList *currentList = LeftGroup.get_list(current_Index);

    taskTableWidget->clearContents();
    taskTableWidget->setRowCount(0);

    if(currentList->Length() == 0){
        setupTaskTable(taskTable);
        return;
    }

    for(int i = 1; i <= currentList->Length(); i++){
        addTaskToTable(currentList->get_task(i), taskTable);
    }
}

// 向表格中添加显示任务
void MainWindow::addTaskToTable(Task task, QTableWidget *taskTable){
            
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

// 添加任务按钮 
void MainWindow::onAddTaskClicked(QTableWidget *taskTable, QListWidget *ListWidget) {
    int current_Index = ListWidget->currentRow();
    if(current_Index < 0) return;

    TaskList *currentList = LeftGroup.get_list(current_Index);

    // 弹出对话框
    bool ok;
    QString name = QInputDialog::getText(this, tr("新建任务"),
                                         tr("任务名称:"), QLineEdit::Normal,
                                         tr("新任务"), &ok);
    if (!ok || name.isEmpty()) {
        return;
    }

    QString description = QInputDialog::getText(this, tr("新建任务"),
                                         tr("任务描述:"), QLineEdit::Normal,
                                         tr("任务描述"), &ok);
    if (!ok || description.isEmpty()) {
        return;
    }

    int priority = QInputDialog::getInt(this, tr("新建任务"),
                                         tr("任务优先级:"), 1, 1, 5, 1, &ok);
    if (!ok) {
        return;
    }

    QString deadline = getDeadlineInput();

    Task newTask(name.toStdString(), description.toStdString(), priority, deadline.toStdString());
    currentList->append(newTask);
    addTaskToTable(newTask, taskTable);
}


// 删除任务按钮
void MainWindow::onDeleteTaskClicked(QTableWidget *taskTable, QListWidget *ListWidget){
    int current_Index = ListWidget->currentRow();
    if(current_Index < 0) return;

    TaskList *currentList = LeftGroup.get_list(current_Index);

    Task t;

    int currentRow = taskTable->currentRow();
    if (currentRow >= 0 && currentRow < currentList->Length()) {
        currentList->remove(currentRow + 1, t);
        taskTable->removeRow(currentRow);
    }
}


// 当List被点击的时候更新显示
void MainWindow::onListClicked(QListWidgetItem *item){
    int current_Index = leftGroupWidget->currentRow();
    if (current_Index >= 0) {
        updateTaskDisplay(taskTableWidget, leftGroupWidget);
    }
}


// 当点击表头时排序
void MainWindow::onHeaderClicked(int column){

    int current_Index = leftGroupWidget->currentRow();
    if(current_Index < 0) return;

    TaskList *currentList = LeftGroup.get_list(current_Index);

    currentList->sort(column, columnSortOrder[column]);

    updateTaskDisplay(taskTableWidget, leftGroupWidget);

    columnSortOrder[column] = !columnSortOrder[column];
}

// 处理截止日期输入
QString MainWindow::getDeadlineInput(){
    QDialog dialog(this);
    dialog.setWindowTitle(tr("新建任务"));

    // 创建日期输入框
    QDateEdit *dateEdit = new QDateEdit(&dialog);
    dateEdit->setCalendarPopup(true);  // 允许使用日历弹出窗口
    dateEdit->setDisplayFormat("yyyy-MM-dd");  // 设置显示格式
    dateEdit->setDate(QDate::currentDate());  // 默认日期为当前日期

    // 创建确认和取消按钮
    QPushButton *okButton = new QPushButton(tr("确认"), &dialog);
    QPushButton *cancelButton = new QPushButton(tr("取消"), &dialog);

    // 设置布局
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(new QLabel(tr("任务截止日期 (格式: YYYY-MM-DD):"), &dialog));
    layout->addWidget(dateEdit);
    layout->addWidget(okButton);
    layout->addWidget(cancelButton);
    dialog.setLayout(layout);

    // 连接按钮信号
    connect(okButton, &QPushButton::clicked, &dialog, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);

    // 显示对话框
    if (dialog.exec() == QDialog::Accepted) {
        return dateEdit->date().toString("yyyy-MM-dd");  // 返回用户选择的日期
    }

    return QString();  // 返回空字符串表示取消输入
}


// -----------右侧区域-------------//

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

    // 创建第一个页面 - 任务详情
    detailsTool = new QWidget;
    setupDetailsTool(detailsTool);
    toolbox->addItem(detailsTool, "任务详情");
    connect(taskTableWidget, &QTableWidget::itemSelectionChanged, this, &MainWindow::onTaskSelected);


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


// 设置任务详情工具
void MainWindow::setupDetailsTool(QWidget *parent) {

    QVBoxLayout *layout = new QVBoxLayout(parent);

    // 创建任务详情标签
    nameLabel = new QLabel;
    descriptionLabel = new QLabel;
    priorityLabel = new QLabel;
    statusLabel = new QLabel;
    deadlineLabel = new QLabel;
    createTimeLabel = new QLabel;

    layout->addWidget(nameLabel);
    layout->addWidget(descriptionLabel);
    layout->addWidget(priorityLabel);
    layout->addWidget(statusLabel);
    layout->addWidget(deadlineLabel);
    layout->addWidget(createTimeLabel);
    
    // 获取当前选中的任务
    int current_Index = leftGroupWidget->currentRow();
    qDebug() << "Current row in leftGroupWidget:" << current_Index;

    if (current_Index < 0){
        return;
    }

    TaskList *currentList = LeftGroup.get_list(current_Index);
    Task t;

    int currentRow = taskTableWidget->currentRow();
    qDebug() << "Current row in taskTableWidget:" << currentRow;

    if (currentRow >= 0 && currentRow < currentList->Length()) {
        t = currentList->get_task(currentRow + 1);
    } 
    else {
        return;
    }
}


// 选择任务时调用更新函数
void MainWindow::onTaskSelected() {
    int current_Index = leftGroupWidget->currentRow();
    if (current_Index < 0) return;

    TaskList *currentList = LeftGroup.get_list(current_Index);
    int currentRow = taskTableWidget->currentRow();
    if (currentRow < 0 || currentRow >= currentList->Length()) return;

    Task t = currentList->get_task(currentRow + 1);
    updateTaskDetails(t);
}

// 更新任务详情
void MainWindow::updateTaskDetails(Task t) {
    nameLabel->setText("任务名称: " + QString::fromStdString(t.get_name()));
    descriptionLabel->setText("任务描述: " + QString::fromStdString(t.get_description()));
    priorityLabel->setText("任务优先级: " + QString::number(t.get_priority()));
    statusLabel->setText("任务状态: " + QString(t.get_status() ? "已完成" : "未完成"));
    deadlineLabel->setText("任务截止日期: " + QString::fromStdString(t.get_deadline()));
    createTimeLabel->setText("任务创建日期: " + QString::fromStdString(t.get_create_time()));
}

