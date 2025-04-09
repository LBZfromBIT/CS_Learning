#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <cstdlib>


const int BUFFER_SIZE = 6;//缓冲区大小
const int STRING_LENGTH = 10;//缓冲单元中字符串长度
const int PRODUCER_COUNT = 2;//生产者数量
const int CONSUMER_COUNT = 3;//消费者数量
const int PRODUCE_TIMES = 12;//每个生产者生产次数
const int CONSUME_TIMES = 8;//每个消费者消费次数

/// @brief 缓冲区 
std::vector<std::string> buffer(BUFFER_SIZE);
int produceIndex = 0;//生产位置索引,采用循环顺序写入
int consumeIndex = 0;//消费位置索引，采用循环顺序读出

HANDLE emptySlots;  // 信号量，表示空槽位
HANDLE fullSlots;   // 信号量，表示满槽位
HANDLE bufferMutex; // 互斥锁，用于保护缓冲区访问


/// @brief 随机休眠函数
void randomSleep() {
    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1000 + 500));
}

/// @brief 获取当前时间
std::string getCurrentTime() {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()) % 1000;
    char buffer[26];
    ctime_s(buffer, sizeof(buffer), &time);
    std::string timeStr(buffer);
    timeStr = timeStr.substr(11, 8) + "." + 
              std::to_string(ms.count());
    return timeStr;
}

///@brief 显示缓冲区状态
void printBuffer() {
    std::cout << "Buffer status: [";
    for (int i = 0; i < BUFFER_SIZE; ++i) {
        if (buffer[i].empty()) {
            std::cout << "Empty";
        } else {
            std::cout << buffer[i];
        }
        if (i < BUFFER_SIZE - 1) std::cout << " | ";
    }
    std::cout << "]" << std::endl;
}


/// @brief 生产者功能函数
/// @param id 进程id
void producer(int id) {
    for (int i = 0; i < PRODUCE_TIMES; ++i) {
        randomSleep();
        std::string data(STRING_LENGTH, 'A' + rand() % 26);//生成一个随机大写字母的字符串

        WaitForSingleObject(emptySlots, INFINITE); // 等待空槽
        WaitForSingleObject(bufferMutex, INFINITE); // 获取互斥锁

        buffer[produceIndex] = data;
        std::cout << "["<< getCurrentTime() << "][Producer" << id << "] Produced: " 
        << data<< " at index " << produceIndex << std::endl;
        printBuffer();
        produceIndex = (produceIndex + 1) % BUFFER_SIZE;

        ReleaseMutex(bufferMutex); // 释放互斥锁
        ReleaseSemaphore(fullSlots, 1, NULL); // 增加满槽计数
    }
}

/// @brief 消费者功能函数
/// @param id 进程id
void consumer(int id) {
    for (int i = 0; i < CONSUME_TIMES; ++i) {
        randomSleep();

        WaitForSingleObject(fullSlots, INFINITE); // 等待满槽
        WaitForSingleObject(bufferMutex, INFINITE); // 获取互斥锁

        std::string data = buffer[consumeIndex];
        buffer[consumeIndex] = "";
        std::cout <<"["<< getCurrentTime() << "][Consumer " << id << "] Consumed: " << data
                  << " at index " << consumeIndex << std::endl;
        printBuffer();
        consumeIndex = (consumeIndex + 1) % BUFFER_SIZE;

        ReleaseMutex(bufferMutex); // 释放互斥锁
        ReleaseSemaphore(emptySlots, 1, NULL); // 增加空槽计数
    }
}


/// @brief 主函数，创建进程和信号量
int main() {
    // 初始化随机数种子
    srand((unsigned)time(NULL));

    emptySlots = CreateSemaphore(NULL, BUFFER_SIZE, BUFFER_SIZE, NULL);//初值为BUFFER_SIZE，最大值为BUFFER_SIZE
    fullSlots = CreateSemaphore(NULL, 0, BUFFER_SIZE, NULL);//初值为0，最大值为BUFFER_SIZE
    bufferMutex = CreateMutex(NULL, FALSE, NULL);//互斥锁,初值为FALSE

    std::vector<std::thread> producers, consumers;//线程容器

    for (int i = 0; i < PRODUCER_COUNT; ++i) {
        producers.emplace_back(producer, i + 1);//追加生产者线程
    }
    for (int i = 0; i < CONSUMER_COUNT; ++i) {
        consumers.emplace_back(consumer, i + 1);//追加消费者线程
    }

    for (auto& th : producers) {
        th.join();//等待线程结束
    }
    for (auto& th : consumers) {
        th.join();//等待线程结束
    }

    CloseHandle(emptySlots);
    CloseHandle(fullSlots);
    CloseHandle(bufferMutex);

    return 0;
}
