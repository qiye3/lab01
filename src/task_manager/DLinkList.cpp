#include"DLinkList.hpp"
#include"../task/Task.hpp"

#include<string>
#include<fstream>
#include<iostream>
using namespace std;


DLinkList::DLinkList(){
    head = new DNode;
    head->next = nullptr;
    head->prior = nullptr;
    tail = head;
    length = 0;
}

DLinkList::~DLinkList(){
    DNode *p = head;
    DNode *q = p->next;
    while(q != nullptr){
        delete p;
        p = q;
        q = q->next;
    }
    delete p;
    length = 0;
}

// --------基本操作---------//

bool DLinkList::append(Task t){
    DNode *s = new DNode;
    s->task = t;
    s->next = nullptr;
    s->prior = tail;
    tail->next = s;

    tail = s;

    length ++;

    return true;
}

bool DLinkList::insert(int i, Task t){
    if(i < 1 || i > length + 1) return false;

    DNode *p = head;
    int j = 0;
    while(p != nullptr && j < i - 1){
        p = p->next;
        j++;
    }

    DNode *s = new DNode;
    s->task = t;
    s->next = p->next;
    s->prior = p;
    p->next = s;
    if(s->next != nullptr) s->next->prior = s;

    if(p == tail){
        tail = s;
    }

    length ++;
    return true;
}

bool DLinkList::remove(int i, Task& t){
    if(i < 1 || i > length) return false;

    DNode *p = head;
    int j = 0;

    while(p != nullptr && j < i - 1){
        p = p->next;
        j++;
    }

    DNode *q = p->next;
    t = q->task;

    p->next = q->next;
    if(q->next != nullptr) q->next->prior = p;

    delete q;

    if(p->next == nullptr){
        tail = p;
    }

    length --;

    return true;
}

bool DLinkList::remove_by_name(string name){
    DNode *p = head->next;
    while(p != nullptr && p->task.get_name() != name){
        p = p->next;
    }

    if(p == nullptr){
        return false;
    }

    p->prior->next = p->next;
    if(p->next != nullptr) p->next->prior = p->prior;

    if(p == tail){
        tail = p->prior;
    }

    delete p;

    length --;

    return true;
}

bool DLinkList::isEmpty() const{
    return length == 0;
}

int DLinkList::Length() const{
    return length;
}

void DLinkList::display() const{
    if(length == 0){
        cout<<"任务列表为空"<<endl;
        return;
    }
    cout << "任务名称"<<" "<< "任务描述"<<" "<< "任务优先级"<<" "<< "任务状态"<<" "<< "任务截止日期"<<" "<< "任务创建日期" << endl;
    DNode *p = head->next;
    while(p != nullptr){
        p->task.display();
        p = p->next;
    }
}

void DLinkList::clear(){
    DNode *p = head->next;
    DNode *q = p;
    while(p != nullptr){
        p = p->next;
        delete q;
        q = p;
    }
    head->next = nullptr;
    tail = head;
    length = 0;
}

Task DLinkList::get_task(int i){
    DNode *p = head->next;
    int j = 1;
    while(p != nullptr && j < i){
        p = p->next;
        j++;
    }

    if(p == nullptr){
        cout<<"没有找到该任务"<<endl;
        return Task();
    }

    return p->task;
}

Task DLinkList::get_task_by_id(int id){
    DNode *p = head->next;
    while(p != nullptr){
        if(p->task.get_id() == id){
            return p->task;
        }
        p = p->next;
    }

    return Task();
}

// ----------排序-----------//

void DLinkList::sort(int op, bool ifreverse){
    if(length <= 1) return;

    DNode *p = head->next; //从第一个结点开始
    DNode *q = head; // 前驱结点
    DNode *lp = nullptr; // 用于记录每一轮排序的最后一个结点

    bool flag = true; // 用于标记是否已经排好序

    while(flag){
        flag = false;
        p = head->next;
        q = head;

        while(p->next != lp){
            if(!p->task.compare(p->next->task, op, ifreverse)){
                q->next = p->next;
                if(p->next != nullptr) p->next->prior = q;
                p->prior = p->next;
                p->next = p->next->next;
                q->next->next = p;
                if(p->next != nullptr) p->next->prior = p;

                flag = true;

                if(p == tail){
                    tail = q->next;
                }

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

void DLinkList::reverse(){
    if(length <= 1) return;

    DNode *p = head;
    DNode *q = tail;

    head->next->prior = nullptr;
    head->next = nullptr;

    while(q != nullptr){
        p->next = q;
        q->prior = p;
        p = q;
        q = q->prior;
    }

    tail = p;
    p->next = nullptr;

}

// ----------筛选-----------//

TaskList* DLinkList::filt_list(int op, string value){
    DLinkList *res = new DLinkList();

    DNode *p = head->next;

    while(p != nullptr){
        if(p->task.filter(op, value)){
            res->append(p->task);
        }
        p = p->next;
    }

    if(res->isEmpty()){
        cout<<"没有符合条件的任务"<<endl;
    }

    return res;
}

// ----------读取-----------//

void DLinkList::read_from_txt(string filename, string filepath){
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