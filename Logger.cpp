#include "Logger.h"

const std::shared_ptr<ILogger> Logger::log = std::make_shared<Logger::_log>();
