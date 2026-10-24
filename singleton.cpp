#include<iostream>
using namespace std;
//单例模型，用最常见的静态局部变量
class Singleton{
public:
	static Singleton& getSingleton(){
		static Singleton s;
		cout<<"单例对象创建成功！"<<endl;
		return s;
	}

	//禁止拷贝构造和拷贝赋值运算
	Singleton(const Singleton& other)=delete;
	Singleton& operator=(const Singleton& other) = delete;
	//禁止拷贝移动和移动赋值
	Singleton(Singleton&& other) = delete;
	Singleton& operator=(Singleton&& other) = delete;

private:
	//把构造和析构设为私有
	Singleton() = default;//default让编译器自动生成默认实现，与下面的等价
	~Singleton() {};

};

int main(){
	//错了，这么写拷贝了一次
	//Singleton s=Singleton::getSingleton();
	//Singleton s2=Singleton::getSingleton();

	Singleton& s1 = Singleton::getSingleton();	
	Singleton& s2 = Singleton::getSingleton();
	cout<<&s2<<endl;
	cout<<&s2<<endl;

	return 0;
}


