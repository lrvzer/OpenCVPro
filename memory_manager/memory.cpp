#include <iostream>
#include <vector>

int main(int argc, char const* argv[])
{
    /***
     * 直接内存管理（new delete）
     *
     * new 分配方式我们称为动态分配（分配在堆上）
     *
     * 概念 "值初始化"，使用"()"来初始化
     */
    // int* pointi = new int;                // 初值未定义
    // std::string* mystr = new std::string; // 空字符串，调用了std::string默认构造函数
    // int* pointi = new int(100); // 用圆括号给一个int的动态对象初值
    // // std::string* mystr = new std::string(5, 'a'); // "aaaaa"
    // std::vector<int>* pointerv = new std::vector<int>{ 1, 2, 3, 4, 5 };
    // std::string* mystr = new std::string{};
    // delete pointi;
    // delete mystr;
    // delete pointerv;

    // c++11中，auto和new配合使用
    std::string* str1 = new std::string(5, 'a');
    std::cout << *str1 << std::endl;
    // auto str2 = new auto(str1);
    // delete str2;
    delete str1;

    // const对象也可以动态分配
    const int* pointci = new const int(200);
    delete pointci;
    return 0;
}
