#include"LinkList.hpp"
#include"Utils.hpp"

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
    while(q != NULL){
        delete p;
        p = q;
        q = q->next;
    }
    delete p;
    length = 0;
}

int LinkList::Length(){
    return length;
}

LinkList::Node* LinkList::get_by_i(int i){
    if(i < 0 || i > length){
        cout<<'i'<<" is out of range"<<endl;
        return NULL;
    }

    Node *p = head->next;
    int j = 1;
    while(p != NULL && j < i){
        p = p->next;
        j++;
    }
    return p;
}

LinkList::Node *LinkList::get_by_name(string name){
    Node *p = head->next;
    while(p != NULL && p->task.get_name() != name){
        p = p->next;
    }
    return p;
    // 如果没有找到（即遍历完链表），最终 p 将为 NULL，因此返回 NULL。
}

bool LinkList::append(Task t){
    Node *s = new Node;
    s->task = t;
    s->next = NULL;
    tail->next = s;
    tail = s;
    length ++;
    return true;
}

void LinkList::display(){
    Node *p = head->next;
    while(p != NULL){
        cout<<p->task.get_name()<<endl;
        p = p->next;
    }
}

bool LinkList::insert(int i, Task t){
    if(i < 1 || i > length){
        cout<<'i'<<" is out of range"<<endl;
        return false;
    }

    Node *p = head;
    int j = 0;
    while(p != NULL && j < i - 1){
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

bool LinkList::remove(int i, Task& t){
    if(i < 1 || i > length){
        cout<<'i'<<" is out of range"<<endl;
        return false;
    }

    Node *p = head;
    int j = 0;
    while(p != NULL && j < i - 1){
        p = p->next;
        j++;
    }

    Node *q = p->next;
    t = q->task;
    p->next = q->next;
    delete q;

    if(p->next == NULL){
        tail = p;
    }

    length --;
    return true;
}

bool LinkList::isEmpty(){
    return length == 0;
}

void LinkList::clear(){
    Node *p = head->next;
    Node *q = p;
    while(p != NULL){
        p = p->next;
        delete q;
        q = p;
    }
    head->next = NULL;
    tail = head;
    length = 0;
}

// ----------排序-----------//

void LinkList::sort(compare_func compare){
    Node *p = head->next;
    Node *q = p->next;
    Node *pre = head;
    Node *r;

    head->next = NULL;
    tail = head;

    while(p != NULL){
        r = p;
        p = p->next;

        
        while(q != NULL){
            if(compare(p->task, q->task)){
                r = q;
                pre = p;
            }
            q = q->next;
        }

        pre->next = r->next;
        r->next = NULL;

        tail->next = r;
        tail = r;
        
        p = head->next;
        q = p->next;
    }
}
