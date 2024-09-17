#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include <memory>
#include <mutex>
#include <chrono>
#include <iomanip>
#include "File.h"

#define threadsafe // включить потокобезопасность

class AbstractLogger
{
private:
#ifdef threadsafe
    std::mutex mutex;
#endif
    std::unique_ptr<File> log_file;
    bool log_file_init = false;
public:
    virtual ~AbstractLogger() = 0;
    void LogFileInitialize(const std::string& file_path, mode_t perms = 0600);

#ifdef threadsafe

    void test() {
        console("test");
    }
    /**
     * @brief Записывает лог в консоль. std::cout
     * @param str Строка которая выводится в консоль.
     * @param add_threadid Добавить в сообщение id потока в котором выполняется эта функция.
     */
    void console(const std::string& str, bool add_threadid = true);

    /**
     * @brief Записывает лог в консоль. std::cerr
     * @param str Строка которая выводится в консоль.
     * @param add_threadid Добавить в сообщение id потока в котором выполняется эта функция.
     */
    void conError(const std::string& str, bool add_threadid = true);

    /// @brief Записывает сообщение в конец файла.
    /// @param data 
    /// @param add_threadid Добавить в сообщение id потока в котором выполняется эта функция.
    void writeFile(const std::string& data, bool add_threadid = true);
#endif

#ifndef threadsafe
    /**
     * @brief Записывает лог в консоль. std::cout
     * @param str Строка которая выводится в консоль.
     */
    void console(const std::string& str);

    /**
     * @brief Записывает лог в консоль. std::cerr
     * @param str Строка которая выводится в консоль.
     */
    void conError(const std::string& str);

    /// @brief Записывает сообщение в конец файла.
    /// @param data 
    void writeFile(const std::string& data);
#endif

private:
    std::string currentTime();
    std::string getThreadID();

protected:
    AbstractLogger() = default;
};
