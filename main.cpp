#include "Logger.h"
#include <functional>

void fun(const std::string s) {
    for (size_t i = 0; i < 10000; i++)
    {
        std::this_thread::sleep_for(std::chrono::microseconds(200));
        Logger::i()->console(s + "\tConsole log");
    }

}

int main() {
    Logger::i()->LogFileInitialize("log.log");

    std::shared_ptr<AbstractLogger> l = Logger::i();

    std::string c = "Console::log";

    std::thread t1(fun, "🔴");
    std::thread t2(fun, "🟡");
    std::thread t3(fun, "🔘");
    std::thread t4(fun, "🟦");
    std::thread t5(fun, "🍆");
    std::thread t6(fun, "⚠️");
    t6.join();
    t5.join();
    t4.join();
    t1.join();
    t2.join();
    t3.join();

    return 0;
}