#include"SeqList.hpp"
#include"../task/Task.hpp"

#include<string>
#include<fstream>
#include<iostream>
using namespace std;

SeqList::SeqList(int InitSize){
    data = new Task[InitSize];
    MaxSize = InitSize;
    length = 0;
}

SeqList::~SeqList(){
    delete[] data;
    length = 0;
}

// --------基本操作---------//

// 向顺序表中添加任务
bool SeqList::append(Task t){
    if(length >= MaxSize){
        return false;
    }
    data[length] = t;
    length ++;
    return true;
}

// 在顺序表的第 i 个位置插入任务
bool SeqList::insert(int i, Task t){
    if(i < 1 || i > length + 1) return false;
    if(length >= MaxSize) return false;

    for(int j = length; j >= i; j--){
        data[j] = data[j - 1];
    }
    data[i - 1] = t;

    length ++;
    return true;
}

// 删除
bool SeqList::remove(int i, Task& t){
    if(i < 1 || i > length) return false;

    t = data[i - 1];
    for(int j = i; j < length; j++){
        data[j - 1] = data[j];
    }

    length --;
    return true;
}

// 根据任务名称删除任务
bool SeqList::remove_by_name(string name){
    int i = 0;
    while(i < length && data[i].get_name() != name){
        i++;
    }

    if(i == length) return false;

    for(int j = i + 1; j < length; j++){
        data[j - 1] = data[j];
    }

    length --;
    return true;
}

// 判断是否为空
bool SeqList::isEmpty() const{
    return length == 0;
}

// 获取长度
int SeqList::Length() const{
    return length;
}

// 命令行展示
void SeqList::display() const{
    if(length == 0){
        cout<<"任务列表为空"<<endl;
        return;
    }
    cout << "任务名称"<<" "<< "任务描述"<<" "<< "任务优先级"<<" "<< "任务状态"<<" "<< "任务截止日期"<<" "<< "任务创建日期" << endl;
    for(int i = 0; i < length; i++){
        data[i].display();
    }
}

// 清除列表
void SeqList::clear(){
    length = 0;
}

// 获取第 i 个任务
Task SeqList::get_task(int i){
    if(i < 1 || i > length){
        return Task();
    }
    return data[i - 1];
}

// 根据任务 ID 获取任务
Task SeqList::get_task_by_id(int id){
    for(int i = 0; i < length; i++){
        if(data[i].get_id() == id){
            return data[i];
        }
    }
    return Task();
}

// ----------排序-----------//

void SeqList::sort(int op, bool ifreverse){
    if(length <= 1) return;

    Task temp;
    for(int i = 0; i < length - 1; i++){
        for(int j = 0; j < length - i - 1; j++){
            if(!data[j].compare(data[j + 1], op, ifreverse)){
                temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }
}

void SeqList::reverse(){
    if(length <= 1) return;

    Task temp;
    for(int i = 0; i < length / 2; i++){
        temp = data[i];
        data[i] = data[length - i - 1];
        data[length - i - 1] = temp;
    }
}

// ----------筛选-----------//

TaskList* SeqList::filt_list(int op1, string value){
    SeqList *res = new SeqList();  // 创建新的 SeqList 对象

    for(int i = 0; i < length; i++){
        if(data[i].filter(op1, value)){
            res->append(data[i]);
        }
    }

    if(res->isEmpty()){
        cout << "没有符合条件的任务" << endl;
    }

    return res;  // 返回基类指针
}

// ----------读取-----------//

void SeqList::read_from_txt(string filename, string filepath){
    ifstream in(filepath + filename);
    if(!in){
        cout<<"文件打开失败"<<endl;
        return;
    }

    string name, description, deadline;
    int priority;

    while (true) {
        // 读取任务名称
        if (!getline(in, name) || name.empty()) {
            break; // 如果读取失败或者到达文件末尾，退出循环
        }

        // 读取任务描述
        if (!getline(in, description)) {
            cout << "读取任务描述时出错" << endl;
            return;
        }

        // 读取任务优先级
        if (in >> priority) {
            in.ignore(); // 忽略优先级后的换行符
        } 
        else {
            cout << "读取任务优先级时出错" << endl;
            return;
        }

        // 读取任务截止日期
        if (!getline(in, deadline)) {
            cout << "读取任务截止日期时出错" << endl;
            return;
        }

        // 创建任务并添加到链表
        Task t;
        t.change_name(name);
        t.change_description(description);
        t.change_priority(priority);
        t.change_deadline(deadline);
        append(t);
    }

    in.close();
    cout<<"读取成功"<<endl;
}