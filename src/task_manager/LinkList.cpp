#include"LinkList.hpp"
#include"../task/Task.hpp"

#include<string>
#include<fstream>
#include<iostream>
using namespace std;


// ----------基本操作---------//

LinkList::LinkList(){
    head = new Node;
    head->next = nullptr;
    tail = head;
    length = 0;
}

LinkList::~LinkList(){
    Node *p = head;
    Node *q = p->next;
    while(q != nullptr){
        delete p;
        p = q;
        q = q->next;
    }
    delete p;
    length = 0;
}

// 获取链表长度
int LinkList::Length() const{
    return length;
}

// 根据索引查找节点
LinkList::Node* LinkList::get_by_i(int i){
    if(i < 0 || i > length){
        cout<<'i'<<" is out of range"<<endl;
        return nullptr;
    }

    Node *p = head->next;
    int j = 1;
    while(p != nullptr && j < i){
        p = p->next;
        j++;
    }
    return p;
}

// 根据任务名称查找节点
LinkList::Node *LinkList::get_by_name(string name){
    Node *p = head->next;
    while(p != nullptr && p->task.get_name() != name){
        p = p->next;
    }
    return p;
    // 如果没有找到（即遍历完链表），最终 p 将为 NULL，因此返回 NULL。
}

// 在链表尾部添加节点
bool LinkList::append(Task t){
    Node *s = new Node;
    s->task = t;
    s->next = nullptr;
    tail->next = s;
    tail = s;
    length ++;
    return true;
}

// 显示链表
void LinkList::display() const{
    Node *p = head->next;
    if(p == nullptr){
        cout<<"任务列表为空"<<endl;
        return;
    }
    cout << "任务名称"<<" "<< "任务描述"<<" "<< "任务优先级"<<" "<< "任务状态"<<" "<< "任务截止日期"<<" "<< "任务创建日期" << endl;
    while(p != nullptr){
        p->task.display();
        p = p->next;
    }
}

// 在第 i 个节点插入节点
bool LinkList::insert(int i, Task t){
    if(i < 1 || i > length){
        cout<<'i'<<" is out of range"<<endl;
        return false;
    }

    Node *p = head;
    int j = 0;
    while(p != nullptr && j < i - 1){
        p = p->next;
        j++;
    }

    Node *s = new Node;
    s->task = t;
    s->next = p->next;
    p->next = s;

    if(p == tail){
        tail = s;
    }

    length ++;
    return true;
}

// 删除第 i 个节点
bool LinkList::remove(int i, Task& t){
    if(i < 1 || i > length){
        cout<<'i'<<" is out of range"<<endl;
        return false;
    }

    Node *p = head;
    int j = 0;
    while(p != nullptr && j < i - 1){
        p = p->next;
        j++;
    }

    Node *q = p->next;
    t = q->task;
    p->next = q->next;
    delete q;

    if(p->next == nullptr){
        tail = p;
    }

    length --;
    return true;
}

// 删除名称为name的任务
bool LinkList::remove_by_name(string name){
    Node *p = head;
    Node *q = p->next;
    while(q != nullptr && q->task.get_name() != name){
        p = q;
        q = q->next;
    }

    if(q == nullptr){
        return false;
    }

    p->next = q->next;
    delete q;

    if(p->next == nullptr){
        tail = p;
    }

    length --;
    return true;
}

// 判断链表是否为空
bool LinkList::isEmpty() const{
    return length == 0;
}

// 清空链表
void LinkList::clear(){
    Node *p = head->next;
    Node *q = p;
    while(p != nullptr){
        p = p->next;
        delete q;
        q = p;
    }
    head->next = nullptr;
    tail = head;
    length = 0;
}

// 从链表中获取第 i 个任务
Task LinkList::get_task(int i){
    Node *p = get_by_i(i);
    if(p == nullptr){
        cout<<"没有找到该任务"<<endl;
        return Task();
    }
    return p->task;
}

// 根据任务 ID 获取任务
Task LinkList::get_task_by_id(int id){
    Node *p = head->next;
    while(p != nullptr){
        if(p->task.get_id() == id){
            return p->task;
        }
        p = p->next;
    }
    return Task();
}

// 排序
void LinkList::sort(int op, bool ifreverse){
    if(length <= 1) return;

    Node *p = head->next; //从第一个结点开始
    Node *q = head; // 前驱结点
    Node *lp = nullptr; // 用于记录每一轮排序的最后一个结点

    bool flag = true; // 用于标记是否已经排好序

    while(flag){
        flag = false;

        p = head->next;
        q = head;

        while(p->next != lp){
            if(!p->task.compare(p->next->task, op, ifreverse)){
                q->next = p->next;
                p->next = p->next->next;
                q->next->next = p;

                flag = true;

                q = q->next;
            }
            else{
                q = p;
                p = p->next;
            }
        }

        lp = p;
    }
}

// 反转
void LinkList::reverse(){
    if(head->next == nullptr) return;

    Node *p = head->next;
    Node *q = p->next;

    head->next = nullptr;

    while(p != nullptr){
        q = p->next;
        p->next = head->next;
        head->next = p;
        p = q;
    }
}

// 筛选
TaskList* LinkList::filt_list(int op, string value) {
    LinkList *res = new LinkList();  // 创建新的 LinkList 对象
    Node *p = head->next;

    while (p != nullptr) {
        if (p->task.filter(op, value)) {
            res->append(p->task);  // 将符合条件的任务添加到结果链表中
        }
        p = p->next;
    }

    if (res->isEmpty()) {
        cout << "没有符合条件的任务" << endl;
    }

    return res;  // 返回基类指针
}

// 从txt文件读取
void LinkList::read_from_txt(string filename, string filepath){
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
