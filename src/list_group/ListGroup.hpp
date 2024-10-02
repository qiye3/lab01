#ifndef LISTGROUP_HPP
#define LISTGROUP_HPP

#include "../task_manager/TaskList.hpp"
#include <string>
#include "../task_manager/LinkList.hpp"
#include "../task_manager/DLinkList.hpp"
#include "../task_manager/SeqList.hpp"
#include<iostream>
using namespace std;

#define MAX_LISTS 100

class ListGroup {
    protected:
        struct Node{
            string Name;
            TaskList *tasklist;
        }listgroup[MAX_LISTS];
        
        int listgroup_num;


    public:
        enum ListType{
            LINKLIST = 0,
            DLINKLIST = 1,
            SEQLIST = 2
        };

        ListGroup();
        ~ListGroup();

        void initialize_example_tasks();

        bool append_list(int ListType, string Name);

        bool remove_list(int i);

        bool remove_list_by_name(string name);

        bool isEmpty() const;

        int Length() const;

        TaskList *get_list(int i);

        string get_i_name(int i);
};


#endif