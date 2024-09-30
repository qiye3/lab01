#include<iostream>
#include"Task.hpp"
#include"LinkList.hpp"


using namespace std;

int main(){

    LinkList list;
    int op;

    list.read_from_txt("test.txt", "../data/");

    while(true){
        cout<<endl;
        cout<<"请选择操作："<<endl;
        cout<<"1. 添加任务"<<endl;
        cout<<"2. 删除任务"<<endl;
        cout<<"3. 显示任务列表"<<endl;
        cout<<"4. 退出"<<endl;
        cout<<"5. 排序"<<endl;
        cout<<"6. 筛选"<<endl;
        cin>>op;
        
        string name;

        switch(op){
            case 1: {
                Task t;
                t.create_task();
                list.append(t);
                break;
            }
            case 2:
                cout<<"请输入要删除的任务名称：";
                cin>>name;
                list.remove_by_name(name);
                break;
            case 3:
                list.display();
                break;
            case 4:
                return 0;
            case 5:
                cout<<"请选择排序方式："<<endl;
                cout<<"0. 任务名称"<<endl;
                cout<<"1. 优先级"<<endl;
                cout<<"2. 截止日期"<<endl;
                cout<<"3. 状态"<<endl;
                cout<<"5. 创建日期"<<endl;
                int sort_op;
                cin>>sort_op;
                list.sort(sort_op);
                cout<<"排序完成"<<endl;
                cout<<"显示排序后的任务列表："<<endl;
                list.display();
                break;
            case 6:{
                cout<<"请选择筛选方式："<<endl;
                cout<<"0. 任务名称"<<endl;
                cout<<"1. 优先级"<<endl;
                cout<<"2. 截止日期"<<endl;
                cout<<"3. 状态"<<endl;
                cout<<"4. 描述"<<endl;
                int filt_op;
                cin>>filt_op;
                cout<<"请输入筛选条件：";
                string value;
                cin>>value;
                list.filt_list(filt_op, value).display();
                break;
            }
            default:
                cout<<"无效操作"<<endl;
                break;
        }
    }
    return 0;
}