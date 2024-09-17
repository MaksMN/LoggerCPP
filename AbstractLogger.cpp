#include "AbstractLogger.h"

AbstractLogger::~AbstractLogger() {}

void AbstractLogger::LogFileInitialize(const std::string& file_path, mode_t perms)
{
    try
    {
        auto _log_file = std::make_unique<File>(file_path, File::open_mode::w, perms);
        log_file = std::move(_log_file);
        log_file_init = log_file != nullptr;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Log file initialization failed. Reason: " << e.what() << '\n';
        throw;
    }
}

#ifdef threadsafe
void AbstractLogger::console(const std::string& str, bool add_threadid)
{

    std::lock_guard<std::mutex> lock(mutex);
    std::string threadIdStr;
    if (add_threadid)
    {
        threadIdStr = "[THREAD " + getThreadID() + "]: ";
    }
    std::cout << threadIdStr << str << std::endl;
}

void AbstractLogger::conError(const std::string& str, bool add_threadid)
{

    std::lock_guard<std::mutex> lock(mutex);
    std::string threadIdStr;
    if (add_threadid)
    {
        threadIdStr = "[THREAD " + getThreadID() + "]: ";
    }
    std::cerr << threadIdStr << str << std::endl;
}

void AbstractLogger::writeFile(const std::string& data, bool add_threadid)
{

    std::lock_guard<std::mutex> lock(mutex);
    std::string str = "[" + currentTime() + "] ";
    if (add_threadid)
    {
        str += "[THREAD " + getThreadID() + "]: ";
    }
    log_file->appendNewLock(str + data);
}
#endif

#ifndef threadsafe
void AbstractLogger::console(const std::string& str)
{
    std::cout << str << std::endl;
}

void AbstractLogger::conError(const std::string& str)
{
    std::cerr << str << std::endl;
}

void AbstractLogger::writeFile(const std::string& data)
{
    std::string str = "[" + currentTime() + "] ";
    log_file->appendNewLock(str + data);
}
#endif

std::string AbstractLogger::currentTime()
{
    std::chrono::system_clock::time_point time_point = std::chrono::system_clock::now();;
    std::time_t time = std::chrono::system_clock::to_time_t(time_point);
    std::tm* local_time = std::localtime(&time);

    std::stringstream ss;
    ss << std::put_time(local_time, "%D %X");
    return ss.str();
}

std::string AbstractLogger::getThreadID()
{
    std::ostringstream oss;
    oss << std::this_thread::get_id();
    std::string str = oss.str();
    return str;
}
