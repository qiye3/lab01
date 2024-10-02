#ifndef LINKLIST_HPP
#define LINKLIST_HPP

#include<iostream>
#include"../task/Task.hpp"
#include"TaskList.hpp"
using namespace std;

class LinkList: public TaskList{
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

        // --------基本操作---------//

        bool append(Task t) override;

        bool insert(int i, Task t) override;

        Node* get_by_i(int i);

        Node* get_by_name(string name);

        bool remove(int i, Task& t) override;

        bool remove_by_name(string name) override;

        bool isEmpty() const override;

        int Length() const override;

        void display() const override;

        void clear() override;

        Task get_task(int i) override;

        // ----------排序-----------//

        void sort(int op) override;

        void reverse() override;

        // ----------筛选-----------//

        TaskList* filt_list(int op, string value) override; 

        // ----------读取-----------//

        void read_from_txt(string filename, string filepath = "") override;
};


#endif