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

class AbstractLogger
{
private:
    std::mutex mutex;
    std::unique_ptr<File> log_file;
    bool log_file_init = false;
public:
    virtual ~AbstractLogger() = 0;
    void LogFileInitialize(const std::string& file_path, mode_t perms = 0600);

    /**
     * @brief Записывает лог в консоль.
     * @param str Строка которая выводится в консоль.
     * @param add_threadid Добавить в сообщение id потока в котором выполняется эта функция.
     */
    void console(const std::string& str, bool add_threadid = true);

    void con_error(const std::string& str, bool add_threadid = true);

    /// @brief Записывает сообщение в конец файла.
    /// @param data 
    /// @param add_threadid Добавить в сообщение id потока в котором выполняется эта функция.
    void write_file(const std::string& data, bool add_threadid = true);

    bool file_initialized();

private:
    std::string currentTime();
protected:
    AbstractLogger() = default;
};
