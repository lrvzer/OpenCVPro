#include <iostream>

/***
 * shared_ptr
 *  工作原理：引用计数，每个shared_ptr的拷贝都指向相同的内存，所以只有最后一个指向该内存（对象）的shared_ptr指针不需要再指向该对象时，，才会去析构所指向的内存
 *  释放内存的时机：
 *      a> 被析构的时候
 *      b> 指向其他的对象时
 *
 *  (1) 常规初始化（shared_ptr和new配合）
 *      注意：裸指针可以初始化shared_ptr，但不推荐。智能指针和裸指针不要穿插使用
 *  (2) std::make_shared函数：标准库里的函数模板，安全高效的分配和使用shared_ptr
 *      能够在动态内存（堆）中分配并初始化一个对象，然后返回指向此对象的shared_ptr
 *  (3) shared_ptr引用计数的增加和减少
 *  (3.1) 引用计数的增加
 *        每个shared_ptr都会记录有多少个其他的shared_ptr指向相同的对象
 *        1) 一个shared_ptr通过另一个shared_ptr进行拷贝构造时
 *        2) 把智能指针作为实参往函数里传递（函数的形参为引用时不会增加）
 *        3) 作为函数的返回值
 *  (3.2) 引用计数的减少
 *        1) 给shared_ptr赋新值，指向新对象
 *        2) 局部的shared_ptr离开作用域
 *        3) 当一个shared_ptr引用计数从1变成0，则它会自动释放自己所管理（指向）的对象
 *  (4) shared_ptr指针常用操作
 *  (4.1) use_count(): 返回多少个智能指针指向某个对象，主要用于调试目的
 *  (4.2) unique(): 是否该智能指针独占某个指向的对象
 *  (4.3) reset(): 恢复（复位/重置）的意思
 *        a> 不带参数时
 *           若pi是唯一指向该对象的指针，那么释放pi所指向的对象，并将pi置空
 *           若pi不是唯一指向该对象的指针，那么不释放pi所指向的对象，但指向该对象的引用计数会减少1，同时将pi置空
 *        b> 带参数时，一般是一个new出来的指针
 *           若pi是唯一指向该对象的指针，那么释放pi所指向的对象，让pi指向新对象
 *           若pi不是唯一指向该对象的指针，那么不释放pi所指向的对象，但指向该对象的引用计数会减少1，同时让pi指向新对象
 *  (4.4) *解引用
 *  (4.5) get(): 考虑到有些函数的参数需要的是一个内置裸指针而不是智能指针
 *  (4.6) swap(): 交换两个智能指针所指向的对象
 *  (4.7) = nullptr
 *        a> 将所指向的对象引用计数减1，若引用计数变为0，则释放智能指针所指向的对象
 *        b> 将智能指针置空
 *  (4.8) 将智能指针名字作为判断条件
 *  (4.9) 指定删除器以及数组问题
 *        a> 指定删除器
 *           一定时机帮我们删除所指向的对象；delete：将delete运算符号作为默认的资源析构方式；
 *           我们可以指定自己的删除器取代系统默认的删除器，当智能指针需要删除所指向的对象时，编译器就会调用我们自己提供的删除器；
 *           shared_ptr指定删除器方式比较简单，一般只需要在参数中添加具体的删除器函数名即可，也可以是lambda表达式；
 *
 *        b> 数组问题，需要自己指定删除器
 *           default_delete来做删除器，删除数组
 *           自定义数组模板
 * (5) 使用场景，陷阱、性能分析，使用建议
 * (5.1) 使用场景
 * (5.2) 使用陷阱分析
 * (5.2.1) 慎用裸指针
 * (5.2.2) 慎用get()返回的指针
 *         不能delete，否则异常
 *         不能将其他智能指针绑定到get返回的指针上
 * (5.2.3) 不要把类对象指针this作为shared_ptr返回，该用enable_shared_from_this
 * (5.2.4) 避免循环引用
 * (5.3) 性能说明
 * (5.3.1) 尺寸问题
 *         第一个裸指针指向的是这个智能指针所指向的对象
 *         第二个裸指针 指向一个很大的数据结构(控制块)，这个控制块里边有啥:
 *             所指对象的强引用计数:shared ptr
 *             所指对象的弱引用计数:weak_ptr
 *             其他数据，比如删除器指针，内存分配器;
 *
 *         这个控制块是由第一个指向某个对象的shared_ptr来创建的;
 *         控制块创建时机:
 *          make_shared:分配并初始化一个对象，返回指向此对象的shared_ptr
 *          用裸指针来创建一个shared_ptr对象时
 * (5.3.2) 移动语义
 * (5.4) 补充说明和使用建议
 *       优先使用make_shared<T>()
 */
