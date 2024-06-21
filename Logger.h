#pragma once

#include "ILogger.h"

class Logger
{
private:
    class _log  final : public ILogger {};

public:
    static const std::shared_ptr<ILogger> log;
};

