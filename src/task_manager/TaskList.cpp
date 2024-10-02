#include"TaskList.hpp"
#include<fstream>

// 实现虚拟析构函数
TaskList::~TaskList(){
    
}

// 从 csv 文件中读取任务
void TaskList::read_from_csv(string filename, string filepath){
    ifstream fin;
    string path = filepath + filename;
    fin.open(path, ios::in);
    if (!fin.is_open()) {
        cout << "文件打开失败" << endl;
        return;
    }

    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        string taskName, taskDescription, priorityStr, statusStr, deadline, createTime;
        
        // 按逗号分割每一行
        getline(ss, taskName, ',');
        getline(ss, taskDescription, ',');
        getline(ss, priorityStr, ',');
        getline(ss, deadline, ',');

        // 将字符串转换为相应类型
        int priority = stoi(priorityStr);
        
        // 创建 Task 对象并设置其属性
        Task t;
        t.change_name(taskName);
        t.change_description(taskDescription);
        t.change_priority(priority);
        t.change_deadline(deadline);

        // 将 Task 对象添加到列表
        append(t);
    }

    fin.close();
}

