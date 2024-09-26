#ifndef LINKLIST_HPP
#define LINKLIST_HPP

#include<iostream>
#include<Task.hpp>
using namespace std;

class LinkList{
    protected:
        struct Node{
            Task task;
            Node* next;
        };
        Node* head;
        Node* tail;
        int length;
    
    public:
        LinkList();
        ~LinkList();

        typedef bool (*compare_func)(const Task&, const Task&); 

        // --------基本操作---------//

        bool append(Task t);

        bool insert(int i, Task t);

        Node* get_by_i(int i);

        Node* get_by_name(string name);

        bool remove(int i, Task& t);

        bool isEmpty();

        int Length();

        void display();

        void clear();

        // ----------排序-----------//

        void sort(compare_func compare);

        void reverse();

        // ----------筛选-----------//

        LinkList filter_by_priority(int priority);

        LinkList filter_by_deadline(string deadline, string op);

        LinkList filter_by_status(bool isDone);

        // ----------修改-----------//

        bool change(int i, string op);



};


#endif