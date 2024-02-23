#include <atomic>
#include <iostream>
#include <mutex>
#include <thread>

/**
 * std::atomic
 * (3.1) 原子操作概念引出范例
 *       互斥量：保护共享数据
 * (3.2) 叙谈
 *       一般atomic原子操作，针对 ++, --, +=, &=, |=, ^=是支持的
 */

// int g_count = 0;
std::atomic<int> g_count = 0;

// std::mutex g_mutex;

void add()
{
    for (size_t i = 0; i < 1000000; i++)
    {
        // 2000w次加锁和解锁
        // g_mutex.lock();
        g_count++; // 原子操作，不会被打断 std::atomic<int>
        // g_count += 1;
        // g_count = g_count + 1; // 不是原子操作
        // g_mutex.unlock();
    }
}

std::atomic<bool> g_ifend = false; // 线程退出标记

void run()
{
    std::chrono::milliseconds dura(1000);
    while (!g_ifend)
    {
        std::cout << "<thread:" << std::this_thread::get_id() << "> is running\n";
        std::this_thread::sleep_for(dura);
    }
    std::cout << "<thread:" << std::this_thread::get_id() << "> is stoped\n";
}

int main(int argc, char const* argv[])
{
    // std::thread th1(add);
    // std::thread th2(add);
    // th1.join();
    // th2.join();

    // std::cout << "g_count [" << g_count << "]" << std::endl;

    std::thread th1(run);
    std::thread th2(run);
    std::chrono::milliseconds dura(5000);
    std::this_thread::sleep_for(dura);
    g_ifend = true;
    th1.join();
    th2.join();
    std::cout << "Run Over!" << std::endl;
    return 0;
}