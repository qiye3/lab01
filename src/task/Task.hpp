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
        string createTime;

    public:
        enum op{
            Name = 0,
            Priority = 1,
            Deadline = 2,
            Status = 3,
            Description = 4,
            CreateTime = 5
        };

        //----构造、析构、展示函数----//

        Task();

        Task(string name, string description, int priority, string deadline);

        ~Task();

        void create_task();

        void display();

        // --------修改变量---------//

        void change_task(string new_name, string new_description, int new_priority, string new_deadline);

        void change_name(string new_name){name = new_name;};

        void change_description(string new_description){description = new_description;};

        void change_priority(int priority);

        void change_deadline(string new_deadline){deadline = new_deadline;};

        void change_status(){isDone = !isDone;};

        // --------获取变量的值-------//

        string get_name(){return name;};

        string get_description(){return description;};

        int get_priority(){return priority;};

        string get_deadline(){return deadline;};

        bool get_status(){return isDone;};

        string get_create_time(){return createTime;};

        // --------比较函数---------//

        bool compare(Task& other, int o){
            switch(o){
                // 任务名称：升序
                case Name:
                    return name < other.name;

                // 优先级：降序
                case Priority:
                    return priority > other.priority;
                
                // 截止日期：升序
                case Deadline:
                    return deadline < other.deadline;

                // 状态：未完成在前
                case Status:
                    return isDone < other.isDone;

                // 创建日期：升序
                case CreateTime:
                    return createTime < other.createTime;

                default: return false; 
            }
        }

        // --------筛选函数---------//
        bool filter(int o, string value){
            switch(o){
                case Name:
                    return name == value;
                case Priority:
                    return priority == stoi(value);
                case Deadline:
                    return deadline == value;
                case Status:
                    return isDone == (value == "true");
                case Description:
                    return description == value;
                case CreateTime:
                    return createTime == value;
                default: return false;
            }

        }


};


#endif