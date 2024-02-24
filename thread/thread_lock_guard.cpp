#include <iostream>
#include <list>
#include <mutex>
#include <thread>
#include <vector>

// 本类用于自动释放windows下的临界区，防止忘记LeaveCriticalSection导致死锁情况的发生
#ifdef __WINDOWS_S__
class CWinLock
{
public:
    CWinLock(CRITICAL_SECTION* pCritmp)
    {
        m_win_mutex = pCritmp;
        EnterCriticalSection(m_win_mutex)
    }

    ~CWinLock()
    {
        LeaveCriticalSection(m_win_mutex);
    }

private:
    CRITICAL_SECTION* m_win_mutex;
};
#endif
class A
{
public:
    // 把收到的消息写到一个队列的线程
    void inMsgRecvQueue()
    {
        for (int i = 0; i < 10000; i++)
        {
            std::cout << "inMsgRecvQueue executed, insert elem" << i << std::endl;
            // m_mutex.lock();
            std::lock(m_mutex1, m_mutex2);
            std::lock_guard<std::mutex> mguard1(m_mutex1, std::adopt_lock);
            std::lock_guard<std::mutex> mguard2(m_mutex2, std::adopt_lock);
            msgRecQueue.push_back(i);
            // m_mutex.unlock();
            // m_mutex1.unlock();
            // m_mutex2.unlock();
        }
    }

    bool outMsgLULPro(int& command)
    {
        // std::lock_guard<std::mutex> mguard(m_mutex); // std::lock_guard构造函数执行了m_mutex.lock() 析构函数执行了m_mutex.unlock()
        std::lock(m_mutex1, m_mutex2);
        std::lock_guard<std::mutex> mguard1(m_mutex1, std::adopt_lock);
        std::lock_guard<std::mutex> mguard2(m_mutex2, std::adopt_lock);
        // m_mutex.lock();
        if (!msgRecQueue.empty())
        {
            command = msgRecQueue.front(); // 返回第一个元素，但不检查元素是否存在
            msgRecQueue.pop_front();
            // m_mutex.unlock();
            // m_mutex1.unlock();
            // m_mutex2.unlock();
            return true;
        }
        // m_mutex.unlock();
        // m_mutex1.unlock();
        // m_mutex2.unlock();
        return false;
    }

    // 把数据从消息队列中取出的线程
    void outMsgRecvQueue()
    {
        int command = 0;
        for (int i = 0; i < 10000; i++)
        {
            bool result = outMsgLULPro(command);
            if (result)
            {
                std::cout << "outMsgRecvQueue executed, msgRecQueue pop_front " << command << std::endl;
            }
            else
            {
                std::cout << "outMsgRecvQueue executed, msgRecQueue is empty " << i << std::endl;
            }
        }

        std::cout << "end" << std::endl;
    }

private:
    std::list<int> msgRecQueue;
    std::mutex m_mutex;
    std::mutex m_mutex1;
    std::mutex m_mutex2;
};

int main(int argc, char const* argv[])
{
    /***
     * 保护共享数据
     * 一、互斥量（mutex）的基本概念
     * 二、互斥量用法
     * 引入`#include <mutex>`
     * (2.1) lock(), unlock()
     *       成对使用
     * (2.2) std::lock_guard(): 直接取代lock()和unlock()
     * 三、死锁
     * (3.3) std::lock()
     *       能力：一次锁住两个或者两个以上的互斥量，他不存在因为在多个线程中，因为锁的顺序问题导致死锁的风险问题
     *       如果互斥量中有一个没有锁住，那就会等待，等所有互斥量都锁住，才能继续往下执行
     *       要么都锁住，要么都没锁住，如果锁住一个，另一个没有锁住成功，它会立即将锁定的锁进行解锁
     * (3.4) std::lock_guard的std::adopt_lock参数，表示被lock过了，不需要再次lock了
     */
    A myObj;
    std::thread myOutMsgObj(&A::outMsgRecvQueue, &myObj);
    std::thread myInMsgObj(&A::inMsgRecvQueue, &myObj);

    myOutMsgObj.join();
    myInMsgObj.join();

    return 0;
}
