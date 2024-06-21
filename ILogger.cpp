#include "ILogger.h"

ILogger::~ILogger() {}

void ILogger::LogFileInitialize(const std::string& file_path, mode_t perms)
{
    auto _log_file = std::make_unique<File>(file_path, perms);
    log_file = std::move(_log_file);
    log_file_init = log_file != nullptr;
    if (!log_file)
        con_error("Error LogFileInitialize():\n" + log_file->error_message());
}

void ILogger::console(const std::string& str, bool add_threadid)
{
    mutex.lock();
    std::string threadIdStr;
    if (add_threadid)
    {
        std::ostringstream oss;
        oss << std::this_thread::get_id();
        threadIdStr = "[THREAD " + oss.str() + "]: ";
    }
    std::cout << threadIdStr << str << std::endl;
    mutex.unlock();
}

void ILogger::con_error(const std::string& str, bool add_threadid)
{
    mutex.lock();
    std::string threadIdStr;
    if (add_threadid)
    {
        std::ostringstream oss;
        oss << std::this_thread::get_id();
        threadIdStr = "[THREAD " + oss.str() + "]: ";
    }
    std::cerr << threadIdStr << str << std::endl;
    mutex.unlock();
}

void ILogger::write_file(const std::string& data, bool add_threadid)
{
    mutex.lock();
    std::string str = "[" + currentTime() + "] ";
    if (add_threadid)
    {
        std::ostringstream oss;
        oss << std::this_thread::get_id();
        str += "[THREAD " + oss.str() + "]: ";
    }
    log_file->append(str + data + "\n");
    mutex.unlock();
}

bool ILogger::file_initialized()
{
    return log_file_init;
}

std::string ILogger::currentTime()
{
    std::chrono::system_clock::time_point time_point = std::chrono::system_clock::now();;
    std::time_t time = std::chrono::system_clock::to_time_t(time_point);
    std::tm* local_time = std::localtime(&time);

    std::stringstream ss;
    ss << std::put_time(local_time, "%D %X");
    return ss.str();
}