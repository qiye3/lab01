#include"Task.hpp"
#include"Utils.hpp"

#include<iostream>
using namespace std;

Task::Task(){
    isDone = false;
    create_time = current_time();
}

Task::~Task(){
}

void Task::display(){
    cout << "任务名称：" << name << endl;
    cout << "任务描述：" << description << endl;
    cout << "任务优先级：" << priority << endl;
    cout << "任务状态：" << (isDone ? "已完成" : "未完成") << endl;
    cout << "任务截止日期：" << deadline << endl;
    cout << "任务创建日期：" << create_time << endl;
}
