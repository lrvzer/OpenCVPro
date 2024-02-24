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
            std::lock_guard<std::recursive_mutex> mguard(m_recursive_mutex);
            msgRecQueue.push_back(i);
        }
    }

    bool outMsgLULPro(int& command)
    {
        std::lock_guard<std::recursive_mutex> mguard(m_recursive_mutex);
        if (!msgRecQueue.empty())
        {
            command = msgRecQueue.front();
            msgRecQueue.pop_front();
            return true;
        }
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
    std::recursive_mutex m_recursive_mutex;
};

int main(int argc, char const* argv[])
{
    A myObj;
    std::thread myOutMsgObj(&A::outMsgRecvQueue, &myObj);
    std::thread myInMsgObj(&A::inMsgRecvQueue, &myObj);

    myOutMsgObj.join();
    myInMsgObj.join();

    return 0;
}
