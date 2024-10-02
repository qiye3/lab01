#ifndef DLINKLIST_HPP
#define DLINKLIST_HPP

#include<iostream>
#include"../task/Task.hpp"
#include"TaskList.hpp"
using namespace std;

class DLinkList: public TaskList{
    protected:
        struct DNode{
            Task task;
            DNode *prior;
            DNode *next;
        }
        *head, *tail;
        int length;
    
    public:
        DLinkList();
        ~DLinkList();

        // --------基本操作---------//

        bool append(Task t) override;

        bool insert(int i, Task t) override;

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