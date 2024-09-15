#include "AbstractLogger.h"

AbstractLogger::~AbstractLogger() {}

void AbstractLogger::LogFileInitialize(const std::string& file_path, mode_t perms)
{
    auto _log_file = std::make_unique<File>(file_path, perms);
    log_file = std::move(_log_file);
    log_file_init = log_file != nullptr;
    if (!log_file)
        con_error("Error LogFileInitialize():\n" + log_file->error_message());
}

void AbstractLogger::console(const std::string& str, bool add_threadid)
{
    std::lock_guard<std::mutex> lock(mutex);
    std::string threadIdStr;
    if (add_threadid)
    {
        std::ostringstream oss;
        oss << std::this_thread::get_id();
        threadIdStr = "[THREAD " + oss.str() + "]: ";
    }
    std::cout << threadIdStr << str << std::endl;
}

void AbstractLogger::con_error(const std::string& str, bool add_threadid)
{
    std::lock_guard<std::mutex> lock(mutex);
    std::string threadIdStr;
    if (add_threadid)
    {
        std::ostringstream oss;
        oss << std::this_thread::get_id();
        threadIdStr = "[THREAD " + oss.str() + "]: ";
    }
    std::cerr << threadIdStr << str << std::endl;
}

void AbstractLogger::write_file(const std::string& data, bool add_threadid)
{
    std::lock_guard<std::mutex> lock(mutex);
    std::string str = "[" + currentTime() + "] ";
    if (add_threadid)
    {
        std::ostringstream oss;
        oss << std::this_thread::get_id();
        str += "[THREAD " + oss.str() + "]: ";
    }
    log_file->append_lock(str + data + "\n");
}

bool AbstractLogger::file_initialized()
{
    return log_file_init;
}

std::string AbstractLogger::currentTime()
{
    std::chrono::system_clock::time_point time_point = std::chrono::system_clock::now();;
    std::time_t time = std::chrono::system_clock::to_time_t(time_point);
    std::tm* local_time = std::localtime(&time);

    std::stringstream ss;
    ss << std::put_time(local_time, "%D %X");
    return ss.str();
}