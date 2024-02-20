#include <iostream>
#include <thread>

/***
 * 整个进程是否执行完毕的标志是主线程是否执行完成。
 * 一般情况下，如果其他子线程还没有执行完毕，那么这些子线程也会被操作系统强行终止。
 *
 * a> 包含头文件 <thread>
 * b> 创建函数
 * c>
 */
void myPrint()
{
    std::cout << "sub thread is running\n";
}

class TA
{
public:
    int& m_i;

    TA(int& mi) : m_i(mi)
    {
        std::cout << "TA custom constructor\n";
    }

    TA(const TA& other) : m_i(other.m_i)
    {
        std::cout << "TA copy constructor\n";
    }

    ~TA()
    {
        std::cout << "TA destructor\n";
    }

    void operator()()
    {
        // std::cout << "TA sub thread is running\n";
        std::cout << "m_i:" << m_i << '\n';
        std::cout << "m_i:" << m_i << '\n';
    }
};

int main(int argc, char const* argv[])
{
#if 0
    // create 1
    std::thread th(myPrint); // 1.创建线程，执行起点（入口）myPrint() 2.线程执行
    std::cout << th.joinable() << '\n';
    // th.join();               // 阻塞主线程，等待子线程执行完成
    th.detach(); // th线程与主线程失去联系，被C++运行时库接管，当这个子线程执行完毕后，由运行时库负责清理该线程相关的资源（守护线程）
    // 一旦使用detach，就不能在使用join了
    std::cout << th.joinable() << '\n';
#endif

#if 0
    // create 2
    // int mc = 6;
    // TA ta(mc);
    // std::thread th2(ta);
    // th2.join();
    /**
     * 一个问题
     * 调用了detach，主线程执行结束，ta对象就不存在了
     * std::thread th2(ta)，ta会被复制到线程中去，尽管主线程中的ta被释放了，线程中复制的TA对象依然存在的
     *                      复制操作可以通过TA类的拷贝构造函数观测到
     * 所以，只要TA类对象里没有引用，没有指针，那么就不会产生问题
     */
#endif

#if 1
    // create 3
    auto mlt = []
    {
        std::cout << "lambda sub thread is running\n";
    };
    std::thread th3(mlt);
    th3.join();
#endif

    std::cout << "main thread is running\n";
    return 0;
}