#include<iostream>
#include<vector>
#include<unistd.h>
using namespace std;

/*
抽象工厂模式 Abstract Factory
核心：生产一整套 / 一系列相互关联的产品，一个工厂可以产出多种产品。
工厂方法：1 个工厂只生产1 种产品。
抽象工厂：1 个工厂生产一组系列产品。
举例场景：做两套 UI 组件
系列 1：Windows 风格按钮、Windows 文本框
系列 2：Linux 风格按钮、Linux 文本框
同一个工厂，既能造按钮，又能造文本框；切换整套风格，只需要换一个工厂对象。
角色
AbstractProductA、AbstractProductB：两套抽象产品（按钮、文本框）
ConcreteProduct：具体系列产品（Win 按钮、Win 文本框；Linux 按钮、Linux 文本框）
AbstractFactory 抽象工厂：声明创建这一组所有产品的虚函数
ConcreteFactory 具体工厂：实现，生产整套同系列产品

*/

class Button{
public:
    virtual ~Button()=default;
    virtual void show()=0;
};

//window btn
class WinBtn:public Button{
public:
    void show() override{
        cout<<"展示win风格按钮"<<endl;
    }
};

class LinuxBtn:public Button{
public:
    void show()override{
        cout<<"展示Linux 风格按钮"<<endl;
    }
};


class TextEdit{
public:
    virtual ~TextEdit()=default;
    virtual void show()=0;
};

class WinTextEdit:public TextEdit{
public:
    void show()override{
        cout<<"展示win文本"<<endl;
    }
};
class LinuxTextEdit:public TextEdit{
public:
    void show() override{
        cout<<"展示linux 文本"<<endl;
    }
};
//====抽象工厂：可以生产整套组件：按钮+文本框====
class AbstractFactory{
public:
    virtual ~AbstractFactory()=default;
    virtual Button* createBtn()=0;
    virtual TextEdit* createTextEdit()=0;
};

//Windows工厂：生产全套Windows组件
class WinFactory:public AbstractFactory{
public:
    Button* createBtn() override{
        cout<<"创建win风格按钮"<<endl;
        return new WinBtn;
    }
    TextEdit* createTextEdit()override{
        cout<<"创建win风格文本"<<endl;
        return new WinTextEdit;
    }
};

//linux工厂，生产全套linux组件
class LinuxFactory:public AbstractFactory{
public:
    Button* createBtn() override{
        cout<<"创建Linux风格按钮"<<endl;
        return new LinuxBtn;
    }
    TextEdit* createTextEdit()override{
        cout<<"创建Linux风格文本"<<endl;
        return new LinuxTextEdit;
    }
};

int main(){
    AbstractFactory* factory=new WinFactory;
    Button* b=factory->createBtn();
    TextEdit* t=factory->createTextEdit();
    b->show();
    t->show();

    delete b;
    delete t;
    delete factory;

    cout << "--------" << endl;
    factory = new LinuxFactory;
    b = factory->createBtn();
    t = factory->createTextEdit();

    b->show();
    t->show();

    delete b;
    delete t;
    delete factory;

    return 0;
}