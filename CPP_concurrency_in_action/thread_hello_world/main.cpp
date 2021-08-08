#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

void func() {
    std::cout << "hello world with concurrent." << std::endl;
}

class thread_func {
    public:
        void operator()() const
        {
            std::cout << "hello world with thread function." << std::endl;
        }
};

class Value {
    private:
        int value = 0;
    public:
        void SetValue(int val) {
            value = val;
        }
        int GetValue() {
            return value;
        }
};

void once_func() {
    std::cout << "hello world once." << std::endl;
}

void func2(int id, std::string value) {
    std::cout << "hello world with id = " << id << ", value = " << value << std::endl;
}

void func3(Value& val) {
    val.SetValue(100);
}

int main() {
    std::thread t(func);
    std::cout << "hello world in main." << std::endl;

    thread_func f;
    std::thread t2(f);

    std::thread t3(thread_func());
    std::thread t4{thread_func()};
    std::thread t5((thread_func()));    // 2

    std::thread t6(func2, 1, "test");
    
    t6.join();
    t5.join();
    t4.join();
    t2.join();
    t.join();

    char tmp[100];
    tmp[0] = '\0';
    std::thread t7(func2, 1, std::string(tmp));
//    t7.detach();

    std::thread t8 = std::move(t7);
    t7 = std::thread(func2, 1, "hello world");
    t7.join();

    t7 = std::move(t8);

    t7.join();

    std::vector<std::thread> threads;
    for (int i = 0; i < 10; i ++) {
        threads.push_back(std::thread(func2, i, ""));
    }
    std::for_each(threads.begin(), threads.end(), [&](std::thread& t) {t.join(); });

    std::cout << std::thread::hardware_concurrency() << std::endl;

    std::cout << t7.get_id() << std::endl;

    std::once_flag once_flag_1;
    std::call_once(once_flag_1, once_func);
    std::call_once(once_flag_1, once_func);

    std::once_flag once_flag_2;
    std::call_once(once_flag_2, once_func);
    return 0;
}
