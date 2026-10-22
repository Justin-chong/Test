#include<iostream>
#include<vector>
#include<unistd.h>
#include<string>
using namespace std;

/*
观察者模式（Observer）
核心思想：一对多依赖关系。当被观察者（主题）状态发生变化，所有注册的观察者自动收到通知，自动更新。
Qt 信号槽本质就是观察者模式。
角色一共两个：
Subject 被观察者（主题）
保存一组观察者
提供接口：注册观察者、移除观察者、通知全部观察者
Observer 观察者
提供update()更新接口，被观察者通知时调用这个函数。
流程：
观察者向主题注册自己
主题内部状态改变
主题遍历所有已注册观察者，调用每一个观察者的update()
观察者执行自己的更新逻辑



优点
解耦：主题只知道观察者抽象基类，不知道具体实现；新增观察者不需要修改 Subject 代码，符合开闭原则。
一对多自动广播。
缺点（面试常问）
通知是顺序同步调用；如果某个观察者 update 执行很慢，会阻塞后面所有观察者。
观察者不知道主题怎么变化，只收到结果；循环依赖风险。
观察者销毁忘记 detach → 野指针，崩溃！（高频坑）
*/


//抽象观察者
class Observer{
    public:
    virtual ~Observer()=default;
    virtual void update(int msg)=0;//收到通知回调
};

//被观察者（主题）
class Subject{
public:
    void attach(Observer* ob){
        if(!ob)return ;
        v.push_back(ob);
    }

    void detach(Observer* ob){
        for(auto it=v.begin();it!=v.end();it++){
            if(*it==ob){
                v.erase(it);
                break;
            }

        }
    }


    void notify(int msg){
        for(auto ob:v){
            ob->update(msg);
        }
    }


    void changeState(int newVal){
        cout << "主题状态改变为:" << newVal << endl;
        notify(newVal);
    }
private:
    vector<Observer*> v;//保存所有注册的观察者
};

class ObserverA:public Observer{
public:
    void update(int msg) override {
        sleep(2);
        cout << "观察者A收到消息:" << msg << endl;
    }
};

//具体观察者B
class ObserverB : public Observer {
public:
    void update(int msg) override {
        sleep(1);
        cout << "观察者B收到消息:" << msg << endl;
    }
};

int main(){
    Subject sub;
    ObserverA a;
    ObserverB b;

    sub.attach(&a);
    sub.attach(&b);
    sub.notify(10);
    sub.changeState(20);//自动通知ab
    sub.detach(&b);
    sub.changeState(30);//自动通知a

    return 0;
}
