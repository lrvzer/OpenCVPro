#include <iostream>
#include <thread>

class A
{
public:
    A(int i) : m_i(i)
    {
        std::cout << "A(int i)          address [" << this << "] thread ID [" << std::this_thread::get_id() << "]\n";
    }

    A(const A& other) : m_i(other.m_i)
    {
        std::cout << "A(const A& other) address [" << this << "] thread ID [" << std::this_thread::get_id() << "] other address " << &other << "\n";
    }

    ~A()
    {
        std::cout << "~A()              address [" << this << "] thread ID [" << std::this_thread::get_id() << "]\n";
    }

    void thread_work(int num)
    {
        std::cout << "sub thread ID  = " << std::this_thread::get_id() << " num = " << num << "\n";
    }

    void operator()(int num)
    {
        std::cout << "sub() thread ID  = " << std::this_thread::get_id() << " num = " << num << "\n";
    }

    // int m_i;
    mutable int m_i;
};

// void myPrint(const int& i, char* pmybuf)
// void myPrint(const int i, char* pmybuf)
void myPrint(const int i, const std::string& pmybuf)
{
    std::cout << "i      = " << i << '\n'; // 实际为值传递
    std::cout << "pmybuf = " << pmybuf << '\n';
    return;
}

// void myPrint2(const int i, const A pmybuf)
void myPrint2(const int i, const A& pmybuf)
{
    pmybuf.m_i = 199;                              // 修改该值不会影响main函数中的值
    std::cout << "i              = " << i << '\n'; // 实际为值传递
    std::cout << "pmybuf         = " << pmybuf.m_i << '\n';
    std::cout << "pmybuf address = " << &pmybuf << '\n';
    std::cout << "sub thread ID  = " << std::this_thread::get_id() << "\n";
    return;
}

void myPrint3(std::unique_ptr<int> pmybuf)
{
}

int main(int argc, char const* argv[])
{
    // 传递临时对象作为线程参数
    // 事实1：只要是用临时构造的A类对象作为参数传递给线程，那么就一定能够在主线程执行完毕之前把线程函数的第二个参数构建出来，从而确保即使detach()，也能保证子线程安全运行
    int mvar = 10;
    int& mvary = mvar;
    char pmybuf[] = "hello, world!";
    // std::thread th(myPrint, mvar, pmybuf);
    // std::thread th(myPrint, mvar, std::string(pmybuf)); // 可以保证在线程中有效

    // std::thread th(myPrint2, mvar, 12);
    // std::thread th(myPrint2, mvar, A(12)); // 可以保证在线程中有效

    // A a(12);
    // std::thread th(myPrint2, mvar, a); // 将类对象作为线程参数
    // std::thread th(myPrint2, mvar, std::ref(a)); // 将类对象作为线程参数
    // std::unique_ptr<int> myp(new int(100));
    // std::thread th(myPrint3, std::move(myp));

    A a(12);
    // std::thread th(&A::thread_work, a, 15); // &a == std::ref(a)
    std::thread th(a, 15);

    th.join();
    // th.detach();
    std::cout << "main thread ID = " << std::this_thread::get_id() << "\n";
    std::cout << "main thread is running\n";
    return 0;
}