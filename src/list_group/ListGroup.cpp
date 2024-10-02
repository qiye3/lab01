#include "ListGroup.hpp"
#include<iostream>
#include<fstream>
using namespace std;

ListGroup::ListGroup(){
    listgroup_num = 0;
}

ListGroup::~ListGroup(){
    for(int i = 0; i < listgroup_num; i++){
        delete listgroup[i].tasklist;
    }

    listgroup_num = 0;
}

// 初始化示例任务
void ListGroup::initialize_example_tasks(){
    listgroup[0].Name = "默认列表";
    
    listgroup[0].tasklist = new LinkList();

    listgroup[0].tasklist->append(Task("任务3", "描述1", 1, "2024-10-05"));
    listgroup[0].tasklist->append(Task("任务2", "描述2", 2, "2024-10-10"));
    listgroup[0].tasklist->append(Task("任务1", "描述3", 3, "2024-10-15"));
    listgroup[0].tasklist->append(Task("任务4", "描述4", 4, "2024-10-20"));
    listgroup[0].tasklist->append(Task("任务5", "描述5", 5, "2024-10-25"));
    listgroup[0].tasklist->append(Task("任务6", "描述6", 1, "2024-10-30"));

    listgroup_num ++;
}


// 向列表组中添加列表
bool ListGroup::append_list(int ListType, string Name){
    if(listgroup_num >= MAX_LISTS){
        // cout<<"列表数量已达上限"<<endl;
        return false;
    }
    listgroup[listgroup_num].Name = Name;
    switch (ListType)
    {
    case LINKLIST:
        listgroup[listgroup_num].tasklist = new LinkList();
        listgroup_num ++;
        break;
    case DLINKLIST:
        listgroup[listgroup_num].tasklist = new DLinkList();
        listgroup_num ++;
        break;
    case SEQLIST:
        listgroup[listgroup_num].tasklist = new SeqList();
        listgroup_num ++;
        break;

    default:
        break;
    }
    return true;
}


// 移除列表组中第i个列表
bool ListGroup::remove_list(int i){
    if(i < 0 || i >= listgroup_num){
        // cout<<"i is out of range"<<endl;
        return false;
    }

    delete listgroup[i].tasklist;

    for(int j = i; j < listgroup_num - 1; j++){
        listgroup[j] = listgroup[j + 1];
    }

    listgroup_num --;

    return true;
}


// 删除列表组中名称为name的列表
bool ListGroup::remove_list_by_name(string name){
    int i = 0;
    while(i < listgroup_num && listgroup[i].Name != name){
        i++;
    }

    if(i == listgroup_num){
        // cout<<"没有找到该列表"<<endl;
        return false;
    }

    delete listgroup[i].tasklist;

    for(int j = i + 1; j < listgroup_num; j++){
        listgroup[j - 1] = listgroup[j];
    }

    listgroup_num --;

    return true;
}


// 判断列表组是否为空
bool ListGroup::isEmpty() const{
    return listgroup_num == 0;
}


// 返回列表组长度
int ListGroup::Length() const{
    return listgroup_num;
}

// 获取第i个列表
TaskList *ListGroup::get_list(int i){
    if(i < 0 || i >= listgroup_num){
        // cout<<"i is out of range"<<endl;
        return nullptr;
    }

    return listgroup[i].tasklist;
}

// 获取第i个列表的名称
string ListGroup::get_i_name(int i){
    if(i < 0 || i >= listgroup_num){
        // cout<<"i is out of range"<<endl;
        return "";
    }

    return listgroup[i].Name;
}

// 改变第i个列表的名称
void ListGroup::change_name(int i, string name){
    if(i < 0 || i >= listgroup_num){
        cout<<"i is out of range"<<endl;
        return;
    }

    listgroup[i].Name = name;
}

// 从csv文件中读取
void ListGroup::read_from_csv(string filename, string filepath){

    append_list(LINKLIST, filename);

    listgroup[listgroup_num - 1].tasklist->read_from_csv(filename, filepath);
}


// 从txt文件中读取
void ListGroup::read_from_txt(string filename, string filepath){
    append_list(LINKLIST, filename);

    listgroup[listgroup_num - 1].tasklist->read_from_txt(filename, filepath);
}


// 将所有列表组写入csv文件
void ListGroup::write_all_to_csv(string *filenames, string filepath){
    for(int i = 0; i < listgroup_num; i++){
        listgroup[i].tasklist->write_to_csv(filenames[i], filepath);
    }
}

// 将所有列表组写入txt文件
void ListGroup::write_all_to_txt(string *filenames, string filepath){
    for(int i = 0; i < listgroup_num; i++){
        listgroup[i].tasklist->write_to_txt(filenames[i], filepath);
    }
}

