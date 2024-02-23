#include <chrono>
#include <future> // std::async, std::future
#include <iostream>
#include <thread>
#include <vector>

/***
 * std::packaged_task
 * 类模板
 */
int execute(const std::string& thread_name)
{
    std::cout << thread_name << " Thread-" << std::this_thread::get_id() << std::endl;
    std::chrono::milliseconds dura(5000);
    std::this_thread::sleep_for(dura);
    std::cout << thread_name << " Thread-" << std::this_thread::get_id() << std::endl;
    return 5;
}

std::vector<std::packaged_task<int(const std::string&)>> tasks;

int main(int argc, char const* argv[])
{
    std::cout << "Main Thread-" << std::this_thread::get_id() << std::endl;
    // std::packaged_task<int(const std::string&)> task(execute);

    auto func = [](const std::string& thread_name) -> int
    {
        std::cout << thread_name << " Thread-" << std::this_thread::get_id() << std::endl;
        std::chrono::milliseconds dura(5000);
        std::this_thread::sleep_for(dura);
        std::cout << thread_name << " Thread-" << std::this_thread::get_id() << std::endl;
        return 5;
    };
    std::packaged_task<int(const std::string&)> task(func);
    // std::future<int> futrue = task.get_future();
    // std::thread th(std::move(task), "Exec");
    // th.join();

    // // task("Exec"); // 函数调用

    // int ret = futrue.get();
    // std::cout << "ret: " << ret << std::endl;
    tasks.push_back(std::move(task));
    std::packaged_task<int(const std::string&)> task2;
    auto iter = tasks.begin();
    task2 = std::move(*iter);
    tasks.erase(iter);
    task2("TASK2");

    std::future<int> futrue = task2.get_future();
    int ret = futrue.get();
    std::cout << "ret: " << ret << std::endl;
    return 0;
}
