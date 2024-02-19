#include <iostream>

/**
 * 1.weak_ptr创建
 * 2.weak_ptr常用操作
 *  2.1 use_count(): 获取与该弱指针共享对象的其他shared_ptr的数量，或者说获得当前所观测资源的强引用计数
 *  2.2 expired(): 是否过期。判断所观测的资源是否已经被释放
 *  2.3 reset(): 将弱引用指针设置为空
 *  2.4 lock()
 * 3.尺寸问题
 *  与shared_ptr尺寸一样，是裸指针的2倍
 */
int main(int argc, char const* argv[])
{
    // auto pi = std::make_shared<int>(100);
    // std::weak_ptr<int> piw(pi);
    // pi.reset();
    // auto pi2 = piw.lock();
    // if (pi2)
    // {
    //     *pi2 = 10;
    // }
    // else
    // {
    //     std::cout << "lock failure\n";
    // }

    // auto pi = std::make_shared<int>(100);
    // auto pi1(pi);
    // std::weak_ptr<int> piw(pi);
    // std::cout << piw.use_count() << "\n";

    // pi.reset();
    // pi1.reset();

    // if (piw.expired())
    // {
    //     std::cout << "resouce released\n";
    // }

    // piw.reset();

    // 3
    std::weak_ptr<int> pw;
    int* p;
    std::cout << sizeof(pw) << std::endl;
    std::cout << sizeof(p) << std::endl;
    return 0;
}