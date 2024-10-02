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

        void change_name(int i, string name);

        void initialize_example_tasks();

        bool append_list(int ListType, string Name);

        bool remove_list(int i);

        bool remove_list_by_name(string name);

        bool isEmpty() const;

        int Length() const;

        TaskList *get_list(int i);

        string get_i_name(int i);

        void read_from_csv(string filename, string filepath = "");

        void read_from_txt(string filename, string filepath = "");

        void write_all_to_csv(string *filenames, string filepath = "");

        void write_all_to_txt(string *filenames, string filepath = "");
};


#endif