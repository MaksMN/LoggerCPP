#include "Logger.h"

std::shared_ptr<AbstractLogger> Logger::instance = nullptr;

std::shared_ptr<AbstractLogger> Logger::i()
{
    if (!instance)
        instance = std::shared_ptr<AbstractLogger>(new Logger::_log);
    return instance;
}
