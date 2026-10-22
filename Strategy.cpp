#include<iostream>
#include<vector>
#include<unistd.h>
using namespace std;
//策略模式就是
//同一种夜魔，不同的算法，随时切换算法，消除大量ifelse

//角色
//抽象策略类，同一算法虚接口
//具体策略类，实现不同算法
//上下文类，通过下下文，切换不同策略实现不同算法


/*
优点
消除大量 if‑else
算法独立封装，方便替换、新增算法；符合开闭原则
算法和业务上下文解耦
❌缺点（面试要会说）
每一个算法就要新增一个策略类，类数量膨胀，类变多
上层需要知道各个策略，才能选择对应的策略
面试口述一句话
策略模式封装一系列算法，提供统一虚接口，上下文持有策略对象，可以动态切换算法；
消除大量 if‑else，新增算法只需增加子类，不修改原有代码，符合开闭原则；缺点会增加很多小类。
*/

class PayStrategy{
public:
    virtual ~PayStrategy()=default;
    virtual void pay(int money)=0;

};

//策略a ，支付宝
class AiliPay:public PayStrategy{
public:
    void pay(int m) override{
        cout<<"支付宝支付："<<m<<"元"<<endl;
    }

};

//策略b,微信
class weixin:public PayStrategy{
public:
    void pay(int m) override{
        cout<<"微信支付："<<m<<"元"<<endl;
    }
};
//上下文 ，持有策略，对外提供接口
class Context{
public:
                //父类指针接受子类对象地址
    void setStrategy(PayStrategy* p){
        s=p;
    }

    void doPay(int money){
        if(s)
        s->pay(money);
    }

private:
    PayStrategy* s=nullptr;
};

int main(){
    // //多态实现，父类指针/引用，指向子类对象
    // PayStrategy* a=new AiliPay;
    // PayStrategy* b=new weixin;
    AiliPay a;
    weixin b;
    Context t;
    t.setStrategy(&a);
    t.doPay(100);

    t.setStrategy(&b);
    t.doPay(200);


    return 0;
}
