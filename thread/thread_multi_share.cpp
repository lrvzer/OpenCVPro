#include <iostream>
#include <thread>
#include <vector>

std::vector<int> g_v = { 1, 2, 3 };

void MyPrint(int inum)
{
    // std::cout << "sub thread start. num = " << inum << std::endl;
    std::cout << "Thread ID[" << std::this_thread::get_id() << "] g_v[0]: " << g_v[0] << std::endl;
    return;
}

int main(int argc, char const* argv[])
{
    // 一、创建和等待多个线程
    // a> 多个线程执行顺序是乱的，跟操作系统内部对线程的运行调度机制有关
    // b> 主线程等待所有子线程运行结束，最后主线程结束，推荐使用join()的方法，更容易写出稳定的程序
    // c> 由容器对线程进行管理
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; i++)
    {
        threads.push_back(std::thread(MyPrint, i));
    }

    for (auto iter = threads.begin(); iter != threads.end(); ++iter)
    {
        iter->join();
    }

    // (2) 数据共享问题分析
    // (2.1) 只读的数据

    std::cout << "main thread is running\n";
    return 0;
}
