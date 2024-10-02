#include"TaskList.hpp"
#include<fstream>

using namespace std;

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

    // 忽略第一行
    string firstLine;
    getline(fin, firstLine);

    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        string taskName, taskDescription, statusStr, deadline, createTime, priorityStr;
        
        // 按逗号分割每一行
        getline(ss, taskName, ',');
        getline(ss, taskDescription, ',');
        getline(ss, priorityStr, ',');
        getline(ss, deadline, ',');

        int priority;
        try{
            priority = stoi(priorityStr);
        } 
        catch (invalid_argument e){
            cerr << "Failed" << endl;
            cerr << e.what() << endl;
            cerr <<priorityStr << endl;
            return;
        }


        
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

// 将任务列表写入 csv 文件
void TaskList::write_to_csv(string filename, string filepath){
    ofstream fout;
    string path = filepath + filename + ".csv";

    // 打开文件（若不存在则创建，若存在则清空）
    fout.open(path);
    if (!fout.is_open()) {
        cerr << "无法打开文件: " << path << endl;
        return;
    }
    // fout.imbue(locale("zh_CN.UTF-8"));

    fout << "任务名称,描述,优先级,截止日期,状态,创建时间" << std::endl;

    for (int i = 1; i <= Length(); i++) {
        Task t = get_task(i);
        fout << t.get_name() << ","
             << t.get_description() << ","
             << (t.get_priority() ? "已完成" : "未完成") << ","
             << t.get_deadline() << ","
             << t.get_create_time() << std::endl;
    }

    fout.close();

    cout << "数据成功保存到: " << path << endl;
}

// 将任务列表写入 txt 文件
void TaskList::write_to_txt(string filename, string filepath){
    ofstream fout;
    string path = filepath + filename + ".txt";

    // 打开文件（若不存在则创建，若存在则清空）
    fout.open(path);
    if (!fout.is_open()) {
        cerr << "无法打开文件: " << path << endl;
        return;
    }
    // fout.imbue(locale("zh_CN.UTF-8"));
    fout << "任务名称,描述,优先级,截止日期,状态,创建时间" << endl;

    for (int i = 1; i <= Length(); i++) {
        Task t = get_task(i);
        fout << t.get_name() << ","
             << t.get_description() << ","
             << (t.get_priority() ? "已完成" : "未完成") << ","
             << t.get_deadline() << ","
             << t.get_create_time() << endl;
    }

    fout.close();

    cout << "数据成功保存到: " << path << endl;
}