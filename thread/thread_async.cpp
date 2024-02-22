#include <future> // std::async, std::future
#include <iostream>
#include <thread>

/**
 * std::async 函数模板，用来启动一个异步任务，返回 std::future对象
 * std::future
 * 成员函数
 * get():
 *  等待线程返回，返回结果
 *  只能执行一次，调用多次会异常
 * wait(): 等待线程返回，并不返回结果
 */

class A
{
public:
    int execute(const std::string& thread_name)
    {
        std::cout << thread_name << " Thread-" << std::this_thread::get_id() << std::endl;
        std::chrono::milliseconds dura(5000);
        std::this_thread::sleep_for(dura);
        std::cout << thread_name << " Thread-" << std::this_thread::get_id() << std::endl;
        return 5;
    }
};

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
    // std::future<int> ret = std::async(execute, std::string("Exec"));
    A a;
    std::future<int> ret = std::async(&A::execute, &a, std::string("ACls"));
    std::cout << "continue...\n";
    std::cout << "Exec Thread returns " << ret.get() << "\n"; // 阻塞
    // std::cout << "Exec Thread returns " << ret.get() << "\n"; // 阻塞
    std::cout << "Main Thread Over\n";
    return 0;
}