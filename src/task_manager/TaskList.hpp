#ifndef TASKLIST_HPP
#define TASKLIST_HPP

#include "../task/Task.hpp"
#include <string>
using namespace std;

class TaskList {
public:
    // TaskList(){};
    virtual ~TaskList();

    // --------基本操作---------//

    virtual bool append(Task t) = 0;

    virtual bool insert(int i, Task t) = 0;

    virtual bool remove(int i, Task& t) = 0;

    virtual bool remove_by_name(string name) = 0;

    virtual bool isEmpty() const = 0;

    virtual int Length() const = 0;

    virtual void display() const = 0;

    virtual void clear() = 0;

    virtual Task get_task(int i) = 0;

    virtual Task get_task_by_id(int id) = 0;

    // ----------排序-----------//

    virtual void sort(int op, bool ifreverse) = 0;

    virtual void reverse() = 0;

    // ----------筛选-----------//

    virtual TaskList* filt_list(int op, string value) = 0; 

    // ----------读取-----------//

    virtual void read_from_txt(string filename, string filepath = "") = 0;

    void read_from_csv(string filename, string filepath = "");

    // ----------写入-----------//

    void write_to_csv(string filename, string filepath = "");

    void write_to_txt(string filename, string filepath = "");
};

#endif // TASKLIST_HPP