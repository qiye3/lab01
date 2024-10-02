#ifndef SEQLIST_HPP
#define SEQLIST_HPP

#include<iostream>
#include"../task/Task.hpp"
#include"TaskList.hpp"
using namespace std;

#define DEFAULT_INIT_SIZE 100

class SeqList: public TaskList{
    protected:
        Task *data;//动态数组
        int MaxSize, length;
    
    public:
        SeqList(int InitSize = DEFAULT_INIT_SIZE);
        ~SeqList();

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