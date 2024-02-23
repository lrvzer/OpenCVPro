#include <chrono>
#include <future> // std::async, std::future
#include <iostream>
#include <thread>
#include <vector>

/***
 * std::promise
 * 能够在一个线程中赋值，在另一个线程中取值使用
 */

int execute(const std::string& thread_name, std::promise<int>& tmpp, int calc)
{
    std::cout << thread_name << " Thread-" << std::this_thread::get_id() << std::endl;
    std::chrono::milliseconds dura(5000);
    std::this_thread::sleep_for(dura);

    calc++;
    calc *= 10;
    int result = calc;
    tmpp.set_value(result);

    std::cout << thread_name << " <Thread:" << std::this_thread::get_id() << ">" << std::endl;
    return 5;
}

// void run(std::future<int>& tmpf)
void run(std::shared_future<int>& tmpf)
{
    auto result = tmpf.get();
    std::cout << "<Thread:" << std::this_thread::get_id() << "> result = " << result << std::endl;
    return;
}

int main(int argc, char const* argv[])
{
    std::cout << "<Thread:" << std::this_thread::get_id() << ">" << std::endl;
    std::promise<int> myprom;
    std::thread th1(execute, "Exec", std::ref(myprom), 180);
    th1.join();

    // std::future<int> ful = myprom.get_future();

    // std::cout << "Before: " << ful.valid() << std::endl;
    // // std::shared_future<int> result_s(std::move(ful));
    // std::shared_future<int> result_s(ful.share());
    // std::cout << "After : " << ful.valid() << std::endl;
    // std::cout << "result: " << result_s.get() << std::endl;

    std::shared_future<int> result_s(myprom.get_future());

    // auto result = ful.get();
    // std::cout << "result = " << result << std::endl;

    // std::thread th2(run, std::ref(ful));
    std::thread th2(run, std::ref(result_s));
    th2.join();
    return 0;
}