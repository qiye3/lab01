#ifndef LINKLIST_HPP
#define LINKLIST_HPP

#include<iostream>
#include"../task/Task.hpp"
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

        bool remove_by_name(string name);

        bool isEmpty() const;

        int Length() const;

        void display() const;

        void clear();

        Task get_task(int i);

        // ----------排序-----------//

        void sort(int op);

        void reverse();

        // ----------筛选-----------//

        LinkList filt_list(int op, string value); 

        // ----------修改-----------//

        bool change(int i, int op);

        // ----------读取-----------//

        void read_from_txt(string filename, string filepath = "");
};


#endif