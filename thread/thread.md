# 并发与多线程

## 一、线程启动、结束，创建线程多种方法、join、detach

### (1) 范例演示线程运行的开始和结束

#### (1.1) thread

#### (1.2) join()

阻塞主线程，等待子线程执行完成

#### (1.3) detach()

传统多线程程序主线程要等待子线程执行完毕，引入detach，主线程无需和子线程汇合

使用detach()后，子线程与主线程失去联系，被C++运行时库接管，当这个子线程执行完毕后，由运行时库负责清理该线程相关的资源（守护线程）

#### (1.4) joinable()

判断是否可以成功使用join()或者detach()

### (2) 其他创建线程的手法

#### (2.1) 用类，以及一个问题范例

#### (2.2) 用lambda表达式


## 二、线程传参详解，detach()大坑，成员函数做线程函数

### (1) 传递临时对象作为线程参数

#### (1.1) 要避免的陷阱(解释1)

#### (1.2) 要避免的陷阱(解释2)

#### (1.3) 总结

- 若传递int这种简单类型参数，建议都是值传递，不要使用引用

- 如果传递类对象，避免隐式类型转换；全部都在创建线程时，就构建出临时对象，然后在函数参数里，用引用来接，否则系统会多构建一个对象，造成浪费

- 建议不使用detach()，只使用join()，这样就不存在局部变量失效，导致线程对内存的非法引用问题

### (2) 临时对象作为线程参数继续讲

#### (2.1) 线程id概念

std::this_thread::get_id()获取

#### (2.2) 临时对象构造时机抓捕

### (3) 传递类对象、智能指针作为线程参数

std::ref()函数

### (4) 用成员函数指针做线程函数

## 三、创建多个线程、数据共亨问题分析、案例代码

### (1) 创建和等待多个线程

- 多个线程执行顺序是乱的，跟操作系统内部对线程的运行调度机制有关
- 主线程等待所有子线程运行结束，最后主线程结束，推荐使用join()的方法，更容易写出稳定的程序
- 由容器对线程进行管理

### (2) 数据共享问题分析

#### (2.1) 只读的数据 - 安全稳定

#### (2.2) 有读有写

#### (2.3) 其他案例

### (3) 共享数据的保护案例代码


std::async
std::future
std::packaged_task
std::promise

std::atomic
- load()
- store()


std::async和std::thread区别
 * std::thread() 如果资源紧张，那么创建线程可能失败，那么执行std::thread()时整个程序可能崩溃
 * std::async() 一般叫做 创建异步任务，有时候并不会创建线程

一、windows临界区，类似std::mutex
```c++
#define __WINDOWS_S__

#ifdef __WINDOWS_S__
    CRITICAL_SECTION m_win_mutex;
    InitializeCriticalSection(&m_win_mutex);
    EnterCriticalSection(&m_win_mutex);
    LeaveCriticalSection(&m_win_mutex);
#endif

```
二、多次进入临界区实验

- 在"同一个线程"中，windows中的"相同临界区变量"代表的临界区进入(EnterCriticalSection)可以被多次调用，而离开(LeaveCriticalSection)临界区时也需要多次调用
- C++11中，不允许同一个线程中lock同一个互斥量多次，否则报异常

三、自动析构技术

四、std::recursive_mutex递归的独占互斥量

五、带有超时的互斥量std::timed_mutex和std::recursive_timed_mutex

try_lock_for(): 参数是一段时间，是等待一段时间
try_lock_until(): 参数是一个未来的时间点