// std::shared_ptr<int> makes(int value)
// {
//     return std::shared_ptr<int>(new int(value));
// }

// void func(std::shared_ptr<int> tmp)
// {
//     return;
// }

// void func(std::shared_ptr<int>& tmp)
// {
//     return;
// }

// std::shared_ptr<int> func(std::shared_ptr<int>& tmp)
// {
//     return tmp;
// }

void myDelete(int* p) // 删除整型指针
{
    std::cout << "myDelete\n";
    delete p;
}

template <typename T>
std::shared_ptr<T> make_shared_array(size_t size)
{
    return std::shared_ptr<T>(new T[size], std::default_delete<T[]>());
}

class A
{
private:
    /* data */
public:
    A(/* args */);
    ~A();
};

A::A(/* args */)
{
}

A::~A()
{
    std::cout << "~A()\n";
}

std::shared_ptr<int> create0(int value)
{
    return std::make_shared<int>(value);
}

void myFunc(int value)
{
    std::shared_ptr<int> ptmp = create0(value);
    return;
}

void proc(std::shared_ptr<int> ptr)
{
    return;
}

class CT : std::enable_shared_from_this<CT>
{
public:
    std::shared_ptr<CT> getSelf()
    {
        // return std::shared_ptr<CT>(this);
        return shared_from_this();
    }
};
class CB;

class CA
{
public:
    std::shared_ptr<CB> pcb;

    ~CA()
    {
    }
};

class CB
{
public:
    // std::shared_ptr<CA> pca;
    std::weak_ptr<CA> pca; // 改为弱引用

    ~CB()
    {
    }
};

