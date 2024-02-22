#include <iostream>
#include <list>
#include <mutex>
#include <thread>
#include <vector>

/***
 * 一、std::condition_variable, wait(), notify_one()
 *    std::condition_variable
 */

class A
{
public:
    // 把收到的消息写到一个队列的线程
    void inMsgRecvQueue()
    {
        for (int i = 0; i < 10000; i++)
        {
            std::cout << "inMsgRecvQueue executed, insert elem" << i << " thread ID " << std::this_thread::get_id() << std::endl;
            std::unique_lock<std::mutex> mguard(m_mutex);
            msgRecQueue.push_back(i);
            m_cond.notify_one();
        }
    }

    // 把数据从消息队列中取出的线程
    void outMsgRecvQueue()
    {
        int command = 0;
        auto pred = [this]
        {
            if (!msgRecQueue.empty())
            {
                return true;
            }
            return false;
        };

        while (true)
        {
            std::unique_lock<std::mutex> mguard(m_mutex);
            // 如果wait()有第二参数，pred返回值为false时，那么就会解锁互斥量，并堵塞在本行
            //                        返回true时，继续执行，不阻塞，有锁
            //  无第二参数时，与pred返回值为false时一样
            m_cond.wait(mguard, pred); // 等待其他线程 调用notify_one()

            command = msgRecQueue.front();
            msgRecQueue.pop_front();

            mguard.unlock();
            std::cout << "outMsgRecvQueue command " << command << " thread ID " << std::this_thread::get_id() << std::endl;
        }

        std::cout << "end" << std::endl;
    }

private:
    std::list<int> msgRecQueue;
    std::mutex m_mutex;
    std::condition_variable m_cond;
};

int main(int argc, char const* argv[])
{
    A myObj;
    std::thread myOutMsgObj1(&A::outMsgRecvQueue, &myObj);
    std::thread myOutMsgObj2(&A::outMsgRecvQueue, &myObj);
    std::thread myInMsgObj(&A::inMsgRecvQueue, &myObj);

    myOutMsgObj1.join();
    myOutMsgObj2.join();
    myInMsgObj.join();

    return 0;
}
