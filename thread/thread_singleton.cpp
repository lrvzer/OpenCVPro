#include <iostream>
#include <mutex>
#include <thread>

std::mutex resource_mutex;
std::once_flag g_falg;

class MyCAS
{
    static void CreateInstance()
    {
        m_instance = new MyCAS();
        static GC gc;
        std::cout << "CreateInstance\n";
    }

private:
    MyCAS() {}

private:
    static MyCAS* m_instance;

public:
    static MyCAS* GetInstance()
    {
        // if (m_instance == nullptr)
        // {
        //     std::unique_lock<std::mutex> mymutex(resource_mutex);
        //     if (m_instance == nullptr)
        //     {
        //         m_instance = new MyCAS();
        //         static GC gc;
        //     }
        // }
        std::call_once(g_falg, CreateInstance); // 两个线程同时执行到这里，其中一个线程要等另一个线程执行完毕CreateInstance
        return m_instance;
    }

    class GC
    {
    public:
        ~GC()
        {
            if (m_instance != nullptr)
            {
                std::cout << "delete\n";
                delete m_instance;
                m_instance = nullptr;
            }
        }
    };

    void func()
    {
        std::cout << "func()" << std::endl;
    }
};

// 类静态变量初始化
MyCAS* MyCAS::m_instance = nullptr;

void myThread()
{
    MyCAS* a = MyCAS::GetInstance();
    std::cout << "thread id [" << std::this_thread::get_id() << "] address " << a << std ::endl;
    a->func();
}

int main(int argc, char const* argv[])
{
    // MyCAS* a = MyCAS::GetInstance();
    // MyCAS* b = MyCAS::GetInstance();

    // std::cout << a << std::endl;
    // std::cout << b << std::endl;

    // a->func();

    std::thread th1(myThread);
    std::thread th2(myThread);

    th1.join();
    th2.join();
    return 0;
}
