#include<iostream>
#include<vector>
#include<unistd.h>
#include<string>
using namespace std;
/*
工厂方法模式 Factory Method
核心思想：定义一个产品的抽象工厂接口，把对象实例化延迟到子类。
简单说：父类工厂只规定接口，创建哪个具体产品由子类工厂决定；新增产品，只需要新增产品类 + 对应的工厂子类，不用修改原有代码，符合开闭原则。
角色
Product（抽象产品）：产品基类，定义产品公共虚接口
ConcreteProduct（具体产品）：继承抽象产品，实现具体功能
Factory（抽象工厂）：工厂基类，声明纯虚的创建产品的方法 createProduct()
ConcreteFactory（具体工厂）：继承抽象工厂，重写createProduct，生产对应的具体产品

✅优点
符合开闭原则：增加新产品，不用修改旧代码
对象创建和业务使用分离，客户端不需要知道产品具体构造细节
❌缺点
每新增一个产品，就要新增产品类、工厂类，类的数量成倍增多，代码膨胀。
面试口述一句话
工厂方法模式，定义抽象工厂基类，声明创建产品的虚工厂方法；
具体工厂子类重写该方法生产对应产品，将对象实例化延迟到子类；
新增产品只需增加产品和工厂子类，符合开闭原则；缺点会造成类数量膨胀。
*/

//抽象产品
class Product{
public:
    virtual ~Product()=default;
    virtual void show()=0;
};

//产品a
class ProductA:public Product{
public:
    void show() override{
        cout<<"产品a展示"<<endl;
    }
};


//产品b
class ProductB:public Product{
public:
    void show() override{
        cout<<"产品b展示"<<endl;
    }
};

//抽象工厂，生产抽象产品
class Factory{
public:
    virtual ~Factory()=default;
    virtual Product* createProduct()=0;
};

//工厂a，专门生产a
class FactoryA:public Factory{
public:
    Product* createProduct()override{
        return new ProductA;
    }
};

//工厂b,专门生产b
class FactoryB:public Factory{
public:
    Product* createProduct()override{
        return new ProductB;
    }
};

int main(){
    Factory* createA=new FactoryA;
    Factory* createB=new FactoryB;
    Product* a=createA->createProduct();
    Product* b=createB->createProduct();

    a->show();
    b->show();

    delete a;
    delete b;

    delete createA;
    delete createB;
    return 0;
}
