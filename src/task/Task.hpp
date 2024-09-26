#ifndef TASK_HPP
#define TASK_HPP

#include <string>
#include <iostream>
#include <chrono>
#include <iomanip>
using namespace std;

class Task{
    protected:
        //任务名称
        string name;
        // 任务描述
        string description;
        // 任务优先级
        int priority;
        // 任务状态
        bool isDone;
        // 任务截止日期
        string deadline;
        // 任务创建日期
        string create_time;

    public:
        enum op{
            Name,
            Priority,
            Deadline,
            Status,
            Description
        };

        //----构造、析构、展示函数----//

        Task();

        ~Task();

        void create_task(string name, string description, int priority, string deadline);

        void display();

        // --------修改变量---------//

        void change_name(string name){name = name;};

        void change_description(string description){description = description;};

        void change_priority(int priority){priority = priority;};

        void change_deadline(string deadline){deadline = deadline;};

        void change_status(bool isDone){isDone = isDone;};

        // --------获取变量的值-------//

        string get_name(){return name;};

        string get_description(){return description;};

        int get_priority(){return priority;};

        string get_deadline(){return deadline;};

        bool get_status(){return isDone;};

        string get_create_time(){return create_time;};

        // --------比较函数---------//

        bool compare(const Task& other, op o){
            switch(o){
                case Name:
                    return name < other.name;
                case Priority:
                    return priority < other.priority;
                case Deadline:
                    return deadline < other.deadline;
                case Status:
                    return isDone < other.isDone;
            }
        }


};


#endif