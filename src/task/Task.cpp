#include"Task.hpp"
#include"../utils/Utils.hpp"

#include<iostream>
using namespace std;

Task::Task(){
    // create_task();
    isDone = false;
    createTime = current_time();
}

Task::~Task(){
}

void Task::change_task(string new_name, string new_description, int new_priority, string new_deadline){
    name = new_name;
    description = new_description;
    priority = new_priority;
    deadline = new_deadline;
}

void Task::create_task(){
    cout<<"请输入任务名称：";
    cin.ignore(); // 忽略前一个输入留下的换行符
    getline(cin, name); // 读取整行输入，包括空格

    cout<<"请输入任务描述：(一行以内)";
    // cin.ignore(); 
    getline(cin, description); 


    do {
        cout << "请输入任务优先级 (1-5)：";
        cin >> priority;
        if (priority < 1 || priority > 5) {
            cout << "优先级必须在 1 到 5 之间，请重新输入。" << endl;
        }
    } while (priority < 1 || priority > 5);

    cout<<"请输入任务截止日期：";
    cin.ignore(); 
    getline(cin, deadline); 
}

void Task::display(){
    cout<<name<<" "<<description<<" "<<priority<<" "<< (isDone ? "已完成" : "未完成")<<" "<<deadline<<" "<<createTime<<endl;
}

void Task::change_priority(int priority) {
    if (priority >= 1 && priority <= 5) {
        this->priority = priority;
    } else {
        cout << "Priority must be between 1 and 5." << endl;
    }
}
