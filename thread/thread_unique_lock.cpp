#include <iostream>
#include <list>
#include <mutex>
#include <thread>
#include <vector>

/***
 * 一、unique_lock取代lock_gurad
 *
 * 二、unique_lock的第二个参数
 * (2.1) std::adopt_lock
 *       使用该参数需要提前将互斥量lock
 *       标记效果，不需要在构造函数中对互斥量进行lock操作
 * (2.2) std::try_to_lock
 * (2.3) std::defer_lock
 *       初始化一个没有加锁的mutex
 *
 * 三、unique_lock的成员函数
 * (3.1) lock()
 * (3.2) unlock()
 * (3.3) try_lock(): 不阻塞
 * (3.4) release()
 *       返回它所管理的mutex对象指针，并释放所有权，即与unique_lock不再有联系
 */

class A
{
public:
    // 把收到的消息写到一个队列的线程
    void inMsgRecvQueue()
    {
        for (int i = 0; i < 10000; i++)
        {
            std::cout << "inMsgRecvQueue executed, insert elem" << i << std::endl;

            // std::lock_guard<std::mutex> mguard(m_mutex);

            // m_mutex.lock(); // 先lock，再使用std::adopt_lock参数
            // std::unique_lock<std::mutex> mguard_u(m_mutex, std::adopt_lock);

            // std::unique_lock<std::mutex> mguard_u(m_mutex, std::try_to_lock);
            // if (mguard_u.owns_lock())
            // {
            //     msgRecQueue.push_back(i);
            // }
            // else
            // {
            //     std::cout << "inMsgRecvQueue not lock\n";
            // }

            // std::unique_lock<std::mutex> mguard_u(m_mutex, std::defer_lock);
            // mguard_u.lock(); // 不用关心unlock
            // mguard_u.unlock();
            // // TODO：非共享代码
            // mguard_u.lock();

            // if (mguard_u.try_lock())
            // {
            //     msgRecQueue.push_back(i);
            // }

            std::unique_lock<std::mutex> mguard_u(m_mutex);
            std::mutex* ptx = mguard_u.release();
            ptx->lock();
            msgRecQueue.push_back(i);
            ptx->unlock();
        }
    }

    bool outMsgLULPro(int& command)
    {
        // std::lock_guard<std::mutex> mguard(m_mutex);
        std::unique_lock<std::mutex> mguard(m_mutex);

        // std::chrono::milliseconds dura(200);
        // std::this_thread::sleep_for(dura); // 休息200ms

        if (!msgRecQueue.empty())
        {
            command = msgRecQueue.front(); // 返回第一个元素，但不检查元素是否存在
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
    std::mutex m_mutex;
    std::mutex m_mutex1;
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
