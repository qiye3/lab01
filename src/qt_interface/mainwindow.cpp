#include "mainwindow.hpp"
#include <QVBoxLayout>
#include <QFile>
#include <QDateEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QDateTime>
#include <QInputDialog>
#include <QSpinBox>
#include <QComboBox>
#include <QFileDialog>
#include <QTextStream>
#include <QCheckBox>

// -----------工具函数------------//




// ------------菜单栏-------------//

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


    // 创建导入子菜单
    QMenu *importMenu = new QMenu("导入", this);
    QAction *importTxtAction = new QAction("从TXT导入", this);
    connect(importTxtAction, &QAction::triggered, this, &MainWindow::importFromTxt);
    connect(importTxtAction, &QAction::triggered, this, &MainWindow::refreshReminderTable);
    QAction *importCsvAction = new QAction("从CSV导入", this);
    connect(importCsvAction, &QAction::triggered, this, &MainWindow::importFromCsv);
    connect(importCsvAction, &QAction::triggered, this, &MainWindow::refreshReminderTable);
    importMenu->addAction(importTxtAction);
    importMenu->addAction(importCsvAction);
    fileMenu->addMenu(importMenu);

    // 导出当前任务列表
    QMenu *exportMenu = new QMenu("导出当前任务列表", this);
    QAction *exportTxtAction = new QAction("导出为TXT", this);
    connect(exportTxtAction, &QAction::triggered, this, &MainWindow::exportToTxtSingle);
    QAction *exportCsvAction = new QAction("导出为CSV", this);
    connect(exportCsvAction, &QAction::triggered, this, &MainWindow::exportToCsvSingle);
    exportMenu->addAction(exportTxtAction);
    exportMenu->addAction(exportCsvAction);
    fileMenu->addMenu(exportMenu);

    // 导出所有任务列表
    QMenu *exportAllMenu = new QMenu("导出所有任务列表", this);
    QAction *exportAllTxtAction = new QAction("导出为TXT", this);
    connect(exportAllTxtAction, &QAction::triggered, this, &MainWindow::exportToTxtAll);
    QAction *exportAllCsvAction = new QAction("导出为CSV", this);
    connect(exportAllCsvAction, &QAction::triggered, this, &MainWindow::exportToCsvAll);
    exportAllMenu->addAction(exportAllTxtAction);
    exportAllMenu->addAction(exportAllCsvAction);
    fileMenu->addMenu(exportAllMenu);

    // 添加退出动作
    QAction *exitAction = new QAction("退出", this);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);
    connect(exitAction, &QAction::triggered, this, &QMainWindow::close);
}

// 从TXT导入
void MainWindow::importFromTxt() {

    qDebug() << "Attempting to open directory dialog...";

    // 打开文件选择对话框
    QString filePath = QFileDialog::getOpenFileName(this, tr("选择文件"), QString(), tr("文本文件 (*.txt)"));

    if(filePath.isEmpty()){
        return;
    }

    qDebug() << "Selected file path: " << filePath;

    // 使用 QFileInfo 提取文件名
    QFileInfo fileInfo(filePath);
    QString fileName = fileInfo.fileName();
    filePath = fileInfo.path();

    qDebug() << "Selected file name: " << fileName;
    qDebug() << "Selected file path: " << filePath;
    
    LeftGroup.read_from_txt(fileName.toStdString(), filePath.toStdString() + "/");

    setUpLeftListGroup(leftGroupWidget);
    
    if(!filePath.isEmpty()){
        QMessageBox::information(this, "成功", "文件导入成功。");
    }
}

// 从CSV导入
void MainWindow::importFromCsv() {
    // 打开文件选择对话框
    QString filePath = QFileDialog::getOpenFileName(this, tr("选择文件"), QString(), tr("CSV 文件 (*.csv)"));

    // 检查用户是否选择了文件
    if (filePath.isEmpty()) {
        return;
    }

    // 使用 QFileInfo 提取文件名
    QFileInfo fileInfo(filePath);
    QString fileName = fileInfo.fileName();
    filePath = fileInfo.path();

    qDebug() << "Selected file name: " << fileName;
    qDebug() << "Selected file path: " << filePath;
    
    LeftGroup.read_from_csv(fileName.toStdString(), filePath.toStdString() + "/");

    setUpLeftListGroup(leftGroupWidget);
    
    if(!filePath.isEmpty()){
        QMessageBox::information(this, "成功", "文件导入成功。");
    }
}

