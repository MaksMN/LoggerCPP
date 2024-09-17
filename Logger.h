#pragma once

#include "AbstractLogger.h"

class Logger
{
private:

    class _log  final : public AbstractLogger {};
    static std::shared_ptr<AbstractLogger> instance;
public:
    static std::shared_ptr<AbstractLogger> i();
};

