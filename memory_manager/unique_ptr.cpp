#include <iostream>

/***
 * (1) unique_ptr概述
 *     独占式的概念：同一个时刻，只能有一个unique_ptr指针指向这个对象（这块内存）
 * (1.1) 常规初始化（unique_ptr和new配合）
 * (1.2) make_unique函数(c++14)
 *
 * (2) unique_ptr常用操作
 * (2.1) unique_ptr不支持的操作
 * (2.2) 移动语义
 * (2.3) release(): 放弃对指针的控制权（切断了智能指针和其所指向的对象之间的联系）
 *                  返回裸指针，将该智能指针置空，返回的这个裸指针可以手工delete来释放，也可以用来初始化另一个智能指针，或者给另一个智能指针赋值
 * (2.4) reset()
 *       不带参数情况: 释放智能指针所指向的对象，并将智能指针置空
 *       带参数情况: 释放智能指针所指向的对象，并将智能指针指向新对象
 * (2.5) = nullptr: 释放智能指针所指向的对象，并将智能指针置空
 * (2.6) 指向一个数组
 * (2.7) get()
 * (2.8) *解引用
 * (2.9) swap()
 * (2.10) 将智能指针名字作为判断条件
 * (2.11) 转换成shared_ptr类型
 *
 * (3)
 * (3.1) 返回unique_ptr
 * (3.2) 指定删除器
 * (3.3) 尺寸问题
 *       通常和裸指针一致，如果指定了自定义删除器，尺寸可能会增加，也可能不增加
 *       a> lambda表达式型删除器，尺寸无变化
 *       b> 函数型删除器，尺寸变化
 * (3.4) 智能指针总结
 * (3.4.1) 智能指针背后的设计思想：帮助程序员释放内存，防止内存泄露
 * (3.4.2) auto_ptr为什么被废弃
 *         不能再容器中保存，也不能从函数中返回auto_ptr
 * (3.4.3) 智能指针的选择
 *         如果程序要使用多个指向同一个对象的指针，应该选择shared_ptr;
 *         如果程序不需要多个指向同一个对象的指针，应该首选unique_ptr;
 */

class A
{
public:
    A() {}

    ~A() {}
};

auto myFunc()
{
    return std::unique_ptr<std::string>(new std::string("hello, world!"));
}

std::unique_ptr<std::string> tuniqp()
{
    return std::unique_ptr<std::string>(new std::string("hello, world!"));
}

void unique_delete(std::string* str)
{
    delete str;
    str = nullptr;
}

int main(int argc, char const* argv[])
{
    // (3.2)
    // a
    typedef void (*fp)(std::string*);
    std::unique_ptr<std::string, fp> ps1(new std::string("hello, world!"), unique_delete);
    // b
    using fp2 = void (*)(std::string*);
    std::unique_ptr<std::string, fp2> ps2(new std::string("hello, world!"), unique_delete);
    // c
    typedef decltype(unique_delete)* fp3;
    std::unique_ptr<std::string, fp3> ps3(new std::string("hello, world!"), unique_delete);
    // d
    std::unique_ptr<std::string, decltype(unique_delete)*> ps4(new std::string("hello, world!"), unique_delete);
    // e: lambda表达式
    auto mydella = [](std::string* pdel)
    {
        delete pdel;
        pdel = nullptr;
    };
    std::unique_ptr<std::string, decltype(mydella)> ps5(new std::string("hello, world!"), mydella);

    // (3.1)
    // std::shared_ptr<std::string> ps;
    // ps = tuniqp();

    // (2.11)
    // std::shared_ptr<std::string> pss1 = myFunc(); // 这里会创建控制块
    // std::shared_ptr<std::string> pss1 = std::unique_ptr<std::string>(new std::string("hello, world!"));
    // std::unique_ptr<std::string> pu(new std::string("hello, world!"));
    // std::shared_ptr<std::string> pss1 = std::move(pu);

    // (2.9)
    // std::unique_ptr<std::string> ps1(new std::string("hello, world!"));
    // std::unique_ptr<std::string> ps2(new std::string("hello, world."));
    // ps1.swap(ps2);
    // std::swap(ps1, ps2);

    // (2.6)
    // std::unique_ptr<int[]> pArr(new int[10]);
    // pArr[0] = 1;
    // pArr[1] = 10;

    // []需要，否则如果有析构函数，就会报异常
    // std::unique_ptr<A[]> paArr(new A[10]);

    // (2.5)
    // std::unique_ptr<std::string> ps1(new std::string("hello, world!"));
    // ps1 = nullptr;

    // (2.4)
    // std::unique_ptr<std::string> ps1(new std::string("hello, world!"));
    // std::unique_ptr<std::string> ps2(new std::string("hello, world."));
    // ps1.reset();
    // ps1.reset(ps2.release());

    // (2.3)
    // std::unique_ptr<std::string> ps1(new std::string("hello, world!"));
    // std::unique_ptr<std::string> ps2(ps1.release());
    // std::string* temp = ps2.release();
    // delete temp; // 需要手动释放

    // (2.2)
    // std::unique_ptr<std::string> ps1(new std::string("hello, world!"));
    // std::unique_ptr<std::string> ps2(std::move(ps1));

    // (2.1)
    // std::unique_ptr<std::string> ps1(new std::string("hello, world!"));
    // std::unique_ptr<std::string> ps2(ps1); // 不支持拷贝操作（定义时初始化）
    // std::unique_ptr<std::string> ps3 = ps1; // 不支持拷贝操作（定义时初始化）
    // std::unique_ptr<std::string> ps4;
    // ps4 = ps1; // 不支持赋值操作

    // (1.2)
    // std::unique_ptr<int> p1 = std::make_unique<int>(100);
    // auto p2 = std::make_unique<int>(200);

    // (1.1)
    // std::unique_ptr<int> pi; // 可以指向int对象的一个空智能指针
    // if (pi == nullptr)
    // {
    //     std::cout << "pi is nullptr\n";
    // }

    // std::unique_ptr<int> pi2(new int(105));
    return 0;
}
