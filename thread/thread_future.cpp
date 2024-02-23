#include <chrono>
#include <future> // std::async, std::future
#include <iostream>
#include <thread>

/**
 * std::future
 * 成员函数
 * get():
 *  阻塞线程，等待线程返回结果
 *  只能执行一次，调用多次会异常
 * wait(): 等待线程返回，并不返回结果
 *
 * std::future_status
 * std::shared_future
 */

int execute(const std::string& thread_name)
{
    std::cout << thread_name << " Thread-" << std::this_thread::get_id() << std::endl;
    std::chrono::milliseconds dura(5000);
    std::this_thread::sleep_for(dura);
    std::cout << thread_name << " Thread-" << std::this_thread::get_id() << std::endl;
    return 5;
}

int main(int argc, char const* argv[])
{
    std::cout << "Main Thread-" << std::this_thread::get_id() << std::endl;
    std::future<int> future = std::async(std::launch::deferred, execute, std::string("Exec"));
    std::cout << "continue...\n";
    // std::cout << "Exec Thread returns " << ret.get() << "\n"; // 阻塞
    std::future_status status = future.wait_for(std::chrono::seconds(6));
    if (status == std::future_status::timeout) // 超时
    {
        std::cout << "thread execute timeout.\n";
    }
    else if (status == std::future_status::ready)
    {
        std::cout << "thread execute completed\n";
    }
    else if (status == std::future_status::deferred) // std::launch::deferred
    {
        std::cout << "result = " << future.get() << "\n";
        std::cout << "thread deferred\n";
    }
    std::cout << "Main Thread Over\n";
    return 0;
}