int main(int argc, char const* argv[])
{
    //  (5.3.2)
    std::shared_ptr<int> p1(new int(100));
    std::shared_ptr<int> p2(std::move(p1)); // p1指向空
    std::shared_ptr<int> p3;
    p3 = std::move(p2); // p2指向空

    // (5.2.4)
    // std::shared_ptr<CA> pca(new CA);
    // std::shared_ptr<CB> pcb(new CB);
    // pca->pcb = pcb;
    // pcb->pca = pca;

    // (5.2.3)
    // std::shared_ptr<CT> pct1(new CT);
    // std::shared_ptr<CT> pct2 = pct1; // 没问题
    // std::shared_ptr<CT> pct2 = pct1->getSelf(); // 有问题

    // (5.2.2)
    // std::shared_ptr<int> myp(new int(100));
    // int* pp = myp.get();
    // delete pp; // 异常
    // std::shared_ptr<int> myp2(pp);

    // (5.2.1)
    // int* p = new int(100); // 裸指针
    // proc(p); // 语法错，int* p不能转换为std::shared_ptr<int>
    // proc(std::shared_ptr<int>(p)); // 参数是个临时的std::shared_ptr<int>，用一个裸指针显示的构造
    // *p = 45; // 潜在的不可预料问题，p指向的内存已经被释放了

    // std::shared_ptr<int> p2(p); // 把一个裸指针绑定到一个shared_ptr上之后，那内存管理的责任就交给了这个shared_ptr，这个时候就不应该再使用裸指针（内置指针）来访问shared_ptr所指向的内存了
    // proc(p2);
    // *p = 45;

    // std::shared_ptr<int> myp(new int(100));
    // proc(myp);
    // *myp = 45;

    // 不要用裸指针初始化多个shared_ptr
    // int* p = new int(100);
    // std::shared_ptr<int> p1(p);
    // std::shared_ptr<int> p2(p); // p1和p2没有关联（p1和p2每个强引用计数都为1），会导致内存被释放两次，产生异常

    // (5.1)
    // myFunc(12);

    // ---------
    // (1 - 2)
    // std::shared_ptr<int> pi; // nullptr
    // std::shared_ptr<int> ptr1(new int(42));
    // std::shared_ptr<int> ptr2 = makes(19);
    // std::shared_ptr<int> ptr3 = std::make_shared<int>(100);
    // std::shared_ptr<string> ptr4 = std::make_shared<string>(5, 'a');

    // std::shared_ptr<int> ptr5 = std::make_shared<int>(); // ptr5指向一个int，int里保存的值是0（值初始化）
    // ptr5 = std::make_shared<int>(400);                   // ptr5指向一个新int；首先释放指向0的内存，然后指向400的内存

    // auto ptr6 = std::make_shared<string>(5, 'a'); // 用auto比较简单

    // (3.1)
    // auto p1 = std::make_shared<int>(100);
    // auto p2(p1);
    // auto p3 = func(p1); // p3:3, p1,p2:3

    // (3.2)
    // p3 = std::make_shared<int>(200); // p3:1, p1,p2:2
    // p2 = std::make_shared<int>(300); // p3:1, p1:1, p2:1
    // p1 = std::make_shared<int>(400);

    // (4.1)
    // std::shared_ptr<int> myp(new int(100));
    // int count = myp.use_count();
    // std::shared_ptr<int> myp2(myp);
    // count = myp.use_count();

    // (4.2)
    // std::shared_ptr<int> myp(new int(100));
    // std::shared_ptr<int> myp2(myp);
    // if (myp.unique())
    //     std::cout << "unique" << std::endl;
    // else
    //     std::cout << "not unique" << std::endl;

    // (4.3)
    // std::shared_ptr<int> pi(new int(100));
    // std::shared_ptr<int> myp2(pi);
    // pi.reset();
    // pi.reset(new int(1));
    // if (nullptr == pi)
    // {
    //     std::cout << "pi is nullptr" << std::endl;
    // }

    // (4.4)
    // std::shared_ptr<int> pother(new int(100));
    // std::cout << *pother << std::endl;

    // (4.5)
    // std::shared_ptr<int> pget(new int(100));
    // int* p = pget.get();
    // *p = 45;

    // (4.6)
    // std::shared_ptr<std::string> ps1(new std::string("hello, world!"));
    // std::shared_ptr<std::string> ps2(new std::string("hello, world."));
    // ps1.swap(ps2);
    // std::swap(ps1, ps2);

    // (4.7)
    // std::shared_ptr<std::string> ps1(new std::string("hello, world!"));
    // std::shared_ptr<std::string> ps2(ps1);
    // ps1 = nullptr;
    // ps2 = nullptr;

    // (4.8)
    // if (ps1) std::cout << "not empty\n";

    // (4.9)
    // std::shared_ptr<int> pd1(new int(100), myDelete);
    // std::shared_ptr<int> pd2(pd1);
    // pd2.reset();
    // pd1.reset();

    // std::shared_ptr<int> pd3(new int[12], [](int* p)
    //                          { delete[] p; });

    // std::shared_ptr<int> pd4(new int[12], std::default_delete<int[]>());
    // std::shared_ptr<int[]> pd5(new int[12]);

    // std::shared_ptr<int> pintArr = make_shared_array<int>(5);
    // std::shared_ptr<A> pAArr = make_shared_array<A>(15);

    return 0;
}