// 导出当前任务列表为TXT
void MainWindow::exportToTxtSingle() {
    int current_Index = leftGroupWidget->currentRow();
    if(current_Index < 0) return;

    TaskList *currentList = LeftGroup.get_list(current_Index);

    // 打开文件夹选择对话框
    QString filePath = QFileDialog::getExistingDirectory(this, tr("选择保存文件夹"), QString());

    // 检查用户是否选择了文件夹
    if (filePath.isEmpty()) {
        return;
    }

    string fileName = LeftGroup.get_i_name(current_Index);
    
    currentList->write_to_txt(fileName, filePath.toStdString() + "/");
    
    QMessageBox::information(this, "成功", "文件导出成功。");
}

// 导出当前任务列表为CSV
void MainWindow::exportToCsvSingle() {
    int current_Index = leftGroupWidget->currentRow();
    if(current_Index < 0) return;

    TaskList *currentList = LeftGroup.get_list(current_Index);

    // 打开文件夹选择对话框
    QString filePath = QFileDialog::getExistingDirectory(this, tr("选择保存文件夹"), QString());

    // 检查用户是否选择了文件夹
    if (filePath.isEmpty()) {
        return;  // 如果用户未选择文件夹，返回
    }

    string fileName = LeftGroup.get_i_name(current_Index);

    currentList->write_to_csv(fileName, filePath.toStdString() + "/");
    
    QMessageBox::information(this, "成功", "文件导出成功。");
}

// 导出所有任务列表为TXT
void MainWindow::exportToTxtAll() {
    QString filePath = QFileDialog::getExistingDirectory(this, tr("选择保存文件夹"), QString());

    if (filePath.isEmpty()) {
        return;
    }
    
    string filenames[LeftGroup.Length()];
    for(int i = 0; i < LeftGroup.Length(); i++){
        filenames[i] = LeftGroup.get_i_name(i);
    }
    
    LeftGroup.write_all_to_txt(filenames, filePath.toStdString() + "/");
    
    QMessageBox::information(this, "成功", "文件导出成功。");
}

// 导出所有任务列表为CSV
void MainWindow::exportToCsvAll() {
    QString filePath = QFileDialog::getExistingDirectory(this, tr("选择保存文件夹"), QString());

    if (filePath.isEmpty()) {
        return;
    }
    
    string filenames[LeftGroup.Length()];
    for(int i = 0; i < LeftGroup.Length(); i++){
        filenames[i] = LeftGroup.get_i_name(i);
    }
    
    LeftGroup.write_all_to_csv(filenames, filePath.toStdString() + "/");
    
    QMessageBox::information(this, "成功", "文件导出成功。");
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
    connect(deleteListButton, &QPushButton::clicked, this, &MainWindow::refreshReminderTable);

    QPushButton *changeNameButton = new QPushButton("*");
    connect(changeNameButton, &QPushButton::clicked, this, [=](){onChangeNameClicked(leftGroupWidget);});
    connect(changeNameButton, &QPushButton::clicked, this, &MainWindow::refreshReminderTable);

    
    QPushButton *toolboxButton = new QPushButton("...");

        
    // 设置按钮为正方形
    newListButton->setFixedSize(30, 30);
    deleteListButton->setFixedSize(30, 30);
    changeNameButton->setFixedSize(30, 30);
    toolboxButton->setFixedSize(30, 30);

    leftButtonLayout->addWidget(newListButton);
    leftButtonLayout->addWidget(deleteListButton);
    leftButtonLayout->addWidget(changeNameButton);
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
    // 清空列表
    leftListGroup->clear();

    int i = 0;
    while(i < LeftGroup.Length()){
        leftListGroup->addItem(QString::fromStdString(LeftGroup.get_i_name(i)));
        i++;
    }
}

// 添加列表按钮
void MainWindow::onAddListClicked(QListWidget *ListWidget){
    // 弹出对话框获取列表名称
    bool ok;
    QString listName = QInputDialog::getText(this, tr("新建列表"),
                                             tr("列表名称:"), QLineEdit::Normal,
                                             tr("新列表"), &ok);
    
    if (!ok || listName.isEmpty()) return;

    // 弹出选择列表类型的对话框
    QStringList listTypes = {"单链表", "双链表", "顺序表"};
    bool typeOk;
    QString selectedType = QInputDialog::getItem(this, tr("选择列表类型"),
                                                 tr("请选择列表类型:"), listTypes, 
                                                 0, false, &typeOk);

    if (typeOk && !selectedType.isEmpty()) {
        int listType;
        if (selectedType == "单链表") {
            listType = ListGroup::LINKLIST;
        } else if (selectedType == "双链表") {
            listType = ListGroup::DLINKLIST;
        } else {
            listType = ListGroup::SEQLIST;
        }

        // 向 LeftGroup 添加新列表
        if (LeftGroup.append_list(listType, listName.toStdString())) {
            ListWidget->addItem(listName);
        } 
        else {
            QMessageBox::warning(this, tr("错误"), tr("列表数量已达上限"));
        }
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

// 改名按钮
void MainWindow::onChangeNameClicked(QListWidget *ListWidget){
    int currentIndex = ListWidget->currentRow();
    if (currentIndex >= 0) {
        bool ok;
        QString newName = QInputDialog::getText(this, tr("重命名列表"),
                                                tr("新名称:"), QLineEdit::Normal,
                                                ListWidget->currentItem()->text(), &ok);
        if (ok && !newName.isEmpty()) {
            LeftGroup.change_name(currentIndex, newName.toStdString());
            ListWidget->currentItem()->setText(newName);
        }
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
    
    for(int i = 0; i < taskTableWidget->columnCount(); i++){
        columnSortOrder[i] = false;
    }

    // 分割线 - 直接放在布局上方
    QFrame *line2 = new QFrame;
    line2->setFrameShape(QFrame::HLine);
    line2->setFrameShadow(QFrame::Sunken);

    // 中间按钮栏
    QHBoxLayout *middleButtonLayout = new QHBoxLayout;
    
    QPushButton *addTaskButton = new QPushButton("+");
    connect(addTaskButton, &QPushButton::clicked, this, [=](){onAddTaskClicked(taskTableWidget, leftGroupWidget);});
    connect(addTaskButton, &QPushButton::clicked, this, &MainWindow::refreshReminderTable);

    QPushButton *deleteTaskButton = new QPushButton("x");
    connect(deleteTaskButton, &QPushButton::clicked, this, [=](){onDeleteTaskClicked(taskTableWidget, leftGroupWidget);});
    connect(deleteTaskButton, &QPushButton::clicked, this, &MainWindow::refreshReminderTable);


    searchEdit = new QLineEdit;
    searchEdit->setPlaceholderText("搜索");
    QPushButton *searchButton = new QPushButton("搜索");
    connect(searchButton, &QPushButton::clicked, this, &MainWindow::onSearchClicked);

    
    addTaskButton->setFixedSize(30, 30);
    deleteTaskButton->setFixedSize(30, 30);
    searchButton->setFixedSize(30, 30);

    middleButtonLayout->addWidget(addTaskButton);
    middleButtonLayout->addWidget(deleteTaskButton);
    middleButtonLayout->addStretch();  // 空白部分
    middleButtonLayout->addWidget(searchEdit);
    middleButtonLayout->addWidget(searchButton);

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

    connect(header, &QHeaderView::sectionClicked, this, &MainWindow::onHeaderClicked);

}


// 随列表选择更新表格显示
void MainWindow::updateTaskDisplay(QTableWidget *taskTable, QListWidget *ListWidget){
    isSearching = false;

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

    bool status = task.get_status();
    
    taskTable->setItem(newRow, 0, new QTableWidgetItem(QString::fromStdString(task.get_name()))); 
    
    taskTable->setItem(newRow, 1, new QTableWidgetItem(QString::fromStdString(task.get_description()))); 
    
    taskTable->setItem(newRow, 2, new QTableWidgetItem(QString::number(task.get_priority()))); 
    
    // taskTable->setItem(newRow, 3, new QTableWidgetItem(task.get_status() ? "已完成" : "未完成"));

    QCheckBox *checkBox = new QCheckBox;
    checkBox->setChecked(status);

    checkBox->setStyleSheet("QCheckBox::indicator { width: 50px; height: 50px; }");

    QWidget *checkBoxWidget = new QWidget;
    QVBoxLayout *playout = new QVBoxLayout(checkBoxWidget);
    playout->addWidget(checkBox);
    checkBoxWidget->setLayout(playout);
    checkBox->setContentsMargins(0, 0, 0, 0);
    playout->setAlignment(Qt::AlignCenter);
    taskTable->setCellWidget(newRow, 3, checkBoxWidget);

    connect(checkBox, &QCheckBox::stateChanged, this, &MainWindow::changeTaskStatus);
    connect(checkBox, &QCheckBox::stateChanged, this, &MainWindow::refreshReminderTable);

    
    taskTable->setItem(newRow, 4, new QTableWidgetItem(QString::fromStdString(task.get_deadline())));
    
    taskTable->setItem(newRow, 5, new QTableWidgetItem(QString::fromStdString(task.get_create_time())));

    setTaskTableColor(status, newRow);
}

// 设置表格颜色
void MainWindow::setTaskTableColor(bool status, int row){
    if(status){
        for(int i = 0; i < taskTableWidget->columnCount(); i++){
            if(i == 3) continue;
            taskTableWidget->item(row, i)->setBackground(QBrush(QColor(0, 255, 0, 50)));
        }
    }
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

    columnSortOrder[column] = !columnSortOrder[column];

    updateTaskDisplay(taskTableWidget, leftGroupWidget);
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


// 点击搜索按钮
void MainWindow::onSearchClicked(){
    QString keyword = searchEdit->text();
    searchTask(keyword, taskTableWidget);
}


// 在当前列表里搜索任务
void MainWindow::searchTask(QString keyword, QTableWidget *taskTable){
    searchResult.clear();

    int current_Index = leftGroupWidget->currentRow();
    if(current_Index < 0) return;

    TaskList *currentList = LeftGroup.get_list(current_Index);

    QRegularExpression datePattern("^\\d{4}-\\d{2}-\\d{2}$");
    QRegularExpressionMatch match = datePattern.match(keyword);
    bool isDate = match.hasMatch();

    taskTable->clearContents();
    taskTable->setRowCount(0);

    setupTaskTable(taskTable);

    isSearching = true;

    for(int i = 1; i <= currentList->Length(); i++){
        Task t = currentList->get_task(i);
        if(isDate){
            if(QString::fromStdString(t.get_deadline()) == keyword){
                addTaskToTable(t, taskTable);
                searchResult.push_back(i);
            }
        }
        else{
            if(t.get_name().find(keyword.toStdString()) != string::npos || t.get_description().find(keyword.toStdString()) != string::npos){
                addTaskToTable(t, taskTable);
                searchResult.push_back(i);
            }
        }
    }

    if(taskTable->rowCount() == 0){
        QMessageBox::information(this, "搜索结果", "没有找到匹配的任务");
    }
}


// 改变任务状态
void MainWindow::changeTaskStatus(){
    QCheckBox *checkBox = qobject_cast<QCheckBox *>(sender());
    if (!checkBox) return;

    // 获取复选框所在的行
    int currentRow = taskTableWidget->indexAt(checkBox->parentWidget()->pos()).row();
    if (currentRow < 0) return;

    int current_Index = leftGroupWidget->currentRow();
    if (current_Index < 0) return;

    TaskList *currentList = LeftGroup.get_list(current_Index);

    Task t;
    
    if(isSearching){
        t = currentList->get_task(searchResult[currentRow]);
    }
    else{
        t = currentList->get_task(currentRow + 1);
    }

    qDebug() << "status changed"<<checkBox->isChecked();
    t.change_status(!t.get_status());
    qDebug() << "status changed"<<t.get_status();

    Task temp;
    if(isSearching){
        currentList->remove(searchResult[currentRow], temp);
        currentList->insert(searchResult[currentRow], t);
    }
    else{
        currentList->remove(currentRow + 1, temp);
        currentList->insert(currentRow + 1, t);
    }

    updateTaskDisplay(taskTableWidget, leftGroupWidget);
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


    // 创建第二个页面 - 展示编辑
    QWidget *showTool = new QWidget;
    QVBoxLayout *showToolLayout = new QVBoxLayout(showTool);
    QLabel *showLabel = new QLabel("任务展示编辑");
    showToolLayout->addWidget(showLabel);
    toolbox->addItem(showTool, "任务展示");

    // 你可以继续添加更多的页面

    return toolbox;
}

// 设置任务详情工具
void MainWindow::setupDetailsTool(QWidget *parent) {

    QVBoxLayout *layout = new QVBoxLayout(parent);

    // 使用 QLineEdit 代替 QLabel
    nameEdit = new QLineEdit();
    descriptionEdit = new QLineEdit();
    
    prioritySpinBox = new QSpinBox();
    prioritySpinBox->setRange(1, 5);
    
    deadlineEdit = new QDateEdit();
    deadlineEdit->setDisplayFormat("yyyy-MM-dd");
    
    statusComboBox = new QComboBox();
    statusComboBox->addItem("未完成");
    statusComboBox->addItem("已完成");
    
    createTimeLabel = new QLabel();


    layout->addWidget(new QLabel("任务名称:"));
    layout->addWidget(nameEdit);
    layout->addWidget(new QLabel("任务描述:"));
    layout->addWidget(descriptionEdit);
    layout->addWidget(new QLabel("任务优先级:"));
    layout->addWidget(prioritySpinBox);
    layout->addWidget(new QLabel("任务状态:"));
    layout->addWidget(statusComboBox);
    layout->addWidget(new QLabel("任务截止日期:"));
    layout->addWidget(deadlineEdit);
    layout->addWidget(createTimeLabel);
    
    // 保存修改的按钮
    QPushButton *saveButton = new QPushButton("保存修改");
    layout->addWidget(saveButton);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::onTaskChanged);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::refreshReminderTable);
    
    // // 获取当前选中的任务
    // int current_Index = leftGroupWidget->currentRow();
    // qDebug() << "Current row in leftGroupWidget:" << current_Index;

    // if (current_Index < 0){
    //     return;
    // }

    // TaskList *currentList = LeftGroup.get_list(current_Index);
    // Task t;

    // int currentRow = taskTableWidget->currentRow();
    // qDebug() << "Current row in taskTableWidget:" << currentRow;

    // if (currentRow >= 0 && currentRow < currentList->Length()) {
    //     t = currentList->get_task(currentRow + 1);
    // } 
    // else {
    //     return;
    // }
}

// 选择任务时调用更新函数
void MainWindow::onTaskSelected() {
    int current_Index = leftGroupWidget->currentRow();
    if (current_Index < 0) return;

    TaskList *currentList = LeftGroup.get_list(current_Index);
    int currentRow = taskTableWidget->currentRow();
    if (currentRow < 0 || currentRow >= currentList->Length()) return;

    Task t;
    if(isSearching){
        t = currentList->get_task(searchResult[currentRow]);
    }
    else{
        t = currentList->get_task(currentRow + 1);
    }
    updateTaskDetails(t);
}

// 更新任务详情
void MainWindow::updateTaskDetails(Task t) {
    nameEdit->setText(QString::fromStdString(t.get_name()));
    descriptionEdit->setText(QString::fromStdString(t.get_description()));
    prioritySpinBox->setValue(t.get_priority());
    deadlineEdit->setDate(QDate::fromString(QString::fromStdString(t.get_deadline()), "yyyy-MM-dd"));
    statusComboBox->setCurrentIndex(t.get_status() ? 1 : 0);
    createTimeLabel->setText("任务创建日期: " + QString::fromStdString(t.get_create_time()));
}

// 修改任务时调用
void MainWindow::onTaskChanged(){
    int current_Index = leftGroupWidget->currentRow();
    if (current_Index < 0) return;

    TaskList *currentList = LeftGroup.get_list(current_Index);
    int currentRow = taskTableWidget->currentRow();
    if (currentRow < 0 || currentRow >= currentList->Length()) return;

    Task t;
    if(isSearching){
        t = currentList->get_task(searchResult[currentRow]);
    }
    else{
        t = currentList->get_task(currentRow + 1);
    }

    t.change_task(nameEdit->text().toStdString(), descriptionEdit->text().toStdString(), prioritySpinBox->value(), deadlineEdit->text().toStdString());
    
    t.change_status(statusComboBox->currentText() == "已完成");

    Task temp;
    if(isSearching){
        currentList->remove(searchResult[currentRow], temp);
        currentList->insert(searchResult[currentRow], t);
    }
    else{
        currentList->remove(currentRow + 1, temp);
        currentList->insert(currentRow + 1, t);
    }

    updateTaskDisplay(taskTableWidget, leftGroupWidget);
}

// 添加标签页布局
QTabWidget* MainWindow::createTabWidget(){
    // 创建 QTabWidget 对象
    QTabWidget *tabWidget = new QTabWidget;

    // 创建第一个标签页 - 提醒工具
    reminderTab = new QWidget;
    setupReminderTab(reminderTab);
    tabWidget->addTab(reminderTab, "提醒工具");
    

    // 创建第二个标签页 - 更多工具
    QWidget *moreToolsTab = new QWidget;
    QVBoxLayout *moreToolsLayout = new QVBoxLayout(moreToolsTab);
    QLabel *moreToolsLabel = new QLabel("更多工具内容");
    moreToolsLayout->addWidget(moreToolsLabel);
    tabWidget->addTab(moreToolsTab, "更多工具");

    // 你可以继续添加更多的标签页

    return tabWidget;
}

// 设置提醒工具标签页
void MainWindow::setupReminderTab(QWidget *parent) {
    QVBoxLayout *layout = new QVBoxLayout(parent);

    // 刷新按钮
    QPushButton *refreshButton = new QPushButton("刷新");
    connect(refreshButton, &QPushButton::clicked, this, &MainWindow::refreshReminderTable);
    layout->addWidget(refreshButton);

    // 提醒列表
    reminderTable = new QTableWidget;
    reminderTable->setColumnCount(3);
    QStringList headers = QStringList() << "任务名称" << "剩余天数"<<"所属列表";
    reminderTable->setHorizontalHeaderLabels(headers);
    reminderTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    reminderTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    reminderTable->setSelectionMode(QAbstractItemView::SingleSelection);

    layout->addWidget(reminderTable);

    // 设置列宽
    reminderTable->setColumnWidth(0, 200);
    reminderTable->setColumnWidth(1, 100);
    reminderTable->setColumnWidth(2, 100);

    refreshReminderTable();
}

// 刷新提醒列表
void MainWindow::refreshReminderTable(){
    reminderTable->clearContents();
    reminderTable->setRowCount(0);

    for(int i = 0; i < LeftGroup.Length(); i++){

        TaskList *currentList = LeftGroup.get_list(i);
        
        for(int j = 1; j <= currentList->Length(); j++){
            
            Task t = currentList->get_task(j);
            
            int daysLeft = calculate_left_days(t.get_deadline());
            
            if(daysLeft <= 3 && t.get_status() == false){
                int newRow = reminderTable->rowCount();
                reminderTable->insertRow(newRow);

                if(daysLeft >= 0){
                    reminderTable->setItem(newRow, 0, new CustomTableWidgetItem(QString::fromStdString(t.get_name())));
                    reminderTable->setItem(newRow, 1, new CustomTableWidgetItem(QString::number(daysLeft)));
                    reminderTable->setItem(newRow, 2, new CustomTableWidgetItem(QString::fromStdString(LeftGroup.get_i_name(i))));

                    // 设置一行的背景颜色
                    if(daysLeft == 0){
                        reminderTable->item(newRow, 0)->setBackground(QBrush(QColor(255, 255, 224, 50)));
                        reminderTable->item(newRow, 1)->setBackground(QBrush(QColor(255, 255, 224, 50)));
                        reminderTable->item(newRow, 2)->setBackground(QBrush(QColor(255, 255, 224, 50)));
                    }
                }
                else{
                    reminderTable->setItem(newRow, 0, new CustomTableWidgetItem(QString::fromStdString(t.get_name())));
                    reminderTable->setItem(newRow, 1, new CustomTableWidgetItem("已过期" + QString::number(-daysLeft) + "天"));
                    reminderTable->setItem(newRow, 2, new CustomTableWidgetItem(QString::fromStdString(LeftGroup.get_i_name(i))));

                    reminderTable->item(newRow, 0)->setBackground(QBrush(QColor(211, 211, 211, 50)));
                    reminderTable->item(newRow, 1)->setBackground(QBrush(QColor(211, 211, 211, 50)));
                    reminderTable->item(newRow, 2)->setBackground(QBrush(QColor(211, 211, 211, 50)));
                }

            }
        }
    }

    sortReminderTable();
}

// 排序提醒列表
void MainWindow::sortReminderTable(){
    if(reminderTable->rowCount() == 0) return;

    reminderTable->sortItems(1, Qt::AscendingOrder);
}

